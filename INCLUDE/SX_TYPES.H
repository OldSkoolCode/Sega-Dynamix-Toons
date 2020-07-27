/* SOUND LIBRARY type declarations */
#ifndef SX_TYPES_H
#define SX_TYPES_H  
typedef struct sx_sound
{
#if AMIGA == 1   
   long         sOldNext;            /*Node header */
   long         sOldPrev;            /*Node header */
#else
   short        sOldNext;            /*Node header */
   short        sOldPrev;            /*Node header */
#endif
   short        sKey;                 /*Node header */
   short        sNumber;
   char FAR *FAR *sPointer;           /*Far pointer to sound resource */
   short        tIndex[16];           /*Index for 16 tracks */
   short        tLoopPoint[16];       /*Loop Point for 16 tracks */
   short        tRest[16];            /*Rest count for 16 tracks */
   short        tLoopRest[16];        /*Rest count at loop for 16 tracks */
   char         tChannel[16];         /*Channel #'s for 16 tracks */
   char         tCommand[16];         /*Last command for 16 tracks (running status)  */
   char         tLoopCommand[16];     /*Command at loop for 16 tracks */
   short        cDamprPbend[15];      /*Damper pedal and pitch bend for 15 channels */
   char         cPriVoice[15];        /*Priority & voice allocation for 15 channels */
   char         cModulation[15];      /*Modulation values for 15 channels */
   char         cPan[15];             /*Pan values for 15 channels */
   char         cVolume[15];          /*Volume values for 1   5 channels */
   char         cProgram[15];         /*Program values for 15 channels */
   char         cCurNote[15];         /*Current note being played */
   char         cFlags[15];
   char         cMute[15];
   short        sDataInc;             /*Current Data Increment cue value */
   short        sTimer;               /*Age of sound (in 60th secs) */
   short        sLoopTime;            /*Timer loop point */
   char         sSignal;
   char         sState;               /*Flags sound as a bed sound (used in restore) */
   char         sHold;                /*Sound hold/release flag */
   char         sFixedPri;
   char         sPriority;            /*Sound priority */
   char         sLoop;                /*Sound loops */
   char         sVolume;              /*Sound volume */
   char         sReverbMode;          /*Reverb setting */
   char         sFadeDest;            /*Fade destination */
   char         sFadeTicks;           /*Clock ticks before next fade */
   char         sFadeCount;           /*Fade tick counter */
   char         sFadeSteps;           /*Fade steps */
   char         sPause;               /*Pause flag           */
   char         sSample;              /*Sample track + 1 */
   char FAR *   data;
   char FAR *   handle;  
   
   /* LH added for Baron: */
   void *      owner;                  /* who emits this sound */
   char        snum;                   /* sound number */
   char        filler;
   /*allow FAR pointers in linked list */
   struct sx_sound FAR *sNext;            /*Node header */
   struct sx_sound FAR *sPrev;            /*Node header */
} Sound;

typedef struct sx_info
   {
   struct sx_info FAR *next;
   void FAR          *data;
   unsigned short    size;
   short             id;
   short             priority;
   Sound FAR         *SndStruc;
   unsigned short    flags;
   }SX_SOUND;
typedef struct sx_time
   {
   unsigned short minutes;
   unsigned short seconds;
   unsigned short frames;
   }SX_TIME;

typedef struct 
   {
   short id;
   long offset;
   } SX_IDX;

typedef struct
   {
   SX_IDX far *ndx;
   short ver;
   short cnt;
   char packType;
   } SX_INF;


#ifdef SX_SIM
/* for sims */
enum _snds_
{
   SX_COCKPIT,          /* (loop)  */
   SX_MACHGUN,          /* (loop)  */
   SX_MAVERICK,         /* (loop)  */
   SX_EXPLO1,           /* (no loop)  */
   SX_EXPLO2,           /* (no loop)  */
   SX_EXPLO3,           /* (no loop)  */
   SX_MISWARN,          /* (loop)  */
   SX_COLWARN,          /* (loop)  */
   SX_CLICK,            /* (no loop)  */
   SX_CHICK,            /* (no loop)  */
   SX_LOGOSTAR,         /* (no loop)  */
   SX_CHOPPER,          /* (loop)  */
   SX_CANON,            /* (no loop)  */
   SX_BOMBREL,          /* (no loop)  */
   SX_ENGINE,           /* (no loop)  */
   SX_OUTSIDE,          /* (loop) */
   SX_VEHICLE,          /* (loop) */
   SX_AA,               /* (loop) */
NUM_SOUND_EFFECTS,
};
#endif
#endif

