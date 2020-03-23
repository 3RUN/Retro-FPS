#ifndef _PROPS_HELPER_H_
#define _PROPS_HELPER_H_

// barrel check for walls
void props_check_walls(ENTITY *ent, VECTOR *from, VECTOR *to, var dmg);

// init visual model for props
// ent - is the bbox model
// ghost - is the visual model, which will change it's skin
// bmap - bmap which will replace skin of ghost ent
void props_visual_ent(ENTITY *ent, ENTITY *ghost, BMAP *bmp);

// check if entity needs to be smashed or not (f.e. by door on close etc)
var props_vs_npc_check(ENTITY *prop, ENTITY *npc, var scale);

#endif