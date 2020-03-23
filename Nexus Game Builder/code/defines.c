
// delay functions
void delay(var time)
{
    if (time == 0)
    {
        time = 1;
    }
    var counter = abs(time);
    while (counter > 0)
    {
        if (level_is_loaded == false)
        {
            break;
        }
        counter -= time_frame / 16;
        wait(1);
    }
}

void ent_delay(ENTITY *ent, var time)
{
    if (!ent)
    {
        error("Can't run delay function, entity doesn't exist!");
        return;
    }
    if (time == 0)
    {
        time = 1;
    }
    var counter = abs(time);
    while (ent)
    {
        if (level_is_loaded == false)
        {
            break;
        }
        counter -= time_frame / 16;
        if (counter <= 0)
        {
            break;
        }
        wait(1);
    }
}

// check if entity is alive
var ent_is_alive(ENTITY *ent)
{
    if (!ent)
    {
        return false;
    }

    if (ent->OBJ_HEALTH >= 1)
    {
        return true;
    }

    return false;
}

// safe remove entity (at the end of the frame)
void ent_delete(ENTITY *ent)
{
    if (!ent)
    {
        error("Can't delete entity, it doesn't exist!");
        return;
    }

    ent->OBJ_DELETE = true;
}

// alternative for c_trace
var ent_trace(ENTITY *ent, VECTOR *from, VECTOR *to, var mode)
{
    if (!ent)
    {
        error("Can't perform c_trace.. My entity doesn't exist!");
        return -1;
    }
    my = ent;
    var distance = c_trace(from, to, mode);
    my = NULL;
    return distance;
}

// alternative for c_scan
var ent_scan(ENTITY *ent, VECTOR *pos, ANGLE *ang, VECTOR *sector, var mode)
{
    if (!ent)
    {
        error("Can't perform c_scan.. My entity doesn't exist!");
        return -1;
    }
    my = ent;
    var distance = c_scan(pos, ang, sector, mode);
    my = NULL;
    return distance;
}

// rotate entity towards the camera
void ent_rotate_to_camera(ENTITY *ent)
{
    if (!ent)
    {
        error("Can't rotate entity to camera, it doesn't exist!");
        return;
    }

    VECTOR temp_vec;
    vec_set(&temp_vec, &camera->x);
    vec_sub(&temp_vec, &ent->x);
    vec_to_angle(&ent->pan, &temp_vec);
    ent->tilt = 0;
    ent->roll = 0;
}

// place entity on the ground
// this function uses c_trace instead of ent_trace
// since it's called in action functions where my already exists !
void ent_place_on_ground(ENTITY *ent)
{
    if (!ent)
    {
        error("Can't place entity on the ground! It doesn't exist..");
        return;
    }

    c_trace(&ent->x, vector(ent->x, ent->y, ent->z - 512), TRACE_FLAGS | IGNORE_MODELS);
    if (HIT_TARGET)
    {
        ent->z = hit->z + ent->max_z;
    }
}

// attach entity on near by wall
void ent_attach_to_near_wall(ENTITY *ent)
{	
    VECTOR temp_vec;
    vec_fill(&temp_vec, 0);

    // we first trace towards the PAN
    vec_set(&temp_vec, vector(WORLD_TILE_SIZE, 0, 0));
    vec_rotate(&temp_vec, vector(ent->pan, 0, 0));
    vec_add(&temp_vec, &ent->x);

    c_ignore(SWITCH_ITEM_GROUP, PROJECTILE_GROUP, PLAYER_GROUP, NPC_GROUP, SHOOT_THROUGH_GROUP, OBSTACLE_GROUP, 0);
    c_trace(&ent->x, &temp_vec, TRACE_FLAGS);
    if (HIT_TARGET)
    {
        VECTOR offset;
        vec_set(&offset, vector(0.05, 0, 0)); // 0.05 away from the surface
        vec_to_angle(&temp_vec, &normal);
        vec_rotate(&offset, &temp_vec);
        vec_add(&offset, &hit->x);
        vec_set(&ent->x, &offset);
        ent->pan = temp_vec.x;
        return;
    }

    // if tracing towards PAN doesn't help..
    // we trace around this entity and find surface to place it on !
    var i = 0;
    var rot = ent->pan;
    for (i = 0; i < 4; i++)
    {
        vec_set(&temp_vec, vector(WORLD_TILE_SIZE, 0, 0));
        vec_rotate(&temp_vec, vector(rot + 90 * i, 0, 0));
        vec_add(&temp_vec, &ent->x);
        
        c_ignore(SWITCH_ITEM_GROUP, PROJECTILE_GROUP, PLAYER_GROUP, NPC_GROUP, SHOOT_THROUGH_GROUP, OBSTACLE_GROUP, 0);
        c_trace(&ent->x, &temp_vec, TRACE_FLAGS);
        if (HIT_TARGET)
        {
            VECTOR offset;
            vec_set(&offset, vector(0.05, 0, 0)); // 0.05 away from the surface
            vec_to_angle(&temp_vec, &normal);
            vec_rotate(&offset, &temp_vec);
            vec_add(&offset, &hit->x);
            vec_set(&ent->x, &offset);
            ent->pan = temp_vec.x;
            break;
        }
    }
}