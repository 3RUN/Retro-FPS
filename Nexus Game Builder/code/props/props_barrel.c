
// barrel's event function
void barrel_event_function()
{
    if (event_type == EVENT_SHOOT)
    {
        // take damage from projectiles
        if (you->OBJ_TYPE == TYPE_PLAYER_MELEE || you->OBJ_TYPE == TYPE_PLAYER_BULLET || you->OBJ_TYPE == TYPE_NPC_MELEE || you->OBJ_TYPE == TYPE_NPC_BULLET)
        {
            my->OBJ_HEALTH -= you->OBJ_TAKE_DAMAGE;
        }

        // if hit by rocket ?
        // explode right now !
        if (you->OBJ_TYPE == TYPE_PLAYER_ROCKET || you->OBJ_TYPE == TYPE_NPC_ROCKET)
        {
            my->OBJ_HEALTH = -999;
        }
    }

    if (event_type == EVENT_SCAN)
    {
        // ignore scans if we are already dead
        if (ent_is_alive(my) == false)
        {
            return;
        }

        // if scan from any type of explosions
        if (you->OBJ_TYPE == TYPE_PLAYER_EXPLOSION || you->OBJ_TYPE == TYPE_NPC_EXPLOSION || you->OBJ_TYPE == TYPE_PROPS_EXPLOSION)
        {
            // check for walls, push away from explosion etc
            props_check_walls(my, &you->x, &my->x, you->OBJ_EXPLO_DAMAGE);
        }
    }
}

// update barrels
void barrel_update(ENTITY *ent)
{
    // get props structure
    PROPS *props = get_props(ent);

    // reset absolute forces slowly (this is used to push player from explosions)
    props->origin.x -= (props->origin.x - 0) * time_step;
    props->origin.y -= (props->origin.y - 0) * time_step;
    props->origin.z = 0;

    accelerate(&props->diff.x, props->origin.x * time_step, barrel_dng_fric);
    accelerate(&props->diff.y, props->origin.y * time_step, barrel_dng_fric);

    // absolute distance
    move_friction = 0;
    c_ignore(SWITCH_ITEM_GROUP, PROJECTILE_GROUP, 0);
    c_move(ent, nullvector, &props->diff, MOVE_FLAGS | GLIDE);

    // update Z position
    ent->z = ent->PROPS_OFFSET_Z_;

    if (ent->parent)
    {
        vec_set(&ent->parent->x, &ent->x);
        ent->parent->z += 4;
        ent_rotate_to_camera(ent->parent);
    }

    // if dead ?
    // then count down till explosion
    if (ent_is_alive(ent) == false)
    {
        ent->OBJ_TIMER -= time_frame / 16;
    }

    if (ent->OBJ_TIMER <= 0)
    {
        // explosion effect here !
        explosion_create(&ent->x, true, ent->OBJ_TYPE);
        ent_delete(ent->parent);
        ent_delete(ent);
    }
}

// main barrels action
action props_barrel()
{
    PROPS *props = register_props(my);
    vec_fill(&props->origin, 0); // reset to zero

    // make bbox a big smaller
    vec_set(&my->scale_x, vector(0.35, 0.35, 0.75));
    c_setminmax(my);

    // correct our Z position
    // and place on ground !
    my->z = WORLD_Z_POS;
    ent_place_on_ground(my);
    my->PROPS_OFFSET_Z_ = my->z;
    my->min_z *= 0.95;

    set(my, POLYGON | INVISIBLE);

    my->group = OBSTACLE_GROUP;
    my->push = OBSTACLE_GROUP;

    my->OBJ_HEALTH = barrel_health;
    my->OBJ_TIMER = barrel_explo_delay; // 1/4 second delay before explosion
    my->OBJ_TYPE = TYPE_PROPS_BARREL;

    my->emask |= (ENABLE_SHOOT | ENABLE_SCAN);
    my->event = barrel_event_function;

    // create visual model
    my->parent = ent_create(props_decor_mdl, &my->x, NULL);
    props_visual_ent(my, my->parent, props_barrel_tga);
}