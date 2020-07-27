/* * * * *
* VM_GLOBS.H
* COPYRIGHT 1989 BY DYNAMIX, INC
*
* Contains all VM global variable externs.
*
* MODIFICATION HISTORY
* NAME            DATE     WHAT
*
* Greg Volkmer     6/?/88  Created.
*                          All VM functions are now far function calls.
* Richard Rayl     89      Improved and maintained by
* Peter Lukaszuk   89...   Improved and maintained by
*
* * * * */

#ifndef VM_GLOBS_H
#define VM_GLOBS_H

/* Globals for Fonts */

extern char  vm_fgcolor;    /* foreground color    */
extern char  vm_bgcolor;    /* background color    */
extern char  vm_mode;       /* 0 - replace, 1 - or */
extern unsigned char vm_font_wid[]; /* width in pixels     */
extern unsigned char vm_font_hgt[]; /* height in pixels    */
/* first (ascii) character, and number of chars in the font */
extern unsigned char vm_font_start[], vm_font_cnt[];
/* ptrs to font data, NULL indicates no font loaded in that slot */
extern unsigned char *vm_font_ptr[];


/* Globals for clipping */

extern short vm_lclip;      /* left clip boundry */
extern short vm_rclip;      /* right clip boundry */
extern short vm_tclip;      /* top clip boundry */
extern short vm_bclip;      /* bottom clip boundry */
extern char  vm_clip;       /* clip flag */
extern short tandy_768k;    /* TRUE on that tandy */

/* Globals for Geometric Shapes */

extern char  vm_lcolor;     /* line color */
extern char  vm_fcolor;     /* fill color */
extern char  vm_fill;       /* fill flag */       
extern char  vm_pcolor;     /* second color for 256 color pattern */
extern short v_listx[];     /* list of x index values */
extern short v_listy[];     /* list of y index values */
extern short vertcnt;       /* number of vertices in the poly */


/* Globals for Buffers */
#ifdef __BORLANDC__
   typedef short VM_VIDPTR;
#else
   typedef void *VM_VIDPTR;
#endif
extern VM_VIDPTR vm_buffptr;    /* buffer pointer */
extern VM_VIDPTR vm_scrnptr;    /* screen pointer */
extern VM_VIDPTR vm_backptr;    /* background pointer */
extern VM_VIDPTR vm_srcptr;     /* source pointer */
extern VM_VIDPTR vm_dstptr;     /* destination pointer  */


/* Globals for current selected palette values */

extern char  vm_open_pal[];
extern char  vm_ppal[];
extern char  vm_col0[];
extern short vm_pal1[];  /* main palette */
extern short vm_pal2[];  /* pattern palette */
extern short vm_tpal[];  /* text palette */
extern char vm_mc_fgcolor[5];


/* Globals for the joystick routines.  */

extern unsigned char vm_havejoy0;   /* READ ONLY!! */
extern unsigned char vm_havejoy1;   /* READ ONLY!! */
extern unsigned char vm_haveaxis;   /* READ ONLY!! */


/* Globals for the keyboard routines. */

extern char  vm_keybd_on;
extern char  vm_capslock;
extern short vm_downkey;
extern char  vm_djoy0;
extern char  vm_djoy1;
extern char  vm_kbuffsize;
extern short vm_akjoy0x;
extern short vm_akjoy0y;
extern short vm_akjoy1x;
extern short vm_akjoy1y;
extern short vm_joyreset0;
extern short vm_joyreset1;
extern short vm_akj_rate;
extern short kbuffer[32];      /* READ ONLY!! */
extern short kheadptr;         /* READ ONLY!! */
extern short ktailptr;         /* READ ONLY!! */
extern char  kftable[];        /* READ ONLY!! */


/* Globals for the mouse routines. */
extern unsigned char vm_havemouse;        /* READ ONLY!! */
extern unsigned char vm_mouse_buttons;    /* READ ONLY!! */
extern unsigned short vm_mouse_x;         /* READ ONLY!! */
extern unsigned short vm_mouse_y;         /* READ ONLY!! */

/* Globals for the timer routines. */

extern char  vm_timer_on;
extern short vm_countdown;

extern char vm_machine;
extern char vm_gmode;
extern char vm_card;
extern char vm_256;
extern char vm_numplanes;
extern short vm_width;
extern short vm_height;

extern char vm_hires;
extern char far * vm_palptrs[];

extern char  vm_max_colors;

/* Globals for the divide overflow interrupt routine. */

extern char  vm_ovfl_on;

#endif /* VM_GLOBS_H */
