

#define USEITHER  0
#define USEEMM    1
#define USEFAR    2



void            far vm_init_mem( short link_in_64K_of_emm_flag );
void            far vm_reset_mem( void );


// 
// USEEMM - forces use of emm block
// USEFAR - will NOT use EMM.
char     huge * far vm_hmalloc (long, long);
void            far vm_hfree (char huge *);


// Returns HANDLE.
// Can still do vm_emm_alloc() if vm_have_emm even if vm_init_mem(0).
short           far vm_emm_alloc( long );

// anything which is locked MUST be unlocked.
char            far * far vm_emm_lock( short handle, short bank_no );

// 
void            far vm_emm_unlock( short );

// Must free all allocs.
void            far vm_emm_free( short );


//
// Bank selection.  No preservation:
// vm_emm_bank ( vm_emm_handle ) will bank in the hmalloc() block.
//
char            far * far vm_emm_bank( short handle );



extern char     vm_have_emm;
extern short    vm_emm_handle;

