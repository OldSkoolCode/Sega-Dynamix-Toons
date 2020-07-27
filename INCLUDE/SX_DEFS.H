
/*SOUND LIBRARY definitions */
#ifndef SX_DEFS_H
#define SX_DEFS_H
/*Version number */
#define VERSION 2
/*status flag defines */
#define  FLG_BED     0x01   
#define  FLG_LOOP    0x02
#define  FLG_MUTE    0x10
/*default song volume */
#define SONG_VOLUME 127
#define SFX_VOLUME 127
/* for non-PC machines */
/* Flag if we can dispose of patch immediately */
#define     KEEP_PATCH     0x0080
#define     BAD_PATCH      0x00ff
/* DAC device types for sx_driverLoad */
#define     SX_AUDBLAST    0
#define     SX_AUDPS       1
#define     SX_AUDTANDAC   2
#define     SX_AUDPRO      3
#define     SX_AUDDS       4

/* MIDI device types for sx_DriverLoad */
#define     SX_NO_INIT  -2    /* no machine was initialized */
#define     SX_NO_TIME  -1  /* supported in gd_setup() only !!!!! */
#define     SX_SPEAKER  0
#define     SX_TANDY    1
#define     SX_ADLIB    2
#define     SX_ROLAND   3
#define     SX_SB_PRO   4   
#define     SX_PS1      5
#define     SX_PRO      6
#define     SX_GEN_MIDI 7
#define     SX_DUMMY    8
#define     SX_AMIGA    0x7e
#define     SX_MAC      0x7f
/* anded with machine type if you do not want patch loaded */
#define     LOAD_MASK   0xFF80



/* machine types for snd file format */
#define     SND_ADL     0X00     /*sndblaster, adlib, proaudio */
#define     SND_GM      0X07     /* general midi */
#define     SND_M32     0X0C     /*roland */
#define     SND_PC      0X12     /*pc internal */
#define     SND_TAN     0X13     /*tandy, tandyDAC, PS1 */
/*sx_alloc memory allocation types */
#define  DRV_PATCH   1
#define  SND_STRUCT  2
#define  SX_STRUCT   3
#define  SNG_DATA    4
#define  SFX_NODE    5
#define  SFX_ARRAY   6
#define  SFX_DATA    7
#define  SFX_LFLAGS  8
#define  TRK_LOAD    9
#define  SX_SND_INDEX 10
/* error codes returned into sx_error */
#define  MEM_ALLOC   1
#define  SX_DATA     2
#define     SIMULTSOUNDS   7
#define     SONGS_WANTED   0

        
/*////////////////////////GDS specific definitions */
/* special sx_id for all sounds or music */
#define ALL_SX       0
#define ALL_MUSIC   -1
#define ALL_SOUNDS  -2
#define FIND_NEXT   -3 
#define NO_MUTE     -4 

#ifdef SX_SIM
/*////////////////////// sim specific definitions */
#define  SX_SELECT      SX_CLICK
#define  SX_WRONG       SX_CHICK
#define  SX_TAB         SX_CHICK
#define  MIDDLE_PBEND      8192
#define  MAXIMUM_PBEND     16380
#define  MINIMUM_PBEND     40
/* */
/* Priorities: */
/* SYSTEM - cursor clicks and such should always be heard */
/* SPECIAL - player gun and bullet hits always heard if within range. */
/* REGULAR - all regular world sounds which are sorted by distance */
/* FRILL - things which are thrown out if there's a bottleneck. */
/*  */
#define  SYSTEM_PRI           120
#define  SPECIAL_PRI          90
#define  REGULAR_PRI          80
#define  FRILL_PRI            60
#define  SFX_SPUTTER       1           /* ctrl bits */
#endif

#ifdef __BORLANDC__
#ifndef FP_OFF
   #if PC == 1
      #define FP_SEG( fp )( (unsigned )( void _seg * )( void far * )( fp ))
      #define FP_OFF( fp )( (unsigned )( fp ))
   #elif MACINTOSH == 1 || AMIGA == 1
      #define FP_SEG( fp ) fp
      #define FP_OFF( fp ) fp
   #else
   #endif
#endif
#endif

#define HDS_PS1 "audps1.drv"
#define HDS_BLAST "audblast.drv"
#define HDS_PRO "audpro.drv"
#define HDS_TNDY "audtandy.drv"
#define HDS_NONE "audnone.drv"
#define AUDIO_BSIZE 10241
#define DISK_IO 1
#define DEFAULT_PORT 0
#define AUD_RATE 11025
#define AUD_RATE_DIV_60 11025/60


#endif

