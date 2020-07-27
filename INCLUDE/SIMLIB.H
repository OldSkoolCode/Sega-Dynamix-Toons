#ifndef SIMLIB_H
#define SIMLIB_H

#include "ts.h"
#include "matrices.h"

/*=========================== Defines ======================================= */


#define  TRAVERSE_FOUND       0
#define  TRAVERSE_CONTINUE    1
#define  TRAVERSE_ABORT       2


#define  QUICK_HYP(l,s)    ( l + ( (s >> 2) + (s >> 3) ) )

#define  QUICK_DIST(dx,dy)   (      ( dy > dx ) ?                    \
                                    QUICK_HYP ( dy, dx )    :        \
                                    QUICK_HYP ( dx, dy )    ) 

typedef  short (*FUNC_PTR)( void * );


/* */
/* Return if short or long is in given range using one compare: */
/* */
#define  SHORT_IN_RANGE(S,MIN,MAX)     \
      ( (unsigned short)((S) - (MIN)) <= (unsigned short)((MAX) - (MIN)) )
#define  LONG_IN_RANGE(L,MIN,MAX)      \
      ( (unsigned long)((L)-(MIN)) <= (unsigned long)((MAX)-(MIN)))



/*=========================== ASM Functions ================================= */

/* SLDIVS.ASM: */
/* div_t          ldivs ( long, short ); */


/* SLSHIFT.ASM: */
long           lsar ( long val, short shift );
long           smulsN ( short x, short y, short shift );


/* SLMULTS.ASM: */
short          smuls10 ( short, short );
unsigned long  usmuls ( unsigned short x, unsigned short y );
long           zmuls ( short, short );
short          log_2 ( long );


/*  TCLDIV.C: */
/* ldiv_t   tcldiv ( long numer, long denom ); */


/* SLQDIST.ASM: */
long  comp_dist3 ( LVEC const * loc1, LVEC const * loc2 );
long  comp_hyp ( long, long );
long  comp_dist ( LVEC const *, LVEC const * );


/*=========================== C Functions =================================== */


LVEC * get_center_loc ( register LVEC const pts[], short numpts );
short in_range ( short val, short min, short max );
long longest_leg2 ( LVEC const * loc1, LVEC const * loc2 );
char * base10 ( short num );
short rcosang ( short r, short ang );
short rsinang ( short r, short ang );
IVEC * shift_up_ivec ( IVEC *ivec, short shift );
IVEC * neg_ivec ( IVEC *ivec );
LVEC *lvec_midpoint ( register LVEC const * v1, register LVEC const * v2 );
IVEC * ivec_minus_ivec ( IVEC * v1, IVEC const * v2 );
IVEC * ivec_plus_ivec ( IVEC * v1, IVEC const * v2 );
LVEC * lvec_minus_lvec ( LVEC * v1, LVEC const * v2 );
LVEC * lvec_plus_lvec ( LVEC * v1, LVEC const * v2 );
LVEC * lvec_plus_ivec ( LVEC * lv, IVEC const * iv );
LVEC * lvec_minus_ivec ( LVEC * lv, IVEC const * iv );
LVEC *lvec_gets_lvec_diff ( LVEC *result, LVEC const *v1, LVEC const *v2 );
LVEC *lvec_gets_lvec_sum ( LVEC *result, LVEC const *v1, LVEC const *v2 );
IVEC * scale_unit_ivec ( register IVEC * dir, register short scalar );
IVEC * ivec_gets_lvec ( register IVEC * iv, register LVEC const * lv );
LVEC * lvec_gets_ivec ( register LVEC * lv, register IVEC const * iv );
long ivec_len2 ( register IVEC const * v );
IVEC * ivec_rotate2 ( register IVEC * v, short angle );
void loc_plus_rot ( LVEC * loc, IVEC const * rot, short speed );
long get_desired_rot ( IVEC * rot, LVEC const * ld, LVEC const * ls );
IVEC * rot_gets_vel ( IVEC * rot, IVEC const * vel );
LVEC *lvec_plus_rotvec ( LVEC * loc, short rotz, short length );
short traverse_line
( 
   LVEC        *start,
   short       maxsteps, 
   IVEC        *rot,
   short       len,
   short ( * check ) ( LVEC * pt, IVEC * udir, IVEC * step )
);
void order_longs ( long * min, long * max );
void order_lvecs ( LVEC * min, LVEC * max );
short cubes_intersect 
( 
   LVEC const * c1min, 
   LVEC const * c1max, 
   LVEC const * c2min, 
   LVEC const * c2max 
);

/* SLROT2LV.C: */
LVEC * rot_to_lvec ( LVEC * retbuf, IVEC const * rot, long dist );


short get_zrot ( LVEC const * dst, LVEC const * src );
short signed_scale_down ( register long value, short * scale_ptr );
long  signed_scale_up ( short value );

/* SL_ROT90.C: */
LVEC * rot_lvec_pos90 ( register LVEC * l );
LVEC * rot_lvec_neg90 ( register LVEC * l );


short lvec_within_rad ( register LVEC const * loc, long rad );
short ivec_within_rad( IVEC const * ivec, short rad );
/* IVEC * sar_ivec ( register IVEC * iv ); */
IVEC * ivec_gets_ldif ( IVEC * res, LVEC const * X, LVEC const * minusY );
long interpolatel ( long l1, long l2, short scale, short rshift );
short small_vector_len ( IVEC const * iv );
long good_dist2 ( long dx, long dy );
long get_angles_to ( IVEC * rot, LVEC const * ld, LVEC const * ls );
short do_lmap 
(
   short    dval,
   short    dmin, short dmax,
   short    rmin, short rmax
);
short angle_to ( long dx, long dy );
long square_root ( long n, short accept );
short ts_cos(short angle);
short ts_sin(short angle);

void pt_on_segment 
( 
   long travd, long dist, LVEC const * p1, LVEC const * p2, LVEC * point 
);


/* BITCNT.ASM: */
short bits_in_long ( unsigned long n );
short bits_in_short ( unsigned short n );

LVEC * lvec_plus_scaled_ivec ( LVEC * lv, IVEC const * iv );
void loc_plus_scaled_rot ( LVEC * loc, IVEC const * rot, short speed );


/* Nathan's extensions */
   LVEC *shift_up_lvec(LVEC *l1, short const shift);
   LVEC *lvec_minimize(LVEC *l1, LVEC const *l2);
   LVEC *lvec_maximize(LVEC *l1, LVEC const *l2);
   LVEC far *lvec_fminimize(LVEC far *l1, LVEC const far *l2);
   LVEC far *lvec_fmaximize(LVEC far *l1, LVEC const far *l2);
   LVEC *lvec_plus_scalar(LVEC *l1, LVEC const *l2, short const s);
   LVEC *lvec_minus_scalar(LVEC *l1, LVEC const *l2, short const s);
   LVEC far *flvec_plus_ivec(LVEC far *l, IVEC const *i);

/* LH-2 */
long lvec_max_component ( const LVEC * l );
LVEC * get_abs_lvec ( LVEC * dst, const LVEC * src );
IVEC * ivec_gets_shifted_lvec ( IVEC * dst, const LVEC * src, short down );
LVEC * lvec_gets_shifted_ivec ( LVEC * dst, const IVEC * src, short up );
LVEC * lvec_times_mat ( const LVEC * src, MATRIX * mat, LVEC * dst );
LVEC * lvec_ivec_sum ( LVEC * sum, const LVEC * lv, const IVEC * iv );
LVEC * loc_plus_rot_vec ( LVEC *, const LVEC *, const IVEC *, MATRICES * );

/* MINMAX.C: */
short smin ( short val1, short val2 );
short smax ( short val1, short val2 );

/* INTINRAD.C: */
short short_in_rad ( short val, short rad );

/* LOCINRAD.C: */
short locs_within_srad ( const LVEC * l1, const LVEC * l2, short srad );
short locs_within_lrad ( const LVEC * l1, const LVEC * l2, short srad );

/* PUTINRAD.C: */
short put_in_srad ( short val, short rad );
long put_in_lrad ( long val, long rad );

/* NEGLVEC.C: */
LVEC * neg_lvec ( LVEC * dst, const LVEC * src );

/* CHARSUM.C: */
short sum_char_array ( char * cp, short size );

/* SARIVEC.C: */
IVEC * sar_ivec ( IVEC * iv, short down );

/* ANG2DIR.C: */
IVEC * ang_to_dir ( IVEC * dir, IVEC const * rot );
IVEC * zrot_to_dir ( IVEC * dir, short zrot );


/* CHKDIST.C: */
char check_dist2 ( const LVEC * l1, const LVEC * l2, long thresh );
char check_dist3 ( const LVEC * l1, const LVEC * l2, long thresh );



#endif


