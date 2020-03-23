
// detect near by enemies
void npc_detect_enemies(ENTITY *ent, NPC *npc)
{
    c_ignore(SWITCH_ITEM_GROUP, PROJECTILE_GROUP, NPC_GROUP, SHOOT_THROUGH_GROUP, OBSTACLE_GROUP, 0);
    ent_scan(ent, &ent->x, &ent->pan, vector(360, 0, npc->scan_range), MOVE_FLAGS | SCAN_ENTS | SCAN_FLAG2);
}

// alert other npcs near by
void npc_alert_friends(ENTITY *ent, NPC *npc)
{
    c_ignore(SWITCH_ITEM_GROUP, PROJECTILE_GROUP, PLAYER_GROUP, SHOOT_THROUGH_GROUP, OBSTACLE_GROUP, 0);
    ent_scan(ent, &ent->x, &ent->pan, vector(360, 0, npc->scan_range), MOVE_FLAGS | SCAN_ENTS | SCAN_FLAG2);
}

// checks if you entity is visible or not
// this function is called from event function only!
var npc_is_you_visible(ENTITY *my_ent, NPC *npc, ENTITY *you_ent)
{
    if (!my_ent || !you_ent)
    {
        error("No valid my or you pointers in is_you_visible funciton!");
        return;
    }

    ENTITY *temp_my = my_ent;
    ENTITY *temp_you = you_ent;

    wait(1); // because we are calling this in event function

    c_ignore(SWITCH_ITEM_GROUP, PROJECTILE_GROUP, PLAYER_GROUP, NPC_GROUP, SHOOT_THROUGH_GROUP, 0);
    c_trace(&temp_my->x, &temp_you->x, TRACE_FLAGS);
    if (HIT_TARGET)
    {
        return false;
    }

    // if you is player
    if (temp_you->OBJ_TYPE == TYPE_PLAYER)
    {
        npc->target_ent = temp_you;
        npc->is_triggered = true;
    }
    else if (temp_you->OBJ_TYPE == TYPE_NPC)
    {
        if (npc->target_ent)
        {
            NPC *friendly_npc = get_npc(temp_you);
            friendly_npc->is_triggered = true;
            friendly_npc->target_ent = npc->target_ent;
            NPC *friendly_npc = NULL;
        }
    }

    temp_my = NULL;
    temp_you = NULL;
    return true;
}

// check if npc can see it's target
var npc_is_target_visible(ENTITY *ent, NPC *npc)
{
    if (!npc->target_ent)
    {
        diag("\nERROR! No visibility check for npc, target ent it doesn't exist!");
        return false;
    }

    c_ignore(SWITCH_ITEM_GROUP, PROJECTILE_GROUP, PLAYER_GROUP, SHOOT_THROUGH_GROUP, 0);
    var trace_res = ent_trace(ent, &ent->x, &npc->target_ent->x, TRACE_FLAGS);

    if (trace_res > 0)
    {
        return false;
    }
    return true;
}

// simple obstacle avoidance
void npc_obstacle_avoidance(ENTITY *ent, NPC *npc)
{
    vec_set(&npc->sensor_right, vector(npc->sensor_distance, -npc->sensor_width, 0));
    vec_rotate(&npc->sensor_right, vector(npc->cct.rotaton_pan, 0, 0));
    vec_add(&npc->sensor_right, &ent->x);

    c_ignore(SWITCH_ITEM_GROUP, PROJECTILE_GROUP, 0);
    ent_trace(ent, &ent->x, &npc->sensor_right, TRACE_FLAGS);
    npc->sensor_hit_right = false;
    if (HIT_TARGET)
    {
        npc->sensor_hit_right = true;
        npc->route_timer = 0;
        npc->route_find = true;
    }

    vec_set(&npc->sensor_left, vector(npc->sensor_distance, npc->sensor_width, 0));
    vec_rotate(&npc->sensor_left, vector(npc->cct.rotaton_pan, 0, 0));
    vec_add(&npc->sensor_left, &ent->x);

    c_ignore(SWITCH_ITEM_GROUP, PROJECTILE_GROUP, 0);
    ent_trace(ent, &ent->x, &npc->sensor_left, TRACE_FLAGS);
    npc->sensor_hit_left = false;
    if (HIT_TARGET)
    {
        npc->sensor_hit_left = true;
        npc->route_timer = 0;
        npc->route_find = true;
    }

    if (npc->sensor_hit_right == true && npc->sensor_hit_left == true)
    {
        npc->cct.rotaton_pan += (180 + (random(90) - random(90)));
    }
    else if (npc->sensor_hit_right == true)
    {
        npc->cct.rotaton_pan += 45 + random(45);
    }
    else if (npc->sensor_hit_left == true)
    {
        npc->cct.rotaton_pan -= 45 + random(45);
    }

    // intaraction trace
    vec_set(&npc->sensor_ahead, vector(npc->sensor_distance + 4, 0, 0));
    vec_rotate(&npc->sensor_ahead, vector(npc->cct.rotaton_pan, 0, 0));
    vec_add(&npc->sensor_ahead, &ent->x);

    c_ignore(SWITCH_ITEM_GROUP, PROJECTILE_GROUP, PLAYER_GROUP, NPC_GROUP, SHOOT_THROUGH_GROUP, 0);
    npc->sensor_hit_ahead = ent_trace(ent, &ent->x, &npc->sensor_ahead, TRACE_FLAGS | ACTIVATE_SHOOT);

#ifdef AI_SHOW_SENSORS
    draw_point3d(&npc->sensor_right, COLOR_WHITE, 100, 1);
    draw_point3d(&npc->sensor_left, COLOR_WHITE, 100, 1);
    draw_point3d(&npc->sensor_ahead, COLOR_RED, 100, 1);
#endif
}

// rotate npc to the given target
void npc_rotate_to(ENTITY *ent, NPC *npc, VECTOR *pos)
{
    if (!ent || !npc)
    {
        error("Can't rotate npc to target, entity or it's structure doesn't exist!");
        return;
    }

    ANGLE temp_angle;
    vec_to_angle(&temp_angle, vec_diff(NULL, pos, &ent->x));
    npc->cct.rotaton_pan = temp_angle.pan;
}

// rotate to something using obstacle avoidance
void npc_rotate_to_with_avoidance(ENTITY *ent, NPC *npc, VECTOR *pos)
{
    // if we aren't looking for a new route
    // then we can look at the player !
    if (npc->route_find == false)
    {
        npc_rotate_to(ent, npc, pos);
    }
    else
    {
        // this is executed each half of a second
        // since fps_max is limited to 60
        if ((total_frames % 30) == 1)
        {
            // if we can see player, while finding new route
            // then we can chase him directly
            if (npc_is_target_visible(ent, npc) == true)
            {
                npc->route_timer = npc->route_def_time;
            }
        }

        // well.. it we are looking for a new route
        // then do that for a specific amount of time only !
        // then rotate back to player and try to rich him
        npc->route_timer += time_frame / 16;
        if (npc->route_timer >= npc->route_def_time)
        {
            npc->route_find = false;
            npc->route_timer -= npc->route_def_time;
        }
    }
}

// detect walls on explosions
void npc_check_walls(ENTITY *ent, VECTOR *from, VECTOR *to, var dmg)
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
    ent->OBJ_HEALTH -= damage + 32; // to make sure, that you will die, if very close

    // if your health is too low, then you need to spawn gibs
    if (ent->OBJ_HEALTH <= -20)
    {
        ent->OBJ_DEATH_TYPE = TYPE_SMASHED;
    }

    // push away
    VECTOR push_vec;
    vec_diff(&push_vec, &my_pos, &you_pos);
    vec_normalize(&push_vec, damage * 0.25);

    NPC *npc = get_npc(ent);
    vec_set(&npc->cct.abs_force, &push_vec);
    npc_go_to_state(my, npc, AI_PAIN_STATE);
}

// event function for all npcs
void npc_event_function()
{
    if (event_type == EVENT_PUSH)
    {
        // smashed by props ?
        if (you->OBJ_TYPE == TYPE_PROPS_SECRET)
        {
            // get props structure
            PROPS *props = get_props(you);
            NPC *npc = get_npc(my);

            // push us away
            vec_set(&npc->cct.push_force, vector(props->diff.x, props->diff.y, 0));

            // if we can perform check ?
            // means that door is almost closed (f.e.)
            if (you->OBJ_CHECK == true)
            {
                // check if we were smashed or not
                if (props_vs_npc_check(you, my, my->scale_x) == true)
                {
                    my->OBJ_HEALTH = -999;
                    my->OBJ_DEATH_TYPE = TYPE_SMASHED;
                }
            }
        }
    }

    if (event_type == EVENT_SHOOT)
    {
        // take damage from projectiles
        if (you->OBJ_TYPE == TYPE_PLAYER_MELEE || you->OBJ_TYPE == TYPE_PLAYER_BULLET)
        {
            my->OBJ_HEALTH -= you->OBJ_TAKE_DAMAGE;
            NPC *npc = get_npc(my);
            npc_go_to_state(my, npc, AI_PAIN_STATE);
            if (npc->is_triggered == false)
            {
                npc->target_ent = you;
                npc->is_triggered = true;
            }
        }

#ifdef FRIENDLY_FIRE
        // take damage from projectiles
        if (you->OBJ_TYPE == TYPE_NPC_MELEE || you->OBJ_TYPE == TYPE_NPC_BULLET)
        {
            my->OBJ_HEALTH -= you->OBJ_TAKE_DAMAGE;
            NPC *npc = get_npc(my);
            npc_go_to_state(my, npc, AI_PAIN_STATE);
        }
#endif

        // if hit by rocket ?
        // explode right now !
        if (you->OBJ_TYPE == TYPE_PLAYER_ROCKET)
        {
            my->OBJ_HEALTH = -999;
        }
    }

    if (event_type == EVENT_SCAN)
    {
        // if scan from any type of explosions
        if (you->OBJ_TYPE == TYPE_PLAYER_EXPLOSION || you->OBJ_TYPE == TYPE_PROPS_EXPLOSION)
        {
            // check for walls, push away from explosion etc
            npc_check_walls(my, &you->x, &my->x, you->OBJ_EXPLO_DAMAGE);
        }

#ifdef FRIENDLY_FIRE
        if (you->OBJ_TYPE == TYPE_NPC_EXPLOSION)
        {
            // check for walls, push away from explosion etc
            npc_check_walls(my, &you->x, &my->x, you->OBJ_EXPLO_DAMAGE);
        }
#endif
    }

    if (event_type == EVENT_DETECT)
    {
        NPC *npc = get_npc(my);

        // player ?
        if (you->OBJ_TYPE == TYPE_PLAYER && ent_is_alive(you) == true)
        {
            if (npc->is_triggered == false)
            {
                npc_is_you_visible(my, npc, you);
            }
        }

        // if we detect an npc near by and we are already trying to kill player
        if (you->OBJ_TYPE == TYPE_NPC)
        {
            if (npc->is_triggered == true)
            {
                NPC *friendly_npc = get_npc(you);
                if (friendly_npc->is_triggered == false)
                {
                    npc_is_you_visible(my, npc, you);
                }
            }
        }
    }
}