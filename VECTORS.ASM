;
; All exption vectors go here!
;
	        xref 	start

		xref	Buserr,Addrerr,Ilglinst
		xref	Zdivide,Chkreg,Overflow
		xref	Privviol,Uninitv

	        xref Vblank,Hint,ExtInt

	        tsection .text

INITSTK:	dc.l	$1000000        ; stack address
INITPC:		dc.l	start           ; program start address
		dc.l	Buserr
		dc.l	Addrerr
		dc.l	Ilglinst
		dc.l	Zdivide
		dc.l	Chkreg
		dc.l	Overflow
		dc.l	Privviol
		dc.l	Uninitv

		ds.b	16*4

AUTO_2:   	dc.l	ExtInt
          	ds.b	4
AUTO_4:   	dc.l	Hint
          	ds.b	4
AUTO_6:   	dc.l	Vblank
          	ds.b	$88-4



