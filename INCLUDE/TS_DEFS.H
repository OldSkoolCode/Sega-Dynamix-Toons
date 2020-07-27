#ifndef TS_DEFS_H
#define TS_DEFS_H

#include "ts_shape.h"
#include "vm_defs.h"

#define TRIGSHIFT 14
#define TS_MAX_PARTS 48
#define TS_MAX_PTS 255
#define TS_MAX_VERTS 20

enum
{
   TS_SML_MATH,   /* small math */
   TS_MED_MATH,   /* medium math */
   TS_BIG_MATH,   /* big math */
   TS_SPC_MATH   /* spherical compression math */
};

/* point processing states */
enum
{
   TS_ROTATED=1,        /* same as transformed for a vector */
   TS_TRANSFORMED=1,
   TS_PROJECTED=2,
   TS_CLIPPED=3
};

typedef struct
{
   short x,y,w,h;
}
TS_BOX;

typedef struct
{
   short shpno;      /* shape number */
   LVEC loc;         /* object location */
   IVEC rot;         /* object rotation */
   ubyte* anim;      /* animation list */
}
TS_OBJECT;

typedef struct
{
   short focal2;     /* focal length power of 2 */
   TS_OBJECT *mount; /* object camera is mounted on */
   IVEC aim;         /* aim vector */
   TS_BOX window;    /* clipping window */
   ubyte *shades;    /* shading */
   ubyte *palmap;    /* color map */
}
TS_CAM;

#endif
