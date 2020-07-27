;{----------------------------------------------------------------------}
;{ Module:	VM_UPDATE.ASM						}
;{ Description:	Update routines for the virtual machine interface	}
;{ Part of:	TOONS.BIN						}
;{ Original:	Kevin L. McGrath					}
;{ Started:	02/21/94						}
;{----------------------------------------------------------------------}
;{		*** Copyright 1994 Futurescape Productions ***		}
;{----------------------------------------------------------------------}

;
; $Log: vm_updat.asm_v $
; Revision 1.1  1994/06/15  23:28:29  KENH
; Initial revision
;
;

		include equates.inc
		include	vm_defs.inc

		XDEF	gr_cols_touched
		XDEF	gr_ct_ptr

		bsection	.bss
		ds.w	0
DMATemp		ds.w	1

gr_cols_touched	ds.b	40	; Column touched flags
		ds.w	0
gr_ct_ptr	ds.l	1	; Temporary pointer

		tsection	.text

		XDEF	_vm_update

;{----------------------------------------------------------------------}
;{ Function:	void vm_update(void);					}
;{ Description:	DMA a section of the CPU screen to the VDP		}
;{ Parmeters:	.							}
;{ Returns:	.							}
;{----------------------------------------------------------------------}

		XREF	_ScrBAddr
		XREF	SetVRAMWrite

_vm_update:
		movem.l	d0-d3/a0-a2,-(sp)
		move.w	sr,-(sp)
		move.w  #$2700,sr	; Disable ints


***
*		Debugging information:
***

		move	_ScrBAddr,d0
		bsr	SetVRAMWrite
		lea	gr_cols_touched,a2
		move.w	_vm_schar,d0
		moveq	#40-1,d1
.loopd		tst.b	(a2)+
		beq.s	.no_upd
		move	#1,VDATA
		bra.s	.again
.no_upd		move	d0,VDATA
.again		add	#25,d0
		dbra	d1,.loopd

***
*		End of debugging information.
***

		move.w	#40-1,d3	; Do up to 40 columns
		lea	gr_cols_touched,a2
		move.l	_vm_scrnptr,a0
		move.w	_vm_schar,d0
		lsl	#5,d0
		bra.s	.start

.dma		bsr	.do_dma
		add	d1,a0		; Done with this block, do next
		add	d1,d0
.start		clr.w	d1		; Start with no bytes to DMA

.loop		tst.b	(a2)+		; DMA this column?
		beq.s	.skip_col
		add	#800,d1		; Add 800 bytes to DMA
		dbra	d3,.loop
		bsr	.do_dma
		bra	.exit
.skip_col	tst.w	d1
		bne.s	.dma
		adda.w	#800,a0		; Bump to next column
		add.w	#800,d0
		dbra	d3,.loop	; Done yet?

.exit		move.w	#40-1,d3	; Clear the flags for all the columns
		lea	gr_cols_touched,a2
.cloop		clr.b	(a2)+
		dbra	d3,.cloop

		move.w	(sp)+,sr
		movem.l	(sp)+,d0-d3/a0-a2
		rts

*d0 = VRAM address
*d1 = length of data (bytes)
*a0 = pointer to data

.do_dma		movem.l	d0-d1/a0,-(sp)
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
		movem.l	(sp)+,d0-d1/a0
		rts

		end
		



