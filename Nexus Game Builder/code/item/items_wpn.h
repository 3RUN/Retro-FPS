#ifndef _ITEM_WPN_PICKUPS_H_
#define _ITEM_WPN_PICKUPS_H_

// pickup effect color
#define ITEM_WPN_COLOR vector(158, 82, 59)

// pickable weapon's stuff
var wpn_bullets_add_ammo = 25;  // default ammo addition when pistol is picked up
var wpn_bullets_max_ammo = 200; // max ammo for pistol
var wpn_shells_add_ammo = 25;   // default ammo addition when shotgun is picked up
var wpn_shells_max_ammo = 100;  // max ammo for shotgun
var wpn_rockets_add_ammo = 3;   // default ammo addition when rocket launcher is picked up
var wpn_rockets_max_ammo = 50;  // max ammo for rocket launcher
var wpn_pickup_snd_volume = 45; // pickup sfx volume

// weapon message strings
STRING *wpn_pistol_str = "Picked up a pistol.";
STRING *wpn_shotgun_str = "Picked up a shotgun.";
STRING *wpn_chaingun_str = "Picked up a chaingun.";
STRING *wpn_rocketl_str = "Picked up a rocket launcher.";

// add ammo to the given weapon
void wpn_add_ammo(var *am_typ, var am, var mx);

// weapon pickup event function
void wpn_event_function();

// init pickable weapon
void wpn_init(var num);

#endif