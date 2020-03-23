#ifndef _PLAYER_BEHAVIOUR_H_
#define _PLAYER_BEHAVIOUR_H_

// initialize all player parameters
void player_init(PLAYER *hero);

// function to update all player's logic
void player_update();

// functon to handle player's interaction trace
void player_interaction(ENTITY *ent, PLAYER *hero);

// player logic function
void player_update_logic(ENTITY *ent);

// toggle auto run mode on and off
void player_toggle_run();

// player in pain effect (sound + gui)
void player_in_pain(ENTITY *ent);

// check for walls
void player_check_walls(ENTITY *ent, VECTOR *from, VECTOR *to, var dmg);

// event function for player
void player_event_function();

#endif