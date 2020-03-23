
#include <acknex.h>
#include <default.c>
#include <windows.h>
#include <strio.c>

#define PRAGMA_POINTER

#define PRAGMA_PATH "code"
#define PRAGMA_PATH "code\\ai"
#define PRAGMA_PATH "code\\cct"
#define PRAGMA_PATH "code\\fx"
#define PRAGMA_PATH "code\\explosion"
#define PRAGMA_PATH "code\\item"
#define PRAGMA_PATH "code\\gui"
#define PRAGMA_PATH "code\\level"
#define PRAGMA_PATH "code\\player"
#define PRAGMA_PATH "code\\props"
#define PRAGMA_PATH "code\\weapon"
#define PRAGMA_PATH "resources"
#define PRAGMA_PATH "resources\\ai"
#define PRAGMA_PATH "resources\\props"
#define PRAGMA_PATH "resources\\props\\foliage"
#define PRAGMA_PATH "resources\\props\\indoor"
#define PRAGMA_PATH "resources\\props\\others"
#define PRAGMA_PATH "resources\\items"
#define PRAGMA_PATH "textures"
#define PRAGMA_PATH "world"

//EDITOR PATHS
#define PRAGMA_PATH "nxs"
#define PRAGMA_PATH "nxs\\game_editor"
#define PRAGMA_PATH "nxs\\game_editor\\code_mesh"
#define PRAGMA_PATH "nxs\\game_editor\\levels"
#define PRAGMA_PATH "nxs\\game_editor\\chapters"
#define PRAGMA_BIND "nxs\\game_editor\\cm_build"

// game states
#define GAME_LEVEL_LOADING 0
#define GAME_LEVEL_RUNNING 1
#define GAME_LEVEL_INFO 2

// game logic stuff
var game_state = GAME_LEVEL_LOADING; // current game state

//Skycube
ENTITY* game_level_skycube =
{
	type = "sky_blue.png";
	flags2 = SKY | DOME | SHOW;
	layer = 100;
	z = 230; // move 30 pixels upwards
}

// include all stuff here
#include "textbox.h"
#include "DynamicModelsPtr.h"
#include "nxs_autobind.h"
#include "nxs_gen.h"
#include "include.h"
#include "nxs_pointers.h"
#include "nxs_gen.c"

// useful function to lock mouse inside of game window
void mouse_lock()
{
	static var autolock_mouse_locked = false;
	if (!autolock_mouse_locked && window_focus)
	{
		autolock_mouse_locked = true;
		RECT rect;
		GetClientRect(hWnd, &rect);
		ClientToScreen(hWnd, &rect);
		ClientToScreen(hWnd, &rect.right);
		ClipCursor(&rect);
	}
	if (autolock_mouse_locked && !window_focus)
	{
		autolock_mouse_locked = false;
		ClipCursor(NULL);
	}
}

// function called each frame
void on_frame_event()
{
	mouse_lock();
	update_gui();

	#ifdef PLAYER_IMMORTAL
		draw_text("Immortal mode is on", screen_size.x - 172, 10, COLOR_WHITE);
	#endif

	fps_max = 60;
	if (key_e)
	{
		fps_max = 30;
	}
	
	switch (game_state)
	{
		case GAME_LEVEL_LOADING:
		gui_level_info_show(false);
		if (level_is_loaded == true)
		{
			game_state = GAME_LEVEL_RUNNING;
		}
		break;

		case GAME_LEVEL_RUNNING:
		level_timer_start();
		props_update();
		player_update();
		npc_update();
		projectiles_update();
		break;

		case GAME_LEVEL_INFO:
		gui_level_info_show(true);
		break;
	}
	// cleanup all entities that should be deleted
	// this is useful (thanks to MasterQ32) since entity will be deleted
	// at the end of the frame
	{
		ENTITY *ent = ent_next(NULL);
		while (ent)
		{
			you = ent;
			ent = ent_next(ent);
			if (your->OBJ_DELETE == true)
			{
				ptr_remove(you);
			}
		}
	}
}

// function called when any entity get's removed
void on_ent_remove_event(ENTITY *ent)
{
	// player ?
	if (ent->OBJ_TYPE == TYPE_PLAYER)
	{
		delete_player_structure(ent);
	}

	// npc ?
	if (ent->OBJ_TYPE == TYPE_NPC)
	{
		delete_npc(ent);
	}

	// props ?
	if (ent->OBJ_TYPE == TYPE_PROPS_DOOR || ent->OBJ_TYPE == TYPE_PROPS_SECRET || ent->OBJ_TYPE == TYPE_PROPS_BARREL)
	{
		delete_props(ent);
	}
}

// called when level was fully loaded
void on_level_load_event(var percent)
{
	level_is_loaded = true;
}

// function is triggered on engine close
void on_close_event()
{
	music_stop();
}

// function to set all engine settings before start
void set_engine_settings()
{
	DMDLSettings.flags |= DMDL_FIXNORMALS;
	
	video_set(800, 600, 16, 2);
	video_aspect = 1.333;

	warn_level = 6;
	doppler_factor = 0;
	mouse_pointer = 0;

	d3d_mipmapping = 1;
	mip_levels = 1;

	max_entities = 10000;
	preload_mode = 3 + 4;

	d3d_near_models = 0.5;
	d3d_near_sprites = 0.5;
	d3d_near_decals = 0.99;

	fps_max = 60;
	fps_min = 30;
	time_smooth = 0.9;

	random_seed(0);
}


BMAP* fps_title_bg = "fps_title_bg.png";
PANEL* fps_title_pan = {pos_x=0; pos_y=0; bmap=fps_title_bg; layer=1000;}

BMAP* press_enter = "press_enter.png";
PANEL* press_enter_pan = {pos_x=293; pos_y=442; bmap=press_enter; layer=1001;}

BMAP* fps_ch_select_bg = "fps_ch_select_bg.png";
PANEL* fps_ch_bg_pan = {pos_x=0; pos_y=0; bmap=fps_ch_select_bg; layer=1000;}

BMAP* ch_selection = "ch_selection.png";
PANEL* ch_selection_pan = {pos_x=197; pos_y=482; bmap=ch_selection; layer=1001;}

int ch_id_is = 1;
int ch_is_selected = false;

STRING* gotofile;
TEXT* ch_index = { strings = 5;}
TEXT* ch_name_1 = { pos_x=400; pos_y=170; layer=1002; font=ackfont_sm; flags=CENTER_X; string = " ";}
TEXT* ch_name_2 = { pos_x=400; pos_y=225; layer=1002; font=ackfont_sm; flags=CENTER_X; string = " ";}
TEXT* ch_name_3 = { pos_x=400; pos_y=280; layer=1002; font=ackfont_sm; flags=CENTER_X; string = " ";}
TEXT* ch_name_4 = { pos_x=400; pos_y=335; layer=1002; font=ackfont_sm; flags=CENTER_X; string = " ";}
TEXT* ch_name_5 = { pos_x=400; pos_y=390; layer=1002; font=ackfont_sm; flags=CENTER_X; string = " ";}

BMAP* ch_selection_cur = "ch_selection_cur.png";
PANEL* ch_select_cur_pan = {pos_x=0; pos_y=151; bmap=ch_selection_cur; layer=1001;}

void cur_flash()
{
	while(ch_is_selected==false)
	{
	while(ch_select_cur_pan->alpha>=5 && ch_is_selected==false){ch_select_cur_pan->alpha-=1;if(ch_select_cur_pan->alpha==5){break;}wait(3);}
	while(ch_select_cur_pan->alpha<=20 && ch_is_selected==false){ch_select_cur_pan->alpha+=1;if(ch_select_cur_pan->alpha==20){break;}wait(3);}
		wait(1);
	}
}

// main game function`
void main()
{
	music_volume = 100;
	wait(3);
	
	//Load content database
	str_cpy(nxs_game_content, "cm_build");   
	nxs_load_editor_cm_data();	
	
	//Init the game
	on_frame = on_frame_event;
	on_close = on_close_event;
	on_level_load = on_level_load_event;
	on_ent_remove = on_ent_remove_event;
	on_caps = player_toggle_run;
	on_r = level_restart;
	gui_init();	
	init_levels();
	set_engine_settings();
	
	//Title Screen
	while(key_any==1){wait(1);}
	music_handle = media_loop("level_1.ogg", NULL, music_volume);
	set(fps_title_pan,SHOW);
	set(press_enter_pan,SHOW);
	while(key_enter==0)
	{
		press_enter_pan->alpha = 30;
		wait(3);
		if(key_enter==1){break;}
		press_enter_pan->alpha = 100;
		wait(3);
		if(key_enter==1){break;}
	}
	snd_play(weapon_rocketl_shoot_ogg, 80, 0); 
	while(key_any==1){wait(1);}
	reset(fps_title_pan,SHOW);
	reset(press_enter_pan,SHOW);
	wait(1);
	
	//Chapter Selection Menu
	//Scan folder for up to 5 chapter files (5 chapters max) (Up to 10 levels each) (Total of 50 Levels to play)
	int _x = 0;
	for (; _x<=4; _x++) {(ch_index->pstring)[_x] = str_create(" ");}
	STRING* gotofile = str_create(work_dir); str_cat(gotofile,"nxs\\game_editor\\chapters\\"); SetCurrentDirectory(_chr(gotofile));txt_for_dir(ch_index, "*.*");
	int found_a_file = false;
	cur_flash();
	set(fps_ch_bg_pan,SHOW);
	set(ch_selection_pan,SHOW);
	set(ch_select_cur_pan,SHOW);
	wait(12); snd_play(props_secret_found_ogg, 80, 0);
	set(ch_name_1,SHOW); str_cpy((ch_name_1->pstring)[0], (ch_index->pstring)[0]);wait(12);
	set(ch_name_2,SHOW); str_cpy((ch_name_2->pstring)[0], (ch_index->pstring)[1]);wait(12); 
	set(ch_name_3,SHOW); str_cpy((ch_name_3->pstring)[0], (ch_index->pstring)[2]);wait(12); 
	set(ch_name_4,SHOW); str_cpy((ch_name_4->pstring)[0], (ch_index->pstring)[3]);wait(12); 
	set(ch_name_5,SHOW); str_cpy((ch_name_5->pstring)[0], (ch_index->pstring)[4]);wait(12);
	while(1)
	{		
		if(key_w==1){while(key_w==1){wait(1);}if(ch_id_is>=2){ch_select_cur_pan->pos_y-=55;}ch_id_is-=1; snd_play(weapon_knife_stab_ogg, 80, 0);}
		if(key_s==1){while(key_s==1){wait(1);}if(ch_id_is<=4){ch_select_cur_pan->pos_y+=55;}ch_id_is+=1; snd_play(weapon_knife_stab_ogg, 80, 0);}
		if(ch_id_is<=1){ch_id_is=1;}
		if(ch_id_is>=5){ch_id_is=5;}
		if(!str_cmp((ch_index->pstring)[0], " ")){if(ch_id_is==1){str_cpy(nxs_game_chapter, (ch_index->pstring)[0]); found_a_file=true;}}
		if(!str_cmp((ch_index->pstring)[1], " ")){if(ch_id_is==2){str_cpy(nxs_game_chapter, (ch_index->pstring)[1]); found_a_file=true;}}
		if(!str_cmp((ch_index->pstring)[2], " ")){if(ch_id_is==3){str_cpy(nxs_game_chapter, (ch_index->pstring)[2]); found_a_file=true;}}
		if(!str_cmp((ch_index->pstring)[3], " ")){if(ch_id_is==4){str_cpy(nxs_game_chapter, (ch_index->pstring)[3]); found_a_file=true;}}
		if(!str_cmp((ch_index->pstring)[4], " ")){if(ch_id_is==5){str_cpy(nxs_game_chapter, (ch_index->pstring)[4]); found_a_file=true;}}
		if(key_enter==true && found_a_file==true){break;}
		wait(1);
	}
	snd_play(weapon_rocketl_shoot_ogg, 80, 0); 
	while(key_any==1){wait(1);}
	wait(12); snd_play(props_secret_found_ogg, 80, 0);
	reset(ch_name_1,SHOW);
	reset(ch_name_2,SHOW);
	reset(ch_name_3,SHOW);
	reset(ch_name_4,SHOW);
	reset(ch_name_5,SHOW);
	ch_is_selected = true;
	reset(ch_select_cur_pan,SHOW);
	reset(fps_ch_bg_pan,SHOW);
	reset(ch_selection_pan,SHOW);
	media_stop(music_handle);
	
	wait(12); snd_play(explosion01_ogg, 80, 0);
	wait(12); snd_play(explosion02_ogg, 80, 0);
	wait(12); snd_play(explosion03_ogg, 80, 0);
	wait(12); snd_play(item_gold_ogg, 80, 0);
	
	//Load the selected chapter
	nxs_load_chapter();
	wait_for(nxs_load_chapter);
	init_levels();
	wait_for(init_levels);
	
	wait(-1);
	//Start The Chapter and play
	level_load(level_id);
}

