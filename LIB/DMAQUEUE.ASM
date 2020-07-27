; $Header: h:\toons\rcs\DMAQUEUE.ASM_v 1.1 1994/02/19 22:48:27 KENH Exp $
;{----------------------------------------------------------------------}
;{ Module:	DMAQUEUE.ASM						}
;{ Description:	Does DMA in a Queue like fashion			}
;{ Part of:	segalib.lib						}
;{ Original:	Kenneth L. Hurley					}
;{ Date:	10/23/93						}
;{----------------------------------------------------------------------}
;{		*** Copyright 1993 Futurescape Productions ***		}
;{----------------------------------------------------------------------}


;
; $Log: DMAQUEUE.ASM_v $
; Revision 1.1  1994/02/19  22:48:27  KENH
; .
;
;

		include	equates.inc
		include	macros.inc
		include	variable.inc
		include segalib.inc
		include	format.inc

Z80NoROM	equ	Z80Base+4	;flag for disabling Z80 ROM accesses
;
; ----- Dma queue equates
;
MAXDMAQUEUE	equ	100			; 100 per frame
MAXDMAXFERAFRAME equ	7*1024			; 7k per frame
		BSECTION	.bss

dmaStart	ds.w	1
dmaEnd		ds.w	1
dmaCurrent	ds.w	1

dmaQueue	ds.b	(SIZEDMASTRUCT*MAXDMAQUEUE)

		TSECTION	.text

;{----------------------------------------------------------------------}
;{ Function:	void addDMAQueue(UWORD vdpaddr, ULONG length, 		}
;{				void *src);				}
;{ Description:	'C' callable function to add to DMA queue		}
;{ Parameters:	vdpaddr = address inside of vdp to download to		}
;{		length = lenght of transfer				}
;{		src = source pointer					}
;{ Returns:	.							}
;{----------------------------------------------------------------------}
		XDEF	_addDMAQueue
_addDMAQueue:
		link	a6,#0
		move.w	8(a6),d0		; vdp address
		move.l	10(a6),d1		; length to download
		move.l	14(a6),a0		; and pointer to data
		bsr	addDMAQueue
		unlk	a6
		rts

;{----------------------------------------------------------------------}
;{ Function:	addDMAQueue						}
;{ Description:	Add to the DMA queue					}
;{ Parameters:	d0 = VRAM address					}
;{		d1 = length of data (bytes)				}
;{		a0 = pointer to data					}
;{ returns:	.							}
;{----------------------------------------------------------------------}
		XDEF	addDMAQueue
addDMAQueue:
		movem.l	d2/a1,-(sp)
		move.w	dmaEnd,d2
		cmp.w	dmaCurrent,d2
		bne.s	.notEmpty		; wait till finished
		move.w	dmaStart,d2
		move.w	d2,dmaEnd
		move.w	d2,dmaCurrent
.notEmpty:
		cmp.w	#MAXDMAQUEUE-1,d2
		bge	.ADQExit
		lsl.w	#3,d2			; times size of dma queue
		lea	dmaQueue,a1
		adda.w	d2,a1
		move.w	d0,VRAMADDRESS(a1)	; save parameters in queue
		move.w	d1,VRAMLENGTH(a1)
		move.l	a0,SRCADDR(a1)
		add.w	#1,dmaEnd
.ADQExit:
		movem.l	(sp)+,d2/a1
		rts

;{----------------------------------------------------------------------}
;{ Function:	waitDMAQueue						}
;{ Description:	wait for DMA queue to end				}
;{ Parameters:	.							}
;{ returns:	.							}
;{----------------------------------------------------------------------}
		xdef	_waitDMAQueue,waitDMAQueue
_waitDMAQueue:
waitDMAQueue:

		move.w	d1,-(sp)
		move.l	d2,-(sp)
.waitDMA:
		move.w	dmaEnd,d1
		cmp.w	dmaCurrent,d1
		bne.s	.waitDMA		; wait till finished

		move.w	dmaStart,d1
		move.w	d1,dmaEnd
		move.w	d1,dmaCurrent

.WaitDMA2:
		move.w	VDPStatus,d0		;get status
		and.w	#DMA,d0			;DMA finished?
		bne.s	.WaitDMA2		;loop if not

		move.l	(sp)+,d2
		move.w	(sp)+,d1
		rts

;{----------------------------------------------------------------------}
;{ Function:	updateDMA						}
;{ Description:	Send as much of DMA as possible. This will split blocks	}
;{		longer than 6k into multiple blocks.  If a new block	}
;{		is started, we check to make sure it can either be sent	}
;{		entirly this frame or we wait until next frame to start	}
;{		the transfer.  This should cause less tearing.		}
;{ Parameters:	.							}
;{ returns:	.							}
;{----------------------------------------------------------------------}
		XDEF	updateDMA
updateDMA:
		movem.l	d0-d4/a0-a1,-(sp)

		move.w	#MAXDMAXFERAFRAME,d3
.DMAQueueLoop:
		lea	dmaQueue,a1
		move.w	dmaCurrent,d2
		cmp.w	dmaEnd,d2
		beq	.allDone

		lsl.w	#3,d2
		adda.w	d2,a1			; get to queue address
		clr.l	d1
		move.w	VRAMADDRESS(a1),d0	; save parameters in queue
		move.w	VRAMLENGTH(a1),d1
		move.l	SRCADDR(a1),a0
		cmp.w	d3,d1			; more than max dma in vblank
		blo.s	.DMASizeOk
		move.w	d3,d1
.DMASizeOk:
		cmp.w	VRAMLENGTH(a1),d1	; can do entire block?
		beq.s	.doDMA
		cmp.w	#MAXDMAXFERAFRAME,d3	; first pass of block?
		bne	.allDone		; nope try next vblank
.doDMA:
		move.l	a0,d4			; into temp register
		add.l	d1,d4			; get ending address
		swap	d4
		move.l	a0,d2
		swap	d2
		cmp.w	d2,d4			; still in same 64k block
		beq.s	.Block64Ok		; yes
		move.l	a0,d1			; get starting address
		and.l	#$ffff,d1		; and do up till this 64k block
		neg.w	d1			; number of bytes left in 64k
.Block64Ok:
		add.l	d1,SRCADDR(a1)		; add to source address
		add.w	d1,VRAMADDRESS(a1)	; and vram address
		sub.w	d1,VRAMLENGTH(a1)	; subtract can do entire block?
		bne.s	.BlockNotDone
		add.w	#1,dmaCurrent
.BlockNotDone:
		cmp.w	#20,d1			; should just shove over
		blo.s	.writeDirect
		bsr	CopyToVRAM
		sub.w	d1,d3			; subtract what we sent
		bgt.s	.DMAQueueLoop		; see if more to do
		bra.s	.allDone
.writeDirect:
		bsr	CopyToVRAM2
.allDone:
		movem.l	(sp)+,d0-d4/a0-a1
		rts


		end
