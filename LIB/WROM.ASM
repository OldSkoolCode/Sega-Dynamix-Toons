


	tsection	.text

	XDEF	_writetorom

_writetorom:
	move.b	$780005,d0
	and.l	#$20,d0
	eor.l	#$20,d0
	rts




