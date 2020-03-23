#ifndef _LEVEL_H_
#define _LEVEL_H_

// level loading logic
var level_id = 0;            // id for currently loding/loaded level
var level_is_loaded = false; // true - when level was loaded, otherwise - false
var level_secrets_found = 0;    // +1 with each new found secret zone (per level)
var level_secrets_total = 0;    // +1 with each created secret zone (per level)
var level_gold_collected = 0;   // amount of collected gold per level
var level_gold_total = 0;       // calculates ammount of all gold on the map
var level_enemies_killed = 0;   // amount of killed enemies
var level_enemies_total = 0;    // amount of enemies per level

// level timer stuff
var level_milli_seconds = 0; // milliseconds since level was loaded
var level_seconds = 0;       // seconds since level was loaded
var level_minutes = 0;       // minutes since level was loaded

// level music
var music_handle = 0;  // used for storing music stream
var music_volume = 35; // volume for level's music

typedef struct LEVEL
{
    char map_name[128];
    char music[128];

    var fog_start;
    var fog_end;
    var minutes;
    var seconds;
} LEVEL;

// list of levels
LEVEL map[MAX_LEVELS];

// setup parameters for the level with the given id
void level_setup(var id_, STRING *map_name_, STRING *music_, var fog_start_, var fog_end_, var score_m, var score_s);

#endif