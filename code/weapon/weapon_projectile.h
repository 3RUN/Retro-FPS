#ifndef _WEAPON_PROJECTILE_H_
#define _WEAPON_PROJECTILE_H_

// projectiles color
#define COLOR_PROJECTILE vector(0, 80, 255)

// melee distance by default
#define WPN_MELEE_DISTANCE 32

// skills used by projectiles (and barrels)
#define WPN_ORIGIN_X skill1
#define WPN_ORIGIN_Y skill2
#define WPN_ORIGIN_Z skill3
#define WPN_DIR_X skill4
#define WPN_DIR_Y skill5
#define WPN_DIR_Z skill6
#define WPN_VEL_X skill7
#define WPN_VEL_Y skill8
#define WPN_VEL_Z skill9
#define WPN_OWNER_GROUP skill10

// projectiles states
#define WPN_PROJ_FLY 0
#define WPN_PROJ_DELETE 1

// melee attack func
void melee_func();

// create melee attack trace
void melee_create(VECTOR *pos, VECTOR *angle, var type_, var group_, var damage_);

// update melee attack
void melee_update(ENTITY *ent);

// create visual projectile sprite for the given entity
void projectile_create_sprite(ENTITY *ent, var size_);

// bullet function
void bullet_func();

// create bullets
void bullet_create(VECTOR *pos, VECTOR *angle, var type_, var group_, var damage_, var speed_, var accuracy_, var size_);

// function to update given bullet
void bullet_update(ENTITY *ent);

// rocket's func
void rocket_func();

// create rocket
void rocket_create(VECTOR *pos, VECTOR *angle, var type_, var group_, var damage_, var speed_, var size_);

// function to update rockets
void rocket_update(ENTITY *ent);

// update all projectiles in this function
void projectiles_update();

#endif