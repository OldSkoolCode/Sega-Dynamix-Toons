/* * * * *
* VM_FUNCS.H
* COPYRIGHT 1989 BY DYNAMIX, INC
*
* VM function prototypes.
*
* MODIFICATION HISTORY
* NAME            DATE     WHAT
*
* Piotr Lukaszuk x/xx/88 Created
* Richard Rayl   8/23/88 Moved all function declarations from VM_GLOBS.H
* Mike Edwards   x/xx/88 Maintained
* Piotr Lukaszuk 88...   Updated and maintained.
*
* * * * */

#ifndef VM_FUNCS_H
#define VM_FUNCS_H

#ifdef __cplusplus
extern "C" {
#endif

/* VM initialization declarations */

short           far vm_init ( short, short, char * );
void            far vm_reset( void );
void            far vm_restore ( void );
short           far vm_init_keybd ( short );
void            far vm_reset_keybd ( void );
short           far vm_init_timer ( short );
short           far vm_reset_timer ( void );
short           far vm_init_joy( void );
short           far vm_init_mouse ( void );
short           far vm_reset_mouse( void );
void            far vm_init_ovfl ( void );
void            far vm_reset_ovfl ( void );
void            far quit ( short );

/* VM Graphics functions */

void            far vm_border ( short );
void            far vm_circle ( short, short, short );
void            far vm_copy ( short, short, short, short );
void            far vm_draw ( struct shape *, short, short );
void            far vm_rectdraw ( struct shape *, short, short );
void            far vm_flip_draw(struct shape *, short, short, short);
void            far vm_flood_fill( short, short, char );
void            far vm_scan_draw(struct shape *, short, short, short);
void            far vm_size_draw( struct shape *, short, short, short, short, short );
void            far vm_scan_size_draw( struct shape *, short, short, short, short, short );
void            far vm_remap_draw( struct shape *, short, short, short, short, short, char * );
void            far vm_scale_draw( struct shape *, short, short, short, short );
void            far vm_size_rotate_draw( struct shape *, short, short, short, short, short, short, short );
void            far vm_texture_map( struct shape * , short * , short * );
void            far vm_get_rotate_dim( short *,short *,short *,short * );
void            far vm_scroll ( struct shape *, short, short);
void            far vm_dissolve ( short, short, short, short, short );
void            far vm_flip ( short );
void            far vm_get ( char huge *, short, short, short, short );
short           far vm_getpix( short, short );
unsigned short  far vm_getsize ( short, short );
void            far vm_line ( short, short, short, short );
short           far vm_poly ( short, short *, short * );
void            far vm_edraw( short far * );
void            far vm_ecopy( short far * );
void            far vm_put ( char huge *, short, short, short, short );
void            far vm_rect ( short, short, short, short );
void            far vm_xor ( short, short, short, short );
void            far vm_setcolor ( short, short );
short           far vm_setpix( short, short, short );
void            far vm_shake( short, short );
void            far vm_show ( short, short, short, short );
void            far vm_xlat1 ( char huge *, short, short, 
                              short, short );
void            far vm_xlat2 ( char huge *, short, short, 
                              short, short );

/* VM User Interaction routines */

unsigned short  far vm_scankey ( void );
unsigned char   far vm_asciikey ( void );
short           far vm_keystatus ( short );
short           far vm_dkey_joy ( short );
void            far vm_ajoy (short, short *, short *);
unsigned char   far vm_djoy( short );
short           far vm_joy_button( short );
short           far vm_joy_axis( short );
short           far vm_get_mouse(short *, short *);
short           far vm_mouse_button(short);
short           far vm_set_mouse(short, short);
void            far vm_mouse_off( void );
void            far vm_mouse_on( void );
void            far vm_set_cursor( struct shape *, short, short);
short           far vm_define_mouse_area(short, short, short, short);
void            far vm_install_mouse_int( void (far *)());

/* block file i/o functions, located in vm_bfile.h */

void            far vm_hfree (char huge *);
char huge *     far vm_hmalloc (long, long);

void            far vm_fontfree ( short );
short           far vm_fontload ( void * );
short           far vm_fontselect ( short );
short           far vm_fontwidth ( short );
short           far vm_fontheight ( short );
short           far vm_str_width( char * );
short           far vm_hstr_width( char far * );
void            far vm_str ( char *, short, short );
void            far vm_hstr ( char far *, short, short );
short           far vm_charsize( short, short *, short * );

void            far vm_palfree ( char far * );
char far *      far vm_palload ( void * );
char far *      far vm_palselect ( char far * );

short           far vm_scrnload ( void * );

struct shape ** far vm_shapeload ( void * );
short           far vm_shapecnt(struct shape **);
void            far vm_shapefree ( struct shape ** );
struct shape *  far vm_alloc_flip ( struct shape *, short );
void            far vm_free_flip ( struct shape * );
struct shape ** far vm_table_flip ( struct shape **, short );
struct shape ** far vm_rectdraw_init ( struct shape ** );
void            far vm_rectdraw_free ( struct shape ** );

short           far vm_speed (unsigned short *, unsigned short *, short );

short           far vm_timer_insert ( void (far *)(), short );
short           far vm_timer_delete ( short );


/* other routines in the VM, not intended for general use */

void            far free_shape_table( struct shape ** );
short           far vm_init_shapecnt ( void );
void            far vm_free_shapecnt ( struct shape ** );
void            far vm_set_shapecnt ( struct shape **, short, short );
void            far flip_it ( struct shape *, struct shape *,
                              short, unsigned long, short );

void            far cga_shapecvt1 ( struct shape **, unsigned char huge *,
                                   long, unsigned char huge *, long );
unsigned short  far shape2cga ( unsigned char huge *, unsigned char huge *,
                                unsigned short, unsigned short, short );
void            far remap_shape ( struct shape*, short, short );
void            far shape2ega ( unsigned char huge *, 
                                unsigned char huge *, short );

short           far vm_tandy_check( void );
void            far where( void );
void            far set_ega(void);
void            far vm_palshade( short, short, short, short );
short           far vm_cycleinit( short, short, short );
void            far vm_cycle( void );
void            far am2mcga(  unsigned char huge *, unsigned char huge *,
                              unsigned short );

short           far vm_maskload( char * );
void            far vm_mask_draw( struct shape *, short, short, short, short, short, char);
void            far vm_mono_draw( struct shape *, short, short, short, short, short, short);

#ifdef __cplusplus
}
#endif


#endif /* VM_FUNCS_H */
