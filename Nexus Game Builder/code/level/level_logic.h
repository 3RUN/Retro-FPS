#ifndef _LEVEL_LOGIC_H_
#define _LEVEL_LOGIC_H_

// initialize all levels
void init_levels();

// set level settings (such as fog, clipping etc)
void set_level_settings();

// reset some global level variables
void level_reset();

// restart current level
void level_restart();

// load level with the given id
void level_load(var num);

#endif