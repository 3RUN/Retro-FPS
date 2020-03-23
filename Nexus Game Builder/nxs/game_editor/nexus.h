/*#########################################################################################################################################################
NEXUS A8 : GAME BUILDER :: By Brian Pressley (Evo) (Evoeon) :::: Nexus Script HEADER :: Lite-C :: 3DGamestudio A8
#########################################################################################################################################################*/


//EDITOR SETTINGS
#define LEVEL_X_MAX         48
#define LEVEL_Y_MAX         48
#define TILESET_MAX         9
#define TILES_ID_MAX        75


//EDITOR STRUCT
typedef struct TILE 
{
	int type;
	int tileset;
	int content;
	int doorFlag1;
	int doorFlag2;
	int doorFlag3;
	int doorFlag4;
	int doorFlag5;
	int propFlag1;
	int propFlag2;
	int propFlag3;
	int propFlag4;
	int propFlag5;
	int bonusFlag1;
	int bonusFlag2;
	int switchID;
	int triggerID;
	int useSwitch;
	int useTrigger;
	int rotation;
} TILE;


//GRID CELLS : IDS AND TILE SETTINGS
TILE tiles[LEVEL_X_MAX][LEVEL_Y_MAX]; //GROUND LAYER
TILE tilesB[LEVEL_X_MAX][LEVEL_Y_MAX];//OBJECT LAYER
TILE tilesC[LEVEL_X_MAX][LEVEL_Y_MAX];//OVER LAYER


//EDITOR CONTENT CREATION DATA
TILE nxsCmData[600];


//EDITOR CONTENT CREATION DATA : Function Names
TEXT* nxs_actions = {strings=600;}


//EDITOR CONTENT CREATION DATA :File Names
TEXT* nxs_files = {strings=600;}


//EDITOR CONTENT CREATION DATA : Texture Names
TEXT* nxs_skins = {strings=600;}


//LEVEL SETTINGS : Main Menu
STRING* set_skybox_name = "sky_blue.png";
STRING* set_audio_name = "level_1.ogg";
STRING* set_floor_name = "floor.tga";
STRING* set_ceiling_name = "ceiling.tga";


//LEVEL SETTINGS FOG-TIME-WEATHER : Settings Menu
var settings_val_near = 128;
var settings_val_far = 1024;
var settings_val_min = 10;
var settings_val_sec = 0;
var settings_weather = 0;


//DEFAULT HANDLE FOR SAVE/LOAD FUNCTIONS
var default_handle;


//GLOBAL POINTER TO ALL TILES AND PANELS
PANEL* over_pan_id = {bmap = cell_empty; flags=UNTOUCHABLE;}


//EDITOR MODE
int editor_mode = 0;


//READS/WRITES INTERNAL EXTENSION TYPES FOR LEVEL AND CHAPTER FILES
// .nxs for levels
// .xch for chapters
STRING* extension_type = " ";


//DETECT STARTUP AND EDITOR ACTIVITY
int editor_startup = false;
int content_pan_active = false;
int level_active = false;
int ch_editor_active = false;
int mod_pan_active = false;
int load_lv_from_file = false;
int resetting_the_lv = false;


//IDENTIFIES TILESET ID AND TILE ID
int tileset_type = 1;
int build_type = 1;


//2D CAMERA PAN SPEED (Grid position boundaries may become incorrect if changed)
int pan_speed = 16;


//Toggle Layers
//0=Ground Layer
//1=Object Layer
//2=Over Layer
int Set_toggle_layers = 0;


//GROUND LAYER : Tile Panels and window spritesheet positions
PANEL* pan_arrayA[LEVEL_X_MAX][LEVEL_Y_MAX];
var pan_arrayA_wx[LEVEL_X_MAX][LEVEL_Y_MAX];
var pan_arrayA_wy[LEVEL_X_MAX][LEVEL_Y_MAX];


//OBJECT LAYER : Tile Panels and window spritesheet positions
PANEL* pan_arrayB[LEVEL_X_MAX][LEVEL_Y_MAX];
var pan_arrayB_wx[LEVEL_X_MAX][LEVEL_Y_MAX];
var pan_arrayB_wy[LEVEL_X_MAX][LEVEL_Y_MAX];


//OVER LAYER : Tile Panels and window spritesheet positions
PANEL* pan_arrayC[LEVEL_X_MAX][LEVEL_Y_MAX];
var pan_arrayC_wx[LEVEL_X_MAX][LEVEL_Y_MAX];
var pan_arrayC_wy[LEVEL_X_MAX][LEVEL_Y_MAX];


//EDITOR SIDE MENU : TILESET BUTTONS AND TILE IDS
PANEL* tileset_A_buttons[5][15];
int tileset_A_functions[5][15];


//USED BY VARIOUS FUNCTIONS TO IDENTIFY AND EDIT SELECTED TILES
PANEL* cm_identify_tile;
int tempXY[2];
int tempTYPE_cm = 0;
var cm_tileset_id = 0;
var cm_tile_id = 0;


//USED BY THE POPUP MENU TO IDENTIFY TILES AND TO EDIT SWITCH/TRIGGER IDS
var popup_swt_id = 0;
var popup_tri_id = 0;
int overpanPos[2];


//FONTS
FONT* small_font = "Arial#12";
FONT* small_fontB = "Arial#12b";
FONT* small_fontC = "Arial#14b";
FONT* small_fontD = "Arial#18b";
FONT* bmap_font = "unispace.png";


//INCLUDES : Headers
#include "textbox.h"
#include "core.h"
#include "cm_control.h"
#include "edit_data.h"
#include "ch_menu.h"


//INCLUDES : Scripts
#include "msg_manager.c"
#include "core.c"
#include "cm_control.c"
#include "edit_data.c"
#include "ch_menu.c"
#include "gen_pointers.c"