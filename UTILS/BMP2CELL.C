/* * * * *
*
*  BMP2CELL.C
*
*  This file contains a simple program that will convert
*  a .BMP file to a file that is compatible with the 3DO
*  cell format.
*
*  By Rich Rayl -- (c) 1993 Dynamix Software Development, Inc.
*	Tabs now set in brief at 4 and 7 (every 3 spaces).
*
*  Modification History:
*  ---------------------
*  11/02/93	KenH		Added sega output format
*  03/22/93 RichR    File created
*
* * * * */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "vm_mylib.h"
#include "vm_bfile.h"
#include "vm.h"
#include "compress.h"

static long   palette[256];
static unsigned short  table_widths[500];
static unsigned short  table_heights[500];
static short  num_shapes;
unsigned char far *bitmap;
char	segaOut = FALSE;

#define SWAP      1     // Set to 0 if not swapping lines

void save3DOFiles(char *fname);
void saveSegaFile(char *fname);
void usage(void);

/* * * * *
*
*  main();
*
* * * * */
short main(int argc, char **argv)
{
   FILE *fp;
   unsigned char far *bptr, color, *pptr;
   long i, size, *lptr;
	short ph;
	int curarg;

	curarg = 1;
	for (curarg=1; curarg < argc; curarg++)
	{
		if ((*argv[curarg] == '-') || (*argv[curarg] == '/')) 
		{
			switch (tolower(*(argv[curarg]+1))) 
			{
				case 's':
					segaOut = TRUE;
					break;
				defualt:
					usage();
			}
		}
		else
			break;
	}

	if (curarg >= argc)
		usage();

   /* Open specified bitmap file */
   fp = vm_bopen(argv[curarg]);
   if(!fp || (vm_bfind(fp,"BMP:INF:",0) == -1))
   {
      printf("Unable to open '%s'.\n", argv[curarg]);
      exit(1);
   }

   /* Determine the width and height of the bitmaps */
   my_fread(&num_shapes, 2, 1, fp);
   my_fread(table_widths, 2, num_shapes, fp);
   my_fread(table_heights, 2, num_shapes, fp);

   /* Determine size of entire shape table */
   size = 0;
   for(i=0; i<num_shapes; i++)
      size += table_widths[i] * table_heights[i];

   /* Allocate memory for bitmap data */
   bitmap = (char far *)vm_hmalloc(size,MEMF_CLEAR);
   if(!bitmap)
   {
      printf("Not enough memory!  %lu more bytes needed.\n",size-(long)vm_hmalloc(-1,0));
      exit(1);
   }

   /* Load EGA part of bitmap data */
   bptr = bitmap;
   if(   (vm_bfind(fp, "BMP:BIN:", 0) != -1)
      && ((ph=vm_pkFopen(0, fp, "r", vm_bsize(fp))) >= 0) )
   {
      printf("Loading BIN block...");
      for(i=size/2; i; i--)
      {
         vm_pkread(ph,&color,1);
         *bptr++ = color>>4;
         *bptr++ = color&0xf;
      }
      vm_pkclose(ph);
   }

   /* Load VGA part of bitmap data */
   bptr = bitmap;
   if(   (vm_bfind(fp, "BMP:VGA:", 0) != -1)
      && ((ph=vm_pkFopen(0, fp, "r", vm_bsize(fp))) >= 0) )
   {
      printf("\nLoading VGA block...");
      for(i=size/2; i; i--)
      {
         vm_pkread(ph, &color, 1);
         *bptr++ |= color&0xf0;
         *bptr++ |= (color&0xf)<<4;
      }
      vm_pkclose(ph);
   }
   vm_bclose(fp);

   /* Load palette by same name */
   printf("\nLoading Palette...");
   strcpy(strchr(argv[curarg],'.'),".pal");
   fp = vm_bopen(argv[curarg]);
   if(!fp)
      fp = vm_bopen("default.pal");
   if(vm_bfind(fp, "PAL:VGA:", 0) == -1)
   {
      printf("Error -- No palette found '%s'\n", argv[curarg]);
      exit(1);
   }
   else
   {
      lptr = palette;
      for(i=256; i; i--)
      {
         pptr = (char *)lptr;
         fread(lptr,3,1,fp);
         if(!*lptr)
            *lptr = 0x04040404L;
         else
         {
            *pptr++ *= 4;
            *pptr++ *= 4;
            *pptr *= 4;
         }
         lptr++;
      }
   }
   vm_bclose(fp);

	if (segaOut)
		saveSegaFile(argv[curarg]);
	else
		save3DOFiles(argv[curarg]);

   return(0);
}

/************************************************************************/
/* Function:		void usage(void)													*/
/* Description:	print out usage for program and exit						*/
/* Parameters:		.																		*/
/* Returns:			.																		*/
/************************************************************************/
void usage(void)
{
      printf("Usage:  BMP2CELL -s {filename.bmp}\n");
		printf("        -s = Sega output\n");
		printf("        default = 3DO output\n");
      exit(1);
}


/************************************************************************/
/* Function:		void save3DOfiles(char *fname);								*/
/* Description:	save off 3DO files to disk										*/
/* Parameters:		fname = filename of bmp											*/
/* Returns:			.																		*/
/************************************************************************/
void save3DOFiles(char *fname)
{
   FILE *fp;

   unsigned char far *bptr, color, *pptr;
   char filename[100];
   short width,height;
   short x, y;
   short bitmap_num;

   /* Save each of the bitmaps */
   printf("\n");
   *strchr(fname,'.') = 0;
   bptr = bitmap;
   for(bitmap_num=0; bitmap_num < num_shapes; bitmap_num++)
   {
      /* Save a .PPM file */
      sprintf(filename,"%s.%03d",fname,bitmap_num);
      width = table_widths[bitmap_num];
      height = table_heights[bitmap_num];
      #if SWAP
         height += height & 1;
      #endif
      printf("Saving Bitmap:  '%s'  Width=%d   Height=%d\n", filename, width, height);
      fp = fopen(filename,"wb");
      fprintf(fp, "P6\n%d %d\n255\n", width, height);
      for(y=0; y<height; y++)
      {
         for(x=0; x<width; x++)
         {
            #if SWAP // Alternate lines
               if((y==height-2) && (height != table_heights[bitmap_num]))
               {
                  bptr++;
                  color = 0;
               }
               else
                  color = *(bptr++ + (y&1 ? -width : width));  
            #else
               color = *bptr++;
            #endif
            if(color)
               fwrite(&palette[color],3,1,fp);
            else
            {
               fputc(0,fp);
               fputc(0,fp);
               fputc(0,fp);
            }
         }
      }
      if(height != table_heights[bitmap_num])
         bptr -= width;
      fclose(fp);
   }

}

/************************************************************************/
/* Function:		void saveSegafile(char *fname);								*/
/* Description:	save off sega files to disk									*/
/* Parameters:		fname = filename of bmp											*/
/* Returns:			.																		*/
/************************************************************************/
void saveSegaFile(char *fname)
{
   FILE *fp;

   unsigned char far *bptr, color, *pptr;
   char filename[100];
   short width,height;
   short x, y;
   short bitmap_num;

   /* Save each of the bitmaps */
   printf("\n");
   *strchr(fname,'.') = 0;
   bptr = bitmap;
   for(bitmap_num=0; bitmap_num < num_shapes; bitmap_num++)
   {
      /* Save a .PPM file */
      sprintf(filename,"%s.%03d",fname,bitmap_num);
      width = table_widths[bitmap_num];
      height = table_heights[bitmap_num];
      #if SWAP
         height += height & 1;
      #endif
      printf("Saving Bitmap:  '%s'  Width=%d   Height=%d\n", filename, width, height);
      fp = fopen(filename,"wb");
      fprintf(fp, "P6\n%d %d\n255\n", width, height);
      for(y=0; y<height; y++)
      {
         for(x=0; x<width; x++)
         {
            #if SWAP // Alternate lines
               if((y==height-2) && (height != table_heights[bitmap_num]))
               {
                  bptr++;
                  color = 0;
               }
               else
                  color = *(bptr++ + (y&1 ? -width : width));  
            #else
               color = *bptr++;
            #endif
            if(color)
               fwrite(&palette[color],3,1,fp);
            else
            {
               fputc(0,fp);
               fputc(0,fp);
               fputc(0,fp);
            }
         }
      }
      if(height != table_heights[bitmap_num])
         bptr -= width;
      fclose(fp);
   }

}
