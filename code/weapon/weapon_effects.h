#ifndef _WEAPON_EFFECTS_H_
#define _WEAPON_EFFECTS_H_

// impact types
#define IMPCT_STATIC 0
#define IMPCT_ALIVE 1

// projectile stuff
var projectile_impact_snd_volume = 96; // volume for impact sound effect

// impact sounds
// MAX 4 sounds at the same time !
void projectie_impact_snd();

// impact animated sprite
void projectie_impact_sprite();

// function to handle impact effects
void projectile_impact_fx(var num, VECTOR *hit_vector, VECTOR *surf_angle);

// handle impact on different surfaces
void projectile_impact_function(ENTITY *ent);

#endif