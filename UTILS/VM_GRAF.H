/* * * * *
* VM_GRAFIX.H
* COPYRIGHT 1989 BY DYNAMIX, INC
*
* Contains externs for VM functions pointers.
*
* MODIFICATION HISTORY
* NAME            DATE     WHAT
*
* M Edwards       11/30/88 Created to parallel grafix.inc
* P Lukaszuk      89       Overlayed.
* P Lukaszuk      89...    Updated and maintained.
*
* * * * */

/* function pointers located in the global jump table
   defined in vm_graf.asm. */

extern short (far * gr_init)( short );
extern void  (far * gr_char)( void );      /* registered based parameters */
extern void  (far * gr_line)(short, short, short, short);
extern void  (far * gr_draw)( struct shape *, short, short );
extern void  (far * gr_copy)( short, short, short, short );
extern void  (far * gr_get)( char huge *, short, short, short, short );
extern void  (far * gr_put)( char huge *, short, short, short, short );
extern unsigned short (far * gr_getsize)( short, short, short, short );
extern void  (far * gr_flip)(short);
extern void  (far * gr_show)(short, short, short, short);
extern void  (far * gr_fill)();      /* registered based parameters */
extern void  (far * gr_patfill)();   /* registered based parameters */
extern short (far * gr_fontload)( void *, short, void * );
extern long  (far * gr_shpsize)( struct shape **, short * );
extern void  (far * gr_shpcvt1)( struct shape **, char huge *, long, char huge *, long );
extern void  (far * gr_shpcvt2)( char huge *, char huge *, short );
extern void  (far * gr_xlat1)( char *, short, short, short, short );
extern void  (far * gr_xlat2)( char *, short, short, short, short );
extern void  (far * gr_palselect)( char far * );
extern short (far * gr_setpix)( short, short, short );
extern short (far * gr_getpix)( short, short );
extern void  (far * gr_dissolve)(short, short, short, short, short );
extern void  (far * gr_shake)( short, short );
extern void  (far * gr_border)( short );
extern void  (far * gr_setcolor)( short, short );
extern void  (far * gr_edraw)( void );
extern void  (far * gr_ecopy)( void );
extern void  (far * gr_ecopy_set)(short, short );
extern void  (far * gr_palshade)( short, short, short, short );
extern void  (far * gr_palwrite)( char *, short, short );
extern void  (far * gr_flip_draw)( struct shape *, short, short );
extern void  (far * gr_rectdraw)( struct shape *, short, short );
extern void  (far * gr_rectdraw_init)( struct shape *);
extern void  (far * gr_rectdraw_free)( struct shape *);
extern void  (far * gr_scroll)( struct shape *, short, short );
extern void  (far * gr_bmpfill)(void);   /* registered based parameters */
extern void  (far * gr_remapdraw)(void); /* registered based parameters */
extern void  (far * gr_maskdraw)(void);  /* registered based parameters */
extern void  (far * gr_monodraw)(void);  /* registered based parameters */
extern void  (far * gr_pixfill)(void);   /* registered based parameters */
extern void  (far * gr_rotatefill)(struct shape *,short );
extern void  (far * gr_size_rotate_draw)( struct shape *, short, short, short, short, short, short, short);
extern void  (far * tandy_set_io)(void);   /* registered based parameters */


/* font arrays */
extern unsigned char vm_font_wid[];    // in pixels
extern unsigned char vm_font_hgt[];    // in pixels
extern unsigned char vm_font_start[];  // first (ascii) chracter
extern unsigned char vm_font_cnt[];    // number of chars in font
extern unsigned char *vm_font_ptr[];   // ptrs to font data

