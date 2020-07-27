/* * * * *
*
*  VOLUME.H
*
*  This file contains the header info for the volume/resource manager.
*
*  By Rich Rayl -- (c) 1990 Dynamix Software Development, Inc.
*
*  Modification History:
*  ---------------------
*  09/24/90 RichR    File created      $Revision: 1.13.0.1 $
*                    Last modified     $Date: 1993/05/04 13:34:04 $
* * * * */

#ifndef VOLUME_H
#define VOLUME_H

/* #include <stdio.h>
#include "vm_mylib.h" 
#include "ports.h" */

extern void volume_init(void);
extern void volume_reset(void);
extern void volume_close(void);
extern short volume_full;
extern short volume_critical_override;
extern short volume_critical_error;
#if 0
extern void my_setbuf(FILE *, char *);

/* Special function to get information about the volumes */
extern long my_vol_offset(FILE *fp);
extern char *my_vol_name(FILE *fp);
#endif

/* Special function if EMM is active */
/*    volume_emm_init(max_pages, max_files, normal, buffer, rotate, list) */
/* short volume_emm_init(short,short,short,short,short,char *);
void volume_emm_reset(void);
short volume_emm_copy(char *);
short volume_emm_remove(char *); */

#endif /* VOLUME_H */
