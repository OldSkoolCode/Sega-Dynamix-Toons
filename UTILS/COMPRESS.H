/*
**   (C) 1988 by Dynamix, Inc.
**
**   COMPRESS.H.
**   Header file for COMPRESS.C.
** 
**   Date:       Name:            What:
**   08/29/88.   Lincoln Hutton.  Created.
*/


#ifndef   COMPRESS_H
#define   COMPRESS_H


/*
;	Algorithms used.
*/
#define  NO_PACKING     0
#define  REPEAT_BYTE    1
#define  LEMPEL_ZIV     2	/* Slightly improved, but still compatible */
#define  LZSS_HUFFMAN	3	/* LZSS with Huffman on top */
#define  MAX_ALGORITHM	LZSS_HUFFMAN


#include  <stdio.h>
#include  "vm_types.h"



#ifdef   MC68000

typedef  char       * FCHARPTR;       /* Far pointer. */
typedef  char      ** FCHARPTRPTR;    /* Pointer to a far pointer. */
#define  LONG(h)      ((long)h)       /* Absolute size of far pointer. */

#else

typedef  char  huge * FCHARPTR;       /* Far pointer. */
typedef  char  huge * huge * FCHARPTRPTR;  /* Far pointer to far pointer */
#define LONG(h) ( \
    ( (ulong) (*((ushort *)(&h)+1)) << 4 ) + (ulong) (*(ushort *)(&h)) \
    )

#endif



/* Elements needed by all packing methods.
** READ THIS!
** Changing this structure will necessitate changing code in rd_lza.asm
** and rd_rlea.asm.  Best not to!
*/
struct  pack_rec
{
	char   * queue;            /* This holds temporary packets.  */
	FCHARPTR table;            /* Table buffer (LZ) */
	union  pdata {             /* Actual packed data - either in a */
	    FCHARPTR fmem;         /* file, or in far memory. */
	    FILE   * fp;
	    } pk_data;
	long     data_off;         /* Offset into source/dest data. */
	long     pck_size;         /* Packed size.  Needed to determine EOF */
	long     unp_size;         /* Size unpacked. */
	long     seek_off;         /* Current (unpacked) offset. */
	uchar    queue_tail;       /* Size of packet in buffer. */
	uchar    queue_head;       /* Where routine left off in packet. */
   fpos_t   save_off;
	uchar    flags;            /* See #defines just below.  */
};



/*
   READ THIS!
   The UNPACKING bit is used in assembly RD_RLEA.ASM and RD_LZA.ASM
   and so should not be changed lightly.
*/
#define   METHOD_MASK   0x1f   /* Up to 32 methods possible. */
#define   IS_FILE       0x20   /* Packing/Unpacking a file.  */
#define   IS_MEM        0      /* opposite of IS_FILE */
#define   UNPACKING     0x40   /* unpacking (writing). */
#define   SEEKING       0      /* opposite of UNPACKING */



/*
;	All packed data has a five byte header.  The first byte contains
;	the packing method employed.  The next four bytes contain the 
;	size of the (rest of the data) when unpacked.
*/
#define   HEADER_SIZE   5        /* 5 byte non-packed header */






#define   PK_OPENFAIL   1   /* Failure opening file. */
#define   PK_BUFFFAIL   2   /* Not enough buffer space available. */
#define   PK_BADFORMAT  3   /* Data not in packed format. */
#define   PK_BADVERS    4   /* Data packed in earlier version  */
#define   PK_NOIMPLMNT  5   /* Packed format not supported (not linked) */
#define   PK_BADHANDLE  6   /* Invalid handle. */



/************************ Externs ***************************/
extern    unsigned   short   buffer_sizes[];


/*
;	Globals set up by check_handle ().
*/
extern    struct pack_rec  * cur_pptr;
extern    char             * cur_queue;
extern    char             * cur_wrbuff;
extern    char             * cur_rdbuff;
extern    long               cur_soff;
extern    unsigned char      cur_alg;
extern    FILE             * cur_fp;
extern    FCHARPTR           cur_dstbuff;
extern    FCHARPTR           cur_table;
extern    FCHARPTR           pack_string_table;



#ifdef __cplusplus
extern "C" {
#endif

ushort unp_read ();
ushort unp_write ( short );
char  * CALLOC ( short );
ushort get_fstr ( FCHARPTR, ushort );
#if  ! defined (USE_TEXT)
#pragma  alloc_text ( all, unp_read, unp_write, CALLOC, get_fstr )
#endif




short  get_byte ();               /* unpack read */
short  get_str (char *, ushort ); /* unpack read */
short move_str ( ushort );        /* unpack read/write.  */
short  store_str ( short, short ); /* unpack write. */
short  store_byte ( short );      /* unpack write. */
short put_byte ( short );         /* pack write.  */
#if  ! defined (USE_TEXT)
#pragma alloc_text (all,get_byte,get_str,move_str)
#pragma alloc_text (all,store_str,store_byte,put_byte)
#endif



short check_handle (short );
short is_read ( char *);
void  smart_free ( char *);
short free_handle ( short );
#if  ! defined (USE_TEXT)
#pragma  alloc_text ( all, check_handle, is_read,smart_free,free_handle)
#endif



short set_handle ( char * );
short  set_queue ( short, char *);
short  far  useiobuff ( unsigned short );
short  far  vm_pkFopen ( short, FILE *, char *, long);
short  far  vm_pkMopen ( short, FCHARPTR, char *, long );
#if  ! defined (USE_TEXT)
#pragma  alloc_text ( all, set_handle,set_queue,vm_pkFopen,vm_pkMopen)
#pragma  alloc_text ( all, useiobuff )
#endif



ushort far  vm_pkclose ( short );
void use_queue ();
ushort do_pkread ( short, ushort );
ushort  far  vm_pkread ( short, FCHARPTR, ushort );
#if  ! defined (USE_TEXT)
#pragma  alloc_text ( all,vm_pkclose, use_queue, do_pkread, vm_pkread)
#endif



ushort far  vm_pkwrite ( short, FCHARPTR, ushort );
long   far  vm_pklength ( short  );
long   far  vm_pkseek ( short, long, short );
ushort far  vm_pkrewind ( short );
#if  ! defined (USE_TEXT)
#pragma  alloc_text ( all,vm_pkwrite,vm_pklength,vm_pkseek,vm_pkrewind)
#endif



ushort  rle_read();
#if ! defined(USE_TEXT)
#pragma  alloc_text ( all, rle_read)
#endif

#ifdef __cplusplus
}
#endif


#endif

