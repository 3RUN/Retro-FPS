#ifndef _PROPS_SECRET_H_
#define _PROPS_SECRET_H_

// This header handles everything related to secret rooms
// Secret walls and zones can be triggered only ONCE !

// USE_SWITCH
// if set, door can be triggered by switch (with the same ID)

// USE_TRIGGER
// if set, door can be triggered by trigger zone (with the same ID)

// update secret wall
void secret_wall_update(ENTITY *ent);

// event function for secret wall
void secret_wall_event_function();

// event function for secret zone
void secret_zone_event_function();

// simple secret zone snd/message trigger
void props_secret_zone();

#endif