#ifndef _AI_MOVEMENT_H_
#define _AI_MOVEMENT_H_

// function to set movement for the given npc
void npc_set_movement(ENTITY *ent, NPC *npc, var forward_, var backward_, var left_, var right_, var run_);

// function to stop all npc's movement
void npc_stop_movement(ENTITY *ent, NPC *npc);

// function to handle all npc's movement
void npc_movement(ENTITY *ent, NPC *npc);

#endif