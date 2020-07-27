;{----------------------------------------------------------------------}
;{ Module:	vm_pix.asm						}
;{ Description:	take care of any pixel drawing stuff to the VDP		}
;{ Part of:	SEGALIB.LIB						}
;{ Original:	Kenneth L. Hurley					}
;{ Updated:	Kevin L. McGrath					}
;{ Started:	10/29/93						}
;{----------------------------------------------------------------------}
;{		*** Copyright 1994 Futurescape Productions ***		}
;{----------------------------------------------------------------------}

		include vm_defs.inc

		XREF	gr_fixclip
                 
	        tsection 	.text

;{----------------------------------------------------------------------}
;{ Function:	void vm_putpix(short x, short y, short color);		}
;{ Description:	'C' callable function to draw a pixel on the sega 	}
;{		screen.							}
;{ Parameters:	x = x position to draw pixel at				}
;{ 		y = y position to draw pixel at				}
;{		color = color to draw pixel				}
;{ Returns:	.							}
;{----------------------------------------------------------------------}

		XDEF	_vm_putpix
_vm_putpix:
		link	a6,#0		; set up for parameters and 0 locals
		move.l	d2,-(sp)

		move.w	8(a6),d0	; get x position
		move.w	10(a6),d1	; and y position
		move.w	12(a6),d2	; get color
		bsr	gr_putpix
		
		move.l	(sp)+,d2
		unlk	a6
		rts

;{----------------------------------------------------------------------}
;{ Function:	gr_putpix						}
;{ Description:	set a pixel in the VDP memory.  			}
;{ Parameters:	d0 = x position of pixel				}
;{		d1 = y position of pixel				}
;{		d2 = color to place there				}
;{ returns:	.							}
;{----------------------------------------------------------------------}

;	This table provides fast access to each character column in the
;	screen buffer.  The bitmapped screen is arranged by Y, meaning
;	there are 40 strips of characters 25 high.

	XDEF	gr_xtable
gr_xtable:
		XREF	gr_tclip
		XREF	gr_bclip
		XREF	gr_lclip
		XREF	gr_rclip
                 
		XDEF	gr_putpix
gr_putpix:
		movem.l	d0-d3/a0,-(sp)

		lsr.w	#1,d0		; Deal with 640x400 virtual
		lsr.w	#1,d1		; screen...

		tst.b	_vm_clip	; Do clipping
		beq.s	.no_clip
		jsr	gr_fixclip
		cmp.w	gr_lclip,d0
		blt.s	.exit
		cmp.w	gr_rclip,d0
		bgt.s	.exit
		cmp.w	gr_tclip,d1
		blt.s	.exit
		cmp.w	gr_bclip,d1
		bgt.s	.exit

.no_clip	move.w	d0,d3		; Compute character column
		lsr.w	#1,d3		; divide by 8 pixels per character
		and.w	#$FFFC,d3	; mask for long address table
		lea	gr_xtable,a0
		move.l	0(a0,d3.w),a0	; get character column addr from table
		lsl.w	#2,d1		; y line offset
		move.w	#$F0,d3
		and.b	#$0F,d2		; only use low nybble of color
		and.w	#7,d0		; x pixel offset
		lsr.w	#1,d0		; convert to byte offset
		bcs.s	.isOddNibble	; is in odd nibble?
		lsl.w	#4,d2		; put in high nibble
		move.w	#$0F,d3
.isOddNibble	add.w	d0,a0		; get actual offset to byte
		add.w	d1,a0
		and.b	d3,(a0)
		or.b	d2,(a0)		; put in pixel
.exit		movem.l	(sp)+,d0-d3/a0
		rts


		end
