/*#########################################################################################################################################################
NEXUS A8 : GAME BUILDER :: By Brian Pressley (Evo) (Evoeon) :::: NEXUS GENERATION DATA :: Lite-C :: 3DGamestudio A8
#########################################################################################################################################################*/


//Nexus 3D Generation Settings for "OldSchool FPS Project".


//NEXUS : MAX GRID CELLS
#define LEVEL_X_MAX         48
#define LEVEL_Y_MAX         48

FONT* ackfont = "ackfont.tga";
FONT* ackfont_sm = "ackfont_sm.png";

//NEXUS : GENERATION STRUCT
typedef struct NXSGEN 
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
} NXSGEN;


//NEXUS : COMPLETE DATA LIST FOR LEVEL GENERATION
NXSGEN tiles[LEVEL_X_MAX][LEVEL_Y_MAX];
NXSGEN tilesB[LEVEL_X_MAX][LEVEL_Y_MAX];
NXSGEN tilesC[LEVEL_X_MAX][LEVEL_Y_MAX];
NXSGEN nxsCmData[600];
TEXT* nxs_actions = {strings=600;}
TEXT* nxs_files = {strings=600;}
TEXT* nxs_skins = {strings=600;}
STRING* nxs_set_skybox_name = "sky_clearday+6.tga";
STRING* nxs_set_audio_name = "level_1.ogg";
STRING* nxs_set_floor_name = "floor.tga";
STRING* nxs_set_ceiling_name = "ceiling.tga";
int nxs_settings_val_near = 0;
int nxs_settings_val_far = 0;
int nxs_settings_val_min = 0;
int nxs_settings_val_sec = 0;
int nxs_settings_weather = 0;


//NEXUS CHAPTER FILE NAME TO BE LOADED
STRING* nxs_game_content = " ";
STRING* nxs_game_chapter = " ";


//CHAPTER EDITOR USER MESSAGES - TEXTBOX STRINGS
STRING* nxs_ch_message_title = " ";
STRING* nxs_ch_message_start = " ";
STRING* nxs_ch_message_final = " ";


//CHAPTER EDITOR LEVEL LINK NAMES
STRING* nxs_set_level_link_1 = " ";
STRING* nxs_set_level_link_2 = " ";
STRING* nxs_set_level_link_3 = " ";
STRING* nxs_set_level_link_4 = " ";
STRING* nxs_set_level_link_5 = " ";
STRING* nxs_set_level_link_6 = " ";
STRING* nxs_set_level_link_7 = " ";
STRING* nxs_set_level_link_8 = " ";
STRING* nxs_set_level_link_9 = " ";
STRING* nxs_set_level_link_10 = " ";


//NEXUS : DEFAULT HANDLE FOR LOAD FUNCTIONS
var default_handle;
var dataHandle;
int nxs_extension_type;


//NEXUS : GENERATION INIT
int nxsGen_init_begin = false;
int nxsGen_complete = false;
STRING* nxstemp_str = " ";
var nxstempID = 0;
var nxs_set_lv_counter = 0;
TEXT* nxs_tex_strings = {strings=600;}
TEXT* nxs_tex_stringsB = {strings=600;}
TEXT* nxs_tex_stringsC = {strings=600;}
int nxs_remove_all = false;


//NEXUS : GENERATION FUNCTIONS
void nxs_load_level_settings();
void nxs_load_chapter();
void nxs_load_editor_cm_data();
void nxs_generation_init();
void nxs_calculate_content();
void nxs_generation_build();
action fps_wall_action();
action fps_floor_action();
action fps_ceiling_action();


//CREATE FPS FONT
FONT* nxs_title_msg_font = "Arial#24b";
FONT* nxs_msg_font = "Arial#18b";


//USED BY THE GENERATION CODE
//ENTITY* cm_identify_content;
float* action_control[600];

int nxs_layer = 1;
int cm_XY[2];

int cm_id = 0;
int cm_id_B = 0;
int cm_id_C = 0;

int cm_tileset_id = 0;
int cm_tile_id = 0;

int cm_tileset_id_B = 0;
int cm_tile_id_B = 0;

int cm_tileset_id_C = 0;
int cm_tile_id_C = 0;

float* merged_acts[74];
float* merged_actsB[74];
float* merged_actsC[74];

BMAP* nxs_load_screen = "loading.png";
PANEL* nxs_loading_pan = {pos_x=0; pos_y=0; bmap=nxs_load_screen; layer=1000;}


//PANEL FOR TEXTBOX
PANEL *panTextbox_msg = {
	pos_x = 40;
	pos_y = 300;
	size_x = 44;
	size_y = 32;
	blue = 255;
	green = 255;
	red = 255;
	layer = 1001;
	flags = LIGHT;
}


//DEFINE TEXTBOX
var ch_textbox_msg() {
	TEXTBOX_CONFIG _config;
	_config.posX = 0;
	_config.posY = 0;
	_config.sizeX = 59;
	_config.sizeY = 9;
	_config.fontScale = 0.5;
	_config.paddingX = 0;
	_config.paddingY = 0;
	_config.borderSize = 0;
	_config.backgroundColor.red = 0;
	_config.backgroundColor.green = 0;
	_config.backgroundColor.blue = 0;
	_config.textColor.red = 255;
	_config.textColor.green = 255;
	_config.textColor.blue = 255;
	_config.selectColor.red = 0;
	_config.selectColor.green = 0;
	_config.selectColor.blue = 0;
	_config.font = ackfont;
	_config.string = nxs_ch_message_start;
	_config.flags = TEXTBOX_REMOVE_STRING | TEXTBOX_REMOVE_FONT;
	return pan_textbox_create (panTextbox_msg, &_config);
}