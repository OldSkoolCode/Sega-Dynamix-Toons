/***
 *	ROM Based file I/O system
 *	Copyright 1994 Futurescape Productions
 *	All Rights Reserved
 *		History:
 *		02/10/94	KLM, Started coding.
 ***/

#define	__EXEFILE__		"ROMDOS"
#define	__USAGE__		"ROM Based file system"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include	<dir.h>
#include "tools.h"

typedef struct file_ident {
	char	name[12];
	LONG	length;
} FILE_IDENT;

#define	MAXBUFF	16384

char	buffer[MAXBUFF];
LONG	arg_add = 0l;
LONG	arg_view = 0l;
char	*arg_infile = NULL;
char	*arg_outfile = NULL;

struct arg_ident {
	char	*cmd;
	void	*var;
	char	*usage;
} arg_array[] = {
	"a",&arg_add,"Add a file to the file system",
	"v",&arg_view,"View the names and lengths of the file in a file system",
	"*",&arg_outfile,"Name of the file system",
	"*",&arg_infile,"Input file for add (wildcards may be used)",
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
						*(BYTE *)ptr->var = TRUE;
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
				printf("] filename ");
			}
		else
			printf(" /%s ",ptr->cmd);
		ptr++;
	}
	printf("\nVersion %s %s.\n",__DATE__,__TIME__);
	printf("Copyright 1994 Futurescape Productions, All Rights Reserved.\n");
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

void
CVTLNG(LONG *lng, void *ptr)
{
	register unsigned char *pn;
	register unsigned char *pc;

	pn = (unsigned char *)lng;
	pc = (unsigned char *)ptr;
	pc += 3;
	*pn++ = *pc;
	*pn++ = *--pc;
	*pn++ = *--pc;
	*pn = *--pc;
}

void
CVTWRD(WORD *wrd, void *ptr)
{
	register unsigned char *pn;
	register unsigned char *pc;

	pn = (unsigned char *)wrd;
	pc = (unsigned char *)ptr;
	pc += 1;
	*pn++ = *pc;
	*pn = *--pc;
}

void
main(int	argc,char *argv[])
{
	FILE				*infile;
	FILE				*outfile;
	LONG				in_filelen;
	LONG				in_curpos;
	LONG				out_filelen;
	LONG				out_curpos;
	LONG				tlength;
	struct ffblk	ffblk;
	int				done;
	FILE_IDENT		cur_file_id;
	char				name[13];
	WORD				twrd;
	WORD				num_files;

	infile = NULL;
	Parse_CmdLine(argc,argv);
	if (arg_add && arg_view)
		Print_Usage("Must use add or view flag, not both");
	if (arg_outfile == NULL)
		Print_Usage("Must use a file system file name");
	if (arg_add && arg_infile == NULL)
		Print_Usage("Must use an input file");
	if ((outfile = fopen(arg_outfile,"r+b")) == NULL) {
		/* File may not exist, so create one */
		if ((outfile = fopen(arg_outfile,"wb")) == NULL)
			Bomb("Can't open output file '%s'",arg_outfile);
		num_files = 0;
		if (fwrite(&num_files, sizeof(WORD), 1, outfile) != 1)
			Bomb("\nError writing to file %s", arg_outfile);
		fclose(outfile);
		if ((outfile = fopen(arg_outfile,"r+b")) == NULL)
			Bomb("Can't open output file '%s'",arg_outfile);
	}
	/* Get the length of the output file */
	fseek(outfile,0l,SEEK_END);
	out_filelen = ftell(outfile);
	/* Read in number of files word */
	fseek(outfile,0l,SEEK_SET);
	if (fread(&twrd, sizeof(WORD), 1, outfile) != 1)
		Bomb("\nError reading from file %s", arg_outfile);
	CVTWRD(&num_files,&twrd);

	name[12] = '\0';
	if (arg_view) {
		printf("%d Files in file system.\n",num_files);
		fseek(outfile,2l,SEEK_SET);
		printf("\tName\t\tLength\n");
		printf("\t============\t========\n");
		out_filelen -= sizeof(WORD);
		while (out_filelen != 0) {
			if (fread(&cur_file_id, sizeof(FILE_IDENT), 1, outfile) != 1)
				Bomb("\nError reading from file %s", arg_outfile);
			CVTLNG(&tlength,&cur_file_id.length);
			memcpy(&name,&cur_file_id.name,12);
			printf("\t%12s\t%ld\n",name,tlength);
			if (tlength & 1)
				tlength += 1;
			fseek(outfile,tlength,SEEK_CUR);
			out_filelen -= tlength + sizeof(FILE_IDENT);
		}
		exit(0);
	}
	if (arg_add) {
		fseek(outfile,0l,SEEK_END);
		done = findfirst(arg_infile,&ffblk,0);
		while (!done) {
			infile = fopen(&ffblk.ff_name,"rb");
			printf("Adding %s to the file system %s...\n",&ffblk.ff_name,
				arg_outfile);
			/* Get the length of the input file */
			fseek(infile,0l,SEEK_END);
			in_filelen = ftell(infile);
			fseek(infile,0l,SEEK_SET);
			/* Copy the file into the file system */
			memset(&cur_file_id.name,0,12);
			memcpy(&cur_file_id.name,&ffblk.ff_name,12);
			CVTLNG(&cur_file_id.length,&in_filelen);
			if (fwrite(&cur_file_id, sizeof(FILE_IDENT), 1, outfile) != 1)
				Bomb("\nError writing to file %s", arg_outfile);
			while (in_filelen != 0) {
				tlength = in_filelen;
				if (in_filelen > MAXBUFF)
					tlength = MAXBUFF;
				if (fread(buffer, tlength, 1, infile) != 1)
					Bomb("\nError reading file %s", &ffblk.ff_name);
				/* pad to word boundaries */
				in_filelen -= tlength;
				if (tlength & 1)
					tlength += 1;
				if (fwrite(buffer, tlength, 1, outfile) != 1)
					Bomb("\nError writing to file %s", arg_outfile);
			}
			fclose(infile);
			/* Bump number of files */
			num_files++;
			done = findnext(&ffblk);
		}
		fflush(outfile);
		fseek(outfile,0l,SEEK_SET);
		CVTWRD(&twrd,&num_files);
		if (fwrite(&twrd, sizeof(WORD), 1, outfile) != 1)
			Bomb("\nError writing to file %s", arg_outfile);
		printf("twrd = %d num_files = %d\n",twrd,num_files);
		fseek(outfile,0l,SEEK_END);
	}
	fclose(outfile);
}

