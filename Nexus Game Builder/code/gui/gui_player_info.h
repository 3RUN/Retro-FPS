#ifndef _GUI_PLAYER_INFO_H_
#define _GUI_PLAYER_INFO_H_

// message font
FONT *player_font;

PANEL *health_pan =
{
    alpha = 100;
    flags = OUTLINE;
}

PANEL *ammo_pan =
{
    alpha = 100;
    flags = OUTLINE | ARIGHT;
}

// player's info init function
void gui_player_info_init();

// create player's font
void gui_player_font_create();

// update player's info
void gui_player_info_update();

// show/hide info visibility
void gui_player_info_show(var show);

#endif