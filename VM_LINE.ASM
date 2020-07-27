
		section		.bss

deldx		ds.w	1
deldy		ds.w	1
delsx		ds.w	1
delsy		ds.w	1

	        section 	.text

;{----------------------------------------------------------------------}
;{ Function:	BresenhamLine						}
;{ Description:	Do a bresenham line in characters			}
;{ Parameters:	d0 = x1 position					}
;{		d1 = y1 position					}
;{		d2 = x2 position					}
;{		d3 = y2 position					}
;{ Returns:	d0 = 1 if collision.					}
;{		     0 otherwise					}
;{----------------------------------------------------------------------}

		XDEF	BresenhamLine
BresenhamLine:
		movem.l	d1-d7,-(sp)		; save registers

		move.w	#1,d6			; initial increment y direction
		move.w	#1,d7			; initial increment x direction
		sub.w	d1,d3			; subtract y1 from y2
		bge.s	.storey			; skip if y2-y1 is nonnegative
		neg.w	d6			; negative y direction
		neg.w	d3			; absolute value of y2-y1
.storey:
		move.w	d6,deldy		; delta move in diagonal y direction
		sub.w	d0,d2			; subtrack x1
		bge.s	.storex			; skip if x2-x1 is postive
		neg.w	d7			; make negative x direction
		neg.w	d2			; absolute value of d2
.storex:
		move.w	d7,deldx		; delta move in diagonal x direction
		cmp.w	d3,d2			; compare dels with delp
		bge.s	.setdiag		; skip if straight move in x direction
		clr.w	d7
		exg	d3,d2			; exchange differences
		bra.s	.storedelsxy		; save off delta straight moves
.setdiag:
		clr.w	d6			; zap y update
.storedelsxy:
		move.w	d7,delsx		; save delta straight x dir
		move.w	d6,delsy		; save delta straight y dir
		add.w	d3,d3			; get delp and * 2
		move.w	d3,d5			; change if straight move
		sub.w	d2,d3			; 2*delp-dels
		move.w	d3,d7			; initial value
		sub.w	d2,d3
		move.w	d3,d6
		addq.w	#1,d2			; increment count

		move.w	d2,d3			; actual counter now
		subq.w	#1,d3			; for dbra
		move.w	d4,d2			; color passing register
.drawline:
;
; ----- put collision detection routine here
;	normally this would be where to plot a pixel
;

		jsr	collision		; test collision
		tst.w	d0			; see if it happened
		bne.s	.exit			; exit if collision

;
; -----	now update to next point on line
;
		tst.w	d7			; determine straight or diagonal
		bge.s	.diagonal
.straight:
		add.w	delsx,d0		;update x
		add.w	delsy,d1		;update y
		add.w	d5,d7			;update error term
		dbra	d3,.drawline
		clr.w	d0			; no collision
		bra.s	.exit
.diagonal:
		add.w	deldx,d0		;update x
		add.w	deldy,d1		;update y
		add.w	d6,d7			;update error term
		dbra	d3,.drawline
		clr.w	d0			; no collision flag
.exit:
		movem.l	(sp)+,d1-d7	
		rts

		end
