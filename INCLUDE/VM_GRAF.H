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

/* font arrays */
extern unsigned char vm_font_wid[];    /* in pixels*/
extern unsigned char vm_font_hgt[];    /* in pixels*/
extern unsigned char vm_font_start[];  /* first (ascii) chracter*/
extern unsigned char vm_font_cnt[];    /* number of chars in font*/
extern unsigned char *vm_font_ptr[];   /* ptrs to font data*/

