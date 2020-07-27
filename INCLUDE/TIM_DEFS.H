/* * * * *
*
*  TIM_DEFS.H
*
*  This module defines all the data structures and constants for T.I.M.
*
*  By Chris Cole -- (c) 1993 Dynamix Software Development, Inc.
*
*  Modification History:
*  ---------------------
*  Originally written by Kevin.
*  04/09/93 ChrisC   File created
*
* * * * */
#ifndef TIM_DEFS_H
#define TIM_DEFS_H

/* * * * *
*
*  constants
*
* * * * */
/*set this to 1 to make edit puzzle mode available*/
#define TIM_EDITOR      0

/*set this to 1 to make a demo disk*/
#define TIM_DEMO        0

/*only set one of these defines to 1*/
#define TIM_ENGLISH     0
#define TIM_FRENCH      0
#define TIM_GERMAN      0



#define TIM_ID          0xACED
#define NEW_TIM_ID      0xACEE
#define TIM_VERSION     0x0105


#define SCALE_SHIFT     9
#define ONE_PIX         ( 1<<SCALE_SHIFT)
#define TWO_PIX         ( 2<<SCALE_SHIFT)
#define THREE_PIX       ( 3<<SCALE_SHIFT)
#define FOUR_PIX        ( 4<<SCALE_SHIFT)
#define FIVE_PIX        ( 5<<SCALE_SHIFT)
#define SIX_PIX         ( 6<<SCALE_SHIFT)
#define SEVEN_PIX       ( 7<<SCALE_SHIFT)
#define EIGHT_PIX       ( 8<<SCALE_SHIFT)
#define NINE_PIX        ( 9<<SCALE_SHIFT)
#define TEN_PIX         (10<<SCALE_SHIFT)
#define ELEVEN_PIX      (11<<SCALE_SHIFT)
#define TWELVE_PIX      (12<<SCALE_SHIFT)
#define THIRTEEN_PIX    (13<<SCALE_SHIFT)
#define FOURTEEN_PIX    (14<<SCALE_SHIFT)
#define FIFTEEN_PIX     (15<<SCALE_SHIFT)
#define SIXTEEN_PIX     (16<<SCALE_SHIFT)
#define FIFTY_PIX       (50<<SCALE_SHIFT)
#define BOUNCE_DAMPER   (1<<(SCALE_SHIFT-3))
#define SLIDING_DAMPER  (1<<(SCALE_SHIFT-4))
#define ROLLING_DAMPER  (1<<(SCALE_SHIFT-8))
#define TV_MAX          (16<<SCALE_SHIFT)
#define TV_SHIFT        7
#define TV_DENSITY      128
#define GRAV_MAX        512


#define TRIGSHIFT 14          /*range of sin/cos tables*/


#define WHITE_OUTLINE   11
#define GREEN_OUTLINE   13
#define RED_OUTLINE     15


#define AP_RESIZE_X     0x0001
#define AP_RESIZE_Y     0x0002
#define AP_FLIPS_LR     0x0004
#define AP_FLIPS_TB     0x0008
#define AP_UNLOCK       0x0010
#define AP_FLUSH        0x0020
#define AP_PICKUP       0x0040
#define AP_HEARTY_PART  0x0080


#define PLAYFIELD_TCLIP		0
#define PLAYFIELD_BCLIP		399
#define PLAYFIELD_LCLIP		0
#define PLAYFIELD_RCLIP		639


#define EXCHANGE_X      0x01
#define EXCHANGE_Y      0x02


#define MOVING_NEITHER  -1
#define MOVING_UP       0
#define MOVING_DOWN     1


/*sound effects*/
#define SND_BELT        1
#define SND_BIKE        2
#define SND_JACK_BOX    3
#define SND_BOUNCE      4
#define SND_BOUNCE3     5
#define SND_CANNON      6
#define SND_CAT         7
#define SND_EXPLOSION   8
#define SND_FAN         9
#define SND_GLASS       10
#define SND_GUNSHOT     11
#define SND_HUM         12
#define SND_MOUSE       13
#define SND_POP         14
#define SND_ROCKET      15
#define SND_SHEARS      16
#define SND_SWITCH      17
#define SND_TEETER      18
#define SND_WHEW        19
#define SND_FOOTSTEP    20
#define SND_VACUUM      21
#define SND_YELL        22
#define SND_DOOR        23
#define SND_SLURP       24
#define SND_TEAPOT      25
#define SND_BUMPER      26

/*sound effects - (sound driver tags)*/
#define SND_TG_BELT        1
#define SND_TG_BIKE        2
#define SND_TG_JACK_BOX    3
#define SND_TG_BOUNCE      4
#define SND_TG_BOUNCE3     5
#define SND_TG_CANNON      6
#define SND_TG_CAT         7
#define SND_TG_EXPLOSION   8
#define SND_TG_FAN         9
#define SND_TG_GLASS       10
#define SND_TG_GUNSHOT     11
#define SND_TG_HUM         12
#define SND_TG_MOUSE       13
#define SND_TG_POP         14
#define SND_TG_ROCKET      15
#define SND_TG_SHEARS      16
#define SND_TG_SWITCH      17
#define SND_TG_TEETER      18
#define SND_TG_WHEW        19
#define SND_TG_FOOTSTEP    20
#define SND_TG_VACUUM      51
#define SND_TG_YELL        54
#define SND_TG_DOOR        58
#define SND_TG_SLURP       61
#define SND_TG_TEAPOT      62
#define SND_TG_BUMPER      64

/*music*/
#define MUS_NONE     -1
#define MUS_TITLE    1001
#define MUS_EURO     1002
#define MUS_FUNK     1003
#define MUS_REGG     1004
#define MUS_ZYDI     1005
#define MUS_ROCK     1006
#define MUS_WEST     1007
#define MUS_BLUZ     1008
#define MUS_CLAS     1009
#define MUS_SLSA     1010
#define MUS_PLKA     1011
#define MUS_CRUZ     1012
#define MUS_ROK2     1013
#define MUS_RMNT     1014
#define MUS_FUSN     1015
#define MUS_METL     1016
#define MUS_CRBN     1017
#define MUS_SPLN     1018
#define MUS_MILR     1019
#define MUS_JNGL     1020
#define MUS_EAST     1021


/*control panel locations*/
#define CP_X         32
#define CP_Y         32
#define CP_PLAY_X    58
#define CP_PLAY_Y    91
#define CP_STOP_X    216
#define CP_STOP_Y    96
#define CP_FF_X      57
#define CP_FF_Y      134
#define CP_LOAD_X    150
#define CP_LOAD_Y    140
#define CP_L_DISK_X  166
#define CP_L_DISK_Y  139
#define CP_SND_UP_X  88
#define CP_SND_UP_Y  93
#define CP_SND_DWN_X 88
#define CP_SND_DWN_Y 111
#define CP_SND_X     110
#define CP_SND_Y     96
#define CP_RESTART_X 188
#define CP_RESTART_Y 92
#define CP_SELECT_X  109
#define CP_SELECT_Y  133
#define CP_SAVE_X    200
#define CP_SAVE_Y    140
#define CP_S_DISK_X  216
#define CP_S_DISK_Y  139
#define CP_GRAV_X    65
#define CP_GRAV_Y    200
#define CP_DENS_X    65
#define CP_DENS_Y    276
#define CP_GKNOB_X   61
#define CP_GKNOB_Y   224
#define CP_DKNOB_X   61
#define CP_DKNOB_Y   300
#define CP_BUT_W     54
#define CP_BUT_H     31
#define CP_DESC_X    276
#define CP_DESC_Y    260

/*directory box locations*/
#define DIR_X        48
#define DIR_Y        48
#define DIR_PATH_X   64
#define DIR_PATH_Y   86
#define DIR_LIST_X   64
#define DIR_LIST_Y   124
#define DIR_NAME_X   64
#define DIR_NAME_Y   268
#define DIR_UP_X     188
#define DIR_UP_Y     116
#define DIR_DOWN_X   188
#define DIR_DOWN_Y   224
#if TIM_ENGLISH
#define DIR_OK_X     64
#define DIR_OK_Y     304
#define DIR_OK_W     64
#define DIR_CANC_X   192
#define DIR_CANC_Y   304
#define DIR_CANC_W   80
#elif TIM_GERMAN
#define DIR_OK_X     64
#define DIR_OK_Y     304
#define DIR_OK_LW    74
#define DIR_OK_SW    96
#define DIR_CANC_X   166
#define DIR_CANC_Y   304
#define DIR_CANC_W   106
#elif TIM_FRENCH
#define DIR_OK_X     60
#define DIR_OK_Y     304
#define DIR_OK_LW    90
#define DIR_OK_SW    120
#define DIR_CANC_X   182
#define DIR_CANC_Y   304
#define DIR_CANC_W   98
#endif

/*puzzle select locations*/
#define PUZ_LIST_X   48
#define PUZ_LIST_Y   76
#define PUZ_UP_X     460
#define PUZ_UP_Y     66
#define PUZ_DOWN_X   460
#define PUZ_DOWN_Y   264
#define PUZ_PASS_X   144
#define PUZ_PASS_Y   316
#if TIM_ENGLISH
#elif TIM_GERMAN
#define PUZ_UP_X     500
#define PUZ_UP_Y     66
#define PUZ_DOWN_X   500
#define PUZ_DOWN_Y   264
#define PUZ_PASS_X   176
#define PUZ_PASS_Y   316
#elif TIM_FRENCH
#define PUZ_UP_X     500
#define PUZ_UP_Y     66
#define PUZ_DOWN_X   500
#define PUZ_DOWN_Y   264
#define PUZ_PASS_X   176
#define PUZ_PASS_Y   316
#endif
#define PUZ_PLAY_X   496
#define PUZ_PLAY_Y   300


#define TM_TITLE     0x8000   /*tim_mode (used by active field)*/
#define TM_DEMO      0x4000
#define TM_RUN       0x2000
#define TM_EDIT      0x1000
#define TM_VICTORY   0x0200
#define TM_PARTBIN   0x0004
#define TM_CP        0x0002
#define TM_EXIT      0x0001

#define TM_PB_PLAY   0x0100   /*tim_mode (used by part bin)*/
#define TM_PB_CLEAR  0x0080
#define TM_PB_MORE   0x0040
#define TM_PB_ADD    0x0020
#define TM_PB_LEFT   0x0010
#define TM_PB_RIGHT  0x0008

#define TM_CP_PLAY   0x8000   /*tim_mode (used by control panel)*/
#define TM_CP_SND_UP 0x4000
#define TM_CP_SND_D  0x2000
#define TM_CP_STOP   0x1000
#define TM_CP_RESTRT 0x0800
#define TM_CP_FF     0x0400
#define TM_CP_SELECT 0x0200
#define TM_CP_LOAD   0x0100
#define TM_CP_SAVE   0x0080
#define TM_CP_GRAV   0x0040
#define TM_CP_DENS   0x0020
#define TM_CP_DESC   0x0010
#define TM_CP_PB     0x0008

#define TM_DIR       0x8000   /*tim_mode (used by freeform load/save)*/
#define TM_DIR_PATH  0x4000
#define TM_DIR_LIST  0x2000
#define TM_DIR_NAME  0x1000
#define TM_DIR_UP    0x0800
#define TM_DIR_DOWN  0x0400
#define TM_DIR_OK    0x0200
#define TM_DIR_CANC  0x0100

#define TM_PUZ       0x8000   /*tim_mode (used by puzzle select)*/
#define TM_PUZ_LIST  0x4000
#define TM_PUZ_UP    0x2000
#define TM_PUZ_DOWN  0x1000
#define TM_PUZ_PASS  0x0800
#define TM_PUZ_PLAY  0x0400

#define TM_ASK       0x8000   /*tim_mode (used by ask yes/no)*/
#define TM_ASK_YES   0x4000
#define TM_ASK_NO    0x2000

#define TSM_FLIP_LR        0x0001  /*tim_sub_mode*/
#define TSM_FLIP_TB        0x0002
#define TSM_SIZE_L         0x0003
#define TSM_SIZE_R         0x0004
#define TSM_SIZE_T         0x0005
#define TSM_SIZE_B         0x0006
#define TSM_PICKUP         0x0007
#define TSM_RECYCLE        0x0008
#define TSM_PLACE          0x0009
#define TSM_NONE           0x000A
#define TSM_UNLOCK         0x000B
#define TSM_HEARTY_PART    0x000C
#define TSM_RESIZING       0x8000


/* erase rectangle constants.*/
#define NUM_ER       180
#define ER_FILL      0x01  /*erase_rect flags*/
#define ER_LINE      0x04
#define ER_SLACK_L   0x08


/* force transfer constants.*/
#define NUM_FT 20


/* pulley belt constants.*/
#define MAX_PULLEY_DIST 140
#define PBF_CLOCKWISE   0x0001   /*pulley belt flags*/
#define PBF_C_CLOCKWISE 0x0002
#define PBF_STUCK       0x0004


/* rope constants.*/
#define RP_SLACK        0x0001  /*rope messages*/
#define RP_PULL_UP      0x0002
#define RP_PULL_DOWN    0x0004
#define RP_PULL_LEFT    0x0008
#define RP_PULL_RIGHT   0x0010
#define RP_JUST_CHECK   0x8000


/* gear constants*/
#define GN_LEFT         0     /*gear neighbor array values*/
#define GN_RIGHT        1
#define GN_TOP          2
#define GN_BOTTOM       3

/* old T.I.M. parts*/
#define NUM_PART_TYPES  66    / *number of different types of parts */
#define PT_INCLINE   2+100   
#define PT_C_CAGE    11+100 
#define PT_CAT       12+100 
#define PT_JB        13+100
#define PT_FISHBOWL  15+100
#define PT_BELLOWS   16+100
#define PT_BUCKET    17+100
#define PT_D_PLUNGER 22+100
#define PT_FAN       24+100
#define PT_GENERATOR 26+100
#define PT_L_BULB    29+100
#define PT_MONKEY    31+100
#define PT_PUMPKIN   32+100
#define PT_HEART     33+100
#define PT_CHRISTMAS 34+100
#define PT_BOX_GLOVE 35+100
#define PT_ROCKET    36+100
#define PT_SOLAR_P   38+100
#define PT_WINDMILL  40+100
#define PT_MOUSE     42+100
#define PT_C_SPIPE   47+100
#define PT_E_MOTOR   50+100
#define PT_NAIL      53+100
#define PT_LITTLEGUY 54+100
#define PT_THE       55+100
#define PT_INCRED_M  56+100
#define PT_CREDITS   57+100
#define PT_HOUSE     58+100
#define PT_ALLIGATOR 61+100
#define PT_PINBALL_B 64+100
#define PT_SHAMROCK  65+100
#define PT_FLASHLITE 66+100
#define PT_CANDLE    67+100


/* flag constants.*/
#define F1_ROLLING      0x0001   /*flags1*/
#define F1_COLLIDE      0x0002
#define F1_IMPACT       0x0004
#define F1_DID_IMPACT   0x0008
#define F1_CREATED      0x0010
#define F1_SLIDES       0x0020
#define F1_MULTIDRAW    0x0040
#define F1_ON_SCREEN    0x0080
#define F1_DRAW         0x0100
#define F1_FLIPS_TB     0x0200
#define F1_FLIPS_LR     0x0400
#define F1_AVAIL_L      0x0800
#define F1_MOVE_L       0x1000
#define F1_STATIC_L     0x2000
#define F1_STATIC       0x4000
#define F1_INITIAL      0x8000

#define F2_BELT         0x0001   /*flags2*/
#define F2_BELT_USED    0x0002
#define F2_ROPE1        0x0004
#define F2_ROPE2        0x0008
#define F2_FLIP_H_DRAW  0x0010
#define F2_FLIP_V_DRAW  0x0020
#define F2_INTERNAL     0x0040
#define F2_RESIZE_X     0x0080
#define F2_RESIZE_Y     0x0100
#define F2_FROZEN       0x0200
#define F2_NOT_FROZEN   0x0400
#define F2_ROT_PROVIDE  0x0800
#define F2_SUPERSHAPE   0x1000
#define F2_INACTIVE     0x2000
#define F2_ALWAYS_COL   0x8000

#define F3_ELECT_PART   0x0001   /*flags3*/
#define F3_ELECT_PLUG   0x0002
#define F3_FUSE         0x0004
#define F3_FINE_PLACE   0x0008
#define F3_INSIDE       0x0010
#define F3_IN_DRAW_LIST 0x0020
#define F3_LOCKED       0x0040
#define F3_IN_HOUSE     0x0080
#define F3_HAS_EATEN    0x0080
#define F3_BUMPER_HIT   0x0080
#define F3_IN_VACUUM    0x0100
#define F3_WAS_EATEN    0x0200
#define F3_PUNCHED      0x0400
#define F3_HEARTY_PART  0x0800
#define F3_BACKGROUND   0x8000


/* part element constants.*/
#define D_VALUE   512      /*density*/
#define D_SHIFT   9
#define E_MAX     256      /*elasticity*/
#define E_SHIFT   8
#define F_MAX     256      /*friction*/
#define F_SHIFT   8




/* * * * *
*
*  DATA STRUCTURES
*
* * * * */

typedef void (*VOID_FUNCPTR) ();

#define TIM_CVEC struct tim_cvec
#define TIM_CVEC_C const struct tim_cvec
TIM_CVEC
{
   char           x,y;
};

#define TIM_SCVEC_C const struct tim_scvec
#define TIM_SCVEC struct tim_scvec
struct tim_scvec
{
   signed char    x,y;
};

#define TIM_VEC_C const struct tim_vec
#define TIM_VEC struct tim_vec
struct tim_vec
{
   short          x,y;
};

#define TIM_LVEC struct tim_lvec
#define TIM_LVEC_C const struct tim_lvec
struct tim_lvec
{
   long           x,y;
};

#define LINE_SEG struct line_seg
LINE_SEG
{
   short          x0,y0;
   short          x1,y1;
};

#define RECT struct rect
RECT
{
   short          x,y,w,h;
};

#define SEQ_RECT struct seq_rect
SEQ_RECT
{
   short          x,y,w,h,first_w;
};

#define HOT_SPOT struct hot_spot
typedef void (*VOID_HSFPTR) (HOT_SPOT *);
HOT_SPOT
{
   HOT_SPOT       *next;
   short          active;
   short          id;
   TIM_VEC        upper_left;
   TIM_VEC        lower_right;
   short          icon_num;
   short          new_mode;
   VOID_HSFPTR    over_func;
   VOID_HSFPTR    click_func;
};


#define ERASE_RECT struct ERASE_RECT
ERASE_RECT
{
   ERASE_RECT far *next;
   char           flags;
   char           count;
   TIM_VEC        loc;
   TIM_VEC        size;
   short          slack;
   short          cx;
   short          cxw;
   short          cy;
   short          cyh;
};


struct part_border
{
   WORD          x,y;
   WORD          slope;
};
#define PART_BORDER struct part_border
#define PART_BORDER_C struct part_border
/* #define PART_BORDER_C const struct part_border */
typedef PART_BORDER far * P_PART_BORDER;
typedef PART_BORDER_C far * PC_PART_BORDER_C;
/* typedef PART_BORDER_C far * const PC_PART_BORDER_C; */
typedef P_PART_BORDER far * P_P_PART_BORDER;

#define PART struct part
#define COLLIDE_INFO struct collide_info
COLLIDE_INFO
{
   PART           *part;
   char           left_of_cog_supported;
   char           right_of_cog_supported;
   short          slope;
   short          border_num;
};



#define FORCE_TRANSFER struct force_transfer
FORCE_TRANSFER
{
   FORCE_TRANSFER *next;
   PART           *pptr;
   long           force;
};



#define SSHAPE struct super_shape
#define SSHAPE_C const struct super_shape
#define F_SSHAPE struct super_shape far
#define F_SSHAPE_C const struct super_shape far
struct super_shape
{
   F_SSHAPE_C		*next;
   unsigned char  plane_num;
   unsigned char  shp_num[4];
   TIM_SCVEC		offset[4];
};
typedef F_SSHAPE * P_SSHAPE;
typedef F_SSHAPE_C * const PC_SSHAPE_C;




#define PBELT struct pulley_belt
PBELT
{
   short          flag;
   PART           *root_part;
   PART           *link1;
   PART           *link2;
   TIM_VEC        pt1,pt2,pt3,pt4;
   TIM_VEC        old_pt1,old_pt2,old_pt3,old_pt4;
   TIM_VEC        old_old_pt1,old_old_pt2,old_old_pt3,old_old_pt4;
};



#define ROPE struct rope
ROPE
{
   PART           *root_part;
   PART           *link1,*link2;
   PART           *org_link1,*org_link2;
   char           l1_num,l2_num;
   char           org_l1,org_l2;
   short          slack;
   short          old_slack;
   short          old_old_slack;
   TIM_VEC        pt[2];
   TIM_VEC        old_pt[2];
   TIM_VEC        old_old_pt[2];
};



#define LEVEL struct level
LEVEL
{
   char           name[80];
   char           description[400];
   short          density;
   short          gravity;
   short          max_ledge;
   short          max_tedge;
   short          music_num;
};


PART
{
   PART           *next,*prev;
   short          type;
   short          flags1;
   short          flags2;
   short          flags3;
   short          toon_state;
   short          state;
   short          old_state;
   short          old_old_state;
   short          sub_state;
   char           redraw;
   TIM_LVEC       loc;
   TIM_VEC        scrn_loc;
   TIM_VEC        old_scrn_loc;
   TIM_VEC        old_old_scrn_loc;
   TIM_VEC        adj_loc;
   TIM_VEC        old_adj_loc;
   TIM_VEC        old_old_adj_loc;
   TIM_VEC        speed;
   short          mass;
   long           force;
   TIM_VEC        base_size;     /* Size of the root frame (state 0)*/
   TIM_VEC        offset;        /* Offset to top left of erase rect*/
   TIM_VEC        border_offset; /* Offset borders are relative to*/
   TIM_VEC        size;
   TIM_VEC        old_size;
   TIM_VEC        old_old_size;
   TIM_VEC        place_size;
   PBELT          *belt;
   TIM_CVEC       belt_loc;
   short          belt_size;
   PART           *wpptr[6];
   ROPE           *rope_tie[2];
   TIM_SCVEC      rope_loc[2];
   TIM_SCVEC      plug_loc[2];
   PART           *draw_list[2];
   PART           *qptr;
   TIM_VEC        qdist;
   unsigned char  plug_num;
   unsigned char  plane_num;
   short          num_borders;
   P_PART_BORDER  border;
   COLLIDE_INFO   col_info;
   TIM_VEC        start_scrn_loc;
   short          start_state;
   short          start_sub_state;
   short          start_flags2;
   short          work_var;
   short          old_work_var;
   short          old_old_work_var;
   short          work_var1;
   short          old_work_var1;
   short          old_old_work_var1;
   char           smart_end1, smart_end2;    /* calculated in smartend.c*/
   short          start_memory;
   short          memory;
   PART           *toon_link;
};

typedef void (* const VOID_VFPTR_C) (void);

typedef void (*VOID_VFPTR) (void);
typedef short (*VOID_BPARTFPTR) (PART *);
typedef void (*VOID_PARTFPTR) (PART *);
typedef void (*VOID_FPARTFPTR) (PART *, short);
typedef short (*VOID_RPARTFPTR) (PART *, PART *, short, short, short, long);


#define PART_ELEMENTS struct part_elements
PART_ELEMENTS
{
   short          density;
   short          mass;
   short          elasticity;
   short          friction;
   short          acel;
   short          terminal_velocity;    
   TIM_VEC        max_size;
   TIM_VEC        min_size;
   void        	*part_shapes;
   PC_SSHAPE_C   far *super_shapes;
   TIM_SCVEC_C far  *shp_offset;
   TIM_VEC_C   far  *shape_size;
   SEQ_RECT       *seq_rect;
   unsigned char  plane_num[2];
   short          num_borders;
   short          part_bin_order;
   short          toon_property;
   VOID_BPARTFPTR bounce_func;
   VOID_PARTFPTR  internal_func;
   VOID_PARTFPTR  reinit_func;
   VOID_FPARTFPTR flip_func;
   VOID_PARTFPTR  resize_func;
   VOID_RPARTFPTR rope_func;
};
typedef struct part_elements far * P_PART_ELEMENTS;


typedef short (*VOID_MAKEPFPTR) (PART *);

#define MAKE_PART struct make_part
MAKE_PART
{
   short          flags1;
   short          flags3;
   short          psize_x;
   short          psize_y;
   short          size_x;
   short          size_y;
   VOID_MAKEPFPTR make_func;
};


#define CHARACTER_SEQ const struct character_seq
struct character_seq
{
   char        num_states;
   char        character_index;
   SEQ_RECT    seq_rect;
};

typedef char far * P_TEXT;
typedef P_TEXT far * P_P_TEXT;
           

#endif

