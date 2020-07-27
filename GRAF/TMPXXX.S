	.opt	proc=68000
	.file	"tn_panel.c68"
	.def	BYTE\	.scl	13\	.type	0x2\	.endef
	.def	UBYTE\	.scl	13\	.type	0xc\	.endef
	.def	WORD\	.scl	13\	.type	0x3\	.endef
	.def	UWORD\	.scl	13\	.type	0xd\	.endef
	.def	LONG\	.scl	13\	.type	0x5\	.endef
	.def	ULONG\	.scl	13\	.type	0xf\	.endef
	.def	_panelChars\	.val	_panelChars\	.scl	2\	.type	0xd\	.endef
	.comm	_panelChars,2,2
	.text
	.align	2
	.globl	_wait
	.def	_wait\	.val	_wait\	.scl	2\	.type	0x10020\	.endef
_wait:
	.ln 	1
	.def	.bf\	.val	.\	.scl	101\	.line	61\	.endef
	.def	count\	.val	8\	.scl	9\	.type	0x3\	.endef
	.def	.ef\	.val	.\	.scl	101\	.line	70\	.endef
	.ln 	10
	rts	
	.def	_wait\	.val	.\	.scl	-1\	.endef
	.align	2
	.globl	_grey_out
	.def	_grey_out\	.val	_grey_out\	.scl	2\	.type	0x10020\	.endef
_grey_out:
	.ln 	1
	.def	.bf\	.val	.\	.scl	101\	.line	83\	.endef
	.def	color\	.val	9\	.scl	9\	.type	0x2\	.endef
	.def	x\	.val	10\	.scl	9\	.type	0x3\	.endef
	.def	y\	.val	12\	.scl	9\	.type	0x3\	.endef
	.def	w\	.val	14\	.scl	9\	.type	0x3\	.endef
	.def	h\	.val	16\	.scl	9\	.type	0x3\	.endef
	.def	.ef\	.val	.\	.scl	101\	.line	92\	.endef
	.ln 	10
	rts	
	.def	_grey_out\	.val	.\	.scl	-1\	.endef
	.align	2
	.globl	_draw_toon_edit_panel
	.def	_draw_toon_edit_panel\	.val	_draw_toon_edit_panel\	.scl	2\	.type	0x10020\	.endef
_draw_toon_edit_panel:
	movem.l	d3/a2,-(sp)
	subq.l	#8,sp
	.ln 	1
	.def	.bf\	.val	.\	.scl	101\	.line	106\	.endef
	.def	x\	.val	8\	.scl	9\	.type	0x3\	.endef
	.def	y\	.val	10\	.scl	9\	.type	0x3\	.endef
	.ln 	6
	move.l	#_panel,(sp)
	jsr 	_DLFPCChars
	ori.w	#-32768,d0
	move.w	d0,_panelChars
	.ln 	7
	move.l	#_panel,(sp)
	jsr 	_FPCSetPal
	.ln 	9
	lea 	_MapABuff,a2
	.ln 	10
	move.w	22(sp),d0
	bpl.s	L72
	addq.w	#7,d0
L72:
	asr.w	#3,d0
	ext.l	d0
	move.w	20(sp),d2
	bpl.s	L74
	addq.w	#7,d2
L74:
	asr.w	#3,d2
	ext.l	d2
	lsl.l	#6,d0
	add.l	d2,d0
	add.l	d0,d0
	adda.l	d0,a2
	.ln 	14
	move.w	_panelChars,d0
	addq.w	#1,d0
	move.w	d0,(a2)+
	.ln 	16
	moveq	#0,d3
L12:
	movea.w	#33,a0
L76:
	.ln 	17
	move.w	_panelChars,d0
	addq.w	#2,d0
	move.w	d0,(a2)+
	addq.w	#1,d3
	cmp.w	a0,d3
	blt 	L76
	.ln 	20
	move.w	_panelChars,d0
	addq.w	#3,d0
	move.w	d0,(a2)+
	.ln 	21
	move.w	_panelChars,d0
	addq.w	#4,d0
	move.w	d0,(a2)+
	.ln 	22
	move.w	_panelChars,d0
	addq.w	#5,d0
	move.w	d0,(a2)+
	.ln 	24
	lea 	54(a2),a2
	.ln 	27
	move.w	_panelChars,d0
	addq.w	#6,d0
	move.w	d0,(a2)+
	.ln 	28
	moveq	#0,d3
L26:
	movea.w	#35,a0
L78:
	.ln 	29
	move.w	_panelChars,d0
	addq.w	#7,d0
	move.w	d0,(a2)+
	addq.w	#1,d3
	cmp.w	a0,d3
	blt 	L78
	.ln 	30
	move.w	_panelChars,d0
	addq.w	#8,d0
	move.w	d0,(a2)+
	.ln 	31
	lea 	54(a2),a2
	.ln 	33
	move.w	_panelChars,d0
	addq.w	#6,d0
	move.w	d0,(a2)+
	.ln 	34
	moveq	#0,d3
L40:
	movea.w	#35,a0
L80:
	.ln 	35
	move.w	_panelChars,d0
	addq.w	#7,d0
	move.w	d0,(a2)+
	addq.w	#1,d3
	cmp.w	a0,d3
	blt 	L80
	.ln 	36
	move.w	_panelChars,d0
	addi.w	#9,d0
	move.w	d0,(a2)+
	.ln 	37
	lea 	54(a2),a2
	.ln 	41
	move.w	_panelChars,d0
	addi.w	#10,d0
	move.w	d0,(a2)+
	.ln 	42
	moveq	#0,d3
L54:
	movea.w	#35,a0
L82:
	.ln 	43
	move.w	_panelChars,d0
	addq.w	#7,d0
	move.w	d0,(a2)+
	addq.w	#1,d3
	cmp.w	a0,d3
	blt 	L82
	.ln 	44
	move.w	_panelChars,d0
	addi.w	#11,d0
	move.w	d0,(a2)+
	.ln 	45
	lea 	54(a2),a2
	.ln 	47
	move.w	_panelChars,d0
	addi.w	#12,d0
	move.w	d0,(a2)+
	.ln 	48
	moveq	#0,d3
L68:
	movea.w	#34,a1
	movea.w	#13,a0
L84:
	.ln 	49
	move.w	_panelChars,d0
	add.w	a0,d0
	move.w	d0,(a2)+
	addq.w	#1,d3
	cmp.w	a1,d3
	blt 	L84
	.ln 	51
	move.w	_panelChars,d0
	addi.w	#14,d0
	move.w	d0,(a2)+
	.ln 	52
	move.w	_panelChars,d0
	addi.w	#15,d0
	move.w	d0,(a2)+
	.ln 	55
	move.l	#_MapABuff,(sp)
	pea 	3584
	moveq	#0,d0
	move.w	_ScrAAddr,d0
	move.l	d0,-(sp)
	jsr 	_SYS_DMA
	lea 	16(sp),sp
	.def	.ef\	.val	.\	.scl	101\	.line	162\	.endef
	.ln 	57
	movem.l	(sp)+,d3/a2
	rts	
	.def	_draw_toon_edit_panel\	.val	.\	.scl	-1\	.endef
	.align	2
	.def	_erase_edit_panel\	.val	_erase_edit_panel\	.scl	3\	.type	0x10020\	.endef
_erase_edit_panel:
	.ln 	1
	.def	.bf\	.val	.\	.scl	101\	.line	173\	.endef
	.def	x\	.val	8\	.scl	9\	.type	0x3\	.endef
	.def	y\	.val	10\	.scl	9\	.type	0x3\	.endef
	.def	.ef\	.val	.\	.scl	101\	.line	181\	.endef
	.ln 	9
	rts	
	.def	_erase_edit_panel\	.val	.\	.scl	-1\	.endef
	.align	2
	.globl	_draw_toon_edit_buttons
	.def	_draw_toon_edit_buttons\	.val	_draw_toon_edit_buttons\	.scl	2\	.type	0x10020\	.endef
_draw_toon_edit_buttons:
	.ln 	1
	.def	.bf\	.val	.\	.scl	101\	.line	192\	.endef
	.def	x\	.val	8\	.scl	9\	.type	0x3\	.endef
	.def	y\	.val	10\	.scl	9\	.type	0x3\	.endef
	.def	.ef\	.val	.\	.scl	101\	.line	204\	.endef
	.ln 	13
	rts	
	.def	_draw_toon_edit_buttons\	.val	.\	.scl	-1\	.endef
	.align	2
	.globl	_draw_toon_control_panel
	.def	_draw_toon_control_panel\	.val	_draw_toon_control_panel\	.scl	2\	.type	0x10020\	.endef
_draw_toon_control_panel:
	.ln 	1
	.def	.bf\	.val	.\	.scl	101\	.line	217\	.endef
	.def	x\	.val	8\	.scl	9\	.type	0x3\	.endef
	.def	y\	.val	10\	.scl	9\	.type	0x3\	.endef
	.def	.ef\	.val	.\	.scl	101\	.line	218\	.endef
	.ln 	2
	rts	
	.def	_draw_toon_control_panel\	.val	.\	.scl	-1\	.endef
	.align	2
	.globl	_draw_toon_control_buttons
	.def	_draw_toon_control_buttons\	.val	_draw_toon_control_buttons\	.scl	2\	.type	0x10020\	.endef
_draw_toon_control_buttons:
	.ln 	1
	.def	.bf\	.val	.\	.scl	101\	.line	231\	.endef
	.def	x\	.val	8\	.scl	9\	.type	0x3\	.endef
	.def	y\	.val	10\	.scl	9\	.type	0x3\	.endef
	.def	.ef\	.val	.\	.scl	101\	.line	273\	.endef
	.ln 	43
	rts	
	.def	_draw_toon_control_buttons\	.val	.\	.scl	-1\	.endef
	.align	2
	.def	_erase_control_panel\	.val	_erase_control_panel\	.scl	3\	.type	0x10020\	.endef
_erase_control_panel:
	.ln 	1
	.def	.bf\	.val	.\	.scl	101\	.line	286\	.endef
	.def	x\	.val	8\	.scl	9\	.type	0x3\	.endef
	.def	y\	.val	10\	.scl	9\	.type	0x3\	.endef
	.def	.ef\	.val	.\	.scl	101\	.line	298\	.endef
	.ln 	13
	rts	
	.def	_erase_control_panel\	.val	.\	.scl	-1\	.endef
	.align	2
	.globl	_draw_toon_go
	.def	_draw_toon_go\	.val	_draw_toon_go\	.scl	2\	.type	0x10020\	.endef
_draw_toon_go:
	.ln 	1
	.def	.bf\	.val	.\	.scl	101\	.line	317\	.endef
	.def	button\	.val	9\	.scl	9\	.type	0x2\	.endef
	.def	x\	.val	10\	.scl	9\	.type	0x3\	.endef
	.def	y\	.val	12\	.scl	9\	.type	0x3\	.endef
	.def	.ef\	.val	.\	.scl	101\	.line	349\	.endef
	.ln 	33
	rts	
	.def	_draw_toon_go\	.val	.\	.scl	-1\	.endef
	.align	2
	.def	_erase_go\	.val	_erase_go\	.scl	3\	.type	0x10020\	.endef
_erase_go:
	.ln 	1
	.def	.bf\	.val	.\	.scl	101\	.line	363\	.endef
	.def	x\	.val	8\	.scl	9\	.type	0x3\	.endef
	.def	y\	.val	10\	.scl	9\	.type	0x3\	.endef
	.def	.ef\	.val	.\	.scl	101\	.line	376\	.endef
	.ln 	14
	rts	
	.def	_erase_go\	.val	.\	.scl	-1\	.endef
	.align	2
	.globl	_draw_toon_control
	.def	_draw_toon_control\	.val	_draw_toon_control\	.scl	2\	.type	0x10020\	.endef
_draw_toon_control:
	.ln 	1
	.def	.bf\	.val	.\	.scl	101\	.line	396\	.endef
	.def	button\	.val	9\	.scl	9\	.type	0x2\	.endef
	.def	x\	.val	10\	.scl	9\	.type	0x3\	.endef
	.def	y\	.val	12\	.scl	9\	.type	0x3\	.endef
	.def	.ef\	.val	.\	.scl	101\	.line	432\	.endef
	.ln 	37
	rts	
	.def	_draw_toon_control\	.val	.\	.scl	-1\	.endef
	.align	2
	.def	_erase_control\	.val	_erase_control\	.scl	3\	.type	0x10020\	.endef
_erase_control:
	.ln 	1
	.def	.bf\	.val	.\	.scl	101\	.line	446\	.endef
	.def	x\	.val	8\	.scl	9\	.type	0x3\	.endef
	.def	y\	.val	10\	.scl	9\	.type	0x3\	.endef
	.def	.ef\	.val	.\	.scl	101\	.line	463\	.endef
	.ln 	18
	rts	
	.def	_erase_control\	.val	.\	.scl	-1\	.endef
	.align	2
	.globl	_draw_toon_edit_icons
	.def	_draw_toon_edit_icons\	.val	_draw_toon_edit_icons\	.scl	2\	.type	0x10020\	.endef
_draw_toon_edit_icons:
	.ln 	1
	.def	.bf\	.val	.\	.scl	101\	.line	479\	.endef
	.def	x\	.val	8\	.scl	9\	.type	0x3\	.endef
	.def	y\	.val	10\	.scl	9\	.type	0x3\	.endef
	.def	.ef\	.val	.\	.scl	101\	.line	483\	.endef
	.ln 	5
	rts	
	.def	_draw_toon_edit_icons\	.val	.\	.scl	-1\	.endef
	.align	2
	.globl	_draw_toon_left_button
	.def	_draw_toon_left_button\	.val	_draw_toon_left_button\	.scl	2\	.type	0x10020\	.endef
_draw_toon_left_button:
	.ln 	1
	.def	.bf\	.val	.\	.scl	101\	.line	503\	.endef
	.def	button\	.val	9\	.scl	9\	.type	0x2\	.endef
	.def	x\	.val	10\	.scl	9\	.type	0x3\	.endef
	.def	y\	.val	12\	.scl	9\	.type	0x3\	.endef
	.def	.ef\	.val	.\	.scl	101\	.line	538\	.endef
	.ln 	36
	rts	
	.def	_draw_toon_left_button\	.val	.\	.scl	-1\	.endef
	.align	2
	.def	_erase_left\	.val	_erase_left\	.scl	3\	.type	0x10020\	.endef
_erase_left:
	.ln 	1
	.def	.bf\	.val	.\	.scl	101\	.line	552\	.endef
	.def	x\	.val	8\	.scl	9\	.type	0x3\	.endef
	.def	y\	.val	10\	.scl	9\	.type	0x3\	.endef
	.def	.ef\	.val	.\	.scl	101\	.line	563\	.endef
	.ln 	12
	rts	
	.def	_erase_left\	.val	.\	.scl	-1\	.endef
	.align	2
	.globl	_draw_toon_right_button
	.def	_draw_toon_right_button\	.val	_draw_toon_right_button\	.scl	2\	.type	0x10020\	.endef
_draw_toon_right_button:
	.ln 	1
	.def	.bf\	.val	.\	.scl	101\	.line	584\	.endef
	.def	button\	.val	9\	.scl	9\	.type	0x2\	.endef
	.def	x\	.val	10\	.scl	9\	.type	0x3\	.endef
	.def	y\	.val	12\	.scl	9\	.type	0x3\	.endef
	.def	.ef\	.val	.\	.scl	101\	.line	619\	.endef
	.ln 	36
	rts	
	.def	_draw_toon_right_button\	.val	.\	.scl	-1\	.endef
	.align	2
	.def	_erase_right\	.val	_erase_right\	.scl	3\	.type	0x10020\	.endef
_erase_right:
	.ln 	1
	.def	.bf\	.val	.\	.scl	101\	.line	633\	.endef
	.def	x\	.val	8\	.scl	9\	.type	0x3\	.endef
	.def	y\	.val	10\	.scl	9\	.type	0x3\	.endef
	.def	.ef\	.val	.\	.scl	101\	.line	648\	.endef
	.ln 	16
	rts	
	.def	_erase_right\	.val	.\	.scl	-1\	.endef
	.align	2
	.globl	_draw_toon_fairy
	.def	_draw_toon_fairy\	.val	_draw_toon_fairy\	.scl	2\	.type	0x10020\	.endef
_draw_toon_fairy:
	.ln 	1
	.def	.bf\	.val	.\	.scl	101\	.line	666\	.endef
	.def	button\	.val	9\	.scl	9\	.type	0x2\	.endef
	.def	x\	.val	10\	.scl	9\	.type	0x3\	.endef
	.def	y\	.val	12\	.scl	9\	.type	0x3\	.endef
	.def	.ef\	.val	.\	.scl	101\	.line	711\	.endef
	.ln 	46
	rts	
	.def	_draw_toon_fairy\	.val	.\	.scl	-1\	.endef
	.align	2
	.def	_erase_fairy\	.val	_erase_fairy\	.scl	3\	.type	0x10020\	.endef
_erase_fairy:
	.ln 	1
	.def	.bf\	.val	.\	.scl	101\	.line	724\	.endef
	.def	x\	.val	8\	.scl	9\	.type	0x3\	.endef
	.def	y\	.val	10\	.scl	9\	.type	0x3\	.endef
	.def	.ef\	.val	.\	.scl	101\	.line	743\	.endef
	.ln 	20
	rts	
	.def	_erase_fairy\	.val	.\	.scl	-1\	.endef
	.align	2
	.globl	_draw_toon_puzzle
	.def	_draw_toon_puzzle\	.val	_draw_toon_puzzle\	.scl	2\	.type	0x10020\	.endef
_draw_toon_puzzle:
	.ln 	1
	.def	.bf\	.val	.\	.scl	101\	.line	761\	.endef
	.def	button\	.val	9\	.scl	9\	.type	0x2\	.endef
	.def	x\	.val	10\	.scl	9\	.type	0x3\	.endef
	.def	y\	.val	12\	.scl	9\	.type	0x3\	.endef
	.def	.ef\	.val	.\	.scl	101\	.line	833\	.endef
	.ln 	73
	rts	
	.def	_draw_toon_puzzle\	.val	.\	.scl	-1\	.endef
	.align	2
	.def	_erase_puzzle\	.val	_erase_puzzle\	.scl	3\	.type	0x10020\	.endef
_erase_puzzle:
	.ln 	1
	.def	.bf\	.val	.\	.scl	101\	.line	846\	.endef
	.def	x\	.val	8\	.scl	9\	.type	0x3\	.endef
	.def	y\	.val	10\	.scl	9\	.type	0x3\	.endef
	.def	.ef\	.val	.\	.scl	101\	.line	865\	.endef
	.ln 	20
	rts	
	.def	_erase_puzzle\	.val	.\	.scl	-1\	.endef
	.align	2
	.globl	_draw_toon_load_arrow
	.def	_draw_toon_load_arrow\	.val	_draw_toon_load_arrow\	.scl	2\	.type	0x10020\	.endef
_draw_toon_load_arrow:
	.ln 	1
	.def	.bf\	.val	.\	.scl	101\	.line	884\	.endef
	.def	button\	.val	9\	.scl	9\	.type	0x2\	.endef
	.def	x\	.val	10\	.scl	9\	.type	0x3\	.endef
	.def	y\	.val	12\	.scl	9\	.type	0x3\	.endef
	.def	.ef\	.val	.\	.scl	101\	.line	932\	.endef
	.ln 	49
	rts	
	.def	_draw_toon_load_arrow\	.val	.\	.scl	-1\	.endef
	.align	2
	.globl	_draw_toon_save_arrow
	.def	_draw_toon_save_arrow\	.val	_draw_toon_save_arrow\	.scl	2\	.type	0x10020\	.endef
_draw_toon_save_arrow:
	.ln 	1
	.def	.bf\	.val	.\	.scl	101\	.line	951\	.endef
	.def	button\	.val	9\	.scl	9\	.type	0x2\	.endef
	.def	x\	.val	10\	.scl	9\	.type	0x3\	.endef
	.def	y\	.val	12\	.scl	9\	.type	0x3\	.endef
	.def	.ef\	.val	.\	.scl	101\	.line	991\	.endef
	.ln 	41
	rts	
	.def	_draw_toon_save_arrow\	.val	.\	.scl	-1\	.endef
	.align	2
	.globl	_draw_toon_pig
	.def	_draw_toon_pig\	.val	_draw_toon_pig\	.scl	2\	.type	0x10020\	.endef
_draw_toon_pig:
	.ln 	1
	.def	.bf\	.val	.\	.scl	101\	.line	1009\	.endef
	.def	button\	.val	9\	.scl	9\	.type	0x2\	.endef
	.def	x\	.val	10\	.scl	9\	.type	0x3\	.endef
	.def	y\	.val	12\	.scl	9\	.type	0x3\	.endef
	.def	.ef\	.val	.\	.scl	101\	.line	1062\	.endef
	.ln 	54
	rts	
	.def	_draw_toon_pig\	.val	.\	.scl	-1\	.endef
	.align	2
	.globl	_draw_toon_chklist
	.def	_draw_toon_chklist\	.val	_draw_toon_chklist\	.scl	2\	.type	0x10020\	.endef
_draw_toon_chklist:
	.ln 	1
	.def	.bf\	.val	.\	.scl	101\	.line	1080\	.endef
	.def	button\	.val	9\	.scl	9\	.type	0x2\	.endef
	.def	x\	.val	10\	.scl	9\	.type	0x3\	.endef
	.def	y\	.val	12\	.scl	9\	.type	0x3\	.endef
	.def	.ef\	.val	.\	.scl	101\	.line	1108\	.endef
	.ln 	29
	rts	
	.def	_draw_toon_chklist\	.val	.\	.scl	-1\	.endef
	.align	2
	.def	_erase_chklist\	.val	_erase_chklist\	.scl	3\	.type	0x10020\	.endef
_erase_chklist:
	.ln 	1
	.def	.bf\	.val	.\	.scl	101\	.line	1120\	.endef
	.def	x\	.val	8\	.scl	9\	.type	0x3\	.endef
	.def	y\	.val	10\	.scl	9\	.type	0x3\	.endef
	.def	.ef\	.val	.\	.scl	101\	.line	1135\	.endef
	.ln 	16
	rts	
	.def	_erase_chklist\	.val	.\	.scl	-1\	.endef
