#ifndef MATRICES_H
#define MATRICES_H

typedef struct 
{
   MATRIX   aim;        /* to rotate from object space into world space */
   MATRIX   world;      /* rotate into object space. */
   char     flags;      /*  */
   char     padding;
   IVEC     *rot;       /* rotation vector that is used to create mats. */
} MATRICES;

MATRIX * mat_aim ( MATRICES * m );
MATRIX * mat_world ( MATRICES * m );
void mat_init ( MATRICES * m, IVEC * rot );
void mat_clear ( MATRICES * m );

#endif


