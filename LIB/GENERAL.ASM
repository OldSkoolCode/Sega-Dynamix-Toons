; $Header: h:\toons\rcs\GENERAL.ASM_v 1.1 1994/02/19 22:48:27 KENH Exp $
;{----------------------------------------------------------------------}
;{	GENERAL.S							}
;{	  general Routines routines for game				}
;{	  Written BY: Kenneth L. Hurley					}
;{	  Futurescape Productions Inc.					}
;{----------------------------------------------------------------------}

;
; $Log: GENERAL.ASM_v $
; Revision 1.1  1994/02/19  22:48:27  KENH
; .
;
;
		OPT	LLBL

		include	equates.inc
		include	macros.inc
		include	variable.inc
		include	sega.inc

		xref	puts
;{----------------------------------------------------------------------}
;{			Variables go here				}
;{----------------------------------------------------------------------}

		bsection	.bss

temppal1	ds.w	64
temppal2	ds.w	64
temppal3	ds.w	64+2
tempbuff	ds.b	80

		tsection	.text


;{----------------------------------------------------------------------}
;{ Function:	ptInRect(short px, short py, short rx, short ry,	}
;{			short rw, rh);					}
;{ Description:	'C' callable function to check for a point in a 	}
;{		rectangle						}
;{ Parameters:	px = x of point						}
;{		py = y of point						}
;{		rx = x of rectangle					}
;{		ry = y of rectangle					}
;{		rw = width of rectangle					}
;{		rh = height of rectangle				}
;{ returns:	d0 = 0 if not in rectangle				}
;{----------------------------------------------------------------------}
		XDEF	_ptInRect
_ptInRect:
		link	a6,#0

		movem.l	d2-d6,-(sp)
		move.w	8(a6),d0
		move.w	10(a6),d1
		move.w	12(a6),d2
		move.w	14(a6),d3
		move.w	16(a6),d4
		move.w	18(a6),d5

		clr.w	d6

		cmp.w	d2,d0
		blt.s	.allDone
		cmp.w	d3,d1
		blt.s	.allDone
		add.w	d2,d4
		cmp.w	d4,d0
		bge.s	.allDone
		add.w	d3,d5
		cmp	d5,d1
		bge.s	.allDone
		move.w	#1,d6
.allDone:
		move.w	d6,d0
		movem.l	(sp)+,d2-d6
		unlk	a6
		rts

;{----------------------------------------------------------------------}
;{ Function:	_ptInRect						}
;{ Description:	Check for point in rectangle				}
;{ Parameters:	d0 = x of point						}
;{		d1 = y of point						}
;{		d2 = x of rectangle					}
;{		d3 = y of rectangle					}
;{		d4 = width of rectangle					}
;{		d5 = height of rectangle				}
;{ returns:	d0 = 0 if not in rectangle				}
;{----------------------------------------------------------------------}
		XDEF	ptInRect
ptInRect:

		movem.l	d4-d6,-(sp)

		clr.w	d6

		cmp.w	d2,d0
		blt.s	.allDone
		cmp.w	d3,d1
		blt.s	.allDone
		add.w	d2,d4
		cmp.w	d4,d0
		bge.s	.allDone
		add.w	d3,d5
		cmp	d5,d1
		bge.s	.allDone
		move.w	#1,d6
.allDone:
		move.w	d6,d0
		movem.l	(sp)+,d4-d6
		rts

;{----------------------------------------------------------------------}
;{ Function:	hextoasc 						}
;{ Description: Converts hexadecimal to ascii and prints it out.	}
;{ Parameters:	d0 = number						}
;{ Returns:	.							}
;{----------------------------------------------------------------------}
hextoasc:
		movem.l	d0-d2/a0-a1,-(sp)
		lea	tempbuff,a0
		lea	hexascii,a1
		moveq	#7,d2
hexLoop:
		rol.l	#4,d0
		move.w	d0,d1
		and.w	#$f,d1
		move.b	$0(a1,d1.w),(a0)+
		dbra	d2,hexLoop
		
		lea	tempbuff,a0
		jsr	puts
		movem.l	(sp)+,d0-d2/a0-a1

		rts

;{----------------------------------------------------------------------}
;{ Function:	hextodec						}
;{ Descprition:	convert hex number to decimal ascii			}
;{ Parameters:	d0.w = number						}
;{ Returns:	.							}
;{----------------------------------------------------------------------}
hextodec:

		movem.l	d0-d2/a0-a1,-(sp)

		lea	tempbuff,a0
		lea	decvals-2,a1
		move.b	#'0',(a0)
		clr.b	1(a0)

		move.w	#5-1,d2
.findLowLoop:
		adda.w	#2,a1
		cmp.w	(a1),d0
		bge.s	.CnvtLoop
		dbra	d2,.findLowLoop
		jmp	.h2dExit
.CnvtLoop:
		move.w	(a1)+,d1
		divu	d1,d0
		add.b	#'0',d0
		move.b	d0,(a0)+
		swap	d0
		dbra	d2,.CnvtLoop
		clr.b	(a0)+
.h2dExit:
		lea	tempbuff,a0
		jsr	puts
		movem.l	(sp)+,d0-d2/a0-a1
		rts

decvals		dc.w	10000,1000,100,10,1
hexascii	dc.b	'0123456789ABCDEF'


;{----------------------------------------------------------------------}
;{ Function:	fadetoPalRange						}
;{ Description:	take range of colors and fade from current palette	}
;{		to them not disturbing outside of range			}
;{ Parameters:	d0 = # steps to fade					}
;{		a0 = source palette					}
;{ Returns:	.							}
;{----------------------------------------------------------------------}
fadetoPalRange:

		movem.l	d0-d5/a0-a2,-(sp)

		lea	temppal1,a1
		lea	temppal2,a2
		sf	_SYS_VDPAccess		; disable VDP accesses

		AutoIncrement 2
		move.w	#0,VCTRL		; address zero
		move.w	#CD3,VCTRL		; and read cram
		move.w	#64-1,d2
.rdLoop:
		move.w	VDATA,d1
		move.w	d1,(a1)+
		move.w	d1,(a2)+
		dbra	d2,.rdLoop

		st	_SYS_VDPAccess		; enable VDP accesses

		lea	-128(a2),a2

		move.w	(a0)+,d1
		add.w	d1,d1
		adda.w	d1,a2			; destination offset
		move.w	(a0)+,d2		; count
		subq.w	#1,d2			; for dbra
.moveLoop:
		move.w	(a0)+,(a2)+
		dbra	d2,.moveLoop		; move in new colors

		lea	temppal1,a0
		lea	temppal2,a1
		bra.s	fadetoFullPal2

;{----------------------------------------------------------------------}
;{ Function:	fadetoFullPal						}
;{ Description:	Fade from one palette to another			}
;{ Parameters:	d0 = # steps to fade					}
;{		a0 = source palette					}
;{		a1 = destination palette				}
;{ Returns:	.							}
;{----------------------------------------------------------------------}
fadetoFullPal:
		movem.l	d0-d5/a0-a2,-(sp)

fadetoFullPal2:
		move.w	d0,d3
		move.w	#1,d2
.f_fade:
		lea	temppal3,a2
		clr.w	(a2)+		; color register index
		move.w	#$40,(a2)+	; number of colors

		moveq	#64-1,d5	; every color
.f_set:
		move.b	(a0)+,d0	; 1st byte of data
		and.w	#$f,d0		; get nibble
		move.w	d0,d4		; save off source
		move.b	(a1)+,d1
		and.w	#$f,d1
		sub.w	d1,d0
		muls	d2,d0
		divs	d3,d0		; scale for current frame
		sub.w	d0,d4
		and.w	#$e,d4		; discard bottom bit
		move.b	d4,(a2)+

		move.b	(a0),d0		; 2nd byte of data/1st nibble
		lsr.w	#4,d0
		and.w	#$f,d0		; get nibble
		move.w	d0,d4		; save off source
		move.b	(a1),d1
		lsr.w	#4,d1
		and.w	#$f,d1
		sub.w	d1,d0
		muls	d2,d0
		divs	d3,d0		; scale for current frame
		sub.w	d0,d4
		and.w	#$e,d4		; discard bottom bit
		lsl.w	#4,d4
		move.b	d4,(a2)

		move.b	(a0)+,d0	; 1st byte of data
		and.w	#$f,d0		; get nibble
		move.w	d0,d4		; save off source
		move.b	(a1)+,d1
		and.w	#$f,d1
		sub.w	d1,d0
		muls	d2,d0
		divs	d3,d0		; scale for current frame
		sub.w	d0,d4
		and.w	#$e,d4		; discard bottom bit
		or.b	d4,(a2)+

		dbra	d5,.f_set	; do all colours
		lea	-128(a0),a0	; point to buffer again
		lea	-128(a1),a1	; point to buffer again
		lea	temppal3,a2
;		move.l	a2,globalPals	; say update palette
;		clr.l	lastPals
;		clr.l	globalPals+4	; say update palette
;		clr.l	globalPals+8	; say update palette
;		clr.l	globalPals+12	; say update palette
.waitPal:
;		cmp.l	#0,lastPals	; wait for palette update
;		beq.s	.waitPal

		addq.w	#1,d2
		cmp.w	d2,d3
		bge	.f_fade

		movem.l	(sp)+,d0-d5/a0-a2

		rts

;{----------------------------------------------------------------------}
;{ Function:	ShellSort						}
;{ Description:	shell sort a list of unknown type			}
;{ Parameters:	d0 = number in list					}
;{ 		d1 = size of item					}
;{		a0 = pointer to data					}
;{		a1 = pointer to compare routine				}
;{----------------------------------------------------------------------}
ShellSort:
		movem.l	d0-d7/a0-a3,-(sp)

		move.l	a0,a2		; data pointer
		move.l	a1,a3		; compare routine

		move.w	d0,d7
		move.w	d0,d2		; starting gap size
		bra.s	.checkgapLoop
.gapLoop:
		move.w	d2,d3		; i = gap
		bra.s	.checkiLoop

.iLoop:
		move.w	d3,d4		; j = i
		bra.s	.nextJ
.jLoop:
		move.w	d4,d5		; temp
		mulu	d1,d5		; * item size
		move.l	a2,a0		; start address
		adda.l	d5,a0		; and get items[j]

		move.w	d4,d5		; j value
		add.w	d2,d5		; + gap
		mulu	d1,d5		; * item size
		move.l	a2,a1
		adda.l	d5,a1

		jsr	(a3)		; see if less than or what

		tst.w	d0
		blt.s	.nextI
	  	move.w	d1,d5		; item size
		subq.w	#1,d5
.copyLoop:
		move.b	(a0),d0
		move.b	(a1),d6
		move.b	d0,(a1)+
		move.b	d6,(a0)+
		dbra	d5,.copyLoop
.nextJ:
		sub.w	d2,d4		; j = j-gap
		bge.s	.jLoop

.nextI:
		addq.w	#1,d3		; i++
.checkiLoop:
		cmp.w	d7,d3
		blt.s	.iLoop

.checkgapLoop:
		lsr.w	#1,d2
		bgt.s	.gapLoop

		movem.l	(sp)+,d0-d7/a0-a3

		rts

	 	end

