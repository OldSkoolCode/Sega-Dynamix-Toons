#ifndef TS_TYPES_H
#define TS_TYPES_H

/*typedef unsigned char ubyte;  TIM is getting a compile error on this line */
typedef unsigned short uword;
typedef char bool;

typedef struct { char x,y,z; } BVEC;      /* byte vector */
typedef struct { short x,y,z; } IVEC;     /* short vector */
typedef struct { long x,y,z; } LVEC;      /* long vector */
typedef struct { short el[9];             /* 3x3 */
            ubyte num_axis; } MATRIX;     /* short matrix */

enum matrix_elements /* to match up with assembler code */
{
   m_0_0,
   m_0_1,
   m_0_2,
   m_1_0,
   m_1_1,
   m_1_2,
   m_2_0,
   m_2_1,
   m_2_2
};

#endif

