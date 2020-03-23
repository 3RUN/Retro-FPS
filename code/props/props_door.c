
// play door's sounds on open/close
void door_snd(ENTITY *ent, var is_shut)
{
    if (is_shut == true)
    {
        if (ent->OBJ_HEALTH == 1)
        {
            if (snd_playing(ent->OBJ_SND_HANDLE))
            {
                snd_stop(ent->OBJ_SND_HANDLE);
            }
            ent->OBJ_SND_HANDLE = ent_playsound(ent, props_door_shut_ogg, door_snd_volume);
            ent->OBJ_HEALTH = 0;
        }
    }
    else
    {
        if (ent->OBJ_HEALTH == 0)
        {
            if (snd_playing(ent->OBJ_SND_HANDLE))
            {
                snd_stop(ent->OBJ_SND_HANDLE);
            }
            ent->OBJ_SND_HANDLE = ent_playsound(ent, props_door_open_ogg, door_snd_volume);
            ent->OBJ_HEALTH = 1;
        }
    }
}

// function to update given door
void door_update(ENTITY *ent)
{
    // get props struct
    PROPS *props = get_props(ent);
    
    // state machine
    switch (ent->OBJ_STATE)
    {

    case (PROPS_OPEN_STATE):
    {
        // save this state
        props->old_state = PROPS_OPEN_STATE;

        // reset polygon flag!
        reset(ent, POLYGON);

        // still can move ?
        if (vec_dist(&ent->x, &ent->PROPS_OFFSET_X_) > 0.5)
        {
            // move to target position
            vec_diff(&props->diff, &ent->PROPS_OFFSET_X_, &ent->x);
            var spd = props->movement_speed * time_step;
            if (vec_length(&props->diff) > spd)
            {
                vec_normalize(&props->diff, spd);
            }
            vec_add(&ent->x, &props->diff);

            // play opening sound effect
            door_snd(ent, false);
        }
        else
        {
            // play shut sound effect
            door_snd(ent, true);

            // set proper position
            vec_set(&ent->x, &ent->PROPS_OFFSET_X_);

            // triggered door, should never close again !
            if (is(ent, USE_TRIGGER))
            {
                // switch to delay
                ent->OBJ_STATE = PROPS_IDLE_STATE;
            }
            else
            {
                // switch to delay
                ent->OBJ_STATE = PROPS_DELAY_STATE;
                ent->OBJ_TIMER = props->delay_time;
            }
        }

        break;
    }

    case (PROPS_CLOSE_STATE):
    {
        // save this state
        props->old_state = PROPS_CLOSE_STATE;

        if (vec_dist(&ent->x, &props->origin) > 0.5)
        {
            vec_diff(&props->diff, &props->origin, &ent->x);
            var spd = props->movement_speed * time_step;
            if (vec_length(&props->diff) > spd)
            {
                vec_normalize(&props->diff, spd);
            }
            c_ignore(SWITCH_ITEM_GROUP, PROJECTILE_GROUP, SHOOT_THROUGH_GROUP, OBSTACLE_GROUP, 0);
            c_move(ent, nullvector, &props->diff, MOVE_FLAGS | IGNORE_WORLD);
            if (HIT_TARGET)
            {
                // hit something ?
                // open back again !
                if (snd_playing(ent->OBJ_SND_HANDLE))
                {
                    snd_stop(ent->OBJ_SND_HANDLE);
                }
                ent->OBJ_HEALTH = 0;
                ent->OBJ_STATE = PROPS_OPEN_STATE;
            }

            // play opening sound effect
            door_snd(ent, false);
        }
        else
        {
            // play shut sound effect
            door_snd(ent, true);

            // set proper position
            vec_set(&ent->x, &props->origin);

            // switch to delay
            ent->OBJ_STATE = PROPS_IDLE_STATE;

            // set polygon flag back, since we not gonna move!
            set(ent, POLYGON);

            // if we used switch, enable them all again
            if (is(ent, USE_SWITCH))
            {
                switch_enable_by_id(ent->ID);
            }
        }

        break;
    }

    case (PROPS_DELAY_STATE):
    {
        ent->OBJ_TIMER -= time_frame / 16;
        if (ent->OBJ_TIMER <= 0)
        {
            ent->OBJ_STATE = PROPS_CLOSE_STATE;
        }

        break;
    }
    }

    if (ent->parent)
    {
        vec_set(&ent->parent->x, &ent->x);
    }
}

// check if player has needed key
var door_player_has_key()
{
    if (is(my, RED_KEY) && player_has_red_key == false)
    {
        return false;
    }
    if (is(my, YELLOW_KEY) && player_has_yellow_key == false)
    {
        return false;
    }
    if (is(my, BLUE_KEY) && player_has_blue_key == false)
    {
        return false;
    }

    return true;
}

// door's can't open sound effect
void door_no_use_snd(ENTITY *ent)
{
    // play no keycard sound here !
    if (snd_playing(ent->OBJ_SND_HANDLE))
    {
        snd_stop(ent->OBJ_SND_HANDLE);
    }
    ent->OBJ_SND_HANDLE = snd_play(props_door_req_ogg, player_snd_volume, 0);
}

// event function for the door
void door_event_function()
{
    if (event_type == EVENT_SHOOT)
    {
        // not interacting with us ? then ignore !
        if (you->OBJ_C_INDICATOR != C_INTERACT)
        {
            return;
        }

        // already moving ? ingore !
        if (my->OBJ_STATE != PROPS_IDLE_STATE)
        {
            return;
        }

        // if this door needs to be triggered by switch, don't interact with it
        if (is(my, USE_SWITCH) || is(my, USE_TRIGGER))
        {
            // play no use snd for player !
            // only if we can be opened by the switch
            // trigger zone should be ignored on interaction
            if (you->OBJ_TYPE == TYPE_PLAYER && is(my, USE_SWITCH))
            {
                // play can't open sound here
                door_no_use_snd(you);

                // show message, that this door opens elsewhere
                show_message(opens_elsewhere_str);
            }
            return;
        }

        // requires a key ?
        if (is(my, RED_KEY) || is(my, YELLOW_KEY) || is(my, BLUE_KEY))
        {
            // interaction from player ?
            if (you->OBJ_TYPE == TYPE_PLAYER)
            {
                // no keys ?
                if (door_player_has_key() == false)
                {
                    // don't allow to interact
                    my->emask &= ~ENABLE_SHOOT;

                    // play can't open sound here
                    door_no_use_snd(you);

                    // show message, that this door requires a key
                    show_message(requires_key_str);

                    // wait for a while
                    ent_delay(my, 1);
                    wait_for_my(ent_delay);

                    my->emask |= (ENABLE_SHOOT);

                    return;
                }
                else
                {
                    // reset our key
                    if (is(my, RED_KEY))
                    {
                        reset(my, RED_KEY);
                    }
                    if (is(my, YELLOW_KEY))
                    {
                        reset(my, YELLOW_KEY);
                    }
                    if (is(my, BLUE_KEY))
                    {
                        reset(my, BLUE_KEY);
                    }
                }
            }
            else
            {
                // ignore npcs
                return;
            }
        }

        // open this door
        my->OBJ_STATE = PROPS_OPEN_STATE;
    }
}

// simple door action
// uses: ID, RED_KEY, YELLOW_KEY, BLUE_KEY, USE_SWITCH, USE_TRIGGER
action props_door()
{
    // correct our Z position
    my->z = WORLD_Z_POS;

    PROPS *props = register_props(my);
    props->movement_speed = 3.5;
    props->delay_time = 5;

    vec_fill(&my->scale_x, 1);
    c_setminmax(my);
    set(my, POLYGON);

    my->group = OBSTACLE_GROUP;
    my->push = OBSTACLE_GROUP;

    my->OBJ_STATE = PROPS_IDLE_STATE;
    my->OBJ_TYPE = TYPE_PROPS_DOOR;

    // predefined offset to open our door
    // if door opens by trigger zone, then it should move upwards !
    if (is(my, USE_TRIGGER))
    {
        set(my, NOFILTER);
        vec_set(&my->PROPS_OFFSET_X_, vector(0, 0, WORLD_TILE_SIZE - 1));
    }
    else
    {
        // if normal door, then it's bbox should be invisible !
        set(my, INVISIBLE);

        // simple sideways opening door
        vec_set(&my->PROPS_OFFSET_X_, vector(0, -WORLD_TILE_SIZE, 0));

        // create visual model
        my->parent = ent_create(props_decor_mdl, &my->x, NULL);
        if (is(my, RED_KEY))
        {
            props_visual_ent(my, my->parent, props_door_red_tga);
        }
        else if (is(my, YELLOW_KEY))
        {
            props_visual_ent(my, my->parent, props_door_yellow_tga);
        }
        else if (is(my, BLUE_KEY))
        {
            props_visual_ent(my, my->parent, props_door_blue_tga);
        }
        else
        {
            props_visual_ent(my, my->parent, props_door_tga);
        }
    }

    vec_rotate(&my->PROPS_OFFSET_X_, &my->pan);
    vec_add(&my->PROPS_OFFSET_X_, &my->x);

    my->emask |= (ENABLE_SHOOT);
    my->event = door_event_function;
}