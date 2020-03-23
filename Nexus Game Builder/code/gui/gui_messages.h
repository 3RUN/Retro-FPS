#ifndef _GUI_MESSAGES_H_
#define _GUI_MESSAGES_H_

// messages stuff
#define MESSAGE_ALPHA 100     // transparency of the text
#define MESSAGE_DELAY 3       // message visible delay (in seconds)
#define MESSAGE_FADE_SPEED 24 // fade in/out speed

// message font
FONT *message_font;

// message strings
STRING *message_str = "#100"; // message can have up to 100 letters

// game text stuff
var game_text_counter = 0;      // counts up each time, we receive a message
var game_text_fadeaway = false; // true - when game text has to fade away, otherwise - false

TEXT *game_info_txt =
{
    alpha = 100;
    flags = CENTER_X | CENTER_Y | TRANSLUCENT | OUTLINE | SHADOW;
}

// message init
void message_init();

// create message font
void message_font_create();

// show in game message
void show_message(STRING *str);

// hide current message
void hide_message();

// updates all logic related to the in game messages
void message_logic_update();

#endif