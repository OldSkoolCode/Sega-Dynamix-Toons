/* * * * *
*
*  TN_GLOB.H
*
*  This file contains all the global variables needed for the new toons 
*  modules.
*
*  By Chris Cole -- (c) 1993 Dynamix Software Development, Inc.
*
*  Modification History:
*  ---------------------
*  03/08/93 ChrisC   File created
*
* * * * */
extern char *error_text;

/* * * * *
*
*  command line options
*
* * * * */
extern CHAR toons_edit;
extern CHAR debug_mode;
extern CHAR reserve_memory;
extern CHAR puzzle_master;
extern char *database_filename;

/* * * * *
*
*  tim_dbox.c
*
* * * * */
extern P_TEXT far text_ptrs[];
extern short num_text_ptrs;
extern short max_width, max_height;

/* * * * *
*
*  interface globals
*
* * * * */
extern enum tpm { EDIT_PUZZLE, PLAY_PUZZLE, TEST_PUZZLE, LOCK_PUZZLE } toon_puzzle_mode;
extern short warning_message;
extern char toon_clear_chklist;
extern char toon_changes_made;
extern char ignore_erasing;
extern char solution_has_ropes;
extern char control_button, go_button, puzzle_edit_button;
 extern void *corners, *edit_corners, *play_corners, *button_shapes,
	*toon_cp_shapes, *toon_rcp_shapes, *quit_shapes, *clapper_shapes,
   *camera_shapes, *burst_shapes, *horn_shapes, *nuke_shapes, 
   *pig_shapes, *updown_arrows, *toonbox_shapes, *handle_shapes;

extern const MAKE_PART far mp_data[TN_NUM_PARTS];

/* * * * *
*
*  hotspots.c
*
* * * * */
extern HOT_SPOT *toon_title_hot_spots;
extern HOT_SPOT *edit_panel_hot_spots;
extern HOT_SPOT *edit_panel_hot_spots2;
extern HOT_SPOT *toon_quit_hot_spots;
extern HOT_SPOT *toon_clapper_hot_spots;
extern HOT_SPOT *toon_rip_hot_spots;
extern HOT_SPOT *toon_copyprot_hot_spots;
extern HOT_SPOT *toon_horn_hot_spots;
extern HOT_SPOT *run_toon_hot_spots;
extern HOT_SPOT *toon_nuke_hot_spots;
extern HOT_SPOT *toon_pig_hot_spots;
extern HOT_SPOT *toonbox_hot_spots;
extern HOT_SPOT *toon_chklist_hot_spots;
extern HOT_SPOT *toon_hearty_part_hot_spots;


/* * * * *
*
*  color maps
*
* * * * */
extern const char panel_color;
extern const char partbin_color;
extern const char bckgrnd_color;
extern const char highlight1;
extern const char highlight2;
extern const char highlight3;
extern const char highlight4;
extern const char highlight5;
extern const char pb_background;
extern const char pb_shadow;
extern const char pb_foreground;


/* * * * *
*
*  interface offsets
*
* * * * */
extern short x_offset, y_offset;
extern short ap_unlock_x, ap_unlock_y;

/* * * * *
*
*  file i/o globals
*
* * * * */
extern unsigned char current_puzzle_number;
extern char current_title[];
extern char current_description[];
extern const char default_description[];
extern const char default_title[];
extern char home_toon_puzzle;

/* * * * *
*
*  mouse globals
*
* * * * */
enum handle_type 
{ 
   HT_NONE,    HT_SIZE_UP, HT_SIZE_DOWN, HT_SIZE_LEFT, HT_SIZE_RIGHT,
   HT_FLIP_LR, HT_FLIP_TB, HT_FLUSH,     HT_HEARTY
};
extern char icon_changed;
extern enum handle_type current_handle;
extern PART *over_part;  

/* * * * *
*
*  sound globals
*
* * * * */
extern char master_volume, current_music_index;
extern short current_music;
extern const short music_table[];


/* * * * *
*
*  ep.c--electric plug (part 2)
*
* * * * */
extern PC_SSHAPE_C far p2_ss_tab[];
extern TIM_VEC_C far p2_size[ ]; 
extern TIM_SCVEC_C far p2_os[ ]; 


/* * * * *
*
*  teapot.c
*
* * * * */
extern PC_SSHAPE_C far teapot_ss_tab[];
extern  TIM_VEC_C far teapot_size[];  
extern TIM_SCVEC_C far teapot_os[];  


/* * * * *
*
*  bullet.c
*
* * * * */
extern PC_SSHAPE_C far bullet_ss_tab[];
extern TIM_VEC_C far bullet_size[];  
extern TIM_SCVEC_C far bullet_os[];  


/* * * * *
*
*  vc.c
*
* * * * */
extern PC_SSHAPE_C far vacuum_ss_tab[];
extern  TIM_VEC_C far vacuum_size[];
extern TIM_SCVEC_C far vacuum_os[];


/* * * * *
*
*  scissors.c
*
* * * * */
extern PC_SSHAPE_C far p16_ss_tab[];
extern  TIM_VEC_C far p16_size[];
extern TIM_SCVEC_C far p16_os[];


/* * * * *
*
*  dynamite.c
*
* * * * */
extern PC_SSHAPE_C far bomb_ss_tab[];
extern TIM_VEC_C far bomb_size[];
extern TIM_SCVEC_C far bomb_os[];
extern PC_SSHAPE_C far p19_ss_tab[];
extern TIM_VEC_C far p19_size[];
extern TIM_SCVEC_C far p19_os[];



/* * * * *
*
*  ww2 bomb
*
* * * * */
extern PC_SSHAPE_C far ww2bomb_ss_tab[];
extern  TIM_VEC_C far ww2bomb_size[]; 
extern TIM_SCVEC_C far ww2bomb_os[]; 

/* * * * *
*
*  gun.c
*
* * * * */
extern PC_SSHAPE_C far gun_ss_tab[];
extern  TIM_VEC_C far gun_size[];
extern TIM_SCVEC_C far gun_os[];


/* * * * *
*
*  balloon.c
*
* * * * */
extern TIM_SCVEC_C far p23_os[];


/* * * * *
*
*  tramp.c
*
* * * * */
extern PC_SSHAPE_C far p24_ss_tab[];
extern  TIM_VEC_C far p24_size[];
extern TIM_SCVEC_C far p24_os[];


/* * * * *
*
*  tn_ant.c
*
* * * * */
extern PC_SSHAPE_C far ant_ernator_ss_tab[];
extern  TIM_VEC_C far ant_ernator_size[]; 
extern TIM_SCVEC_C far ant_ernator_os[];


/* * * * *
*
*  tn_eatmotor.c
*
* * * * */
extern PC_SSHAPE_C far eatmotor_ss_tab[];
extern  TIM_VEC_C far eatmotor_size[]; 
extern TIM_SCVEC_C far eatmotor_os[];


/* * * * *
*
*  m_glass.c
*
* * * * */
extern PC_SSHAPE_C far mag_ss_tab[];
extern TIM_SCVEC_C far mag_os[]; 
extern  TIM_VEC_C far mag_size[]; 


/* * * * *
*
*  candle.c
*
* * * * */
extern PC_SSHAPE_C far p45_ss_tab[];
extern  TIM_VEC_C far p45_size[];
extern TIM_SCVEC_C far p45_os[];


/* * * * *
*
*  explosio.c
*
* * * * */
extern PC_SSHAPE_C far explosion_ss_tab[]; 
extern  TIM_VEC_C far explosion_size[]; 
extern TIM_SCVEC_C far explosion_os[]; 

/* * * * *
*
*  balls
*
* * * * */
extern PC_SSHAPE_C far baseball_ss_tab[];
extern  TIM_VEC_C far baseball_size[];
extern TIM_SCVEC_C far baseball_os[];
extern PC_SSHAPE_C far soccer_ss_tab[];
extern  TIM_VEC_C far soccer_size[];
extern TIM_SCVEC_C far soccer_os[];

/* * * * *
*
*  tn_tt.c
*
* * * * */
extern  TIM_VEC_C far tt_size[];
extern TIM_SCVEC_C far tt_os[];
extern PC_SSHAPE_C far tt_ss_tab[];

/* * * * *
*
*  tn_hair.c
*
* * * * */
extern TIM_SCVEC_C far p4_os[];
extern  TIM_VEC_C far p4_size[];

/* * * * *
*
*  catapult.c
*
* * * * */
extern PC_SSHAPE_C far catapult_ss_tab[];
extern  TIM_VEC_C far catapult_size[];
extern TIM_SCVEC_C far catapult_os[];
extern PC_PART_BORDER_C far catapult_bord_tab[];
extern P_PART_BORDER far catapult_fbord_tab[];
extern CHARACTER_SEQ *catapult_sequence[];
extern RECT catapult_bound_rect[];
extern RECT catapult_fbound_rect[];

/* * * * *
*
*  dragon
*
* * * * */
extern CHARACTER_SEQ *dragon_sequence[];
extern PC_SSHAPE_C far dragon_ss_tab[];
/*extern RECT dragon_bound_rect[];*/
/*extern RECT dragon_fbound_rect[];*/
extern  TIM_VEC_C far dragon_size[];
extern TIM_SCVEC_C far dragon_os[];
extern PC_PART_BORDER_C far dragon_bord_tab[];
extern P_PART_BORDER far dragon_fbord_tab[];

/* * * * *
*
*  tn_egg.c
*
* * * * */
extern PC_SSHAPE_C far egg_timer_ss_tab[];
extern RECT egg_timer_bound_rect[];
extern RECT egg_timer_fbound_rect[];
extern  TIM_VEC_C far egg_timer_size[]; 
extern TIM_SCVEC_C far egg_timer_os[];
extern CHARACTER_SEQ *egg_timer_sequence[];


/* * * * *
*
*  incline.c
*
* * * * */
extern PC_SSHAPE_C far incline_ss_tab[];
extern  TIM_VEC_C far incline_size[];
extern TIM_SCVEC_C far incline_os[];


/* * * * *
*
*  tn_shswt.c
*
* * * * */
extern PC_SSHAPE_C far chuteswitch_ss_tab[];
extern  TIM_VEC_C far chuteswitch_size[];
extern TIM_SCVEC_C far chuteswitch_os[]; 


/* * * * *
*
*  tn_updwn.c
*
* * * * */
extern PC_SSHAPE_C far updown_ss_tab[];
extern  TIM_VEC_C far updown_size[]; 
extern TIM_SCVEC_C far updown_os[]; 


/* * * * *
*
*  tn_mesg.c
*
* * * * */
extern PC_SSHAPE_C far message_ss_tab[];
extern  TIM_VEC_C far message_size[];
extern TIM_SCVEC_C far message_os[];
extern short messager_font;


/* * * * *
*
*  tn_rtrns.c
*
* * * * */
extern PC_SSHAPE_C far rottrans_ss_tab[];
extern  TIM_VEC_C far rottrans_size[];
extern TIM_SCVEC_C far rottrans_os[];


/* * * * *
*
*  tn_trot.c
*
* * * * */
extern PC_SSHAPE_C far transrot_ss_tab[];
extern  TIM_VEC_C far transrot_size[];
extern TIM_SCVEC_C far transrot_os[];
extern PC_PART_BORDER_C far transrot_bord_tab[];
extern P_PART_BORDER far transrot_fbord_tab[];


/* * * * *
*
*  tn_incre.c
*
* * * * */
extern PC_SSHAPE_C far incdec_ss_tab[];
extern  TIM_VEC_C far incdec_size[];


/* * * * *
*
*  tn_piano.c
*
* * * * */
extern PC_SSHAPE_C far piano_ss_tab[];
extern  TIM_VEC_C far piano_size[];
extern TIM_SCVEC_C far piano_os[];


/* * * * *
*
*  cat_def.c
*
* * * * */
extern PART_BORDER far cat_root_border[];
extern CHARACTER_SEQ * far const cat_sequences[];
extern CHAR const cat_shape_files[CAT_NUM_SEQUENCES][9];
extern void *cat_shape_tables[];
extern PC_SSHAPE_C far cat_ss_table[];
extern RECT far cat_bound_rect[];
extern RECT far cat_fbound_rect[];
extern TIM_VEC_C far cat_size[];
extern TIM_SCVEC_C far cat_os[];
extern PC_PART_BORDER_C far cat_border_table[];
extern P_PART_BORDER far cat_fborder_table[];
extern CHAR cat_bord_num;

/* * * * *
*
*  sid_def.c
*
* * * * */
extern PART_BORDER_C far mouse_root_border[];
extern CHARACTER_SEQ * const far mouse_sequences[];
extern CHAR const mouse_shape_files[SID_NUM_SEQUENCES][9];
extern void *mouse_shape_tables[];
extern PC_SSHAPE_C far mouse_ss_table[];
extern RECT far sid_bound_rect[];
extern RECT far sid_fbound_rect[];
extern  TIM_VEC_C far mouse_size[];
extern TIM_SCVEC_C far mouse_os[];
extern PC_PART_BORDER_C far mouse_border_table[];
extern P_PART_BORDER far mouse_fborder_table[];

/* * * * *
*
*  TN_DRYER.C
*
* * * * */
extern PC_SSHAPE_C far hairdryer_ss_tab[];
extern  TIM_VEC_C far hairdryer_size[]; 
extern TIM_SCVEC_C far hairdryer_os[]; 


/* * * * *
*
*  TN_WHSTL.C
*
* * * * */
extern PC_SSHAPE_C far noonwhistle_ss_tab[];
extern  TIM_VEC_C far noonwhistle_size[]; 
extern TIM_SCVEC_C far noonwhistle_os[]; 

/* * * * *
*
*  TN_ELEPH.C
*
* * * * */
extern PC_SSHAPE_C far elephant_ss_tab[];
extern  TIM_VEC_C far elephant_size[]; 
extern TIM_SCVEC_C far elephant_os[]; 

/* * * * *
*
*  TN_EGG1.C
*
* * * * */
extern PC_SSHAPE_C far egg_ss_tab[];
extern  TIM_VEC_C far egg_size[]; 
extern TIM_SCVEC_C far egg_os[]; 

/* * * * *
*
*  TN_CHKEN.C
*
* * * * */
extern PC_SSHAPE_C far chicken_ss_tab[];
extern  TIM_VEC_C far chicken_size[]; 
extern TIM_SCVEC_C far chicken_os[]; 

/* * * * *
*
*  TN_BANA.C
*
* * * * */
extern PC_SSHAPE_C far banana_ss_tab[];
extern  TIM_VEC_C far banana_size[]; 
extern TIM_SCVEC_C far banana_os[]; 

/* * * * *
*
*  TN_TRAP.C
*
* * * * */
extern PC_SSHAPE_C far trapdoor_ss_tab[];
extern  TIM_VEC_C far trapdoor_size[]; 
extern TIM_SCVEC_C far trapdoor_os[]; 




