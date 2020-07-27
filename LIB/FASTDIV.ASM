; $Header: h:\toons\rcs\FASTDIV.ASM_v 1.1 1994/02/19 22:48:27 KENH Exp $
;{----------------------------------------------------------------------}
;{ Module:	FASTDIV.ASM						}
;{ Description:	fast divide routines					}
;{ Part of:	SEGALIB.LIB						}
;{ Original:	Kevin L. McGrath					}
;{ Started:	5/1/93							}
;{----------------------------------------------------------------------}
;{		*** Copyright 1993 Futurescape Productions ***		}
;{----------------------------------------------------------------------}

;
; $Log: FASTDIV.ASM_v $
; Revision 1.1  1994/02/19  22:48:27  KENH
; .
;
;

		include	equates.inc
		include	macros.inc
		include	variable.inc

Z80NoROM	equ	Z80Base+4	;flag for disabling Z80 ROM accesses

		TSECTION	.text


;{----------------------------------------------------------------------}
;{ Function:	fdiv(long dividend, long divisor);			}
;{ Description:	32x32 bit fractional divide				}
;{ Parameters:	dividend = the dividend					}
;{		divisor = the divisor					}
;{ returns:	d0 = 32 result						}
;{----------------------------------------------------------------------}
		XDEF	_fdiv
_fdiv		link	a6,#0
		movem.l	d1-d5,-(sp)
		clr	d4		; Signflag = FALSE
		move.l	8(a6),d0	; Get dividend
		bpl.s	ds1
		not	d4
		neg.l	d0
ds1		move.l	12(a6),d1	; Get divisor
		beq.s	dout		; We don't do division by zero
		bpl.s	ds2
		not	d4
		neg.l	d1
ds2		move.l	d0,d5		; Set up extra 16 bits
		swap	d5
		move	#0,d5
		move	d5,d0
		swap	d0
		clr.l	d2
		move	#64-1,d3	; Loop 64 times
		move	#0,CCR		; Clear X flag
dloop		roxl.l	#1,d5
		roxl.l	#1,d0
		roxl.l	#1,d2
		cmp.l	d1,d2
		blt.s	ddec		; if dividend < divisor loop
		sub.l	d1,d2		; else dividend -= divisor
		move	#$10,CCR	; Set X flag
ddec		dbra	d3,dloop
		roxl.l	#1,d5		; shift in last bit
		move.l	d5,d0
		tst	d4
		beq.s	dout
		neg.l	d0
dout		movem.l	(sp)+,d1-d5
		unlk	a6
		rts

		end


