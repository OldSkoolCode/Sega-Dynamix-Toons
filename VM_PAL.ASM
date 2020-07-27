;{----------------------------------------------------------------------}
;{ Module:	vm_pal.asm						}
;{ Description:	Take care of virtual machine palette stuff		}
;{ Part of:	SEGALIB.LIB						}
;{ Original:	Kevin L. McGrath					}
;{ Started:	02/24/94						}
;{----------------------------------------------------------------------}
;{		*** Copyright 1994 Futurescape Productions ***		}
;{----------------------------------------------------------------------}

		include vm_defs.inc
		include equates.inc

		OPT	LLBL
                 
		bsection	.bss

		ds.w	0
gr_palbuffer	ds.w	64

	        tsection 	.text

;{----------------------------------------------------------------------}
;{ Function:	void vm_setanimpal(long animptr);			}
;{ Description:	'C' callable function to set the palette from an	}
;{		animation file.						}
;{ Parameters:	animptr = animation file pointer (FPA file)		}
;{ Returns:	.							}
;{ 	Palette structure:						}
;{		dc.w	startcolour					}
;{		dc.w	number						}
;{									}
;{		dc.w	colour						}
;{		...							}
;{									}
;{		dc.w	-1 (or repeat structure)			}
;{----------------------------------------------------------------------}

		XDEF	_vm_setanimpal
_vm_setanimpal:
		link	a6,#0		; set up for parameters and 0 locals
		movem.l	d0/a0-a1,-(sp)

		move.l	8(a6),a0
		add.w	(a0),a0		; Point to palette in FPA file

		bra.s	.get		; Jump to start
.set		lea	gr_palbuffer,a1	; Point at slave buffer
		add.w	d0,d0		; 2 * color
		add.w	d0,a1		; Index correct slave
		move.w	(a0)+,d0	; Get count of values
		subq.w	#1,d0
.lp		move.w	(a0)+,(a1)+	; Copy value to slave buffer
		dbra	d0,.lp
.get		move.w	(a0)+,d0	; Get flag/address
		bpl.s	.set		; Do more if not negative

		move.l	#$C0000000,VCTRL
		lea	gr_palbuffer,a1
		moveq	#64-1,d0	; Number of colors (4*16 colors)
.set_lp		move.w	(a1)+,VDATA	; Move data to CRAM
		dbra	d0,.set_lp	; Move all

		movem.l	(sp)+,d0/a0-a1
		unlk	a6
		rts

		end
