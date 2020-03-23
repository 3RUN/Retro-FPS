
// action used in WED
action ai_human_melee()
{
    level_enemies_total++; // plus one enemy on the level

    // correct our Z position
    my->z = WORLD_Z_POS;

    NPC *npc = register_npc(my);
    npc->sensor_distance = 16;
    npc->sensor_width = 8;
    npc->route_def_time = 1.5;
    npc->scan_range = 512;

    // movement
    npc->cct.movement_speed = human_melee_movement_speed;

    // unique parameters
    npc->animator.sprite_type = AI_SPRITE_HUMAN_MELEE;
    npc->attack_range = human_melee_attack_range;
    npc->weapon_type = AI_MELEE_WEAPON;
    npc->idle_def_time = human_melee_idle_def_time;
    npc->idle_def_random_time = human_melee_idle_def_random_time;
    npc->walk_def_time = human_melee_walk_def_time;
    npc->walk_def_random_time = human_melee_walk_def_random_time;
    npc->melee_attack_rate = human_melee_attack_rate;
    npc->melee_damage = npc_melee_def_damage;

    // not used for melee npcs
    npc->melee_range = npc->attack_range;
    npc->melee_approach_range = npc->attack_range;
    npc->fire_rate = 0;
    npc->attack_def_random_amount = 0;
    npc->dodge_def_time = 0;
    npc->dodge_def_random_time = 0;

    set(my, INVISIBLE | FLAG2); // in order to get alerted by other npcs
    vec_fill(&my->scale_x, 0.75);
    c_setminmax(my);
    ent_place_on_ground(my);
    npc->cct.fixed_z_pos = my->z;

    var bbox_x = biggest_bbox_x_side - 3;
    var bbox_y = biggest_bbox_y_side - 3;
    var bbox_z = biggest_bbox_z_side - 6;
    vec_set(&my->max_x, vector(bbox_x, bbox_y, bbox_z));
    vec_set(&my->min_x, vector(-bbox_x, -bbox_y, -bbox_z));

    my->OBJ_HEALTH = human_melee_health;
    my->OBJ_STATE = AI_IDLE_STATE;
    my->OBJ_TYPE = TYPE_NPC;
    my->OBJ_ALLOW_MOVE = true;

    my->group = NPC_GROUP;
    my->push = NPC_GROUP;

    my->emask |= (ENABLE_SHOOT | ENABLE_SCAN | ENABLE_DETECT | ENABLE_PUSH);
    my->event = npc_event_function;

    npc_create_visual_sprite(my, npc);
}