

		tsection	.text


;    			00000000001111111111222222222233333333334444444444
;    			01234567890123456789012345678901234567890123456789
segahdr:
		dc.b	'SEGA GENESIS    '
		dc.b	'(C)1994 DYNAMIX '
		dc.b	'Sid & Al',39,'s Incredible Toons                     '
		dc.b	'Sid & Al',39,'s Incredible Toons                     '
		dc.b	'GM 00000000-00'
		dc.w	0
		dc.b	'J',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		dc.l	0,0x20000
		dc.l	0xff0000,0xffffff
		dc.b	'            '
		dc.b	'            '
		dc.b	'                                        '
		dc.b	'JUE             '

		IFNE	$100-(*-segahdr)
		.ECHO	segahdr size is not $100
		FAIL	2
		ENDC

