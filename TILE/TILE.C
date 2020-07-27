/* $Header$ */
/************************************************************************/
/* Module:			TILE.C																*/
/* Description:	convert an IFF file to Futurescape Productions format.*/
/* Part of:			TILE.EXE																*/
/* Original:		Kenneth L. Hurley													*/
/* Date:				10/31/93																*/
/************************************************************************/
/*						*** Copyright 1993 Futurescape Productions ***			*/
/************************************************************************/

/*
 *
 * $Log$
 *
 */

/************************************************************************/
/* includes section																		*/
/************************************************************************/
#include <stdio.h>
#include	"machine.h"


/************************************************************************/
/* typedefs																					*/
/************************************************************************/

typedef struct iffHead {
		char 		id[4];				/* character ID's 	*/
		ULONG		size;					/* size of chunk 		*/
		} iffHead;


/************************************************************************/
/* defines																					*/
/************************************************************************/

#define	LONGSWAP(dest, src) \
				asm { \
				mov	ax,word ptr src; \
				mov	dx,word ptr src+2; \
				xchg	ah,al; \
				xchg	dh,dl; \
				mov	word ptr dest,dx; \
				mov	word ptr dest+2,ax; \
				} 

#define	WORDSWAP(dest, src) \
				asm { \
				mov	ax,word ptr src; \
				xchg	ah,al; \
				mov	word ptr dest,ax; \
				} 

#define	
/************************************************************************/
/* global variables																		*/
/************************************************************************/

/************************************************************************/
/* Function:		void main(int argc, char **argv);							*/
/* Description:	main interface to program										*/
/* Parameters:		argc = number of arguments										*/
/* 					argv = pointer to pointer of characters of parameters	*/
/* returns:			.																		*/
/************************************************************************/
void main(int argc, char **argv)
{
	ULONG	temp1, temp2;


	temp1 = 0xff001055;

	LONGSWAP(temp2,temp1);

	printf("temp1 = %lx\ttemp2 = %lx\n", temp1, temp2);

}

