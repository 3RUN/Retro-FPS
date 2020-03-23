
// update all cct's movement here
void cct_update_movement(ENTITY *ent, CCT *cct)
{
    // accelerate movement
    accelerate(&cct->speed.x, cct->input.x * time_step, cct_gnd_fric);
    accelerate(&cct->speed.y, cct->input.y * time_step, cct_gnd_fric);
    cct->speed.z = 0;

    move_friction = 0;
    c_ignore(PROJECTILE_GROUP, 0);
    cct->moving_distance = c_move(ent, nullvector, &cct->speed, MOVE_FLAGS | IGNORE_PUSH | GLIDE);

    if (cct->moving_distance > 0)
    {
        cct->moving_speed = cct->moving_distance / time_step;
        cct->is_moving = true;
    }
    else
    {
        cct->moving_speed = 0;
        cct->is_moving = false;
    }

    // reset absolute forces slowly (this is used to push cct from explosions)
    cct->abs_force.x -= (cct->abs_force.x - 0) * 0.5 * time_step;
    cct->abs_force.y -= (cct->abs_force.y - 0) * 0.5 * time_step;
    cct->abs_force.z = 0;

    accelerate(&cct->abs_dist.x, cct->abs_force.x * time_step, cct_gnd_fric);
    accelerate(&cct->abs_dist.y, cct->abs_force.y * time_step, cct_gnd_fric);

    // add pushing forces (from secret wall)
    if (vec_length(vector(cct->push_force.x, cct->push_force.y, 0)) > 0)
    {
        cct->abs_dist.x = cct->push_force.x;
        cct->abs_dist.y = cct->push_force.y;
        vec_fill(&cct->push_force, 0);
    }

    // absolute distance
    move_friction = 0;
    c_ignore(PROJECTILE_GROUP, 0);
    c_move(ent, nullvector, &cct->abs_dist, MOVE_FLAGS | IGNORE_PUSH | GLIDE);

    // correct our Z position
    ent->z = cct->fixed_z_pos;
}

// set input from cct
void cct_set_movement(ENTITY *ent, CCT *cct)
{
    // XY movement part starts here
    cct->input.x = cct->movement_speed * (cct->forward - cct->backward);
    cct->input.y = cct->movement_speed * (cct->strafe_left - cct->strafe_right);
    cct->input.z = 0;

    // don't allow to 'speed' cheat, while f.e. holding down forward and left movement keys
    if (vec_length(vector(cct->input.x, cct->input.y, 0)) > cct->movement_speed)
    {
        var len = sqrt(cct->input.x * cct->input.x + cct->input.y * cct->input.y);
        cct->input.x *= ((cct->movement_speed) / len);
        cct->input.y *= ((cct->movement_speed) / len);
    }

    // handle running and autorun
    if (cct->always_run == true)
    {
        if (cct->run == true)
        {
            cct->input.x *= cct->walk_speed_factor;
            cct->input.y *= cct->walk_speed_factor;
        }
        else
        {
            cct->input.x *= cct->run_speed_factor;
            cct->input.y *= cct->run_speed_factor;
        }
    }
    else
    {
        if (cct->run == true)
        {
            cct->input.x *= cct->run_speed_factor;
            cct->input.y *= cct->run_speed_factor;
        }
        else
        {
            cct->input.x *= cct->walk_speed_factor;
            cct->input.y *= cct->walk_speed_factor;
        }
    }

    // rotate input with camera pan
    vec_rotate(&cct->input, vector(cct->rotaton_pan, 0, 0));
}

// stop all cct's movement
void cct_stop_movement(ENTITY *ent, CCT *cct)
{
    vec_fill(&cct->input, 0);

    cct->run = 0;
    cct->forward = 0;
    cct->backward = 0;
    cct->strafe_left = 0;
    cct->strafe_right = 0;
}