;{----------------------------------------------------------------------}
;{	SCROLL.ASM							}
;{	  Scrolling Routines Module					}
;{	  Written BY: Kenneth L. Hurley					}
;{	  Futurescape Productions Inc.					}
;{----------------------------------------------------------------------}


		include	macros.inc
		include equates.inc
		include sega.inc
		include format.inc

		OPT	LLBL

		XDEF	_hscrollValue
		XDEF	_oldhscrollVal
		XDEF	_vscrollValue
		XDEF	_oldvscrollVal
		XDEF	updatescroll
		XREF	SetVRAMWrite
		XREF	_Work_Sprlist
		XREF	_SprAttrAddr
		XREF	CopyToVRAM
		XREF	_SYS_SprAvail
		XDEF	_SYS_ScrollUpdate


		bsection	.bss

_hscrollValue	ds.w	1
_oldhscrollVal	ds.w	1
_vscrollValue	ds.w	1
_oldvscrollVal	ds.w	1
_SYS_ScrollUpdate ds.b	1


		tsection	.text

;{----------------------------------------------------------------------}
;{ Function:	updatescroll						}
;{ Description:	update scroll registers to reflect current scroll 	}
;{		position and adjust sprites.				}
;{ Parameters:	.							}
;{ Returns:	.							}
;{----------------------------------------------------------------------}
updatescroll:
		tst.b	_SYS_ScrollUpdate
		beq	.allDone
		move.l	#$40000010,VCTRL
		move.w	_vscrollValue,d0
		cmp.w	_oldvscrollVal,d0
		beq.s	.noUpdateV
		swap	d0
		move.w	#$120,d0
;		move.w	_vscrollValue,d0
;		add.w	#$100,d0
		move.l	d0,VDATA
.noUpdateV:
		move.w	_hscrollValue,d1
		cmp.w	_oldhscrollVal,d1
		beq.s	.noUpdateH

		neg.w	d1
		move.l	#HScroll,d0
		bsr	SetVRAMWrite

		move.w	d1,VDATA		; set plane a's scroll value
		move.w	#0,VDATA
;		move.w	d1,VDATA		; and plane b's

.noUpdateH:
;
; ----- Now update sprites possibly
;
		move.l	#_Work_Sprlist,a0
		move.w	_SYS_SprAvail,d0
		subq.w	#1,d0			; this many sprites right now
		bmi.s	.DontUpdateSprites

		move.w	_oldhscrollVal,d1
		sub.w	_hscrollValue,d1
	
		move.w	_oldvscrollVal,d2
		sub.w	_vscrollValue,d2

		move.w	d2,d3
		or.w	d1,d3
		beq.s	.DontUpdateSprites
.updateLoop:
		add.w	d1,SLX(a0)
		add.w	d2,SLY(a0)
		adda.w	#SPRLISTSIZE,a0
		dbra	d0,.updateLoop

		move.l	#_Work_Sprlist,a0
		move.w	_SYS_SprAvail,d1
		lsl.w	#3,d1
		move.w	_SprAttrAddr,d0
		jsr	CopyToVRAM		; and copy to VDP
.DontUpdateSprites:
		move.w	_hscrollValue,_oldhscrollVal
		move.w	_vscrollValue,_oldvscrollVal
.allDone:
		rts

		end

