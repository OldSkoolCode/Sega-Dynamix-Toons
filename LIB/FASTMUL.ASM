; $Header: h:\toons\rcs\FASTMUL.ASM_v 1.1 1994/02/19 22:48:27 KENH Exp $
;{----------------------------------------------------------------------}
;{ Module:	FASTMUL.ASM						}
;{ Description:	fast multiply routines					}
;{ Part of:	SEGALIB.LIB						}
;{ Original:	Kevin L. McGrath					}
;{ Started:	5/1/93							}
;{----------------------------------------------------------------------}
;{		*** Copyright 1993 Futurescape Productions ***		}
;{----------------------------------------------------------------------}

;
; $Log: FASTMUL.ASM_v $
; Revision 1.1  1994/02/19  22:48:27  KENH
; .
;
;

		include	equates.inc
		include	macros.inc
		include	variable.inc

Z80NoROM	equ	Z80Base+4	;flag for disabling Z80 ROM accesses

		TSECTION	.text

FASTMUL		equ	1

;{----------------------------------------------------------------------}
;{ Function:	fmul(long multiplier, long multiplicand);		}
;{ Description:	32x32 bit fractional multiply				}
;{ Parameters:	multiplier = the multiplier				}
;{		mulitplicand = the multiplicand				}
;{ returns:	d0 = 32 result						}
;{----------------------------------------------------------------------}
		XDEF	_fmul

		IFNE	FASTMUL
_fmul		link	a6,#0
		movem.l	d1-d5,-(sp)
		clr	d4		; Signflag = FALSE
		move.l	8(a6),d0	; Get multiplier
		bpl.s	ms1
		not	d4
		neg.l	d0
ms1:
		move.l	12(a6),d2	; Get multiplicand
		bpl.s	ms2
		not	d4
		neg.l	d2
ms2		move.l	d0,d1		; copy A to d1
		move.l	d0,d3		; copy A to d3
		move.l	d0,d5		; copy A to d5
		mulu	d2,d5		; BL * AL
		swap	d1		; AH
		mulu	d2,d1		; BL * AH
		swap	d2		; BH
		swap	d0		; AH
		mulu	d2,d0		; BH * AH
		mulu	d2,d3		; BH * AL
		add.l	d3,d1		; x = ((BH * AL) + (BL * AH)) << 16
		swap	d0		; (BH * AH) << 32 + x + (BL * AL)
		move	#0,d0
		move	#0,d5
		swap	d5
		add.l	d1,d0
		add.l	d5,d0
		tst	d4
		beq.s	mout
		neg.l	d0
mout		movem.l	(sp)+,d1-d5
		unlk	a6
		rts

		ELSEC

_fmul		link	a6,#0
		movem.l	d1-d4,-(sp)
		clr	d4		; Signflag = FALSE
		move.l	8(a6),d0	; Get multiplier
		bpl.s	ms1
		not	d4
		neg.l	d0
ms1		move.l	12(a6),d1	; Get multiplicand
		bpl.s	ms2
		not	d4
		neg.l	d1
ms2		clr.l	d2
		move	#32,d3		; Loop 32 plus 1 times
		move	#0,CCR		; Clear X flag
mloop		roxr.l	#1,d2
		roxr.l	#1,d0
		bcc.s	mdec		; If next bit is 0
		add.l	d1,d2
mdec		dbra	d3,mloop
		move	#0,d0		; Adjust for 16-bit fraction
		swap	d0
		swap	d2
		move	#0,d2
		or.l	d2,d0
		tst	d4
		beq.s	mout
		neg.l	d0
mout		movem.l	(sp)+,d1-d4
		unlk	a6
		rts
		ENDC

		end


