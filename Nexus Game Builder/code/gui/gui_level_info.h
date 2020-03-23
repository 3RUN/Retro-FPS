#ifndef _GUI_LEVEL_INFO_H_
#define _GUI_LEVEL_INFO_H_

// info font
FONT *info_title_font;
FONT *info_detail_font;
FONT *info_input_font;
FONT *info_restart_font;

// info element id's
#define INFO_TITLE 1
#define INFO_TIME 2
#define INFO_SECRET 3
#define INFO_GOLD 4
#define INFO_ENEMIES 5

#define INFO_INPUT_CONTINUE 1
#define INFO_INPUT_RESTART 2

#define INFO_INPUT_FADING_SPEED 8

// info colors
#define INFO_TITLE_COLOR vector(255, 255, 255)
#define INFO_TIME_COLOR vector(255, 255, 255)
#define INFO_COLLECTABLES_COLOR vector(61, 91, 32)
#define INFO_ENEMIES_COLOR vector(28, 4, 246)
#define INFO_INPUT_CONTINUE_COLOR vector(255, 255, 255)
#define INFO_INPUT_RESTART_COLOR vector(129, 128, 154)

// strings used for info
STRING *info_time_str = "";
STRING *info_secret_str = "";
STRING *info_treasure_str = "";
STRING *info_enemies_str = "";

// string messages
STRING *level_complete_str = "Level\ncomplete!";
STRING *press_to_continue_str = "Press ENTER for next level!";
STRING *press_to_restart_str = "or R to restart...";

// info stuff
var info_title_timer = 0;                // timer for viewing elements, after title was shown
var info_title_def_time = 1;             // wait 1 second, after showing title, before showing other info elements
var info_allow_showing_elements = false; // true - if we can show other info elements, otherwise - false
var info_timer = 0;                      // timer to view each level info step by step
var info_def_time = 0.25;                // time between showing each level info element
var info_counter = INFO_TITLE;           // counter, starts with title (points for each element to be displayed)
var info_snd_volume = 65;                // volume for info show effect

PANEL *level_info_pan =
{
    alpha = 100;
    flags = OUTLINE | CENTER_X | CENTER_Y;
}

PANEL *level_info_input_pan =
{
    alpha = 0;
    flags = OUTLINE | CENTER_X | CENTER_Y | TRANSLUCENT;
}

PANEL *level_info_background_pan = 
{
    flags = LIGHT | TRANSLUCENT;
}

// init level info
void gui_level_info_init();

// create info elements
void gui_level_info_create(var num);

// reset all info elements
void gui_level_info_reset();

// create level info font
void gui_level_info_font_create();

// show level info
void gui_level_info_show(var show);

// update level info gui
void gui_level_info_update();

#endif