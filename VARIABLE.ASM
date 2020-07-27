*************************************************************************
*                              VARIABLES                                *
*************************************************************************

	BSECTION	.bss

	include	equates.inc

	XDEF	FlyBackFlag
	XDEF	_SYS_JoyHit
	XDEF	KeyHit
	XDEF	_SYS_JoyTable
	XDEF	_SYS_Joy2Table
	XDEF	KeyTab1
	XDEF	KeyTab2
	XDEF	CellMapCols
	XDEF	CellMapRows
	XDEF	DMATemp
	XDEF	PalBuffer
	XDEF	_SYS_LastChar
	XDEF	_SYS_FirstChar
	XDEF	_SYS_VDPAccess
	XDEF	_MapABuff
;	XDEF	_MapBBuff
	XDEF	_MapX
	XDEF	_MapY
	XDEF	_SYS_VCount
	XDEF	_SprAttrAddr

_SYS_VDPAccess	ds.b	1		; whether can access VDP or not

		ds.w	0
FlyBackFlag	ds.w	1
_SYS_JoyHit:
KeyHit		ds.w	1
_SYS_JoyTable:
KeyTab1		ds.b	16
_SYS_Joy2Table:
KeyTab2		ds.b	16
CellMapCols	ds.w	1
CellMapRows	ds.w	1
DMATemp		ds.l	1

_MapABuff	ds.w	(MAPWIDTH*MAPHEIGHT)
;_MapBBuff	ds.w	(MAPWIDTH*MAPHEIGHT)

PalBuffer	ds.b	128

_SYS_FirstChar	ds.w	1		; first character allocated in VDP
_SYS_LastChar	ds.w	1		; last character allocated in VDP

_MapX		ds.w	1
_MapY		ds.w	1

_SYS_VCount	ds.l	1

_SprAttrAddr	ds.w	1
