/***
 *	Dynamix BMP file to Futurescape Productions Sega Sprites (FPA) Converter
 *	Copyright 1993 Futurescape Productions
 *	All Rights Reserved
 *		History:
 *		09/06/92	KLM, Started coding.
 *		12/31/92	KLM, Added Kens DPaint Animate reading code to CVTSCE.
 *		04/27/93 KLM, Fixed bug in bitmap size allocation.
 *		04/27/93 KLM, Added arg_debug flag, clean printfs'.
 *		04/27/93 KLM, Added RLE compression.
 *		05/06/93 KLH, added simple duplicate frame removal.
 ***/

#define	__EXEFILE__		"BMP2FPA"
#define	__USAGE__		"Convert Dynamix BMP to Sega Sprites"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include	<ctype.h>
#include <errno.h>
#include <dos.h>
#include "tools.h"
#include "vm_mylib.h"
#include "vm_bfile.h"
#include "vm.h"
#include "compress.h"


char	*arg_infile = NULL;
char	*arg_outfile = NULL;
int	arg_list = FALSE;
int	arg_oneoffset = FALSE;
LONG	arg_pal = -1l;
int	arg_scaled = FALSE;
int	arg_bitmap = FALSE;
int	arg_noinfo = FALSE;
int	arg_debug = FALSE;
int	arg_rle = FALSE;
int	arg_view = FALSE;
int	arg_genoverlay = FALSE;
int	arg_zerooff = FALSE;
int	arg_ydir = FALSE;

short	GBph;
short	GVph;

char	hasBin = FALSE;
char	hasVGA = FALSE;

/*	multiple input file variables	*/
char	inFile[30][30];						/*	30 input file names	*/

struct arg_ident {
	char	*cmd;
	void	*var;
	char	*usage;
} arg_array[] = {
	"g",&arg_genoverlay,"generate overlayed sprites",
	"b",&arg_bitmap,"Set bitmap Output file",
	"d",&arg_debug,"Debugging information printed",
	"l",&arg_list,"Input file is text list of multiple anims",
	"o",&arg_oneoffset,"Use anim position from first file only",
	"p#",&arg_pal,"Set palette to #",
	"r",&arg_rle,"RLE compression for bitmaps only",
	"s",&arg_scaled,"Set scaled Output file",
	"x",&arg_noinfo,"Exclude flip/color information",
	"v",&arg_view,"View Animation as converting",
	"y",&arg_ydir,"Do Y direction bitmap",
	"z",&arg_zerooff,"Zero offsets",
	"*",&arg_infile,"Input file",
	"*",&arg_outfile,"Output file",
	"",0,""
};

void
Parse_CmdLine(int cnt,char *cmdline[])
{
	int					i;
	struct arg_ident	*ptr;

	for (i=1; i<cnt; i++) {
		ptr = &arg_array[0];
		if (cmdline[i][0] == '/' || cmdline[i][0] == '-') {
			while (ptr->cmd[0] != '\0') {
				if (ptr->cmd[0] == cmdline[i][1] && ptr->cmd[0] != '*')
					if (ptr->cmd[1] == '#')
						sscanf(&cmdline[i][2],"%ld",(LONG *)ptr->var);
					else
						*(UBYTE *)ptr->var = TRUE;
				ptr++;
			}
		} else {
			/* Must be a file name */
			while (ptr->cmd[0] != '\0') {
				if (ptr->cmd[0] == '*' && *(char **)ptr->var == NULL) {
					*(char **)ptr->var = cmdline[i];
					break;
				}
				ptr++;
			}
		}
	}
}

void
Print_Usage(char *errstr)
{
	struct arg_ident	*ptr;
	int					fcnt = 0;

	printf("Error: %s.\n%s [",errstr,__EXEFILE__);
	ptr = &arg_array[0];
	while (ptr->cmd[0] != '\0') {
		if (ptr->cmd[0] == '*')
			if (fcnt) {
				fcnt++;
				printf("filename ");
			} else {
				fcnt++;
				printf(" ] filename ");
			}
		else
			printf(" /%s",ptr->cmd);
		ptr++;
	}
	printf("\nVersion %s %s.\n",__DATE__,__TIME__);
	printf("Copyright 1993 Futurescape Productions, All Rights Reserved.\n");
	printf("  %s.\n",__USAGE__);
	ptr = &arg_array[0];
	while (ptr->cmd[0] != '\0') {
		if (ptr->cmd[0] == '*')
			printf("       %s.\n",ptr->usage);
		else
			printf("  /%-4s%s.\n",ptr->cmd,ptr->usage);
		ptr++;
	}
	exit(1);
}

void
Bomb(char *fmt, ...)
{
	va_list	args;

	va_start(args,fmt);
	fprintf(stderr,"%s: ",__EXEFILE__);
	vfprintf(stderr,fmt,args);
	fprintf(stderr,".\n");
	perror("Error");
	va_end(args);
	exit(1);
}

/******************************************************
		Futurescape Productions Sega File Formats

	Background Maps:
		UWORD	Offset to Palette
		UWORD	Offset to Map
		UWORD	Offset to Character Definitions
		???
		Palette:
			WORD	Color Register index
			UWORD	Number of colors
				UWORD	RGB Value (Sega format)
				...
			...Repeat...
			-1		End of list
		Map:
			UWORD	Width of Map
			UWORD	Height of Map
			UWORD	Map[][]
		???	Insert new blocks here.
		Character Definitions:
			UBYTE	32 Bytes per character

	Animation Files:
		UWORD	Offset to Palette
		UWORD	Offset to Animation list
		UWORD	Offset to Animation to Frame catalog
		UWORD	Offset to Frame to Sprite catalog
		UWORD	Offset to Hotspot catalog
		UWORD	Offset to Character Definitions
		UWORD flags
				bit 0 = Scaleable sprite format
				bit 1 = bitmap sprite format
				bit 2 = no flip/color information
				bit 3 = RLE compression
				bit 4 = y stored bitmap
		???
		Palette:
			WORD	Color Register index
			UWORD	Number of colors
				UWORD	RGB Value (Sega format)
				...
			...Repeat...
			-1		End of list
		Animation list:
			UWORD	Number of frames
			UWORD	Offset to first Animation to Frame offset
			...
		Animation to Frame catalog:
			UWORD	Offset to first Frame to Sprite structure
			...
		Frame to Sprite catalog:
			UWORD	Number of sprites in frame
			UWORD	Hotspot catalog offset
				WORD	Y Position on screen (0..n)
				WORD	H size, V Size, Link
				UWORD	Priority, Palette, VFlip, HFlip, Char number
				WORD	X Position on screen (0..n)
			...
		Hotspot catalog:
			UWORD	Number of X,Y pairs
				WORD	X Position
				WORD	Y Position
				...
			...
		Scalable Frame to Sprite catalog:
			UWORD Number of sprites in frame
			UWORD hotspot catalog offset
				WORD Y Position on screen (0..n)
				WORD H size, V Size, Link
				UWORD Priority, Palette, VFlip, HFlip
				WORD x Position on screen

		Bitmap Frame to Sprite catalog:
			UWORD Number of sprites in frame
			UWORD hotspot catalog offset
				WORD Y Position on screen (0..n)
				WORD H size, V Size, Link
				UWORD Priority, Palette, VFlip, HFlip
				WORD x Position on screen

		???	Insert new blocks here.

		*****	Dependant on flags settings *****		
		Character Definitions:
			UBYTE	32 Bytes per character

		Scaleable sprite Definitions
			UBYTE (w * h)/2 Bytes per character
			 format is stored in Y then X sega format.
			
		RLE Compression format:
			This is optimised for quick decompression in the scaler.
		Each scanline:
			BYTE		Bytes to skip to get to next scanline
			BYTE		X offset from left side (BYTEs)
			data...	BYTES of pixel packed image data

 ******************************************************/

void
fwrite_68k_word(UWORD wrd,FILE *file)
{
	fputc(wrd >> 8,file);
	fputc(wrd & 0xFF,file);
}

UWORD
fread_68k_word(FILE *file)
{
	UWORD wrd;

	wrd = fgetc(file) << 8;
	wrd |= fgetc(file) & 0xFF;
	return(wrd);
}

int		total_anims;
int		total_frames[30];
int		total_sprites[30];
int		total_chrs;
int		frame_size;
long		anim_pos;
long		frame_pos[30];
long		sprite_pos[30];
UWORD		sega_palette[256];

unsigned short *table_widths;
unsigned short *table_heights;
int num_shapes;
int palSize = 0;

int palUsed[4];

/**************************************************************************
 *		Code to read DPaint Animate files
 **************************************************************************/

#include <malloc.h>

FILE				*bmp_file;			/* DPaint Animate file */
UBYTE				lppalette[769];	/* anim file palette is loaded here */
UBYTE far		*outbuf;				/* pointer to the output buffer where data is rendered */
UBYTE				backcolor;			/* Background color */
UBYTE				nonbackcolor;			/* Background color */

/* finds the sallest rectangle that will enclose the frame of data */
void
FindEdges(int *LeftEdge, int *TopEdge, int *RightEdge, int *BottomEdge)
{
	UWORD x,y;
	UWORD	foundflag;

	foundflag = FALSE;
	for (x = 0; x < 320 && !foundflag; x++) {
		for (y = 0; y < 200; y++) {
			if (outbuf[(y * 320) + x] != backcolor) {
				nonbackcolor = outbuf[(y * 320) + x];
				foundflag = TRUE;
				break;
			}
		}
	}
	/* x will be incremented before foundflag check */
	*LeftEdge = x-1;
	foundflag = FALSE;
	/* for unsigned words wait till wraps above 319 hack hack hack */
	for (x = 319; x <= 319 && !foundflag; x--) {
		for (y = 0; y < 200; y++) {
			if (outbuf[(y * 320) + x] != backcolor) {
				foundflag = TRUE;
				break;
			}
		}
	}
	/* x will be incremented before foundflag check so 320-(x+1)*/
	*RightEdge = x+1;
	foundflag = FALSE;
	for (y = 0; y < 200 && !foundflag; y++) {
		for (x = 0; x < 320; x++) {
			if (outbuf[(y * 320) + x] != backcolor) {
				foundflag = TRUE;
				break;
			}
		}
	}
	*TopEdge = y-1;
	foundflag = FALSE;
	/* for unsigned words wait till wraps above 199 hack hack hack */
	for (y = 199; y <= 199 && !foundflag; y--) {
		for (x = 0; x < 320; x++) {
			if (outbuf[(y * 320) + x] != backcolor) {
				foundflag = TRUE;
				break;
			}
		}
	}
	*BottomEdge = y+1;

}

/***
 *			High level routines
 *			Only support for one ANM file at a time
 ***/

void
BMP_Open(char *fname, int doDisplay)
{
	long	i;
	UBYTE	tpal;
	FILE	*fp;
	char	tempname[80];

	palSize = 0;
	/* had to use "halloc" because I had to allocate a buffer exactly 64k long */
	if (!outbuf)
		outbuf = (UBYTE far *)halloc(0x10000l,1);	/* allocate output buffer */
	if (!outbuf)
		Bomb("Out of memory allocating output buffer.\n");

   bmp_file = vm_bopen(fname);
   if(!bmp_file || (vm_bfind(bmp_file,"BMP:INF:",0) == -1))
		Bomb("Unable to open %s!\n", fname);

   /* Determine the width and height of the bitmaps */
   my_fread(&num_shapes, 2, 1, bmp_file);

	table_widths = (unsigned short *)malloc(num_shapes*2);
	if (!table_widths)
		Bomb("Out of memory allocating table widths.\n");
   my_fread(table_widths, 2, num_shapes, bmp_file);

	table_heights = (unsigned short *)malloc(num_shapes*2);
	if (!table_heights)
		Bomb("Out of memory allocating table heights.\n");

   my_fread(table_heights, 2, num_shapes, bmp_file);

   /* Load palette by same name */
	if (arg_debug)						
	   printf("\nLoading Palette...");

	strcpy(tempname,fname);
   strcpy(strchr(tempname,'.'),".pal");
   fp = vm_bopen(tempname);
   if(!fp)
      fp = vm_bopen("default.pal");
   if(vm_bfind(fp, "PAL:VGA:", 0) == -1)
      Bomb("Error -- No palette found '%s'\n", tempname);
   else
		fread(&lppalette,256*3,1,fp);		/* read in palette */
   vm_bclose(fp);

   if ((arg_view) && doDisplay) {
		asm {
			mov	ax,1012h;
			xor	bx,bx;
			mov	cx,256;
			mov	dx,seg lppalette;
			mov	es,dx;
			mov	dx,offset lppalette;
			int	10h;
		}
	}
			
	backcolor = 0;
}

int BMP_Render(UWORD frame, int doDisplay, int plane)
{
	short ph;
	unsigned char color;
	long i;
	int  x, y;
	unsigned char far *bptr;
	unsigned char far *bptr2;
	long size;

	bptr = outbuf;
	if (!plane) {
		for(i = 0; i < 65536; i++)
			*(bptr++) = 0;
		backcolor = 0;
	}

   /* Load EGA part of bitmap data */
   bptr = outbuf;
   if(   (vm_bfind(bmp_file, "BMP:BIN:", 1) != -1)
      && ((GBph=vm_pkFopen(0, bmp_file, "r", vm_bsize(bmp_file))) >= 0) )
	{
		size = 0;
		for (i=0;i<frame;i++)
			size += (table_widths[i]/2)*table_heights[i];

		vm_pkseek(GBph, size, SEEK_CUR);
			
		if (arg_debug)
	      printf("Loading BIN block...\n");
      for(y=0;y<table_heights[frame];y++)
      {
			for (x=0;x<table_widths[frame];x+=2)
			{
	         vm_pkread(GBph,&color,1);
	         *bptr++ = color>>4;
	         *bptr++ = color&0xf;
			}
			bptr += 320-table_widths[frame];
      }
	   vm_pkclose(GBph);

   }

   /* Load VGA part of bitmap data */
   bptr = outbuf;
   if(   (vm_bfind(bmp_file, "BMP:VGA:", 1) != -1)
      && ((GVph=vm_pkFopen(0, bmp_file, "r", vm_bsize(bmp_file))) >= 0) )
	{
		size = 0;
		for (i=0;i<frame;i++)
			size += (table_widths[i]/2)*table_heights[i];

		vm_pkseek(GVph, size, SEEK_CUR);
			
		if (arg_debug)
	      printf("Loading VGA block...\n");
      for(y=0;y<table_heights[frame];y++)
      {
			for (x=0;x<table_widths[frame];x+=2)
			{
	         vm_pkread(GVph,&color,1);
	         *bptr++ |= color&0xf0;
   	      *bptr++ |= (color&0xf)<<4;
			}
			bptr += 320-table_widths[frame];
      }
   	vm_pkclose(GVph);
   }

	
	if (arg_genoverlay) {
		x = FALSE;						/* really if anything is found in this plane */
		bptr = outbuf;
		for (i=0;i<65536;i++) {
			if (((*bptr >> 4) & 0x03) == plane)
				x = TRUE;
			else
				*bptr = backcolor;
			bptr++;
		}

		if (x)
			palUsed[plane] = TRUE;
	} else {
		palUsed[(nonbackcolor >> 4) & 3] = TRUE;
		if (!plane)
			x = TRUE;
		else
			x = FALSE;
	}

	bptr = outbuf;
	bptr2 = MK_FP(0xa000,(320*50)+160);	/* let far pointer wrap */
	if ((arg_view) && doDisplay && x) {
		for (i=0;i<65536;i++)
			*bptr2++ = *bptr++;

	while (!kbhit());
	getchar();
	}
	return(x);
}

void
BMP_Close(void )
{
	vm_bclose(bmp_file);
}

/**************************************************************************
 *		End DPaint Animate reader
 **************************************************************************/


UBYTE		Cur_Char[256];		/* Character generated or X/Y scanline */
int		dupsize;

/***
 *		Get_BRLELine:	Get Bitmapped RLE scaline
 *			Returns data packet size
 ***/

int
Get_BRLELine(int scrn_x, int scrn_y, int width)
{
	int			x;
	int			first_x;		/* First non transparent pixel found */
	int			last_x;		/* Last non trnasparent pixel found */
	int			size;			/* Number bytes taken for packed scanline */
	UBYTE far	*ptr;
	UBYTE far	*tptr;
	UBYTE			*bptr;
	UBYTE			tbyte1,tbyte2;

	/* Grab each pixel (currently a BYTE), munge it into a NYBBLE and store
		it in the Cur_Char buffer to be written out. */
	ptr = outbuf;
	ptr += ((long)scrn_y * 320) + (long)scrn_x;
	bptr = Cur_Char;

	/* Find first and last pixel packed BYTE */
	tptr = ptr;
	first_x = -1;
	last_x = -1;
	for (x = 0; x < width / 2; x++) {
		tbyte1 = *tptr++;
		tbyte2 = *tptr++;
		if (tbyte1 == backcolor)
			tbyte1 = 0;
		if (tbyte2== backcolor)
			tbyte2= 0;
		tbyte1 = ((tbyte1 & 0x0F) << 4) | (tbyte2 & 0x0F);
		if (tbyte1) {
			if (first_x == -1)
				first_x = x;
			last_x = x;
		}
	}

	if (first_x == -1) {
		/* Empty scanline, store skip values */
		*bptr++ = 2;		/* BYTEs to skip to get to next scanline */
		*bptr++ = 0;		/* X offset from left side */
		size = 2;
	} else {
		/* BYTEs to skip to get to next scanline */
		*bptr++ = last_x - first_x + 3;
		/* X offset from left side */
		*bptr++ = first_x;
		size = 2;
		ptr += first_x * 2;
		for (x=first_x; x <= last_x; x++) {
			tbyte1 = *ptr++;
			tbyte2 = *ptr++;
			if (tbyte1 == backcolor)
				tbyte1 = 0;
			if (tbyte2== backcolor)
				tbyte2= 0;
			*bptr++ = ((tbyte1 & 0x0F) << 4) | (tbyte2 & 0x0F);
			size++;
		}
	}
	return (size);
}

/***
 *		Walk through the DPaint Animate file and get totals for everything
 ***/

void
Get_Sizes(void)
{
	int		anm_fcnt;			/* Frame counter of ANM file */
	int		ax1,ay1,ax2,ay2;	/* Returned coordinates from FindEdges */
	int		width;				/* Width of Frame in Characters */
	int		height;				/* Height of Frame in Characters */
	int		big_x,big_y;		/* Large sprite variables */
	int		rem_x,rem_y;		/* Remainder sprite variables */
	int		ssize;				/* Number of sprites in current frame */
	int		curInFile;			/*	current input file counter	*/
	int		y;
	int		plane;

	/*	total_anims = 1;	*/		/*	now set in SetFileNames	*/
	for (curInFile = 0; curInFile < total_anims; curInFile++)
		{
		/*	open the current anim	*/
		total_sprites[curInFile] = 0;

		BMP_Open(inFile[curInFile], FALSE);

		total_frames[curInFile] = num_shapes;

		for (anm_fcnt=0; anm_fcnt<total_frames[curInFile]; anm_fcnt++)
			{
			frame_size += 4;		/* 2 Words for every Frame */
			/* Compute size of image */
			if (arg_bitmap || arg_scaled) {
				/* Bitmaps */
				BMP_Render(anm_fcnt, FALSE, 0);
				FindEdges(&ax1,&ay1,&ax2,&ay2);
				width = (ax2 - ax1 + 1) & 0xFFFE;		// align to Byte
				height = ay2 - ay1 + 1;
				total_sprites[curInFile]++;
				frame_size += 8;
				if (arg_rle) {
					/* Compute size of compressed frame */
					ssize = 0;
					for (y=0; y < height; y++)
						ssize += Get_BRLELine(ax1, ay1 + y, width);
					big_x = (ssize + 31) >> 5;
				} else {
					/* 4 Words for every sprite... */
					rem_x = (width >> 1) * height;
					big_x = (rem_x + 31) >> 5;
				}
				total_chrs += big_x;
			} else {
				plane = 0;
				ssize = 0;
				while (BMP_Render(anm_fcnt, FALSE, plane)) {
#if 0
					if (plane)
						FindEdges(&ax1,&ay1,&ax2,&ay2);
					else {
						ax1 = 0;
						ax2 = table_widths[anm_fcnt]-1;
						ay1 = 0;
						ay2 = table_heights[anm_fcnt]-1;
					}
#else
						ax1 = 0;
						ax2 = table_widths[anm_fcnt]-1;
						ay1 = 0;
						ay2 = table_heights[anm_fcnt]-1;
#endif

					plane++;
					/* Normal sprites */
					width = ((ax2-ax1+7)>>3);
					height = ((ay2-ay1+7)>>3);
					/* Generate optimal Genesis sprites */
					big_x = width >> 2;	/* How many 4xN sprites? */
					big_y = height >> 2;	/* How many Nx4 sprites? */
					rem_x = width & 3;	/* Remaining sprite size... */
					rem_y = height & 3;
					ssize += (big_x + (rem_x?1:0)) * (big_y + (rem_y?1:0));
					total_chrs += width * height;
				}
				/* 4 Words for every sprite... */
				total_sprites[curInFile] += ssize;
				frame_size += ssize * 8;
			}
		}
		/*	close the anim file	*/
		BMP_Close();
	}
}

/***
 *		Grab a Sega 8x8 character from the buffer in the proper palette
 ***/

void
Get_Char(int scrn_x, int scrn_y)
{
	int			x,y;
	UBYTE far	*ptr;
	UBYTE			*bptr;
	UBYTE tbyte1, tbyte2;

	/* Grab each pixel (currently a BYTE), munge it into a NYBBLE and store
		it in the Cur_Char buffer to be written out. */
	ptr = outbuf;
	ptr += ((long)scrn_y * 320) + (long)scrn_x;
	bptr = Cur_Char;
	for (y=0; y<8; y++) {
		for (x=0; x<4; x++) {
			tbyte1 = *ptr++;
			tbyte2= *ptr++;
			if (tbyte1 == backcolor)
				tbyte1 = 0;
			if (tbyte2== backcolor)
				tbyte2= 0;
			*bptr++ = ((tbyte1 & 0x0F) << 4) | (tbyte2& 0x0F);
		}
		ptr += 320 - 8;
	}
}

/*
***
*/
void
Get_ScaledYLine(int scrn_x, int scrn_y, int height)
{
	int			y;
	UBYTE far	*ptr;
	UBYTE			*bptr;
	UBYTE tbyte1, tbyte2;

	/* Grab each pixel (currently a BYTE), munge it into a NYBBLE and store
		it in the Cur_Char buffer to be written out. */
	ptr = outbuf;
	ptr += ((long)scrn_y * 320) + (long)scrn_x;
	bptr = Cur_Char;
	for (y=0; y<height/2; y++, bptr++) {

		tbyte1 = *ptr;
		if (tbyte1 == backcolor)
			tbyte1 = 0;
		tbyte2 = *(ptr+320);
		if (tbyte2 == backcolor)
			tbyte2 = 0;
		*bptr = ((tbyte1 & 0x0F) << 4) | (tbyte2 & 0x0F);
		ptr += 640;
	}
}

/*
***
*/
void
Get_BMYLine(int scrn_x, int scrn_y, int height)
{
	int			y;
	UBYTE far	*ptr;
	UBYTE			*bptr;
	UBYTE tbyte1, tbyte2;

	/* Grab sets of 2 pixels in the y direction and store
		it in the Cur_Char buffer to be written out. */

	ptr = outbuf;
	ptr += ((long)scrn_y * 320) + (long)scrn_x;
	bptr = Cur_Char;
	for (y=0; y<height; y++) {
		tbyte1 = *ptr;
		if (tbyte1 == backcolor)
			tbyte1 = 0;
		tbyte2 = *(ptr+1);
		if (tbyte2 == backcolor)
			tbyte2 = 0;
		*bptr++ = ((tbyte1 << 4) | (tbyte2 & 0x0f));
		ptr += 320;
	}
}


/*
***
*/
void
Get_BMXLine(int scrn_x, int scrn_y, int width)
{
	int			x;
	UBYTE far	*ptr;
	UBYTE			*bptr;
	UBYTE tbyte1, tbyte2;

	/* Grab each pixel (currently a BYTE), munge it into a NYBBLE and store
		it in the Cur_Char buffer to be written out. */
	ptr = outbuf;
	ptr += ((long)scrn_y * 320) + (long)scrn_x;
	bptr = Cur_Char;
	for (x=0; x<width/2; x++) {
			tbyte1 = *ptr++;
			tbyte2= *ptr++;
			if (tbyte1 == backcolor)
				tbyte1 = 0;
			if (tbyte2== backcolor)
				tbyte2= 0;
			*bptr++ = ((tbyte1 & 0x0F) << 4) | (tbyte2& 0x0F);
	}
}

/***
 *		Write out NxN Sega Characters from the buffer
 ***/

void
Write_Chars(FILE *file, int sx, int sy, int width, int height)
{
	int	x,y;

	/* Write characters out in Sega Sprite format, Y then X */
	for (x=0; x<width; x++)
		for (y=0; y<height; y++) {
			Get_Char(sx+(x*8),sy+(y*8));
			fwrite(Cur_Char,32,1,file);
		}
}

void
Write_Scaled(FILE *file, int sx, int sy, int width, int height)
{
	int	x;

	/* Write characters out in Sega Scalable format, Y then X */
	for (x=0; x<width; x++) {
		Get_ScaledYLine(sx+x,sy, height);
		fwrite(Cur_Char,height/2,1,file);
		}
}

void
Write_Bitmaps(FILE *file, int sx, int sy, int width, int height)
{
	int	y;

	for (y=0; y<height; y++) {
		Get_BMXLine(sx, sy+y, width);
		fwrite(Cur_Char,width/2,1,file);
	}
}

/*
***
*/
void
Write_YBitmaps(FILE *file, int sx, int sy, int width, int height)
{
	int	x;

	/* Write characters out in Futurescape Y direction bitmap format */
	/* x is already rounded up to even bytes */
	for (x=0; x<width; x+=2) {
		Get_BMYLine(sx+x, sy, height);
		fwrite(Cur_Char,height,1,file);
	}
}


int
Write_RLE(FILE *file, int sx, int sy, int width, int height)
{
	int	y;
	int	size;
	int	total;

	/* Write characters out in Futurescape Scalable format, X then Y */
	total = 0;
	for (y=0; y < height; y++) {
		size = Get_BRLELine(sx, sy+y, width);
		fwrite(Cur_Char,size,1,file);
		total += size;
	}
	return (total);
}

void	SetFileNames(void)
{
FILE	*listFile;

	if (arg_list)
		{
		/*	input file is a text file of anims	*/
		/*	open the file	*/
		if ((listFile = fopen(arg_infile,"r")) == NULL)
			Bomb("Can't open input file '%s'",arg_infile);

		/*	reset file name counter	*/
		total_anims = 0;
		/*	loop through the file until EOF	*/
		while (!feof(listFile))
			{
			/*	read a line of text	*/
			if (fgets(inFile[total_anims],30,listFile))
				{
				inFile[total_anims][strcspn(inFile[total_anims],"\n")] = 0;
				if (strlen(inFile[total_anims]))
					{
					total_anims++;
					strupr(inFile[total_anims]);	/* convert to upper case */
					}
				}
			}
		}
	else
		{
		/*	input file is only anim	*/
		total_anims = 1;
		strcpy(inFile[0],arg_infile);
		}
}

/*********************************************************************/
/* Function:		findDupFrame(int anm_cnt, int frm_cnt, 				*/
/*											FILE *infile);								*/
/* Description:	find out if we already wrote out this frame from	*/
/*						this file and if so seek to data and copy frame		*/
/*						to sprite information into cur_char for writing		*/
/*						later.															*/
/* Parameters:		anm_cnt = current animation count						*/
/*						frm_cnt = current frame count								*/
/*						infile = output file to check								*/
/* Returns:			TRUE - if found duplicate frame							*/
/*********************************************************************/
int findDupFrame(int anm_cnt, int frm_cnt, FILE *infile)
{
	int	i;
	long	curpos;
	int	found;
	UWORD	offset;
	int	j;

	found = FALSE;

	for (i=0; i<anm_cnt; i++)
		if (!strcmp(inFile[i], inFile[anm_cnt]))
			{
			curpos = ftell(infile);					/* save current position */
			fseek(infile, (i*4)+14+38+2, SEEK_SET);	/* get to animation list */
			offset = fread_68k_word(infile);
			offset += frm_cnt<<1;					/* now get to frame offset */
			fseek(infile, offset, SEEK_SET);
			offset = fread_68k_word(infile);
			fseek(infile, offset, SEEK_SET);
			fread(&Cur_Char, 4, 1, infile);
			j = (unsigned int)Cur_Char[0] | (unsigned int)Cur_Char[1];
			dupsize = 4;
			for (found=0;found<j;found++)
				{
				fread(&Cur_Char[dupsize], 8, 1, infile);
				dupsize += 8;
				}
			fseek(infile, curpos, SEEK_SET);
			found = TRUE;
			i = anm_cnt;
			}

	return(found);
}
/***
 *		Main Routine
 ***/

main(int argc,char *argv[])
{
	FILE		*outfile;
	LONG		filelen;
	LONG		curpos, nspritepos;
	LONG		block_size;
	int		i,i2,i3,j,k,l;
	int		x,y;
	int		anim_cnt,frm_cnt;
	UBYTE		*ptr;
	UBYTE		*end_ptr;
	UBYTE		found;
	UWORD		*wptr;
	UWORD		color;
	int		chr_cnt;
	int		scrn_x,scrn_y;
	UBYTE		*chr_ptr;
	UWORD		temp;
	int		total_all_frames,total_all_sprites;

	int		ax1,ay1,ax2,ay2;
	int		anm_fcnt;			/* Frame counter of ANM file */

	outbuf = 0l;
	
	Parse_CmdLine(argc,argv);

	if (arg_infile == NULL)
		Print_Usage("Must use an input file");

	if (arg_outfile == NULL)
		Print_Usage("Must use an output file");

	if (arg_rle && !arg_bitmap)
		Print_Usage("RLE Compression can only be done with bitmaps");

	if (arg_ydir && !arg_bitmap)
		Print_Usage("Y direction storage can only be done with bitmaps");

	if (!arg_view)
		printf("Calculating Final Sizes...\n");

	if ((arg_bitmap) || (arg_scaled))
		arg_genoverlay = FALSE;

	/*	set up for multiple file names	*/
	SetFileNames();

	frame_size = 0;
	Get_Sizes();
	total_all_frames = 0;
	total_all_sprites = 0;
	for (i = 0; i < total_anims; i++)
		total_all_frames += total_frames[i];

	for (i = 0; i < total_anims; i++)
		total_all_sprites += total_sprites[i];

	for (i=0;i<4;i++)
		if (palUsed[i])
			palSize += 16;
		else
			memmove(&lppalette[i*16*3], &lppalette[(i+1)*16*3], 16*3);

	/* Convert ANM palette into Sega colors, only first 64 */
	ptr = lppalette;
	for (i=0; i<palSize; i++) {
		color = (*ptr++ >> 2) & 0xE;
		color |= (*ptr++ << 2) & 0xE0;
		color |= (*ptr++ << 6) & 0xE00;
		sega_palette[i] = color;
		if (arg_debug)
			printf("Color %2d = $%04X\n",i,color);
	}


	if (!arg_view)
		printf("Background Color = %d\n",backcolor);
	/* Write out Futurescape Productions type file */
	if (!arg_view) {
		if (arg_scaled)
			printf("Generating FPS file...\n");
		else
			if (arg_bitmap)
				printf("Generating FPB file...\n");
			else
				printf("Generating FPA file...\n");
		if (arg_rle)
			printf("Using RLE compression...\n");
	}

	if ((outfile = fopen(arg_outfile,"w+b")) == NULL)
		Bomb("Can't open output file '%s'",arg_outfile);
	if (!arg_view) {
		printf("%d Total 8x8 Characters.\n",total_chrs);
		if (total_anims == 1)
			printf("%d Animation, with %d frames.\n",total_anims,total_frames[0]);
		else
			printf("%d Animations, with %d frames.\n",total_anims,total_all_frames);
		printf("%d Total Sega Sprites.\n",total_all_sprites);
	}
	fwrite_68k_word(14,outfile);	/* Offset to palette */
	fwrite_68k_word(14+6+(palSize*2),outfile);	/* Offset to animation list */
	i = 14 + 6+(palSize*2) + (total_anims * 4);
	fwrite_68k_word(i,outfile);	/* Offset to anim to frame catalog */
	i += (total_all_frames * 2);
	fwrite_68k_word(i,outfile);	/* Offset to frame to sprite cat */
	fwrite_68k_word(0,outfile);	/* Offset to hotspots */
	i += frame_size;
	fwrite_68k_word(i,outfile);	/* Offset to characters */
	i = 0;
	if (arg_scaled)
		i |= 1;
	if (arg_bitmap)
		i |= 2;							/* flags = bitmap */
	if (arg_noinfo)
		i |= 4;
	if (arg_rle)
		i |= 8;							/* flags = RLE compression */
	if (arg_ydir)
		i |= 16;							/* flags = y direction storage */

	fwrite_68k_word(i,outfile);	/* flags = not scaled */
		
	/* Write palette */
	if (arg_pal == -1)
		arg_pal = nonbackcolor / 16;
	k = arg_pal*16;
	fwrite_68k_word(k,outfile);
	fwrite_68k_word(palSize,outfile);
	k = nonbackcolor & 0xfff0;
	for (i=0; i<palSize; i++)
		fwrite_68k_word(sega_palette[i],outfile);
	fwrite_68k_word(0xFFFF,outfile);

	if (arg_view)
		asm {
			mov	ax,13h;
			int	10h;
		}

	/* Write blank animation list */
	anim_pos = ftell(outfile);
	block_size = 0l;
	for (i = 0; i < total_anims; i++)
		fwrite(&block_size,4,1,outfile);

	for (i = 0; i < total_anims; i++)
		{
		/* Write blank frame list */
		frame_pos[i] = ftell(outfile);

		for (i2 = 0; i2 < total_frames[i]; i2++)
			fwrite(&block_size,2,1,outfile);

		/* Write blank sprite sprite list */
		sprite_pos[i] = ftell(outfile);

		for (i2 = 0; i2 < total_frames[i]; i2++)
			fwrite(&block_size,4,1,outfile);	/*	num sprs, hotspot offset	*/

		for (i3 = 0; i3 < total_sprites[i]; i3++)
			{
			fwrite(&block_size,4,1,outfile);	/*	spr data	*/
			fwrite(&block_size,4,1,outfile);	/*	spr data	*/
			}
		}

	fwrite_68k_word(total_chrs,outfile);

	/* Update all blank lists */
	anim_cnt = chr_cnt = 0;
	color = arg_pal << 13;		/* Use as a mask for setting Chars Palette # */

	for (anim_cnt=0; anim_cnt<total_anims; anim_cnt++) {
		/*	open this animation	*/
		BMP_Open(inFile[anim_cnt], TRUE);

		k = total_frames[anim_cnt];		/* k = total frames for this anim */
		/* Update animation pointer */
		curpos = ftell(outfile);

		fseek(outfile,anim_pos,SEEK_SET);
		fwrite_68k_word(k,outfile);
		fwrite_68k_word(frame_pos[anim_cnt],outfile);
		anim_pos += 4;
		fseek(outfile,curpos,SEEK_SET);
		if (!arg_view) {
			printf("Creating Animation #%d.\n",anim_cnt);
			Tick_Init();
		}
		for (frm_cnt=0; frm_cnt<k; frm_cnt++) {
			int	big_x,big_y;		/* Large sprite variables */
			int	rem_x,rem_y;		/* Remainder sprite variables */
			int	x,y;
			int	xs,ys;				/* X,Y position of the current screen chr */
			int	ax1,ay1,ax2,ay2;	/* Box around current frame */
			int	tax1, tay1;			/* temporary offset in frame */
			int	width;				/* Width in characters of frame */
			int	height;				/* Height in characters of frame */
			int	num_sprs;			/* Number of sprites for this frame */
			int	plane;

			/* Update frame offset */
			curpos = ftell(outfile);

			fseek(outfile,frame_pos[anim_cnt],SEEK_SET);	/* seek to anim to frame offsets */
			fwrite_68k_word(sprite_pos[anim_cnt],outfile);	/* write offset */
			frame_pos[anim_cnt] += 2;							/* update frame position */
			fseek(outfile,curpos,SEEK_SET);

			/*
			** Find duplicate frame if already written
			*/
			i2 = findDupFrame(anim_cnt, frm_cnt, outfile);
			/*
			** if one was found just copy frame to sprite catalog
			**	size = 12 bytes for frame to sprite catalog
			*/
			if (i2)	{
				curpos = ftell(outfile);
				fseek(outfile,sprite_pos[anim_cnt],SEEK_SET);
				fwrite(Cur_Char, dupsize, 1 ,outfile);
				fseek(outfile,curpos,SEEK_SET);
				sprite_pos[anim_cnt] += dupsize;
			} else if (arg_scaled) {
				BMP_Render(frm_cnt, TRUE, 0);
				FindEdges(&ax1,&ay1,&ax2,&ay2);
				width = ((ax2-ax1+1) & 0xfffe);		// align to byte
				height = ((ay2-ay1+1) & 0xfffe);
				if (frm_cnt == 0) {
					if (((anim_cnt != 0) && (arg_oneoffset == FALSE)) ||
							(anim_cnt == 0))	{
						/* Set origin (at middle bottom of first frame) */
						scrn_x = ax1 + width/2;
						scrn_y = ay1 + height;
					}
				}
				if (arg_zerooff) {
					scrn_x = ax1;
					scrn_y = ay1;
				}

				curpos = ftell(outfile);
				fseek(outfile,sprite_pos[anim_cnt],SEEK_SET);
				fwrite_68k_word(1,outfile); 		/* number of sprites in frame */
				fwrite_68k_word(0,outfile);		/* hotspot catalog offset */
				fwrite_68k_word(ay1 - scrn_y,outfile);		// write y Position
				temp = (((UWORD)(height) << 8) | (width & 0xff));
				fwrite_68k_word(temp,outfile);				// and h&v size
				fwrite_68k_word(chr_cnt | color,outfile);
				fwrite_68k_word(ax1 - scrn_x,outfile);
				sprite_pos[anim_cnt] += 12;
				fseek(outfile,curpos,SEEK_SET);
				Write_Scaled(outfile,ax1,ay1,width,height);
				big_x = (((ax2-ax1+7) & 0xfff8)>>3) * 
									(((ay2-ay1+7) & 0xfff8) >>3);
				chr_cnt += big_x;
				rem_x = (width>>1)*height;
				big_x = big_x<<5;
				if (rem_x < big_x)
					fwrite(Cur_Char,(big_x-rem_x),1,outfile);
			} else if (arg_bitmap) {
				BMP_Render(frm_cnt, TRUE, 0);
				FindEdges(&ax1,&ay1,&ax2,&ay2);
				width = ((ax2 - ax1 + 1) & 0xFFFE);		// align to Byte
				height = ay2 - ay1 + 1;
				if (frm_cnt == 0) {
					if (((anim_cnt != 0) && (arg_oneoffset == FALSE)) ||
							(anim_cnt == 0))	{
						/* Set origin (at middle bottom of first frame) */
						scrn_x = ax1 + (width/2);
						scrn_y = ay1 + height;
					}
				}
				if (arg_zerooff) {
					scrn_x = ax1;
					scrn_y = ay1;
				}

				curpos = ftell(outfile);
				fseek(outfile,sprite_pos[anim_cnt],SEEK_SET);
				temp = (((UWORD)(width) << 8) | (height & 0xff));
				fwrite_68k_word(1,outfile); 		/* number of sprites in frame */
				fwrite_68k_word(0,outfile);		/* hotspot catalog offset */
				fwrite_68k_word(ay1 - scrn_y,outfile);		// write y Position
				fwrite_68k_word(temp,outfile);				// and h&v size
				fwrite_68k_word(chr_cnt | color,outfile);
				fwrite_68k_word(ax1 - scrn_x,outfile);
				sprite_pos[anim_cnt] += 12;
				fseek(outfile,curpos,SEEK_SET);
				if (arg_rle) {
					rem_x = Write_RLE(outfile,ax1,ay1,width,height);
					/* Pad file */
					big_x = (rem_x + 31) & 0xFFE0;
					chr_cnt += big_x >> 5;
				} else if (arg_ydir) {
					Write_YBitmaps(outfile,ax1,ay1,width,height);
					/* Pad file */
					rem_x = (width >> 1) * height;
					big_x = (rem_x + 31) & 0xFFE0;
					chr_cnt += big_x >> 5;
				} else {
					Write_Bitmaps(outfile,ax1,ay1,width,height);
					/* Pad file */
					rem_x = (width >> 1) * height;
					big_x = (rem_x + 31) & 0xFFE0;
					chr_cnt += big_x >> 5;
				}
					
				/* Write pad to file */
				if (rem_x < big_x) {
					memset(Cur_Char,0,256);
					fwrite(Cur_Char,(big_x-rem_x),1,outfile);
				}
			} else {
				nspritepos = sprite_pos[anim_cnt];
				sprite_pos[anim_cnt] += 4;
				plane = 0;
				num_sprs = 0;
				while (BMP_Render(frm_cnt, TRUE, plane)) {
					curpos = ftell(outfile);
#if 0
					if (plane)
						FindEdges(&ax1,&ay1,&ax2,&ay2);
					else {
						ax1 = 0;
						ax2 = table_widths[frm_cnt]-1;
						ay1 = 0;
						ay2 = table_heights[frm_cnt]-1;
					}
#else
						ax1 = 0;
						ax2 = table_widths[frm_cnt]-1;
						ay1 = 0;
						ay2 = table_heights[frm_cnt]-1;
#endif

					width = ((ax2-ax1+7)>>3);
					height = ((ay2-ay1+7)>>3);
					/* Write out Sprites */
					if (frm_cnt == 0) {
						if (((anim_cnt != 0) && (arg_oneoffset == FALSE)) ||
								(anim_cnt == 0))	{
							/* Set origin (at middle bottom of first frame) */
							scrn_x = ax1 + (width * 4);
							scrn_y = ay1 + (height * 8);
						}
					}
					/* Generate optimal Genesis sprites */
					big_x = width >> 2;
					big_y = height >> 2;
					rem_x = width & 3;
					rem_y = height & 3;
					num_sprs += (big_x + (rem_x?1:0)) * (big_y + (rem_y?1:0));

					tax1 = ax1;
					tay1 = ay1;
					if (arg_zerooff) {
						tax1 = scrn_x;
						tay1 = scrn_y;
					}
					fseek(outfile,curpos,SEEK_SET);
					ys = 0;
					while (big_y) {
						xs = 0;
						while (big_x) {
							/* Generate 4x4 sprite */
							curpos = ftell(outfile);
							fseek(outfile,sprite_pos[anim_cnt],SEEK_SET);
							fwrite_68k_word(tay1 - scrn_y + ys,outfile);	// write y Position
							fwrite_68k_word(0x0F00,outfile);					// and h&v size
							fwrite_68k_word(chr_cnt | (color+plane << 13),outfile);
							fwrite_68k_word(tax1 - scrn_x + xs,outfile);
							sprite_pos[anim_cnt] += 8;
	
							fseek(outfile,curpos,SEEK_SET);
							Write_Chars(outfile,ax1+xs,ay1+ys,4,4);
							big_x--;
							xs += 4*8;
							chr_cnt += 16;
						}
						if (rem_x) {
							/* Generate Nx4 sprite */
							curpos = ftell(outfile);
							fseek(outfile,sprite_pos[anim_cnt],SEEK_SET);
							fwrite_68k_word(tay1 - scrn_y + ys,outfile);
							fwrite_68k_word( (((rem_x-1) << 2) + 3) << 8 ,outfile);
							fwrite_68k_word(chr_cnt | (color+plane << 13),outfile);
							fwrite_68k_word(tax1 - scrn_x + xs,outfile);
							sprite_pos[anim_cnt] += 8;
							fseek(outfile,curpos,SEEK_SET);
							Write_Chars(outfile,ax1+xs,ay1+ys,rem_x,4);
							chr_cnt += 4 * rem_x;
						}
						big_x = width >> 2;
						big_y--;
						ys += 4*8;
					}
					if (rem_y) {
						xs = 0;
						while (big_x) {
							/* Generate 4xN sprite */
							curpos = ftell(outfile);
							fseek(outfile,sprite_pos[anim_cnt],SEEK_SET);
							fwrite_68k_word(tay1 - scrn_y + ys,outfile);
							fwrite_68k_word(((rem_y-1) + 0xC) << 8,outfile);
							fwrite_68k_word(chr_cnt | (color+plane << 13),outfile);
							fwrite_68k_word(tax1 - scrn_x + xs,outfile);
							sprite_pos[anim_cnt] += 8;
							fseek(outfile,curpos,SEEK_SET);
							Write_Chars(outfile,ax1+xs,ay1+ys,4,rem_y);
							chr_cnt += 4 * rem_y;
							big_x--;
							xs += 4*8;
						}
						if (rem_x) {
							/* Generate NxN sprite */
							curpos = ftell(outfile);
							fseek(outfile,sprite_pos[anim_cnt],SEEK_SET);
							fwrite_68k_word(tay1 - scrn_y + ys,outfile);
							fwrite_68k_word((((rem_x-1) << 2) | rem_y-1) << 8,outfile);
							fwrite_68k_word(chr_cnt | (color+plane << 13),outfile);
							fwrite_68k_word(tax1 - scrn_x + xs,outfile);
							sprite_pos[anim_cnt] += 8;
							fseek(outfile,curpos,SEEK_SET);
							Write_Chars(outfile,ax1+xs,ay1+ys,rem_x,rem_y);
							chr_cnt += rem_x * rem_y;
						}
					}
					curpos = ftell(outfile);
					fseek(outfile,nspritepos,SEEK_SET);
					fwrite_68k_word(num_sprs,outfile);
					fwrite_68k_word(0,outfile);		/* hotspot catalog offset */
					fseek(outfile,curpos,SEEK_SET);
					plane++;
				}
			}
			if (arg_debug)
				printf("# Planes = %d\n",plane);
			
			if (!arg_view)
				Tick_User((long)frm_cnt,(long)k);
		}
		/*	close the current animation	*/
		BMP_Close();
		if (!arg_view)
			Tick_Exit();
	}
	fclose(outfile);

	hfree(outbuf);
	free(table_widths);
	free(table_heights);

	if (arg_view)
		asm {
			mov	ax,03;
			int	10h;
		}

	return 0;
}


