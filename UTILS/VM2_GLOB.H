#ifndef ubyte 
#define  ubyte unsigned char 
#endif


#define   bpos_t  struct save_bpos
bpos_t
{
   long     bitoff;        // offset in bit stream.
   long     byteoff;       // offset in byte stream.
};


#define  BITS struct bit_stream
BITS
{
   long        off;           // bit offset.
   ubyte huge *buffer;     
};



extern short vm2_flipscreen;  // works as in vm_flip_draw but with screens
extern ubyte vm2_zerofill;     // reset if color 0 is transparent 
