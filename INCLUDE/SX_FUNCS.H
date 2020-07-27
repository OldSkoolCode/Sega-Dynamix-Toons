/* SOUND LIBRARY function prototypes */

#ifndef SX_FUNCS_H
#define SX_FUNCS_H
/* low level midi functions */
#if PC == 1
unsigned long FAR sx_GetSMPTE(Sound FAR * Node );
unsigned char FAR sx_PatchReq( char FAR * Driver );
#elif AMIGA == 1
unsigned char sx_PatchReq( char *Driver, short *numV, short *numD, short *devID);
void sx_GetSMPTE(Sound *node, short *mins, short *secs, short *frames);
#else
#endif
short FAR sx_Init( char FAR * FixedPtr );
void FAR sx_Terminate( void );
void FAR sx_PlaySound( Sound FAR *Node, short SngSfxBool );
void FAR sx_FadeSound( Sound FAR *Node, short DstVol, short delay, short rate);
void FAR sx_SoundOn( short OnOffBool );
void FAR sx_EndSound( Sound FAR * Node );
void FAR sx_HoldSound( Sound FAR * Node, short Value);
char FAR sx_GetSignal( Sound FAR * Node);
short FAR sx_SetReverb(short ReverNum);
void FAR sx_SendController( Sound FAR *Node, short ConNum, short Value,
                                                      short Channel);
void FAR sx_PitchBend( Sound FAR * Node, short Bend, short Channel);
void FAR sx_ChangeVol( Sound FAR * Node, short Volume);
void FAR sx_PauseSound(Sound FAR * Node, short OnOffBool);
char FAR sx_MasterVol(short Volume);
void FAR sx_RestoreSound(Sound FAR * Node);
void FAR sx_ChangePri(Sound FAR * Node, short Priority);
short FAR sx_GetDataInc(Sound FAR * Node);
short FAR sx_MuteSound( Sound FAR * Node, short OnOffBool );
void FAR SoundServer( void );
/*mid level support functions - initialization and reset functions */
short FAR sx_driver_load( short midiType , short audType, short audPort, char * fname);
void FAR sx_int( void );
void FAR sx_deinstall( void );
/*mid level support functions - data handling routines */
Sound FAR * FAR sx_FixUpSndStruc( char FAR * dataptr );
char FAR * FAR sx_PartialLoad( FILE * fp , long size, long *unpaksize, short type );
char FAR * FAR sx_UnPakBlock( FILE * fp , long size, long *unpaksize, short type );
char FAR * fixupPtr( unsigned char FAR * );
Sound FAR * sx_sfx_node( char FAR * dataptr );
char FAR * FAR sx_loadblock( char *, char *, short);
char FAR * FAR getnextsng( FILE * fp, short type );
short FAR sx_patchload( char *, short*, short );
/*mid level support functions - memory allocation  */
void FAR * sx_alloc( long, short );
void sx_freemem( void FAR *, short );
/*mid level - sfx functions */
short FAR sx_sfx_init( void );
short FAR sx_sfx_deinstall( void );
char FAR ** FAR sx_sfx_load( void * );
char FAR ** FAR sx_sfx_free( char FAR ** );
Sound FAR * FAR sx_sfx_start( char FAR * dataptr, short vol, char loop );
void FAR sx_sfx_stop( char FAR * dataptr );
void FAR sx_sfx_all_stop( void );
void FAR sx_sfx_endsnd ( Sound FAR * snd );
short FAR sx_sfx_cnt(char FAR **sarray);
void FAR sx_sfx_volume ( char FAR * dataptr, short vol );
Sound FAR * sx_sfx_node( char FAR * dataptr );
/*mid level - song related functions */
Sound FAR * FAR sx_loadsong( char * fname );
void FAR sx_freesong( Sound FAR * song );
Sound FAR * FAR sx_startsong( Sound FAR * song, short num, short vol );
void FAR sx_stopsong( Sound FAR * song, short num );
short FAR sx_songcnt ( Sound FAR * song );
void FAR sx_songvol( Sound FAR * song, short num, short vol );
Sound FAR * find_song ( Sound FAR * song, short num );
void FAR sx_fadesong( Sound FAR * song, short num );
/* high level - GDS functions */
short sx_setup( short midDev, short audDev, short audPort, char *fname );
void sx_reset( void );
short sx_patch( void *file, short patch);
SX_SOUND FAR * sx_find( short id );
void *sx_load( void *file, short id );
short sx_free( short id );
short sx_start( short id );
short sx_stop( short id );
short sx_pause( short id );
short sx_unpause( short id );
short sx_mute( short id );
short sx_unmute( short id );
short sx_vol( short id, short volume );
short sx_bend( short id, short bend, short channel );
short sx_controller( short id, short number, short value, short channel );
short sx_hold( short id, short value );
short sx_fade( short id, short volume, short time );
short sx_signal( short id );
short sx_datainc( short id );
short sx_restore( short id );
short sx_priority( short id, short priority );
short sx_smpte( short id, SX_TIME *);
short sx_reverb( short reverb );
short sx_master_vol( short volume );
unsigned long sx_mem( void );
short sx_check( short id, short type );
Sound FAR * sx_get_struc( short id );
short sx_LoadNextSng( FILE * fp, char pType );
Sound FAR * find_struc( SX_SOUND FAR * Song );

#ifdef SX_SIM
/* high level - sim functions */
short once_only_init_sounds ( char *, char *, 
                     unsigned short, unsigned short, char );
void once_only_reset_sounds ( short force_reset );
short init_sound_system ( short on );
void reset_sound_system ( void );
void clear_loop_sounds ( void );
void update_sounds ( LVEC * camloc, short external );
void turn_off_sounds ( void );
void stop_all_sounds ( void );
void turn_on_sounds ( void );
short sounds_are_on ( void );
short is_valid_sound ( short sound );
short sound_loops ( short sound );
short start_sound ( short sound, LVEC * loc, IVEC *absvel );
short make_bent_sound ( short, LVEC *, short, IVEC*, short );
short start_custom_sound ( short sound, short vol, short pbend );
#endif
#if MACINTOSH == 1
/*mac specific code */
extern void *load_data_resource(char * fname);
extern void *load_code_resource(char * fname);
#endif
#if AMIGA == 1
void put_word(short *, short);
#endif


/* low level hard disk streaming calls */
extern unsigned short audInit( unsigned short diskVsMem, unsigned short defaultPort );
extern void audRate( unsigned short sampleRate );
extern void audFill( void );
extern void audSelect( char far* fileName, unsigned long filePos,
   unsigned long dataSize, unsigned char huge *audBuf, unsigned short bufSize,
   unsigned short comprOn ); 
extern void audPlay( void );
extern void audWPlay( void );
extern unsigned long audChk( void );
extern void audFin( void );
extern void audStop( void );

/* hard disk streaming library protos */
extern short hdsDeInit( void );
extern short hdsStop( void );
extern short hdsPlay( void );
extern short hdsLoad( char far *fname );
extern short hdsInit( unsigned short bSize  );
extern unsigned long hdsPos( void );

#endif

