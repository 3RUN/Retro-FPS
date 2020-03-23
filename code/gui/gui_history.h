#ifndef _GUI_HISTORY_H_
#define _GUI_HISTORY_H_

#define MAX_GUI_HISTORY 5       // only 5 messages in history allowed
#define GUI_HISTORY_FADE_TIME 3 // time in seconds

FONT *gui_history_font;

// history message strings
STRING *gui_history_str[MAX_GUI_HISTORY];

// fading timer for each line
var gui_history_timer[MAX_GUI_HISTORY];

// texts for each line
TEXT *gui_history_txt[MAX_GUI_HISTORY];

// initialize all gui history related stuff
void gui_history_init();

// create history fonts
void gui_history_font_create();

// reset the history
void gui_history_reset();

// remove all strings and texts
void gui_history_remove_all();

// add text to the gui history
void gui_history_add_message(STRING *msg);

// update gui history
void gui_history_update();

#endif