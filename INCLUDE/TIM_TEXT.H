extern char *slash_char;

extern char continue_btn[];
extern char yes_btn[];
extern char no_btn[];
extern char replay_btn[];
extern char advance_btn[];

extern char no_mem1_msg[];
extern char no_mem2_msg[];
extern char need_org_msg[];
extern char no_vm_msg[];
extern char goodbye_msg[];

#if TIM_ENGLISH
extern char password1_msg[];
extern char password2_msg[];
#elif TIM_GERMAN || TIM_FRENCH
extern char password1_msg[];
extern char password2a_msg[];
extern char password2b_msg[];
#endif

extern char version_title[];
extern char version_message[];

extern char low_mem_title[];
extern char low_mem_message[];
extern char out_mem_title[];
extern char out_mem_message[];

extern char quit_title[];
extern char quit_question[];
extern char rs_title[];
extern char rs_question[];
extern char ff_title[];
extern char ff_question[];
extern char l_ff_title[];
extern char l_ff_question[];
extern char no_grav_title[];
extern char no_grav_message[];
extern char no_dens_title[];
extern char no_dens_message[];
extern char c_pb_title[];
extern char c_pb_question[];
extern char adj_pb_title[];

extern char ow_title[];
extern char ow_question[];
extern char fe_title[];
extern char fe_message0[];
extern char fe_message1[];
extern char fe_message2[];
extern char path_title[];
extern char path_message[];
extern char not_tim_title[];
extern char not_tim_message[];

extern char password_title[];
extern char password_msg[];
extern char bad_pass_title[];
extern char bad_pass_msg[];
extern char bad_score_code_title[];
extern char bad_score_code_msg[];

extern char pdir_text[];

extern char lm_text[];
extern char sm_text[];
extern char load_text[];
extern char save_text[];
extern char canc_text[];
extern char file_name_text[];

extern char ff_mode_title[];
extern char puzzle_text[];
extern char completed_text[];
extern char bonus_text[];
extern char ptext[];
extern char click_text[];

extern char replay_title[];
extern char replay_msg[];

extern char sp_text[];
extern char password_text[];

extern char all_puzzles_title[];

#if TIM_DEMO

extern char demo_part_title[];
extern char ff_mode_desc[];
extern char demo_load_title[];
extern char demo_load_message[];
extern char demo_save_title[];
extern char demo_save_message[];
extern char all_puzzles_message[];

#else

extern char ff_mode_desc[];
extern char all_puzzles_message[];

#endif
