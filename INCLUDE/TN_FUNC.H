/* * * * *
*
*  TN_FUNC.H
*
*  This is the prototype include file for all T.I.M. Toons modules.
*
*  By Chris Cole -- (c) 1993 Dynamix Software Development, Inc.
*
*  Modification History:
*  ---------------------
*  03/08/93 ChrisC   File created
*
* * * * */


extern void vm_init2(void);
extern void vm_flip2(short wait);

/* * * * *
*
*  tim.c
*
* * * * */
extern void quit (short temp);
extern void check_dongle(void);

/* * * * *
*
*  victory.c
*
* * * * */
extern void check_victory(void);
extern PART *get_n_type(short type, short n, short list);

/* * * * *
*
*  finale.c
*
* * * * */
extern void show_grand_finale(void);
extern short load_title_script(char *filename);
extern void free_title_script(void);
extern void play_title_script(void);

/* * * * *
*
*  memory.c
*
* * * * */
extern void * tn_calloc (short amount, short size );
extern void * tn_malloc(unsigned short size);
extern void configure_memory(long minfar, long minems);
extern void verify_near_memory(void);
extern unsigned short avail_near_memory(void);
extern short check_free_memory( void);

/* * * * *
*
*  database.c
*
* * * * */
extern void load_database(void);
extern void save_database(void);
extern char * get_next_puzzle(short bin);   /* bin is 0 to 3 */
extern short puzzle_solved(void);
extern short get_puzzle_flags(short puzzle);
extern short bin_to_puzzle(short bin, short index);
extern short get_current_bin(void);
extern short get_jigsaw_pieces_left(void);
extern short get_jigsaw_puzzle_piece(short index);
extern void unlock_all_puzzles(void);
extern short check_database_checksum(short set);
extern short get_num_puzzles_left(void);


/* * * * *
*
*  jigsaw.c
*
* * * * */
void show_jigsaw_puzzle(void);

/* * * * *
*
*  copyprot.c
*
* * * * */
void do_toon_copy_protection(void);


/* * * * *
*
*  tn_fix.c
*
* * * * */
extern void fix_char_data(short type);
extern void edit_cat_data(void);
extern void edit_sid_data(void);


/* * * * *
*
*  tn_panel.c
*
* * * * */
extern void wait(short count);
#ifdef __MSDOS__
extern void grey_out(char color, short x, short y, short w, short h);
#else
extern void grey_out(UWORD *palptr);
#endif
extern void draw_toon_control_panel(short x, short y);
extern void do_speed_select(void);
extern void erase_control_panel(short x, short y);
extern void draw_toon_control_buttons(short x, short y);
extern void draw_toon_edit_panel(short x, short y);
extern void erase_edit_panel(short x, short y);
extern void erase_control(short x, short y);
extern void draw_toon_edit_buttons(short x, short y);
extern void draw_toon_go(char button, short x, short y);
extern void draw_toon_control(char button, short x, short y);
extern void draw_toon_edit_icons(short x, short y);
extern void draw_toon_left_button(char button, short x, short y);
extern void draw_toon_right_button(char button, short x, short y);
extern void draw_toon_fairy(char button, short x, short y);
extern void draw_toon_puzzle(char button, short x, short y);
extern void draw_toon_save_arrow(char button, short x, short y);
extern void draw_toon_load_arrow(char button, short x, short y);
extern void draw_toon_pig(char button, short x, short y);
extern void draw_toon_chklist(char button, short x, short y);

/* * * * *
*
*  tn_misc.c
*
* * * * */
extern short do_loadsave_interface(void);
extern short do_toon_overrite(void);
extern short do_puzzle_not_saved(void);
extern short do_generic_requester(short requester);
extern void draw_outline_text(P_TEXT string, short x, short y, short multi_color);
extern void draw_shadow_text(P_TEXT string, short x, short y, short multi_color);
extern void draw_indent_text(P_TEXT string, short x, short y, short multi_color);
extern void draw_text(P_TEXT text, short x, short y, short w, short h, short style);

/* * * * *
*
*  tn_ed_md.c
*
* * * * */
extern void do_toon_edit_panel(void);
extern void toggle_toon_edit_play(void);
extern void redraw_parts(void);

/* * * * *
*
*  chklist.c
*
* * * * */
extern void do_toon_chklist(void);


/* * * * *
*
*  tn_flush.c
*
* * * * */
extern void remap_panel_colors(void);
extern void bring_up_control_panel(void);
extern void close_down_control_panel(void);
extern void swap_play_edit_panels(void);
extern void redraw_panels(void);
extern void grey_panels(void);
extern void grey_panel(short x, short y, short w, short h);



/* * * * *
*
*  tn_edit.c
*
* * * * */
extern void init_toon_machine(void);
extern void set_toon_clip(short x, short y, short w, short h);
extern void redraw_full_screen(void);
extern void reset_game_screen(void);
extern void init_toon_level(void);
extern void draw_toon_bin_icons(short x, short y);
extern void draw_toon_icon_shape(void *icon,short x,short y, short w,short h, 
							short shp_num);
extern void setup_toon_edit(void);
extern void reset_toon_edit(void);
extern void edit_toon_machine(void);
                                               
/* * * * *
*
*  tn_sound.c
*
* * * * */
extern void do_toon_horn(void);
extern short get_button_sound(void);
extern void draw_horn(char button, short x, short y);
extern void draw_toon_horn(char button, short x, short y);

/* * * * *
*
*  tn_rndom.c
*
* * * * */
extern unsigned short my_random(void);
extern void my_seed_random(unsigned char seed);

/* * * * *
*
*  tn_quit.c
*
* * * * */
extern void do_toon_quit(void);
extern void draw_toon_stop(char button, short x, short y);
extern void draw_toon_quit(char button, short x, short y);

/* * * * *
*
*  tn_htypt.c
*
* * * * */
extern void do_hearty_part(void);


/* * * * *
*
*  smartend.c
*
* * * * */
extern short determine_smart_ends(PART *part);
extern void  draw_smart_ends(PART *part);
extern short check_smart_ends(PART *part, ERASE_RECT far *erptr);

/* * * * *
*
*  borders.c
*
* * * * */
extern void set_border_table_slopes(short id, short flip, 
         P_P_PART_BORDER btable, P_P_PART_BORDER fbtable, short num_states);
extern void set_border_slopes(short id, short flip, P_PART_BORDER borders,
         P_PART_BORDER fborders, short state);
extern void set_boundry_rect(short id, RECT far *boundry, 
         P_P_PART_BORDER btable, short num_states);


/* * * * *
*
*  logerror.c
*
* * * * */
extern void log_error(short error, char *string, ...);


/* * * * *
*
*  tn_clapr.c
*
* * * * */
extern void do_toon_clapper(void);
extern void draw_toon_clapper(char button, short x, short y);
extern void draw_clapper(char button, short x, short y);


/* * * * *
*
*  tn_text.c
*
* * * * */
extern void my_str(char *string, short x, short y);
extern void tn_my_str(P_TEXT string, short x, short y, short background, 
   short shadow, short foreground);
extern void edit_field(P_TEXT string, short x, short y, short w, short h,
   char foreground, char background, char shadow, char mode, 
   short max_strlen, short scroll);
extern void draw_field(P_TEXT string, short x, short y, short w, short h,
   char foreground, char background, char shadow, char mode);
   

/* * * * *
*
*  editor.c
*
* * * * */
extern void do_edit_modes( void);
extern void recycle_a_part( void);
extern void check_special_draw( void);
extern void set_pb_offset(short type);

/* * * * *
*
*  query.c
*
* * * * */
extern void tn_query_dist(PART *,short,short,short,short,short);


/* * * * *
*
*  tn_my_vm.c
*
* * * * */
extern void vm_my_line(short x1, short y1, short x2, short y2);
extern void vm_my_rect(short x, short y, short w, short h);
extern void vm_my_setpix(short x, short y, short color);
extern void vm_my_circle(short radius, short x, short y);



/* * * * *
*
*  tn_nuke.c
*
* * * * */
extern void do_toon_nuke(void);
extern void draw_toon_nuke(char button, short x, short y);
extern void draw_nuke(char button, short x, short y);



/* * * * *
*
*  tn_free.c
*
* * * * */
extern void make_partbin(void);
extern void make_free_form(void);
extern PART *reuse_a_part(short type);
extern PART *make_a_part(short type);
extern void clear_the_pb(void);
extern void free_the_parts(void);
extern void free_a_part(PART *cur_part);
extern void set_default_place_size(PART *pptr);



/* * * * *
*
*  egafade.c
*
* * * * */
extern void ega_mask_rect(short x, short y, short w, short h, short white);

/* * * * *
*
*  tn_tunel.c
*
* * * * */
extern void tunnel_reinit(PART *tunnel);

/* * * * *
*
*  tn_ladr.c
*
* * * * */
extern void ladder_reinit(PART *ladder);

/* * * * *
*
*  tn_cata.c
*
* * * * */
extern short catapult_bounce(PART *cur_part);
extern void catapult_internal(PART *c_part);
extern void catapult_reinit(PART *c_part);
extern void catapult_flip(PART *c_part,short flip_mode);

/* * * * *
*
*  hc_belt.c
*
* * * * */
void draw_conveyor_belt(PART *pptr,unsigned char plane,short loc_scale_adj,
   short size_scale_adj);


/* * * * *
*
*  ball.c
*
* * * * */
extern void ball_reinit(PART *ball);
extern void ball_bounce(PART *cur_part);
extern void ball_internal(PART *ball);

/* * * * *
*
*  tn_rip.c
*
* * * * */
extern void do_toon_rip(void);

	
/* * * * *
*
*  tn_pig.c
*
* * * * */
extern void do_toon_pig(short mode);
extern void draw_pig_button(short button, short frame, short x, short y);
extern void draw_pig(char button, short x, short y);

/* * * * *
*
*  tn_tnbox.c
*
* * * * */
extern void do_toonbox(void);
extern void draw_toonbox(char button, short x, short y);

/* * * * *
*
*  tn_file.c
*
* * * * */
extern short init_num_puzzles( char *);
extern void load_next_puzzle(void);
extern void load_puzzle( char *name, short);
extern short save_puzzle( char *name);
extern short in_tim_format( char *);
extern short get_puzzle_name( char *, short, char *);
extern short get_pw_number( char *);
extern void get_pw_string( short, char *);
extern short read_toon_cfg( void);
extern void write_toon_cfg( void);
extern short read_char( int, char *);
extern void read_short( int, void *);
extern void read_string( int, char *);
extern void read_line( int, char *);
extern void read_part( int, PART *);
extern void read_parts( int, PART *, short);
extern void write_char( int, char *);
extern void write_short( int, void *);
extern void write_string( int, char *);
extern void write_part( int, PART *);
extern void write_parts( int, PART *, short);
extern void write_num_parts( int, PART *);

/* * * * *
*
*  support.c
*
* * * * */
extern void reset_mouse_icon(void);
extern void my_set_border_slope(P_PART_BORDER border, char num_borders);
extern void reinit_sounds(void);
extern void reset_sounds(void);


/* * * * *
*
*  drawing.c
*
* * * * */
extern void draw_norm_part( PART *, UCHAR, SHORT, SHORT);
extern void draw_supershape(PART *pptr,P_SSHAPE ssptr,void **shape_table,
   UCHAR plane,SHORT loc_scale_adj,SHORT size_scale_adj);
extern void free_er_processed(void);
extern void draw_panels_using_erase(void);

/* * * * *
*
*  tn_char.c
*
* * * * */
extern void update_character(PART *pptr);
extern void update_character_position(PART *pptr, short direction);
extern void set_character_borders(SHORT type);
extern void set_flip_borders(short type, P_PART_BORDER *bord_tab,
   P_PART_BORDER *fbord_tab,short num_states,short direction);
extern void character_from_move_to_static(PART *character);
extern void character_from_static_to_move(PART *character);
extern PART *create_part(SHORT part_number, SHORT x_loc, SHORT y_loc,
   SHORT old_x_loc, SHORT old_y_loc, SHORT speed_x, SHORT speed_y,
   SHORT flags1, SHORT flags2);
extern void kill_character(PART *character);
extern void character_collision(PART *cat, PART *mouse);
extern short short_to_pix(short num);
extern short generic_static_to_static_collide(PART *ppt1, PART *pptr2);
extern short is_opaque(PART *character, PART *pptr, short threshold);
extern short opaque_but_important(PART *pptr);


/* * * * *
*
*  tn_prop.c
*
* * * * */
extern void init_bin_order(void);
extern void special_reinit(PART *pptr);


/* * * * *
*
*  tn_cat.c
*
* * * * */
extern void al_cat_reinit(PART *cat);
extern void cat_flip(PART *cat, SHORT flip_mode);
extern void al_cat_internal(PART *cat);
extern short al_cat_collide(PART *cur_part);
extern void load_cat_shapes(void);
extern void free_cat_shapes(void);
extern CHAR preempt_cat(PART *cat);

/* * * * *
*
*  tn_dragn.c
*
* * * * */
extern void dragon_reinit(PART *dragon);
extern void dragon_flip(PART *dragon, SHORT flip_mode);
extern short dragon_collide(PART *cur_part);
extern void dragon_internal(PART *dragon);

/* * * * *
*
*  tn_sid.c
*
* * * * */
extern void mouse_reinit(PART *mouse);
extern void sid_flip(PART *mouse, SHORT flip_mode);
extern short mouse_collide(PART *cur_part);
extern void mouse_internal(PART *mouse);
extern void load_mouse_shapes(void);
extern void free_mouse_shapes(void);


/* * * * *
*
*  gameplay.c
*
* * * * */
void init_game(void);

/* * * * *
*
*  tn_hair.c
*
* * * * */
extern void hair_reinit(PART *hair);
extern short hair_bounce(PART *cur_part);
extern void hair_internal(PART *hair);

/* * * * *
*
*  bitmaps.c
*
* * * * */
extern void load_part_bitmaps(short id);
extern void load_cat_bitmaps(short id);
extern void load_mouse_bitmaps(short id);
extern void free_cat_bitmaps(short id);
extern void free_mouse_bitmaps(short id);
extern void *load_bitmap_file(char *filename);
extern short remove_bitmap_file(void);
extern void draw_bitmap(void *, short x, short y, short flip, short shp_num);
extern void draw_sbitmap(void *, short x, short y, short flip, short shp_num);
extern void free_emm_bitmap_handles(void);
extern void free_bitmap_file(void *table);

/* * * * *
*
*  m_glass.c
*
* * * * */
extern short magnify_check_cat(PART *m_glass, PART *cat);
extern short magnify_check_mouse(PART *m_glass, PART *mouse);

/* * * * *
*
*  tn_ladr.c
*
* * * * */
extern void ladder_resize(PART *wall_part);
extern void init_part_ladder(PART *part, short run_index, short climb_seq,
   short default_index, short default_seq);
extern short ladder_exit(PART *part, PART *ladder, short direction, short exit);


/* * * * *
*
*  tn_mallt.c
*
* * * * */
extern void hammer_reinit(PART *hammer);
extern void mallet_internal(PART *mallet);

/* * * * *
*
*  tn_anvil.c
*
* * * * */
extern void anvil_reinit(PART *anvil);
extern void anvil_internal(PART *anvil);

/* * * * *
*
*  tn_egg.c
*
* * * * */
extern void egg_timer_reinit(PART *egg);
extern void egg_timer_flip(PART *egg, SHORT flip_mode);
extern short egg_timer_collide(PART *cur_part);
extern void egg_timer_internal(PART *egg);
extern void draw_egg_timer(PART *messager,UCHAR plane,SHORT loc_scale_adj,SHORT size_scale_adj);

/* * * * *
*
*  tn_shswt.c
*
* * * * */
extern void chuteswitch_reinit(PART *chuteswitch_part);
extern void chuteswitch_flip(PART *chuteswitch_part,short flip_mode);
extern void chuteswitch_internal(PART *chuteswitch_part);

/* * * * *
*
*  tn_updwn.c
*
* * * * */
extern void updown_reinit(PART *updown_part);
extern void updown_internal(PART *updown_part);
extern void updown_flip(PART *updown_part,short flip_mode);
extern short updown_bounce(PART *cur_part);
extern void draw_ud_counter(PART *counter,UCHAR plane,SHORT loc_scale_adj,SHORT size_scale_adj);
extern short collide_with_ud_counter(PART *counter, PART *pptr);


/* * * * *
*
*  tn_mesg.c
*
* * * * */
extern void message_reinit(PART *message);
extern void message_internal(PART *message);
extern short message_bounce(PART *cur_part);
extern short message_rope(PART *from_part,PART *message,short tie_num,short rope_type,short mass,long force);
extern void draw_messager(PART *messager,UCHAR plane,SHORT loc_scale_adj,SHORT size_scale_adj);


/* * * * *
*
*  tn_rtrns.c
*
* * * * */
extern void rottrans_reinit(PART *rottrans);
extern void rottrans_flip(PART *rottrans,short flip_mode);
extern void rottrans_internal(PART *rottrans);


/* * * * *
*
*  tn_trot.c
*
* * * * */
extern void transrot_reinit(PART *transrot);
extern void transrot_flip(PART *transrot,short flip_mode);
extern void transrot_internal(PART *transrot);
extern short transrot_bounce(PART *cur_part);
extern short transrot_rope(PART *from_part,PART *transrot,short tie_num,short rope_type,short mass,long force);
extern short collide_with_transrot(PART *transrot, PART *pptr);


/* * * * *
*
*  tn_incdec.c
*
* * * * */
extern void incdec_reinit(PART *incdec);
extern void incdec_flip(PART *incdec,short flip_mode);
extern void incdec_internal(PART *incdec);
extern void incdec_resize(PART *incdec);
extern short incdec_bounce(PART *cur_part);
extern void draw_incdec(PART *incdec,UCHAR plane,SHORT loc_scale_adj,SHORT size_scale_adj);

/* * * * *
*
*  tn_hatpn.c
*
* * * * */
extern void hatpin_reinit(PART *hatpin);
extern void hatpin_flip(PART *hatpin,short flip_mode);

/* * * * *
*
*  tn_chees.c
*
* * * * */
extern void cheese_reinit(PART *cheese);

/* * * * *
*
*  tn_gum.c
*
* * * * */
extern void gum_reinit(PART *gum);

/* * * * *
*
*  tn_nut.c
*
* * * * */
extern void nut_reinit(PART *nut);

/* * * * *
*
*  tn_pencl.c
*
* * * * */
extern void pencil_reinit(PART *pencil);

/* * * * *
*
*  tn_piano.c
*
* * * * */
extern void piano_reinit(PART *piano);
extern void piano_internal(PART *piano);
extern short piano_collide(PART *cur_part);

/* * * * *
*
*  ww2bomb
*
* * * * */
extern short ww2bomb_bounce(PART *cur_part);
extern void ww2bomb_reinit(PART *ww2bomb);
extern void ww2bomb_internal(PART *ww2bomb);

/* * * * *
*
*  tn_dryer.c
*
* * * * */
extern void hairdryer_reinit(PART *hairdryer);
extern void hairdryer_flip(PART *hairdryer,short flip_mode);
extern void hairdryer_internal(PART *hairdryer);

/* * * * *
*
*  tn_whstl.c
*
* * * * */
extern void whistle_reinit(PART *whistle);
extern short whistle_rope(PART *from_part,PART *whistle,short tie_num,short rope_type,short mass,long force);
extern void whistle_internal(PART *whistle);

/* * * * *
*
*  tn_eleph.c
*
* * * * */
extern void elephant_reinit(PART *elephant);
extern short elephant_bounce(PART *cur_part);
extern void elephant_flip(PART *elephant,short flip_mode);
extern void elephant_internal(PART *elephant);


/* * * * *
*
*  tn_fish.c
*
* * * * */
extern void fish_reinit(PART *fish);


/* * * * *
*
*  tn_egg1.c
*
* * * * */
extern void egg_reinit(PART *egg);
extern short egg_bounce(PART *cur_part);
extern void egg_internal(PART *egg);

/* * * * *
*
*  tn_chken.c
*
* * * * */
extern void chicken_reinit(PART *chicken);
extern short chicken_bounce(PART *cur_part);
extern void chicken_internal(PART *chicken);

/* * * * *
*
*  tn_bana.c
*
* * * * */
extern void banana_reinit(PART *banana);
extern void banana_internal(PART *banana);

/* * * * *
*
*  tn_rug.c
*
* * * * */
extern void rug_reinit(PART *rug);
extern short rug_collide(PART *cur_part);
extern void rug_internal(PART *rug);

/* * * * *
*
*  tn_trap.c
*
* * * * */
extern void trap_door_reinit(PART *trap_door);
extern short trap_door_bounce(PART *cur_part);
extern short trap_door_rope(PART *from_part,PART *trap_door,short tie_num,short rope_type,short mass,long force);
extern void trap_door_flip(PART *trap_door,short flip_mode);
extern void trap_door_internal(PART *trap_door);
extern short collide_with_trap_door(PART *trap_door, PART *pptr);

/* * * * *
*
*  tn_ant.c
*
* * * * */
extern void ant_reinit( PART *);
extern short ant_bounce( PART *);
extern void ant_internal( PART *);
extern void ant_flip( PART *, short);
extern void startle_ant( PART *);

/* * * * *
*
*  tn_eatmotor.c
*
* * * * */
extern void eatmotor_reinit( PART *);
extern short eatmotor_bounce( PART *);
extern void eatmotor_internal( PART *);
extern void eatmotor_flip( PART *, short);




