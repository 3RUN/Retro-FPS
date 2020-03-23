/*#########################################################################################################################################################
NEXUS A8 : GAME BUILDER :: By Brian Pressley (Evo) (Evoeon) :::: Content Manager Script HEADER :: Lite-C :: 3DGamestudio A8
#########################################################################################################################################################*/


//CONTENT CREATION MENU : BMAPS
BMAP* content_menu = "content_menu.png";
BMAP* ckbox_bu = "ckbox_bu.png";
BMAP* ckbox_bu_over = "ckbox_bu_over.png";
BMAP* ckbox_bu_on = "ckbox_bu_on.png";
BMAP* ckbox_bu_on_ov = "ckbox_bu_on_ov.png";
BMAP* ckbox_bu_star = "ckbox_bu_star.png";
BMAP* ckbox_bu_star_ov = "ckbox_bu_star_ov.png";
BMAP* disable_cm_all = "disable_cm_all.png";
BMAP* disable_cm_top = "disable_cm_top.png";
BMAP* disable_cm_mid = "disable_cm_mid.png";
BMAP* disable_cm_bot = "disable_cm_bot.png";


//OVERLAYS TO DISABLE OPTIONS IN THE CONTENT MANAGER
PANEL* disable_all_options =  {bmap=disable_cm_all;	pos_x=683;	pos_y=186;	layer = 18;}
PANEL* disable_ent_options =  {bmap=disable_cm_top;	pos_x=682;	pos_y=241;	layer = 18;}
PANEL* disable_skin_options = {bmap=disable_cm_top;	pos_x=682;	pos_y=285;	layer = 18;}
PANEL* disable_door_options = {bmap=disable_cm_mid;	pos_x=682;	pos_y=335;	layer = 18;}
PANEL* disable_prop_options = {bmap=disable_cm_mid;	pos_x=873;	pos_y=335;	layer = 18;}
PANEL* disable_swt_options =  {bmap=disable_cm_bot;	pos_x=682;	pos_y=494;	layer = 18;}
PANEL* disable_bonus_options = {bmap=disable_cm_bot;	pos_x=873;	pos_y=494;	layer = 18;}


//CONTENT CREATION MENU : FILE NAMES
STRING* content_name_ent = " ";
STRING* content_name_skin = " ";
TEXT* show_content_name_ent = 
{
	pos_x=771; 
	pos_y=263; 
	layer=17; 
	string=content_name_ent; 
	font=small_font; 
	red=1; green=1; blue=1; 
	flags=LIGHT;
}
TEXT* show_content_name_skin = 
{
	pos_x=771; 
	pos_y=306; 
	layer=17; 
	string=content_name_skin; 
	font=small_font; 
	red=1; green=1; blue=1; 
	flags=LIGHT;
}


//CONTENT MANAGER PANEL
PANEL* editor_content_panel = 
{
	bmap=content_menu;
	
	//Primary
	button(812,108,ckbox_bu_over,ckbox_bu,ckbox_bu_over,NULL,NULL,NULL);
	button(899,108,ckbox_bu_over,ckbox_bu,ckbox_bu_over,NULL,NULL,NULL);
	button(993,108,ckbox_bu_over,ckbox_bu,ckbox_bu_over,NULL,NULL,NULL);
	button(812,131,ckbox_bu_over,ckbox_bu,ckbox_bu_over,NULL,NULL,NULL);
	button(899,131,ckbox_bu_over,ckbox_bu,ckbox_bu_over,NULL,NULL,NULL);
	button(993,131,ckbox_bu_over,ckbox_bu,ckbox_bu_over,NULL,NULL,NULL);
	button(812,154,ckbox_bu_over,ckbox_bu,ckbox_bu_over,NULL,NULL,NULL);
	button(899,154,ckbox_bu_over,ckbox_bu,ckbox_bu_over,NULL,NULL,NULL);
	button(993,154,ckbox_bu_over,ckbox_bu,ckbox_bu_over,NULL,NULL,NULL);
	
	//Entity files
	button(703,258,import_bu_over,import_bu,import_bu_over,import_entity_file,NULL,NULL);
	button(703,301,import_bu_over,import_bu,import_bu_over,import_entity_skin,NULL,NULL);
	
	//Door Flags
	button(823,367,ckbox_bu_over,ckbox_bu,ckbox_bu_over,set_flag_door_Op_1,NULL,NULL);
	button(823,390,ckbox_bu_over,ckbox_bu,ckbox_bu_over,set_flag_door_Op_2,NULL,NULL);
	button(823,413,ckbox_bu_over,ckbox_bu,ckbox_bu_over,set_flag_door_Op_3,NULL,NULL);
	button(823,436,ckbox_bu_over,ckbox_bu,ckbox_bu_over,set_flag_door_Op_4,NULL,NULL);
	button(823,459,ckbox_bu_over,ckbox_bu,ckbox_bu_over,set_flag_door_Op_5,NULL,NULL);
	
	//Prop Flags
	button(986,367,ckbox_bu_over,ckbox_bu,ckbox_bu_over,set_flag_prop_Op_1,NULL,NULL);
	button(986,390,ckbox_bu_over,ckbox_bu,ckbox_bu_over,set_flag_prop_Op_2,NULL,NULL);
	button(986,413,ckbox_bu_over,ckbox_bu,ckbox_bu_over,set_flag_prop_Op_3,NULL,NULL);
	button(986,436,ckbox_bu_over,ckbox_bu,ckbox_bu_over,set_flag_prop_Op_4,NULL,NULL);
	button(986,459,ckbox_bu_over,ckbox_bu,ckbox_bu_over,set_flag_prop_Op_5,NULL,NULL);
	
	//Control Flags
	button(823,527,ckbox_bu_over,ckbox_bu,ckbox_bu_over,set_flag_swt_Op_1,NULL,NULL);
	button(823,550,ckbox_bu_over,ckbox_bu,ckbox_bu_over,set_flag_swt_Op_2,NULL,NULL);
	
	//Bonus Flags
	button(986,527,ckbox_bu_over,ckbox_bu,ckbox_bu_over,set_flag_bonus_Op_1,NULL,NULL);
	button(986,550,ckbox_bu_over,ckbox_bu,ckbox_bu_over,set_flag_bonus_Op_2,NULL,NULL);
	
	//X buttons to reset the custom function name
	button(1026,197,sm_x_bu_over,sm_x_bu,sm_x_bu_over,reset_funcname_empty,NULL,NULL);
	button(1026,248,sm_x_bu_over,sm_x_bu,sm_x_bu_over,reset_entname_empty,NULL,NULL);
	button(1026,291,sm_x_bu_over,sm_x_bu,sm_x_bu_over,reset_entskin_empty,NULL,NULL);
	
	//Reset button and save button
	button(768,605,gui_bu_2_over,gui_bu_2,gui_bu_2_over,reset_cm_slot_data,NULL,NULL);
	button(880,605,gui_bu_over,gui_bu,gui_bu_over,save_cm_slot_data,NULL,NULL);
	
	//Show selected tile IDS on content menu
	digits(694, 69, -2, small_fontD, 1, cm_tileset_id);
	digits(1028, 69, -2, small_fontD, 1, cm_tile_id);
	pos_x=0;	pos_y=0;	layer = 16;
}


//SAVE CONTENT CREATION FILE (cm_build)
void save_editor_cm_data();


//LOAD CONTENT CREATION FILE (cm_build)
void load_editor_cm_data();


//USED BY THE CONTENT EDITOR TO SET PRIMARY CONTENT TYPES (Checkboxes)
void click_primary_bu1();
void click_primary_bu2();
void click_primary_bu3();
void click_primary_bu4();
void click_primary_bu5();
void click_primary_bu6();
void click_primary_bu7();
void click_primary_bu8();
void click_primary_bu9();


//USED BY THE CONTENT EDITOR TO SET DOOR FLAGS (Checkboxes)
void set_flag_door_Op_1();
void set_flag_door_Op_2();
void set_flag_door_Op_3();
void set_flag_door_Op_4();
void set_flag_door_Op_5();


//USED BY THE CONTENT EDITOR TO SET PROP FLAGS (Checkboxes)
void set_flag_prop_Op_1();
void set_flag_prop_Op_2();
void set_flag_prop_Op_3();
void set_flag_prop_Op_4();
void set_flag_prop_Op_5();


//USED BY THE CONTENT EDITOR TO SET SWITCH AND TRIGGER FLAGS (Checkboxes)
void set_flag_swt_Op_1();
void set_flag_swt_Op_2();


//USED BY THE CONTENT EDITOR TO SET BONUS FLAGS (Checkboxes)
void set_flag_bonus_Op_1();
void set_flag_bonus_Op_2();


//USED BY THE CONTENT EDITOR TO IDENTIFY AND SET CORRECT TILE DATA
void set_content_data();


//USED BY THE CONTENT EDITOR TO SAVE CONTENT DATA OF ANY EDITED TILES
void save_cm_slot_data();


//USED BY THE CONTENT EDITOR TO RESET CONTENT DATA OF ANY SELECTED TILES
void reset_cm_slot_data();


//USED BY THE CONTENT EDITOR TO SET OR IMPORT NAMES OF ENTITIES AND TEXTURE SKINS 
void import_entity_file();
void import_entity_skin();


//OPENS THE CONTENT MENU WHEN SIDE MENU TILESET ICONS ARE CLICKED
void open_content_menu();


//EMPTIES A CONTENT MENU STRING WHEN SMALL X IS CLICKED
void reset_funcname_empty();
void reset_entname_empty();
void reset_entskin_empty();


//AUTO GENERATE A HEADER FOR ACTION AND FUNCTION POINTERS
void gen_nxs_pointers();


//AUTO GENERATE BMAPS FOR MODEL SKINS
void gen_nxs_bmap_ptrs();