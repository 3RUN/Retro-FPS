#ifndef _AI_STATE_MACHINE_H_
#define _AI_STATE_MACHINE_H_

// if we need to debug state machine
//#define DEBUG_NPC_STATE_MACHINE

// npc states
#define AI_IDLE_STATE 0
#define AI_WALK_STATE 1
#define AI_CHASE_STATE 2
#define AI_ATTACK_STATE 3
#define AI_DODGE_STATE 4
#define AI_RUN_FOR_MELEE 5
#define AI_MELEE_STATE 6
#define AI_PAIN_STATE 7
#define AI_DEATH_STATE 8

// npc stuff
var npc_pain_time = 0.25;  // this amount of time spent on playing pain animation (seconds)
var npc_remove_time = 999; // after this amount of time, npc get's removed (seconds)
var npc_snd_volume = 256;  // volume for npc effects

// go to the given state
void npc_go_to_state(ENTITY *ent, NPC *npc, var state_);

// debug state machine
void npc_state_machine_debug(ENTITY *ent, NPC *npc);

// function to update logic for given npc
void update_npc_logic(ENTITY *ent);

#endif