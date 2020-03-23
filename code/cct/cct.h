#ifndef _CCT_H_
#define _CCT_H_

// cct stuff
var cct_gnd_fric = 0.5;                            // ground friction for cct movement
var cct_interact_distance = WORLD_TILE_SIZE * 1.5; // cct interaction trace length

typedef struct CCT
{
    VECTOR input;
    VECTOR speed;

    var rotaton_pan;
    var movement_speed;
    var walk_speed_factor;
    var run_speed_factor;
    var always_run;
    var moving_distance;
    var moving_speed;
    var is_moving;
    var fixed_z_pos;

    VECTOR push_force;
    VECTOR abs_force;
    VECTOR abs_dist;

    // input keys
    var forward;
    var backward;
    var strafe_left;
    var strafe_right;
    var run;
} CCT;

// checks if given cct is inside of the given entity
// returns true if true, else if not
var is_cct_in_rect(ENTITY *cct, ENTITY *rect, var scale_);

#endif