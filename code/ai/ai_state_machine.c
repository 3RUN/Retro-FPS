
// go to the given state
void npc_go_to_state(ENTITY *ent, NPC *npc, var state_)
{
    npc->state_timer = 0;
    npc->animator.anim_frame = 0;
    npc->animator.anim_attack = 0;

    switch (state_)
    {
    case AI_IDLE_STATE:
        npc->state_def_time = npc->idle_def_time + random(npc->idle_def_random_time);
        ent->OBJ_STATE = state_;
        break;

    case AI_WALK_STATE:
        npc->state_def_time = npc->walk_def_time + random(npc->walk_def_random_time);
        npc->cct.rotaton_pan = random(360);
        ent->OBJ_STATE = state_;
        break;

    case AI_CHASE_STATE:
        npc->state_def_time = 0;
        ent->OBJ_STATE = state_;
        break;

    case AI_ATTACK_STATE:
        npc->state_def_time = npc->fire_rate;
        npc->attack_counter = 0;
        npc->attack_amount = 1 + random(npc->attack_def_random_amount);
        ent->OBJ_STATE = state_;
        break;

    case AI_DODGE_STATE:
        npc->state_def_time = npc->dodge_def_time + random(npc->dodge_def_random_time);
        var dodge_dir_angle[4] = {-90, 90, 120, -120};
        npc_rotate_to(ent, npc, &npc->target_pos);                   // look at player first
        npc->cct.rotaton_pan += dodge_dir_angle[integer(random(4))]; // then set new direction to dodge at
        ent->OBJ_STATE = state_;
        break;

    case AI_RUN_FOR_MELEE:
        npc_rotate_to(ent, npc, &npc->target_pos); // look at player first
        npc->state_def_time = 0;
        ent->OBJ_STATE = state_;
        break;

    case AI_MELEE_STATE:
        npc->state_def_time = npc->melee_attack_rate; // melee fire rate
        ent->OBJ_STATE = state_;
        break;

    case AI_PAIN_STATE:
        if (random(1) < 0.75)
        {
            npc->state_def_time = npc_pain_time;
            ent->OBJ_STATE = state_;
        }
        if (snd_playing(ent->OBJ_SND_HANDLE))
        {
            snd_stop(ent->OBJ_SND_HANDLE);
        }
        ent->OBJ_SND_HANDLE = ent_playsound(ent, npc_pain_ogg, npc_snd_volume);
        break;

    case AI_DEATH_STATE:
        npc->state_def_time = npc_remove_time;
        ent->OBJ_STATE = state_;
        break;
    }
}

// debug state machine
void npc_state_machine_debug(ENTITY *ent, NPC *npc)
{
    VECTOR temp_pos;
    vec_set(&temp_pos, &ent->x);
    temp_pos.z += 32;
    if (vec_to_screen(&temp_pos, camera))
    {
        temp_pos.x -= 64;

        switch (ent->OBJ_STATE)
        {
        case AI_IDLE_STATE:
            draw_text("AI_IDLE_STATE", temp_pos.x, temp_pos.y, COLOR_WHITE);
            break;

        case AI_WALK_STATE:
            draw_text("AI_WALK_STATE", temp_pos.x, temp_pos.y, COLOR_WHITE);
            break;

        case AI_CHASE_STATE:
            draw_text("AI_CHASE_STATE", temp_pos.x, temp_pos.y, COLOR_WHITE);
            break;

        case AI_ATTACK_STATE:
            draw_text("AI_ATTACK_STATE", temp_pos.x, temp_pos.y, COLOR_WHITE);
            break;

        case AI_DODGE_STATE:
            draw_text("AI_DODGE_STATE", temp_pos.x, temp_pos.y, COLOR_WHITE);
            break;

        case AI_RUN_FOR_MELEE:
            draw_text("AI_RUN_FOR_MELEE", temp_pos.x, temp_pos.y, COLOR_WHITE);
            break;

        case AI_MELEE_STATE:
            draw_text("AI_MELEE_STATE", temp_pos.x, temp_pos.y, COLOR_WHITE);
            break;

        case AI_PAIN_STATE:
            draw_text("AI_PAIN_STATE", temp_pos.x, temp_pos.y, COLOR_WHITE);
            break;

        case AI_DEATH_STATE:
            draw_text("AI_DEATH_STATE", temp_pos.x, temp_pos.y, COLOR_WHITE);
            break;
        }
        var dist_to_cam = vec_dist(vector(ent->x, ent->y, 0), vector(camera->x, camera->y, 0));
        draw_text(
            str_printf(
                NULL,
                "health : %d \ndistance to target : %d \nis_triggered : %d",
                (long)ent->OBJ_HEALTH, (long)npc->dist_to_target, (long)npc->is_triggered),
            temp_pos.x,
            temp_pos.y - 64,
            COLOR_WHITE);
    }
}

// function to update logic for given npc
void update_npc_logic(ENTITY *ent)
{
    // set npc structure from his entity
    NPC *npc = get_npc(ent);

    if (!ent || !npc)
    {
        diag("\nERROR! No update for npc, entity or structure doesn't exist!");
        return;
    }

    // no health ?
    if (ent_is_alive(ent) == false)
    {
        // if not yet in death state ?
        // then switch to it
        if (ent->OBJ_STATE != AI_DEATH_STATE)
        {
            level_enemies_killed++;
            set(ent, PASSABLE);
            // stop all player sounds
            if (snd_playing(ent->OBJ_SND_HANDLE))
            {
                snd_stop(ent->OBJ_SND_HANDLE);
            }
            if (ent->OBJ_DEATH_TYPE == TYPE_SMASHED)
            {
                ent->OBJ_SND_HANDLE = ent_playsound(ent, npc_smashed_death_ogg, npc_snd_volume);
            }
            else
            {
                ent->OBJ_SND_HANDLE = ent_playsound(ent, npc_death_ogg, npc_snd_volume);
            }
            npc_go_to_state(ent, npc, AI_DEATH_STATE);
        }
    }
    else
    {
        // if we are in IDLE or WALK states and don't have target yet ?
        if (npc->is_triggered == false)
        {
            // scan for enemies
            npc_detect_enemies(ent, npc);
        }
        else
        {
            // if we've found player while walking around
            if (ent->OBJ_STATE == AI_IDLE_STATE || ent->OBJ_STATE == AI_WALK_STATE)
            {
                if (snd_playing(ent->OBJ_SND_HANDLE))
                {
                    snd_stop(ent->OBJ_SND_HANDLE);
                }
                ent->OBJ_SND_HANDLE = ent_playsound(ent, npc_alert_ogg, npc_snd_volume);
                npc_alert_friends(ent, npc);
                npc_go_to_state(ent, npc, AI_CHASE_STATE);
            }
        }

        // if we have target set, then calculate distance to it
        if (npc->target_ent)
        {
            npc->dist_to_target = vec_dist(&ent->x, &npc->target_ent->x);
            vec_set(&npc->target_pos, &npc->target_ent->x);

            // target is dead ?
            // then we don't have target to kill
            if (ent_is_alive(npc->target_ent) == false)
            {
                npc->is_triggered = false;
                npc->target_ent = NULL;
                npc_go_to_state(ent, npc, AI_IDLE_STATE);
            }
        }
    }

    // state machine
    switch (ent->OBJ_STATE)
    {
    case AI_IDLE_STATE:
        npc_stop_movement(ent, npc);
        npc->state_timer += time_frame / 16;
        if (npc->state_timer >= npc->state_def_time)
        {
            npc_go_to_state(ent, npc, AI_WALK_STATE);
        }
        break;

    case AI_WALK_STATE:
        npc_set_movement(ent, npc, true, false, false, false, false);
        npc_obstacle_avoidance(ent, npc);
        npc->state_timer += time_frame / 16;
        if (npc->state_timer >= npc->state_def_time)
        {
            npc_go_to_state(ent, npc, AI_IDLE_STATE);
        }
        break;

    case AI_CHASE_STATE:
        npc_set_movement(ent, npc, true, false, false, false, true);
        npc_obstacle_avoidance(ent, npc);
        npc_rotate_to_with_avoidance(ent, npc, &npc->target_pos);

        // can attack ?
        // then go for it
        if (npc->dist_to_target <= npc->attack_range)
        {
            // if melee weapon we have
            if (npc->weapon_type <= AI_MELEE_WEAPON)
            {
                // target is visible ?
                if (npc_is_target_visible(ent, npc) == true)
                {
                    npc_go_to_state(ent, npc, AI_MELEE_STATE); // melee attack !
                }
            }
            else
            {
                // this is executed once a second
                // since fps_max is limited to 60
                if ((total_frames % 60) == 1) // to prevent enemies peeking around the corner
                {
                    if (npc_is_target_visible(ent, npc) == true) // target is visible
                    {
                        // and too close ?
                        if (npc->dist_to_target <= npc->melee_approach_range)
                        {
                            npc_go_to_state(ent, npc, AI_RUN_FOR_MELEE); // run for melee attack
                        }
                        else // otherwise just shoot at it
                        {
                            npc_go_to_state(ent, npc, AI_ATTACK_STATE);
                        }
                    }
                }
            }
        }
        break;

    case AI_ATTACK_STATE:
        // add some randomization for rotating to enemy
        if ((total_frames % npc->accuracy) == 1)
        {
            npc_rotate_to(ent, npc, &npc->target_pos);
        }
        npc_stop_movement(ent, npc);
        npc->state_timer += time_frame / 16;
        if (npc->state_timer >= npc->state_def_time)
        {
            // create projectiles here
            npc_create_projectile(ent, npc);

            npc->attack_counter += 1;
            if (npc->attack_counter >= npc->attack_amount)
            {
                if (npc->dist_to_target > npc->attack_range)
                {
                    npc_go_to_state(ent, npc, AI_CHASE_STATE);
                }
                else
                {
                    npc_go_to_state(ent, npc, AI_DODGE_STATE);
                }
            }
            npc->state_timer -= npc->state_def_time;
        }

        // this is executed each half of a second
        // since fps_max is limited to 60
        if ((total_frames % 30) == 1) // shoot few more times, before going after player
        {
            // if we can't see target directly
            // then go back to chase state
            if (npc_is_target_visible(ent, npc) == false)
            {
                npc_go_to_state(ent, npc, AI_CHASE_STATE);
            }
        }

        // if too close, go for melee attack
        if (npc->dist_to_target <= npc->melee_approach_range)
        {
            npc_go_to_state(ent, npc, AI_RUN_FOR_MELEE);
        }
        break;

    case AI_DODGE_STATE:
        npc_set_movement(ent, npc, true, false, false, false, true);
        npc_obstacle_avoidance(ent, npc);

        npc->state_timer += time_frame / 16;
        if (npc->state_timer >= npc->state_def_time)
        {
            // if we can't see target directly or out of attack range
            // then go back to chase state
            if (npc->dist_to_target > npc->attack_range || npc_is_target_visible(ent, npc) == false)
            {
                npc_go_to_state(ent, npc, AI_CHASE_STATE);
            }
            else
            {
                npc_go_to_state(ent, npc, AI_ATTACK_STATE);
            }
        }

        if (npc_is_target_visible(ent, npc) == true) // target is visible
        {
            // and too close ?
            if (npc->dist_to_target <= npc->melee_approach_range)
            {
                npc_go_to_state(ent, npc, AI_RUN_FOR_MELEE); // run for melee attack
            }
        }
        break;

    case AI_RUN_FOR_MELEE:
        npc_set_movement(ent, npc, true, false, false, false, true);
        npc_obstacle_avoidance(ent, npc);
        npc_rotate_to_with_avoidance(ent, npc, &npc->target_pos);

        // target is visible
        if (npc_is_target_visible(ent, npc) == true)
        {
            // and too close ?
            if (npc->dist_to_target <= npc->melee_range)
            {
                npc_go_to_state(ent, npc, AI_MELEE_STATE); // kick his ass
            }
            else if (npc->dist_to_target >= npc->melee_approach_range) // he is out of our melee range ?
            {
                // start chasing him as usual
                npc_go_to_state(ent, npc, AI_CHASE_STATE);
            }
        }
        else // if we don't see him, go back to chase state
        {
            npc_go_to_state(ent, npc, AI_CHASE_STATE);
        }
        break;

    case AI_MELEE_STATE:
        npc_rotate_to(ent, npc, &npc->target_pos);
        npc_stop_movement(ent, npc);
        npc->state_timer += time_frame / 16;
        if (npc->state_timer >= npc->state_def_time)
        {
            // melee attack here
            npc_create_melee(ent, npc);

            npc->state_timer -= npc->state_def_time;
        }
        // if we have melee weapon
        if (npc->weapon_type <= AI_MELEE_WEAPON)
        {
            // out of melee range or not visible ?
            if (npc->dist_to_target > npc->attack_range || npc_is_target_visible(ent, npc) == false)
            {
                // if out of melee approach range OR not visible
                // chase as usual
                npc_go_to_state(ent, npc, AI_CHASE_STATE);
            }
        }
        else
        {
            // if out of melee range and yet visible
            // then try to get closer to target
            if (npc->dist_to_target > npc->melee_range && npc_is_target_visible(ent, npc) == true)
            {
                npc_go_to_state(ent, npc, AI_RUN_FOR_MELEE);
            }
            else if (npc->dist_to_target > npc->melee_approach_range || npc_is_target_visible(ent, npc) == false)
            {
                // if out of melee approach range OR not visible
                // chase as usual
                npc_go_to_state(ent, npc, AI_CHASE_STATE);
            }
        }
        break;

    case AI_PAIN_STATE:
        npc_stop_movement(ent, npc);
        npc->state_timer += time_frame / 16;
        if (npc->state_timer >= npc->state_def_time)
        {
            npc_go_to_state(ent, npc, AI_CHASE_STATE);
        }
        break;

    case AI_DEATH_STATE:
        npc_stop_movement(ent, npc);
        npc->state_timer += time_frame / 16;
        if (npc->state_timer >= npc->state_def_time)
        {
            ent_delete(ent->parent);
            ent_delete(ent);
        }
        break;
    }

    // handle all movement
    // only if alive
    if (ent_is_alive(ent) == true)
    {
        npc_movement(ent, npc);
    }

    // visual sprite update
    npc_update_visual_sprite(ent, npc);

#ifdef DEBUG_NPC_STATE_MACHINE
    npc_state_machine_debug(ent, npc);
#endif
}