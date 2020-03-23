
// initialize all player parameters
void player_init(PLAYER *hero)
{
    if (!hero)
    {
        error("Can't initialize player, his structure doesn't exist!");
        return;
    }
		
	 if(nxs_layer == 1){my->pan = tiles[cm_XY[0]][cm_XY[1]].rotation + 90;}
	 if(nxs_layer == 2){my->pan = tilesB[cm_XY[0]][cm_XY[1]].rotation + 90;}
	 if(nxs_layer == 3){my->pan = tilesC[cm_XY[0]][cm_XY[1]].rotation + 90;}
	 
    hero->cct.movement_speed = 5.5;
    hero->cct.rotaton_pan = my->pan;
    hero->cct.walk_speed_factor = 1;
    hero->cct.run_speed_factor = 2;

    vec_set(&hero->cam.position, &my->x);
    vec_set(&camera->x, &my->x);
    vec_set(&hero->cam.angle, &my->pan);
    vec_set(&camera->pan, vector(my->pan, 0, 0));
    hero->cam.height = 0;
    hero->cam.fov = cam_fov;
    hero->cam.bob_z_offset = 1.5;
    hero->cam.bob_speed_factor = 2;
    hero->cam.recoil_power = 1;
}

// function to update all player's logic
void player_update()
{
    ENTITY *ent;
    for (ent = ent_next(NULL); ent; ent = ent_next(ent))
    {
        if (ent->OBJ_TYPE == TYPE_PLAYER)
        {
            player_update_logic(ent);
        }
    }
}

// functon to handle player's interaction trace
void player_interaction(ENTITY *ent, PLAYER *hero)
{
    // if we are allowed to move and we are alive
    if (ent->OBJ_ALLOW_MOVE == true && ent_is_alive(ent) == true)
    {
        vec_set(&hero->interact_pos, vector(cct_interact_distance, 0, 0));
        vec_rotate(&hero->interact_pos, &camera->pan);
        vec_add(&hero->interact_pos, &camera->x);

        if (hero->interact == true)
        {
            if (hero->interact_once == false)
            {
                // make sure to note that this is an interaction trace
                ent->OBJ_C_INDICATOR = C_INTERACT;
                c_ignore(PROJECTILE_GROUP, PLAYER_GROUP, NPC_GROUP, 0);
                ent_trace(ent, &camera->x, &hero->interact_pos, TRACE_FLAGS | ACTIVATE_SHOOT);
                // play no use sound effect here

                hero->interact_once = true;
            }
        }
        else
        {
            hero->interact_once = false;
        }
    }
}

// player logic function
void player_update_logic(ENTITY *ent)
{
    // get structure
    PLAYER *hero = get_player_structure(ent);

    if (!hero)
    {
        error("Player structure doesn't exist!");
        return;
    }

    // test death
    if (key_q)
    {
        ent->OBJ_HEALTH = -1;
    }

    // update variables
    player_health = ent->OBJ_HEALTH;
    player_allow_move = ent->OBJ_ALLOW_MOVE;

    // if alive
    if (ent_is_alive(ent) == true && ent->OBJ_ALLOW_MOVE == true)
    {
        // get input
        hero->cct.run = key_shift;
        hero->cct.always_run = player_always_run;
        hero->cct.forward = key_w;
        hero->cct.backward = key_s;
        hero->cct.strafe_left = key_a;
        hero->cct.strafe_right = key_d;
        hero->shoot = mouse_left;
        hero->interact = mouse_right;
        hero->weapon_1 = key_1;
        hero->weapon_2 = key_2;
        hero->weapon_3 = key_3;
        hero->weapon_4 = key_4;
        hero->weapon_5 = key_5;
        hero->cct.rotaton_pan = camera->pan;

        // set input from player
        cct_set_movement(ent, &hero->cct);
    }
    else
    {
        // reset input
        hero->shoot = 0;
        hero->interact = 0;
        hero->weapon_1 = 0;
        hero->weapon_2 = 0;
        hero->weapon_3 = 0;
        hero->weapon_4 = 0;
        hero->weapon_5 = 0;

        // stop all movement if we are dead or not allowed to move
        cct_stop_movement(ent, &hero->cct);

        // if dead
        if (ent_is_alive(ent) == false)
        {
            // play death sound once
            // we'll use OBJ_EXPLO_RANGE to play snd once
            // since player doesn't use OBJ_EXPLO_RANGE anywhere else
            if (ent->OBJ_EXPLO_RANGE != -1)
            {
                // death effect
                gui_player_dead_effect();

                // no events from here on
                ent->emask &= ~(ENABLE_PUSH | ENABLE_SHOOT | ENABLE_SCAN);
                ent->event = NULL;

                // stop all player sounds
                if (snd_playing(ent->OBJ_SND_HANDLE))
                {
                    snd_stop(ent->OBJ_SND_HANDLE);
                }
                if (ent->OBJ_DEATH_TYPE == TYPE_SMASHED)
                {
                    ent->OBJ_SND_HANDLE = snd_play(npc_smashed_death_ogg, player_snd_volume, 0);
                }
                else
                {
                    ent->OBJ_SND_HANDLE = snd_play(player_death_ogg, player_snd_volume, 0);
                }
                ent->OBJ_EXPLO_RANGE = -1;
            }
        }
    }

    // handle all player's movement
    hero->cct.fixed_z_pos = WORLD_Z_POS;
    cct_update_movement(ent, &hero->cct);

    // attach and update camera
    camera_update(ent, hero);

    // allow interactions
    player_interaction(ent, hero);

    // update weapons
    player_weapons_update(ent, hero);
}

// toggle auto run mode on and off
void player_toggle_run()
{
    if (player_allow_move == false || player_health <= 0)
    {
        return;
    }
    if (level_is_loaded == false)
    {
        return;
    }

    player_always_run += 1;
    player_always_run -= 2;
}

// player in pain effect (sound + gui)
void player_in_pain(ENTITY *ent)
{
    // only if alive !
    if (ent_is_alive(ent) == false)
    {
        return;
    }

    if (snd_playing(ent->OBJ_SND_HANDLE))
    {
        snd_stop(ent->OBJ_SND_HANDLE);
    }
    gui_do_game_effect(PLAYER_DAMAGE_COLOR);
    ent->OBJ_SND_HANDLE = snd_play(player_pain_ogg, player_snd_volume, 0);
}

// check for walls
void player_check_walls(ENTITY *ent, VECTOR *from, VECTOR *to, var dmg)
{
    // save input
    VECTOR you_pos;
    VECTOR my_pos;
    vec_set(&you_pos, from);
    vec_set(&my_pos, to);
    var temp_damage = dmg;

    wait(1); // because in called in event function !

    // if we are close enough ?
    if (vec_dist(&you_pos, &my_pos) > explo_default_range)
    {
        return;
    }

    c_ignore(SWITCH_ITEM_GROUP, PROJECTILE_GROUP, PLAYER_GROUP, NPC_GROUP, SHOOT_THROUGH_GROUP, 0);
    if (c_trace(&you_pos, &my_pos, TRACE_FLAGS))
    {
        return;
    }

    // calculate damage
    // 128 quants (by default), because it's the closes range
    var damage = (1 - (vec_dist(&you_pos, &my_pos) / explo_default_range)) * temp_damage;
#ifndef PLAYER_IMMORTAL
    ent->OBJ_HEALTH -= damage + 32; // to make sure, that you will die, if very close
#endif
    player_in_pain(ent);

    // if your health is too low, then you need to spawn gibs
    if (ent->OBJ_HEALTH <= -20)
    {
        ent->OBJ_DEATH_TYPE = TYPE_SMASHED;
    }

    // push away
    VECTOR push_vec;
    vec_diff(&push_vec, &my_pos, &you_pos);
    vec_normalize(&push_vec, damage * 0.25);

    PLAYER *hero = get_player_structure(ent);
    vec_set(&hero->cct.abs_force, &push_vec);
    camera_add_damage_effect(my, hero, &you_pos);
}

// event function for player
void player_event_function()
{
    if (event_type == EVENT_PUSH)
    {
        // smashed by props ?
        if (you->OBJ_TYPE == TYPE_PROPS_SECRET)
        {
            // get props structure
            PROPS *props = get_props(you);
            PLAYER *hero = get_player_structure(my);

            // push us away
            vec_set(&hero->cct.push_force, vector(props->diff.x, props->diff.y, 0));

            // if we can perform check ?
            // means that door is almost closed (f.e.)
            if (you->OBJ_CHECK == true)
            {
                // check if we were smashed or not
                if (props_vs_npc_check(you, my, my->scale_x) == true)
                {
#ifndef PLAYER_IMMORTAL
                    my->OBJ_HEALTH = -999;
                    my->OBJ_DEATH_TYPE = TYPE_SMASHED;
#endif
                }
            }
        }
    }

    if (event_type == EVENT_SHOOT)
    {
        // take damage from projectiles
        if (you->OBJ_TYPE == TYPE_NPC_MELEE || you->OBJ_TYPE == TYPE_NPC_BULLET)
        {
#ifndef PLAYER_IMMORTAL
            my->OBJ_HEALTH -= you->OBJ_TAKE_DAMAGE;
#endif
            PLAYER *hero = get_player_structure(my);
            camera_add_damage_effect(my, hero, &you->x);
            player_in_pain(my);
        }

        // if hit by rocket ?
        // explode right now !
        if (you->OBJ_TYPE == TYPE_NPC_ROCKET)
        {
#ifndef PLAYER_IMMORTAL
            my->OBJ_HEALTH = -999;
#endif
        }
    }

    if (event_type == EVENT_SCAN)
    {
        // if scan from any type of explosions
        if (you->OBJ_TYPE == TYPE_PLAYER_EXPLOSION || you->OBJ_TYPE == TYPE_NPC_EXPLOSION || you->OBJ_TYPE == TYPE_PROPS_EXPLOSION)
        {
            // get player's structure
            PLAYER *hero = get_player_structure(my);

            // shake camera !
            var explo_cam_range = (1 - (vec_dist(&my->x, &you->x) / you->OBJ_EXPLO_RANGE)) * you->OBJ_EXPLO_DAMAGE;
            hero->cam.explo_power = maxv(1, explo_cam_range / 8);

            // check for walls, push away from explosion etc
            player_check_walls(my, &you->x, &my->x, you->OBJ_EXPLO_DAMAGE);
        }
    }
}

// simple action called in WED
action player_controller()
{
    // correct our Z position
    my->z = WORLD_Z_POS;

    // reset player's stuff
    player_has_red_key = false;
    player_has_yellow_key = false;
    player_has_blue_key = false;

    // register player structure here
    PLAYER *hero = register_player_structure(my);
    player_init(hero);
    player_weapons_init(my, hero);

    set(my, TRANSLUCENT | FLAG2); // flag2 - is set for enemies c_scan
    my->alpha = 0;
    c_setminmax(my);
    var bbox_x = biggest_bbox_x_side - 2;
    var bbox_y = biggest_bbox_y_side - 2;
    var bbox_z = biggest_bbox_z_side - 2;
    vec_set(&my->max_x, vector(bbox_x, bbox_y, bbox_z));
    vec_set(&my->min_x, vector(-bbox_x, -bbox_y, -bbox_z));

    // object settings
    my->OBJ_HEALTH = 100;
    my->OBJ_TYPE = TYPE_PLAYER;
    my->OBJ_ALLOW_MOVE = true;

    // safe stuff for gui etc
    player_health = my->OBJ_HEALTH;
    player_allow_move = my->OBJ_ALLOW_MOVE;

    my->group = PLAYER_GROUP;
    my->push = PLAYER_GROUP;
			
    my->emask |= (ENABLE_SHOOT | ENABLE_SCAN | ENABLE_PUSH);
    my->event = player_event_function;
}