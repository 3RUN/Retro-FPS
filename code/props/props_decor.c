

// sprites event function
void sprite_event_function()
{
    if (event_type == EVENT_FRAME)
    {
        // does it needs to be rotated to the camera ?
        if (is(my, ROTATE_TO_CAM))
        {
            ent_rotate_to_camera(my);
        }

        if (my->parent)
        {
            vec_set(&my->parent->x, &my->x);
        }
    }
}

// uses: ROTATE_TO_CAM, IS_OBSTACLE, SHOOT_THROUGH, ATTACH_TO_WALL
// FLAG3: ROTATE_TO_CAM 1
action props_sprite()
{
    // correct our Z position
    my->z = WORLD_Z_POS;

    // sprite is always passable
    // for collisions we use bboxes !
    set(my, PASSABLE | NOFILTER);

    // not rotating to camera
    if (!is(my, ROTATE_TO_CAM))
    {
        if (my->pan == 0)
        {
            my->pan += 0.01;
        }
    }

    // we should be attached to the wall ?
    if (is(my, ATTACH_TO_WALL))
    {
        ent_attach_to_near_wall(my);
    }

    // create bbox model
    my->parent = ent_create(bbox_props_mdl, &my->x, NULL);
    set(my->parent, INVISIBLE);
    vec_set(&my->parent->scale_x, vector(0.5, 0.5, 1));
    c_setminmax(my->parent);

    // if we aren't passable
    if (is(my, IS_OBSTACLE))
    {
        set(my->parent, POLYGON);

        // set ground depending on
        // can we shoot through this obstacle or not
        if (is(my, SHOOT_THROUGH))
        {
            my->parent->group = SHOOT_THROUGH_GROUP;
            my->parent->push = SHOOT_THROUGH_GROUP;
        }
        else
        {
            my->parent->group = OBSTACLE_GROUP;
            my->parent->push = OBSTACLE_GROUP;
        }
    }
    else
    {
        set(my->parent, PASSABLE);
        my->parent->group = SWITCH_ITEM_GROUP;
        my->parent->push = SWITCH_ITEM_GROUP;
    }

    my->emask |= (ENABLE_FRAME);
    my->event = sprite_event_function;
}