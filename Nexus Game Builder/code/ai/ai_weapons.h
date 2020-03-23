#ifndef _AI_WEAPONS_H_
#define _AI_WEAPONS_H_

// weapons stuff
var npc_pistol_accuracy = 1;                            // accuracy for npc pistols (same as for player)
var npc_bullet_damage = player_bullet_damage;           // same as for player
var npc_bullet_speed = player_bullet_projectile_speed;  // same as for player
var npc_bullet_size = player_bullet_projectile_size;    // same as for player
var npc_shotgun_accuracy = 8;                           // accuracy for npc shotguns
var npc_shell_damage = player_shell_damage;             // same as for player
var npc_shell_speed = player_shell_projectile_speed;    // same as for player
var npc_shell_size = player_shell_projectile_size;      // same as for player
var npc_rocketl_accuracy = 1;                           // accuracu for npc rocket launchers (same as for player)
var npc_rocketl_speed = player_rocket_projectile_speed; // same as for player
var npc_rocketl_size = player_rocket_projectile_size;   // same as for player
var npc_melee_def_damage = 25;                          // defaut melee damage for npc (same as for player)
var weapon_npc_shoot_volume = 256;                      // shooting sound volume for all npcs

// create projectile
void npc_create_projectile(ENTITY *ent, NPC *npc);

// create melee attack
void npc_create_melee(ENTITY *ent, NPC *npc);

#endif