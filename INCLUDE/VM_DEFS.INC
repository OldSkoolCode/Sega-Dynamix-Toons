
SCREENVREZ	equ	200
SCREENHREZ	equ	320

MAX_FONTS	equ	2
MAX_VERTS	equ	500
MAX_PALS	equ	4
MAX_XREZ	equ	320
MAX_YREZ	equ	200

VSTAT		equ	$C00004
VCOUNT		equ	$C00008


		XREF  _vm_fgcolor,_vm_bgcolor,_vm_mode
		XREF  _vm_lclip,_vm_rclip,_vm_tclip,_vm_bclip,_vm_clip
		XREF  _vm_fill,_vm_fcolor,_vm_lcolor,_vm_pcolor
		XREF  _vm_backptr,_vm_buffptr,_vm_scrnptr,_vm_srcptr
		XREF  _vm_dstptr,_vm_backptr,_vm_machine
		XREF  _vm_gmode,_vm_max_colors
		XREF  _vm_card,_vm_256,_vm_numplanes

		XREF  linecolor,fillcolor1,fillcolor2,fill_rt
		XREF  fgcolor,bgcolor
		XREF  top_line,bot_line,pattern

		XREF  font_wid,font_hgt
		XREF  _vm_font_wid,_vm_font_hgt

		XREF  font_start,font_cnt,font_ptr
		XREF  _vm_font_start,_vm_font_cnt,_vm_font_ptr
		XREF  _scratch1,_scratch2,_scratch3,_scratch4
		XREF  v_listx,v_listy,v2_listx,v2_listy,vertcnt
		XREF  _v_listx,_v_listy,_vertcnt,v3_listx,v3_listy
		XREF  _edge_table
		XREF  _vm_reset_screen

		XREF  _vm_hires,_vm_ytable
		XREF  _vm_width,_vm_height,_vm_palptrs

		XREF  _vm_cpu_screen
		XREF  _vm_schar


	  

