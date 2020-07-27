/* * * * *
* VM_KEYS.H
* COPYRIGHT 1989 BY DYNAMIX, INC
*
* Defines to be used with vm_scankey().
*
* MODIFICATION HISTORY
* NAME            DATE     WHAT
*
* Mike Edwards    03/08/89 Created.
*
* * * * */

#ifndef VM_KEYS_H
#define VM_KEYS_H

/* Defines for the keyboard routines
*/
/* this one can also be used with vm_asciikey() */
#define CNTRL(A)        (A & 0x0080)
#define SCAN(a)         (a>>8)
#define ASCII(a)        (a&0x07f)

#define BACKSPACE       0x0e08
#define TAB             0x0f09
#define RETURN          0x1c0d
#define ENTER           0x1c0d
#define ESCAPE          0x011b
#define SPACE           0x3920
#define INSERT          0x5200

#define F1              0x3B00
#define F2              0x3C00
#define F3              0x3D00
#define F4              0x3E00
#define F5              0x3F00
#define F6              0x4000
#define F7              0x4100
#define F8              0x4200
#define F9              0x4300
#define F10             0x4400
#define F11             0x5700
#define F12             0x5800
#define LEFT_UP         0x4700
#define UP              0x4800
#define RIGHT_UP        0x4900
#define LEFT            0x4B00
#define CENTER          0x4C00
#define RIGHT           0x4D00
#define LEFT_DOWN       0x4F00
#define DOWN            0x5000
#define RIGHT_DOWN      0x5100
#define INSERT          0x5200
#define DELETE          0x5300
#define PRTSCRN         0x3700
#define SYSREQ          0x4300      /* Same as Function key 9? */

#endif /* VM_KEYS_H */
