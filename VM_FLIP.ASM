;{----------------------------------------------------------------------}
;{ Module:	VM_FLIP.ASM						}
;{ Description:	Draw a flippped shape into _vm_cpuscreen		}
;{ Part of:	TOONS.BIN						}
;{ Original:	Kevin L. McGrath					}
;{ Started:	02/26/94						}
;{----------------------------------------------------------------------}
;{		*** Copyright 1994 Futurescape Productions ***		}
;{----------------------------------------------------------------------}

		include	vm_defs.inc
		include	format.inc

		OPT	LLBL
		OPT	MEX

		tsection	.text

		XREF	gr_fixclip
		XREF	gr_cols_touched
		XREF	gr_ct_ptr


;{----------------------------------------------------------------------}
;{ Function:	vm_flip_draw(short x, short y, short frame, long shpptr,}
;{			short flipflags);				}
;{ Description:	'C' callable routine to draw a flipped shape into the	}
;{		character buffer.					}
;{ Parameters:	x,y = x, y position					}
;{		frame = frame in animation				}
;{		shpptr = pointer to FPB file				}
;{		flipflags = flip flags 1=Horizontal, 2=Vertical, 3=Both	}
;{ Returns:	.							}
;{----------------------------------------------------------------------}
                 
		XDEF	_vm_flip_draw
_vm_flip_draw:
		link	a6,#0
		movem.l	d1-d3/a0,-(sp)

		move.w	8(a6),d0
		move.w	10(a6),d1
		move.w	12(a6),d2
		move.l	14(a6),a0
		move.w	18(a6),d3
		bsr	gr_flip_draw

		movem.l	(sp)+,d1-d3/a0
		unlk	a6
		rts

;{----------------------------------------------------------------------}
;{ Function:	gr_draw							}
;{ Description:	draw a bitmap into the character buffer			}
;{ Parameters:	a0 = pointer to shape					}
;{		d0 = x position on the screen to draw the shape		}
;{		d1 = y position on the screen to draw the shape		}
;{		d2 = frame number					}
;{		d3 = flip flags 1=Horizontal, 2=Vertical, 3=Both	}
;{ returns:	.							}
;{----------------------------------------------------------------------}

		XREF	gr_xtable
		XREF	gr_pixtab0
		XREF	gr_pixtab1
		XREF	gr_pixtab2
		XREF	gr_pixtab3
		XREF	gr_pixtab4
		XREF	gr_pixtab0h
		XREF	gr_pixtab1h
		XREF	gr_pixtab2h
		XREF	gr_pixtab3h
		XREF	gr_pixtab4h

		XREF	gr_tclip
		XREF	gr_bclip
		XREF	gr_lclip
		XREF	gr_rclip

		XDEF	gr_flip_draw
gr_flip_draw:
		movem.l	d0-d7/a0-a6,-(sp)

		lsr.w	#1,d0			; Deal with 640x400 virtual
		lsr.w	#1,d1			; screen...

		swap	d3			; Save flip flags
; Get bitmap info
		move.w	AHFLISTOFFSET(a0),d4	; Assume 1 animation
		add.w	d2,d2			; Add in frame #
		add.w	d2,d4

*
*	Test for frame number overflow
*
		cmp.w	AHSPRITEOFFSET(a0),d4
		blo.s	.offs_ok
.hang		bra.s	.hang
		bra	.exit
.offs_ok


		move.w	0(a0,d4.w),d4		; Get offset to frame info
		lea	SAHEADSIZE(a0,d4.w),a2	; Get ptr to frame info
		clr.w	d2
		clr.w	d3
		move.b	SAHVLINK(a2),d2		; Get width
		move.b	SAHVLINK+1(a2),d3	; Get height

; Do clipping
		moveq.l	#0,d7
		tst.b	_vm_clip
		beq	.no_clip
		jsr	gr_fixclip
		moveq.l	#0,d6		; Setup X clipping offset
		cmp.w	gr_lclip,d0	; Test LEFT side
		bge.s	.OkL
		move.w	gr_lclip,d4	; Calculate new left side
		sub.w	d0,d4
		cmp.w	d2,d4		; Is the image totally out?
		bge	.exit
		move.w	gr_lclip,d0	; Change X to left side
		sub.w	d4,d2		; Change Width to new width
		lsr.w	#1,d4		; This will fuck up on odd pixel clips
		mulu.w	d3,d4
		move.w	d4,d6
.OkL		cmp.w	gr_rclip,d0	; Test RIGHT side
		bgt	.exit		; Is the image totally out?
		move.w	d0,d4
		add.w	d2,d4
		cmp.w	gr_rclip,d4
		ble.s	.OkR
		move.w	gr_rclip,d2	; Calculate new right side
		sub.w	d0,d2
.OkR		cmp.w	gr_tclip,d1	; Test TOP side
		bge.s	.OkT
		move.w	gr_tclip,d4	; Calculate new left side
		sub.w	d1,d4
		cmp.w	d3,d4		; Is the image totally out?
		bge	.exit
		move.w	gr_tclip,d1	; Change Y to top side
		sub.w	d4,d3		; Change Height to new height
		move.w	d4,d7		; Set top skip value
.OkT		cmp.w	gr_bclip,d1	; Test BOTTOM side
		bgt	.exit		; Is the image totally out?
		move.w	d1,d4
		add.w	d3,d4
		cmp.w	gr_bclip,d4
		ble.s	.no_clip
		swap	d7		; Calculate new bottom side
		move.w	d3,d7
		move.w	gr_bclip,d3
		sub.w	d1,d3
		beq	.exit
		sub.w	d3,d7
		swap	d7

; Get more bitmap info
.no_clip	moveq.l	#0,d4
		move.w	SAATTRIBUTES(a2),d4
		lsl.l	#5,d4			; * 32 bytes per character
		move.w	AHCHAROFFSET(a0),d5	; Get to character data ...
		adda.w	d5,a0			; ... info list
		adda.l	d4,a0			; Now pointing to bitmap
		adda.l	#2,a0			; Skip number of characters
		lsr.w	#1,d2			; For dbra's...
		sub.w	#1,d2
		bmi	.exit
		sub.w	#1,d3

; Get offsets into bitmapped screen
		move.w	d0,d4		; Compute character column for X1
		lsr.w	#1,d4		; Divide by 8 pixels per character
		and.w	#$FFFC,d4	; Mask for long address table
		lea	gr_xtable,a1
		move.l	0(a1,d4.w),a1	; Get character column addr from table
		move.w	d1,d4
		add.w	d4,d4		; Y line offset
		add.w	d4,d4
		add.w	d4,a1		; Get actual offset to scanline

		move.w	d0,d4		; Set pointer to column update vars
		lsr.w	#3,d4
		lea	gr_cols_touched,a4
		add.w	d4,a4
		move.l	a4,gr_ct_ptr

; Handle flip stuff
		swap	d3		; Restore flip flags
		moveq.l	#1,d1
		swap	d1
		btst	#0,d3		; Vertical flip?
		beq.s	.not_vert
		neg.w	d7		; Negate clipping skippers
		swap	d7
		neg.w	d7
		swap	d7
		move.w	#-1,d1		; Change to negative increment
		swap	d1
		move.b	SAHVLINK+1(a2),d1	; Get height adjustment
.not_vert	btst	#1,d3		; Horizontal flip?
		beq.s	.not_horz
		moveq.l	#0,d4
		moveq.l	#0,d5
		move.b	SAHVLINK(a2),d5		; Get width
		lsr.w	#1,d5
		move.b	SAHVLINK+1(a2),d4	; Get height
		mulu.w	d4,d5
		add.w	d4,d5
		adda.l	d5,a0		; Adjust to the end of the bitmap
		add.w	d4,d4		; Adjust first clip skipper to go
		sub.w	d4,d7		; backwards one line everyline
		neg.l	d6		; Adjust clip offset
.not_horz	adda.l	d6,a0

;
; ----- d0 = x position
;	d1 = height adjustment for vertical flip
;	d2 = (width/2)-1
;	d3 = height-1
;	d4 = TEMP
;	d5 = TEMP
;	d6 = Y clipping adjustment
;	d7 = Ending Y offset / Begging Y offset
;	a0 = pointer to bitmapped pixels
;	a1 = pointer into the frame buffer

		btst	#2,d0		; Odd word column?
		beq.s	.even
		adda.l	#2,a1		; Bump to the next word
.even		btst	#0,d0		; Odd pixel start?
		bne	.odd_blit

****
****		Even pixel boundary blitter
****

.even_blit	btst	#1,d3		; Horizontal flip?
		beq.s	.not_h1
		lea	gr_pixtab1h,a2	; Get pointers to the mask tables
		lea	gr_pixtab3h,a4
		bra.s	.exit_h1
.not_h1		lea	gr_pixtab1,a2	; Get pointers to the mask tables
		lea	gr_pixtab3,a4
.exit_h1	swap	d3		; Restore height
		move.w	d3,d4		; Restore DBRA counter
		move.l	a1,a3		; Restore frame buffer pointer
		move	d0,d5		; Jump to the correct blit to start
		and	#7,d5
		add	d5,d5		; Only need to * 2 because X is even
		lea	.even_jmp,a5
		move.l	0(a5,d5.w),a5
		jmp	(a5)

.blit0		add.w	d1,a0		; Do vertical flip skip
		swap	d1
		add.w	d7,a0		; Skip top for clipping
.loop0		clr.w	d5		; Get 2 pixels
		move.b	(a0),d5
		add.w	d1,a0
		add.w	d5,d5		; Convert them into a long table offs
		add.w	d5,d5
		move.l	0(a2,d5.w),d5	; Grab the mask and shifted color
		and.w	d5,(a3)		; Cut a hole into the frame buffer
		swap	d5
		or.w	d5,(a3)		; Paint two pixels into the hole
		addq	#4,a3		; Bump to next scanline
		dbra	d4,.loop0
		swap	d7		; Skip bottom for clipping
		add.w	d7,a0
		swap	d7
		swap	d1		; Do vertical flip skip
		add.w	d1,a0
		move.w	d3,d4		; Restore DBRA counter

		move.l	gr_ct_ptr,a3	; Set this column to be updated
		st.b	(a3)

		move.l	a1,a3		; Restore frame buffer pointer
		dbra	d2,.blit1
		bra	.exit

.blit1		add.w	d1,a0		; Do vertical flip skip
		swap	d1
		add.w	d7,a0		; Skip top for clipping
.loop1		clr.w	d5		; Get 2 pixels
		move.b	(a0),d5
		add.w	d1,a0
		add.w	d5,d5		; Convert them into a long table offs
		add.w	d5,d5
		move.l	0(a4,d5.w),d5	; Grab the mask and shifted color
		and.w	d5,(a3)		; Cut a hole into the frame buffer
		swap	d5
		or.w	d5,(a3)		; Paint two pixels into the hole
		addq	#4,a3		; Bump to next scanline
		dbra	d4,.loop1
		swap	d7		; Skip bottom for clipping
		add.w	d7,a0
		swap	d7
		swap	d1		; Do vertical flip skip
		add.w	d1,a0
		move.w	d3,d4		; Restore DBRA counter
		adda.l	#2,a1		; Bump to the next word

		move.l	gr_ct_ptr,a3	; Set this column to be updated
		st.b	(a3)

		move.l	a1,a3		; Restore frame buffer pointer
		dbra	d2,.blit2
		bra	.exit

.blit2		add.w	d1,a0		; Do vertical flip skip
		swap	d1
		add.w	d7,a0		; Skip top for clipping
.loop2		clr.w	d5		; Get 2 pixels
		move.b	(a0),d5
		add.w	d1,a0
		add.w	d5,d5		; Convert them into a long table offs
		add.w	d5,d5
		move.l	0(a2,d5.w),d5	; Grab the mask and shifted color
		and.w	d5,(a3)		; Cut a hole into the frame buffer
		swap	d5
		or.w	d5,(a3)		; Paint two pixels into the hole
		addq	#4,a3		; Bump to next scanline
		dbra	d4,.loop2
		swap	d7		; Skip bottom for clipping
		add.w	d7,a0
		swap	d7
		swap	d1		; Do vertical flip skip
		add.w	d1,a0
		move.w	d3,d4		; Restore DBRA counter

		move.l	gr_ct_ptr,a3	; Set this column to be updated
		st.b	(a3)

		move.l	a1,a3		; Restore frame buffer pointer
		dbra	d2,.blit3
		bra	.exit

.blit3		add.w	d1,a0		; Do vertical flip skip
		swap	d1
		add.w	d7,a0		; Skip top for clipping
.loop3		clr.w	d5		; Get 2 pixels
		move.b	(a0),d5
		add.w	d1,a0
		add.w	d5,d5		; Convert them into a long table offs
		add.w	d5,d5
		move.l	0(a4,d5.w),d5	; Grab the mask and shifted color
		and.w	d5,(a3)		; Cut a hole into the frame buffer
		swap	d5
		or.w	d5,(a3)		; Paint two pixels into the hole
		addq	#4,a3		; Bump to next scanline
		dbra	d4,.loop3
		swap	d7		; Skip bottom for clipping
		add.w	d7,a0
		swap	d7
		swap	d1		; Do vertical flip skip
		add.w	d1,a0
		move.w	d3,d4		; Restore DBRA counter
		adda.l	#800-2,a1	; Bump to the next character column

		move.l	gr_ct_ptr,a3	; Set this column to be updated
		st.b	(a3)
		add.l	#1,gr_ct_ptr	; Bump column flags pointer

		move.l	a1,a3		; Restore frame buffer pointer
		dbra	d2,.blit0
		bra	.exit

****
****		Odd pixel boundary blitter
****

.odd_blit	btst	#1,d3		; Horizontal flip?
		beq.s	.not_h2
		lea	gr_pixtab0h,a2	; Get pointers to the mask tables
		lea	gr_pixtab2h,a4
		lea	gr_pixtab4h,a6
		bra.s	.exit_h2
.not_h2		lea	gr_pixtab0,a2	; Get pointers to the mask tables
		lea	gr_pixtab2,a4
		lea	gr_pixtab4,a6
.exit_h2	swap	d3		; Restore height
		move.w	d3,d4		; Restore DBRA counter
		move.l	a1,a3		; Restore frame buffer pointer
		move	d0,d5		; Jump to the correct blit to start
		and	#7,d5
		sub	#1,d5
		add	d5,d5		; Only need to * 2 because X is even
		lea	.odd_jmp,a5
		move.l	0(a5,d5.w),a5
		jmp	(a5)

.blit4		add.w	d1,a0		; Do vertical flip skip
		swap	d1
		add.w	d7,a0		; Skip top for clipping
.loop4		clr.w	d5		; Get 2 pixels
		move.b	(a0),d5
		add.w	d1,a0
		add.w	d5,d5		; Convert them into a long table offs
		add.w	d5,d5
		move.l	0(a4,d5.w),d5	; Grab the mask and shifted color
		and.w	d5,(a3)		; Cut a hole into the frame buffer
		swap	d5
		or.w	d5,(a3)		; Paint two pixels into the hole
		addq	#4,a3		; Bump to next scanline
		dbra	d4,.loop4
		swap	d7		; Skip bottom for clipping
		add.w	d7,a0
		swap	d7
		swap	d1		; Do vertical flip skip
		add.w	d1,a0
		move.w	d3,d4		; Restore DBRA counter

		move.l	gr_ct_ptr,a3	; Set this column to be updated
		st.b	(a3)

		move.l	a1,a3		; Restore frame buffer pointer
		dbra	d2,.blit5
		bra	.exit

; Special odd pixel case, upper pixel is in one word, lower is in another:

.blit5		add.w	d1,a0		; Do vertical flip skip
		swap	d1
		add.w	d7,a0		; Skip top for clipping
.loop5		clr.w	d0		; Get 2 pixels
		move.b	(a0),d0
		add.w	d1,a0
		add.w	d0,d0		; Convert them into a long table offs
		add.w	d0,d0
		move.l	0(a6,d0.w),d5	; Grab the mask and shifted color
		and.w	d5,(a3)		; Cut a hole into the frame buffer
		swap	d5
		or.w	d5,(a3)+	; Paint two pixels into the hole
		move.l	0(a2,d0.w),d5	; Grab the mask and shifted color
		and.w	d5,(a3)		; Cut a hole into the frame buffer
		swap	d5
		or.w	d5,(a3)+	; Paint two pixels into the hole
		dbra	d4,.loop5
		swap	d7		; Skip bottom for clipping
		add.w	d7,a0
		swap	d7
		swap	d1		; Do vertical flip skip
		add.w	d1,a0
		move.w	d3,d4		; Restore DBRA counter
		adda.l	#2,a1		; Bump to the next word

		move.l	gr_ct_ptr,a3	; Set this column to be updated
		st.b	(a3)

		move.l	a1,a3		; Restore frame buffer pointer
		dbra	d2,.blit6
		bra	.exit

.blit6		add.w	d1,a0		; Do vertical flip skip
		swap	d1
		add.w	d7,a0		; Skip top for clipping
.loop6		clr.w	d5		; Get 2 pixels
		move.b	(a0),d5
		add.w	d1,a0
		add.w	d5,d5		; Convert them into a long table offs
		add.w	d5,d5
		move.l	0(a4,d5.w),d5	; Grab the mask and shifted color
		and.w	d5,(a3)		; Cut a hole into the frame buffer
		swap	d5
		or.w	d5,(a3)		; Paint two pixels into the hole
		addq	#4,a3		; Bump to next scanline
		dbra	d4,.loop6
		swap	d7		; Skip bottom for clipping
		add.w	d7,a0
		swap	d7
		swap	d1		; Do vertical flip skip
		add.w	d1,a0
		move.w	d3,d4		; Restore DBRA counter

		move.l	gr_ct_ptr,a3	; Set this column to be updated
		st.b	(a3)

		move.l	a1,a3		; Restore frame buffer pointer
		dbra	d2,.blit7
		bra	.exit

; Special odd pixel case, upper pixel is in one char, lower is in another:

.blit7		add.w	d1,a0		; Do vertical flip skip
		swap	d1
		add.w	d7,a0		; Skip top for clipping
		adda.l	#800-2,a1	; Bump to the next character column
		move.l	a1,a5		; Keep next column bitmap pointer
.loop7		clr.w	d0		; Get 2 pixels
		move.b	(a0),d0
		add.w	d1,a0
		add.w	d0,d0		; Convert them into a long table offs
		add.w	d0,d0
		move.l	0(a6,d0.w),d5	; Grab the mask and shifted color
		and.w	d5,(a3)		; Cut a hole into the frame buffer
		swap	d5
		or.w	d5,(a3)		; Paint two pixels into the hole
		move.l	0(a2,d0.w),d5	; Grab the mask and shifted color
		and.w	d5,(a5)		; Cut a hole into the frame buffer
		swap	d5
		or.w	d5,(a5)		; Paint two pixels into the hole
		addq	#4,a3		; Bump to next scanline
		addq	#4,a5		; Bump to next scanline
		dbra	d4,.loop7
		swap	d7		; Skip bottom for clipping
		add.w	d7,a0
		swap	d7
		swap	d1		; Do vertical flip skip
		add.w	d1,a0
		move.w	d3,d4		; Restore DBRA counter

		move.l	gr_ct_ptr,a3	; Set this column to be updated
		st.b	(a3)
		add.l	#1,gr_ct_ptr	; Bump column flags pointer
		st.b	1(a3)

		move.l	a1,a3		; Restore frame buffer pointer
		dbra	d2,.blit4

.exit		movem.l	(sp)+,d0-d7/a0-a6
		rts

.even_jmp	DC.L	.blit0
		DC.L	.blit1
		DC.L	.blit2
		DC.L	.blit3

.odd_jmp	DC.L	.blit4
		DC.L	.blit5
		DC.L	.blit6
		DC.L	.blit7

		end
		




