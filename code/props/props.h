#ifndef _PROPS_H_
#define _PROPS_H_

// skills used by all props
#define ID skill1
#define PROPS_OFFSET_X_ skill2
#define PROPS_OFFSET_Y_ skill3
#define PROPS_OFFSET_Z_ skill4

#define USE_SWITCH FLAG4
#define USE_TRIGGER FLAG5
#define RED_KEY FLAG6
#define YELLOW_KEY FLAG7
#define BLUE_KEY FLAG8

// props states
#define PROPS_IDLE_STATE 0
#define PROPS_OPEN_STATE 1
#define PROPS_CLOSE_STATE 2
#define PROPS_DELAY_STATE 3
#define PROPS_DEAD_STATE 4

// sprite flags
#define ROTATE_TO_CAM FLAG3
#define IS_OBSTACLE FLAG4
#define SHOOT_THROUGH FLAG5
#define ATTACH_TO_WALL FLAG6

// door messages
STRING *opens_elsewhere_str = "This door opens elsewhere.";
STRING *requires_key_str = "This door requires a key.";

// secret messages
STRING *you_fond_a_secret_str = "You found a secret area!";

// barrel stuff
var barrel_health = 45;        // name speaks for itself
var barrel_explo_delay = 0.25; // delay before barrel explodes
var barrel_dng_fric = 0.75;    // friction for barrel's movement

// door's stuff
var door_snd_volume = 256; // volume for all door sound effects

// secret stuff xD
var secret_wall_snd_volume = 512; // volume for all secret wall related sound effects
var secret_found_snd_volume = 50; // volume for 'found secret' sound effect

// switch stuff
var switch_snd_volume = 256; // volume for all switch sound effect

// props main structure
typedef struct
{
    VECTOR diff;
    VECTOR origin;
    var movement_speed;
    var delay_time;
    var old_state;
} PROPS;

// register and initializes new props (f.e. doors, platforms, elevators)
// and save it's pointer into given entity's obj_struct skill
PROPS *register_props(ENTITY *ent);

// initialize all major variables for the given props
// this function called inside of register_props right after creating new props
void init_props(ENTITY *ent, PROPS *props);

// returns pointer of the props from given entity's obj_struct skill
PROPS *get_props(ENTITY *ent);

// removes props from the memory
// pointer is taken from given entity's obj_struct skill
void delete_props(ENTITY *ent);

// remove given props from the memory
void delete_props(PROPS *props);

#endif