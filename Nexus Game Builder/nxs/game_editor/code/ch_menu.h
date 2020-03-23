/*#########################################################################################################################################################
NEXUS A8 : GAME BUILDER :: By Brian Pressley (Evo) (Evoeon) :::: Chapter Menu HEADER :: Lite-C :: 3DGamestudio A8
#########################################################################################################################################################*/


//CHAPTER EDITOR BMAPS
BMAP* chapter_menu = "chapter_menu.png";
BMAP* ch_save_bu = "ch_save_bu.png";
BMAP* ch_save_bu_over = "ch_save_bu_over.png";
BMAP* ch_load_bu = "ch_load_bu.png";
BMAP* ch_load_bu_over = "ch_load_bu_over.png";
BMAP* ch_exit_bu = "ch_exit_bu.png";
BMAP* ch_exit_bu_over = "ch_exit_bu_over.png";


//USED BY CHAPTER EDITOR
int chapter_link_id = 0;


//CHAPTER EDITOR LEVEL LINK NAMES
STRING* set_level_link_1 = " ";
STRING* set_level_link_2 = " ";
STRING* set_level_link_3 = " ";
STRING* set_level_link_4 = " ";
STRING* set_level_link_5 = " ";
STRING* set_level_link_6 = " ";
STRING* set_level_link_7 = " ";
STRING* set_level_link_8 = " ";
STRING* set_level_link_9 = " ";
STRING* set_level_link_10 = " ";
TEXT* show_link_1_name = {pos_x=841; pos_y=195; layer=21; string=set_level_link_1; font=small_fontB; red=1; green=1; blue=1; flags=LIGHT;}
TEXT* show_link_2_name = {pos_x=841; pos_y=235; layer=21; string=set_level_link_2; font=small_fontB; red=1; green=1; blue=1; flags=LIGHT;}
TEXT* show_link_3_name = {pos_x=841; pos_y=276; layer=21; string=set_level_link_3; font=small_fontB; red=1; green=1; blue=1; flags=LIGHT;}
TEXT* show_link_4_name = {pos_x=841; pos_y=317; layer=21; string=set_level_link_4; font=small_fontB; red=1; green=1; blue=1; flags=LIGHT;}
TEXT* show_link_5_name = {pos_x=841; pos_y=358; layer=21; string=set_level_link_5; font=small_fontB; red=1; green=1; blue=1; flags=LIGHT;}
TEXT* show_link_6_name = {pos_x=841; pos_y=398; layer=21; string=set_level_link_6; font=small_fontB; red=1; green=1; blue=1; flags=LIGHT;}
TEXT* show_link_7_name = {pos_x=841; pos_y=439; layer=21; string=set_level_link_7; font=small_fontB; red=1; green=1; blue=1; flags=LIGHT;}
TEXT* show_link_8_name = {pos_x=841; pos_y=480; layer=21; string=set_level_link_8; font=small_fontB; red=1; green=1; blue=1; flags=LIGHT;}
TEXT* show_link_9_name = {pos_x=841; pos_y=522; layer=21; string=set_level_link_9; font=small_fontB; red=1; green=1; blue=1; flags=LIGHT;}
TEXT* show_link_10_name = {pos_x=841; pos_y=563; layer=21; string=set_level_link_10; font=small_fontB; red=1; green=1; blue=1; flags=LIGHT;}


//CHAPTER EDITOR
PANEL* chapter_menu_bg = 
{
	bmap=chapter_menu;
	pos_x=0;	pos_y=0;	layer = 20;
	button(550,122,ch_save_bu_over,ch_save_bu,ch_save_bu_over,save_chapter_to_file,NULL,NULL);	
	button(612,122,ch_load_bu_over,ch_load_bu,ch_load_bu_over,load_chapter_from_file,NULL,NULL);
	button(674,122,ch_exit_bu_over,ch_exit_bu,ch_exit_bu_over,close_chapter_menu,NULL,NULL);
	button(774,190,import_bu_over,import_bu,import_bu_over,ch_import_bu_id_1,NULL,NULL);
	button(774,230,import_bu_over,import_bu,import_bu_over,ch_import_bu_id_2,NULL,NULL);
	button(774,271,import_bu_over,import_bu,import_bu_over,ch_import_bu_id_3,NULL,NULL);
	button(774,312,import_bu_over,import_bu,import_bu_over,ch_import_bu_id_4,NULL,NULL);
	button(774,353,import_bu_over,import_bu,import_bu_over,ch_import_bu_id_5,NULL,NULL);
	button(774,393,import_bu_over,import_bu,import_bu_over,ch_import_bu_id_6,NULL,NULL);
	button(774,434,import_bu_over,import_bu,import_bu_over,ch_import_bu_id_7,NULL,NULL);
	button(774,475,import_bu_over,import_bu,import_bu_over,ch_import_bu_id_8,NULL,NULL);
	button(774,517,import_bu_over,import_bu,import_bu_over,ch_import_bu_id_9,NULL,NULL);
	button(774,558,import_bu_over,import_bu,import_bu_over,ch_import_bu_id_10,NULL,NULL);
	button(161,177,sm_x_bu_over,sm_x_bu,sm_x_bu_over,reset_the_ch_txt_title,NULL,NULL);
	button(161,231,sm_x_bu_over,sm_x_bu,sm_x_bu_over,reset_the_ch_txt_msgA,NULL,NULL);
	button(161,415,sm_x_bu_over,sm_x_bu,sm_x_bu_over,reset_the_ch_txt_msgB,NULL,NULL);
	button(1097,180,sm_x_bu_over,sm_x_bu,sm_x_bu_over,reset_the_ch_link_1,NULL,NULL);
	button(1097,220,sm_x_bu_over,sm_x_bu,sm_x_bu_over,reset_the_ch_link_2,NULL,NULL);
	button(1097,262,sm_x_bu_over,sm_x_bu,sm_x_bu_over,reset_the_ch_link_3,NULL,NULL);
	button(1097,302,sm_x_bu_over,sm_x_bu,sm_x_bu_over,reset_the_ch_link_4,NULL,NULL);
	button(1097,343,sm_x_bu_over,sm_x_bu,sm_x_bu_over,reset_the_ch_link_5,NULL,NULL);
	button(1097,383,sm_x_bu_over,sm_x_bu,sm_x_bu_over,reset_the_ch_link_6,NULL,NULL);
	button(1097,424,sm_x_bu_over,sm_x_bu,sm_x_bu_over,reset_the_ch_link_7,NULL,NULL);
	button(1097,465,sm_x_bu_over,sm_x_bu,sm_x_bu_over,reset_the_ch_link_8,NULL,NULL);
	button(1097,507,sm_x_bu_over,sm_x_bu,sm_x_bu_over,reset_the_ch_link_9,NULL,NULL);
	button(1097,548,sm_x_bu_over,sm_x_bu,sm_x_bu_over,reset_the_ch_link_10,NULL,NULL);
}


//SMALL X BUTTONS TO RESET CHAPTER BOX DATA
void reset_the_ch_link_1();
void reset_the_ch_link_2();
void reset_the_ch_link_3();
void reset_the_ch_link_4();
void reset_the_ch_link_5();
void reset_the_ch_link_6();
void reset_the_ch_link_7();
void reset_the_ch_link_8();
void reset_the_ch_link_9();
void reset_the_ch_link_10();
void reset_the_ch_txt_title();
void reset_the_ch_txt_msgA();
void reset_the_ch_txt_msgB();


//OPEN THE CHAPTER EDITOR
void open_chapter_menu();


//REMOVE THE CHAPTER EDITOR
void close_chapter_menu();


//IMPORT LEVEL FILES TO LINK THEM TOGETHER AS A CHAPTER FILE
void import_level_name();


//BUTTONS FUNCTIONS TO IMPORT UP TO 10 LEVELS TO LINK TOGETHER
void ch_import_bu_id_1();
void ch_import_bu_id_2();
void ch_import_bu_id_3();
void ch_import_bu_id_4();
void ch_import_bu_id_5();
void ch_import_bu_id_6();
void ch_import_bu_id_7();
void ch_import_bu_id_8();
void ch_import_bu_id_9();
void ch_import_bu_id_10();


//SAVES A CHAPTER FILE
void save_chapter_to_file();


//LOADS A CHAPTER FILE
void load_chapter_from_file();