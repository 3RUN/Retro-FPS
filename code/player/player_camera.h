#ifndef _PLAYER_CAMERA_H_
#define _PLAYER_CAMERA_H_

// get input from player
void camera_get_input(PLAYER *hero);

// animate camera
void camera_bobbing(PLAYER *hero);

// reset bobbing effect
void camera_bobbing_reset(PLAYER *hero);

// handle recoil effect
void camera_recoil(ENTITY *ent, PLAYER *hero);

// handle camera shaking effect (used for explosions and moving on platforms/elevators)
void camera_explosion_shake(PLAYER *hero);

// handle camera damage effect
void camera_add_damage_effect(ENTITY *ent, PLAYER *hero, VECTOR *from);

// update camera damage effect
void camera_update_damage_effect(PLAYER *hero);

// update everything related to the camera
void camera_update(ENTITY *ent, PLAYER *hero);

#endif