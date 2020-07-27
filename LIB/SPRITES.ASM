; $Header: h:\toons\rcs\SPRITES.ASM_v 1.1 1994/02/19 22:48:27 KENH Exp $
;{----------------------------------------------------------------------}
;{	SPRITES.S							}
;{	  Sprite Routines Module					}
;{	  Written BY: Kenneth L. Hurley					}
;{	  Futurescape Productions Inc.					}
;{----------------------------------------------------------------------}

;
; $Log: SPRITES.ASM_v $
; Revision 1.1  1994/02/19  22:48:27  KENH
; .
;
;

		include	macros.inc
		include equates.inc
		include sega.inc
		include format.inc

		OPT	LLBL

MAXSPRITES	equ	80
MAXSTATICSPRITES equ	10

		XREF	DlChars
		XREF	addDMAQueue
		XDEF	_Work_Sprlist 
		XDEF	_StaticSprites
		XREF	_SprAttrAddr
		XREF	addDMAQueue
		XREF	waitDMAQueue
		XREF	_SYS_SetPalette
		XDEF	_SYS_LastSpr
		XDEF	_SYS_SprAvail
		XDEF	_SYS_FirstSpr
		XREF	_SYS_LastChar
		XDEF	_remapOffset
		XREF	CopyToVRAM

;{----------------------------------------------------------------------}
;{			Variables go here				}
;{----------------------------------------------------------------------}

		bsection	.bss

_Work_Sprlist	ds.w	(SPRLISTSIZE/2)*MAXSPRITES
_SYS_LastSpr	ds.w	1
_SYS_SprAvail	ds.w	1		; first sprite opening
_SYS_FirstSpr	ds.w	1
_StaticSprites	ds.w	1
HoleSizes	ds.b	MAXSPRITES
HoleChars	ds.w	MAXSPRITES
baseSprChar	ds.w	1
_remapOffset	ds.w	1		; for palette remapping of sprites

_UpdateHoleSafe	ds.b	1
_isHoleUpdate	ds.b	1

;{----------------------------------------------------------------------}
;{	start of code section						}
;{----------------------------------------------------------------------}

		tsection	.text


;{----------------------------------------------------------------------}
;{ Function:	UWORD SendAnimChars(UWORD vdpChar,void *FPAptr);	}
;{ Description:	'C' callable function to download entire animation	}
;{		characters to the vdp					}
;{ Parameters:	anim,frame = animation and frame to download		}
;{		vdpChar = vpd character to download to			}
;{ 		FPAptr = futurescape productions animation file ptr.	}
;{ Returns:	d0 = number of characters downloaded to vdp		}
;{----------------------------------------------------------------------}
		XDEF	_SendAnimChars
_SendAnimChars:
		link	a6,#0
		movem.l	d2,-(sp)

		move.w	8(a6),d0		; vdp character to download
		move.l	10(a6),a0		; animation file ptr.

		move.w	AHCHAROFFSET(a0),d2
		adda.w	d2,a0
		move.w	(a0)+,d2		; save for later
		move.w	d2,d1
		
		lsl.w	#5,d1			; total # bytes
		lsl.w	#5,d0			; to vdp address
		jsr	addDMAQueue		; add to dma queue

		move.w	d2,d0			; return # characters dma'ed

		movem.l	(sp)+,d2
		unlk	a6
		rts

;{----------------------------------------------------------------------}
;{ Function:	void ClearSprites(void);				}
;{ Description:	'C' callable clear the sprites in sprite list and 	}
;{		disable all on the screen				}
;{ Parameters:	.							}
;{ Returns:	.							}
;{----------------------------------------------------------------------}
		XDEF	_ClearSprites
_ClearSprites:
		move.l	#_Work_Sprlist,a0
		clr.l	(a0)+			; clear first sprite
		clr.l	(a0)+

		subq.w	#8,a0
		move.w	_SprAttrAddr,d0
		move.w	#8,d1
		jsr	addDMAQueue		; add to dma queue
		rts

;{----------------------------------------------------------------------}
;{ Function:	UWORD SendFrameChars(UWORD anim, UWORD frame, 		}
;{			UWORD vdpChar, void *FPAptr);			}
;{ Description:	'C' callable function to download a frames characters	}
;{		to the vdp.						}
;{ Parameters:	anim,frame = animation and frame to download		}
;{		vdpChar = vpd character to download to			}
;{ 		FPAptr = futurescape productions animation file ptr.	}
;{ Returns:	d0 = number of characters downloaded to vdp		}
;{----------------------------------------------------------------------}
		XDEF	_SendFrameChars
_SendFrameChars:
		link	a6,#0
		movem.l	d2-d4,-(sp)

		move.w	8(a6),d2		; animation
		move.w	10(a6),d3		; frame
		move.w	12(a6),d4		; vdp character to download
		move.l	14(a6),a0		; animation file ptr.

		move.l	a0,a1			; save for later
		bsr	getFrameChars		; get the frames character info
		move.l	a0,d1
		move.l	a1,a0
		move.l	d1,a1

		move.w	AHCHAROFFSET(a0),d2
		adda.w	d2,a0
		move.w	d0,d1			; into dma register
		move.w	d1,d2			; save for later
		lsl.w	#5,d1			; total # bytes
		move.w	SAATTRIBUTES(a1),d0	; get character # in file
		and.l	#$7ff,d0
		lsl.l	#5,d0			; make char offset in file
		adda.l	d0,a0			; get actual pointer
		add.w	#2,a0			; bypass character count
		move.w	d4,d0			; vdp character
		lsl.w	#5,d0			; to vdp address
		jsr	addDMAQueue		; add to dma queue

		move.w	d2,d0			; return # characters dma'ed

		movem.l	(sp)+,d2-d4
		unlk	a6
		rts


;{----------------------------------------------------------------------}
;{ Function:	SendFrameChars						}
;{ Description:	Send frames character set over to VRAM			}
;{ Parameters:	a0 = pointer to animation structure			}
;{ Returns:	d0 = character loaded into				}
;{----------------------------------------------------------------------}

SendFrameChars:
		move.w	AHCHAROFFSET(a0),d0
		lea	0(a0,d0.w),a0
		jsr	DlChars		; download character set
		rts

;{----------------------------------------------------------------------}
;{ Function:	UWORD GetFrameChars(UWORD anim, UWORD frame, 		}
;{			void *animptr);					}
;{ Description:	'C' callable function to return # of characters in 	}
;{		animation						}
;{ Parameters:	anim = animation #					}
;{		frame = frame #						}
;{		animptr = pointer to FPA file				}
;{ Returns:	d0 = # characters in frame				}
;{----------------------------------------------------------------------}
		XDEF	_GetFrameChars
_GetFrameChars:
		link	a6,#0

		movem.l	d2-d7/a1-a2,-(sp)

		move.w	8(a6),d2
		move.w	10(a6),d3
		move.l	12(a6),a0	; get anim file pointer
		bsr	getFrameChars
		movem.l	(sp)+,d2-d7/a1-a2
		unlk	a6
		rts

;{----------------------------------------------------------------------}
;{ Function:	getFrameChars						}
;{ Description:	get starting and ending frame characters from animation	}
;{ Parameters:	d2 = animation #					}
;{		d3 = frame #						}
;{		a0 = pointer to animation structure			}
;{ Returns:	d0 = # characters in frame				}
;{		a0 = pointer to sprite info structure			}
;{----------------------------------------------------------------------}
		XDEF	getFrameChars
getFrameChars:
		movem.l	d2-d7/a1-a2,-(sp)

		move.l	a0,a2		; save for later
		bsr	getFrameInfo	; get current frames address

		btst.b	#2,AHFLAGS+1(a2) ; is it a background animation?
		beq.s	.notBackAnim

		clr.w	d0
		clr.w	d1
		move.b	SAHVLINK(a0),d0	; get horizontal size
		move.b	SAHVLINK+1(a0),d1 ; and vertical size (y)
		mulu	d1,d0		; and get number of characters
		bra.s	.Exit
.notBackAnim:
		move.l	a0,a1		; save first animation for later
		move.w	-SAHEADSIZE(a0),d5 ; get number of sprites in frame
		subq.w	#1,d5		; for dbra
		lea	sprite2Char,a2	; conversion of bits to # char table
		clr.w	d6		; current count of characters
.countLoop:
		move.w	SAHVLINK(a0),d7	; get size of character
		lsr.w	#7,d7		; into low nibble for table access
		and.w	#$1e,d7
		add.w	0(a2,d7.w),d6	; add in character count
		lea	SASIZE(a0),a0	; next sprite of frame
		dbra	d5,.countLoop	; and do entire list

		move.w	d6,d0
		move.l	a1,a0		; return first sprite info pointer
.Exit:
		movem.l	(sp)+,d2-d7/a1-a2
		rts

;{----------------------------------------------------------------------}
;{ Function:	short Disp1AnimFrame(short x, short y, short anim, 	}
;{			short frame, short vdpChar, long address);	}
;{ Description:	'C' callable routine to draw animation frame		}
;{ Parameters:	x,y = position of sprite on the screen			}
;{		anim,frame = animation # and frame #			}
;{		vdpChar = vdp character to download to			}
;{		address = address of animation file			}	
;{ Returns:	d0.w = # characters loaded				}
;{----------------------------------------------------------------------}
		XDEF	_Disp1AnimFrame
_Disp1AnimFrame:
		link	a6,#0

		movem.l	d2-d4,-(sp)

		move.w	8(a6),d0	; get x position
		move.w	10(a6),d1	; and y position
		move.w	12(a6),d2	; and animation
		move.w	14(a6),d3	; and frame
		move.w	16(a6),d4	; character to download to
		move.l	18(a6),a0	; and get address of sprite
	
		bsr	Disp1AnimFrame	; call assembler routine

		movem.l	(sp)+,d2-d4

		unlk	a6
		rts

;{----------------------------------------------------------------------}
;{ Function:	void getFrameWH(short anim, short frame, 		}
;{			void *FPAaddress, short *width, short *height);	}
;{ Descripion:	get width and height for a sprite or bitmap		}
;{ Parameters:	anim,frame = animation and frame for FPA file		}
;{		width, height, pointers to words to receive information	}
;{		FPAaddress = address of Futurescape Sprite file		}
;{ Returns:	.							}
;{----------------------------------------------------------------------}
		XDEF	_GetFrameWH
_GetFrameWH:
		link	a6,#0
		movem.l	d2-d5/a0-a2,-(sp)

		move.w	8(a6),d2
		move.w	10(a6),d3
		move.l	12(a6),a0
		move.l	a0,a2		; save for later
		bsr	getFrameInfo

		lea	-SAHEADSIZE(a0),a0
		move.w	SAWIDTH(a0),d0
		move.w	SAHEIGHT(a0),d1

		move.l	16(a6),a1
		move.w	d0,(a1)		; send width

		move.l	20(a6),a1
		move.w	d1,(a1)		; send height
.allDone:

		movem.l	(sp)+,d2-d5/a0-a2
		unlk	a6
		rts

;{----------------------------------------------------------------------}
;{ Function:	short _SprFrametoMap(short anim, short frame, 		}
;{					short vdpChar, long FPAaddress,	}
;{					long mapAddress);		}
;{ Description:	'C' callable routine to draw animation frame into char	}
;{			character buffer				}
;{ Parameters:	x,y = position of sprite in the map - 8 bit boundary	}
;{		anim,frame = animation # and frame #			}
;{		vdpChar = vdp character to download to			}
;{		FPAaddress = address of animation file			}
;{		mapAddress = address of map to draw into		}
;{ Returns:	d0.w = # characters loaded				}
;{----------------------------------------------------------------------}
		XDEF	_SprFrametoMap
_SprFrametoMap:
		link	a6,#0

		movem.l	d2-d6/a1-a4,-(sp)

		move.w	8(a6),d2	; and animation
		move.w	10(a6),d3	; and frame
		move.w	12(a6),d4	; character to download to
		move.l	14(a6),a0	; and get address of sprite
		move.l	18(a6),a2	; map address

		bsr	getFrameInfo	; get current frames address

		move.w	-SAHEADSIZE(a0),d5 ; get number of sprites in frame
		subq.w	#1,d5		; for dbra
		move.w	d4,d6		; initial character to start at
.countLoop:
		move.b	SAHVLINK(a0),d0	; get size of character
		move.w	d0,d1
		and.w	#%11,d0		; vertical size
		lsr.w	#2,d1
		and.w	#%11,d1		; horizontal size
		move.l	a2,a4		; save map address for later
.horzLoop:
		move.w	d1,d7
		move.l	a4,a3		; save for later
		adda.w	#2,a4		; next horizontal for later
.vertLoop:
		move.w	d6,(a3)
		adda.w	#MAPWIDTH*2,a3	; next vertical position
		addq.w	#1,d6		; next character
		dbra	d7,.vertLoop
		dbra	d1,.horzLoop

		move.w	SAXPOS(a0),d0	; get current x position
		move.w	SAYPOS(a0),d1	; get current y position
		adda.w	#SASIZE,a0

		sub.w	SAYPOS(a0),d1
		lsl.w	#4,d1		; /8*(MAPWIDTH*2)
		and.w	#$fff8,d1
		add.w	d1,a2		; next y map address

		sub.w	SAXPOS(a0),d0	; get diffence x position
		asr.w	#2,d0		; /8*(2 WORDS per x)
		and.w	#$fffe,d0	; mask to word
		add.w	d0,a2

		dbra	d5,.countLoop	; and do entire list

		sub.w	d4,d6		; number of characters put out
		and.l	#$ffff,d6
		move.l	d6,d1		; save for dma routine
		lsl.l	#5,d1		; d6 = count of 8x8 characters * 32 bytes

		movea.l	a1,a0		; address of source bytes

		move.w	d4,d0		; address of destination character
		lsl.w	#5,d0		; * 32
		jsr	addDMAQueue	; and send them next frame

		move.w	d6,d0

		movem.l	(sp)+,d2-d6/a1-a4

		unlk	a6
		rts


;{----------------------------------------------------------------------}
;{ Function:	Disp1AnimFrame						}
;{ Description:	Display 1 frame character and send chars over to VRAM	}
;{ Parameters:	d0 = x position						}
;{		d1 = y position						}
;{		d2 = animation #					}
;{		d3 = frame #						}
;{		d4 = character to download to				}
;{		a0 = pointer to animation structure			}
;{ Returns:	d0 = # characters loaded				}
;{----------------------------------------------------------------------}
Disp1AnimFrame:
		movem.l	d1-d7/a2,-(sp)

		movem.l	d0-d2/a0,-(sp)

		move.l	a0,-(sp)
		bsr	getFrameInfo	; get current frames address

		move.w	SAATTRIBUTES(a0),d0
		and.l	#$1fff,d0
		move.w	d0,baseSprChar	; base characters to start at.
		lsl.l	#5,d0		; * 32 for source offset
		move.l	(sp)+,a1	; get base of file
		move.w	AHCHAROFFSET(a1),d5
		and.l	#$ffff,d5
		add.l	d5,d0 		; add in characters offset in file
		addq.l	#2,d0		; bypass # characters
		adda.l	d0,a1		; and now a1 has source address

		move.w	-SAHEADSIZE(a0),d5 ; get number of sprites in frame
		subq.w	#1,d5		; for dbra
		bpl.s	.isOk
		movem.l	(sp)+,d0-d2/a0
		clr.w	d0
		bra.s	.AllDone
.isOk:
		lea	sprite2Char,a2	; conversion of bits to # char table
		clr.w	d6		; current count of characters
.countLoop:
		move.w	SAHVLINK(a0),d7	; get size of character
		lsr.w	#7,d7		; into low nibble for table access
		and.w	#$1e,d7
		add.w	0(a2,d7.w),d6	; add in character count
		lea	SASIZE(a0),a0	; next sprite of frame
		dbra	d5,.countLoop	; and do entire list

		and.l	#$ffff,d6
		lsl.l	#5,d6		; d6 = count of 8x8 characters * 32 bytes
		move.l	d6,d1		; save for dma routine

		movea.l	a1,a0		; address of source bytes

		move.w	d4,d0		; address of destination character
		lsl.w	#5,d0		; * 32
		tst.b	_isHoleUpdate
		beq.s	.NotHoleUpdate
		jsr	CopyToVRAM
		bra.s	.HoleUpdated
.NotHoleUpdate:
		jsr	addDMAQueue	; and send them next frame
.HoleUpdated:
		move.w	d1,d7

		movem.l	(sp)+,d0-d2/a0

		jsr	DispFrame	; send sprite attribute lists
		clr.w	baseSprChar	; zero out offset for normal sprite

		move.w	d7,d0
		lsr.w	#5,d0		; return # characters loaded
.AllDone:
		movem.l	(sp)+,d1-d7/a2
		rts

;{----------------------------------------------------------------------}
;{ Function:	void getFrameInfo(UWORD anim, UWORD frame, 		}
;{			void *FPAptr, UWORD *maxanims, UWORD *maxframes,}
;{			void **sprInfo, void **charData);		}
;{ Description:	'C' callable function to get information about an 	}
;{		animation file.						}
;{ Parameters:	anim, frame = animation and frame in FPA file		}
;{ 		FPAptr = Futurescape Productions animation file ptr.	}
;{		maxanims = word pointer to receive max animations	}
;{		maxframes = word pointer to receive max frames		}
;{		sprInfo = ptr to ptr to receive sprite Info pointer	}
;{		charData = ptr to ptr to receive character data ptr.	}
;{ Returns:	.							}
;{----------------------------------------------------------------------}
		XDEF	_getFrameInfo
_getFrameInfo:
		link	a6,#0
		movem.l	d2-d3/a1-a2,-(sp)

		move.w	8(a6),d2
		move.w	10(a6),d3
		move.l	12(a6),a0	; get FPA file information
		bsr	getFrameInfo

		move.l	16(a6),a2	; get pointer to word
		cmpa.l	#0,a2
		beq.s	.NoAnim
		move.w	d1,(a2)		; and set maximum animations
.NoAnim:

		move.l	20(a6),a2	; get pointer to word
		cmpa.l	#0,a2
		beq.s	.NoFrame
		move.w	d0,(a2)		; and set maximum frames
.NoFrame:
		move.l	24(a6),a2
		cmpa.l	#0,a2
		beq.s	.NoInfo
		move.l	a0,(a2)
.NoInfo:
		move.l	28(a6),a2
		cmpa.l	#0,a2
		beq.s	.noCharData
		move.l	a1,(a2)
.noCharData:

		movem.l	(sp)+,d2-d3/a1-a2
		unlk	a6
		rts

;{----------------------------------------------------------------------}
;{ Function:	getFrameInfo						}
;{ Description: get Frames information and return it			}
;{ Parameters:	d2 = animation #					}
;{		d3 = frame #						}
;{		a0 = Pointer to Animation Header			}
;{ Returns:	d0 = maximum frames					}
;{		d1 = maximum animations in file				}
;{		a0 = Pointer to Sprite Information			}
;{		a1 = Pointer to actual data				}
;{----------------------------------------------------------------------}
		XDEF	getFrameInfo
getFrameInfo:
		movem.l	d1-d7,-(sp)

		move.l	a0,a1
		move.w	AHALISTOFFSET(a0),d5	; get animation list offset
		lsl.w	#2,d2
		add.w	d2,d5
		lea	0(a0,d5.w),a0
		move.w	(a0)+,d7	; number of frames in animations
		cmp.w	d7,d3		; see if in range
		bge.s	.GFIExit
		move.w	(a0),d5		; anim to frame offset
		lsl.w	#1,d3
		add.w	d3,d5
		lea	0(a1,d5.w),a0	; get to framelists
		move.w	(a0),d5		; get offset to sprite info
		lea	0(a1,d5.w),a0
		add	#SAHEADSIZE,a0	; skip # sprites and hotspot offset
		clr.l	d0
		move.w	SAATTRIBUTES(a0),d0	; get character number
		btst.b	#1,AHFLAGS+1(a1)
		bne.s	.isBitMap
		and.l	#$1fff,d0
.isBitMap:
		lsl.l	#5,d0		; * 32 bytes per character
		clr.l	d1
		move.w	AHCHAROFFSET(a1),d1
		add.l	d1,d0
		add.l	#2,d0
		add.l	d0,a1
.GFIExit:
		move.w	d7,d0
		movem.l	(sp)+,d1-d7
		rts

;{----------------------------------------------------------------------}
;{ Function:	_DispScaledSprite					}
;{ Description:	Put Scaled sprite list in sprite list structure		}
;{ Parameters:	d0 = x position on screen				}
;{		d1 = y position on screen				}
;{		D4 = character # loaded into				}
;{		a0 = pointer to scaled list				}
;{ Returns:	.							}
;{----------------------------------------------------------------------}
_SendScaledSprite:

		movem.l	d0-d7/a0-a2,-(sp)
		bra.s	SendSpriteFrames

;{----------------------------------------------------------------------}
;{ Function:	void DispFrame(UWORD xpos, UWORD ypos, UWORD anim,	}
;{			UWORD frame, UWORD vdpchar, long FPAfile);	}
;{ Description:	put frame in work_sprlist structures so will be 	}
;{		displayed when sendsprlist is called.			}
;{ Parameters:	xpos, ypos = x,y position on screen			}
;{		anim, frame = animation & frame of sprite to show	}
;{		vdpchar = vdp character that was downloaded to.		}
;{		FPAfile = futurescape production animation file ptr	}
;{ Returns:	.							}
;{----------------------------------------------------------------------}
		XDEF	_DispFrame
_DispFrame:
		link	a6,#0
		movem.l	d2-d4,-(sp)

		move.w	8(a6),d0
		move.w	10(a6),d1
		move.w	12(a6),d2
		move.w	14(a6),d3
		move.w	16(a6),d4
		move.l	18(a6),a0
		bsr	DispFrame

		movem.l	(sp)+,d2-d4
		unlk	a6
		rts

;{----------------------------------------------------------------------}
;{ Function:	DispFrame						}
;{ Description: Put Frame is Display list structure			}
;{ Parameters:	d0 = x position						}
;{ 		d1 = y position						}
;{		d2 = animation #					}
;{		d3 = frame #						}
;{		d4 = char # for start of sprite data			}
;{		a0 = Pointer to Animation Header			}
;{ Returns:	.							}
;{----------------------------------------------------------------------}
		XDEF	DispFrame
DispFrame:
		movem.l	d0-d7/a0-a3,-(sp)

		sf	_UpdateHoleSafe
		movea.l	#spritesize,a3
		move.l	a0,a1
		move.w	AHALISTOFFSET(a0),d5	; get animation list offset
		lsl.w	#2,d2
		add.w	d2,d5
		lea	0(a0,d5.w),a0
		cmp.w	(a0)+,d3	; see if in range
		bge	.DFExit
		move.w	(a0),d5
		lsl.w	#1,d3
		add.w	d3,d5
		lea	0(a1,d5.w),a0	; get to framelists
		move.w	(a0),d5		; get offset to sprite info
		lea	0(a1,d5.w),a0
SendSpriteFrames:
		move.w	(a0)+,d5	; # of sprites in frame
		addq	#2,a0
		move.w	(a0)+,d2	; get width in pixels
		swap	d2		; save for later
		move.w	(a0)+,d6	; get height
		swap	d6
		move.l	#_Work_Sprlist,a2
		move.w	_SYS_SprAvail,d6 ; get first sprite opening
		move.w	d6,d2		; save system last sprite for later
		lsl.w	#3,d6
		lea	0(a2,d6.w),a2	; pointer to sprite lists
		move.w	d2,d6
		add.w	d5,d6
		cmp.w	#MAXSPRITES,d6
		bgt.s	.DFExit		; to many sprites
		subq.l	#1,d5
.SpriteLoop:
		move.w	(a0)+,d3	; get vertical position
		move.b	(a0),d7		; get hsize/vsize
		and.w	#$0f,d7		; mask to hsize/vsize bits
		add.w	d7,d7		; long word index
		add.w	d7,d7
		move.l	0(a3,d7.w),d7	; now have horizontal/vertical size
		btst.l	#CHARVFBIT,d4	; vertically flipped
		beq.s	.noVFFlip
		neg.w	d3		; negate y offset
		swap	d6
		add.w	d6,d3		; adjust to y+height
		swap	d6		; save for later again
		sub.w	d7,d3		; and subtract height of sprite

.noVFFlip:
		add.w	d1,d3		; add in y position
		add.w	#$80,d3
		move.w	d3,(a2)+	; save it
		add.w	#1,d2		; next system last sprite
		move.w	(a0)+,d3
		add.w	d2,d3		; make link
		move.w	d3,(a2)+	; save link info
		move.w	(a0)+,d3	; get character pointer.
		sub.w	baseSprChar,d3
		add.w	_remapOffset,d3	; remap palette if wanted
		add.w	d4,d3		; update character pointer
		move.w	d3,(a2)+
		move.w	(a0)+,d3
		btst.l	#CHARHFBIT,d4	; horizontally flipped?
		beq.s	.noHFlip	; nope
		neg.w	d3		; negate x offset
		swap	d2
		add.w	d2,d3		; adjust to x+width
		swap	d7		; get height of sprite
		sub.w	d7,d3		; and subtract from sprite
		swap	d2		; put d2 back
.noHFlip:
		add.w	d0,d3		; make x position
		add.w	#$80,d3
		move.w	d3,(a2)+	; and store it
		dbra	d5,.SpriteLoop

		move.w	d2,_SYS_SprAvail
		subq.w	#1,d2		; this is last sprite
		move.w	d2,_SYS_LastSpr
		
.DFExit:
		st	_UpdateHoleSafe

		movem.l	(sp)+,d0-d7/a0-a3
		rts

;{----------------------------------------------------------------------}
;{ Function:	UWORD updateFrame(UWORD anim, UWORD frame, 		}
;{				void *animptr);}			}
;{ Description:	'C' callable function to update a frame			}
;{ Parameters:	anim,frame = animatoion # and frame #			}
;{		animptr = pointer to FPA file				}
;{ Returns:	Next frame						}
;{----------------------------------------------------------------------}
		XDEF	_updateFrame
_updateFrame:
		link	a6,#0

		move.w	8(a6),d2
		move.w	10(a6),d0
		move.l	12(a6),a0

		bsr	updateFrame

		cmp.w	#-1,d1		; wrapped
		bne.s	.NoWrap
		move.w	d1,d0
.NoWrap:
		unlk	a6
		rts

;{----------------------------------------------------------------------}
;{ Function:	_updateFrame						}
;{ Description:	update frame for sprite and make sure still in range	}
;{ Parameters:	d0 = frame						}
;{		d2 = animation number					}
;{		a0 = pointer to sprite animation			}
;{ Returns:	d0 = new frame						}
;{		d1 = -1 - wrapped					}
;{----------------------------------------------------------------------}
		XDEF	updateFrame
updateFrame:
		movem.l	d2-d3,-(sp)
		move.w	d0,d1
		add.w	#1,d1
		clr.w	d3
		jsr	getFrameInfo
		cmp.w	d0,d1
		blt	.frameInRange
		clr.w	d1
		move.w	#-1,d0
.frameInRange:
		exg	d1,d0
		movem.l	(sp)+,d2-d3
		rts

;{----------------------------------------------------------------------}
;{ Function:	_sortSprites						}
;{ Description:	sort sprite list 					}
;{ Parameters:	.							}
;{ Returns:	.							}
;{----------------------------------------------------------------------}
_sortSprites:
		rts

;{----------------------------------------------------------------------}
;{ Function:	_SendSprList						}
;{ Description:	Send sprite list to VRAM				}
;{ Parameters:	.							}
;{ Returns:	.							}
;{----------------------------------------------------------------------}
		XDEF	_SendSprList
_SendSprList:
		movem.l	d0-d7/a0-a1,-(sp)

		clr.w	d1
		lea	_Work_Sprlist,a0
		move.w	_SYS_LastSpr,d2
		cmp.w	_StaticSprites,d2
		bne.s	.NotOnlyStatic
		move.w	_StaticSprites,d2
.NotOnlyStatic:
		tst.w	_SYS_SprAvail
		beq.s	.StaticSpritesOnly
		lsl.w	#3,d2
		move.w	d2,d1
		add.w	#8,d1
.StaticSpritesOnly:
		lea	0(a0,d2.w),a1		; get to last sprite in list
		move.w	SLLINK(a1),d3
		and.w	#$0f00,SLLINK(a1)	; make last in list
		move.w	_SprAttrAddr,d0
		lea	_Work_Sprlist,a0
		move.w	_StaticSprites,d2
		beq.s	.NoStaticSprites2	; none so don't bypass 0
		subq	#1,d2			; need last sprite link changed
		lsl.w	#3,d2			; size of sprite info (*8)
		add.w	d2,d0			; don't update static sprite list
		add.w	d2,a0			; source address
		sub.w	d2,d1			; # bytes to move is reduced
.NoStaticSprites2:

		tst.w	d1
		beq.s	.noDMA
		move.w	d1,d2			; save last sprite #

		jsr	addDMAQueue
		jsr	waitDMAQueue
.noDMA:
		move.w	_SYS_FirstSpr,d0
		move.w	d0,_SYS_SprAvail	; zero out sprites.
		subq.w	#1,d0
		bpl.s	.IsPositive
		clr.w	d0
.IsPositive:
		move.w	d0,_SYS_LastSpr		; zero out sprites.
		move.w	d3,SLLINK(a1)		; put link back in
.SLExit:
		movem.l	(sp)+,d0-d7/a0-a1
		rts

;{----------------------------------------------------------------------}
;{ Function:	void SetSpritePal(void *sprStruct);			}
;{ Description:	set the palette for the sprite structure		}
;{ Parameters:	sprStruct = FPA file pointer				}
;{ Returns:	.							}
;{----------------------------------------------------------------------}
		XDEF	_SetSpritePal
_SetSpritePal:
		link	a6,#0
		move.l	8(a6),a0
		bsr	SetSpritePal		; and set the palette
		unlk	a6
		rts

;{----------------------------------------------------------------------}
;{ Function:	SetSpritePal						}
;{ Description:	Set the palette from Sprite structure			}
;{ Parameters:	a0 = pointer to sprite structure			}
;{ Returns:	.							}
;{----------------------------------------------------------------------}
		XDEF	SetSpritePal
SetSpritePal:
		move.w	(a0),d0		; get palette offset
		lea	0(a0,d0.w),a0
		move.l	a0,-(sp)
		jsr 	_SYS_SetPalette
		adda.w	#4,sp
		rts

;{----------------------------------------------------------------------}
;{ Function:	UWORD AddHole(WORD x, WORD y, UWORD anim, UWORD frame,	}
;{			UWORD CharNum, void *animptr);			}
;{ Description:	'C' callable function to add a hole in the sprite list	}
;{		that is the biggest sprite in the animation.  This 	}
;{		allows multiple sized sprites to be placed in the same	}
;{		sprite area						}
;{ Parameters:	x,y = x,y position on screen to put animation		}
;{ 		anim,frame = animation and frame of sprites		}
;{		CharNum = character number to download			}
;{		animptr = animation pointer				}
;{ Returns:	hole number (index into work_sprlist).			}
;{----------------------------------------------------------------------}
		XDEF	_AddHole
_AddHole:
		link	a6,#0
		movem.l	d2-d7/a1-a3,-(sp)	; save registers were gonna use

;
; ----- find the number of frames in this animation
;
		move.w	12(a6),d2		; get animation #
		clr.w	d3			; dummy first frame
		move.l	18(a6),a0		; animation pointer
		bsr	getFrameInfo		; and get frame information
		move.w	d0,d7			; save maximum frames
		subq.w	#1,d7			; for dbra
;
; ----- next find the biggest sprite & biggest in characters
;
		move.w	12(a6),d2		; animation #
		clr.w	d3			; starting frame #
		clr.w	d6			; current highest char count
		clr.w	d5			; current biggest sprite count
.FindLoop:
		move.l	18(a6),a0		; get animation pointer
		bsr	getFrameChars		; get number of chars in sprite
		cmp.w	d0,d6
		bgt.s	.NotBiggestChar		; not biggest sprite in chars
		move.w	d0,d6			; bigger than last one
.NotBiggestChar:
		move.w	-SAHEADSIZE(a0),d0	; get number of sprites
		cmp.w	d0,d5			; is this the biggest so far?
		bgt.s	.NotBiggestSpr
		move.w	d0,d5			; now have new biggest sprite
.NotBiggestSpr:
		addq.w	#1,d3			; next frame
		dbra	d7,.FindLoop		; loop through all sprites

		move.w	16(a6),d4		; get current to download to
		add.w	d4,d6			; allocate this many chars

		move.w	_SYS_LastSpr,d7		; get current opening
		add.w	d7,d5			; and this many sprites
;
; ----- Now display the frame wanted
;
		move.w	8(a6),d0		; x position
		move.w	10(a6),d1		; y position
		move.w	12(a6),d2		; animation #
		move.w	14(a6),d3		; frame #
		move.l	18(a6),a0		; animation pointer
		bsr	Disp1AnimFrame

		move.w	_SYS_SprAvail,d0	; get current sprite opening
		move.l	#HoleSizes,a1
		move.b	d0,0(a1,d7.w)		; save off current end hole 
		move.l	#HoleChars,a1
		move.w	d4,0(a1,d7.w)		; save off starting character

		and.w	#$7ff,d6
		move.w	d6,_SYS_LastChar	; move character count up.
		move.w	d5,_SYS_SprAvail	; and reserve enough for biggest

		move.w	d7,d0
		IFEQ	SPRLISTSIZE-8
		add.w	d0,d0
		add.w	d0,d0
		add.w	d0,d0			; and get to structure
		ELSEC
		mulu	#SPRLISTSIZE,d0
		ENDC

		move.l	#_Work_Sprlist,a0
		move.w	SLLINK(a0,d0.w),d1	; get current link
		and.w	#$0f00,d1		; mask to just info
		move.b	d5,d1			; and get new size
		move.w	d1,SLLINK(a0,d0.w)	; and relink to new bigger size

		move.w	d7,d0			; return hole number

		movem.l	(sp)+,d2-d7/a1-a3	; save registers were gonna use
		unlk	a6
		rts

;{----------------------------------------------------------------------}
;{ Function:	void UpdateHole(WORD x, WORD y, UWORD anim, UWORD frame,}
;{			void *animptr, UWORD holenum, UWORD newSpr);	}
;{ Description:	'C' callable function to update a hole in the sprite 	}
;{		list to a new frame					}
;{ Parameters:	x,y = x,y position on screen to put animation		}
;{ 		anim,frame = animation and frame of sprites		}
;{		animptr = animation pointer				}
;{		hole number (index into work_sprlist).			}
;{		NewSpr says whether to download new sprite characters	}
;{ Returns:	.							}
;{----------------------------------------------------------------------}
		XDEF	_UpdateHole
_UpdateHole:
		link	a6,#0
		movem.l	d2-d7/a1-a3,-(sp)	; save registers were gonna use

;		tst.b	_UpdateHoleSafe
;		beq	.NotSafe

		st	_isHoleUpdate

		move.w	20(a6),d7		; hole number
		move.l	#HoleSizes,a1
		clr.w	d6
		move.b	0(a1,d7.w),d6		; get last sprite in hole
		move.w	d6,d3			; save for later
		IFEQ	SPRLISTSIZE-8
		add.w	d6,d6
		add.w	d6,d6
		add.w	d6,d6			; multiply by 8
		ELSEC
		.ECHO	SPRLISTSIZE != 8
		FAIL	1
		ENDC
		move.l	#_Work_Sprlist,a2
		move.w	SLLINK(a2,d6.w),d5	; get last sprite in holes link
		move.l	#HoleChars,a1
		move.w	0(a1,d7.w),d4		; get first character of sprhole
		move.w	_SYS_SprAvail,d0
		move.w	d7,_SYS_SprAvail	; temporarily set last sprite
		move.w	d0,d7			; save for later

		tst.w	22(a6)			; want to download characters?
		beq.s	.NoNewChars

		move.w	8(a6),d0
		move.w	10(a6),d1
		move.w	12(a6),d2
		move.w	14(a6),d3
		move.l	16(a6),a0
		bsr	Disp1AnimFrame		; display new frame

		move.w	_SYS_SprAvail,d0
		move.w	20(a6),d6		; get hole number
		move.l	#HoleSizes,a1
		move.b	d0,0(a1,d6.w)		; save new last sprite in hole

		move.w	_SYS_LastSpr,d0		; save for later

		IFEQ	SPRLISTSIZE-8
		add.w	d0,d0			; get new last sprite in hole
		add.w	d0,d0
		add.w	d0,d0
		ELSEC
		.ECHO	SPRLISTSIZE != 8
		FAIL	1
		ENDC

		move.l	#_Work_Sprlist,a0
		move.b	d5,SLLINK+1(a0,d0.w)	; save new link

		move.w	d7,_SYS_SprAvail	; reset first opening in sprlist
		subq.w	#1,d5
		move.w	d7,_SYS_LastSpr
		bra	.NotSafe
.NoNewChars:
		move.w	d3,d4			; save size in sprites of hole
		move.w	20(a6),d6		; get hole number
		IFEQ	SPRLISTSIZE-8
		add.w	d6,d6
		add.w	d6,d6
		add.w	d6,d6			; multiply by 8
		ELSEC
		.ECHO	SPRLISTSIZE != 8
		FAIL	1
		ENDC
		move.w	8(a6),d0
		add.w	#$80,d0
		move.w	10(a6),d1
		add.w	#$80,d1
		move.l	#_Work_Sprlist,a2
		lea	0(a2,d6.w),a3		; get to first sprite
		move.w	SLX(a3),d2		; get orginal x,y
		move.w	SLY(a3),d3
		move.w	d4,d5			; also save for later
		subq.w	#1,d4			; for dbra
.updatexyLoop:
		sub.w	d2,SLX(a3)
		sub.w	d3,SLY(a3)
		add.w	d0,SLX(a3)
		add.w	d1,SLY(a3)
		addq.w	#8,a3
		dbra	d4,.updatexyLoop

		lea	0(a2,d6.w),a0		; source address
		move.w	d5,d1			; length in sprites
		IFEQ	SPRLISTSIZE-8
		add.w	d1,d1
		add.w	d1,d1
		add.w	d1,d1
		ELSEC
		.ECHO	SPRLISTSIZE != 8
		FAIL	1
		ENDC
		move.w	_SprAttrAddr,d0		; address in vram
		add.w	d6,d0			; and holes offset
		jsr	CopyToVRAM
		move.w	d7,_SYS_SprAvail	; reset first opening in sprlist
.NotSafe:
		sf	_isHoleUpdate
		movem.l	(sp)+,d2-d7/a1-a3	; save registers were gonna use
		unlk	a6
		rts

;{----------------------------------------------------------------------}
;{	start of data section						}
;{----------------------------------------------------------------------}

sprite2Char:
		dc.w	1,2,3,4,2,4,6,8,3,6,9,12,4,8,12,16

spritesize:
		dc.l	$080008,$080010,$080018,$080020
		dc.l	$100008,$100010,$100018,$100020
		dc.l	$180008,$180010,$180018,$180020
		dc.l	$200008,$200010,$200018,$200020

		end
