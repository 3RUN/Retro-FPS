#ifndef _AI_HUMAN_PISTOL_H_
#define _AI_HUMAN_PISTOL_H_

// human with pistol parameters
var human_pistol_health = 100;                  // default health
var human_pistol_attack_range = 512;            // attack range within which player is detected
var human_pistol_melee_range = WORLD_TILE_SIZE; // when within this range, npc starts melee attacking
var human_pistol_movement_speed = 1;            // default movement speed
var human_pistol_idle_def_time = 0.5;           // time spent in IDLE before going to walk
var human_pistol_idle_def_random_time = 0.5;    // randomization added to above time
var human_pistol_walk_def_time = 1.5;           // time spent in WALK before going to idle
var human_pistol_walk_def_random_time = 0.5;    // randomization added to above time
var human_pistol_fire_rate = 0.25;              // range weapon fire rate
var human_pistol_melee_attack_rate = 0.5;       // attacking rate for melee attacks
var human_pistol_attack_random_amount = 5;      // randomization for range attacks (1 + this value)
var human_pistol_dodge_def_time = 1.5;          // tile spent in dodge state before chasing or attacking
var human_pistol_dodge_def_random_time = 0.5;   // randomization to above value

#endif