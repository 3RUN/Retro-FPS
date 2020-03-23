/*#########################################################################################################################################################
NEXUS A8 : GAME BUILDER :: By Brian Pressley (Evo) (Evoeon) :::: Core Script HEADER :: Lite-C :: 3DGamestudio A8
#########################################################################################################################################################*/


//EDITOR TILESETS
BMAP* tileset_A  = "tileset_A.png";
BMAP* tileset_A1 = "tileset_A1.png";
BMAP* tileset_A2 = "tileset_A2.png";
BMAP* tileset_A3 = "tileset_A3.png";
BMAP* tileset_A4 = "tileset_A4.png";
BMAP* tileset_A5 = "tileset_A5.png";
BMAP* tileset_A6 = "tileset_A6.png";
BMAP* tileset_A7 = "tileset_A7.png";


//EDITOR BMAPS
BMAP* active_grid = "active_grid.png";
BMAP* active_tileset = "active_tileset.png";
BMAP* editor_bg = "editor_bg.png";
BMAP* tile_empty = "tile_empty.png";
BMAP* cell_empty = "cell.png";
BMAP* cell_over = "cell_over.png";
BMAP* arrow = "arrow.png";
BMAP* sm_x_bu = "sm_x_bu.png";
BMAP* sm_x_bu_over = "sm_x_bu_over.png";
BMAP* editor_overlay = "editor_overlay.png";
BMAP* gui_bu = "gui_bu.png";
BMAP* gui_bu_over = "gui_bu_over.png";
BMAP* gui_bu_2 = "gui_bu_2.png";
BMAP* gui_bu_2_over = "gui_bu_2_over.png";
BMAP* gui_bu_3 = "gui_bu_3.png";
BMAP* gui_bu_3_over = "gui_bu_3_over.png";
BMAP* gui_bu_load = "gui_bu_load.png";
BMAP* gui_bu_load_over = "gui_bu_load_over.png";
BMAP* gui_bu_3d = "gui_bu_3d.png";
BMAP* gui_bu_3d_over = "gui_bu_3d_over.png";
BMAP* menu_bu_4 = "menu_bu_4.png";
BMAP* menu_bu_4_over = "menu_bu_4_over.png";
BMAP* tile_menu = "tile_menu.png";
BMAP* import_bu = "import_bu.png";
BMAP* import_bu_over = "import_bu_over.png";
BMAP* sm_bu_minus = "sm_bu_minus.png";
BMAP* sm_bu_minus_over = "sm_bu_minus_over.png";
BMAP* sm_bu_plus = "sm_bu_plus.png";
BMAP* sm_bu_plus_over = "sm_bu_plus_over.png";
BMAP* intro_title = "intro_title.png";
BMAP* icon_bu = "icon_bu.png";
BMAP* tog_layer_bu = "tog_layer_bu.png";
BMAP* tog_layer_bu_ov = "tog_layer_bu_ov.png";
BMAP* tog_buildmode_bu = "tog_buildmode_bu.png";
BMAP* tog_buildmode_bu_ov = "tog_buildmode_bu_ov.png";
BMAP* tog_eventmode_bu = "tog_eventmode_bu.png";
BMAP* tog_eventmode_bu_ov = "tog_eventmode_bu_ov.png";
BMAP* tog_settings_bu = "tog_settings_bu.png";
BMAP* tog_settings_bu_ov = "tog_settings_bu_ov.png";
BMAP* settings_menu = "settings_menu.png";


//ACTIVE TILESET NAME SHOWN ON MAIN MENU
STRING* tileset_names = "";
TEXT* show_tileset_names = 
{
	pos_x=1180; 
	pos_y=7; 
	layer=21;
	string=tileset_names; 
	font=bmap_font; 
	red=1; green=1; blue=1; 
	flags=SHOW | LIGHT | CENTER_X;
}


//LEVEL NAME STRING : Visible on the top menu whenever a level file is saved or loaded)
STRING* lv_nm_on_main = "#61";
TEXT* show_lv_nm_on_main = 
{
	pos_x=689; 
	pos_y=7; 
	layer=13; 
	string=lv_nm_on_main; 
	font=small_fontD; 
	red=255; green=255; blue=255; 
	flags=SHOW | LIGHT | CENTER_X;
}


//LAYER STRING : SHOWS WHICH LAYER IS ACTIVE (Visible at the bottom left corner of the screen)
STRING* editor_layer_txt = "Layer 1 : Ground";
TEXT* show_layer_txt = 
{
	pos_x=10; 
	pos_y=680; 
	layer=1000; 
	string=editor_layer_txt; 
	font=small_fontD; 
	red=255; green=255; blue=255; 
	flags=SHOW | LIGHT | OUTLINE;
}


//MODE STRING : SHOWS WHICH EDITOR MODE IS ACTIVE (Visible at the bottom left corner of the screen)
STRING* editor_mode_txt = "Build Mode Enabled";
TEXT* show_mode_txt = 
{
	pos_x=10; 
	pos_y=700; 
	layer=1000; 
	string=editor_mode_txt; 
	font=small_fontD; 
	red=255; green=255; blue=255; 
	flags=SHOW | LIGHT | OUTLINE;
}


//SIDE MENU : IMPORT FILE NAMES (GLOBAL SETTINGS)
TEXT* show_skybox_name = 
{
	pos_x=1158; 
	pos_y=570; 
	layer=13; 
	string=set_skybox_name; 
	font=small_font; 
	red=1; green=1; blue=1; 
	flags=SHOW | LIGHT;
}
TEXT* show_audio_name = 
{
	pos_x=1158; 
	pos_y=610; 
	layer=13; 
	string=set_audio_name; 
	font=small_font; 
	red=1; green=1; blue=1; 
	flags=SHOW | LIGHT;
}
TEXT* show_floor_name = 
{
	pos_x=1158; 
	pos_y=651; 
	layer=13; 
	string=set_floor_name; 
	font=small_font; 
	red=1; green=1; blue=1; 
	flags=LIGHT;
}
TEXT* show_ceiling_name = 
{
	pos_x=1158; 
	pos_y=691; 
	layer=13; 
	string=set_ceiling_name; 
	font=small_font; 
	red=1; green=1; blue=1; 
	flags=LIGHT;
}


//LEVEL WEATHER STRING (LEVEL SETTINGS)
STRING* weather_name = "Weather : None";
TEXT* show_weather_name = 
{
	pos_x=722; 
	pos_y=400; 
	layer=21; 
	string=weather_name; 
	font=small_fontC; 
	red=1; green=1; blue=1; 
	flags=LIGHT | CENTER_X;
}


//OVERLAY OUTLINE OF ACTIVE GRID AREA
PANEL* show_active_grid = 
{
	bmap=active_grid;
	pos_x=0;	
	pos_y=32; 
	alpha=90; 
	layer = 12;
	flags=LIGHT | SHOW | UNTOUCHABLE;
	red=255; green=255; blue=255;
}


//OVERLAY OUTLINE OF SIDE MENU TILESET AREA
PANEL* show_active_tileset = 
{
	bmap=active_tileset;
	pos_x=1085;	
	pos_y=34; 
	alpha=40; 
	layer = 12;
	flags=UNTOUCHABLE;
}


//BG IMAGE
PANEL* editor_bg_panel = 
{
	bmap=editor_bg;
	pos_x=0;	
	pos_y=0;	
	layer = -1;
	flags=SHOW;
}


//TITLE IMAGE
PANEL* intro_panel = 
{
	bmap=intro_title;
	pos_x=0;	
	pos_y=0;	
	layer = 1001;
	flags=SHOW;
}


//CURSOR FOR SELECTED TILE
PANEL* cursor_over = 
{
	bmap=cell_over;
	pos_x=1134;	
	pos_y=64;	
	layer = 13;
	flags=SHOW | UNTOUCHABLE;
}


//EDITOR TOP MENU
PANEL* cell_editor_overlay = 
{
	bmap=editor_overlay;
	pos_x=0;
	pos_y=0;
	layer = 11;
	flags=SHOW;
	button(10,2,gui_bu_over,gui_bu,gui_bu_over,save_level_to_file,NULL,NULL);
	button(96,2,gui_bu_load_over,gui_bu_load,gui_bu_load_over,load_level_from_file,NULL,NULL);
	button(182,2,gui_bu_2_over,gui_bu_2,gui_bu_2_over,reset_the_level,NULL,NULL);
	button(290,2,gui_bu_3d_over,gui_bu_3d,gui_bu_3d_over,open_chapter_menu,NULL,NULL);
	button(948,3,tog_layer_bu_ov,tog_layer_bu,tog_layer_bu_ov,toggle_layers,NULL,NULL);
	button(980,3,tog_buildmode_bu_ov,tog_buildmode_bu,tog_buildmode_bu_ov,activate_build_mode,NULL,NULL);
	button(1012,3,tog_eventmode_bu_ov,tog_eventmode_bu,tog_eventmode_bu_ov,activate_event_mode,NULL,NULL);
	button(1044,3,tog_settings_bu_ov,tog_settings_bu,tog_settings_bu_ov,open_settings_menu,NULL,NULL);
	button(1082,5,sm_bu_minus_over,sm_bu_minus,sm_bu_minus_over,change_tileset_minus,NULL,NULL);
	button(1252,5,sm_bu_plus_over,sm_bu_plus,sm_bu_plus_over,change_tileset_plus,NULL,NULL);
}


//EDITOR SIDE MENU
PANEL* tile_icon_menu = 
{
	bmap=tile_menu;
	pos_x=1080;	pos_y=0;	layer = 10;
	button(11,565,import_bu_over,import_bu,import_bu_over,import_skybox_name,NULL,NULL);
	button(11,605,import_bu_over,import_bu,import_bu_over,import_audio_name,NULL,NULL);
//	button(11,646,import_bu_over,import_bu,import_bu_over,import_floor_name,NULL,NULL);
//	button(11,687,import_bu_over,import_bu,import_bu_over,import_ceiling_name,NULL,NULL);
	flags=SHOW;
}


//TILESET
PANEL* tileset_A_panel = 
{
	bmap=tileset_A;
	pos_x=1102;	pos_y=64;	layer = 11;
	flags=SHOW;
}


//SETTINGS MENU PANEL
PANEL* show_settings_menu = 
{
	bmap=settings_menu;
	
	//Set Fog : Near
	button(601,314,sm_bu_minus_over,sm_bu_minus,sm_bu_minus_over,change_fognear_minus,NULL,NULL);
	digits(630,316, -4, small_fontC, 1, settings_val_near);
	button(658,314,sm_bu_plus_over,sm_bu_plus,sm_bu_plus_over,change_fognear_plus,NULL,NULL);
	
	//Set Fog : Far
	button(737,314,sm_bu_minus_over,sm_bu_minus,sm_bu_minus_over,change_fogfar_minus,NULL,NULL);
	digits(766,316, -4, small_fontC, 1, settings_val_far);
	button(794,314,sm_bu_plus_over,sm_bu_plus,sm_bu_plus_over,change_fogfar_plus,NULL,NULL);
	
	//Set Time : Minutes
	button(601,355,sm_bu_minus_over,sm_bu_minus,sm_bu_minus_over,change_timemin_minus,NULL,NULL);
	digits(636,357, -2, small_fontC, 1, settings_val_min);
	button(658,355,sm_bu_plus_over,sm_bu_plus,sm_bu_plus_over,change_timemin_plus,NULL,NULL);
	
	//Set Time : Seconds
	button(737,355,sm_bu_minus_over,sm_bu_minus,sm_bu_minus_over,change_timesec_minus,NULL,NULL);
	digits(772,357, -2, small_fontC, 1, settings_val_sec);
	button(794,355,sm_bu_plus_over,sm_bu_plus,sm_bu_plus_over,change_timesec_plus,NULL,NULL);
	
	//Set Weather
	button(624,396,sm_bu_minus_over,sm_bu_minus,sm_bu_minus_over,change_weather_minus,NULL,NULL);
	button(794,396,sm_bu_plus_over,sm_bu_plus,sm_bu_plus_over,change_weather_plus,NULL,NULL);
	
	//Save and Exit
	button(612,435,ch_save_bu_over,ch_save_bu,ch_save_bu_over,close_settings_menu,NULL,NULL);
	
	pos_x=0;	pos_y=0; layer = 20;
	red=1; green=1; blue=1;
}


//ENABLE MOUSE
void call_mouse();


//USE BY SAVE/LOAD FOR FILE CREATION
void next_line();


//TOP MENU BUTTONS
//Toggle Layers (Not Included In The Prototype Version)
//Enable Build Mode
//Enable Event Mode
//Open Settings Menu
void toggle_layers();
void activate_build_mode();
void activate_event_mode();
void open_settings_menu();


//EDIT FOG SETTING (Settings Menu)
void change_fognear_minus();
void change_fognear_plus();
void change_fogfar_minus();
void change_fogfar_plus();


//EDIT LEVEL TIME SETTING (Settings Menu)
void change_timemin_minus();
void change_timemin_plus();
void change_timesec_minus();
void change_timesec_plus();


//EDIT LEVEL WEATHER (Settings Menu)
void set_weather_name();
void change_weather_minus();
void change_weather_plus();


//CLOSE SETTINGS MENU
void close_settings_menu();


//IDENTIFY/SWITCH BETWEEN TILESETS
void identify_tileset();
void change_tileset_minus();
void change_tileset_plus();


//LEFT MOUSE BUTTON : WHEN ANY GRID TILE IS CLICKED IT SETS CORRECT TILE DATA THEN CALLS THE DRAW FUNCTION
void interactive_grid();


//RIGHT MOUSE BUTTON : WHEN ANY GRID TILE IS CLICKED : REMOVE THE TILE
void reset_a_tile();


//EMPTY LEVEL : RESETS ALL TILES
void reset_the_level();


//BUILDS THE INTERACTIVE GRID TILES : LAYER A
void build_grid_layer_A();


//DELETES THE INTERACTIVE GRID TILES : LAYER A
void delete_grid();


//BUILD SIDE MENU TILESET BUTTONS : 75 TOTAL
void build_tileset_buttons();


//SIDE MENU TILESET FUNCTIONS : CLICK TO SELECT ANY TILE FROM THE TILESET MENU
void tileset_A_clicked();


//IMPORT FILE NAMES FOR GLOBAL SETTINGS
void import_skybox_name();
void import_audio_name();
void import_floor_name();
void import_ceiling_name();


//LOADS A SAVED LEVEL FILE
void load_level_from_file();


//SAVES A LEVEL TO FILE
void save_level_to_file();


//DRAWS ANY SELECTED TILE ON THE LEVEL GRID
void edit_cell_tile();


//INIT THE EDITOR
void init_editor();


//EXIT THE EDITOR
void exit_editor();
