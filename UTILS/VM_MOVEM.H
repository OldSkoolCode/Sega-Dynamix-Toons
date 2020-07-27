/* Header info for VM_MOVEM.ASM.
 */

#ifndef  VM_MOVEM_H
#define  VM_MOVEM_H

char  huge  * far vm_hmemmove ( char huge *, char huge *, long );
char  huge  * far vm_hmemcpy ( char huge *, char huge *, short );
void  far vm_hmemset ( char huge *, short, long );
char  huge  * far vm_cnvrt_ptr (char huge *);
short far vm_huge_cmp ( char huge *, char huge *);
char  huge  * far vm_small_off ( char huge *);

#endif
