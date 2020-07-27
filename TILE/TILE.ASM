;{----------------------------------------------------------------------}
;{ Module:	TILE.ASM						}
;{ Description:	tileize an IFF file into a Futurescape Productions type	}
;{		file.							}
;{ Part of:	TILE.COM						}
;{ Original:	Kenneth L. Hurley					}
;{ Date:	10/31/93						}
;{----------------------------------------------------------------------}
;{		*** Copyright 1993 Futurescape Productions ***		}
;{----------------------------------------------------------------------}

;{----------------------------------------------------------------------}
;{ includes section							}
;{----------------------------------------------------------------------}
		include dos.inc

;{----------------------------------------------------------------------}
;{ equates section							}
;{----------------------------------------------------------------------}
RETURN_AOK	equ	0
RETURN_NOARG	equ	1
RETURN_NOPEN	equ	2
RETURN_INTERNAL	equ	3
RETURN_INVALIDF	equ	4
RETURN_INVALIDP	equ	4

;{----------------------------------------------------------------------}
;{ macros section							}
;{----------------------------------------------------------------------}
pushall		macro
		push	bx
		push	cx
		push	dx
		push	bp
		push	si
		push	di
		push	ds
		push	es
		endm

popall		macro
		pop	es
		pop	ds
		pop	di
		pop	si
		pop	bp
		pop	dx
		pop	cx
		pop	bx
		endm

;{----------------------------------------------------------------------}
;{ structures								}
;{----------------------------------------------------------------------}
HeaderRtns	struc
header		db	4 dup (?)	; the actual header information
theRoutine	dw	?		; routine to call to handle header
HeaderRtns	ends

BMHDstruc	struc
widthPixels	dw	?		; width of bitmap
heightPixels	dw	?		; height of bitmap
originalX	dw	?		; original x position
originalY	dw	?		; original y position
nPlanes		db	?		; # planes
masking		db	?		; masking type
compression	db	?		; compression type
pad1		db	?		; pad byte
trclr		dw	?		; transparent color
xAspect		db	?		; x aspect ratio
yAspect		db	?		; y aspect ratio
pWidth		dw	?		; original page Width
pHeight		dw	?		; original page Height
BMHDstruc	ends

;{----------------------------------------------------------------------}
;{ global variables							}
;{----------------------------------------------------------------------}
dseg		segment	'FARDATA'

IFFheadRtns	HeaderRtns	<"FORM", offset flagForm>
		HeaderRtns	<"PBM ", offset flagPBM>
		HeaderRtns	<"IBLM", offset flagILBM>
		HeaderRtns	<"BMHD", offset ReadBMHD>
		HeaderRtns	<"CMAP", offset ReadCMAP>
		HeaderRtns	<"BODY", offset ReadBody>
NHEADERS	equ	($-IFFheadRtns)/size HeaderRtns

headerStr	db	'Convert IFF files to FSC tile files ',CR,LF
		db	'version ', ??DATE, ' ', ??TIME, CR,LF
		db	'Copyright 1993 Futurescape Productions',CR,LF
		db	'$'
UsageStr	db	'Usage: tile.exe [-c w h ]<inputfile> <outputfile>',CR,LF
		db	'       -c w h = clip picture to w h',CR,LF
		db	'$'

OpenError	db	"Unable to open file ->$"
InternalError	db	"Internal Error!$"
EOL		db	CR,LF,"$",0
InvalidFile	db	" doesn't seem to be an IFF file.",CR,LF,"$",0
BitmapHeadErr	db	"Bitmap Header is wrong size, newer version perhaps?"
		db	CR,LF,"$",0
InvalidParm	db	"Error: Invalid parameter.",CR,LF,'$',0
CompressError	db	"I don't know how to handle the compression on this"
		db	"  file.",CR,LF,'$',0
fileSize	dd	?
infile		db	80 dup (?)
outfile		db	80 dup (?)
palBuff		dw	64 dup (0)	; sega palette buffer
PBMFlag		db	?
FORMflag	db	?
BMHDData	BMHDstruc	<>

clipWidth	dw	?
clipHeight	dw	?

tempPalPtr	dd	?

dseg		ends

;{----------------------------------------------------------------------}
;{ some stack space please						}
;{----------------------------------------------------------------------}
_STACK		segment	byte public STACK 'STACK' ; end of program locator
		db	100 dup ('STACK')
_STACK		ends

;{----------------------------------------------------------------------}
;{ start of code section						}
;{----------------------------------------------------------------------}
cseg		segment	'CODE'

		assume	cs:cseg,ds:dseg

start:
		call	far ptr init		; initialize system

		mov	ah,PRINTSTR
		mov	dx,seg headerStr
		mov	ds,dx
		mov	dx,offset headerStr
		int	MSDOS

		call	far ptr parsecl		; parse the command line
		jnc	@@FoundParm		; must have at least one parm.
ShowUsage:
		mov	dx,seg UsageStr
		mov	ds,dx
		mov	dx,offset UsageStr
		mov	al,RETURN_NOARG
		jmp	ErrorExit
@@FoundParm:
		mov	ds,ax
		cmp	byte ptr [bx],'-'
		je	@@IsSwitch
		cmp	byte ptr [bx],'/'
		jne	@@IsFile
@@IsSwitch:
		mov	cl,byte ptr [bx+1]
		cmp	cl,'c'
		jne	@@NotClipParm

		call	far ptr parsecl		; get width parameter
		jc	ShowUsage

		call	far ptr atoi		; convert to integer
		mov	bx,seg clipWidth
		mov	ds,bx
		mov	clipWidth,ax

		call	far ptr parsecl		; and get height parameter
		jc	ShowUsage

		call	far ptr atoi
		mov	clipHeight,ax		; and save it

		
		call	far ptr parsecl		; get width parameter
		jc	ShowUsage
		jmp	@@isFile		; found valid file name

@@NotClipParm:
		mov	dx,seg InvalidParm
		mov	ds,dx
		mov	dx,offset InvalidParm
		mov	ax,RETURN_INVALIDP
		jmp	ErrorExit
@@isFile:
		mov	cx,ax
		mov	dx,bx
		mov	ax,seg infile
		mov	bx,offset infile
		call	far ptr strcpy		; because DTA kill command line

		call	far ptr parsecl
		jc	@@NoSecondName

		mov	cx,ax
		mov	dx,bx
		mov	ax,seg outfile		; save output file name
		mov	bx,offset outfile
		call	far ptr strcpy

@@NoSecondName:
		
		mov	ax,seg infile
		mov	bx,offset infile
		call	far ptr loadmem		; load and allocate memory
		or	ax,ax
		je	@@OpenOk
		mov	dx,seg OpenError
		mov	ds,dx
		mov	dx,offset OpenError
		mov	ah,PRINTSTR
		int	MSDOS
		mov	ax,seg infile
		mov	bx,offset infile
		mov	cx,seg EOL
		mov	dx,offset EOL
		call	far ptr strcat
		mov	dx,seg infile
		mov	ds,dx
		mov	dx,offset infile
		mov	ax,RETURN_NOPEN
		jmp	ErrorExit
@@OpenOk:
		mov	si,di
		mov	di,es
		mov	ds,di
		mov	ax,seg fileSize
		mov	es,ax
		mov	word ptr es:fileSize,cx
		mov	word ptr es:fileSize+2,bx ; save file size for counter
;
; ----- ds:si now contains pointer to file
;
@@NextHeader:
		mov	cx,NHEADERS
		mov	di,offset IFFheadRtns
@@CheckLoop:
		cmpsw
		jne	@@NotThisHeader
		cmpsw
		je	@@FoundHeader
		sub	si,2
		sub	di,2
@@NotThisHeader:
		sub	si,2
		add	di,4
		loop	@@CheckLoop

		add	si,4			; back to length

		cmp	es:Formflag,TRUE	; didn't find 'FORM'
		je	@@ValidFile		; ???

		mov	ax,seg infile		; invalid file then
		mov	ds,ax
		mov	bx,offset infile
		mov	cx,seg InvalidFile
		mov	dx,offset InvalidFile
		call	far ptr strcat
		mov	dx,offset infile
		mov	ax,RETURN_INVALIDF
		jmp	short ErrorExit

@@ValidFile:
		call	near ptr SkipChunk
		jmp	short @@SkipCall
@@FoundHeader:
		call	word ptr es:[di]	; call routine
		fartohuge si,ds			; convert to huge pointer
@@SkipCall:
		mov	ax,word ptr es:fileSize
		or	ax,word ptr es:fileSize+2
		je	@@AllDone
		jmp	@@NextHeader

@@AllDone:
		mov	ax,(PTERM SHL 8) OR RETURN_AOK
		int	MsDos
ErrorExit:
		mov	bl,al
		cmp	cs:VideoMode,0
		je	NoReset2
		mov	ax,3
		int	VideoIO
NoReset2:
		mov	ah,PRINTSTR
		int	MSDOS
		mov	al,bl
		mov	ah,PTERM
		int	MSDOS

VideoMode	db	0

SkipChunk:
		sub	word ptr es:fileSize,4
		sbb	word ptr es:fileSize+2,0 ; adjust count
		lodsw
		mov	dx,ax
		lodsw
		xchg	ah,al
		xchg	dh,dl
		mov	bx,ax			; save offset
		add	ax,4
		adc	dx,0
		sub	word ptr es:fileSize,ax
		sbb	word ptr es:fileSize+2,dx	; skip this headers size
		mov	ax,bx
		longtopara dx,ax		; convert to paragraph offset
		mov	dx,ds
		add	dx,ax			; add in paragraph offset
		mov	ds,dx
		and	bx,0fh
		add	si,bx
		ret

flagForm:
		mov	es:Formflag,TRUE
skipHeader:
		add	si,4
		sub	word ptr es:fileSize,8
		sbb	word ptr es:fileSize+2,0 ; skip this headers size
		ret
flagPBM:
		mov	es:PBMflag,TRUE
		sub	word ptr es:fileSize,4
		sbb	word ptr es:fileSize+2,0 ; skip this headers size
		ret
flagILBM:
		mov	es:PBMflag,FALSE
		sub	word ptr es:fileSize,4
		sbb	word ptr es:fileSize+2,0 ; skip this headers size
		ret
readBMHD:
		lodsw
		mov	dx,ax
		lodsw				; bypass size of chunk
		xchg	ah,al
		xchg	dh,dl
		or	dx,dx
		jne	@@BMHDError
		cmp	ax,size BMHDstruc
		jne	@@BMHDError		; see if same as we know it
		add	ax,8
		adc	dx,0
		sub	word ptr es:fileSize,ax	; reduce whats left in file
		sbb	word ptr es:fileSize+2,dx
		mov	di,offset BMHDData
		lodsw				; get width in pixels
		xchg	ah,al
		stosw
		lodsw				; and height 
		xchg	ah,al
		stosw				
		lodsw				; get original x position
		xchg	ah,al
		stosw
		lodsw				; get original y position
		xchg	ah,al
		stosw
		movsw				; move nplanes/masking
		movsw				; move compression/pad
		lodsw				; get transparent color
		xchg	ah,al
		stosw
		movsw				; move x/y aspect bytes
		lodsw				; get page width
		xchg	ah,al
		stosw
		lodsw				; and page height
		xchg	ah,al
		stosw
		cmp	es:BMHDData.compression,0 ; uncompressed
		je	short @@BMHDOK
		cmp	es:BMHDData.compression,1 ; or byte- RLE
		je	short @@BMHDOK
		mov	dx,seg CompressError
		mov	dx,offset CompressError
		jmp	ErrorExit
@@BMHDOK:
		ret
@@BMHDError:
		mov	dx,seg BitmapHeadErr
		mov	ds,dx
		mov	dx,offset BitmapHeadErr
		jmp	ErrorExit
readCMAP:
		mov	word ptr es:tempPalPtr,si
		mov	word ptr es:tempPalPtr+2,ds ; save palette pointer
		jmp	SkipChunk
readBody:
		mov	ax,es:BMHDData.widthPixels ; number of pixels per scan line
		shr	ax,1			; << 3(*8) >> 4 for paragraphs
		inc	ax			; + 1 for padding
		call	far ptr malloc		; allocate a buffer of 
						; 1 character scan line high
		jmp	SkipChunk


;{----------------------------------------------------------------------}
;{ Function:	unpakLine						}
;{ Description:	unpack an IFF line to a buffer				}
;{ Parameters:	ax = size of line in bytes				}
;{		ds:si = source buffer					}
;{ 		es:di = destination buffer				}
;{ Returns:	.							}
;{----------------------------------------------------------------------}
unpakIFFLine	Proc	Near

		push	cx
		push	dx
		mov	dx,ax			; into counter register
@@unpakLoop:
		lodsb				; get byte
		xor	ch,ch
		cmp	al,80h			; is less < 80h
		jg	@@IsRun
		je	@@Nop
		inc	al
		mov	cl,al
		shr	cx,1
		rep	movsw			; copy literal data
		adc	cx,cx			; really, really fast
		rep	movsb
@@IsRun:
		cbw
		neg	ax			; repeated data
		add	ax,257
		mov	cx,ax
		lodsb	      			; get repeat byte
		mov	ah,al
		shr	cx,1
		rep	stosw			; and store to destination
		adc	cx,cx
		rep	stosb
@@Nop:
		dec	dx
		jne	@@unpakLoop
		
		pop	dx
		pop	cx
		ret

unpakIFFLine	Endp

cseg		ends

		end	start

