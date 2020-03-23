#ifndef _EXPLOSION_FX_H_
#define _EXPLOSION_FX_H_

// explosion stuff
var explo_snd_volume = 512;   // volume for explosion sound effect
var explo_default_range = 64; // default range for the explosion damage !

// explosion scan
void explosion_scan();

// explosion from the player
void explosion_from_player_scan();

// explosion from the enemies
void explosion_from_npc_scan();

// explosion from the props
void explosion_from_props_scan();

// animated explosion sprite on floor (f.e. for barrels)
void explosion_on_floor_sprite();

// animated explosion sprite in the air (f.e. for rocket launcher)
void explosion_in_air_sprite();

// explosion sound effect
// only 4 explosion snds at the time !
void explosion_snd();

// create explosion at the given position
void explosion_create(VECTOR *pos, var is_on_ground, var type_);

#endif