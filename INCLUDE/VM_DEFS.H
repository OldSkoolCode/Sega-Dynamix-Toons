/* * * * *
* VM_DEFS.H
* COPYRIGHT 1989 BY DYNAMIX, INC
*
* Contains VM defines.
*
* MODIFICATION HISTORY
* NAME            DATE     WHAT
*
* Peter Lukaszuk  88       Created.
* Richard Rayl    08/23/88 Moved all definitions from VM_GLOBS.H
* Peter Lukaszuk  88 ...   Updated and maintained.
* 
* * * * */

#ifndef VM_DEFS_H
#define VM_DEFS_H

   /* defines for graphics modes 
   */
   #define AUTOSELECT   0
   #define CGA          1
   #define EGA          2
   #define TANDY        3
   #define HCGA         4  /* Hercules is no longer available */
/* #define HERCULES     4 */
   #define MCGA         5
   #define AMIGAVM      6
   #define EVA          7
   #define VGA          8
   #define EVGA         9
   #define HVGA         10
   #define EGA640x200   11
   #define EGA640x350   12
   #define VGA640x480   13
   #define VGA640x400   14
   #define HEGA         EGA640x200
   #define VGA320x400   15

   #define CGA_BIT          1
   #define EGA_BIT          2
   #define TANDY_BIT        4
   #define HCGA_BIT         8  /* Hercules is no longer available */
/* #define HERCULES_BIT     8 */
   #define MCGA_BIT         16
   #define AMIGAVM_BIT      32
   #define ATARIST_BIT      64
   #define VGA_BIT          128
   #define AUTOSELECT_BITS  255

   /* Maximum number of shape tables allowed */
   #define MAX_SHAPE_TABLES   40
   /* flip directions for shape flipping functions */
   #define FLIP_HORIZONTAL 1
   #define FLIP_VERTICAL   2
   #define FLIP_HORZ FLIP_HORIZONTAL
   #define FLIP_VERT FLIP_VERTICAL

   /* some equates and externs from grafix.inc */
   #define MAX_FONTS 20
   #define MAX_PALS  10
   #define MAX_VERTS 20

   #define NUM_GRAFIX_ROUTINES 50

   /* for second paramater of vm_hmalloc() calls */
   #define MEMF_PUBLIC (1<<0)
   #define MEMF_CHIP   (1<<1)
   #define MEMF_FAST   (1<<2)

   #define MEMF_CLEAR  (1L<<16)
   #define MEMF_LARGEST (1L<<17)

   #define ORTEXT    1
   #define BOLD      2
   #define ITALIC    4
   #define UNDERLINE 8
   #define LITE      16

/* Structure definition */
#ifdef __BORLANDC__
   typedef struct shape
   {
      short shp_seg;
      short shp_ptr;
      short mask_ptr;
      short width;
      short height;
   };

   /* Extended shape structure definition */
   typedef struct xshape {
      short shp_seg;
      short shp_ptr;
      short mask_ptr;
      short width;
      short height;
      short xanchor;
      short yanchor;
      char  skipcolor;
      char  flags;
   };
#endif



#endif /* VM_DEFS_H */
