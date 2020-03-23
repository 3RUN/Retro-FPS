
// enable all switches with the given id
void switch_enable_by_id(var num)
{
    ENTITY *temp_ent = NULL;
    for (temp_ent = ent_next(NULL); temp_ent; temp_ent = ent_next(temp_ent))
    {
        if (temp_ent->OBJ_TYPE == TYPE_PROPS_SWITCH)
        {
            // same ID? then disable it
            if (temp_ent->ID == num)
            {
                temp_ent->emask |= (ENABLE_SHOOT);
                ent_setskin(temp_ent->parent, props_switch_off_tga, 1);
            }
        }
    }
}

// disable all switches with the given id
void switch_disable_by_id(var num)
{
    ENTITY *temp_ent = NULL;
    for (temp_ent = ent_next(NULL); temp_ent; temp_ent = ent_next(temp_ent))
    {
        if (temp_ent->OBJ_TYPE == TYPE_PROPS_SWITCH)
        {
            // same ID? then disable it
            if (temp_ent->ID == num)
            {
                temp_ent->emask &= ~ENABLE_SHOOT;
                ent_setskin(temp_ent->parent, props_switch_on_tga, 1);
            }
        }
    }
}

// function used to trigger props with the same id
void switch_trigger_props()
{
    ENTITY *temp_ent = NULL;
    for (temp_ent = ent_next(NULL); temp_ent; temp_ent = ent_next(temp_ent))
    {
        // props
        if (temp_ent->OBJ_TYPE == TYPE_PROPS_DOOR || temp_ent->OBJ_TYPE == TYPE_PROPS_SECRET)
        {
            // not the same ID OR not using switch ? ignore
            if (temp_ent->ID != my->ID || !is(temp_ent, USE_SWITCH))
            {
                continue;
            }

            // already triggered ? ignore
            if (temp_ent->OBJ_STATE != PROPS_IDLE_STATE)
            {
                continue;
            }

            // open found props
            temp_ent->OBJ_STATE = PROPS_OPEN_STATE;
        }
    }
}

// switch's event function
void switch_event_function()
{
    if (event_type == EVENT_SHOOT)
    {
        // only player can trigger switches ?
        if (you->OBJ_TYPE == TYPE_PLAYER)
        {
            // not interacting with us ? then ignore !
            if (you->OBJ_C_INDICATOR != C_INTERACT)
            {
                return;
            }

            // disable all switches with the same ID
            switch_disable_by_id(my->ID);

            // play switch sound
            if (snd_playing(my->OBJ_SND_HANDLE))
            {
                snd_stop(my->OBJ_SND_HANDLE);
            }
            my->OBJ_SND_HANDLE = ent_playsound(my, props_switch_ogg, switch_snd_volume);

            // wait for a while
            ent_delay(my, 1);
            wait_for_my(ent_delay);

            // trigger props with the same ID
            switch_trigger_props();
        }
    }
}

// switch to trigge other props
// uses: ID
action props_switch()
{
    // correct our Z position
    // and attach to the near by wall !
    my->z = WORLD_Z_POS;
    ent_attach_to_near_wall(my);
    wait_for(ent_attach_to_near_wall);

    vec_set(&my->scale_x, vector(0.15, 0.5, 0.5));
    c_setminmax(my);
    set(my, POLYGON | INVISIBLE);

    my->group = SWITCH_ITEM_GROUP;
    my->push = SWITCH_ITEM_GROUP;

    my->OBJ_TYPE = TYPE_PROPS_SWITCH;

    my->emask |= (ENABLE_SHOOT);
    my->event = switch_event_function;

    // create visual sprite
    my->parent = ent_create(props_decor_mdl, &my->x, NULL);
    props_visual_ent(my, my->parent, props_switch_off_tga);
}