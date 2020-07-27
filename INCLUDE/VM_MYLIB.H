/* * * * *
* VM_MYLIB.H
* COPYRIGHT 1989 BY DYNAMIX, INC
*
* Contains function external declarations for vm_mylib.c
*
* MODIFICATION HISTORY
* NAME            DATE     WHAT
*
* Mike Edwards    09/28/88 Created.
*
* * * * */

#ifndef VM_MYLIB_H
#define VM_MYLIB_H

#ifndef  FILE
#include "stdio.h"
#endif

/* Low level I/O */
short          far my_open( char *, short );
short          far my_create( char *, short, short );
short          far my_read( short, void *, unsigned short );
long           far my_lseek( short, long, short );
short          far my_close( short );

/* File level I/O */
FILE *         far my_fopen( char *, char * );
unsigned short far my_fread( void *, unsigned short, unsigned short, FILE *);
unsigned long  far my_hfread( void huge *, unsigned long, unsigned long, FILE *);
short          far my_fgetc ( FILE * );
unsigned short far my_fwrite ( void *, unsigned short, unsigned short, FILE *);
short          far my_fputc ( short, FILE *);
long           far my_ftell ( FILE * );
short          far my_fseek ( FILE *, long, short );
void           far my_rewind ( FILE *);
short          far my_feof( FILE * );
short          far my_fclose( FILE *);

/* Memory and strings */
void *         far my_malloc( unsigned short );
void *         far my_calloc ( short, short );
void           far my_free( void * );
char *         far my_strcat( char *, char * );
char *         far my_strcpy( char *, char * );
char *         far my_strchr( char *, short  );

#endif /* VM_MYLIB_H */
