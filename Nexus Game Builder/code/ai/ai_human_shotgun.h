#ifndef _AI_HUMAN_SHOTGUN_H_
#define _AI_HUMAN_SHOTGUN_H_

// human with shotgun parameters
var human_shotgun_health = 145;                  // default health
var human_shotgun_attack_range = 128;            // attack range within which player is detected
var human_shotgun_melee_range = WORLD_TILE_SIZE; // when within this range, npc starts melee attacking
var human_shotgun_movement_speed = 0.75;         // default movement speed
var human_shotgun_idle_def_time = 0.5;           // time spent in IDLE before going to walk
var human_shotgun_idle_def_random_time = 0.5;    // randomization added to above time
var human_shotgun_walk_def_time = 1.5;           // time spent in WALK before going to idle
var human_shotgun_walk_def_random_time = 0.5;    // randomization added to above time
var human_shotgun_fire_rate = 0.65;              // range weapon fire rate
var human_shotgun_melee_attack_rate = 0.5;       // attacking rate for melee attacks
var human_shotgun_attack_random_amount = 3;      // randomization for range attacks (1 + this value)
var human_shotgun_dodge_def_time = 1.75;         // tile spent in dodge state before chasing or attacking
var human_shotgun_dodge_def_random_time = 0.75;  // randomization to above value

#endif