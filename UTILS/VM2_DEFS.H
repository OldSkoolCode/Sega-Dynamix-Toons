#define  ADDR(seg,ofs)	  ((void far *)(((unsigned long)(unsigned short)(seg) << 16) | (unsigned)(ofs)))


#define  TOP_LEFT_BIT      8
#define  TOP_RIGHT_BIT     4
#define  BOT_LEFT_BIT      2
#define  BOT_RIGHT_BIT     1

