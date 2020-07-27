
#ifndef TIM_FUNC_H
#define TIM_FUNC_H

#include "tim.h"


/*other*/
extern short angle_to(long,long);

/*collide.c*/
extern short collide( PART *);

/*cp.c*/
extern void do_control_panel( void);
extern void special_load_save_draw( void);
extern void over_cp_ff_button( HOT_SPOT *);
extern void over_cp_load_button( HOT_SPOT *);
extern void over_cp_save_button( HOT_SPOT *);
extern void over_cp_grav_button( HOT_SPOT *);
extern void over_cp_dens_button( HOT_SPOT *);
extern void over_cp_desc_button( HOT_SPOT *);
extern void over_cp_partbin_button( HOT_SPOT *);

/*drawing.c*/
extern void draw_wood_window( short, short, short, short, short);
extern void draw_brass_text( char *, short, short, short);
extern void draw_brass_button( char *, short, short, short);
extern void draw_brass_plate( short, short, short, short);
extern void draw_plain_brass_plate( short, short, short, short);
extern void draw_brass_outline( short, short, short, short, short);
extern void give_message( char *, char *);
extern short ask_yes_no( char *, char *);
extern short prompt_user( char *, char *, char *, char *);
extern void draw_victory_message( void);
extern void draw_gp_screen( void);
extern void draw_digit( char, short, short);
extern void draw_all_borders( void);
extern void draw_tb_border( void);
extern void draw_bb_border( void);
extern void draw_lb_border( void);
extern void draw_rb_border( void);
extern void draw_rb_icons( void);
extern void draw_rbi_shape( void *, short, short, short, short);
extern void draw_go_shape( void);
extern void draw_active_icon( void);
extern void hilite_part( PART *, SHORT, SHORT, SHORT);
void draw_part(PART *,SHORT,SHORT,UCHAR);
extern void draw_parts( short);
extern void init_draw_list( void);
extern void add_to_draw_list( PART *);
extern void do_draw_list( short, short);
extern void draw_curved_line( short, short, short, short, short);
extern void draw_debug( void);

/*editor.c*/
extern void edit_machine( void);
extern void over_go( HOT_SPOT *);
#if TIM_DEMO
extern void click_over_go(HOT_SPOT *);
#endif
extern void over_partbin( HOT_SPOT *);
extern void click_over_partbin( short slotnum);
extern void over_edit_screen( HOT_SPOT *);
extern void scroll_pb_left( short);
extern void scroll_pb_right( short);

/*hot_spot.c*/
extern void process_hs( HOT_SPOT *);
extern void init_hs( void);
extern void reset_hs( void);

/*interact.c*/
extern void interactions( void);

/*level.c*/
extern void play_level( void);
extern void init_level( void);
extern void reset_level( void);
extern void load_part_shapes( void);
extern void load_part_shape( short);
extern void free_part_shapes( void);
extern void free_part_shape( short);
extern short select_puzzle( void);

/*mspeed.asm*/
extern void mouse_speed( short);

/*partbin.c*/
extern void adjust_partbin( void);

/*physics.c*/
extern void init_prop_physics( void);
extern void check_term_velocity( PART *);
extern void adjust_falling( PART *);
extern void adjust_rolling( PART *);
extern void move_part( PART *);
extern void roll_part( PART *);
extern void bounce( PART *);
extern void impact( PART *);

/*run.c*/
extern void run_machine( void);
extern void init_run_machine( void);
extern void reset_run_machine( void);
extern void advance_go_count( void);

/*score.c*/
extern void init_scoreboard( void);
extern void process_score( void);
extern void draw_all_digits( void);
extern void award_bonus( void);
extern void score_to_code( long, char *);
extern long code_to_score( char *);

/*set_lc.asm*/
extern void set_lc( short);

/*set_vb.asm*/
extern void set_vb( short);

/*query.c*/
extern void query_dist( PART *, short, short, short, short, short);
extern void query_rect( PART *, short, short, short, short, short);
extern void query_line( PART *, short, LINE_SEG *);
extern void query_rect_fuse( PART *, short, short, short, short);
extern void query_inside_bucket( PART *);
extern short query_in_bucket_list( PART *, PART *);
extern void query_move_bucket_list( PART *);

/*support.c*/
extern void rotate2d( short *, short *, short);
extern short segment_intersect( LINE_SEG *, LINE_SEG *, TIM_VEC *);
extern void adjust_segment_slope( LINE_SEG *);
extern short within_range( short, short, short);
extern short angle_to_centers( PART *, PART *);
extern short should_skip_pair( short, short);
extern short part_overlap( PART *);
extern short gross_overlap(PART *part1);
extern short border_overlap( PART *, PART *);
extern void reverse_rope_links( ROPE *);
extern PART *mouse_over_part( PART *);
extern PART *mouse_over_rope_tie( short *, PART *);
extern void choose_wait_icon( void);
extern void choose_pause_icon( void);
extern void restore_icon( void);
extern void change_mouse_icon( short);
extern short get_sub_mode_icons( void);
extern short get_ap_flags( PART *);
extern short get_tim_sub_mode( PART *);
extern short valid_pulley_dist( TIM_VEC *, TIM_VEC *);
extern short valid_pulley( PBELT *);
extern short get_angle_to_part( PART *, PART *);
extern void orient_pulleys( PART *);
extern void orient_pulley( PART *);
extern void generate_pbelt_lines( PBELT *);
extern void generate_rope_lines( ROPE *rptr);
extern void connect_plug( void);
extern void disconnect_plug( PART *);
extern void remove_pbelt( PART *);
extern void remove_rope( PART *, short);
extern void freeform_remove_part( PART *);
extern void finish_removal( void);
extern void remove_from_list( PART *);
extern void insert_into_list( PART *, PART *);
extern void move_to_avail(PART *);
extern void move_from_avail(PART *);
extern void remove_all_parts( void);
extern short inside_border(PART *pptr1, PART *pptr2);
extern short do_handles(PART *pptr, TIM_VEC *my_loc, TIM_VEC *my_size);
#if TIM_EDITOR
extern void get_puzzle_num( void);
extern void add_a_part( void);
extern void remove_a_part( void);
#endif
extern PART *get_pb_part( short);
extern PART *get_last_pb_part( void);
extern void set_redraw( PART *, short);
extern PART *copy_part( PART *);
extern PART *get_first_part( short);
extern PART *get_next_part(PART *, short);
extern void set_adjusted_loc_size( PART *);
extern void set_part_size( PART *);
extern void set_border_slope( PART *);
extern void clear_er( void);
extern void sub_parts_to_er( PART *, short);
extern void belt_to_er( PART *, short);
extern void rope_to_er( PART *, short);
extern void norm_to_er( PART *, short);
extern void part_to_er( PART *, short);
extern void add_to_er( TIM_VEC *, TIM_VEC *, char, char, short);
extern void process_er( void);
extern void set_redraw_from_er( void);
extern void set_redraw_from_draw( void);
extern void erase_and_draw( PART *);
extern PART *get_belt_link( PART *);
extern short get_rope_action( ROPE *, short, short);
extern short get_rope_return_tie_num( PART *, PART *);
extern PART *get_rope_link( PART *, ROPE *);
extern short get_rope_len( ROPE *, short, short);
extern short get_len_diff( PART *, ROPE *, short);
extern short get_blink_rot( PART *);
extern void set_part_speed( PART *, short, short);
extern void set_speed_from_loc( PART *, short, short, short);
extern short let_rope_adj_loc( PART *);
extern void clear_ft( void);
extern short add_to_ft( PART *, PART *);
extern void set_bucket_mass( PART *);
extern void add_to_mass( PART *, PART *);
extern void save_old_part_info( void);
extern void reinit_parts( void);
extern short mouse_over_playfield( void);
extern void turn_mouse_off( void);
extern void turn_mouse_on( void);
extern void my_mouse_off( void);
extern void my_mouse_on( void);
extern void my_mouse_move( void);
extern void my_flip( short);
extern void flip_and_copy( void);
extern void copy_and_flip( void);
extern void set_special_dates( void);
extern void set_playfield_clip( void);
extern void set_game_scrn_clip( void);
extern void set_full_scrn_clip( void);
extern void start_music( short);
extern void start_sound( short);
extern void stop_sound( short);
extern unsigned short coremax( void);
extern void my_my_free( void *);
extern short my_heapcheck( void);
extern unsigned short remap_key( unsigned short);

/*freeform.c*/
extern void make_free_form( void);
extern PART *make_a_part( short);
extern void clear_the_pb( void);
extern void free_the_parts( void);
extern void free_a_part( PART *);

/*tim_dbox.c*/
extern void build_text_ptrs( P_TEXT, short, short, short);;
extern void default_text( P_TEXT, short, short, short, short, char, char, char, char);
extern void default_set_xywh( P_TEXT, P_TEXT, short, short, short, short, short *, short *);
extern P_TEXT default_set_ptr( P_TEXT, short, short, short, short, short, short);

/*tim_dir.c*/
extern short get_file_name( char *, char *, char *);
extern void edit_string( char, char *, short);

/*title.c*/
extern void title( void);


/*PART routines*/

/*ball.c*/
extern void big_ball_reinit( PART *);
extern void medium_ball_reinit( PART *);
extern void small_ball_reinit( PART *);

/*balloon.c*/
extern void balloon_reinit( PART *);
extern short balloon_bounce( PART *);
extern void balloon_internal( PART *);
extern short balloon_rope( PART *, PART *, short, short, short, long);

/*bellows.c*/
extern short bellows_bounce( PART *);
extern void bellows_internal( PART *);
extern void bellows_reinit( PART *);
extern void bellows_flip( PART *, short);

/*boxglove.c*/
extern short bg_bounce( PART *);
extern void bg_reinit( PART *);
extern void bg_internal( PART *);
extern void bg_flip( PART *, short);

/*bucket.c*/
extern short bucket_bounce( PART *);
extern void bucket_reinit( PART *);
extern short bucket_rope( PART *, PART *, short, short, short, long);

/*bullet.c*/
extern short bullet_bounce( PART *);
extern void bullet_internal( PART *);
extern void bullet_reinit( PART *);

/*candle.c*/
extern void candle_internal( PART *);
extern void candle_reinit( PART *);

/*cannon.c*/
extern void cannon_internal( PART *);
extern void cannon_reinit( PART *);
extern void cannon_flip( PART *, short);

/*cat.c*/
extern void cat_reinit( PART *);
extern short cat_bounce( PART *);
extern void cat_internal( PART *);
extern void cat_flip( PART *, short);

/*cc.c*/
extern void cc_reinit( PART *);
extern short cc_rope( PART *, PART *, short, short, short, long);

/*christmas.c*/
extern void christmas_reinit( PART *);

/*credits.c*/
extern void incredible_reinit( PART *);
extern void credit_reinit( PART *);
extern void credit_internal( PART *);
extern short credit_rope( PART *, PART *, short, short, short, long);

/*dynamite.c*/
extern short dynamite_bounce( PART *);
extern void dynamite_reinit( PART *);
extern void dynamite_internal( PART *);
extern void dynamite_flip( PART *, short);

/*e_motor.c*/
extern void em_reinit( PART *);
extern void em_internal( PART *);
extern void em_flip( PART *, short);

/*ep.c*/
extern void ep_reinit( PART *);
extern short ep_bounce( PART *);
extern void ep_internal( PART *);
extern void ep_flip( PART *, short);

/*explosion.c*/
extern void explosion_internal( PART *);
extern void explode(PART *pptr,short x,short y);

/*eyehook.c*/
extern void eyehook_reinit( PART *);
extern void eyehook_flip( PART *, short);

/*fan.c*/
extern void fan_reinit( PART *);
extern void fan_internal( PART *);
extern void fan_flip( PART *, short);

/*fishbowl.c*/
extern void fishbowl_reinit( PART *);
extern short fishbowl_bounce( PART *);
extern void fishbowl_internal( PART *);
extern void fishbowl_break( PART *);

/*flshlite.c*/
extern short fl_bounce( PART *);
extern void fl_reinit( PART *);
extern void fl_internal( PART *);
extern void fl_flip( PART *, short);

/*gear.c*/
extern short gear_bounce( PART *);
extern void gear_reinit( PART *);
extern void gear_internal( PART *);

/*genrator.c*/
extern short generator_bounce( PART *);
extern void generator_reinit( PART *);
extern void generator_internal( PART *);

/*gun.c*/
extern void gun_reinit( PART *);
extern void gun_internal( PART *);
extern void gun_flip( PART *, short);
extern short gun_rope( PART *, PART *, short, short, short, long);

/*hc_belt.c*/
extern void hc_belt_reinit( PART *);
extern short hc_belt_bounce( PART *);
extern void hc_belt_internal( PART *);
extern void hc_belt_resize( PART *);

/*heart.c*/
extern void heart_reinit( PART *);
extern short heart_rope( PART *, PART *, short, short, short, long);

/*incline.c*/
extern void incline_reinit( PART *);
extern void incline_resize( PART *);
extern void incline_flip( PART *, short);

/*jack_box.c*/
extern void jb_internal( PART *);
extern void jb_reinit( PART *);
extern void jb_flip( PART *, short);

/*lb.c*/
extern short lb_bounce( PART *);
extern void lb_reinit( PART *);
extern void lb_internal( PART *);
extern void lb_flip( PART *, short);
extern short lb_rope( PART *, PART *, short, short, short, long);

/*m_bike.c*/
extern short mb_bounce( PART *);
extern void mb_reinit( PART *);
extern void mb_internal( PART *);
extern void mb_flip( PART *, short);
extern short mb_rope( PART *, PART *, short, short, short, long);

/*m_glass.c*/
extern void mg_reinit( PART *);
extern void mg_internal( PART *);
extern void mg_flip( PART *, short);

/*plunger.c*/
extern short plunger_bounce( PART *);
extern void plunger_reinit( PART *);
extern void plunger_internal( PART *);
extern void plunger_flip( PART *, short);
extern short plunger_rope( PART *, PART *, short, short, short, long);

/*pt_mouse.c*/
extern void pt_mouse_reinit( PART *);
extern short pt_mouse_bounce( PART *);
extern void pt_mouse_internal( PART *);
extern void pt_mouse_flip( PART*, short);

/*pumpkin.c*/
extern void pumpkin_reinit( PART *);

/*rocket.c*/
extern void rocket_reinit( PART *);
extern void rocket_internal( PART *);

/*sc_pipe.c*/
extern void scp_reinit( PART *);
extern void scp_flip( PART *, short);

/*scissors.c*/
extern short scissors_bounce( PART *);
extern void scissors_reinit( PART *);
extern void scissors_internal( PART *);
extern void scissors_flip( PART *, short);

/*sp.c*/
extern void sp_reinit( PART *);
extern void sp_internal( PART *);

/*tramp.c*/
extern short tramp_bounce( PART *);
extern void tramp_internal( PART *);
extern void tramp_reinit( PART *);

/*tt.c*/
extern short tt_bounce( PART *);
extern void tt_internal( PART *);
extern void tt_reinit( PART *);
extern void tt_flip( PART *, short);
extern short tt_rope( PART *, PART *, short, short, short, long);

/*wall.c*/
extern void wall_reinit( PART *);
extern void wall_resize( PART *);
extern short wall_bounce( PART *);

/*windmill.c*/
extern void wm_reinit( PART *);
extern void wm_internal( PART *);
extern void wm_flip( PART *, short);


/*PART routines (DATA DISK #1)*/

/*alligato.c*/
extern short alligator_bounce( PART *);
extern void alligator_reinit( PART *);
extern void alligator_internal( PART *);
extern void alligator_flip( PART *, short);

/*bumper.c*/
extern short bumper_bounce( PART *);
extern void bumper_reinit( PART *);
extern void bumper_internal( PART *);

/*cheese.c*/
extern void cheese_reinit( PART *);

/*guy.c*/
extern short guy_bounce( PART *);
extern void guy_reinit( PART *);
extern void guy_internal( PART *);
extern void guy_flip( PART *, short);

/*house.c*/
extern void house_internal( PART *);

/*nail.c*/
extern short nail_bounce( PART *);
extern void nail_reinit( PART *);

/*shamrock.c*/
extern void shamrock_reinit( PART *);

/*teapot.c*/
extern void teapot_reinit( PART *);
extern void teapot_internal( PART *);
extern void teapot_flip( PART *, short);

/*vc.c*/
extern short vc_bounce( PART *);
extern void vc_reinit( PART *);
extern void vc_internal( PART *);
extern void vc_flip( PART *, short);

#endif

