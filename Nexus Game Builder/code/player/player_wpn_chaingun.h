#ifndef _PLAYER_WPN_CHAINGUN_H_
#define _PLAYER_WPN_CHAINGUN_H_

// initialize all chaingun parameters
void player_chaingun_init(PLAYER *hero, var col);

// chaingun shoot function
void player_chaingun_shoot(ENTITY *ent, PLAYER *hero);

#endif