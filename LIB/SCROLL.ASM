;{----------------------------------------------------------------------}
;{ Module:	SCROLL.ASM						}
;{ Description:	scrolling routines					}
;{ Part of:	SEGALIB.LIB						}
;{ Original:	Ken Hurley						}
;{ Started:	5/1/93							}
;{----------------------------------------------------------------------}
;{		*** Copyright 1993 Futurescape Productions ***		}
;{----------------------------------------------------------------------}


		include	equates.inc
		include	variable.inc
		include sega.inc

		OPT	LLBL

		section	.bss

tempbuff	ds.w	67
		XDEF	_SrcMap
_SrcMap:
SrcMap		ds.l	1
maxXPos		ds.w	1
maxYPos		ds.w	1
mapChars1	ds.w	1
mapChars2	ds.w	1
_SaveVCount	ds.l	1
UpdateChars	ds.w	MAPWIDTH*2
HScrollBuff	ds.w	1024
_oldMapX	ds.w	1
_oldMapY	ds.w	1


		section	.text

		XREF	addDMAQueue,waitDMAQueue
		XREF	DrawMap
		XREF	_ScrAAddr,_ScrBAddr
		XREF	_SYS_SetPalette

		XDEF	_ScrollMap
_ScrollMap:
		link	a6,#0

		move.l	8(a6),d0
		move.l	d0,SrcMap
		bsr	ScrollMap

		unlk	a6
		rts

;
;
;
ScrollMap:
		move.l	SrcMap,a0
		
		move.l	#'CSET',d0
		jsr	findIffHeader
		move.w	d0,d1			; save size for later
		lsr.w	#5,d0
		move.w	_SYS_LastChar,d2
		add.w	d0,_SYS_LastChar
		move.w	d2,d0
		move.w	d0,mapChars1
		lsl.w	#5,d0
		jsr	addDMAQueue
		jsr	waitDMAQueue
				  
		move.l	SrcMap,a0
		move.l	#'CMAP',d0
		jsr	findIffHeader
		lea	tempbuff,a1
		clr.w	(a1)+
		move.w	#64,(a1)+
		move.w	#64-1,d0
.moveLoop:
		move.b	(a0)+,d1
		lsr.w	#2,d1
		and.w	#$0e,d1
		move.w	d1,d2
		move.b	(a0)+,d1
		add.w	d1,d1
		add.w	d1,d1
		and.w	#$e0,d1
		or.w	d1,d2
		move.b	(a0)+,d1
		lsl.w	#6,d1
		and.w	#$e00,d1
		or.w	d1,d2
		move.w	d2,(a1)+
		dbra	d0,.moveLoop
		move.w	#-1,(a1)+

		move.l	SrcMap,a0
		move.l	#'MAPA',d0
		jsr	findIffHeader
		move.w	(a0),d0			; get x blocks
		rol.w	#8,d0
		lsl.w	#3,d0
		move.w	d0,maxXPos		; maximum x to move
		move.w	2(a0),d1
		rol.w	#8,d1
		sub.w	#6,d1
		lsl.w	#3,d1
		move.w	d1,maxYPos
		
		clr.w	d0
		clr.w	d1
		lea	_MapABuff,a1
		move.w	mapChars1,d2
		jsr	DrawMap

		move.l	SrcMap,a0
		move.l	#'MAPB',d0
		jsr	findIffHeader
		clr.w	d0
		clr.w	d1
		lea	_MapBBuff,a1
		move.w	mapChars1,d2
		jsr	DrawMap

		lea	_MapABuff,a0
		move.w	_ScrAAddr,d0
		move.w	#(MAPWIDTH*2)*MAPHEIGHT,d1
		jsr	addDMAQueue

		lea	_MapBBuff,a0
		move.w	_ScrBAddr,d0
		move.w	#(MAPWIDTH*2)*MAPHEIGHT,d1
		jsr	addDMAQueue
		
		jsr	waitDMAQueue
		pea	tempbuff
		jsr	_SYS_SetPalette
		add.l	#4,sp
		clr.b	_SYS_JoyHit

ScrollLoop:
		move.l	_SYS_VCount,d0
		move.l	d0,_SaveVCount

		move.w	_MapY,d1
		move.w	_MapX,d2

		tst.b	_SYS_JoyTable+JOY_UP
		beq.s	.notUp
		sub.w	#3,d1
.notUp:
		tst.b	_SYS_JoyTable+JOY_DOWN
		beq.s	.notDown
		add.w	#3,d1
.notDown:
		tst.b	_SYS_JoyTable+JOY_RIGHT
		beq.s	.notRight
		add.w	#3,d2
.notRight:
		tst.b	_SYS_JoyTable+JOY_LEFT
		beq.s	.notLeft
		sub.w	#3,d2
.notLeft:
		tst.b	_SYS_JoyTable+JOY_A
		bne.s	.outaHere
.noButtons:
		move.l	SrcMap,a0
		move.w	d2,d0
		jsr	_CenterMap

		move.l	_SaveVCount,d0
		add.l	#1,d0
		cmp.l	_SYS_VCount,d0
		bgt.s	.GameSync		; find out if we need to
		move.l	_SYS_VCount,d0		; wait at least one not to
		addq.l	#1,d0			; interfere with scrolling
.GameSync:
		cmp.l	_SYS_VCount,d0
		bgt.s	.GameSync

		jsr	waitDMAQueue

		move.l	SrcMap,a0
		move.w	mapChars1,d0
		jsr	_RefreshMap		; refresh parts of map

		jmp	ScrollLoop

.outaHere:
		rts

;{----------------------------------------------------------------------}
;{ Function:	_CenterMap						}
;{ Description:	center a map around the x,y given			}
;{ Paramters:	d0 = x position						}
;{		d1 = y position 					}
;{		a0 = pointer to current map				}
;{ Returns:	.							}
;{----------------------------------------------------------------------}
		XDEF	_CenterMap
_CenterMap:
		movem.l	d0-d5/a0-a2,-(sp)

		move.l	a0,a2
		move.w	d0,d2
		move.l	#'MAPA',d0
		jsr	findIffHeader

		sub.w	#CENTERMAPX,d2			; left edge
		bpl.s	.okLeft
		clr.w	d2
.okLeft:
		sub.w	#CENTERMAPY,d1			; top edge
		bpl.s	.okTop			; is it ok?
		clr.w	d1			; nope
.okTop:
		move.w	(a0),d0			; get last character x
		rol.w	#8,d0
		sub.w	#VISIBLEWIDTH,d0
		lsl.w	#3,d0
		cmp.w	d0,d2
		bls.s	.okRight
		move.w	d0,d2
.okRight:
		move.w	2(a0),d0		; get last character y
		rol.w	#8,d0
		sub.w	#VISIBLEHEIGHT,d0
		lsl.w	#3,d0
		cmp.w	d0,d1
		bls.s	.okBottom
		move.w	d0,d1
.okBottom:
		move.w	_MapX,d0
		move.w	d0,_oldMapX		; save old map x for refresh
		move.w	_MapY,d0
		move.w	d0,_oldMapY		; and map Y

		move.w	d2,d0
		add.w	#CENTERMAPX,d0			; center x position
		move.w	d0,_MapX

		move.w	d1,d0

		add.w	#CENTERMAPY,d0			; center y position
		move.w	d0,_MapY

		lsr.w	#3,d2
		lsr.w	#3,d1
		move.w	d2,d0

		lea	HScrollBuff,a0
		move.w	_MapX,d0
		sub.w	#CENTERMAPX,d0
		and.w	#1023,d0
		neg.w	d0
		move.w	#MAPHEIGHT-1,d1
.hscrollLoop:
		move.w	d0,(a0)+
		move.w	d0,(a0)+
		adda.w	#28,a0
		dbra	d1,.hscrollLoop

		lea	HScrollBuff,a0
		move.w	#1024,d1
		move.w	#HScroll,d0
		jsr	addDMAQueue

		movem.l	(sp)+,d0-d5/a0-a2
		rts


;{----------------------------------------------------------------------}
;{ Function:	_RefreshMap						}
;{ Description:	refreshes parts of map that may have gotten scrolled	}
;{		out of bounds						}
;{ Paramters:	a0 = pointer to map					}
;{		d0 = character number of VDP load			} 
;{		_MapX, _MapX, _oldMapX, _oldMapY			}
;{ Returns:	.							}
;{----------------------------------------------------------------------}
		XDEF	_RefreshMap
_RefreshMap:

		movem.l	d0-d7/a0-a4,-(sp)

		move.w	d0,d7
		move.l	a0,a2
		move.l	#'MAPB',d0   		; get MAPB pointer
		jsr	findIffHeader
		move.l	a0,a1

		move.l	a2,a0
		move.l	#'MAPA',d0		; and MAPB pointer
		jsr	findIffHeader

		movem.l	d0-d7/a0-a6,-(sp)
		jsr	UpdateXMap
		movem.l	(sp)+,d0-d7/a0-a6

		jsr	UpdateYMap

		AutoIncrement 2

		st	_SYS_VDPAccess

		movem.l	(sp)+,d0-d7/a0-a4
		rts


;
;
;
UpdateXMap:

		move.w	_oldMapX,d0		; assume right movement
		sub.w	#CENTERMAPX,d0
		and.w	#~7,d0
		add.w	#MAPWIDTH*8,d0

		move.w	_MapX,d4
		and.w	#~7,d4
		move.w	_oldMapX,d2
		and.w	#~7,d2
		sub.w	d2,d4
		bge.s	.dontNeg
		move.w	_MapX,d0
		sub.w	#CENTERMAPX,d0
		and.w	#~7,d0
		neg.w	d4
.dontNeg:
		asr.w	#3,d0
		asr.w	#3,d4			; # characters
		subq.w	#1,d4
		blt	.noXMovement		; didn't move x wise

		and.l	#$ffff,d0

		move.w	_MapY,d2
		sub.w	#CENTERMAPY,d2
		and.w	#~7,d2
		lsr.w	#3,d2
		move.w	d2,d5
		and.w	#(MAPHEIGHT*2)-1,d2	; destination buffer
		lsl.w	#1,d2			; and words
		lea	UpdateChars,a2

		move.w	(a0),d3			; get width of map
		rol.w	#8,d3
		mulu	d3,d5			; mul by y character

		add.l	d0,d5			; + x character offset

		lsl.l	#1,d5
		lsl.w	#1,d3			; width of map

		lea	4(a0),a3		; bypass width * height
		lea	4(a1),a4
		adda.l	d5,a3
		adda.l	d5,a4

		move.w	#MAPHEIGHT-1,d6
.moveLoop1:
		move.w	(a3),d1
		adda.w	d3,a3
		rol.w	#8,d1
		add.w	d7,d1
		move.w	d1,0(a2,d2.w)		; store in source
		addq.w	#2,d2
		and.w	#(MAPHEIGHT*4)-1,d2
		dbra	d6,.moveLoop1

		move.w	#MAPHEIGHT-1,d6
.moveLoop2:
		move.w	(a4),d1
		adda.w	d3,a4
		rol.w	#8,d1
		add.w	d7,d1
		move.w	d1,0(a2,d2.w)		; store in source
		addq.w	#2,d2
		and.w	#(MAPHEIGHT*4)-1,d2
		dbra	d6,.moveLoop2

		move.w	_ScrAAddr,d5
		and.w	#MAPWIDTH-1,d0
		lsl.w	#1,d0
		add.w	d0,d5
		CalcVramWrtAddrCode d5,d0
		move.l	d0,d5

		sf	_SYS_VDPAccess		; don't screw with VDP accesses
		AutoIncrement (MAPWIDTH*2)
		lea	UpdateChars,a2
		move.w	#(MAPHEIGHT*2)-1,d0
		move.l	d5,VCTRL
.MXLoop:
		move.w	(a2)+,VDATA
		dbra	d0,.MXLoop
.noXMovement:
		rts


;
;
;
UpdateYMap:

		move.w	_oldMapY,d0		; assume right movement
		sub.w	#CENTERMAPY,d0
		and.w	#~7,d0
		add.w	#MAPHEIGHT*8,d0

		move.w	_MapY,d4
		and.w	#~7,d4
		move.w	_oldMapY,d2
		and.w	#~7,d2
		sub.w	d2,d4
		bge	.dontNeg
		move.w	_MapY,d0
		sub.w	#CENTERMAPY,d0
		and.w	#~7,d0
		neg.w	d4
.dontNeg:
		asr.w	#3,d0
		asr.w	#3,d4			; # characters
		subq.w	#1,d4
		blt	.noYMovement		; didn't move y wise

		and.l	#$ffff,d0

		move.w	_MapX,d2
		sub.w	#CENTERMAPX,d2
		and.w	#~7,d2
		lsr.w	#3,d2
		move.w	d2,d5
		and.w	#MAPWIDTH-1,d2		; destination buffer
		lsl.w	#1,d2			; and words
		lea	UpdateChars,a2

		move.w	(a0),d3			; get width of map
		rol.w	#8,d3
		mulu	d0,d3			; mul by y character

		add.l	d3,d5			; + y character offset

		lsl.l	#1,d5

		lea	4(a0),a3		; bypass width * height
		lea	4(a1),a4
		adda.l	d5,a3
		adda.l	d5,a4

		move.w	#MAPWIDTH-1,d6
.moveLoop1:
		move.w	(a3)+,d1
		rol.w	#8,d1
		add.w	d7,d1
		move.w	d1,0(a2,d2.w)		; store in source
		addq.w	#2,d2
		and.w	#(MAPWIDTH*2)-1,d2
		dbra	d6,.moveLoop1

		move.w	#MAPWIDTH-1,d6
		lea	UpdateChars+(MAPWIDTH*2),a2
.moveLoop2:
		move.w	(a4)+,d1
		rol.w	#8,d1
		add.w	d7,d1
		move.w	d1,0(a2,d2.w)		; store in source
		addq.w	#2,d2
		and.w	#(MAPWIDTH*2)-1,d2
		dbra	d6,.moveLoop2

		move.w	_ScrAAddr,d5
		move.w	d0,d6
		and.w	#(MAPHEIGHT*2)-1,d0
		lsl.w	#7,d0
		add.w	d0,d5
		CalcVramWrtAddrCode d5,d0
		move.l	d0,d5

		sf	_SYS_VDPAccess		; don't screw with VDP accesses

		AutoIncrement 2
		lea	UpdateChars,a2
		move.w	#MAPWIDTH-1,d0
		move.l	d5,VCTRL
.MYLoop1:
		move.w	(a2)+,VDATA
		dbra	d0,.MYLoop1


		move.w	_ScrAAddr,d5
		add.w	#MAPHEIGHT,d6		; b map offset
		and.w	#(MAPHEIGHT*2)-1,d6
		lsl.w	#7,d6
		add.w	d6,d5
		CalcVramWrtAddrCode d5,d0
		move.l	d0,d5

		lea	UpdateChars+(MAPWIDTH*2),a2
		move.w	#MAPWIDTH-1,d0
		move.l	d5,VCTRL
.MYLoop2:
		move.w	(a2)+,VDATA
		dbra	d0,.MYLoop2
.noYMovement:
		rts


;{----------------------------------------------------------------------}
;{ Function:	findIffHeader						}
;{ Description:	find match to iff header and return address just past	}
;{ Parameters:	d0 = long "XXXX" iff id					}
;{		a0 = start of file					}
;{ Returns:	d0 = length of block					}
;{		a0 = pointer just past block header			}
;{----------------------------------------------------------------------}
		XDEF	findIffHeader
findIffHeader:

		movem.l	d1-d2/a1,-(sp)

.findLoop:
		move.l	(a0)+,d1
		cmp.l	d0,d1
		bne.s	.notFound

		move.l	(a0)+,d0
		add.l	#1,d0		; round to word
		and.l	#$fffffffe,d0
		bra.s	.foundIt
.notFound:
		move.l	(a0)+,d1
		add.l	#1,d1
		and.l	#$fffffffe,d1
		adda.l	d1,a0
		bra.s	.findLoop
.foundIt:
		movem.l	(sp)+,d1-d2/a1
		rts


;
; ----- Now update vscroll if needed
;


		end
