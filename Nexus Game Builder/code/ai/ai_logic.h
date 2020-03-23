#ifndef _AI_LOGIC_H_
#define _AI_LOGIC_H_

// we need to debug obstacle avoice sensors?
//#define AI_SHOW_SENSORS

// detect near by enemies
void npc_detect_enemies(ENTITY *ent, NPC *npc);

// alert other npcs near by
void npc_alert_friends(ENTITY *ent, NPC *npc);

// checks if you entity is visible or not
// this function is called from event function only!
var npc_is_you_visible(ENTITY *my_ent, NPC *npc, ENTITY *you_ent);

// check if npc can see it's target
var npc_is_target_visible(ENTITY *ent, NPC *npc);

// simple obstacle avoidance
void npc_obstacle_avoidance(ENTITY *ent, NPC *npc);

// rotate npc to the given target
void npc_rotate_to(ENTITY *ent, NPC *npc, VECTOR *pos);

// rotate to something using obstacle avoidance
void npc_rotate_to_with_avoidance(ENTITY *ent, NPC *npc, VECTOR *pos);

// detect walls on explosions
void npc_check_walls(ENTITY *ent, VECTOR *from, VECTOR *to, var dmg);

// event function for all npcs
void npc_event_function();

#endif