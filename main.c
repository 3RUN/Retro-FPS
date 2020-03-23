
#include <acknex.h>
#include <default.c>
#include <windows.h>

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

// game states
#define GAME_LEVEL_LOADING 0
#define GAME_LEVEL_RUNNING 1
#define GAME_LEVEL_INFO 2

// game logic stuff
var game_state = GAME_LEVEL_LOADING; // current game state

// include all stuff here
#include "include.h"

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

// main game function
void main()
{
	on_frame = on_frame_event;
	on_close = on_close_event;
	on_level_load = on_level_load_event;
	on_ent_remove = on_ent_remove_event;
	on_caps = player_toggle_run;
	on_r = level_restart;

	gui_init();
	init_levels();
	set_engine_settings();

	level_load(level_id);
}