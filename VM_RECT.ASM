;{----------------------------------------------------------------------}
;{ Module:	vm_rect.asm						}
;{ Description:	Take care of any rectangle drawing stuff to the VDP	}
;{ Part of:	SEGALIB.LIB						}
;{ Original:	Kevin L. McGrath					}
;{ Started:	02/23/94						}
;{----------------------------------------------------------------------}
;{		*** Copyright 1994 Futurescape Productions ***		}
;{----------------------------------------------------------------------}

		include vm_defs.inc

		OPT	LLBL

		XREF	gr_fixclip
		XREF	gr_cols_touched
		XREF	gr_ct_ptr
                 
	        tsection 	.text

;{----------------------------------------------------------------------}
;{ Function:	void vm_rect(short x, short y, short w, short h);	}
;{ Description:	'C' callable function to draw a rectangle on the sega 	}
;{		screen.							}
;{ Parameters:	x = x position						}
;{ 		y = y position						}
;{		w = width						}
;{ 		h = height						}
;{ VM Globs:	vm_fill = 0 means border only				}
;{		vm_lcolor = border line color				}
;{		vm_fcolor = interior color				}
;{		vm_clip = 0 means don't clip				}
;{		vm_tclip = top clip line				}
;{		vm_bclip = bottom clip line				}
;{		vm_lclip = left clip pixel				}
;{		vm_rclip = right clip pixel				}
;{ Returns:	.							}
;{----------------------------------------------------------------------}

		XREF	gr_line
                 
		XREF	gr_tclip
		XREF	gr_bclip
		XREF	gr_lclip
		XREF	gr_rclip

		XDEF	_vm_rect
_vm_rect:
		link	a6,#0		; set up for parameters and 0 locals
		movem.l	d0-d5,-(sp)

		move.w	8(a6),d0	; get x position
		move.w	10(a6),d1	; get y position
		move.w	12(a6),d2	; get width
		beq	.exit
		move.w	14(a6),d3	; get height
		beq	.exit

		lsr.w	#1,d0		; Deal with 640x400 virtual
		lsr.w	#1,d1		; screen...
		lsr.w	#1,d2
		lsr.w	#1,d3

		add	d0,d2		; convert to x2
		add	d1,d3		; convert to y2
		move.b	_vm_lcolor,d5	; get line color
		tst.b	_vm_clip	; do we need to clip?
		beq.s	.noclip
		jsr	gr_fixclip
		cmp.w	gr_lclip,d0	; do clipping
		bge.s	.OkX1a
		move.w	gr_lclip,d0
.OkX1a		cmp.w	gr_rclip,d0
		ble.s	.OkX1b
		move.w	gr_rclip,d0
.OkX1b		cmp.w	gr_lclip,d2
		bge.s	.OkX2a
		move.w	gr_lclip,d2
.OkX2a		cmp.w	gr_rclip,d2
		ble.s	.OkX2b
		move.w	gr_rclip,d2
.OkX2b		cmp.w	gr_tclip,d1
		bge.s	.OkY1a
		move.w	gr_tclip,d1
.OkY1a		cmp.w	gr_bclip,d1
		ble.s	.OkY1b
		move.w	gr_bclip,d1
.OkY1b		cmp.w	gr_tclip,d3
		bge.s	.OkY2a
		move.w	gr_tclip,d3
.OkY2a		cmp.w	gr_bclip,d3
		ble.s	.noclip
		move.w	gr_bclip,d3

.noclip		tst.b	_vm_fill	; do we need to fill?
		beq.s	.wires
		move.b	_vm_fcolor,d4
		bsr	gr_rect
		cmp.b	_vm_fcolor,d5	; line color same as fill color?
		beq.s	.exit

.wires
		add.w	d0,d0		; Deal with 640x400 virtual
		add.w	d1,d1		; screen...
		add.w	d2,d2
		add.w	d3,d3

		move	d5,d4		; Get line color
		move	d3,-(sp)
		move	d1,d3
		bsr	gr_line
		move	(sp)+,d3
		move	d2,-(sp)
		move	d0,d2
		bsr	gr_line
		move	(sp)+,d2
		move	d0,-(sp)
		move	d2,d0
		bsr	gr_line
		move	(sp)+,d0
		move	d3,d1
		bsr	gr_line

.exit		movem.l	(sp)+,d0-d5
		unlk	a6
		rts

;{----------------------------------------------------------------------}
;{ Function:	gr_rect							}
;{ Description:	Fill a rectangle in the screen memory. 			}
;{		Clipping is assumed to be done.				}
;{ Parameters:	d0 = x1							}
;{		d1 = y1							}
;{		d2 = x2							}
;{		d3 = y2							}
;{		d4 = color to fill					}
;{ returns:	.							}
;{----------------------------------------------------------------------}

		XREF	gr_xtable

gr_rect_lft:
		DC.L	$FFFFFFFF
		DC.L	$0FFFFFFF
		DC.L	$00FFFFFF
		DC.L	$000FFFFF
		DC.L	$0000FFFF
		DC.L	$00000FFF
		DC.L	$000000FF
		DC.L	$0000000F

gr_rect_rgt:
		DC.L	$F0000000
		DC.L	$FF000000
		DC.L	$FFF00000
		DC.L	$FFFF0000
		DC.L	$FFFFF000
		DC.L	$FFFFFF00
		DC.L	$FFFFFFF0
		DC.L	$FFFFFFFF

gr_color_tab	DC.L	$00000000
		DC.L	$11111111
		DC.L	$22222222
		DC.L	$33333333
		DC.L	$44444444
		DC.L	$55555555
		DC.L	$66666666
		DC.L	$77777777
		DC.L	$88888888
		DC.L	$99999999
		DC.L	$AAAAAAAA
		DC.L	$BBBBBBBB
		DC.L	$CCCCCCCC
		DC.L	$DDDDDDDD
		DC.L	$EEEEEEEE
		DC.L	$FFFFFFFF

		XDEF	gr_rect
gr_rect:
		movem.l	d0-d7/a0-a5,-(sp)

		and	#$F,d4		; Replicate color into all nybbles
		lsl	#2,d4
		lea	gr_color_tab,a0
		move.l	0(a0,d4.w),d4

		move.w	d0,d5		; Compute character column for X1
		lsr.w	#1,d5		; divide by 8 pixels per character
		and.w	#$FFFC,d5	; mask for long address table
		lea	gr_xtable,a0
		move.l	0(a0,d5.w),a1	; get character column addr from table
		lsl.w	#2,d1		; y line offset
		add.w	d1,a1		; get actual offset to scanline

		move.w	d0,d7		; Set pointer to column update vars
		lsr.w	#3,d7
		lea	gr_cols_touched,a5
		add.w	d7,a5

		move.w	d2,d6		; Compute character column for X2
		lsr.w	#1,d6		; divide by 8 pixels per character
		and.w	#$FFFC,d6	; mask for long address table
		move.l	0(a0,d6.w),a4	; get character column addr from table
		add.w	d1,a4		; get actual offset to scanline
		swap	d6		; Save Y offset for latter...
		move	d1,d6

		lsr.w	#2,d1		; Save off dbra count for # of lines
		sub	d1,d3
;
; ------ KLH: (y2-y1)+1 = width, dbra's = -1 
;		so no add or subtract is necessary
;
;		sub	#1,d3		; D3 is now height - 1
		cmp	#-1,d3		; Make sure it is within range
		ble	.exit

; Do Left side
		move.l	d4,-(sp)
		move	d0,d7		; Get left side mask
		and	#7,d7
		lsl	#2,d7
		lea	gr_rect_lft,a3
		move.l	0(a3,d7.w),d1
		cmpa.l	a1,a4		; Is it a left & right case?
		bne.s	.notlr
		lea	gr_rect_rgt,a3
		and.l	0(a3,d7.w),d1
.notlr		and.l	d1,d4		; Mask color for left side
		not.l	d1
		move.l	a1,a2
		move	d3,d7
.lftlp		and.l	d1,(a2)
		or.l	d4,(a2)+
		dbra	d7,.lftlp
		move.l	(sp)+,d4

		st.b	(a5)		; Mark column to be updated

; Do Right side
		swap	d6
		cmp	d5,d6		; Is it a left & right case?
		beq.s	.norgt
		move	d2,d7		; Get right side mask
		and	#7,d7
		lsl	#2,d7
		lea	gr_rect_rgt,a3
		move.l	0(a3,d7.w),d1
		move.l	d4,-(sp)
		and.l	d1,d4		; Mask color for left side
		not.l	d1
		move.l	a4,a2
		move	d3,d7
.rgtlp		and.l	d1,(a2)
		or.l	d4,(a2)+
		dbra	d7,.rgtlp
		move.l	(sp)+,d4


		move.l	a5,-(sp)
		move.w	d2,d7		; Set pointer to column update vars
		lsr.w	#3,d7
		lea	gr_cols_touched,a5
		add.w	d7,a5
		st.b	(a5)		; Mark column to be updated
		move.l	(sp)+,a5

; Do Middle columns
.norgt
		move	d2,d1		; Calculate width in columns
		lsr	#3,d1
		move	d0,d7
		lsr	#3,d7
		sub	d7,d1
		sub	#2,d1		; D1 is now width in columns - 2
		cmp	#-1,d1
		ble.s	.exit
		add	#4,d5		; Bump to next column

		addq.l	#1,a5

		move.l	0(a0,d5.w),a1
		swap	d6
.midlp_outer	move.l	a1,a2
		add	d6,a2
		move	d3,d7
.midlp_inner	move.l	d4,(a2)+
		dbra	d7,.midlp_inner

		st.b	(a5)+		; Mark column to be updated

		add	#4,d5		; Bump to next column
		move.l	0(a0,d5.w),a1
		dbra	d1,.midlp_outer

.exit		movem.l	(sp)+,d0-d7/a0-a5
		rts


		end
