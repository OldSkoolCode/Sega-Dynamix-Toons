; $Header: h:\toons\rcs\MAPS.ASM_v 1.1 1994/02/19 22:48:27 KENH Exp $
;{----------------------------------------------------------------------}
;{	MAPS.S								}
;{	  Map Routines 							}
;{	  Written BY: Kenneth L. Hurley					}
;{	  Futurescape Productions Inc.					}
;{----------------------------------------------------------------------}

;
; $Log: MAPS.ASM_v $
; Revision 1.1  1994/02/19  22:48:27  KENH
; .
;
;

		include	equates.inc
		include	variable.inc
		include sega.inc
		include	format.inc

		OPT	LLBL
;{----------------------------------------------------------------------}
;{			Variables go here				}
;{----------------------------------------------------------------------}

		bsection .bss

;{----------------------------------------------------------------------}
;{	start of code section						}
;{----------------------------------------------------------------------}

		tsection .text

		XREF	addDMAQueue,waitDMAQueue
		XREF	_ScrAAddr,_ScrBAddr
		XREF	findIffHeader
		XREF	getFrameInfo
		XREF	SetPalette

;{----------------------------------------------------------------------}
;{ Function:	short _MapFrametoMap(short x, short y, short anim, 	}
;{				short frame, short vdpChar, 		}
;{				long FPAaddress, long mapAddress);	}
;{ Description:	'C' callable routine to draw animation frame into char	}
;{			character buffer				}
;{ Parameters:	x,y = position of sprite in the map - 8 pixel boundary	}
;{		anim,frame = animation # and frame #			}
;{		vdpChar = vdp character to download to			}
;{		FPAaddress = address of animation file			}
;{		mapAddress = address of map to draw into		}
;{ Returns:	d0.w = # characters loaded				}
;{----------------------------------------------------------------------}
		XDEF	_MapFrametoMap
_MapFrametoMap:
		link	a6,#0

		movem.l	d2-d7/a1-a4,-(sp)

		move.w	12(a6),d2	; and animation
		move.w	14(a6),d3	; and frame
		move.w	16(a6),d4	; character to download to
		move.l	18(a6),a0	; and get address of sprite
		move.l	22(a6),a2	; map address

		jsr	getFrameInfo	; get current frames address

		move.w	SAXPOS(a0),d0	; get current x position
		add.w	8(a6),d0	; add in x position
		move.w	SAYPOS(a0),d1	; get current y position
		add.w	10(a6),d1	; add in y position

		lsr.w	#3,d0
		lsr.w	#3,d1
		move.w	#MAPWIDTH*2,d2	; y position in map indecies
		mulu	d1,d2
		adda.w	d2,a2		; into map

		add.w	d0,d0		; x position in map indecies
		adda.w	d0,a2
;
; ----- now place in map
;
		clr.w	d2
		clr.w	d3
		move.b	SAHVLINK(a0),d2	; get width
		subq.w	#1,d2		; for dbra
		move.b	SAHVLINK+1(a0),d3 ; and height
		subq.w	#1,d3		; for dbra
		clr.w	d6		; character count
		move.w	d4,d7		; save for later
.heightLoop:
		move.w	d2,d5
		move.l	a2,a3		; save map address for later
		add.w	d2,d6		; update number of characters
		addq.w	#1,d6
.widthLoop:
		move.w	d7,(a3)+	; put in map indecies
		addq.w	#1,d7
		dbra	d5,.widthLoop	; do one width
		adda.w	#MAPWIDTH*2,a2	; next y map indecie
		dbra	d3,.heightLoop

		and.l	#$ffff,d6
		move.l	d6,d1		; save for dma routine
		lsl.l	#5,d1		; d6 = count of 8x8 characters * 32 bytes

		movea.l	a1,a0		; address of source bytes

		move.w	d4,d0		; address of destination character
		lsl.w	#5,d0		; * 32
		jsr	addDMAQueue	; and send them next frame

		move.w	d6,d0

		movem.l	(sp)+,d2-d7/a1-a4

		unlk	a6
		rts


;{----------------------------------------------------------------------}
;{ Function:	void SYS_DrawMap(UWORD srcx, UWORD srcy, UWORD VDPChar,	}
;{				 char *map, char *buff);		}
;{ Description:	'C' callable function to draw a map or a portion	}
;{		of a map						}
;{ Parameters:	srcx = starting x position inside of map		}
;{		srcy = starting y position inside of map		}
;{		srcw = width of map to draw				}
;{		srch = height of map to draw				}
;{		VDPChar = Starting vdp Character for character bitmaps	}
;{		map = pointer to futurescape map file			}
;{		buff = destination buffer				}
;{ Returns:	.							}
;{----------------------------------------------------------------------}
		XDEF	_SYS_DrawMap

_SYS_DrawMap:
		link	a6,#0			; no locals
		movem.l	d2-d3,-(sp)

		move.w	8(a6),d0		; x position
		move.w	10(a6),d1		; y
		move.w	12(a6),d2		; vdp character
		move.l	18(a6),a1		; buffer pointer
		move.l	14(a6),a0		; map pointer
		move.w	BHMAPOFFSET(a0),d3
		adda.w	d3,a0

		bsr	DrawFPCMap

		movem.l	(sp)+,d2-d3
		unlk	a6
		rts


;{----------------------------------------------------------------------}
;{ Function:	DrawMap							}
;{ Description:	Draw map to Map A screen				}
;{ Parameters:	d0 = x char in map to draw				}
;{		d1 = y character in map to start at			}
;{		d2 = character # of downloaded characters		}
;{		a0 = pointer to map structure				}
;{		a1 = pointer to buffer					}
;{ Returns:	.							}
;{----------------------------------------------------------------------}
		XDEF	DrawMap
DrawMap:
		movem.l	d0-d6/a0-a1,-(sp)

		move.w	(a0)+,d4		; get width of map
		rol.w	#8,d4
		move.w	(a0)+,d5
		rol.w	#8,d5
		add.w	d4,d4
		mulu	d4,d1			; into temp reg
		add.l	d1,a0

		add.w	d0,d0			; * 2 for words
		add.w	d0,a0
		sub.w	d0,d4

		cmp.w	#(MAPWIDTH*2),d4
		ble.s	.startXLoop
		sub.w	#(MAPWIDTH*2),d4
		add.w	d4,d0
		move.w	#(MAPWIDTH*2),d4
.startXLoop:
		lsr.w	#1,d4
		subq.w	#1,d5
		cmp.w	#MAPHEIGHT-1,d5
		ble.s	.YLoop
		move.w	#MAPHEIGHT-1,d5
.YLoop:
		move.w	d4,d6			; number bytes not going to move
		subq.w	#1,d6
.XLoop:
		move.w	(a0)+,d1
		rol.w	#8,d1
		add.w	d2,d1
		move.w	d1,(a1)+
		dbra	d6,.XLoop
		add.w	d0,a0			; update source offset
		add.w	#(MAPWIDTH*2),a1
		sub.w	d4,a1
		sub.w	d4,a1
		dbra	d5,.YLoop
		
		movem.l	(sp)+,d0-d6/a0-a1
		rts

;{----------------------------------------------------------------------}
;{ Function:	DrawFPCMap						}
;{ Description:	Draw map to Map A screen				}
;{ Parameters:	d0 = x char in map to draw				}
;{		d1 = y character in map to start at			}
;{		d2 = character # of downloaded characters		}
;{		a0 = pointer to map structure				}
;{		a1 = pointer to buffer					}
;{ Returns:	.							}
;{----------------------------------------------------------------------}
DrawFPCMap:

		movem.l	d0-d6/a0-a1,-(sp)

		move.w	(a0)+,d4		; get width of map
		move.w	(a0)+,d5
DrawFPCMap2:
		add.w	d4,d4
		mulu	d4,d1			; into temp reg
		add.l	d1,a0

		add.w	d0,d0			; * 2 for words
		add.w	d0,a0
		sub.w	d0,d4

		cmp.w	#128,d4
		ble.s	.startXLoop
		sub.w	#128,d4
		add.w	d4,d0
		move.w	#128,d4
.startXLoop:
		lsr.w	#1,d4
		subq.w	#1,d5
		cmp.w	#27,d5
		ble.s	.YLoop
		move.w	#27,d5
.YLoop:
		move.w	d4,d6			; number bytes not going to move
		subq.w	#1,d6
.XLoop:
		move.w	(a0)+,d1
		add.w	d2,d1
		move.w	d1,(a1)+
		dbra	d6,.XLoop
		add.w	d0,a0			; update source offset
		add.w	#(MAPWIDTH*2),a1
		sub.w	d4,a1
		sub.w	d4,a1
		dbra	d5,.YLoop
		
		movem.l	(sp)+,d0-d6/a0-a1
		rts

;{----------------------------------------------------------------------}
;{ Function:	UWORD DLFPCChars(long FPCAddr);				}
;{ Description:	'C' callable function to download characters from 	}
;{		Futurescape Productions Character file to VDP.		}
;{ Parameters:	FPCAddr = address of file in memory			}
;{ Returns:	.							}
;{----------------------------------------------------------------------}
		XDEF	_DLFPCChars
_DLFPCChars:
		link	a6,#0

		move.l	8(a6),a0		; get address map
		move.w	BHCHAROFFSET(a0),d0
		adda.w	d0,a0
		bsr	DlChars			; and call asm routine

		unlk	a6
		rts

;{----------------------------------------------------------------------}
;{ Function:	DlChars							}
;{ Description:	Download characters to vram				}
;{ Parameters:	a0 = pointer to charcters structure			}
;{ Returns:	d0 = character # in VRAM				}
;{----------------------------------------------------------------------}
		XDEF	DlChars
DlChars:

		movem.l	d1-d3/a0,-(sp)
		sf	_SYS_VDPAccess
		move.w	_SYS_LastChar,d0	; get last character downloaded
		move.w	d0,d1
		and.l	#$ffff,d1
		lsl.l	#5,d1
		CalcVramWrtAddrCode d1,d2

		move.w	(a0)+,d3		; number of characters
		add.w	d3,_SYS_LastChar
		lsl.w	#4,d3
		AUTOINCREMENT 2
		move.l	d2,VCTRL
		subq.l	#1,d3
.DLLoop:
		move.w	(a0)+,VDATA
		dbra	d3,.DLLoop

		st	_SYS_VDPAccess
		movem.l	(sp)+,d1-d3/a0
		rts


;{----------------------------------------------------------------------}
;{ Function:	SetMapPal						}
;{ Description:	Set the palette from Map structure			}
;{ Parameters:	a0 = pointer to map structure				}
;{ Returns:	.							}
;{----------------------------------------------------------------------}
SetMapPal:
		movem.l	d0-d2/a0,-(sp)
		move.w	BHPALOFFSET(a0),d0	; get offset to palette
		lea	0(a0,d0.w),a0
		bra.s	.setPal2

;{----------------------------------------------------------------------}
;{ Function:	void FPCSetPal(long FPCAddr);				}
;{ Description:	'C' callable function to set palette for 	 	}
;{		Futurescape Productions Character file.			}
;{ Parameters:	FPCAddr = address of file in memory			}
;{ Returns:	.							}
;{----------------------------------------------------------------------}
		XDEF	_FPCSetPal
_FPCSetPal:
		link	a6,#0

		move.l	8(a6),a0		; get address map
		move.w	BHPALOFFSET(a0),d0
		adda.w	d0,a0
		jsr	_SetPal			; and call asm routine

		unlk	a6
		rts

;{----------------------------------------------------------------------}
;{ Function:	void FPCStorePal(long FPCAddr);				}
;{ Description:	'C' callable function to set palette for 	 	}
;{		Futurescape Productions Character file.			}
;{ Parameters:	FPCAddr = address of file in memory			}
;{ Returns:	.							}
;{----------------------------------------------------------------------}
		XDEF	_FPCStorePal
_FPCStorePal:
		move.l	4(sp),a0		; get address map
		move.w	BHPALOFFSET(a0),d0
		adda.w	d0,a0
		jsr	SetPalette		; and call asm routine
		rts

;{----------------------------------------------------------------------}
;{ Function:	_SetPal							}
;{ Description:	Set the palette from RGB structure			}
;{ Parameters:	a0 = pointer to RGB structure				}
;{ Returns:	.							}
;{----------------------------------------------------------------------}
_SetPal:
		movem.l	d0-d2/a0,-(sp)
.setPal2:
		sf	_SYS_VDPAccess
		move.w	BPCOLORINDEX(a0),d0	; get color index
		lsl.w	#1,d0
		move.w	BPNUMCOLORS(a0),d2
		subq.l	#1,d2
		lea	BPRGBVALUES(a0),a0
		CalcCramWrtAddrCode d0,d1	; calculate color ram address

		AutoIncrement 2			; make sure inc's words
		move.l	d1,VCTRL		; send to hardware
.ColorLoop:
		move.w	(a0)+,VDATA
		dbra	d2,.ColorLoop

		st	_SYS_VDPAccess
		movem.l	(sp)+,d0-d2/a0
		rts


;{----------------------------------------------------------------------}
;{ Function:	short DrawAnimMapFrame(WORD xchar, WORD ychar, 		}
;{			UWORD frame, void *FAMAddress, void *mapAddress,}
;{			UWORD vdpChar);					}
;{ Description:	'C' callable function to draw a animated map frame	}
;{		to a buffer						}
;{ Parameters:	frame = frame number in animated map			}
;{		FAMAddress = address of file				}
;{		mapAddress = buffer to draw to				}
;{		vdpChar = vdp character to download to			}
;{----------------------------------------------------------------------}
		xdef	_DrawAnimMapFrame
_DrawAnimMapFrame:
		link	a6,#0
		movem.l	d2-d5/a2,-(sp)

		move.l	14(a6),a2		; get FAM address
		move.l	a2,a0
		move.w	BHINFOOFFSET(a2),d0	; get go map information
		adda.w	d0,a0
		move.w	(a0)+,d0		; get number of frames
		move.w	12(a6),d1
		cmp.w	d0,d1
		bge	.Exit			; out of range

		IFEQ	SIZEAMSTRUCT-10
		add.w	d1,d1			; get to frames info
		adda.w	d1,a0
		add.w	d1,d1
		add.w	d1,d1
		adda.w	d1,a0
		ELSEC
		.ECHO	SIZEAMSTRUCT != 10
		FAIL	1
		ENDC
		move.w	AMYOFFSET(a0),d0	; get y offset
		add.w	10(a6),d0		; and screen y
		lsl.w	#6,d0			; * 64 characters
		add.w	AMXOFFSET(a0),d0	; add in x offset
		add.w	8(a6),d0		; and screen x
		add.w	d0,d0			; double for words
		move.l	18(a6),a1		; get address of map
		adda.w	d0,a1			; and point to offset

		move.w	22(a6),d2		; get vdp character
		move.w	AMMAPOFFSET(a0),d0	; get map offset
		move.l	a2,a0
		adda.w	d0,a0			; now have source map pointer

		move.w	(a0)+,d1		; get width of map
		subq.w	#1,d1
		move.w	(a0)+,d3		; and height of map
		subq.w	#1,d3
.heightLoop:
		move.w	d1,d4
.widthLoop:
		move.w	(a0)+,d0
		add.w	d2,d0
		move.w	d0,(a1)+		; move in on character 
		dbra	d4,.widthLoop
		adda.w	#126,a1			; number bytes wide -2
		sub.w	d1,a1			; and move to next line
		sub.w	d1,a1
		dbra	d3,.heightLoop
.Exit:
		movem.l	(sp)+,d2-d5/a2
		unlk	a6
		rts

;{----------------------------------------------------------------------}
;{ Function:	short EraseAnimMapFrame(WORD x, WORD y, UWORD frame, 	}
;{			void *FAMAddress, void *mapAddress, 		}
;{			UWORD vdpchar);					}
;{ Description:	Erase a mini-map by replacing it with a section of the 	}
;{		first frames map.					}
;{ Parameters:	x,y = x,y character on screen				}
;{		frame = frame number in animated map			}
;{		FAMAddress = the futurescape animated map file		}
;{		mapAddress = where to write the map to			}
;{ Returns:	.							}
;{----------------------------------------------------------------------}
		xdef	_EraseAnimMapFrame
_EraseAnimMapFrame:
		link	a6,#0
		movem.l	d2-d6/a2,-(sp)

		move.l	14(a6),a2		; get FAM address
		move.l	a2,a0
		move.w	BHINFOOFFSET(a2),d0	; get go map information
		adda.w	d0,a0
		move.w	(a0)+,d0		; get number of frames
		move.w	12(a6),d1
		cmp.w	d0,d1
		bge	.Exit			; out of range

		IFEQ	SIZEAMSTRUCT-10
		add.w	d1,d1			; get to frames info
		adda.w	d1,a0
		add.w	d1,d1
		add.w	d1,d1
		adda.w	d1,a0
		ELSEC
		.ECHO	SIZEAMSTRUCT != 10
		FAIL	1
		ENDC
		move.w	AMXOFFSET(a0),d4	; and x offset
		add.w	8(a6),d4
		move.w	AMYOFFSET(a0),d5	; get y offset
		add.w	10(a6),d5
		move.w	d5,d0
		lsl.w	#7,d0			; * 64 characters
		add.w	d4,d0
		add.w	d4,d0

		move.l	18(a6),a1		; get address of map
		adda.w	d0,a1			; and point to offset

		move.w	AMMAPOFFSET(a0),d0	; get map offset
		lea	0(a2,d0.w),a0		; now have source map pointer

		move.w	BMWIDTH(a0),d1		; get width of map
		subq.w	#1,d1
		move.w	BMHEIGHT(a0),d3		; and height of map
		subq.w	#1,d3
.heightLoop1:
		move.w	d1,d2
.widthLoop1:
		clr.w	(a1)+
		dbra	d2,.widthLoop1
		adda.w	#126,a1			; number bytes wide -2
		sub.w	d1,a1			; and move to next line
		sub.w	d1,a1
		dbra	d3,.heightLoop1
;
; ----- Now draw intersection of rectangles
;	d4 = erase rect x
;	d5 = erase rect y
;	a0 = pointer to map width & height
;	a2 = pointer to beginning of file
;
		move.w	BMWIDTH(a0),d0
		add.w	d4,d0			; get right edge-1
		move.w	BMHEIGHT(a0),d1
		add.w	d5,d1			; get bottom edge-1

		move.l	a2,a0
		adda.w	BHINFOOFFSET(a2),a0
		addq.w	#2,a0

		move.w	AMXOFFSET(a0),d2	; get x,y offset of frame 0
		add.w	8(a6),d2
		move.w	AMYOFFSET(a0),d3
		add.w	10(a6),d3
		cmp.w	d4,d2			; find biggest x offset
		blt.s	.NotXBiggest
		move.w	d2,d4			; get bigger x offset
.NotXBiggest:
		cmp.w	d5,d3			; find biggest y offset
		blt.s	.NotYBiggest
		move.w	d3,d5			; get bigger y offset
.NotYBiggest:
		move.w	AMMAPOFFSET(a0),d6	; get to frame 0 map
		lea	0(a2,d6.w),a0
		move.w	(a0)+,d6		; adjust a0 to point to map
		add.w	d6,d2			; add in width
		swap	d6
		move.w	(a0)+,d6		; adjust a0 to point to map
		add.w	d6,d3			; add in height

		cmp.w	d0,d2			; find smallest right edge
		bgt.s	.NotWSmallest
		move.w	d2,d0
.NotWSmallest:
		cmp.w	d1,d3			; find smallest bottom edge
		bgt.s	.NotHSmallest
		move.w	d3,d1
.NotHSmallest:
		sub.w	d4,d0			; get actual width
		bmi.s	.Exit			; doesn't intersect
		sub.w	d5,d1
		bmi.s	.Exit			; doesn't intersect

		sub.w	d6,d3			; get y position of frame 0
		neg.w	d3
		add.w	d5,d3			; get y difference
		swap	d6			; put width of frame 0 in low
		mulu	d6,d3
		adda.w	d3,a0			; adjust for top clip
		adda.w	d3,a0			; adjust for top clip *2 for

		sub.w	d6,d2			; get x position of frame 0
		neg.w	d2			; negate frame 0's x (f0_x)
		add.w	d4,d2			; add erase rect x (er_x)
		add.w	d2,a0			; *2 for words
		add.w	d2,a0

		move.w	d6,d3
		sub.w	d0,d3			; f0_width - er_widthand 
		add.w	d3,d3			; double for words

		subq.w	#1,d0
		subq.w	#1,d1

		move.w	d5,d6
		lsl.w	#7,d6			; * 64 characters
		add.w	d4,d6
		add.w	d4,d6

		move.l	18(a6),a1		; get address of map
		adda.w	d6,a1			; add in offset
		move.w	22(a6),d6		; get vdp characters for map

.heightLoop2:
		move.w	d0,d2
.widthLoop2:
		move.w	(a0)+,d4
		add.w	d6,d4
		move.w	d4,(a1)+
		dbra	d2,.widthLoop2
		adda.w	d3,a0
		adda.w	#126,a1			; number bytes wide -2
		sub.w	d0,a1			; and move to next line
		sub.w	d0,a1
		dbra	d1,.heightLoop2
.Exit:
		movem.l	(sp)+,d2-d6/a2
		unlk	a6
		rts

;{----------------------------------------------------------------------}
;{	start of data section						}
;{----------------------------------------------------------------------}
		section	.data


BlackmapPal:
		dc.w	0			; offset of palette
		dc.w	$40			; number of palette entries
		dcb.w	$40,0

	 	end





