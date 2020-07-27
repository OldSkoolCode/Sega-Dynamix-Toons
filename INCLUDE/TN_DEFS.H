/* * * * *
*
*  TN_DEFS.H
*
*  This modules contains all the definitions needed for the new toons modules.
*
*  By Chris Cole -- (c) 1993 Dynamix Software Development, Inc.
*
*  Modification History:
*  ---------------------
*  03/08/93 ChrisC   File created
*
* * * * */


#define NO_PLANE        0
#define NO_LOCK         0

/* * * * *
*
*  Define the current language.
*
* * * * */
#ifndef ENGLISH
   #define ENGLISH 0
#endif
#ifndef GERMAN
   #define GERMAN    0
#endif
#ifndef FRENCH
   #define FRENCH    0
#endif
#if !ENGLISH && !GERMAN && !FRENCH
   #undef  ENGLISH
   #define ENGLISH   1
#endif

/* * * * *
*
*  ASCII needs to be redefined in foreign languages.
*
* * * * */
#if ENGLISH
#elif FRENCH || GERMAN
   #undef  ASCII
   #define ASCII(k) (k&0xff)
#endif


/* * * * *
*
*  Text styles for draw_text().
*
* * * * */
#define OUTLINE_TEXT    0
#define SHADOW_TEXT     1
#define INDENT_TEXT     2
#define CENTER_TEXT_X   0x10     /* can be added to any above style */
#define CENTER_TEXT_Y   0x20     /* can be added to any above style */


/* * * * *
*
*  Rope Tie sizes and offsets
*
* * * * */
#define ROPETIE_W    18
#define ROPETIE_H    14
#define ROPETIE_X    (-ROPETIE_W/2)
#define ROPETIE_Y    (-ROPETIE_W/2)

/* * * * *
*
*  MISC
*
* * * * */
#define MAX_FORCE (1L<<30)

/* * * * *
*
*  TOON MODES
*
* * * * */
#define TOON_EDIT          0x8000   
#define TOON_FREE_FORM     0x4000   
#define TOON_PUZZLE_MODE   0x2000   
#define TOON_GO            0x4000
#define TOON_CONTROL       0x2000
#define TOON_LEFT          0x1000
#define TOON_RIGHT         0x0800
#define TOON_FAIRY         0x0400
#define TOON_PUZZLE        0x0200
#define TOON_LOAD_ARROW    0x0100
#define TOON_SAVE_ARROW    0x0080
#define TOON_PIG           0x0040
#define TOON_CLAPPER       0x0020
#define TOON_HORN          0x0010
#define TOON_NUKE          0x0008
#define TOON_RIP           0x0004
#define TOON_STOP          0x0002
#define TOON_CHKLIST       0x0001
#define TOON_LOADSAVE      0x0040
#define TOON_OVERRITE      0x0040
#define TOON_HEARTY_PART   0x0001   /* NOTE: 0x0001 is reused here */
#define TOON_COPYPROT      0x0800   /* Must be larger than 128 */


/* toon quit button */
#define TOON_STOP_NO          0x0003
#define TOON_STOP_AFFIRMATIVE 0x0004

/* toon clapper button */
#define TOON_CLAPPER_CAMERA   0x0021
#define TOON_CLAPPER_GOAL     0x0022

/* toon rest in peace button */
#define TOON_RIP_REPLAY       0x0023
#define TOON_RIP_ADVANCE      0x0024

/* toon horn button */
#define TOON_HORN_NEVERMIND   0x0011
#define TOON_HORN_SND_UP      0x0012
#define TOON_HORN_SND_DOWN    0x0013
#define TOON_HORN_CHNL_UP     0x0014
#define TOON_HORN_CHNL_DOWN   0x0015
#define TOON_HORN_HAMMER      0x0016
#define TOON_HORN_TUNE        0x0017
#define TOON_HORN_REPEAT      0x0018

/* toon_nuke button */
#define TOON_NUKE_YES         0x0009
#define TOON_NUKE_NO          0x000A

/* toon pig buttons. */
#define TOON_PIG_CAKE_WALK    0x0041
#define TOON_PIG_ALL_BRAUN    0x0042
#define TOON_PIG_REALLY_HARD  0x0043
#define TOON_PIG_LOONEY_BIN   0x0044
#define TOON_PIG_HOME_TOONS   0x0045
#define TOON_PIG_UP           0x0046
#define TOON_PIG_DOWN         0x0047
#define TOON_PIG_LOAD         0x0048
#define TOON_PIG_CANCEL       0x0049

/* Check list buttons */
#define TOON_CHKLIST_MAKE_TOON   (1000 + 1)
#define TOON_CHKLIST_TEST_TOON   (1000 + 2)
#define TOON_CHKLIST_SAVE_TOON   (1000 + 3)
#define TOON_CHKLIST_GOAL        (1000 + 4)
#define TOON_CHKLIST_LOCK        (1000 + 5)
#define TOON_CHKLIST_TUNES       (1000 + 6)
#define TOON_CHKLIST_CANCEL      (1000 + 7)
#define TOON_CHKLIST_CORNER      (1000 + 8)
#define TOON_CHKLIST_BUTTON      (1000 + 9)     /* On control panel */

/* toonbox buttons. */
#define TOONBOX               0x0004
#define TOONBOX_UP            0x0005
#define TOONBOX_DOWN          0x0006
#define TOONBOX_LEFT          0x0007
#define TOONBOX_RIGHT         0x0008
#define TOONBOX_OK            0x0009

/* hearty part buttons */
#define TOON_HEARTY_PART_UP_ARROW      (1000 + 1)
#define TOON_HEARTY_PART_DOWN_ARROW    (1000 + 2)
#define TOON_HEARTY_PART_CANCEL        (1000 + 3)

/* loadsave buttons */
#define TOON_LOADSAVE_LOAD    (1100 + 1)
#define TOON_LOADSAVE_SAVE    (1100 + 2)

/* overrite buttons */
#define TOON_OVERRITE_OK      (1100 + 1)
#define TOON_OVERRITE_CANCEL  (1100 + 2)

/* copy protection buttons */
#define TOON_COPYPROT_BUTTON  1101
#define TOON_COPYPROT_CORRECT 1102

/* * * * *
*
*  tn_edit.c
*
* * * * */
#define Y_START_OF_BIN  176<<VIRTUALCOORDS
#define X_START_OF_BIN  40<<VIRTUALCOORDS
#define X_END_OF_BIN    256<<VIRTUALCOORDS


/* * * * *
*
*  icon shape table definitions
*
* * * * */
#define IC_NONE            0
#define IC_CLOCK           1
#define IC_HAND            6
#define IC_FLUSH           3
#define IC_FLIPVERT        4
#define IC_PICKUP				5
#define IC_FLIPHORIZ       5
#define IC_SCALELEFT       6
#define IC_SCALERIGHT      6
#define IC_QUESTION        7
#define IC_SCALEUP         7
#define IC_SCALEDOWN       7
#define IC_LOCK            8
#define IC_UNLOCK          8
#define IC_RUBBERBAND      9
#define IC_BELT            8
#define IC_ROPE            9
#define IC_HANDR				10
#define IC_GO              13
#define IC_CP              14
#define IC_LEFT            15
#define IC_RIGHT           16
#define IC_FREE_FORM       17
#define IC_PUZZLE_MODE     18
#define IC_LOAD            19
#define IC_SAVE            20
#define IC_PIG             21
#define IC_CLAPPER         22
#define IC_HORN            23
#define IC_NUKE            24
#define IC_CHKLIST         25
#define IC_STOP            26
#define IC_DOWN            27
#define IC_PAUSE           30
#define IC_PASSWORD        31
#define IC_DONT_KNOW       32
#define NUM_IC             33
#define IC_HEARTY          0
#if 0
   #define IC_FLUSH1          27
   #define IC_SCALELEFT1      28
   #define IC_SCALERIGHT1     28
   #define IC_SCALEUP1        29
   #define IC_SCALEDOWN1      29
   #define IC_FLIPVERT1       30
   #define IC_FLIPHORIZ1      31
   #define IC_LOCK1           32
   #define IC_UNLOCK1         33
   #define IC_PAUSE           34
#endif




/* * * * *
*
*  parts definitions
*
* * * * */
#define CHARACTER_X_RANGE  600
#define TN_NUM_PARTS       85
#define TN_PT_MED_BALL     0


#define PT_HC_BELT         0
#define PT_PBELT           1
#define PT_E_PLUG          2
#define PT_TT              3
#define PT_HAIR_BALL       4        
#define PT_DUSTBUNNY       5
#define PT_ROCK            6
#define PT_YARNBALL        7
#define PT_BASEBALL        8
#define PT_SOCCER          9
#define PT_BEACHBALL       10
#define PT_CAT_EYE_M       11
#define PT_TEAPOT          12
#define PT_VACUUM          13
#define PT_ROPE            14
#define PT_EYEHOOK         15
#define PT_SCISSORS        16
#define PT_PULLEY          17
#define PT_GEAR            18
#define PT_BOMB            19
#define PT_HANDGUN         20
#define PT_BULLET          21
#define PT_CANNON          22
#define PT_CATAPULT        22
#define PT_BALLOON         23
#define PT_TRAMP           24
#define PT_ANT             25 
#define PT_WALL0           26
#define PT_WALL1           27
#define PT_WALL2           28
#define PT_WALL3           29
#define PT_M_GLASS         30
#define PT_STEELY_M        31
#define PT_BOULDER_M       32
#define PT_PEE_WEE_M       33
#define PT_STRIPE_M        34
#define PT_DRAGON          35
#define PT_AL_CAT          36
#define PT_SID_MOUSE       37
#define PT_EGG_TIMER       38
#define PT_UD_COUNTER      39
#define PT_INCR_DECR       40
#define PT_SHOOT_SWTCH     41
#define PT_MESSAGER        42
#define PT_TRANS_ROT       43
#define PT_ROT_TRANS       44
#define PT_LADDER          45
#define PT_TUNNEL          46
#define PT_INCLINE0        47
#define PT_INCLINE1        48
#define PT_INCLINE2        49
#define PT_INCLINE3        50
#define PT_INCLINE4        51
#define PT_HAIRDRYER       52
#define PT_WHISTLE         53
#define PT_GUM             54
#define PT_EGG             55
#define PT_FISH            56
#define PT_CHEESE          57
#define PT_PEANUT          58
#define PT_BANANA          59
#define PT_PIANO           60
#define PT_ANVIL           61
#define PT_WWII_BOMB       62
#define PT_HATPIN          63
#define PT_PENCIL          64
#define PT_HAMMER          65
#define PT_MIRROR          66
#define PT_KNIFE           67
#define PT_ELEPHANT        68
#define PT_CHICKEN         69
#define PT_GUIDO           70
#define PT_GIL             71
#define PT_CHAINSAW        72
#define PT_ONT             73
#define PT_LARD            74
#define PT_EXPLOSION       75
#define PT_PHANTOM         76
#define PT_RUG             77
#define PT_TRAP_DOOR       78
#define PT_BERNY           79
#define PT_FAT_MAN         80
#define PT_ENGINE          81
#define PT_WALL4           82
#define PT_WALL5           83
#define PT_INCLINE5        84


/* T.I.M. placeholder defines. */
#define PT_BOWL_B    8
#define PT_CANNON_B  6
#define PT_EIGHTBALL 11


/* * * * *
*
*  toon string definition.
*
* * * * */
#define TITLE_MAX_STRLEN            (sizeof(cur_level.name)-1)
#define DESCRIPTION_MAX_STRLEN      (sizeof(cur_level.description)-1)
#define DOS_MAX_STRLEN              80
#define PASSWORD_MAX_STRLEN         10

/* * * * *
*
*  POWER BUTTONS 
*
* * * * */
#define BALL_WIDTH   8
#define HANDLE_WIDTH 32


/* * * * *
*
*  BIT SHIFT DEFINITIONS
*
* * * * */
#define EIGHT_BITS         8


/* * * * *
*
*  ALIGNMENT DIRECTIONS
*
* * * * */
#define ALIGN_DOWN         1
#define ALIGN_UP           2
#define ALIGN_LEFT         3
#define ALIGN_RIGHT        4

/* * * * *
*
*  SOUND DEFINITIONS
*
* * * * */
#define NUM_MUSIC_SONGS    32
   #define SONG_NONE          0
   #define SONG1              1001     /* toonsthm     */
   #define SONG2              1002     /* toonsind     */
   #define SONG5              1100     /* VENTURES     */
   #define SONG19             1101     /* MTL2         */
   #define SONG14             1102     /* TS_BEACH     */
   #define SONG11             1103     /* R.E.M.          */
   #define SONG4              1104     /* MORNING         */
   #define SONG22             1105     /* MOZART         */
   #define SONG6              1106     /* JUMP         */
   #define SONG18             1107     /* CAN          */
   #define SONG8              1108     /* BRBR         */
   #define SONG24             1109     /* DOG          */
   #define SONG27             1110     /* MRCH         */
   #define SONG26             1111     /* ARAB         */
   #define SONG7              1112     /* DEVO         */
   #define SONG21             1113     /* METL         */
   #define SONG25             1114     /* ONCL         */
   #define SONG13             1115     /* DSCO         */
   #define SONG12             1116     /* POET         */
   #define SONG9              1117     /* CLSA         */
   #define SONG3              1118     /* STIMPY         */
   #define SONG20             1119     /* ORGN         */
   #define SONG15             1120     /* SEGA         */
   #define SONG16             1121     /* YOGI         */
   #define SONG10             1122     /* BLUDANUB     */
   #define SONG17             1123     /* IRSHWASH     */
   #define SONG28             1124     /* TS_SEL4      */
   #define SONG29             1125     /* TS_SEL1      */
   #define SONG23             1126     /* FREEJAZZ     */
   #define SONG30             1127     /* LAKE */
   #define SONG31             1128     /* FINALE */

/* * * * *
*
*  interface sounds
*
* * * * */
#define SX_TP_FEET         3003
#define SX_TP_BURP         3011
#define SX_GIGGLE          3019
#define SX_GO              3047
#define SX_CONTROL         3054
#define SX_LEFT            3055
#define SX_RIGHT           3056
#define SX_FAIRY           3012
#define SX_PUZZLE          3088 
#define SX_LOAD_ARROW      3017
#define SX_SAVE_ARROW      3086 
#define SX_PIG             3025
#define SX_CLAPPER         3038
#define SX_HORN            3024
#define SX_NUKE            3040 
#define SX_CHKLIST         3044
#define SX_STOP            3033
#define SX_STOP_NO         3052
#define SX_STOP_YES        1
#define SX_CLAPPER_CAMERA  3036
#define SX_HORN_NEVERMIND  3049
#define SX_HORN_SND_UP     3002
#define SX_HORN_SND_DOWN   3027
#define SX_HORN_CHNL_UP    3057
#define SX_HORN_CHNL_DOWN  3052
#define SX_HORN_HAMMER_UP  3028  
#define SX_HORN_HAMMER_DOWN 3001
#define SX_NUKE_YES        3117
#define SX_NUKE_NO         3102 
#define SX_PIG_CAKE_WALK   3019
#define SX_PIG_ALL_BRAUN   3020
#define SX_PIG_REALLY_HARD 3021
#define SX_PIG_LOONEY_BIN  3023 
#define SX_PIG_HOME_TOONS  3110
#define SX_PIG_UP          3062
#define SX_PIG_DOWN        3063
#define SX_PIG_LOAD        3056
#define SX_PIG_CANCEL      3060
#define SX_BOX_UP          0
#define SX_BOX_DOWN        0
#define SX_BOX_LEFT        0
#define SX_BOX_RIGHT       0
#define SX_BOX_OK          0
#define SX_TSM_FLIP_LR     23
#define SX_TSM_FLIP_TB     3032
#define SX_TSM_SIZE_L      8
#define SX_TSM_SIZE_R      22
#define SX_TSM_SIZE_T      7
#define SX_TSM_SIZE_B      3027
#define SX_TSM_PICKUP      3056
#define SX_TSM_RECYCLE     3066
#define SX_TSM_PLACE       3002
#define SX_TSM_NONE        0
#define SX_TSM_UNLOCK      3017
#define SX_TSM_RESIZING    3056
#define SX_TSM_HEART_PART  3048
#define SX_VICTORY         3011

/* * * * *
*
*  part sounds
*
* * * * */
#define SX_CONVEYOR        0  
#define SX_SWITCH          3006
#define SX_TEETER_TOTTER   3082
#define SX_HAIRBALL        3005
#define SX_ROCK            3006
#define SX_BASEBALL        3086
#define SX_SOCCER          3002
#define SX_TEAPOT_GASP     3114
#define SX_TEAPOT_BLOW     0  
#define SX_VACUUM          0  
#define SX_SCISSORS        3054
#define SX_BOMB            3122
#define SX_GUN_GASP        3031
#define SX_GUN_SPIT        3008
#define SX_CATAPULT        3010
#define SX_BALLOON         3040
#define SX_BALLOON_BOUNCE  32
#define SX_TRAMP           3002
#define SX_ANT_GRUNT       3003
#define SX_DRAGON_GASP     3031
#define SX_DRAGON_BLOW     3143
#define SX_DRAGON_BURP     3035
#define SX_EGGTIMER_TICK   15
#define SX_EGGTIMER_ARM    3009
#define SX_UPDOWN_COUNTER  3017
#define SX_INCRE_DECRE     3088
#define SX_CHUTE_SWITCH    3123
#define SX_HAIRDRYER       0  
#define SX_NOONWHISTLE     3089
#define SX_EGG             3067
#define SX_PIANO           3074
#define SX_WW2_BOMB        9
#define SX_ELEPHANT_FLIP   3010
#define SX_ELEPHANT_SUCK   0  
#define SX_ELEPHANT_BLOW   3045
#define SX_ELEPHANT_SCARED 3118
#define SX_ELEPHANT_EAT    3073  
#define SX_CHICKEN_HEN     3077
#define SX_CHICKEN_DOG     3062
#define SX_CHICKEN_PIG     3025
#define SX_CHICKEN_DUCK    3026
#define SX_CHICKEN_BURP    3035
#define SX_EXPLOSION1      3007
#define SX_EXPLOSION2      3112
#define SX_EXPLOSION3      3113
#define SX_TRAPDOOR        3082
#define SX_FATMAN_EAT      3104
#define SX_FATMAN_WALK     3041
#define SX_MESSAGE         3009

/* * * * *
*
*  generic sounds
*
* * * * */
#define SX_CUTTING         3054
#define SX_CLANK           3055
#define SX_WHOP            3056

/* * * * *
*
*  cat sounds
*
* * * * */
#define SX_CAT_SCREECK     3053
#define SX_CAT_SHAKE       3050
#define SX_CAT_CRACK       3004
#define SX_CAT_CRUMBLE     3065
#define SX_CAT_WALK        3003
#define SX_CAT_JUMP        3002
#define SX_CAT_BIRDS_BONK  6
#define SX_CAT_BIRDS       3051
#define SX_CAT_SMASH       3053
#define SX_CAT_YARN_JUMP   3062
#define SX_CAT_FIGHT0      3053
#define SX_CAT_FIGHT1      3062
#define SX_CAT_FIGHT2      3103
#define SX_CAT_FIGHT3      3104
#define SX_CAT_FLAIL       3059
#define SX_CAT_ANGEL       3012
#define SX_CAT_LICK_TAIL   3013
#define SX_CAT_GAG         3014
#define SX_CAT_HAIR        3015
#define SX_CAT_SHOT        3039
#define SX_CAT_SHOT_HIT    3061
#define SX_CAT_SHOT_LILI   3017
#define SX_CAT_SNORING     3016
#define SX_CAT_SKID        3011
#define SX_CAT_ATE_SHAKE   3042
#define SX_CAT_ATE_CRUMPLE 3044
#define SX_CAT_ATE_THROW   8
#define SX_CAT_ATE_GULP    3073
#define SX_CAT_ATE_CHEW    3043
#define SX_CAT_ATE_SLURP   3013
#define SX_CAT_ATE_BURP    3035
#define SX_CAT_BANANA_SQUEEZE 3072
#define SX_CAT_BANANA_THROW 18
#define SX_CAT_BANANA_GULP 3073
#define SX_CAT_BANANA_CHEW 3064
#define SX_CAT_BOMB        3065
#define SX_CAT_BUTT        3043
#define SX_CAT_CLIMB       5
#define SX_CAT_EGG_CRACK   3067
#define SX_CAT_EGG_MAD     3003
#define SX_CAT_EGG_BURN    3044
#define SX_CAT_FISH_GULP   3104
#define SX_CAT_FISH_PULL   7
#define SX_CAT_GUM_SPLAT   3005
#define SX_CAT_GUM_CHEW    3043
#define SX_CAT_GUM_GULP    3073
#define SX_CAT_GUM_POP     3040
#define SX_CAT_GUM_SLURP   3013
#define SX_CAT_GUM_BLOW    3070
#define SX_CAT_GUM_GRAB    16
#define SX_CAT_GUM_THROW   8
#define SX_CAT_GUM_SWALLOW 3073
#define SX_CAT_HIT_FLOOR   3002
#define SX_CAT_HIT_CEILING 3055
#define SX_CAT_HIT_WALL    3067
#define SX_CAT_LUNCH_PAIL_OUT 3130
#define SX_CAT_LUNCH_PAIL_DOWN 3005
#define SX_CAT_LUNCH_LUNCH_POP 3017
#define SX_CAT_LUNCH_FALL_DOWN 18
#define SX_CAT_LUNCH_CRASH 3028
#define SX_CAT_LUNCH_SLURP_TEA 3013
#define SX_CAT_LUNCH_CHEW  3064
#define SX_CAT_LUNCH_KICK  3028
#define SX_CAT_PEEL_SLIP   8
#define SX_CAT_PEEL_HIT    3003
#define SX_CAT_PENCIL_PICKUP 3010
#define SX_CAT_PENCIL_ERASE 3075
#define SX_CAT_PENCIL_THROW 21
#define SX_CAT_PIN         10
#define SX_CAT_PIN3_YELL   3061
#define SX_CAT_POUNCE      3053
#define SX_CAT_RUG         3059
#define SX_CAT_RUN         3041
#define SX_CAT_RUNAW       3041
#define SX_CAT_SCRATCH     3010
#define SX_CAT_SLIDE1      0        /*3100 */
#define SX_CAT_SLIDE2      0        /*3110 */
#define SX_CAT_SLIDE3      0        /*3119 */
#define SX_CAT_SLIDE4      0        /*2008 */
#define SX_CAT_SPIN0       3138     /* growl */
#define SX_CAT_SPIN1       3139     /* I am going to tell */
#define SX_CAT_SPIN2       3135     /* one of these days */
#define SX_CAT_SPIN3       3092     /* I will moiderize him */
#define SX_CAT_SPIN4       3093     /* Oh a wiseguy, huh! */
#define SX_CAT_SPINAW      3061
#define SX_CAT_STOP        3009
#define SX_CAT_TAKE        3052
#define SX_CAT_TUNNEL_POCKET 3044
#define SX_CAT_TUNNEL_MATCH 3069
#define SX_CAT_TUNNEL_POOF 5
#define SX_CAT_TUNNEL_TOSS 3010
#define SX_CAT_TUNNEL_SQUEEZE 3043
#define SX_CAT_TUNNEL_OUT  3003
#define SX_CAT_TUNNEL_HIT  3024
#define SX_CAT_TUNNEL_POP1 3017
#define SX_CAT_TUNNEL_POP2 3102
#define SX_CAT_VAC_SUCKED  3084

/* * * * *
*
* sid sounds
*
* * * * */
#define SX_SID_ANVIL       22
#define SX_SID_BANANA_HUM  3115
#define SX_SID_BANANA_SQUEEZE 3072
#define SX_SID_BANANA_THROW 3010
#define SX_SID_BANANA_SMACK 3064
#define SX_SID_BOMB_GASP   3031
#define SX_SID_BOMB_YELL   3061
#define SX_SID_BOMB_GIGGLE 3019
#define SX_SID_BOMB_FALL   9
#define SX_SID_BONK_SQUEEK 16
#define SX_SID_BONK_HEAD   2
#define SX_SID_BRONX       3021
#define SX_SID_GIGGLE      3019
#define SX_SID_GUM_CHEW    3043  /*6 ALT */
#define SX_SID_GUM_BLOW    3070
#define SX_SID_BUBBLE      3040  /*3005 ALT */
#define SX_SID_BUBBLE2_HIT 3005
#define SX_SID_BUBBLE2_STRETCH 3043
#define SX_SID_BUBBLE2_SHAKE 3063
#define SX_SID_BUTT_YELL   3061
#define SX_SID_CHEESE_LIFT 8
#define SX_SID_CHEESE_CRASH 3071
#define SX_SID_CLIMB       5
#define SX_SID_DRAGON_BURN 3044
#define SX_SID_DRAGON_CRUMPLE 3065
#define SX_SID_DUSTBUNNY_GASP 3031
#define SX_SID_DUSTBUNNY_SNEEZE 3008
#define SX_SID_EGG_CRACK   3067
#define SX_SID_EGG_BIRDS   3051
#define SX_SID_EGG_CLAP    3036
#define SX_SID_FALL        3051
#define SX_SID_GUN_ROUND   3001
#define SX_SID_GUN_DIZZY   3051
#define SX_SID_HAIR_HIT    3044
#define SX_SID_HAIR_STATUE 3046
#define SX_SID_HAIR_FALL   3065
#define SX_SID_HAIRDRYER   3005
#define SX_SID_HEADLESS    9
#define SX_SID_HIT_CEILING 3047
#define SX_SID_HIT_FLOOR   3047
#define SX_SID_HIT_WALL    3103
#define SX_SID_LUNCH_PAIL  3006
#define SX_SID_LUNCH_GASP  3031
#define SX_SID_LUNCH_CHOMP 3104
#define SX_SID_LUNCH_CHEW  3064
#define SX_SID_LUNCH_DONE  3131
#define SX_SID_PEEL        3061
#define SX_SID_PENCIL1     3131  /*3010 ALT */
#define SX_SID_PENCIL2     3041
#define SX_SID_PENCIL3_1   3075
#define SX_SID_PENCIL3_2   3131  /*3010 ALT */
#define SX_SID_PENCIL3_3   3002
#define SX_SID_PENCIL3_4   3009
#define SX_SID_PENCIL3_5   3040
#define SX_SID_PENCIL4_1   21
#define SX_SID_PENCIL4_2   3131  /*3010 ALT */
#define SX_SID_PIN1_HIT    10
#define SX_SID_PIN1_YELL   3090
#define SX_SID_PIN2_HIT    10
#define SX_SID_PIN2_YELL   3043  /*6 ALT */
#define SX_SID_RUN         13    /* 5     3041 ALT originally 3102 */
#define SX_SID_SHAKE       3063
#define SX_SID_STOP_1      3033
#define SX_SID_STOP_2      3009
#define SX_SID_TAKE        3023  /*3057,3022 ALT */
#define SX_SID_TUNNEL_HELMET 3055
#define SX_SID_TUNNEL_ZIP  3010
#define SX_SID_TUNNEL_LIGHT 5
#define SX_SID_TUNNEL_HAT  3105
#define SX_SID_TUNNEL_HUM  3115
#define SX_SID_TUNNEL_OUT  3010  /*3001 ALT */
#define SX_SID_WAIT1       5     /*3041 ALT */
#define SX_SID_WAIT2       3043  /*6 ALT */
#define SX_SID_WAIT3       3043  /*3131,3044  ALT */
#define SX_SID_WAIT4_1     3125  
#define SX_SID_WAIT4_2     3064
#define SX_SID_WALK        3     /* 5  3041 ALT      */

/* * * * *
*
*  PART DEFINITIONS
*
* * * * */
#define BULLET_PLANE          5
#define BULLET_PLANE1         -1
#define BULLET_BORDERS        4
#define BULLET_NUM_STATES     3
#define BULLET_SPEED          (SIXTEEN_PIX+EIGHT_PIX)
#define BOMB_PLANE            2
#define BOMB_PLANE1           -1
#define BOMB_BORDERS          9
#define BOMB_NUM_STATES       9
#define WW2BOMB_PLANE         2
#define WW2BOMB_PLANE1        -1
#define WW2BOMB_BORDERS       6
#define WW2BOMB_NUM_STATES    4
#define EXPLOSION_PLANE       0
#define EXPLOSION_PLANE1      0
#define HAIR_SPEED            SIXTEEN_PIX
#define DRAGON_PLANE          4
#define DRAGON_PLANE1         4
#define DRAGON_BORDERS        9
#define DRAGON_NUM_STATES     11
#define DRAGON_REST           0
#define DRAGON_FIRE           1
#define CATAPULT_PLANE        4
#define CATAPULT_PLANE1       4
#define CATAPULT_BORDERS      7
#define CATAPULT_NUM_STATES   19
#define EGG_TIMER_NUM_STATES  17
#define EGG_TIMER_BORDERS     10
#define EGG_TIMER_PLANE       4
#define EGG_TIMER_PLANE1      4
#define EGG_THRESHOLD         FIVE_PIX
#define TUNNEL_BORDERS        0
#define TUNNEL_PLANE          5
#define TUNNEL_PLANE1         -1
#define CHUTESWITCH_PLANE     5
#define CHUTESWITCH_PLANE1    -1
#define CHUTESWITCH_BORDERS   8
#define CHUTESWITCH_NUM_STATES 3
#define UPDOWN_PLANE          5
#define UPDOWN_PLANE1         5
#define UPDOWN_BORDERS        8
#define MESSAGE_PLANE         5
#define MESSAGE_PLANE1        5
#define MESSAGE_BORDERS       6
#define MESSAGE_NUM_STATES    7
#define ROTTRANS_PLANE        5
#define ROTTRANS_PLANE1       5
#define ROTTRANS_BORDERS      7
#define ROTTRANS_BELT_SIZE    28 /* 29 */
#define TRANSROT_PLANE        5
#define TRANSROT_PLANE1       5
#define TRANSROT_BORDERS      8
#define TRANSROT_NUM_STATES   7
#define TRANSROT_BELT_SIZE    6 /* 4     used in TN_FREE.C */
#define INCDEC_PLANE          5
#define INCDEC_PLANE1         5
#define INCDEC_MACHINE_SIZE_Y 65
#define INCDEC_TBUT_START_Y   0    
#define INCDEC_TBUT_SIZE_Y    17    
#define INCDEC_TBUT_START_X   17    
#define INCDEC_TBUT_SIZE_X    26    
#define INCDEC_BBUT_START_Y   0    
#define INCDEC_BBUT_SIZE_Y    9    
#define INCDEC_BBUT_START_X   19    
#define INCDEC_BBUT_SIZE_X    24    
#define INCDEC_SIZE_Y         (INCDEC_MACHINE_SIZE_Y+INCDEC_TBUT_SIZE_Y+INCDEC_BBUT_SIZE_Y)    
#define INCDEC_SIZE_MAX_X     142
#define INCDEC_SIZE_MIN_X     102
#define INCDEC_MAX_NUM        5
#define INCDEC_BORDERS        (6+INCDEC_MAX_NUM*4+6) 
#define MEMORY_RUN_BIT        0x0020
#define MEMORY_DOWN_BIT       0x0040
#define MEMORY_ORIENT_LEFT_BIT 0x0080
#define MEMORY_EXIT_BLOCK     0x001F
#define MEMORY_NO_EXIT        31
#define EXIT_SCALE            0
#define BLOCK_SCALE           4
#define HATPIN_BORDERS        5
#define GUM_BORDERS           6
#define NUT_BORDERS           8
#define PENCIL_BORDERS        5
#define CHEESE_BORDERS        8
#define PIANO_PLANE           1
#define PIANO_PLANE1          1
#define PIANO_BORDERS         9
#define PIANO_NUM_STATES  8
#define PIANO_FALL_THRESHOLD  FOUR_PIX
#define HAIRDRYER_PLANE       4
#define HAIRDRYER_PLANE1      -1
#define HAIRDRYER_BORDERS     10
#define NOONWHISTLE_PLANE     4
#define NOONWHISTLE_PLANE1    4
#define NOONWHISTLE_BORDERS   5
#define NOONWHISTLE_NUM_STATES 11
#define ELEPHANT_PLANE        4
#define ELEPHANT_PLANE1       4
#define ELEPHANT_BORDERS      7
#define ELEPHANT_NUM_STATES   21
#define FISH_PLANE            2
#define FISH_PLANE1           -1
#define FISH_BORDERS          9
#define EGG_PLANE             2
#define EGG_PLANE1            -1
#define EGG_BORDERS           8
#define EGG_NUM_STATES        16
#define BANANA_PLANE          2
#define BANANA_PLANE1         -1
#define BANANA_BORDERS        5
#define BANANA_NUM_STATES     5
#define BANANA_PEEL           4
#define RUG_PLANE             5
#define RUG_PLANE1            -1
#define RUG_BORDERS           4
#define RUG_NUM_STATES        2
#define CHICKEN_PLANE         2
#define CHICKEN_PLANE1        -1
#define CHICKEN_BORDERS       8
#define CHICKEN_NUM_STATES    5
#define HAMMER_PLANE          4
#define HAMMER_PLANE1         -1
#define HAMMER_BORDERS        9
#define TRAPDOOR_PLANE        5
#define TRAPDOOR_PLANE1       5
#define TRAPDOOR_BORDERS      4
#define TRAPDOOR_NUM_STATES   15
#define CONVEYOR_PLANE        5
#define CONVEYOR_PLANE1       -1
#define CONVEYOR_BORDERS      4
#define BELT_PLANE            0
#define BELT_PLANE1           -1
#define SWITCH_PLANE          5
#define SWITCH_PLANE1         -1
#define SWITCH_BORDERS        4
#define TT_PLANE              4
#define TT_PLANE1             -1
#define TT_BORDERS            8
#define TT_NUM_STATES         3
#define WALL_PLANE            5
#define WALL_PLANE1           -1
#define WALL_BORDERS          4
#define LADDER_PLANE          4
#define LADDER_PLANE1         -1
#define HAIRBALL_PLANE        1  
#define HAIRBALL_PLANE1       -1
#define HAIRBALL_BORDERS      2
#define DUSTBUNNY_PLANE       1
#define DUSTBUNNY_PLANE1      -1
#define DUSTBUNNY_BORDERS     8
#define BALL_PLANE            2
#define BALL_PLANE1           -1
#define BALL_BORDERS          8
#define TEAPOT_PLANE          3
#define TEAPOT_PLANE1         -1
#define TEAPOT_BORDERS        9
#define SCISSORS_PLANE        0
#define SCISSORS_PLANE1       4
#define SCISSORS_BORDERS      10
#define ANT_ERNATOR_PLANE     4
#define ANT_ERNATOR_PLANE1    -1
#define ANT_ERNATOR_BORDERS   6
#define EATMOTOR_PLANE        4
#define EATMOTOR_PLANE1       4
#define EATMOTOR_BORDERS      6
#define EATMOTOR_NUM_STATES   16
#define GUN_PLANE             4
#define GUN_PLANE1            -1
#define GUN_BORDERS           11
#define GUN_NUM_STATES        5
#define VACUUM_PLANE          2
#define VACUUM_PLANE1         -1
#define VACUUM_BORDERS        9
#define VACUUM_NUM_STATES     4


/* * * * *
*
*  AL CAT DEFINITIONS
*
* * * * */
#define CAT_LINK                       0
#define CAT_PLANE                      3
#define CAT_PLANE1                     3
#define CAT_WIDTH                      50
#define CAT_HEIGHT                     50
#define CAT_NUM_SEQUENCES              60
#define CAT_BORDERS                    6
#define CAT_POUNCE_DIST                80
#define CAT_POUNCE_RUN_DIST            35

/* cat sequence indices */
#define CAT_ROOT_INDEX                 0     /*catroot.bmp */
#define CAT_SLEEP_INDEX                1     /*catsleep.bmp */
#define CAT_BOMB_INDEX                 2     /*catbomb.bmp */
#define CAT_WALK_INDEX                 3     /*catwalk.bmp */
#define CAT_CRACK_INDEX                4     /*catcrack.bmp */
#define CAT_SHAKE_INDEX                5     /*catshake.bmp */
#define CAT_RUN_INDEX                  6     /*catrun.bmp */
#define CAT_HAIR_INDEX                 7     /*catshake.bmp */
#define CAT_BIRDS_INDEX                8     /*catbirds.bmp */
#define CAT_FLAIL_INDEX                9     /*catflail.bmp */
#define CAT_UNUSED1_INDEX              10     
#define CAT_UNUSED2_INDEX              11
#define CAT_UNUSED3_INDEX              12
#define CAT_UNUSED4_INDEX              13
#define CAT_POUNCE_INDEX               14    /* catpounc.bmp */
#define CAT_YARN_INDEX                 15    /* catyarn.bmp */
#define CAT_SHOT_INDEX                 16    /*catshot.bmp */
#define CAT_ANGEL_INDEX                17    /*catshot.bmp */
#define CAT_SPIN_INDEX                 18    /*catrun.bmp */
#define CAT_SKID_INDEX                 19    /*catrun.bmp */
#define CAT_ATE_INDEX                  20    /*sid_ate.bmp */
#define CAT_RUNAW_INDEX                21    /*catrunaw.bmp */
#define CAT_SPINAW_INDEX               22    /*catrunaw.bmp */
#define CAT_TAKE_INDEX                 23    /*cattake.bmp */
#define CAT_CLIMB_INDEX                24    /*catclimb.bmp */
#define CAT_CUT_INDEX                  25    /* catcut.bmp */
#define CAT_STOP_INDEX                 26    /* catstop.bmp */
#define CAT_HIT_FLOOR_INDEX            27    /* catsmash.bmp */
#define CAT_HIT_CEILING_INDEX          28   /* catsmash.bmp */
#define CAT_HIT_LEFT_WALL_INDEX        29    /* catsmash.bmp */
#define CAT_HIT_RIGHT_WALL_INDEX       30    /* catsmash.bmp */
#define CAT_SLIDE1_INDEX               31    /* catslide.bmp */
#define CAT_SLIDE2_INDEX               32    /* catslide.bmp */
#define CAT_SLIDE3_INDEX               33    /* catslide.bmp */
#define CAT_SLIDE4_INDEX               34    /* catslide.bmp */
#define CAT_PIN1_INDEX                 35    /* catpin1.bmp */
#define CAT_PIN2_INDEX                 36    /* catpin2.bmp */
#define CAT_PIN3_INDEX                 37    /* catpin3.bmp */
#define CAT_VAC1_INDEX                 38    /* catvac.bmp */
#define CAT_VAC2_INDEX                 39    /* catvac.bmp */
#define CAT_VAC3_INDEX                 40    /* catvac.bmp */
#define CAT_PIANO_INDEX                41    /* catpiano.bmp */
#define CAT_GUM_INDEX                  42    /* catgum.bmp */
#define CAT_BUTT_INDEX                 43    /* catbutt.bmp */
#define CAT_LUNCH_INDEX                44    /* catlunch.bmp */
#define CAT_TUNNEL_INDEX               45    /* catunnel.bmp */
#define CAT_PENCIL1_INDEX              46    /* catpencl.bmp */
#define CAT_PENCIL2_INDEX              47    /* catpencl.bmp */
#define CAT_SCRATCH_INDEX              48    /* catsrtch.bmp */
#define CAT_PENCIL4_INDEX              49    /* catpencl.bmp */
#define CAT_FISH_INDEX                 50    /* catfish.bmp */
#define CAT_HAIRDRYER_INDEX            51    /* cathdryr.bmp */
#define CAT_MIRROR1_INDEX              52    /* catmiror.bmp */
#define CAT_MIRROR2_INDEX              53    /* catmiror.bmp */
#define CAT_PEEL_INDEX                 54    /* catpeel.bmp */
#define CAT_BANANA_INDEX               55    /* catbanan.bmp */
#define CAT_RUG_INDEX                  56    /* catrug.bmp */
#define CAT_GUM2_INDEX                 57    /* catgum.bmp */
#define CAT_GUM3_INDEX                 58    /* catgum.bmp */
#define CAT_EGG_INDEX                  59    /* categg.bmp */

/* cat number of frames in sequences */
#define CAT_ROOT_NUM_STATES            1
#define CAT_SLEEP_NUM_STATES           3
#define CAT_BOMB_NUM_STATES            10
#define CAT_WALK_NUM_STATES            11
#define CAT_CRACK_NUM_STATES           10
#define CAT_SHAKE_NUM_STATES           4
#define CAT_RUN_NUM_STATES             4
#define CAT_HAIR_NUM_STATES            13
#define CAT_BIRDS_NUM_STATES           11
#define CAT_FLAIL_NUM_STATES           12
#define CAT_UNUSED1_NUM_STATES         0
#define CAT_UNUSED2_NUM_STATES         0
#define CAT_UNUSED3_NUM_STATES         0
#define CAT_UNUSED4_NUM_STATES         24   
#define CAT_POUNCE_NUM_STATES          3
#define CAT_YARN_NUM_STATES            6
#define CAT_SHOT_NUM_STATES            12
#define CAT_ANGEL_NUM_STATES           3
#define CAT_SPIN_NUM_STATES            4
#define CAT_SKID_NUM_STATES            4
#define CAT_ATE_NUM_STATES             47
#define CAT_RUNAW_NUM_STATES           4
#define CAT_SPINAW_NUM_STATES          4
#define CAT_TAKE_NUM_STATES            4
#define CAT_CLIMB_NUM_STATES           3
#define CAT_CUT_NUM_STATES             4
#define CAT_STOP_NUM_STATES            6
#define CAT_HIT_FLOOR_NUM_STATES       3  
#define CAT_HIT_CEILING_NUM_STATES     3
#define CAT_HIT_LEFT_WALL_NUM_STATES   1
#define CAT_HIT_RIGHT_WALL_NUM_STATES  1
#define CAT_SLIDE1_NUM_STATES          3
#define CAT_SLIDE2_NUM_STATES          3
#define CAT_SLIDE3_NUM_STATES          3
#define CAT_SLIDE4_NUM_STATES          3
#define CAT_PIN1_NUM_STATES            2
#define CAT_PIN2_NUM_STATES            3
#define CAT_PIN3_NUM_STATES            4
#define CAT_VAC1_NUM_STATES            2
#define CAT_VAC2_NUM_STATES            8
#define CAT_VAC3_NUM_STATES            1
#define CAT_PIANO_NUM_STATES           5
#define CAT_GUM_NUM_STATES             28
#define CAT_BUTT_NUM_STATES            2
#define CAT_LUNCH_NUM_STATES           56
#define CAT_TUNNEL_NUM_STATES          36
#define CAT_PENCIL1_NUM_STATES         3
#define CAT_PENCIL2_NUM_STATES         12
#define CAT_SCRATCH_NUM_STATES         6
#define CAT_PENCIL4_NUM_STATES         7
#define CAT_FISH_NUM_STATES            16
#define CAT_HAIRDRYER_NUM_STATES       3
#define CAT_MIRROR1_NUM_STATES         13
#define CAT_MIRROR2_NUM_STATES         13
#define CAT_PEEL_NUM_STATES            12
#define CAT_BANANA_NUM_STATES          13
#define CAT_RUG_NUM_STATES             1
#define CAT_GUM2_NUM_STATES            2
#define CAT_GUM3_NUM_STATES            16
#define CAT_EGG_NUM_STATES             29

/* cat number of sequence starting shape */
#include "catequ.h"

/* * * * *
*
*  SID MOUSE DEFINITIONS
*
* * * * */
#define SID_LINK                       0
#define SID_PLANE                      3
#define SID_PLANE1                     3
#define SID_WIDTH                      50
#define SID_HEIGHT                     50
#define SID_NUM_SEQUENCES              57
#define SID_BORDERS                    4

/* mouse sequence indices */
#define SID_ROOT_INDEX                 0     /* sidroot.bmp */
#define SID_TAKE_INDEX                 1     /* sidtake.bmp */
#define SID_RUN_INDEX                  2     /* sidrun.bmp */
#define SID_GIGGLE_INDEX               3     /* sidgiggl.bmp */
#define SID_BRONX_INDEX                4     /* sidbronx.bmp */
#define SID_FALL_INDEX                 5     /* sidfall.bmp */
#define SID_SPLAT_INDEX                6     /* sidsplat.bmp */
#define SID_WAIT_INDEX                 7     /* sidwalk.bmp */
#define SID_HAIR_INDEX                 8     /* sidhair.bmp */
#define SID_CUT_INDEX                  9     /* sidcut.bmp */
#define SID_WHOP_INDEX                 10    /* sidwhop.bmp */
#define SID_CLIMB_INDEX                11    /* sidclimb.bmp */
#define SID_WALK_INDEX                 12    /* sidwailk.bmp */
#define SID_GUN_INDEX                  13    /* sidgun.bmp */
#define SID_DUSTB_INDEX                14    /* siddustb.bmp */
#define SID_BUTT_INDEX                 15    /* sidbutt.bmp */
#define SID_BONK_INDEX                 16    /* sidbonk.bmp */
#define SID_ANVIL_INDEX                17    /* sidanvil.bmp */
#define SID_CHEESE_INDEX               18    /* sidcheez.bmp */
#define SID_LUNCH_INDEX                19    /* sidlunch.bmp */
#define SID_PIANO_INDEX                20    /* sidpiano.bmp */
#define SID_HIT_FLOOR_INDEX            21    /* sidfall.bmp */
#define SID_HIT_CEILING_INDEX          22    /* sidfall.bmp */
#define SID_HIT_LEFT_WALL_INDEX        23    /* sidfall.bmp */
#define SID_HIT_RIGHT_WALL_INDEX       24    /* sidfall.bmp */
#define SID_FLY_UP_INDEX               25    /* sidroot.bmp */
#define SID_BOMB_INDEX                 26    /* sidbomb.bmp */
#define SID_SHAKE_INDEX                27    /* sidshake.bmp */
#define SID_DRAGON_INDEX               28    /* sidragon.bmp */
#define SID_HDRYR_INDEX                29    /* sidhdryr.bmp */
#define SID_GUM_INDEX                  30    /* sidgum.bmp */
#define SID_WAIT1_INDEX                31    /* sidwait.bmp */
#define SID_WAIT2_INDEX                32    /* sidwait.bmp */
#define SID_WAIT3_INDEX                33    /* sidwait.bmp */
#define SID_WAIT4_INDEX                34    /* sidwait.bmp */
#define SID_STOP_INDEX                 35    /* sidstop.bmp */
#define SID_PIN1_INDEX                 36    /* sidpin.bmp */
#define SID_PIN2_INDEX                 37    /* sidpin.bmp */
#define SID_SLIDE1_INDEX               38    /* sidslide.bmp */
#define SID_SLIDE2_INDEX               39    /* sidslide.bmp */
#define SID_SLIDE3_INDEX               40    /* sidslide.bmp */
#define SID_SLIDE4_INDEX               41    /* sidslide.bmp */
#define SID_VAC_INDEX                  42    /* sidvac.bmp */
#define SID_VAC2_INDEX                 43    /* sidvac.bmp */
#define SID_VAC3_INDEX                 44    /* sidvac.bmp */
#define SID_TUNNEL_INDEX               45    /* sidtunel.bmp */
#define SID_PENCIL1_INDEX              46    /* sidpencl.bmp */
#define SID_PENCIL2_INDEX              47    /* sidpencl.bmp */
#define SID_PENCIL3_INDEX              48    /* sidpencl.bmp */
#define SID_PENCIL4_INDEX              49    /* sidpencl.bmp */
#define SID_PEEL_INDEX                 50    /* sidpeel.bmp */
#define SID_HEADLESS_INDEX             51    /* sidhless.bmp */
#define SID_BANANA_INDEX               52    /* sidbanan.bmp */
#define SID_BUBBLE_INDEX               53    /* sidgum.bmp */
#define SID_BUBBLE2_INDEX              54    /* sidgum.bmp */
#define SID_EGG_INDEX                  55    /* sidegg.bmp */

/* mouse number of frames in sequences */
#define SID_ROOT_NUM_STATES            1
#define SID_TAKE_NUM_STATES            1
#define SID_RUN_NUM_STATES             3
#define SID_GIGGLE_NUM_STATES          3
#define SID_BRONX_NUM_STATES           2
#define SID_FALL_NUM_STATES            6
#define SID_SPLAT_NUM_STATES           10
#define SID_WAIT_NUM_STATES            2
#define SID_HAIR_NUM_STATES            17
#define SID_CUT_NUM_STATES             4
#define SID_WHOP_NUM_STATES            3
#define SID_CLIMB_NUM_STATES           3
#define SID_WALK_NUM_STATES            8
#define SID_GUN_NUM_STATES             12
#define SID_DUSTB_NUM_STATES           7
#define SID_BUTT_NUM_STATES            8
#define SID_BONK_NUM_STATES            8
#define SID_ANVIL_NUM_STATES           9
#define SID_CHEESE_NUM_STATES          9
#define SID_LUNCH_NUM_STATES           11
#define SID_PIANO_NUM_STATES           7
#define SID_HIT_FLOOR_NUM_STATES       2  
#define SID_HIT_CEILING_NUM_STATES     2  
#define SID_HIT_LEFT_WALL_NUM_STATES   1 
#define SID_HIT_RIGHT_WALL_NUM_STATES  1
#define SID_FLY_UP_NUM_STATES          1
#define SID_BOMB_NUM_STATES            35
#define SID_SHAKE_NUM_STATES           7
#define SID_DRAGON_NUM_STATES          11
#define SID_HDRYR_NUM_STATES           5
#define SID_GUM_NUM_STATES             18
#define SID_WAIT1_NUM_STATES           2
#define SID_WAIT2_NUM_STATES           2
#define SID_WAIT3_NUM_STATES           2
#define SID_WAIT4_NUM_STATES           5
#define SID_STOP_NUM_STATES            6
#define SID_PIN1_NUM_STATES            5
#define SID_PIN2_NUM_STATES            9
#define SID_SLIDE1_NUM_STATES          6
#define SID_SLIDE2_NUM_STATES          6
#define SID_SLIDE3_NUM_STATES          3
#define SID_SLIDE4_NUM_STATES          2
#define SID_VAC_NUM_STATES             2
#define SID_VAC2_NUM_STATES            36
#define SID_VAC3_NUM_STATES            1
#define SID_TUNNEL_NUM_STATES          25
#define SID_PENCIL1_NUM_STATES         13
#define SID_PENCIL2_NUM_STATES         2
#define SID_PENCIL3_NUM_STATES         35
#define SID_PENCIL4_NUM_STATES         16
#define SID_PEEL_NUM_STATES            7
#define SID_HEADLESS_NUM_STATES        6
#define SID_BANAN_NUM_STATES           16
#define SID_BUBBLE_NUM_STATES          2
#define SID_BUBBLE2_NUM_STATES         16
#define SID_EGG_NUM_STATES             43

/* mouse number of sequence starting shape */
#include "sidequ.h"


