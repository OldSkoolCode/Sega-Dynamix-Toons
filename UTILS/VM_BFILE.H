/* * * * *
* VM_BFILE.H
* COPYRIGHT 1989 BY DYNAMIX, INC
*
* Include file for block file i/o routines.
*
* MODIFICATION HISTORY
* NAME            DATE     WHAT
*
* Lincoln Hutton  03/28/89 Submitted.
*
* * * * */


#ifndef VM_BFILE_H
#define VM_BFILE_H

#ifndef  FILE
#include "stdio.h"
#endif


#define  MAX_DEPTH      6
#define  MAX_BFILES     4
#define  PARENT         0x80000000     /* high bit of long */




/*
;  This record forms a state vector for open blocked files.  Available
;  records are flagged as such by fp == 0.  cur_path is the current path
;  string.  The '+ 1' is for NULL ending.  endoffs gives the ending 
;  absolute file offsets for each block in the current path.  These are
;  needed to know when to 'fall out' in the search.  The 0th end offset
;  always contains the file length, and is set in vm_bopen ().
;  
;  The bfile structures are not dynamically allocated at run time in 
;  order to avoid possible memory segmentation problems.
*/
struct bfile  {
      FILE *   fp;
      char     cur_path [ MAX_DEPTH * 4 + 1 ];
      long     endoffs [ MAX_DEPTH + 1];
      short    depth;
      short    N;               /* which occurance of cur path */
      long     cur_off;         /* current offset into file */
      long     cur_size;        /* size of current block */
   };





/* static */ 
struct bfile *
find_fp ( FILE * fp );

/* static */ 
void reset_bfile ( struct bfile * b  );

/* static */ 
str_eq ( register char * s1, register char * s2, short  N );

FILE * far vm_bopen ( char * fname );

/* static */
long
bfind_error ( struct bfile * b ) ;

long far
vm_bfind ( FILE * fp, char * path, short N );

long far 
vm_bsize ( FILE * fp );

short far
vm_bclose ( FILE * fp  );

short far
vm_isbfile ( void * fp );


struct bfile * far 
vm_bfile_get ( struct bfile *, FILE * );

short far
vm_bfile_set ( struct bfile * );


#ifndef USE_TEXT
#pragma alloc_text(all,find_fp,reset_bfile,str_eq,vm_bopen,bfind_error)
#pragma alloc_text(all,vm_bfind,vm_bsize,vm_bclose,vm_isbfile)
#pragma alloc_text(all,vm_bfile_get, vm_bfile_set) 
#endif


#endif
