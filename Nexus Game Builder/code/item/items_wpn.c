
// add ammo to the given weapon
void wpn_add_ammo(var *am_typ, var am, var mx)
{
    *am_typ += am;
    *am_typ = clamp(*am_typ, 0, mx);
}

// weapon pickup event function
void wpn_event_function()
{
    if (event_type == EVENT_PUSH)
    {
        // player is that you ?
        if (you->OBJ_TYPE != TYPE_PLAYER)
        {
            return;
        }

        // if you are dead
        if (ent_is_alive(you) == false)
        {
            return;
        }

        // only once !
        my->emask &= ~ENABLE_PUSH;

        // get player's structure
        PLAYER *hero = get_player_structure(you);

        // play pickup snd
        if (snd_playing(player_pick_snd_handle))
        {
            snd_stop(player_pick_snd_handle);
        }
        player_pick_snd_handle = snd_play(item_ammo_ogg, wpn_pickup_snd_volume, 0);

        // pickup effect
        gui_do_game_effect(ITEM_WPN_COLOR);

        // we don't have this weapon ?
        // then collect it
        if (hero->weapon[my->ID].collected == false)
        {
            hero->weapon[my->ID].collected = true;

            // if our current weapon is weaker ?
            // then switch to new one automatically
            if (weapon_id < my->ID)
            {
                player_switch_weapon_by_id(hero, my->ID);
            }
        }

        // also add some ammo
        switch (my->ID)
        {
        case PLAYER_WPN_PISTOL:
            wpn_add_ammo(&player_ammo_bullets, wpn_bullets_add_ammo, wpn_bullets_max_ammo);
            gui_history_add_message(wpn_pistol_str);
            break;

        case PLAYER_WPN_SHOTGUN:
            wpn_add_ammo(&player_ammo_shells, wpn_shells_add_ammo, wpn_shells_max_ammo);
            gui_history_add_message(wpn_shotgun_str);
            break;

        case PLAYER_WPN_CHAINGUN:
            wpn_add_ammo(&player_ammo_bullets, wpn_bullets_add_ammo, wpn_bullets_max_ammo);
            gui_history_add_message(wpn_chaingun_str);
            break;

        case PLAYER_WPN_ROCKETL:
            wpn_add_ammo(&player_ammo_rockets, wpn_rockets_add_ammo, wpn_rockets_max_ammo);
            gui_history_add_message(wpn_rocketl_str);
            break;
        }
        my->OBJ_HEALTH = -1;
    }

    if (event_type == EVENT_FRAME)
    {
        if (my->parent)
        {
            vec_set(&my->parent->x, &my->x);
            my->parent->z = WORLD_Z_POS;
            ent_rotate_to_camera(my->parent);
        }

        if (my->OBJ_HEALTH <= 0)
        {
            ent_delete(my->parent);
            ent_delete(my);
        }
    }
}

// init pickable weapon
void wpn_init(var num)
{
    vec_set(&my->scale_x, vector(0.5, 0.5, 1));
    c_setminmax(my);
    ent_place_on_ground(my);
    set(my, POLYGON | INVISIBLE);

    my->group = SWITCH_ITEM_GROUP;
    my->push = SWITCH_ITEM_GROUP;

    if (num < 0 || num > MAX_WEAPONS)
    {
        my->ID = PLAYER_WPN_PISTOL;
    }
    my->ID = num;
    my->OBJ_HEALTH = 100;
    my->OBJ_TYPE = TYPE_PICKABLE_ITEM;

    my->emask |= (ENABLE_PUSH | ENABLE_FRAME);
    my->event = wpn_event_function;

    // create visual model
    my->parent = ent_create(props_decor_mdl, &my->x, NULL);

    // depending on our type, create visual sprite
    switch (my->ID)
    {
    case PLAYER_WPN_PISTOL:
        item_visual_ent(my->parent, item_wpn_pistol_tga);
        break;

    case PLAYER_WPN_SHOTGUN:
        item_visual_ent(my->parent, item_wpn_shotgun_tga);
        break;

    case PLAYER_WPN_CHAINGUN:
        item_visual_ent(my->parent, item_wpn_chaingun_tga);
        break;

    case PLAYER_WPN_ROCKETL:
        item_visual_ent(my->parent, item_wpn_rocketl_tga);
        break;
    }
}

// pickable weapons
action wpn_pistol()
{
    wpn_init(PLAYER_WPN_PISTOL);
}

action wpn_shotgun()
{
    wpn_init(PLAYER_WPN_SHOTGUN);
}

action wpn_chaingun()
{
    wpn_init(PLAYER_WPN_CHAINGUN);
}

action wpn_rocketlauncher()
{
    wpn_init(PLAYER_WPN_ROCKETL);
}