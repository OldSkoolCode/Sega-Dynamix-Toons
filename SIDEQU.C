

#include	"tn_defs.h"

int tempint[] = {
SID_ROOT_SEQ          ,
SID_TAKE_SEQ          ,
SID_RUN_SEQ           ,
SID_GIGGLE_SEQ        ,
SID_BRONX_SEQ         ,
SID_FALL_SEQ          ,
SID_SPLAT_SEQ         ,
SID_WAIT_SEQ          ,
SID_HAIR_SEQ          ,
SID_CUT_SEQ           ,
SID_WHOP_SEQ          ,
SID_CLIMB_SEQ         ,
SID_WALK_SEQ          ,
SID_GUN_SEQ           ,
SID_DUSTB_SEQ         ,
SID_BUTT_SEQ          ,
SID_BONK_SEQ          ,
SID_ANVIL_SEQ         ,
SID_CHEESE_SEQ        ,
SID_LUNCH_SEQ         ,
SID_PIANO_SEQ         ,
SID_HIT_FLOOR_SEQ     ,
SID_HIT_CEILING_SEQ   ,
SID_HIT_LEFT_WALL_SEQ ,
SID_HIT_RIGHT_WALL_SEQ,
SID_FLY_UP_SEQ        ,
SID_BOMB_SEQ          ,
SID_SHAKE_SEQ         ,
SID_DRAGON_SEQ        ,
SID_HDRYR_SEQ         ,
SID_GUM_SEQ           ,
SID_WAIT1_SEQ         ,
SID_WAIT2_SEQ         ,
SID_WAIT3_SEQ         ,
SID_WAIT4_SEQ         ,
SID_STOP_SEQ          ,
SID_PIN1_SEQ          ,
SID_PIN2_SEQ          ,
SID_SLIDE1_SEQ        ,
SID_SLIDE2_SEQ        ,
SID_SLIDE3_SEQ        ,
SID_SLIDE4_SEQ        ,
SID_VAC_SEQ           ,
SID_VAC2_SEQ          ,
SID_VAC3_SEQ          ,
SID_TUNNEL_SEQ        ,
SID_PENCIL1_SEQ       ,
SID_PENCIL2_SEQ       ,
SID_PENCIL3_SEQ       ,
SID_PENCIL4_SEQ       ,
SID_PEEL_SEQ          ,
SID_HEADLESS_SEQ      ,
SID_BANANA_SEQ        ,
SID_BUBBLE_SEQ        ,
SID_BUBBLE2_SEQ       ,
SID_EGG_SEQ           ,
SID_NUM_STATES        };


char *tempname[] = {
"SID_ROOT_SEQ          ",
"SID_TAKE_SEQ          ",
"SID_RUN_SEQ           ",
"SID_GIGGLE_SEQ        ",
"SID_BRONX_SEQ         ",
"SID_FALL_SEQ          ",
"SID_SPLAT_SEQ         ",
"SID_WAIT_SEQ          ",
"SID_HAIR_SEQ          ",
"SID_CUT_SEQ           ",
"SID_WHOP_SEQ          ",
"SID_CLIMB_SEQ         ",
"SID_WALK_SEQ          ",
"SID_GUN_SEQ           ",
"SID_DUSTB_SEQ         ",
"SID_BUTT_SEQ          ",
"SID_BONK_SEQ          ",
"SID_ANVIL_SEQ         ",
"SID_CHEESE_SEQ        ",
"SID_LUNCH_SEQ         ",
"SID_PIANO_SEQ         ",
"SID_HIT_FLOOR_SEQ     ",
"SID_HIT_CEILING_SEQ   ",
"SID_HIT_LEFT_WALL_SEQ ",
"SID_HIT_RIGHT_WALL_SEQ",
"SID_FLY_UP_SEQ        ",
"SID_BOMB_SEQ          ",
"SID_SHAKE_SEQ         ",
"SID_DRAGON_SEQ        ",
"SID_HDRYR_SEQ         ",
"SID_GUM_SEQ           ",
"SID_WAIT1_SEQ         ",
"SID_WAIT2_SEQ         ",
"SID_WAIT3_SEQ         ",
"SID_WAIT4_SEQ         ",
"SID_STOP_SEQ          ",
"SID_PIN1_SEQ          ",
"SID_PIN2_SEQ          ",
"SID_SLIDE1_SEQ        ",
"SID_SLIDE2_SEQ        ",
"SID_SLIDE3_SEQ        ",
"SID_SLIDE4_SEQ        ",
"SID_VAC_SEQ           ",
"SID_VAC2_SEQ          ",
"SID_VAC3_SEQ          ",
"SID_TUNNEL_SEQ        ",
"SID_PENCIL1_SEQ       ",
"SID_PENCIL2_SEQ       ",
"SID_PENCIL3_SEQ       ",
"SID_PENCIL4_SEQ       ",
"SID_PEEL_SEQ          ",
"SID_HEADLESS_SEQ      ",
"SID_BANANA_SEQ        ",
"SID_BUBBLE_SEQ        ",
"SID_BUBBLE2_SEQ       ",
"SID_EGG_SEQ           ",
"SID_NUM_STATES        " };

int main(void)
{

	int	i;
	int 	j;

	j = sizeof(tempint)/sizeof(int);

	for (i=0;i<j;i++)
		printf("#define\t%s\t%d\n",tempname[i], tempint[i]);

	return(0);
}



