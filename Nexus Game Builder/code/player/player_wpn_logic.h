#ifndef _PLAYER_WPN_LOGIC_H_
#define _PLAYER_WPN_LOGIC_H_

// function used for all weapon sprites
void player_weapon_fnc();

// morph weapon to the one that we've equiped
void player_weapon_morph(PLAYER *hero);

// animate equiped weapon
void player_animate_weapons(PLAYER *hero);

// switch to weapon by id
void player_switch_weapon_by_id(PLAYER *hero, var num);

// find better weapon
void player_weapon_find_better(PLAYER *hero, var num);

// save ammo and weapons at the beginning of the level
void player_weapons_save_at_level_start(PLAYER *hero);

// save ammo and weapons at the end of the level
void player_weapons_save_at_level_end(PLAYER *hero);

// get weapons from the previous level OR reset to default ones (from the level start)
void player_weapons_set_param(PLAYER *hero);

// setup basic weapon settings at start
void player_weapons_init(ENTITY *ent, PLAYER *hero);

// update weapon's pos/angle
void player_weapon_view_pos(PLAYER *hero);

// switch weapons
void player_switch_weapons(PLAYER *hero);

// main function to update all weapons
void player_weapons_update(ENTITY *ent, PLAYER *hero);

#endif