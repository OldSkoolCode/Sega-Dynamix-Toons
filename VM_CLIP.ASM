;{----------------------------------------------------------------------}
;{ Module:	vm_clip.asm						}
;{ Description:	Take care of any clip setting and testing		}
;{ Part of:	SEGALIB.LIB						}
;{ Original:	Kevin L. McGrath					}
;{ Started:	02/25/94						}
;{----------------------------------------------------------------------}
;{		*** Copyright 1994 Futurescape Productions ***		}
;{----------------------------------------------------------------------}

		include vm_defs.inc
                 
		OPT	LLBL
                 
		XDEF	gr_tclip
		XDEF	gr_bclip
		XDEF	gr_lclip
		XDEF	gr_rclip
                 
		bsection	.bss

gr_tclip	ds.w	1
gr_bclip	ds.w	1
gr_lclip	ds.w	1
gr_rclip	ds.w	1

	        tsection 	.text

;{----------------------------------------------------------------------}
;{ Function:	gr_fixclip						}
;{ Description:	Temporary clip checker and adjustment for TOONS		}
;{ Parameters:	.							}
;{ VM Globs:	vm_tclip = top clip line				}
;{		vm_bclip = bottom clip line				}
;{		vm_lclip = left clip pixel				}
;{		vm_rclip = right clip pixel				}
;{ Returns:	.							}
;{----------------------------------------------------------------------}

		XDEF	gr_fixclip
gr_fixclip:
		move.w	_vm_tclip,gr_tclip	; Deal with 640x400 virtual
		lsr.w	gr_tclip		; screen...
		move.w	_vm_bclip,gr_bclip
		lsr.w	gr_bclip
		move.w	_vm_lclip,gr_lclip
		lsr.w	gr_lclip
		move.w	_vm_rclip,gr_rclip
		lsr.w	gr_rclip

		cmp.w	#319,gr_lclip		; Left fix
		ble.s	.LOk1
		move.w	#319,gr_lclip
.LOk1		tst.w	gr_lclip
		bpl.s	.LOk2
		clr.w	gr_lclip
.LOk2		cmp.w	#319,gr_rclip		; Right fix
		ble.s	.ROk1
		move.w	#319,gr_rclip
.ROk1		tst.w	gr_rclip
		bpl.s	.ROk2
		clr.w	gr_rclip
.ROk2		cmp.w	#199,gr_tclip		; Top fix
		ble.s	.TOk1
		move.w	#199,gr_tclip
.TOk1		tst.w	gr_tclip
		bpl.s	.TOk2
		clr.w	gr_tclip
.TOk2		cmp.w	#199,gr_bclip		; Bottom fix
		ble.s	.BOk1
		move.w	#199,gr_bclip
.BOk1		tst.w	gr_bclip
		bpl.s	.BOk2
		clr.w	gr_bclip
.BOk2		and.w	#$FFFE,gr_lclip	; Left and right must be even
		and.w	#$FFFE,gr_rclip
		rts

		end
