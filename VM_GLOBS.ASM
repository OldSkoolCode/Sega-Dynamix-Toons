;* * * * *
;* VM_GLOBS.ASM
;* COPYRIGHT 1989 BY DYNAMIX, INC
;*
;* Contains all VM global variable definitions.
;*
;* MODIFICATION HISTORY
;* NAME            DATE     WHAT
;*
;* Greg Volkmer    6/?/88   Created.
;* Michael Edwards 88-89    Maintained
;* Peter Lukaszuk  Nov 89   Overlayed
;*
;* * * * *

SCREENVREZ	equ	200
SCREENHREZ	equ	320

MAX_FONTS	equ	2
MAX_VERTS	equ	0
MAX_PALS	equ	4
MAX_YREZ	equ	200

		XDEF  _vm_fgcolor,_vm_bgcolor,_vm_mode
		XDEF  _vm_lclip,_vm_rclip,_vm_tclip,_vm_bclip,_vm_clip
		XDEF  _vm_fill,_vm_fcolor,_vm_lcolor,_vm_pcolor
		XDEF  _vm_backptr,_vm_buffptr,_vm_scrnptr,_vm_srcptr
		XDEF  _vm_dstptr,_vm_backptr,_vm_machine
		XDEF  _vm_gmode,_vm_max_colors
		XDEF  _vm_card,_vm_256,_vm_numplanes

		XDEF  linecolor,fillcolor1,fillcolor2,fill_rt
		XDEF  fgcolor,bgcolor
		XDEF  top_line,bot_line,pattern

		XDEF  font_wid,font_hgt
		XDEF  _vm_font_wid,_vm_font_hgt

		XDEF  font_start,font_cnt,font_ptr
		XDEF  _vm_font_start,_vm_font_cnt,_vm_font_ptr
		XDEF  _scratch1,_scratch2,_scratch3,_scratch4
		XDEF  v_listx,v_listy,v2_listx,v2_listy,vertcnt
		XDEF  _v_listx,_v_listy,_vertcnt,v3_listx,v3_listy
		XDEF  _vm_reset_screen

		XDEF  _vm_hires
		XDEF  _vm_width,_vm_height,_vm_palptrs

		XDEF  _vm_schar

		bsection	.bss

; Font Info
_vm_fgcolor	ds.b    1       ;foreground color
_vm_bgcolor	ds.b    1       ;background color
_vm_mode	ds.b    1       ;mode (0 - replace,1 - or)
_vm_clip	ds.b    1       ;clipping on or off flag

; Clipping Info
_vm_lclip	ds.w    1       ;left clip location 
_vm_rclip	ds.w    1	;right clip location
_vm_tclip	ds.w    1       ;top clip location
_vm_bclip	ds.w    1	;bottom clip location
                          
_vm_fill    	ds.b    1       ;solid fills on or off flag
_vm_fcolor	ds.b    1       ;fill color
_vm_lcolor	ds.b    1       ;line color
_vm_pcolor	ds.b    1       ;planes for ega bitmaps

; Buffer Info
_vm_backptr	ds.l    1       ;background segment
_vm_buffptr	ds.l    1       ;screen buffer segment
_vm_scrnptr	ds.l    1       ;physical screen segment
_vm_srcptr	ds.l    1       ;source pointer
_vm_dstptr 	ds.l    1       ;destination pointer

_vm_machine 	ds.b    1       ; 1 -> Tandy, 0 -> not Tandy
_vm_gmode   	ds.b    1       ; 1 -> CGA, 2 -> EGA,...
_vm_card    	ds.b    1       ;the actual graphics card running on
_vm_256     	ds.b    1       ;flag for running in MCGA or VGA mode.
_vm_numplanes 	ds.b	1       ;number of bitplanes in present graphics mode

_vm_max_colors	ds.b	1

; locals used in various graphics routines
linecolor         ds.w      1
fillcolor1        ds.w      1
fillcolor2        ds.w      1
fgcolor           ds.b      1
bgcolor           ds.b      1
pattern           ds.w      1
top_line          ds.w      1
bot_line          ds.w      1
fill_rt           ds.l      1

; font variables

_vm_font_wid:
font_wid          ds.b      MAX_FONTS

_vm_font_hgt:
font_hgt          ds.b      MAX_FONTS

_vm_font_start:
font_start        ds.b      MAX_FONTS

_vm_font_cnt:
font_cnt          ds.b      MAX_FONTS

_vm_font_ptr:
font_ptr          ds.w      MAX_FONTS


; polygon vertice lists
_v_listx:
v_listx           ds.w      MAX_VERTS
_v_listy:
v_listy           ds.w      MAX_VERTS
v2_listx          ds.w      MAX_VERTS
v2_listy          ds.w      MAX_VERTS
v3_listx          ds.w      MAX_VERTS
v3_listy          ds.w      MAX_VERTS
_vertcnt:
vertcnt           ds.w      1


;palettes
_vm_open_pal:
_vm_palptrs       ds.l      MAX_PALS

_scratch1	  ds.w      1
_scratch2	  ds.w      1
_scratch3	  ds.w      1
_scratch4	  ds.w      16

_vm_hires         ds.b      2
_vm_width         ds.w      1     ;vm screen width
_vm_height        ds.w      1     ;vm screen height
_unused2          ds.l      1     ;palptrs

; 200 lines of four bytes each.  Extra 32 so we can align.
_vm_reset_screen   ds.w     1

_vm_schar 	ds.w	1       ; Starting character index for VDP.

