
// melee attack func
void melee_func()
{
    set(my, PASSABLE | INVISIBLE);
    my->OBJ_TIMER = 16;
    my->group = PROJECTILE_GROUP;
    my->push = PROJECTILE_GROUP;
}

// create melee attack trace
void melee_create(VECTOR *pos, VECTOR *angle, var type_, var group_, var damage_)
{
    ENTITY *projectile_ent = ent_create(NULL, pos, melee_func);
    vec_set(&projectile_ent->WPN_ORIGIN_X, pos);
    vec_set(&projectile_ent->WPN_DIR_X, vector(WPN_MELEE_DISTANCE, 0, 0));
    vec_rotate(&projectile_ent->WPN_DIR_X, angle);
    vec_add(&projectile_ent->WPN_DIR_X, &projectile_ent->WPN_ORIGIN_X);
    projectile_ent->WPN_OWNER_GROUP = group_;
    projectile_ent->OBJ_TAKE_DAMAGE = damage_;
    projectile_ent->OBJ_TYPE = type_;
    projectile_ent = NULL;
}

// update melee attack
void melee_update(ENTITY *ent)
{
    c_ignore(SWITCH_ITEM_GROUP, PROJECTILE_GROUP, ent->WPN_OWNER_GROUP, SHOOT_THROUGH_GROUP, 0);
    ent_trace(ent, &ent->x, &ent->WPN_DIR_X, TRACE_FLAGS | ACTIVATE_SHOOT | USE_POLYGON);
    if (HIT_TARGET)
    {
        projectile_impact_function(you);
    }

    ent_delete(ent);
}

// create visual projectile sprite for the given entity
void projectile_create_sprite(ENTITY *ent, var size_)
{
    if (!ent)
    {
        error("There is no projectile to create bullet for!");
        return;
    }
    ent->parent = ent_create(projectile_tga, &ent->x, NULL);
    vec_fill(&ent->parent->scale_x, size_);
    set(ent->parent, PASSABLE | NOFILTER | UNLIT | LIGHT);
    vec_fill(&ent->parent->blue, 255);
    ent->parent->ambient = 100;
    ent->parent->material = mtl_z_write;
}

// bullet function
void bullet_func()
{
    set(my, PASSABLE | INVISIBLE);
    my->OBJ_STATE = WPN_PROJ_FLY;
    my->OBJ_TIMER = 16;
    my->group = PROJECTILE_GROUP;
    my->push = PROJECTILE_GROUP;
}

// create bullets
void bullet_create(VECTOR *pos, VECTOR *angle, var type_, var group_, var damage_, var speed_, var accuracy_, var size_)
{
    ENTITY *projectile_ent = ent_create(NULL, pos, bullet_func);
    vec_set(&projectile_ent->WPN_ORIGIN_X, pos);
    vec_set(&projectile_ent->WPN_DIR_X, vector(speed_, (random(accuracy_ * 2) - accuracy_), (random(accuracy_ * 2) - accuracy_)));
    vec_rotate(&projectile_ent->WPN_DIR_X, angle);
    projectile_ent->WPN_OWNER_GROUP = group_;
    projectile_ent->OBJ_TAKE_DAMAGE = damage_;
    projectile_ent->OBJ_TYPE = type_;
    projectile_create_sprite(projectile_ent, size_);
    projectile_ent = NULL;
}

// function to update given bullet
void bullet_update(ENTITY *ent)
{
    // simply flying ?
    if (ent->OBJ_STATE == WPN_PROJ_FLY)
    {
        vec_set(&ent->WPN_VEL_X, &ent->WPN_DIR_X);
        vec_scale(&ent->WPN_VEL_X, time_step);
        vec_add(&ent->WPN_VEL_X, &ent->WPN_ORIGIN_X);

        c_ignore(SWITCH_ITEM_GROUP, PROJECTILE_GROUP, ent->WPN_OWNER_GROUP, SHOOT_THROUGH_GROUP, 0);
        ent_trace(ent, &ent->WPN_ORIGIN_X, &ent->WPN_VEL_X, TRACE_FLAGS | ACTIVATE_SHOOT | USE_POLYGON);
        if (HIT_TARGET)
        {
            projectile_impact_function(you);
            ent->OBJ_TIMER = -1; // kill us
        }
        vec_set(&ent->WPN_ORIGIN_X, &ent->WPN_VEL_X);

        // if we run out of time, delete projectile
        ent->OBJ_TIMER -= time_step;
        if (ent->OBJ_TIMER <= 0)
        {
            ent->OBJ_STATE = WPN_PROJ_DELETE;
        }
    }

    // remove projectile
    if (ent->OBJ_STATE == WPN_PROJ_DELETE)
    {
        ent_delete(ent->parent);
        ent_delete(ent);
    }

    if (ent->parent)
    {
        vec_set(&ent->parent->x, &ent->WPN_VEL_X);
        ent_rotate_to_camera(ent->parent);
    }
}

// rocket's func
void rocket_func()
{
    vec_fill(&my->scale_x, 0.35);
    c_setminmax(my);
    set(my, INVISIBLE);
    my->OBJ_STATE = WPN_PROJ_FLY;
    my->OBJ_TIMER = 32;
    my->group = PROJECTILE_GROUP;
    my->push = PROJECTILE_GROUP;
}

// create rocket
void rocket_create(VECTOR *pos, VECTOR *angle, var type_, var group_, var damage_, var speed_, var size_)
{
    ENTITY *projectile_ent = ent_create(bbox_props_mdl, pos, rocket_func);
    vec_set(&projectile_ent->pan, angle);
    projectile_ent->OBJ_ALLOW_MOVE = speed_;
    projectile_ent->WPN_OWNER_GROUP = group_;
    projectile_ent->OBJ_TAKE_DAMAGE = damage_;
    projectile_ent->OBJ_TYPE = type_;
    projectile_create_sprite(projectile_ent, size_);
    projectile_ent = NULL;
}

// function to update rockets
void rocket_update(ENTITY *ent)
{
    // simply flying ?
    if (ent->OBJ_STATE == WPN_PROJ_FLY)
    {
        c_ignore(SWITCH_ITEM_GROUP, PROJECTILE_GROUP, ent->WPN_OWNER_GROUP, SHOOT_THROUGH_GROUP, 0);
        c_move(ent, vector(ent->OBJ_ALLOW_MOVE * time_step, 0, 0), nullvector, MOVE_FLAGS | ACTIVATE_SHOOT | USE_POLYGON);
        if (HIT_TARGET)
        {
            // place slightly above the surface
            vec_set(&ent->WPN_ORIGIN_X, vector(2, 0, 0));
            vec_to_angle(&ent->WPN_DIR_X, &normal);
            vec_rotate(&ent->WPN_ORIGIN_X, &ent->WPN_DIR_X);
            vec_add(&ent->WPN_ORIGIN_X, &hit->x);
            ent->OBJ_TIMER = -1; // kill projectile
        }

        // if far enough from camera
        if (vec_dist(&camera->x, &ent->x) > 64)
        {
            ent->OBJ_PAIN_TYPE = 1; // use this in order to enable smoketrail effect
        }

        if (ent->OBJ_PAIN_TYPE == 1)
        {
            effect(smoketrail_particle, 4, &ent->x, nullvector);
        }

        // if rocket runs out of time, then remove it
        // this may happen if we f.e. shoot it in the air etc.
        ent->OBJ_TIMER -= time_step;
        if (ent->OBJ_TIMER <= 0)
        {
            ent->OBJ_STATE = WPN_PROJ_DELETE;
        }
    }

    // remove rocket
    if (ent->OBJ_STATE == WPN_PROJ_DELETE)
    {
        explosion_create(&ent->WPN_ORIGIN_X, false, ent->OBJ_TYPE);
        ent_delete(ent->parent);
        ent_delete(ent);
    }

    if (ent->parent)
    {
        vec_set(&ent->parent->x, &ent->x);
        ent_rotate_to_camera(ent->parent);
    }
}

// update all projectiles in this function
void projectiles_update()
{
    ENTITY *ent;
    for (ent = ent_next(NULL); ent; ent = ent_next(ent))
    {
        if (ent->OBJ_TYPE == TYPE_PLAYER_MELEE || ent->OBJ_TYPE == TYPE_NPC_MELEE)
        {
            melee_update(ent);
        }

        if (ent->OBJ_TYPE == TYPE_PLAYER_BULLET || ent->OBJ_TYPE == TYPE_NPC_BULLET)
        {
            bullet_update(ent);
        }

        if (ent->OBJ_TYPE == TYPE_PLAYER_ROCKET || ent->OBJ_TYPE == TYPE_NPC_ROCKET)
        {
            rocket_update(ent);
        }
    }
}