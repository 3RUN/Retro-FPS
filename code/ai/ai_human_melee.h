#ifndef _AI_HUMAN_MELEE_H_
#define _AI_HUMAN_MELEE_H_

// human with pistol parameters
var human_melee_health = 100;                      // default health
var human_melee_attack_range = WPN_MELEE_DISTANCE; // attack range within which player is detected
var human_melee_movement_speed = 3;                // default movement speed
var human_melee_idle_def_time = 0.5;               // time spent in IDLE before going to walk
var human_melee_idle_def_random_time = 0.5;        // randomization added to above time
var human_melee_walk_def_time = 1.5;               // time spent in WALK before going to idle
var human_melee_walk_def_random_time = 0.5;        // randomization added to above time
var human_melee_attack_rate = 0.25;                // attacking rate for melee attacks

#endif