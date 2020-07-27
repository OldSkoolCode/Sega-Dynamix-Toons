#ifndef TS_SHAPE_H
#define TS_SHAPE_H

#include "vm_types.h"
#include "ts_types.h"

/* Shape Data Structures are defined here. */
/* All pointers are offsets to the start of the shape. */
/* use MK_FP(shp_seg,ptr) if the shape is not in the near data segment. */

enum polygon_flags
{
   TS_P_FILL = 0x80,    /* solid fill */
   TS_P_HAS_GI = 0x40,  /* has ground info */
   TS_P_NSHADE = 0x20,  /* normal shading */
   TS_P_DSHADE = 0x10	  /* distance shading */
};

/* the least significan two bits are used to */
/* indicate the visibility test to be used for this polygon. */
enum
{
   TS_ALWAYS,  /* always visible */
   TS_NORMAL,  /* normal test */
   TS_NEVER   /* never visible */
};

typedef struct
{
   ubyte flags;      /* fill and vis test */
   ubyte vga_lcolor; /* line color */
   ubyte vga_fcolor; /* fill color */
   ubyte ega_lcolor; /* line color */
   ubyte ega_fcolor; /* fill color */
   ubyte normal;     /* normal vector */
   uword vlist;      /* vertex list */
}
TS_POLY;

typedef struct
{
   short num_polys;  /* number of polygons */
   uword poly_list;  /* list of polygons */
   short padding;    /* used to pad structure for alignment */
}
TS_GROUP;

typedef struct
{
   short radius;     /* radius of sphere */
   ubyte center;     /* center location */
   ubyte vga_color;  /* sphere color */
   ubyte ega_color;  /* sphere color */
   ubyte padding;    /* used to pad structure for alignment */
}
TS_SPHERE;

typedef struct
{
   short bmp_no;     /* bitmap number */
   short radius;     /* world radius - if zero, shape radius used */
   ubyte true_width; /* if zero, taken from shape structure */
   ubyte center;     /* point number for center */
}
TS_BITMAP;

/* tags for detail defintions */
enum
{
   TS_T_GROUP,       /* group of polygons */
   TS_T_SPHERE,      /* sphere */
   TS_T_BITMAP      /* bitmap */
};

typedef struct
{
   ubyte tag;        /* solid type */
   ubyte padding;    /* used to pad structure for alignment */
   union
   {
      TS_GROUP g;
      TS_SPHERE s;
      TS_BITMAP b;
   }
   gsb;
}
TS_CELL;

typedef struct
{
   ubyte seqno;         /* sequence number */
   ubyte dvector;       /* display vector */
   ubyte dpoint;        /* display point */
   ubyte num_points;    /* # of point in the part */
   uword point_list;    /* point list */
   short num_cells;     /* # of cells */
   uword cell_list;     /* list of cells */
   short num_subparts;  /* # of sub-parts */
   uword subparts;      /* list of sub-parts */
}
TS_PART;

typedef struct
{
   short size;          /* automatic size selection */
   short num_parts;     /* # of parts */
   uword part_list;     /* list of parts */
}
TS_DETAIL;

enum shape_flags
{
   TS_FILTER  = 0x80,   /* filter the parts */
   TS_PARTSORT = 0x40,  /* sort the parts */
   TS_CUBIC = 0x20     /* cubic radius (no extent is given) */
};

typedef struct
{
   ubyte flags;         /* shape flags */
   ubyte shp_class;     /* shape class */
   ubyte priority;      /* sorting priority */
   ubyte scale;         /* point scale */
   short num_seqs;      /* number of seqences */
   uword seq_len;       /* list of sequence lengths */
   short num_details;   /* # of details */
   uword detail_list;   /* list of detail */
   short radius;        /* radius of entire shape */
   IVEC min_extent;     /* not present if TS_CUBIC flag set */
   IVEC max_extent;
}
TS_SHAPE;

#endif
