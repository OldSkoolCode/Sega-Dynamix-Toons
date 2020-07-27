/* SOUND LIBRARY global variables */
#ifndef SX_GLOBS_H
#define SX_GLOBS_H
extern char FAR * sx_midiDrvPtr;  /* pointer to the driver */
extern char FAR * sx_audDrvPtr ;
extern Sound FAR * sfx_node[SIMULTSOUNDS];   /* sfx array */
extern char sx_init_flag;        /* flag for initialization */
extern SX_SOUND FAR *FirstSong;  /* gds link list first song */
extern short GotDAC;             /* flag for midi to check for DAC */
extern unsigned short Patch_number;        /* # returned from sx_PatchReq */
extern short sx_set_timer;       /* boolean to indicate if timer was installed */
                                 /* sx_setup    */
extern short sx_midiTimerHandle; /* vm timer handle from installing sx_int */
extern short sx_audTimerHandle;
extern char *LoopFlags;          /* pointer to sfx loop and priority array */
extern short sx_error;           /*  */
extern char FAR *Patch;          /* pointer to patch data */
extern unsigned short devID;     /* device id returned for patch request */
extern short Sx_mute_status;     /* current status of muted sounds */
extern SX_INF far *sxInf;        /* array of offsets into sx file */
extern FILE *sxFp;                /* pointer to current sound file */
extern short sxClose;            /* should sx close the file at reset; */
extern short sx_partial;         /* determines if sounds are fully or partially loaded */
extern short sx_midiType;        /* machine type for midi device */
extern short sx_audType;         /* machine type for audio device */
extern unsigned short hdsRate;   /* the audio rate at which sounds are played back */
  
#if MACINTOSH == 1
/*mac specific code */
extern char *midi_ptr;
#endif
#if AMIGA == 1
extern unsigned long bseg;       /* segment pointer to Driver */
#endif

#endif

