#ifndef _GUI_H_
#define _GUI_H_

// layers
#define GUI_PLAYER_INFO_LAYER 2
#define GUI_PLAYER_MESSAGE_LAYER 2
#define GUI_PLAYER_HISTORY_LAYER 2
#define GUI_PLAYER_PICKUP_LAYER 3
#define GUI_LEVEL_INFO_BACKGROUND_LAYER 4
#define GUI_LEVEL_INFO_LAYER 5

// create game font
void create_fonts();

// show/hide in game gui
void game_gui_show(var show);

// initialize gui
void gui_init();

// reset gui
void gui_reset();

// update whole game gui
void update_gui();

#endif