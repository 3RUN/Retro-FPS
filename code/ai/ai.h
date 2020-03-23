#ifndef _AI_H_
#define _AI_H_

// friendly fire
// projectiles ignore ENEMY_GROUP by default (can be changed if needed)
// so this won't allow npc to damage other teammates BUT
// this will allow npc to get killed by friendly rocket explosion etc
#define FRIENDLY_FIRE

// ai weapon types
#define AI_MELEE_WEAPON 0
#define AI_PISTOL_WEAPON 1
#define AI_SHOTGUN_WEAPON 2
#define AI_CHAINGUN_WEAPON 3
#define AI_ROCKETL_WEAPON 4

typedef struct NPC_ANIM
{
    var sprite_type;
    var anim_row;
    var anim_frame;
    var anim_attack;
} NPC_ANIM;

typedef struct NPC
{
    NPC_ANIM animator;
    CCT cct;

    // logic stuff
    ENTITY *target_ent;
    VECTOR target_pos;

    var scan_range;
    var dist_to_target;
    var is_triggered;

    VECTOR sensor_right;
    VECTOR sensor_left;
    VECTOR sensor_ahead;
    var sensor_distance;
    var sensor_width;
    var sensor_hit_right;
    var sensor_hit_left;
    var sensor_hit_ahead;
    var route_find;
    var route_timer;
    var route_def_time;

    var state_timer;
    var state_def_time;

    var attack_range;
    var attack_counter;
    var attack_amount;
    var melee_range;
    var melee_approach_range;
    var melee_damage;

    // parameters unique for each npc type
    var accuracy;
    var weapon_type;
    var fire_rate;
    var melee_attack_rate;
    var idle_def_time;
    var idle_def_random_time;
    var walk_def_time;
    var walk_def_random_time;
    var attack_def_random_amount;
    var dodge_def_time;
    var dodge_def_random_time;
} NPC;

// register and initializes new npc
// and save it's pointer into given entity's obj_struct skill
NPC *register_npc(ENTITY *ent);

// initialize all major variables for the given npc
// this function called inside of register_npc right after creating new npc
void init_npc(ENTITY *ent, NPC *npc);

// returns pointer of the npc from given entity's obj_struct skill
NPC *get_npc(ENTITY *ent);

// removes npc from the memory
// pointer is taken from given entity's obj_struct skill
void delete_npc(ENTITY *ent);

// remove given npc from the memory
void delete_npc(NPC *npc);

#endif