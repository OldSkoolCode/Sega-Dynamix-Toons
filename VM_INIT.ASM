; $Header: h:\toons\rcs\vm_init.asm_v 1.1 1994/06/15 23:26:45 KENH Exp $
;{----------------------------------------------------------------------}
;{ Module:	VM_INIT.ASM						}
;{ Description:	Initialization routines for virtual machine interface	}
;{ Part of:	TOONS.BIN						}
;{ Original:	Kenneth L. Hurley					}
;{ Started:	10/20/93						}
;{----------------------------------------------------------------------}
;{		*** Copyright 1993 Futurescape Productions ***		}
;{----------------------------------------------------------------------}

;
; $Log: vm_init.asm_v $
; Revision 1.1  1994/06/15  23:26:45  KENH
; Initial revision
;
; Revision 1.1  1993/12/08  15:19:53  KENH
; Initial revision
;
;

		include equates.inc
		include	vm_defs.inc

		tsection	.text

		XDEF	_vm_init
		XREF	SetVRAMWrite
		XREF	_ScrBAddr

;{----------------------------------------------------------------------}
;{ Function:	void vm_init(void);					}
;{ Description:	initialize all the variables for the Virutal Machine	}
;{ Parmeters:	.							}
;{ Returns:	.							}
;{----------------------------------------------------------------------}

_vm_init:
	        move.w  #$2700,sr
		move.w	#$8104,VCTRL	; Kill display
		move.l	#$C0000000,VCTRL	; Clear the palette
		clr.l	d0
		moveq.l	#64*2/4-1,d1
.cpl		move.l	d0,VDATA
		dbra	d1,.cpl
;
; ----- Initialize the VDP Registers
;
		lea	InitialVDP,a0	;point to VDP initialization data
		move	#$8000,d0	;register increment
		moveq	#19-1,d1	;count
.loop		move.b	(a0)+,d0
		move	d0,VCTRL
		add.w	#$0100,d0	;increment register
		dbra	d1,.loop	;slave all regs

		move.w	#$8f02,VCTRL	; make sure VDP inc = 2

;
; ----- Initialize the VDP Video RAM
;
		clr.l	d0
		jsr	SetVRAMWrite
		move.w	#65536/4-1,d1
		moveq	#0,d0
.cloop		move.l	d0,VDATA
		dbra	d1,.cloop
;
; ----- Initialize the first character to a solid color for debugging:
;
		move	#32,d0
		jsr	SetVRAMWrite
		move.w	#8-1,d1
		move.l	#$11111111,d0
.cloop2		move.l	d0,VDATA
		dbra	d1,.cloop2
;
; ----- Initialize the VDP Scroll RAM
;
		move.l	#$40000010,VCTRL
		move.w	#40-1,d1
		move.l	#$120,d0
.slp		move.l	d0,VDATA
		dbra	d1,.slp
		move.l	#$40000010,VCTRL
;		move.l	#$FFF400F4,VDATA
;
; ----- Initialize the VDP Color Palette
;
		move.l	#$C0000000,VCTRL
		lea	PALETTE(pc),a0
		moveq.l	#64/2-1,d1
.ploop		move.l	(a0)+,VDATA
		dbra	d1,.ploop

;
; ----- Initialize the VDP Screen indecies
;

		ifne	0
		move	_ScrBAddr,d0
		bsr	SetVRAMWrite

		move.w	_vm_schar,d0
		move	#25-1,d1
.coloop		move	d0,d3
		move	#40-1,d2	; Init one row
.ciloop1	move	d3,VDATA
		add	#25,d3
		dbra	d2,.ciloop1
		move	#64-40-1,d2	; Clear the rest of the character row
.ciloop2	move	#0,VDATA
		dbra	d2,.ciloop2
		add	#1,d0
		dbra	d1,.coloop
		move	#((32-25)*64)-1,d1	; Clear bottom of the screen
.coloop2	move	#0,VDATA
		dbra	d1,.coloop2
		endc

		move.b	#16,_vm_max_colors
		move.w	#SCREENHREZ,d0
		move.w	#SCREENVREZ,d1
		clr.w	_vm_lclip
		clr.w	_vm_tclip
		move.w	d0,_vm_width
		move.w	d0,_vm_rclip
		move.w	d1,_vm_height
		move.w	d1,_vm_bclip
		move.b	#8,_vm_font_wid
		move.b	#8,_vm_font_hgt
		move.l	#0,_vm_font_ptr
		rts


InitialVDP:
	DC.B	%00000100	; 0 no H interrupt, enable read HV counter
	DC.B	%01100100	; 1 ENABLE display, ENABLE V interrupt, NO DMA, 28CELL HIGH(NTSC)
	DC.B	ScrollA>>10	; 2 Pattern Table A
	DC.B	Window>>10	; 3 Pattern Window
	DC.B	ScrollB>>13	; 4 Pattern Table B
	DC.B	SpriteAttr>>9	; 5 Sprite Attributes
	DC.B	0		; 6 MUST BE 0
	DC.B	%00000000	; 7 Background colour 0 in palette 0
	DC.B	0		; 8 MUST BE 0
	DC.B	0		; 9 MUST BE 0
	DC.B	%11111111	;10 H interrupt divider
	dc.b	%00000000	;11 NO Ext interrupt, FULL V scroll, FULL H scroll
*	dc.b	%00000010	;11 NO Ext interrupt, FULL V scroll, FULL H scroll
	DC.B	%10000001	;12 40CELL WIDE, NO shadow/hilight, NO interlace
	DC.B	HScroll>>10	;13 H Scroll Table    @62K
	DC.B	0		;14 MUST BE 0
	DC.B	%00000010	;15 Autoinc = 2 (i.e. increment by WORD)
	DC.B	%00010001	;16 Scroll size 64 HIGH by 64 WIDE occupies 64*64*2=8K bytes. NB CellMapCols
	DC.B	%00000000	;17 Window H position = 0  \  => NO window
	DC.B	%00000000	;18 Window V position = 0  /

	DS.W	0		; Align
*************************************************************************
*
*	DEFAULT SEGA PALETTE
*
*************************************************************************

PALETTE:
*		  BGR
	DC.W	$0000	; 0 Transparent
	DC.W	$000E	; 1 Bright Red
	DC.W	$0008	; 2 Medium Red
	DC.W	$0004	; 3 Dark Red
	DC.W	$00E0	; 4 Bright Green
	DC.W	$0080	; 5 Medium Green
	DC.W	$0040	; 6 Dark Green
	DC.W	$0E00	; 7 Bright Blue
	DC.W	$0800	; 8 Medium Blue
	DC.W	$0400	; 9 Dark Blue
	DC.W	$0E0E	; A Purple
	DC.W	$00EE	; B Yellow
	DC.W	$0EEE	; C White
	DC.W	$0AAA	; D Grey
	DC.W	$0444	; E Dk. Grey
	DC.W	$0000	; F Black

	DC.W	$0000	; 0 Transparent
	DC.W	$000E	; 1 Bright Red
	DC.W	$0008	; 2 Medium Red
	DC.W	$0004	; 3 Dark Red
	DC.W	$00E0	; 4 Bright Green
	DC.W	$0080	; 5 Medium Green
	DC.W	$0040	; 6 Dark Green
	DC.W	$0E00	; 7 Bright Blue
	DC.W	$0800	; 8 Medium Blue
	DC.W	$0400	; 9 Dark Blue
	DC.W	$0E0E	; A Purple
	DC.W	$00EE	; B Yellow
	DC.W	$0000	; C BLACK
	DC.W	$0AAA	; D Grey
	DC.W	$0444	; E Dk. Grey
	DC.W	$0EEE	; F WHITE

	DC.W	$0000	; 0 Transparent
	DC.W	$000E	; 1 Bright Red
	DC.W	$0008	; 2 Medium Red
	DC.W	$0004	; 3 Dark Red
	DC.W	$00E0	; 4 Bright Green
	DC.W	$0080	; 5 Medium Green
	DC.W	$0040	; 6 Dark Green
	DC.W	$0E00	; 7 Bright Blue
	DC.W	$0800	; 8 Medium Blue
	DC.W	$0400	; 9 Dark Blue
	DC.W	$0E0E	; A Purple
	DC.W	$00EE	; B Yellow
	DC.W	$00EE	; C YELLOW
	DC.W	$0AAA	; D Grey
	DC.W	$0444	; E Dk. Grey
	DC.W	$0000	; F BLACK

	DC.W	$0000	; 0 Transparent
	DC.W	$000E	; 1 Bright Red
	DC.W	$0008	; 2 Medium Red
	DC.W	$0004	; 3 Dark Red
	DC.W	$00E0	; 4 Bright Green
	DC.W	$0080	; 5 Medium Green
	DC.W	$0040	; 6 Dark Green
	DC.W	$0E00	; 7 Bright Blue
	DC.W	$0800	; 8 Medium Blue
	DC.W	$0400	; 9 Dark Blue
	DC.W	$0E0E	; A Purple
	DC.W	$00EE	; B Yellow
	DC.W	$0EE0	; C CYAN
	DC.W	$0AAA	; D Grey
	DC.W	$0444	; E Dk. Grey
	DC.W	$0000	; F BLACK

	DS.W	0		; Align

		end
		



