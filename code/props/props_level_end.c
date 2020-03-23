
// event function for visual part of level end
void level_end_event_function()
{
    if (event_type == EVENT_FRAME)
    {
        ent_rotate_to_camera(my);

        if (my->parent)
        {
            vec_set(&my->parent->x, &my->x);
            my->parent->z = WORLD_Z_POS / 2;
            my->OBJ_HEALTH = my->parent->OBJ_HEALTH;
        }

        if (ent_is_alive(my) == false)
        {
            ent_delete(my->parent);
            ent_delete(my);
        }
    }
}

// event function for level end bbox
void level_end_bbox_event_function()
{
    if (event_type == EVENT_PUSH)
    {
        // player is that you ?
        if (you->OBJ_TYPE != TYPE_PLAYER)
        {
            return;
        }

        // dead ?
        if (player_health <= 1 || ent_is_alive(you) == false)
        {
            return;
        }

        // only once !
        my->emask &= ~ENABLE_PUSH;

        // save player's weapons
        PLAYER *hero = get_player_structure(you);
        player_weapons_save_at_level_end(hero);

        // kill us and switch game state to info
        my->OBJ_HEALTH = -1;
        game_state = GAME_LEVEL_INFO;
    }
}

// level ending props
action props_level_end()
{
    // correct our Z position
    my->z = WORLD_Z_POS;
    set(my, PASSABLE | NOFILTER);
    my->material = mtl_z_write;
    my->OBJ_TYPE = TYPE_PROPS_LEVEL_END;
    my->OBJ_HEALTH = 1;
    my->emask |= (ENABLE_FRAME);
    my->event = level_end_event_function;

    // create bbox
    my->parent = ent_create(bbox_props_mdl, &my->x, NULL);
    set(my->parent, POLYGON | INVISIBLE);
    vec_set(&my->parent->scale_x, vector(0.25, 0.25, 1));
    c_setminmax(my->parent);
    my->parent->OBJ_HEALTH = my->OBJ_HEALTH;
    my->parent->OBJ_STATE = my->OBJ_STATE;
    my->parent->OBJ_TYPE = my->OBJ_TYPE;
    my->parent->group = SWITCH_ITEM_GROUP;
    my->parent->push = SWITCH_ITEM_GROUP;

    my->parent->emask |= (ENABLE_PUSH);
    my->parent->event = level_end_bbox_event_function;
}