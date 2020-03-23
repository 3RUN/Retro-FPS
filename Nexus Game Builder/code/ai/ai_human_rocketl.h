#ifndef _AI_HUMAN_ROCKETL_H_
#define _AI_HUMAN_ROCKETL_H_

// human with rocketl parameters
var human_rocketl_health = 250;                  // default health
var human_rocketl_attack_range = 256;            // attack range within which player is detected
var human_rocketl_melee_range = WORLD_TILE_SIZE; // when within this range, npc starts melee attacking
var human_rocketl_movement_speed = 0.5;          // default movement speed
var human_rocketl_idle_def_time = 0.5;           // time spent in IDLE before going to walk
var human_rocketl_idle_def_random_time = 0.5;    // randomization added to above time
var human_rocketl_walk_def_time = 1.5;           // time spent in WALK before going to idle
var human_rocketl_walk_def_random_time = 0.5;    // randomization added to above time
var human_rocketl_fire_rate = 0.65;              // range weapon fire rate
var human_rocketl_melee_attack_rate = 0.5;       // attacking rate for melee attacks
var human_rocketl_attack_random_amount = 1;      // randomization for range attacks (1 + this value)
var human_rocketl_dodge_def_time = 1.75;         // tile spent in dodge state before chasing or attacking
var human_rocketl_dodge_def_random_time = 0.75;  // randomization to above value

#endif