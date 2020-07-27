

#ifndef __MSDOS__
#define far 
#define huge 
#define max(a,b)    (((a) > (b)) ? (a) : (b))
#define min(a,b)    (((a) < (b)) ? (a) : (b))
#endif


#ifndef FALSE
#define FALSE  0
#define TRUE   !FALSE
#endif


typedef char				CHAR;
typedef char				SCHAR;
typedef unsigned char	UCHAR;
typedef char				BYTE;
typedef unsigned char	UBYTE;
typedef short				WORD;
typedef short				SWORD;
typedef short				SHORT;
typedef short				SSHORT;
typedef unsigned short	USHORT;
typedef unsigned short	UWORD;
typedef long				LONG;
typedef unsigned long	ULONG;

   /* Defines for the joystick routines.
   */
#define	JOY_UP		0x0
#define	JOY_DOWN		0x2
#define	JOY_LEFT		0x4
#define	JOY_RIGHT	0x6
#define	JOY_B			0x8
#define	JOY_C			0xA
#define	JOY_A			0xC
#define	JOY_START	0xE

/************************************************************************/
/* system structures																		*/
/************************************************************************/
typedef struct sprlist {
		WORD sly;		/* y position of sprite */
		UWORD sllink;	/* link for sprite */
		UWORD	slchr;	/* starting character for sprite */
		WORD slx;		/* x position of sprite */
		} sprlist;

typedef struct cursoritem {
		UWORD ix;				/* items x position 									*/
		UWORD iy;				/* items y position 									*/
		UWORD iw;				/* items width											*/
		UWORD ih;				/* items height										*/
		} cursoritem;

typedef struct editSlot {
		UWORD anim;
		UWORD	frame;
		UBYTE *animptr;
		BYTE count;
		BYTE partNo;
		} editSlot;

/****** Sysytem Prototypes ******/
extern void SetSR(UWORD sr);
extern void	SYS_DMA(ULONG video_addr,ULONG length,void *src_addr);
extern void	SYS_SetVAddr(UWORD video_addr);
extern void	SYS_SetPalette(UWORD *pal_addr);
extern void	SYS_SendPalette(void);
extern void	SYS_ClrPalette(void);
extern void	SYS_FadeIn(ULONG frames);
extern void	SYS_FadeOut(ULONG frames);
extern void SYS_WaitFrame(void);
extern void SYS_DumpCharCache(void);
extern BYTE	SYS_JoyTable[16];
extern BYTE	SYS_Joy2Table[16];
extern UWORD	SYS_JoyHit;
extern void	EHInts();
extern UWORD SYS_LastChar;
extern UWORD SYS_SprAvail;
extern UWORD StaticSprites;
extern UWORD SYS_FirstSpr;
extern UWORD SYS_FirstChar;
extern UBYTE SYS_VDPAccess;
extern UWORD MapX, MapY;
extern ULONG SYS_VCount;

extern BYTE request;

extern UWORD ScreenRow;
extern UWORD ScreenCol;
extern UWORD ScrAAddr;
extern UWORD ScrBAddr;
extern UWORD AsciiPalette;
extern ULONG CharSet;
extern UWORD remapOffset;

extern UWORD MapABuff;
extern UWORD MapBBuff;
extern sprlist Work_Sprlist[];
extern UWORD vm_schar;
extern UWORD spriteChar;
extern UWORD startSprChar1;
extern UWORD startSprChar2;
extern UWORD endSprChar1;
extern UWORD endSprChar2;
extern UWORD displaycursor;
extern UBYTE cursoractive;
extern UBYTE partbin_active;

extern cursoritem pb_hs[12];
extern UBYTE is_partbin;
extern UBYTE catroot;
extern UBYTE cursors;

extern short runfirsttime;
extern UWORD AsciiChars;
extern UWORD NumberChars;

/************************************************************************/
/* external Function Prototypes														*/
/************************************************************************/
/* TN_PANEL.C68 */
void draw_toon_edit_panel(short x, short y);
/* VM_CIRC.C68 */
void vm_circle( short radius, short x, short y);
/* VM_INIT.ASM */
short	vm_init ( void );
/* VDPLIB.ASM */
void ClearCellMap(ULONG screenAddr);
void ClearVSRAM(void);
void ClearVRAM(void);
void ClearMapBuff(void *mapPtr);
void CopyToVRAM2(UWORD vdpAddr, UWORD length, void *dptr);
void FadeOut(UWORD frames);
void FadeIn(UWORD frames);
void StorePalette(void *palPtr);

/* LINE.ASM */
void SYS_setpix(short x, short y, short color);
void SYS_DumpCharCache(void);
void SYS_Line(short x1, short y1, short x2, short y2,	short color);

/* DMAQUEUE.ASM */
void waitDMAQueue(void);
void addDMAQueue(UWORD vdpaddr, ULONG length, void *src);

/* SCROLL.ASM */
void ScrollMap(BYTE *mapAddr);
/* GRAF.ASM */
extern BYTE mainGMPFile;
/* sprites.asm */
short Disp1AnimFrame(short x, short y, short anim,
	short frame, short vdpChar, void *address);
void SendSprList(void);
short AnimFrametoMap(short anim, short frame, 		
			short vdpChar, long FPAaddress,	
			long mapAddress);		
void DispFrame(UWORD xpos, UWORD ypos, UWORD anim,
	UWORD frame, UWORD vdpchar, void *FPAfile);
UWORD SendFrameChars(UWORD anim, UWORD frame,
	UWORD vdpChar, void *FPAptr);
UWORD SendAnimChars(UWORD vdpChar,void *FPAptr);
void getFrameInfo(UWORD anim, UWORD frame, 		
	void *FPAptr, UWORD *totalAnims, UWORD *totalframes,
	void **sprInfo, void **charData);
void SetSpritePal(void *sprStruct);
UWORD GetFrameChars(UWORD anim, UWORD frame,	void *animptr);
UWORD AddHole(WORD x, WORD y, UWORD anim, UWORD frame, UWORD CharNum, 
					void *animptr);
void UpdateHole(WORD x, WORD y, UWORD anim, UWORD frame,	void *animptr, 
					UWORD holenum, UWORD newChars);

UWORD updateFrame(UWORD anim, UWORD frame, void *animptr);
void GetFrameWH(short anim, short frame, void *FPAaddress, short *width, 
						short *height);
void ClearSprites(void);

/* MAPS.ASM */
UWORD DLFPCChars(void *FPCAddr);
void FPCSetPal(void *FPCAddr);
void SYS_DrawMap(UWORD srcx, UWORD srcy, UWORD VDPChar,void *map, void *buff);
short MapFrametoMap(WORD x, WORD y, UWORD anim, UWORD frame, UWORD vdpChar,
		void *FPAaddress, void *mapAddress);	
short DrawAnimMapFrame(WORD x, WORD Y, UWORD frame, void *FAMAddress, 
								void *mapAddress, UWORD vdpChar);
short EraseAnimMapFrame(WORD x, WORD y, UWORD frame, void *FAMAddress, 
								void *mapAddress,	UWORD vdpChar);

/* VM_DRAW.ASM */
SYS_draw(short x, short y, short frame, long shpptr);
/* GENERAL.ASM */
UWORD ptInRect(short px, short py, short rx, short ry, short rw, short rh);
/* CURS_MLH.C68 */
void put_crawl(short x, short y, short width, short height, short anim, 
			short color);

/* DUMMY.C68 */
void makeTempStatic(void);
void resetPaging(void);
void checkwritetorom(short dummy);
extern UWORD saveSYS_FirstSpr;
extern UWORD FirstPageChar;

#define	DisableInts()	asm(" move.w #$2700,SR");
#define	EnableInts()	asm(" move.w #$2000,SR");

#define	SpriteAttr		55*1024
#define	Hscroll			54*1024


#define	CENTERMAPX	160
#define	CENTERMAPY	112

#define	IBMLEDGE		91
#define	SEGALEDGE	16
#define	IBMTEDGE		-8
#define	SEGATEDGE	0

/**** MACROS *****/
#define EXT_DATA		(*((BYTE *)0xA10007))
#define EXT_CTRL		(*((BYTE *)0xA1000D))
#define VDATA			(*((UWORD *)0xC00000))
#define VCTRL			(*((ULONG *)0xC00004))
#define WVCTRL			(*((UWORD *)0xC00004))
#define VCNTR			(*((UWORD *)0xC00008))

/** Set vdp register macro has mondo side effects! **/
#define SetVdpRegister(reg,val) *((UWORD *)0xC00004)=0x8000|((reg<<8)|val);VdpShadow[reg]=val

#define		CHARPRIORITY	0x8000
#define		CHARCP1			0x4000
#define		CHARCP0			0x2000
#define		CHARVF			0x1000
#define		CHARHF			0x800

#define		MAPHEIGHT			32
#define		MAPWIDTH				64
#define		MAXYREZ				224
#define		VISIBLEMAPWIDTH	40
#define		VISIBLEWIDTH		40
#define		VISIBLEHEIGHT		28

#define		EDITPANEL			0
#define		CONTROLPANEL		1
#define		PICKUP_CURSOR 		5
#define		STANDARD_CURSOR 	6
#define		QUESTION_CURSOR	7

/* make this 1 for 640x400 virtual coordinates 	*/
/* else make it 0.										*/
#define		VIRTUALCOORDS		0

#define smuls(a,b) (long)((short)a*(short)b)

