typedef void (far * farfunc) ();

extern short far sx_machtype();		/*internal only */
extern short far musicstart(struct _mushdr far * ptr,short pri);
char far * far sx_musloops();

#define PPI	0x61		

#define MAX_SNDBANKS 10
#define MAX_MUSBANKS 15

/* pc channels: 0,1,2,3 */
/* Tandy channels: 4,5,6,7 */
#define TN_CHAN 4
#define TN_NOISE 7
#define NUM_CHAN 10
#define DIG_CHAN 8
#define DMA_CHAN 9
#define SXCNT 1193180
#define CURRENT_VERSION 23001

typedef struct farptrcell {
	long far *blockaddr;
	struct farptrcell *next;
	char blname[10];		/* name of this block */
	} FARPTRCELL;

typedef struct _audbank {
	FARPTRCELL firstblock;
   short num_auds;
   short num_mods;
	FARPTRCELL *modchunk;
   } AUDBANK;

extern short far seg_handle[];
extern unsigned int far priority[];   /* i,i,i,i,dig */
extern short far mod_tab[];
extern short far env_tab[];

typedef struct _sndhdr {
   short typ;
   unsigned short len;
   short cnt;			/* playback rate */
   short sp1;
   short sp2;
} SNDHDR;

typedef struct _mushdr {
   unsigned short len;
	short tempo;
	short tpb;
	short iduno;
} MUSHDR;

struct INFHDR {
   short version;
   short num_sounds;
   short num_mods;
};


struct modstruct {
   short start;
   short length;
};


/*extern far sx_indy_on(char far *,short chan ,char far *modtab,short env); */
extern far sx_indy_on(SNDHDR far *,short,char far *,short);
extern far sx_indy_off(short);
extern far sx_indy_pitch(short,short);

extern far sx_startdig();
extern far sx_stopdig();
extern far sx_digpitch();

/* TandyTL routines: */
extern int far DAC_Play( char far *, short, short, short );
short far DAC_Status();
void far DAC_Restore();

short far sx_401init();
short far sx_401install();
short far sx_401command();
void far sx_401sound(SNDHDR far *Sound);
short far sx_401put();
short far sx_401quit();
short far sx_401start(MUSHDR far *ptr);
short far sx_401stop(void);

short far sx_pctandy_event();
short far sx_indy_mus(unsigned priority);
void far _nullret(void);

/* Adlib routines-- */
void far sx_AdlibInit();
short far sx_adlib_event();
void far sx_Adlibquiet();

extern far mastertimer();

extern short far exists401();
extern short far existsAdlib();
extern short far sx_machtype();

extern farfunc far *do_event; 

/* PC/Tandy routines: */
extern far sx_do_pc();
extern far sx_do_tn();

extern far sx_digfar();
extern far sx_digint();

enum fakename {
SPC,
STANDY,
S1,
S8SVX,	/* signed 8-bit */
S8
};

#define SMT_32 11

#define FARMEMFAIL  1
#define NEARMEMFAIL 2
#define BADBLOCK  3

extern void far sxint(void);

void far SetVoiceVolume( short voice , char volume);
void far SetVoiceTimbre( short voice,short  * paramArray);
void far NoteOn( short voice, unsigned char pitch);
void far NoteOff( short voice);


short far sx_ovrlyblck( AUDBANK *bank ,FILE *fp,char *blockname);

extern char far sx_audibility;

extern short far indy_num[]; 
extern short far chan_flags[];
extern short tempo;
extern short far sx_401quiet();
