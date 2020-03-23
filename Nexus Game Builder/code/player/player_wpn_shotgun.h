#ifndef _PLAYER_WPN_SHOTGUN_H_
#define _PLAYER_WPN_SHOTGUN_H_

// initialize all shotgun parameters
void player_shotgun_init(PLAYER *hero, var col);

// shotgun shoot function
void player_shotgun_shoot(ENTITY *ent, PLAYER *hero);

#endif