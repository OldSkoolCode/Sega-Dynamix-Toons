; $Header: h:\toons\rcs\VDPLIB.ASM_v 1.1 1994/02/19 22:48:27 KENH Exp $
;{----------------------------------------------------------------------}
;{ Module:	VDPLIB.ASM						}
;{ Description:	vdp access routines					}
;{ Part of:	SEGALIB.LIB						}
;{ Original:	Kevin L. McGrath					}
;{ Started:	5/1/93							}
;{----------------------------------------------------------------------}
;{		*** Copyright 1993 Futurescape Productions ***		}
;{----------------------------------------------------------------------}

;
; $Log: VDPLIB.ASM_v $
; Revision 1.1  1994/02/19  22:48:27  KENH
; .
;
;

		include	equates.inc
		include	macros.inc
		include	variable.inc
		include	sega.inc

Z80NoROM	equ	Z80Base+4	;flag for disabling Z80 ROM accesses

		TSECTION	.text


;
;	void ClearMapBuff(void *mapPtr);
;
		XDEF	_ClearMapBuff
_ClearMapBuff:
		link	a6,#0
		move.l	8(a6),a0
		move.w	#(MAPWIDTH*MAPHEIGHT)-1,d0
.Loop1:
		clr.w	(a0)+
		dbra	d0,.Loop1
		unlk	a6
		rts

**************************************************************************
**         SCAN JOYSTICK INTERFACE AND GENERATE HIT AND HELD INFO        *
**************************************************************************

	XREF	_gemsholdz80	; hold Z80, before accessing joystick
	XREF	_gemsreleasez80	; resume the Z80, after accessing joystick

		XDEF	ScanJoy1
ScanJoy1:
		lea	Data1,a0	;point to hardware
;		Z80Di			;grab Z80
		jsr	_gemsholdz80
		move.b	#$00,(a0)	;TH=0
		nop
		nop			;wait
		move.b	(a0),d0		;get bits 6..7 (in 4..5)
		lsl.w	#2,d0		;move to 6..7
		move.b	#$40,(a0)	;TH=1
		and.w	#$C0,d0		;mask 6..7
		move.b	(a0),d1		;get 0..5
;		Z80Ei			;let Z80 continue
		jsr	_gemsreleasez80
		and.w	#$3f,d1		;mask 0..5
		or.w	d1,d0		;combine (top byte of word=0)

		lea	KeyTab1,a0	;point to button status table
		moveq	#8-1,d1		;8 buttons
sj_key:
		lsr.b	#1,d0		;check bit
		bcs.s	sj_up		;skip if up
		tst.b	(a0)		;test held status
		bne.s	sj_next		;skip if already down
		st	KeyHit		;flag hit occured (global)
		move.w	#$101,(a0)	;flag hit and held
		bra.s	sj_next		;next bit
sj_up:
		clr.b	(a0)		;not held (leave hit status)
sj_next:
		addq.w	#2,a0		;next ststus entry
		dbra	d1,sj_key	;do all bits
		rts

***
**	Second joystick scanner
***

		XDEF	ScanJoy2
ScanJoy2:
		lea	Data2,a0	;point to hardware
;		Z80Di			;grab Z80
		jsr	_gemsholdz80
		move.b	#$00,(a0)	;TH=0
		nop
		nop			;wait
		move.b	(a0),d0		;get bits 6..7 (in 4..5)
		lsl.w	#2,d0		;move to 6..7
		move.b	#$40,(a0)	;TH=1
		and.w	#$C0,d0		;mask 6..7
		move.b	(a0),d1		;get 0..5
;		Z80Ei			;let Z80 continue
		jsr	_gemsreleasez80
		and.w	#$3f,d1		;mask 0..5
		or.w	d1,d0		;combine (top byte of word=0)

		lea	KeyTab2,a0	;point to button status table
		moveq	#8-1,d1		;8 buttons
sj_key2:
		lsr.b	#1,d0		;check bit
		bcs.s	sj_up2		;skip if up
		tst.b	(a0)		;test held status
		bne.s	sj_next2	;skip if already down
		st	KeyHit		;flag hit occured (global)
		move.w	#$101,(a0)	;flag hit and held
		bra.s	sj_next2	;next bit
sj_up2:
		clr.b	(a0)		;not held (leave hit status)
sj_next2:
		addq.w	#2,a0		;next ststus entry
		dbra	d1,sj_key2	;do all bits
		rts

**************************************************************************
**                         CLEAR JOYSTICK HIT INFO                       *
**************************************************************************

		XDEF	ClearKeys
ClearKeys:
		sf	KeyHit		;flag no key hit
		lea	KeyTab1+1,a0	;point at hit entries
		moveq	#8-1,d0		;8 of them
ck_lp:
		sf	(a0)+		;clear hit flag
		addq.w	#1,a0		;index next hit ststus
		dbra	d0,ck_lp	;do all
		rts

**************************************************************************
**                 SYNCHRONIZE TO VERTICAL VIDEO INTERRUPT               *
**************************************************************************
*interrupts must be ON!

		XDEF	WaitFrame,_SYS_WaitFrame
_SYS_WaitFrame:
WaitFrame:
		sf	FlyBackFlag	;clear flag
wf_lp:
		tst.b	FlyBackFlag	;has interrupt set it yet
		beq.s	wf_lp		;wait until it has
		rts

**************************************************************************
**                         CLEAR JOYSTICK HIT INFO                       *
**************************************************************************
*entry:-
*d0 = number of frames to wait (remember: 60/s on NTSC, 50/s on PAL)

		XDEF	WaitFrames
WaitFrames:
		subq.w	#1,d0
wfs_lp:
		bsr	WaitFrame
		dbra	d0,wfs_lp
		rts

**************************************************************************
**                            SET WRITE TO VRAM                          *
**************************************************************************

* C Callable SYS_SetVAddr:
*	SYS_SetVAddr(UWORD video_addr);

		XDEF	_SYS_SetVAddr
_SYS_SetVAddr:
		moveq.l	#0,d0
		move.w	4(sp),d0
		bsr	SetVRAMWrite
		rts


;{----------------------------------------------------------------------}
;{ Function:	SetVRAMWrite						}
;{ Description:	Set the VDP RAM address to write to location in D0	}
;{ Parmeters:	D0 = VRAM Address					}
;{ Returns:	.							}
;{----------------------------------------------------------------------}

		XDEF	SetVRAMWrite
SetVRAMWrite:
		move.l	d0,-(sp)
		or.w	#$4000,d0
		swap	d0
		move.w	2(sp),d0
		rol.w	#2,d0
		and.l	#$7FFF0003,d0
		move.l	d0,VCTRL
		move.l	(sp)+,d0
		rts

		move.w	d7,-(sp)
		move.b	_SYS_VDPAccess,d7
		sf	_SYS_VDPAccess
		move.l	d0,-(sp)
		or.w	#CD0,d0
		swap	d0
		move.w	2(sp),d0
		rol.w	#2,d0
		and.l	#($FFFF-CD1)<<16+%11,d0
		move.l	d0,VDPControl
		move.l	(sp)+,d0
		move.b	d7,_SYS_VDPAccess
		move.w	(sp)+,d7
		rts

**************************************************************************
**                            SET READ FROM VRAM                         *
**************************************************************************
*entry:-
*d0 = VRAM address

		XDEF	SetVRAMRead
SetVRAMRead:
		move.w	d7,-(sp)
		move.b	_SYS_VDPAccess,d7
		sf	_SYS_VDPAccess
		move.l	d0,-(sp)
		swap	d0
		move.w	2(sp),d0
		rol.w	#2,d0
		and.l	#($FFFF-CD1-CD0)<<16+%11,d0
		move.l	d0,VDPControl
		move.l	(sp)+,d0
		move.b	d7,_SYS_VDPAccess
		move.w	(sp)+,d7
		rts

**************************************************************************
**                            SET WRITE TO CRAM                          *
**************************************************************************
*entry:-
*d0 = CRAM address

		XDEF	SetCRAMWrite
SetCRAMWrite:
		move.w	d7,-(sp)
		move.b	_SYS_VDPAccess,d7
		sf	_SYS_VDPAccess
		and.w	#$7F,d0
		or.w	#CD1+CD0,d0
		move.w	d0,VDPControl
		move.w	#0,VDPControl
		and.w	#$7F,d0
		move.b	d7,_SYS_VDPAccess
		move.w	(sp)+,d7
		rts

**************************************************************************
**                            SET READ FROM CRAM                         *
**************************************************************************
*entry:-
*d0 = CRAM address

		XDEF	SetCRAMRead
SetCRAMRead:
		move.w	d7,-(sp)
		move.b	_SYS_VDPAccess,d7
		sf	_SYS_VDPAccess
		and.w	#$7F,d0
		move.w	d0,VDPControl
		move.w	#CD3,VDPControl
		move.b	d7,_SYS_VDPAccess
		move.w	(sp)+,d7
		rts

**************************************************************************
**                            SET WRITE TO VSRAM                         *
**************************************************************************
*entry:-
*d0 = VSRAM address

* C Callable SYS_SetVAddr:
*	SYS_SetVSAddr(UWORD video_addr);

		XDEF	_SYS_SetVSAddr
_SYS_SetVSAddr:
		link	a6,#0
		move.l	8(a6),d0
		bsr	SetVSRAMWrite
		unlk	a6
		rts

		XDEF	SetVSRAMWrite
SetVSRAMWrite:
		move.w	d7,-(sp)
		move.b	_SYS_VDPAccess,d7
		sf	_SYS_VDPAccess
		and.w	#$3f,d0
		or.w	#CD0,d0
		move.w	d0,VDPControl
		move.w	#CD2,VDPControl
		and.w	#$3f,d0
		move.b	d7,_SYS_VDPAccess
		move.w	(sp)+,d7
		rts

**************************************************************************
**                            SET READ FROM VSRAM                        *
**************************************************************************
*entry:-
*d0 = VSRAM address

		XDEF	SetVSRAMRead
SetVSRAMRead:
		move.w	d7,-(sp)
		move.b	_SYS_VDPAccess,d7
		sf	_SYS_VDPAccess
		and.w	#$3f,d0
		move.w	d0,VDPControl
		move.w	#CD2,VDPControl
		move.b	d7,_SYS_VDPAccess
		move.w	(sp)+,d7
		rts

**************************************************************************
**                SET ALL ENTRIES IN PALETTE TO COLOUR 0                 *
**************************************************************************

		XDEF	BlackOut
BlackOut:
		sf	_SYS_VDPAccess
		moveq	#0,d0		;CRAM address 0
		bsr	SetCRAMWrite	;set write to CRAM
		moveq	#64*2/4-1,d1	;long words less 1
bo_lp:
		move.l	d0,VDPData	;clear 2 entries
		dbra	d1,bo_lp	;until all clear
		st	_SYS_VDPAccess
		rts

**************************************************************************
**                        CREATE PALETTE SLAVE BUFFER                    *
**************************************************************************

* C Callable SYS_SetPalette:
*	SYS_SetPalette(UWORD *pal_addr);

		XDEF	_SYS_SetPalette
_SYS_SetPalette:
		link	a6,#0
		movem.l	a1,-(sp)
		move.l	8(a6),a0
		bsr	SetPalette
		bsr	JumpIn
		movem.l	(sp)+,a1
		unlk	a6
		rts

		XDEF	_StorePalette
_StorePalette:
		move.l	4(sp),a0
*entry:-
*a0 = pointer to data structure
*	dc.w	startcolour
*	dc.w	number
*
*	dc.w	colour
*	...
*
*	dc.w	-1 (or repeat structure)

		XDEF	SetPalette
SetPalette:
		bra.s	sp_get		;jump to start
sp_set:
		lea	PalBuffer,a1	;point at slave buffer
		add.w	d0,d0		;2*colour
		add.w	d0,a1		;index correct slave
		move.w	(a0)+,d0	;get count of values
		subq.w	#1,d0		;for dbra
sp_lp:
		move.w	(a0)+,(a1)+	;copy value to slave buffer
		dbra	d0,sp_lp	;do values
sp_get:
		move.w	(a0)+,d0	;get flag/address
		bpl.s	sp_set		;adress if not -ve
		rts			;stop

**************************************************************************
**                     COPY PALETTE SLAVES TO PALETTE                    *
**************************************************************************

		XDEF	JumpIn
JumpIn:
		sf	_SYS_VDPAccess
		AutoIncrement 2
		moveq	#0,d0		;first colour
		bsr	SetCRAMWrite	;set write to colour RAM
		lea	PalBuffer,a0	;point at slaves
		moveq	#64-1,d0	;number of colours (4*16 colour palettes)
ji_lp:
		move.w	(a0)+,VDPData	;move data to CRAM
		dbra	d0,ji_lp	;move all
		st	_SYS_VDPAccess
		rts

;{----------------------------------------------------------------------}
;{ Function:	void FadeIn(UWORD frames);				}
;{ Description:	'C' callable function to fade in stored palette		}
;{ Parameters:	frames = number of frames to take			}
;{ Returns:	.							}
;{----------------------------------------------------------------------}
		XDEF	_FadeIn
_FadeIn:
		move.w	4(sp),d0

;{----------------------------------------------------------------------}
;{ Function:	FadeIn							}
;{ Description:	ASM version of fade in to stored palette		}
;{ Parameters:	d0.w = number of frames to take				}
;{ Returns:	.							}
;{----------------------------------------------------------------------}
		XDEF	FadeIn
FadeIn:
		movem.l	d3-d7,-(sp)
		sf	_SYS_VDPAccess
		lea	PalBuffer,a0	;point to slaves
FadeAnyIn
		move.w	d0,d7		;maximum frame
		moveq	#1,d6		;first frame
		moveq	#1,d5		;direction
	      	bra.s	f_join		;do it

;{----------------------------------------------------------------------}
;{ Function:	void FadeOut(UWORD frames);				}
;{ Description:	'C' callable function to fade out to black		}
;{ Parameters:	frames = number of frames to take			}
;{ Returns:	.							}
;{----------------------------------------------------------------------}
		XDEF	_FadeOut
_FadeOut:
		move.w	4(sp),d0

;{----------------------------------------------------------------------}
;{ Function:	FadeOut							}
;{ Description:	ASM version of fade to black				}
;{ Parameters:	d0.w = number of frames to take				}
;{ Returns:	.							}
;{----------------------------------------------------------------------}
		XDEF	FadeOut
FadeOut:
		movem.l	d3-d7,-(sp)
		sf	_SYS_VDPAccess
		lea	PalBuffer,a0	;point to slaves
		move.w	d0,d7		;maximum frame
		move.w	d0,d6
		subq.w	#1,d6		;first frame
		moveq	#-1,d5		;direction
		moveq	#0,d0		;set address of palettes (in CRAM)
		bsr	SetCRAMRead	;set read of palette
		moveq	#64-1,d0	;words
f_get:
		move.w	VDPData,(a0)+	;read palette
		dbra	d0,f_get	;read all
		lea	-128(a0),a0	;point to buffer
f_join:
		move.w	d7,d4
		subq.w	#1,d4		;frames to do (adjusted for dbra)
f_fade:
		bsr	WaitFrame	;synchronize to video
		moveq	#0,d0		;address to write (in CRAM)
		bsr	SetCRAMWrite	;set write palette
		moveq	#64-1,d1	;every colour
f_set:
		move.b	(a0)+,d0	;1st byte of data
		bsr	f_nib		;do nybble
		move.b	d0,-(sp)
		move.w	(sp)+,d0	;byte swap
		move.b	(a0)+,d0	;2nd byte of data
		ror.b	#4,d0		;top nibble
		bsr	f_nib		;do nybble
		ror.b	#4,d0		;bottom nibble
		bsr	f_nib		;do nybble
		move.w	d0,VDPData	;set colour
		dbra	d1,f_set	;do all colours
		lea	-128(a0),a0	;point to buffer again
		add.w	d5,d6		;next frame
		dbra	d4,f_fade	;fade
		st	_SYS_VDPAccess
		movem.l	(sp)+,d3-d7
		rts
f_nib:
		move.w	d0,d3
		and.w	#$f,d0		;get nibble
		eor.w	d0,d3		;clear nibble
		mulu	d6,d0
		divu	d7,d0		;scale for current frame
		and.w	#$e,d0		;discard bottom bit
		or.w	d3,d0		;include other nibbles
		rts

**************************************************************************
**                       WAIT FOR DMA TO FINISH                          *
**************************************************************************
*only required when moving from ROM or work RAM

		XDEF	WaitForDMA
WaitForDMA
		move.w	VDPStatus,d0	;get status
		and.w	#DMA,d0		;DMA finished?
		bne.s	WaitForDMA	;loop if not
		rts

**************************************************************************
**                      CLEAR VRAM WITH DMA                              *
**************************************************************************

		XDEF	ClearVRAM,_ClearVRAM
_ClearVRAM:
ClearVRAM:
		sf	_SYS_VDPAccess
;
; ----- Initialize the VDP Video RAM
;
		clr.l	d0
		bsr	SetVRAMWrite
		move.w	#65536/4-1,d1
		moveq	#0,d0
.cloop		move.l	d0,VDATA
		dbra	d1,.cloop

		st	_SYS_VDPAccess
		rts
 
**************************************************************************
**                 CLEAR VERTICAL SCROLL RAM                             *
**************************************************************************

		XDEF	ClearVSRAM,_ClearVSRAM
_ClearVSRAM:
ClearVSRAM:
		sf	_SYS_VDPAccess
		moveq	#0,d0		;start address
		bsr	SetVSRAMWrite	;set VSRAM write
		moveq	#80/4-1,d1	;long words
		lea	VDPData,a0	;point to VDP data port
cv_lp:
		move.l	d0,(a0)		;clear scrolls
		dbra	d1,cv_lp	;clear all
		st	_SYS_VDPAccess
		rts
	
**************************************************************************
**                 CLEAR HORIZONTAL SCROLL RAM                           *
**************************************************************************

		XDEF	ClearHSRAM
ClearHSRAM:
		sf	_SYS_VDPAccess
		move.w	#HScroll,d0	;address of scroll table (in VRAM)
		bsr	SetVRAMWrite	;set write to VRAM
		moveq	#0,d0		;clear d0
		move.w	#1024/4-1,d1	;long words
		lea	VDPData,a0	;point to VDP data port
ch_lp:		move.l	d0,(a0)		;clear scrolls
		dbra	d1,ch_lp	;clear all
		st	_SYS_VDPAccess
		rts

**************************************************************************
**      COPY DATA FROM WORK RAM OR ROM TO VRAM USING DMA                 *
**************************************************************************

* C Callable DMA:
*	SYS_DMA(ULONG video_addr,ULONG length,ULONG *src_addr)

		XDEF	_SYS_DMA
_SYS_DMA:
		link	a6,#0
		movem.l	d1/a0,-(sp)
		move.l	8(a6),d0
		move.l	12(a6),d1
		move.l	16(a6),a0
		bsr	CopyToVRAM
		moveq	#0,d0
		movem.l	(sp)+,d1/a0
		unlk	a6
		rts

*entry:-
*d0 = VRAM address
*d1 = length of data (bytes)
*a0 = pointer to data
         
	XREF	_gemsdmastart	; tell the z80 we want to do dma
	XREF	_gemsdmaend	; tell the z80 we're done with dma

		XDEF	CopyToVRAM
CopyToVRAM:
		movem.l	d0-d2,-(sp)
		sf	_SYS_VDPAccess
		move.w	sr,-(sp)	;save status
		DI			;disable interrupts
;		Z80Di			;grab Z80
;		st	Z80NoROM	;flag ROM accesses NOT permitted
;		Z80Ei			;allow Z80 to continue
		jsr	_gemsdmastart
		move.w	(sp)+,sr	;reset old interrupt status
*d0 = VRAM address
*d1 = length of data (bytes)
*a0 = pointer to data

.wait		move.w	VCTRL,d2	; Get status
		and.w	#2,d2		; DMA finished?
		bne.s	.wait		; Loop if not
         
		move	#$8F02,VCTRL
		move	#$8174,VCTRL
		lsr.w	#1,d1		; convert length to words
		move.w	d1,-(sp)
		move	#$9300,d2
		move.b	d1,d2
		move	d2,VCTRL
		add	#$0100,d2
		move.b	(sp)+,d2
		move	d2,VCTRL
		move.l	a0,d1		;get address
		lsr.l	#1,d1		;convert to word address
		add	#$0100,d2	; Set DMA Address
		move.b	d1,d2
		move	d2,VCTRL
		move.w	d1,-(sp)
		move.b	(sp)+,d2
		add	#$0100,d2
		move	d2,VCTRL
		swap	d1
		and.b	#$7F,d1
		add	#$0100,d2
		move.b	d1,d2
		move	d2,VCTRL
* Set VRAM Address
		move	d0,d2
		lea	VCTRL,a0
		and.w	#$7FFF,d0	;clear CD1
		or.w	#$4000,d0	;set CD0
		move.w	d0,(a0)		;set first word of address
		move	d2,d0
		rol.w	#2,d0		;move bits 14/15 to bits 0/1
		and.w	#%11,d0		;mask them (clear CD2 and other bits)
		or.w	#$80,d0		;set bit 7
		move.w	d0,DMATemp	; Last DMA access must be from RAM
		move.w	DMATemp,(a0)
		move	#$8164,VCTRL
		move.w	sr,-(sp)	;save status
		DI			;disable interrupts
;		Z80Di			;grab Z80
;		sf	Z80NoROM	;flag ROM accesses permitted
;		Z80Ei			;allow Z80 to continue
		jsr	_gemsdmaend
		move.w	(sp)+,sr	;reset old interrupt status
		movem.l	(sp)+,d0-d2
		st	_SYS_VDPAccess
		rts

;{----------------------------------------------------------------------}
;{ Function:	void CopyToVRAM2(UWORD vdpAddr, UWORD length, 		}
;{				ULONG dptr);				}
;{ Description:	'C' callable function to copy directly to the VDP	}
;{		without using DMA					}
;{ Parameters:	vdpaddr = address in vdp to download to			}
;{		length = length to copy to vdp				}
;{		dptr = source pointer for data				}
;{ Returns:	.							}
;{----------------------------------------------------------------------}
		XDEF	_CopyToVRAM2
_CopyToVRAM2:
		link	a6,#0
		move.w	8(a6),d0
		move.w	10(a6),d1
		move.l	12(a6),a0
		bsr	CopyToVRAM2
		unlk	a6
		rts

**************************************************************************
**      COPY DATA FROM WORK RAM OR ROM TO VRAM WITHOUT DMA               *
**************************************************************************
*entry:-
*d0 = VRAM address
*d1 = length of data (bytes) assumed even
*a0 = pointer to data

		XDEF	CopyToVRAM2
CopyToVRAM2
		sf	_SYS_VDPAccess
		bsr	SetVRAMWrite	;set VRAM address for write
		lsr.w	#1,d1		;words
		subq.w	#1,d1		;adjust for dbra
ctv_load:
		move.w	(a0)+,VDPData	;load word
		dbra	d1,ctv_load	;until done
		st	_SYS_VDPAccess
		rts

**************************************************************************
**     SET UP A VERTICAL GRID OF CONTIGUOUS CELLS IN A CELL MAP          *
**************************************************************************
*entry:-
*d0 = start x (cells)
*d1 = start y (cells)
*d2 = width (cells)
*d3 = height (cells)
*d4 = first cell nuber and cell attribute
*d5 = address of cell map

		XDEF	VerticalGrid
VerticalGrid:
		sf	_SYS_VDPAccess
		add.w	d0,d0		;scale x position to words
		move.w	CellMapCols,d7	;get cell map width
		add.w	d7,d7		;convert to bytes
		mulu	d7,d1		;scale y position to lines
		add.w	d1,d0		;add line to x offset
		add.w	d5,d0		;create cell map address of top left cell
		move.w	d4,d1		;copy first cell number
		move.w	d3,d6		;copy height
		subq.w	#1,d6		;adjust height for dbra
		subq.w	#1,d2		;adjust width for dbra
vg_rows:
		move.w	d2,d5		;get width count
		bsr	SetVRAMWrite	;set up left most address (cannot use a macro here!)
		add.w	d7,d0		;update address for next line down cell map
vg_cols:
		move.w	d1,VDPData	;set cell map
		add.w	d3,d1		;next horizontal character number
		dbra	d5,vg_cols	;do a row
		addq.w	#1,d4		;make next sequential character below left most character
		move.w	d4,d1		;get it
		dbra	d6,vg_rows	;do all rows
		st	_SYS_VDPAccess
		rts			;simple really!	

**************************************************************************
**                   COPY A GRID OF CELLS TO A CELL MAP                  *
**************************************************************************
*entry:-
*d0 = start x (cells)
*d1 = start y (cells)
*d2 = width (cells)
*d3 = height (cells)
*d4 = address of cell map

		XDEF	LoadCellMap
LoadCellMap:
		sf	_SYS_VDPAccess
		add.w	d0,d0		;scale x position to words
		move.w	CellMapCols,d7	;get cell map width
		add.w	d7,d7		;convert to bytes
		mulu	d7,d1		;scale y position to lines
		add.w	d1,d0		;add line to x offset
		add.w	d4,d0		;create cell map address of top left cell
		subq.w	#1,d2		;adjust width for dbra
		subq.w	#1,d3		;adjust height for dbra
		lea	VDPData,a1	;point to VDP data port
lc_rows:
		move.w	d2,d5		;get width
		bsr	SetVRAMWrite	;set address
		add.w	d7,d0		;get next line address
lc_cols:
		move.w	(a0)+,(a1)	;put data in cell map
		dbra	d5,lc_cols	;do row
		dbra	d3,lc_rows	;do all rows
		st	_SYS_VDPAccess
		rts

**************************************************************************
**                           LOAD A CHARACTER SET INTO VRAM              *
**************************************************************************
*entry:-
*d0 = first cell number
*d1 = number of characters
*d2 = foreground colour
*d3 = background colour
*a0 = pointer to sets of 8 bytes of 2 colour character data

		XDEF	LoadChars
LoadChars:
		sf	_SYS_VDPAccess
		lsl.w	#5,d0		;make VRAM address
		bsr	SetVRAMWrite	;set write to VRAM
		lsl.w	#3,d1		;bytes to expand
		subq.w	#1,d1		;adjust for dbra
		lea	VDPData,a1	;point at data port
		and.w	#$f,d2
		and.w	#$f,d3		;force colours into range
		mulu	#%1000100010001,d2
		mulu	#%1000100010001,d3 ;duplicate nybble into all 4 nybbles
lc_bytes:
		move.b	(a0),d0		;get byte
		and.w	#$f0,d0		;mask top nybble
		lsr.w	#3,d0		;make index
		bsr	lc_donybble	;expand nybble
		move.b	(a0)+,d0	;reget byte (and move data ptr)
		and.w	#$0f,d0		;mask bottom nybble
		add.w	d0,d0		;make mask
		bsr	lc_donybble	;expand nybble
		dbra	d1,lc_bytes	;expand all
		rts
lc_donybble:
		move.w	lc_nybble4(pc,d0.w),d4 ;expand a nybble
		move.w	d4,d0		;duplicate
		not.w	d0		;make background mask
		and.w	d2,d4		;put in colour
		and.w	d3,d0		;put in other colour
		or.w	d4,d0		;combine
		move.w	d0,(a1)		;write expanded word to VRAM
		st	_SYS_VDPAccess
		rts
lc_nybble4:
		dc.w	$0000,$000F,$00F0,$00FF
		dc.w	$0F00,$0F0F,$0FF0,$0FFF
		dc.w	$F000,$F00F,$F0F0,$F0FF
		dc.w	$FF00,$FF0F,$FFF0,$FFFF
	

**************************************************************************
**                      SET CELL MAP (OR CLEAR TO 0)                     *
**************************************************************************
*entry:-
*d0 = address in VRAM
*d1 = value (only used in SetCellMap)
	
		XDEF	ClearCellMap,_ClearCellMap
_ClearCellMap:
		move.l	4(sp),d0
	ClearCellMap:
		sf	_SYS_VDPAccess
		moveq	#0,d1		;set value to 0
		bsr	SetVRAMWrite	;set address
		move.w	CellMapCols,d0	;get width
		mulu	CellMapRows,d0	;number of words in cell map
		subq.w	#1,d0		;dbra
		lea	VDPData,a0	;point to VDP data port
scm_clr:
		move.w	d1,(a0)		;set cells
		dbra	d0,scm_clr	;set all
		st	_SYS_VDPAccess
		rts
	
**************************************************************************
**                    SET A BLOCK OF CELLS TO A VALUE                    *
**************************************************************************
*entry:-
*d0 = start x (cells)
*d1 = start y (cells)
*d2 = width (cells)
*d3 = height (cells)
*d4 = first cell nuber and cell attribute
*d5 = address of cell map

		XDEF	SetCellBlock
SetCellBlock:
		sf	_SYS_VDPAccess
		add.w	d0,d0		;scale x position to words
		move.w	CellMapCols,d7	;get cell map width
		add.w	d7,d7		;convert to bytes
		mulu	d7,d1		;scale y position to lines
		add.w	d1,d0		;add line to x offset
		add.w	d5,d0		;create cell map address of top left cell
		subq.w	#1,d2		;dbra
		subq.w	#1,d3		;dbra
scb_next:
		bsr	SetVRAMWrite	;set write
		move.w	d2,d1		;width count
scb_set:
		move.w	d4,VDPData	;write cell and attribute
		dbra	d1,scb_set	;do line
		add.w	d7,d0		;down a line
		dbra	d3,scb_next	;do all lines
		st	_SYS_VDPAccess
		rts

**************************************************************************
**                 LOAD THE Z80 WITH A PROGRAM AND EXECUTE IT            *
**************************************************************************
*entry:-
*d0 = length of program (bytes)
*a0 = pointer to valid Z80 program (execution adress 0)

		XDEF	LoadZ80	
LoadZ80:
		move.w	sr,-(sp)	;save interrupt status
		DI			;disable intterupts
		Z80di			;grab Z80
	
		lea	Z80Base,a1	;point at Z80 memory
si_lp0:
		move.b	(a0)+,(a1)+	;only possible to byte access
		dbra	d0,si_lp0	;load Z80 program
	
		Z80eiGO			;start Z80 and reset it (execute from address 0)
		move.w	(sp)+,sr	;reset old interrupt status
		rts


		end
