#ifndef _AI_SPRITE_H_
#define _AI_SPRITE_H_

// row position on the ai skin
#define AI_ANIM_WALK 0
#define AI_ANIM_ATTACK 1
#define AI_ANIM_MELEE 1
#define AI_ANIM_PAIN 2
#define AI_ANIM_DEATH 3

// different sprite types (visuals)
#define AI_SPRITE_HUMAN_MELEE 0
#define AI_SPRITE_HUMAN_PISTOL 1
#define AI_SPRITE_HUMAN_SHOTGUN 2
#define AI_SPRITE_HUMAN_CHAINGUN 3
#define AI_SPRITE_HUMAN_ROCKETL 4

// create visual sprite for the given npc
void npc_create_visual_sprite(ENTITY *ent, NPC *npc);

// handle everything related to the visual sprite (animations, position etc)
void npc_update_visual_sprite(ENTITY *ent, NPC *npc);

#endif