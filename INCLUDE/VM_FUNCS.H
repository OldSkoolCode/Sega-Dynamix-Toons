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

/* VM initialization declarations */

#ifdef   __cplusplus
extern "C"
{
#endif

short           far vm_init ( void );
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
void            far vm_draw ( short , short, short, void *);
void            far vm_flip_draw(short, short, short, void *, short);
void            far vm_flood_fill( short, short, char );
void            far vm_dissolve ( short, short, short, short, short );
void            far vm_flip ( short );
void            far vm_get ( char huge *, short, short, short, short );
short           far vm_getpix( short, short );
unsigned long   far vm_getsize ( short, short );
void            far vm_line ( short, short, short, short );
short           far vm_poly ( short, short *, short * );
void            far vm_trans_poly ( short, short *, short *, char * );
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
short           far vm_define_mouse_area(short, short, short, short);
void            far vm_install_mouse_int( void (far *)());
void            far vm_mouse_flip( void );

/* block file i/o functions, located in vm_bfile.h */

void            far vm_hfree (void huge *);
void huge *     far vm_hmalloc (long, long);

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

short           far vm_speed (unsigned short *, unsigned short *, short );

/* short           far vm_timer_insert ( void (_far *)(), short );
short           far vm_timer_delete ( short ); */


/* other routines in the VM, not intended for general use */

short           far vm_tandy_check( void );
void            far where( void );
void            far set_ega(void);
void            far vm_palshade( short, short, short, short );
short           far vm_cycleinit( short, short, short );
void            far vm_cycle( void );
void            far am2mcga(  unsigned char huge *, unsigned char huge *,
                              unsigned short );

short           far vm_maskload( char * );

#ifdef   __cplusplus
}
#endif
#endif /* VM_FUNCS_H */
