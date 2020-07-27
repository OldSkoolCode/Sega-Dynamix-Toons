*
*	Startup Code.
*

		INCLUDE	equates.inc
		INCLUDE	segalib.inc
		INCLUDE	variable.inc
		INCLUDE	sega.inc

		OPT	LLBL

		XDEF	Buserr
		XDEF	Addrerr
		XDEF	Ilglinst
		XDEF	Zdivide
		XDEF	Chkreg
		XDEF	Overflow
		XDEF	Privviol
		XDEF	Uninitv
		XDEF  __exit

		XREF	load_tbl,_main
		XREF	CellMapCols,CellMapRows
		XREF	updateDMA
		XREF	_ScrAAddr,_ScrBAddr
		XREF	_SprAttrAddr
		XREF	_updateCursor
		XREF	_remapOffset
		XREF	_hscrollValue
		XREF	_oldhscrollVal
		XREF	_vscrollValue
		XREF	_oldvscrollVal
		XREF	updatescroll

		TSECTION	.text

;		XDEF	heap_org,heap_len
;heap_org	equ	$180000
;heap_len	equ	50*1024

		XDEF	MainEntry

MainEntry:
		nop
		nop
		nop
.wait		move.w	VCTRL,d0	; Get status
		and.w	#2,d0		; DMA finished?
		bne.s	.wait		; Loop if not

		lea	VDP_Regs(pc),a0		; Initialize the VDP Registers
		move	#$8000,d0
		moveq.l	#19-1,d1
.loop		move.b	(a0)+,d0
		move	d0,VCTRL
		add.w	#$0100,d0		; Bump register
		dbra	d1,.loop

	   	move.l	#$FFFF0000,a0
		move.w	#65536/4-1,d1
		moveq	#0,d0
sl_clr:		
		move.l	d0,(a0)+
		dbra	d1,sl_clr	;clear all of the work RAM (NB. will clear a stack!)

		move.w	#64,CellMapCols	;set up cell map width
		move.w	#32,CellMapRows	;set up cell map height
		clr.w	_remapOffset

		move.b	#$00,SCtrl1	; set parallel mode and clear ints (p75)
		move.b	#$00,SCtrl2	; set parallel mode and clear ints (p75)
		move.b	#$00,SCtrl3	; set parallel mode and clear ints (p75)
		move.b	#$40,Ctrl1
		move.b	#$40,Ctrl2
*		move.b	#$40,Ctrl3
		move.b	#$7F,Ctrl3

		jsr	load_tbl

;
; ----- The following is set up for scrolling
;
setVScroll:
		moveq	#0,d0		;start address
		and.w	#$3f,d0
		or.w	#CD0,d0
		move.w	d0,VCTRL
		move.w	#CD2,VCTRL
		moveq	#80/2-1,d1	;long words
		lea	VDATA,a0	;point to VDP data port
		clr.w	d0
.sv_lp:
		move.w	d0,(a0)		; clear scrolls for A
		move.w	#$120,(a0)	; set b past scroll A
		dbra	d1,.sv_lp	; set all
		st	_SYS_VDPAccess	; say can access VDP now

;		move.w	#CENTERMAPX,_MapX
;		move.w	#CENTERMAPY,_MapY
		clr.w	_hscrollValue
		clr.w	_oldhscrollVal
		clr.w	_vscrollValue
		clr.w	_oldvscrollVal

		move.w	#ScrollA,_ScrAAddr
		move.w	#ScrollB+((MAPWIDTH*2)*(MAPHEIGHT+4)),_ScrBAddr
		move.w	#SpriteAttr,_SprAttrAddr

		jmp	_main
__exit:		
		bra	__exit
		rts
		jmp	__exit

VDP_Regs:
	DC.B	%00000100	; 0 no H interrupt, enable read HV counter
	DC.B	%01110100	; 1 ENABLE display, ENABLE V interrupt, NO DMA, 28CELL HIGH(NTSC)
	DC.B	ScrollA>>10	; 2 Pattern Table A
	DC.B	Window>>10	; 3 Pattern Window
	DC.B	ScrollB>>13	; 4 Pattern Table B
	DC.B	SpriteAttr>>9	; 5 Sprite Attributes
	DC.B	0		; 6 MUST BE 0
	DC.B	%00000000	; 7 Background colour 0 in palette 0
	DC.B	0		; 8 MUST BE 0
	DC.B	0		; 9 MUST BE 0
	DC.B	%11111111	;10 H interrupt divider
	DC.B	%00000100	;11 NO Ext interrupt, 2CELL V scroll, FULL H scroll
	DC.B	%10000001	;12 40CELL WIDE, NO shadow/hilight, NO interlace
	DC.B	HScroll>>10	;13 H Scroll Table    @62K
	DC.B	0		;14 MUST BE 0
	DC.B	%00000010	;15 Autoinc = 2 (i.e. increment by WORD)
	DC.B	%00010001	;16 Scroll size 64 HIGH by 64 WIDE occupies 64*64*2=8K bytes. NB CellMapCols
	DC.B	%00000000	;17 Window H position = 0  \  => NO window
	DC.B	%00000000	;18 Window V position = 0  /

	DS.W	0		; Align

;{----------------------------------------------------------------------}
;{ Function:	__stk_ck						}
;{ Description:	Check to make sure that the heap doesn't overrun the	}
;{		stack.  To turn on, set compiler flag -XS		}
;{ Parameters:	.							}
;{ Returns:	.							}
;{----------------------------------------------------------------------}

	XDEF	__stk_ck

	XREF	__heap_base
	XREF	heap_org

	XREF	_CharSet
	XREF	_AsciiPalette
	XREF	_SYS_SetPalette
	XREF	_ScreenRow
	XREF	_ScreenCol
	XREF	_puts

__stk_ck:
	movea.l	__heap_base,a0	; get current bottom of available heap
	move.l	a0,d1
	tst.l	d1
	bne.s	.valid
	movea.l	#heap_org,a0	; if NULL, use __heap_org
.valid	adda.l	#100,a0		; add a safety margin
	adda.l	d0,a0		; adjust for stack space to be used by
	cmpa.l	sp,a0		; current function
	blt.s	.exit

	sf.b	_SYS_VDPAccess
	clr.l	d0		; Initialize the VDP Video RAM
	jsr	SetVRAMWrite
	move.w	#65536/4-1,d1
	moveq	#0,d0
.cloop	move.l	d0,VDATA
	dbra	d1,.cloop
	move.l	#32,d0		; Load the character set
	jsr	SetVRAMWrite
	lea.l	_CharSet,a1
	adda.l	#32,a1
	move	#16*96-1,d1
.loop	move	(a1)+,VDATA
	dbra	d1,.loop
	pea.l	_AsciiPalette
	jsr	_SYS_SetPalette
	addq.l	#4,sp
	move	#5,_ScreenRow
	move	#5,_ScreenCol
	pea.l	.msg
	jsr	_puts
	addq.l	#4,sp

.dead	bra.s	.dead

.exit	rts

.msg	.byte	"Stack/Heap overlap!\0"
	.align	2


* ERROR EXCEPTION FUNCTIONS - JUST LET US KNOW WHAT WENT WRONG

ErrorVect:
        bra     ErrorVect               ; We point all unhandled exceptions here

	XDEF	_EnableInts
	XDEF	_DisableInts
*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
*  Enables all interrupts! TEMP FUNCTION -----
* REVISIONS:    11/91   -jf-
*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
_EnableInts:
	move.w	#$8174,VCTRL
        move.w  #$2000,SR
        rts

	XDEF	_EHInts
_EHInts:
	move.w	#$8014,VCTRL
	move.w	#$8174,VCTRL
*	move.w	#$8A01,VCTRL	; Interrupt every other scanline
        move.w  #$2000,SR
        rts

_DisableInts:
        move.w  #$2700,SR
        rts

	XDEF	Vblank
*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
* FUNCTION:     Vblank
* DESCRIPTION:  .
* RETURNS:      .
* PARAMETERS:   .
* SIDE EFFECTS: USES
* REVISIONS:    10/91   -jf-
*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Vblank:
		movem.l	d0-d7/a0-a6,-(sp)
		tst.b	_SYS_VDPAccess		; can we touch VDP right now?
		beq.s	.NoVDPAccess
		jsr	updatescroll
		jsr	_updateCursor
		jsr	updateDMA		; update DMA queue
.NoVDPAccess:
		jsr	ScanJoy1		; scan joystick
		addq.l	#1,_SYS_VCount
		st	FlyBackFlag		; set flat
		movem.l	(sp)+,d0-d7/a0-a6
	        rte


		XDEF	Hint
*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
* FUNCTION:     Hint
* DESCRIPTION:  .
* RETURNS:      .
* PARAMETERS:   .
* SIDE EFFECTS: USES
* REVISIONS:    10/91   -jf-
*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Hint:
HIexit	rte

	XDEF	ExtInt
*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
* FUNCTION:     ExtInt
* DESCRIPTION:  .
* RETURNS:      .
* PARAMETERS:   .
* SIDE EFFECTS: USES
* REVISIONS:    10/91   -jf-
*;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
ExtInt:
        rte

* Interrupt numbers.  These numbers are also defined in the standard
* header file <signal.h>.  Any modifications to these numbers *MUST*
* be accompanied by identical modifications to those #defines.

SIGBUS	 EQU 2		; Bus error.
SIGCHK	 EQU 3		; chk instruction exception.
SIGILL	 EQU 5		; Illegal instruction.
SIGOFLOW EQU 7		; Overflow (trapv instruction).
SIGPRIV	 EQU 8		; Privilege violation.
SIGSEGV	 EQU 9		; Address error.
SIGUIV	 EQU 11		; Uninitialized exception vector.
SIGZDIV	 EQU 12		; Divide by zero.

	XREF	__xraise

Buserr:
    movem.l d0-d7/a0-a7,-(sp)	; SIGBUS
    move.l  #SIGBUS,d0		; Set signal #.
    bra.s   L1

Addrerr:
    movem.l d0-d7/a0-a7,-(sp)	; SIGSEGV
    move.l  #SIGSEGV,d0		; Set signal #.
    bra.s   L1

Ilglinst:
    movem.l d0-d7/a0-a7,-(sp)	; SIGILL
    move.l  #SIGILL,d0		; Set signal #.
    bra.s   L1

Zdivide:
    movem.l d0-d7/a0-a7,-(sp)	; SIGZDIV
    move.l  #SIGZDIV,d0		; Set signal #.
    bra.s   L1

Chkreg:
    movem.l d0-d7/a0-a7,-(sp)	; SIGCHK
    move.l  #SIGCHK,d0		; Set signal #.
    bra.s   L1

Overflow:
    movem.l d0-d7/a0-a7,-(sp)	; SIGOFLOW
    move.l  #SIGOFLOW,d0	; Set signal #.
    bra.s   L1

Privviol:
    movem.l d0-d7/a0-a7,-(sp)	; SIGPRIV
    move.l  #SIGPRIV,d0		; Set signal #.
    bra.s   L1

Uninitv:
    movem.l d0-d7/a0-a7,-(sp)	; SIGUIV
    move.l  #SIGUIV,d0		; Set signal #.
L1:
	move.l	d0,-(sp)
	jsr	__xraise
	movem.l (sp)+,d0-d7/a0-a7
	rte


