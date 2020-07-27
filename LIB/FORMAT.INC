;
; ----- DMA queue structure
;
		OFFSET	0
VRAMADDRESS	ds.w	1		; address in vram
VRAMLENGTH	ds.w	1		; length to dma in bytes
SRCADDR		ds.l	1		; source address
SIZEDMASTRUCT	equ	*-VRAMADDRESS


;	Background Maps:
;		UWORD	Offset to Palette
;		UWORD	Offset to Map
;		UWORD	Offset to Character Definitions
;		???
;		Palette:
;			WORD	Color Register index
;			UWORD	Number of colors
;				UWORD	RGB Value (Sega format)
;				...
;			...Repeat...
;			-1		End of list
;		Map:
;			UWORD	Width of Map
;			UWORD	Height of Map
;			UWORD	Map[][]
;		???	Insert new blocks here.
;		Character Definitions:
;			UWORD 	Number of characters
;			BYTE	32 Bytes per character

;{----------------------------------------------------------------------}
;{									}
;{	Animated background Maps:					}	}
;{		UWORD	Offset to Palette				}
;{		UWORD	Offset to Map					}
;{		UWORD	Offset to Character Definitions			}
;{		UWORD	Offset to Map B					}
;{		UWORD	Offset to Obstical Map				}
;{		UWORD	Offset to Animated Map Info			}
;{		???							}
;{		Palette:						}
;{			WORD	Color Register index			}
;{			UWORD	Number of colors			}
;{				UWORD	RGB Value (Sega format)		}
;{				...					}
;{			...Repeat...					}
;{			-1		End of list			}
;{		MapInfo:						}
;{			UWORD	nframes					}
;{				UWORD xoffset;				}
;{				UWORD yoffset;				}
;{				UWORD mapoffset;			}
;{				UWORD startchar;			}
;{				UWORD numchars;				}
;{			...Repeat nframes...				}
;{									}
;{		Map:							}
;{			UWORD	Width of Map				}
;{			UWORD	Height of Map				}
;{			UWORD	Map[][]					}
;{		???	Insert new blocks here.				}
;{		Character Definitions:					}
;{			UWORD 	Number of characters			}
;{			BYTE	32 Bytes per character			}
;{									}
;{----------------------------------------------------------------------}

		OFFSET	0
BHPALOFFSET	ds.w	1		; offset to palette
BHMAPOFFSET	ds.w	1		; offset to map
BHCHAROFFSET	ds.w	1		; offset to character definitions
BHMAPBOFFSET	ds.w	1		; offset to map b
BHOBSTOFFSET	ds.w	1		; offset to obstical map
BHINFOOFFSET	ds.w	1		; animated map info offset



;
; -----	Palette structure
;
		OFFSET	0
BPCOLORINDEX	ds.w	1
BPNUMCOLORS	ds.w	1
BPRGBVALUES	ds.w	0


;
; -----	Animated map header info structure
;

		OFFSET	0
AMNFRAMES	ds.w	1
		OFFSET	0
AMXOFFSET	ds.w	1
AMYOFFSET	ds.w	1
AMMAPOFFSET	ds.w	1
AMSTARTCHAR	ds.w	1
AMNUMCHARS	ds.w	1
SIZEAMSTRUCT	equ	*-AMXOFFSET

;
; ----- Map structure
;
		OFFSET	0
BMWIDTH		ds.w	1
BMHEIGHT	ds.w	1
BMMAP		ds.w	0


;
; -----	Character structure
;
		OFFSET	0
BCNUMCHARS	ds.w	1
BCCHARBITMAPS	ds.w	0


;	Animation Files:
;		UWORD	Offset to Palette
;		UWORD	Offset to Animation list
;		UWORD	Offset to Animation to Frame catalog
;		UWORD	Offset to Frame to Sprite catalog
;		UWORD	Offset to Hotspot catalog
;		UWORD	Offset to Character Definitions
;		UWORD 	flags
;				bit 0 = Scaleable sprite format
;				bit 1 = bitmap sprite format
;		???
;		Palette:
;			WORD	Color Register index
;			UWORD	Number of colors
;				UWORD	RGB Value (Sega format)
;				...
;			...Repeat...
;			-1		End of list
;		Animation list:
;			UWORD	Number of frames
;			UWORD	Offset to first Animation to Frame offset
;			...
;		Animation to Frame catalog:
;			UWORD	Offset to first Frame to Sprite structure
;			...
;		Frame to Sprite catalog:
;			UWORD	Number of sprites in frame
;			UWORD	Hotspot catalog offset
;			UWORD	width in pixels of frame
;			UWORD	height in pixels of frame
;				WORD	Y Position on screen (0..n)
;				WORD	H size, V Size, Link
;				UWORD	Priority, Palette, VFlip, HFlip, Char number
;				WORD	X Position on screen (0..n)
;			...
;		Hotspot catalog:
;			UWORD	Number of X,Y pairs
;				WORD	X Position
;				WORD	Y Position
;				...
;			...
;		???	Insert new blocks here.
;		Character Definitions:
;			UWORD	Number of characters
;			BYTE	32 Bytes per character
;
;		*****	Dependant on flags settings *****		
;		Character Definitions:
;			UBYTE	32 Bytes per character
;
;		Scaleable sprite Definitions
;			UBYTE (w * h)/2 Bytes per character
;			 format is stored in Y then X sega format.
;

		OFFSET	0
AHPALOFFSET	ds.w	1		; offset to palette
AHALISTOFFSET	ds.w	1		; offset to animation list
AHFLISTOFFSET	ds.w	1		; offset to frame list
AHSPRITEOFFSET	ds.w	1		; offset to sprite info list
AHHOTSPOTOFFSET	ds.w	1		; offset to hotspot information
AHCHAROFFSET	ds.w	1		; offset to charoffset
AHFLAGS		ds.w	1		; flags for type of animation
AHHEADSIZE	equ	*-AHPALOFFSET

;
; ----- Animation List Structure
;
		OFFSET	0
ALNUMFRAMES	ds.w	1		; Number of frames 
ALANIMOFFSET	ds.w	1		; animation list offset

;
; -----	Animation frame structure
;
		OFFSET	0
FLSPRATTROFFSET	ds.w	1		; Sprite attribute pointer

;
; -----	Sprite Attribute structure
;
		OFFSET	0
SANUMSPRITES	ds.w	1		; Number of sprites
SAHOTOFFSET	ds.w	1		; Hot spot offset
SAWIDTH		ds.w	1		; width in pixels of frame
SAHEIGHT	ds.w	1		; height of pixels of frame
SAHEADSIZE	equ	*-SANUMSPRITES
		OFFSET	0
SAYPOS		ds.w	1		; y position of sprite
SAHVLINK	ds.w	1		; h size, vsize and link
SAATTRIBUTES	ds.w	1		; Priority, palette, vflip, hflip charnum
SAXPOS		ds.w	1		; x position of sprite
SASIZE		equ	*-SAYPOS

;
; ----- Hot spot structure
;
		OFFSET	0
HLNUMHS		ds.w	1		; number of x,y pairs
HLXPOS		ds.w	1		; x position
HLYPOS		ds.w	1		; y position

;
; -----	Sprite list structure
;
;
; -----	Sprite list structure
;
		OFFSET	0
SLY		ds.w	1		; y position of sprite
SLLINK		ds.w	1		; link for sprite
SLCHR		ds.w	1		; starting character for sprite
SLX		ds.w	1		; x position of sprite
SPRLISTSIZE	equ	*-SLY


;
;
;
; -----	Character map bit definitions
;

CHARPRIORITY	equ	%1000000000000000
CHARCP1		equ	%0100000000000000
CHARCP0		equ	%0010000000000000
CHARVF		equ	%0001000000000000
CHARHF		equ	%0000100000000000

CHARPRIORITYBIT	equ	15
CHARVFBIT	equ	12
CHARHFBIT	equ	11

