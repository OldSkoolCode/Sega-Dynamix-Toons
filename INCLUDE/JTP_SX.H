/* * * * *
*
*  JTP_SX.H
*
*  Header file contains the J.T.P. interface to the Dynamix/Sierra
*  sound drivers.  It allows both sounds to be played from memory
*  and from disk (via the hard disk streaming system).
*
*  By Rich Rayl -- (c) 1993 Dynamix, Inc.  (Jeff Tunnell Productions)
*
*  Modification History:
*  ---------------------
*  05/05/93 RichR    File created      $Revision: 1.13.0.1 $
*                    Last modified     $Date: 1993/05/06 19:04:48 $
* * * * */

#ifndef JTP_SX_H
#define JTP_SX_H

#include "sx_defs.h"    /* Need audio and digitial device definitions */

/* Define the sound id type */
typedef short JTP_SX_ID;

   /* The following can be used as a JTP_SX_ID */
   #define JTP_SX_ALL      -1    /* All sounds and music */
   #define JTP_SX_MUSIC    -2    /* Only the music */
   #define JTP_SX_SFX      -3    /* Only the sound effects */
   #define JTP_SX_SFX_FM   -4    /* Only the FM/MIDI sounds */
   #define JTP_SX_SFX_DIGI -5    /* Only the memory based digitized sounds */
   #define JTP_SX_SFX_HDS  -6    /* Only the hard disk streaming sounds */

   /* The following ranges have been assigned to different sound types */
   /*    1 to  999 are reserved for FM/MIDI sounds.                (.SX ) */
   /* 1000 to 1999 are reserved for music.                         (.SX ) */
   /* 2000 to 2999 are reserved for memory based digitized sounds. (.SX ) */
   /* 3000 to 3999 are reserved for hard disk streaming sounds.    (.RAW) */
   /* 4000 and up are illegal and will be ignored */


/* Declare the function prototypes */
short jtp_sx_init(short midi, short audio, short port);
void  jtp_sx_reset(void);
short jtp_sx_load(JTP_SX_ID id);
void  jtp_sx_free(JTP_SX_ID id);
short jtp_sx_play(JTP_SX_ID id, short priority, short preempt);
void  jtp_sx_stop(JTP_SX_ID id);
void  jtp_sx_fade(JTP_SX_ID id);
void  jtp_sx_volume(JTP_SX_ID id, short volume);
short jtp_sx_master_volume(short volume);
long  jtp_sx_playing(JTP_SX_ID id);


#endif
