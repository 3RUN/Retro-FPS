#ifndef _CCT_MOVEMENT_H_
#define _CCT_MOVEMENT_H_

// update all cct's movement here
void cct_update_movement(ENTITY *ent, CCT *cct);

// set input from cct
void cct_set_movement(ENTITY *ent, CCT *cct);

// stop all cct's movement
void cct_stop_movement(ENTITY *ent, CCT *cct);

#endif