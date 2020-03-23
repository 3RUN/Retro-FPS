#ifndef _DEFINES_H_
#define _DEFINES_H_

// max indexes
#define MAX_LEVELS 10
#define MAX_WEAPONS 5

// world Z position for all objects
#define WORLD_Z_POS 16
#define WORLD_TILE_SIZE 32

// fog and sky colors
#define COLOR_FOG vector(0, 0, 0)
#define COLOR_SKY vector(192, 128, 8)

// default trace/move flags
#define TRACE_FLAGS (IGNORE_ME | IGNORE_PASSABLE | IGNORE_PASSENTS | IGNORE_MAPS | IGNORE_SPRITES | IGNORE_CONTENT)
#define MOVE_FLAGS (IGNORE_ME | IGNORE_PASSABLE | IGNORE_PASSENTS | IGNORE_MAPS | IGNORE_SPRITES | IGNORE_CONTENT)

// collision push/group groups (used by c_ignore)
#define SWITCH_ITEM_GROUP 2
#define PROJECTILE_GROUP 3
#define PLAYER_GROUP 4
#define NPC_GROUP 5
#define SHOOT_THROUGH_GROUP 6
#define OBSTACLE_GROUP 7

// object structures
#define OBJ_STRUCT skill50

// different object types
#define OBJ_TYPE skill51
#define TYPE_NONE 0
#define TYPE_PLAYER 1
#define TYPE_PLAYER_WEAPON 2
#define TYPE_PLAYER_MELEE 3
#define TYPE_PLAYER_BULLET 4
#define TYPE_PLAYER_ROCKET 5
#define TYPE_PLAYER_EXPLOSION 6
#define TYPE_NPC 7
#define TYPE_NPC_SPRITE 8
#define TYPE_NPC_MELEE 9
#define TYPE_NPC_BULLET 10
#define TYPE_NPC_ROCKET 11
#define TYPE_NPC_EXPLOSION 12
#define TYPE_PROPS_BARREL 13
#define TYPE_PROPS_EXPLOSION 14
#define TYPE_PROPS_DOOR 15
#define TYPE_PROPS_LEVEL_END 16
#define TYPE_PROPS_SECRET 17
#define TYPE_PROPS_SECRET_ZOME 18
#define TYPE_PROPS_SWITCH 19
#define TYPE_PROPS_TRIGGER_ZONE 20
#define TYPE_PICKABLE_ITEM 21

// interaction indicator
#define OBJ_C_INDICATOR skill52
#define C_NONE 0
#define C_INTERACT 1
#define C_SHOOT 2

// death and pain types
#define OBJ_DEATH_TYPE skill53
#define OBJ_PAIN_TYPE skill54
#define TYPE_UNDEFINED 0
#define TYPE_SHOOT 1
#define TYPE_MELEE 2
#define TYPE_EXPLO 3
#define TYPE_SMASHED 4

// other object skills
#define OBJ_HEALTH skill60
#define OBJ_ALLOW_MOVE skill61
#define OBJ_SND_HANDLE skill62
#define OBJ_DELETE skill63
#define OBJ_STATE skill64
#define OBJ_TIMER skill65
#define OBJ_CHECK skill66
#define OBJ_TAKE_DAMAGE skill67
#define OBJ_EXPLO_RANGE skill68
#define OBJ_EXPLO_DAMAGE skill69

// bboxes for checks
var biggest_bbox_x_side = 8;  // consider this as a bixest bbox X size (8+8=16)
var biggest_bbox_y_side = 8;  // same as above, but for Y
var biggest_bbox_z_side = 16; // same as above, but for Z (16+16=32)

// prototypes
// delay functions
void delay(var time);
void ent_delay(ENTITY *ent, var time);

// check if entity is alive
var ent_is_alive(ENTITY *ent);

// safe remove entity (at the end of the frame)
void ent_delete(ENTITY *ent);

// alternative for c_trace
var ent_trace(ENTITY *ent, VECTOR *from, VECTOR *to, var mode);

// alternative for c_scan
var ent_scan(ENTITY *ent, VECTOR *pos, ANGLE *ang, VECTOR *sector, var mode);

// rotate entity towards the camera
void ent_rotate_to_camera(ENTITY *ent);

// place entity on the ground
// this function uses c_trace instead of ent_trace
// since it's called in action functions where my already exists !
void ent_place_on_ground(ENTITY *ent);

// attach entity on near by wall
void ent_attach_to_near_wall(ENTITY *ent);

#endif