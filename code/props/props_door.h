#ifndef _PROPS_DOOR_H_
#define _PROPS_DOOR_H_

// NOTE - props_door_a and props_door_b differ only by sound effects

// RED_KEY || YELLOW_KEY || BLUE_KEY
// if any set, then door will require the key with the set color to be opened!

// USE_SWITCH
// if set, door can be triggered by switch (with the same ID)

// USE_TRIGGER
// if set, door can be triggered by trigger zone (with the same ID)

// play door's sounds on open/close
void door_snd(ENTITY *ent, var is_shut);

// function to update given door
void door_update(ENTITY *ent);

// check if player has needed key
var door_player_has_key();

// door's can't open sound effect
void door_no_use_snd(ENTITY *ent);

// event function for the door
void door_event_function();

#endif