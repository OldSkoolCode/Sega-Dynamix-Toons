
#ifndef TIM_GLOB_H
#define TIM_GLOB_H



#include <stdlib.h>
#include <stdio.h>

#include "tim.h"


extern char file_path[];
extern char exe_path[];
extern char load_save_path[];
extern char file_name[];

extern unsigned int _stklen;
extern long free_k;

extern short time_to_quit;

extern FILE *sx_fp;
extern short snd_vol_tab[];
extern short snd_tag[];
extern short snd_mem_needed[];

extern F_SSHAPE single_super_shape;   /*this is in prop.c*/
extern PART_ELEMENTS far prop[];        /*this is in prop.c*/

extern void *mouse_shapes,*cp_shapes;
extern short show_mouse;
extern unsigned short my_key;

extern char far *tim_pal;
extern char far *title_pal;
extern char far *sierra_pal;
extern char far *black_pal;
extern short tim_font;

extern short pf_lclip,pf_rclip1,pf_rclip2,pf_tclip,pf_bclip;

extern short belt_snd_on,bike_snd_on,fan_snd_on,hum_snd_on,vacuum_snd_on,teapot_snd_on;

extern short background_color,pb_color,hilite_color,line_color;
extern TIM_VEC line_pt1,line_pt2;

#if TIM_EDITOR
extern short in_edit_mode;
#endif

extern PART static_list, move_list, avail_list, *active_part, *pb_part;
extern PART *draw_plane[];
extern short ap_flags;

extern LEVEL cur_level;
extern void *score_shapes,*bord_shapes,*menu_shapes;
extern void *icon_shapes;
extern short old_mouse_icon,last_icon;

extern short tim_sound_volume;
extern short b1_fraction,b2_fraction;
extern short run_count,victory_count,tim_timing;

extern short ledge,tedge;
extern short old_ledge,old_tedge,old_old_ledge,old_old_tedge;
extern short place_offset_x,place_offset_y;

extern short redraw_rbi,redraw_tb,redraw_bb,redraw_lb,redraw_rb,redraw_ai;
extern short go_count;

extern short force_fail,warned_low;

extern short is_valentine,is_st_pat,is_halloween,is_christmas,is_forth_july;

extern HOT_SPOT *hot_spots,*cp_hot_spots,*disk_hot_spots,*ask_hot_spots,*puz_hot_spots;
extern HOT_SPOT *ask_yes_hs,*ask_no_hs;
extern unsigned short tim_mode,tim_sub_mode,freeform_mode;
extern unsigned short old_tim_mode;
extern short unique_pb;

extern char ReturnBuffer[];
extern short num_pb_slots;

extern FORCE_TRANSFER *ft_list,*ft_avail;
extern UBYTE power_buttons;

#ifdef _MSDOS_
extern ERASE_RECT far *er_list;
extern ERASE_RECT far *er_avail;
extern ERASE_RECT far *er_processed;
#endif

#endif
