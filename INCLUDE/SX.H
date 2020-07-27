#ifndef _SX_H_
   #define _SX_H_
   #ifndef  FILE
      #include <stdio.h>
   #endif
   #if MACINTOSH == 1
      #pragma segment MUSIC
   #endif
   
   #include "ports.h"
   #include "sx_defs.h"

#ifdef SX_SIM
#ifndef TS_H
   #include "ts.h"
#endif
#endif

   #include "sx_types.h"
   #include "sx_globs.h"
   #include "sx_funcs.h"
#endif
