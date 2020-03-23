#ifndef _AI_HUMAN_CHAINGUN_H_
#define _AI_HUMAN_CHAINGUN_H_

// human with chaingun parameters
var human_chaingun_health = 200;                  // default health
var human_chaingun_attack_range = 512;            // attack range within which player is detected
var human_chaingun_melee_range = WORLD_TILE_SIZE; // when within this range, npc starts melee attacking
var human_chaingun_movement_speed = 0.5;          // default movement speed
var human_chaingun_idle_def_time = 0.5;           // time spent in IDLE before going to walk
var human_chaingun_idle_def_random_time = 0.5;    // randomization added to above time
var human_chaingun_walk_def_time = 1.5;           // time spent in WALK before going to idle
var human_chaingun_walk_def_random_time = 0.5;    // randomization added to above time
var human_chaingun_fire_rate = 0.15;              // range weapon fire rate
var human_chaingun_melee_attack_rate = 0.5;       // attacking rate for melee attacks
var human_chaingun_attack_random_amount = 25;     // randomization for range attacks (1 + this value)
var human_chaingun_dodge_def_time = 1.5;          // tile spent in dodge state before chasing or attacking
var human_chaingun_dodge_def_random_time = 0.5;   // randomization to above value

#endif