
// stop item pick up snd
void item_snd_stop()
{
    if (snd_playing(player_pick_snd_handle))
    {
        snd_stop(player_pick_snd_handle);
    }
}

// health pickup snd effect
void item_health_up_snd()
{
    item_snd_stop();
    player_pick_snd_handle = snd_play(item_health_ogg, item_pickup_snd_volume, 0);
}

// gold pickup snd effect
void item_gold_snd()
{
    item_snd_stop();
    player_pick_snd_handle = snd_play(item_gold_ogg, item_pickup_snd_volume, 0);
}

// ammo pickup snd effect
void item_ammo_snd()
{
    item_snd_stop();
    player_pick_snd_handle = snd_play(item_ammo_ogg, item_pickup_snd_volume, 0);
}

// key pickup snd effect
void item_key_snd()
{
    item_snd_stop();
    player_pick_snd_handle = snd_play(item_key_ogg, item_pickup_snd_volume, 0);
}

// init visual model for item
// ent - is the visual model, which will change it's skin
// bmap - bmap which will replace skin of ghost ent
void item_visual_ent(ENTITY *ent, BMAP *bmp)
{
    ent_cloneskin(ent);
    ent_setskin(ent, bmp, 1);
    set(ent, PASSABLE | NOFILTER);
    ent->material = mtl_z_write;
}

// visual sprites function
// create visual sprite for the item
void item_create_sprite()
{
    // create visual model
    my->parent = ent_create(props_decor_mdl, &my->x, NULL);

    // and set it's skin correctly
    switch (my->ID)
    {
    case ITEM_HEALTH_SMALL:
        item_visual_ent(my->parent, item_health_small_tga);
        break;

    case ITEM_HEALTH_BIG:
        item_visual_ent(my->parent, item_health_big_tga);
        break;

    case ITEM_FOOD_SMALL:
        if (random(1) > 0.5)
        {
            item_visual_ent(my->parent, item_food_small_a_tga);
        }
        else
        {
            item_visual_ent(my->parent, item_food_small_b_tga);
        }
        break;

    case ITEM_FOOD_BIG:
        item_visual_ent(my->parent, item_food_big_tga);
        break;

    case ITEM_GOLD_SMALL:
        var rnd = integer(random(3));
        if (rnd == 0)
        {
            item_visual_ent(my->parent, item_gold_small_a_tga);
        }
        if (rnd == 1)
        {
            item_visual_ent(my->parent, item_gold_small_b_tga);
        }
        if (rnd == 2)
        {
            item_visual_ent(my->parent, item_gold_small_c_tga);
        }
        break;

    case ITEM_GOLD_BIG:
        var rnd = integer(random(3));
        if (rnd == 0)
        {
            item_visual_ent(my->parent, item_gold_big_a_tga);
        }
        if (rnd == 1)
        {
            item_visual_ent(my->parent, item_gold_big_b_tga);
        }
        if (rnd == 2)
        {
            item_visual_ent(my->parent, item_gold_big_c_tga);
        }
        break;

    case ITEM_AMMO_PACK:
        item_visual_ent(my->parent, item_ammo_pack_tga);
        break;

    case ITEM_AMMO_BULLETS:
        item_visual_ent(my->parent, item_ammo_bullets_tga);
        break;

    case ITEM_AMMO_SHELLS:
        item_visual_ent(my->parent, item_ammo_shells_tga);
        break;

    case ITEM_AMMO_ROCKETS:
        item_visual_ent(my->parent, item_ammo_rockets_tga);
        break;

    case ITEM_KEY_RED:
        item_visual_ent(my->parent, item_key_red_tga);
        break;

    case ITEM_KEY_YELLOW:
        item_visual_ent(my->parent, item_key_yellow_tga);
        break;

    case ITEM_KEY_BLUE:
        item_visual_ent(my->parent, item_key_blue_tga);
        break;
    }
}

// pickup item
void item_pickup(ENTITY *ent, var num)
{
    // pickup depending on our ID
    switch (my->ID)
    {
    case ITEM_HEALTH_SMALL:
        if (ent->OBJ_HEALTH >= player_hp_max_for_small)
        {
            my->emask |= (ENABLE_PUSH);
            return;
        }
        ent->OBJ_HEALTH += item_health_small_add;
        ent->OBJ_HEALTH = clamp(ent->OBJ_HEALTH, 0, player_hp_max_for_small);
        item_health_up_snd();
        gui_do_game_effect(ITEM_HEALTH_COLOR);
        gui_history_add_message(item_health_small_str);
        break;

    case ITEM_HEALTH_BIG:
        if (ent->OBJ_HEALTH >= player_hp_max_for_big)
        {
            my->emask |= (ENABLE_PUSH);
            return;
        }
        ent->OBJ_HEALTH += item_health_big_add;
        ent->OBJ_HEALTH = clamp(ent->OBJ_HEALTH, 0, player_hp_max_for_big);
        item_health_up_snd();
        gui_do_game_effect(ITEM_HEALTH_COLOR);
        gui_history_add_message(item_health_big_str);
        break;

    case ITEM_FOOD_SMALL:
        if (ent->OBJ_HEALTH >= player_hp_max_for_small)
        {
            my->emask |= (ENABLE_PUSH);
            return;
        }
        ent->OBJ_HEALTH += item_food_small_add;
        ent->OBJ_HEALTH = clamp(ent->OBJ_HEALTH, 0, player_hp_max_for_small);
        item_health_up_snd();
        gui_do_game_effect(ITEM_HEALTH_COLOR);
        gui_history_add_message(item_food_small_str);
        break;

    case ITEM_FOOD_BIG:
        if (ent->OBJ_HEALTH >= player_hp_max_for_big)
        {
            my->emask |= (ENABLE_PUSH);
            return;
        }
        ent->OBJ_HEALTH += item_food_big_add;
        ent->OBJ_HEALTH = clamp(ent->OBJ_HEALTH, 0, player_hp_max_for_big);
        item_health_up_snd();
        gui_do_game_effect(ITEM_HEALTH_COLOR);
        gui_history_add_message(item_food_big_str);
        break;

    case ITEM_GOLD_SMALL:
        level_gold_collected += item_gold_small_add;
        item_gold_snd();
        gui_do_game_effect(ITEM_GOLD_COLOR);
        gui_history_add_message(item_gold_small_str);
        break;

    case ITEM_GOLD_BIG:
        level_gold_collected += item_gold_big_add;
        item_gold_snd();
        gui_do_game_effect(ITEM_GOLD_COLOR);
        gui_history_add_message(item_gold_big_str);
        break;

    case ITEM_AMMO_PACK:
        // already full ammo ?
        if (player_ammo_bullets >= wpn_bullets_max_ammo &&
            player_ammo_shells >= wpn_shells_max_ammo &&
            player_ammo_rockets >= wpn_rockets_max_ammo)
        {
            my->emask |= (ENABLE_PUSH);
            return;
        }

        // add ammo to all weapons
        wpn_add_ammo(&player_ammo_bullets, item_bullets_big_add, wpn_bullets_max_ammo);
        wpn_add_ammo(&player_ammo_shells, item_shells_big_add, wpn_shells_max_ammo);
        wpn_add_ammo(&player_ammo_rockets, item_rockets_big_add, wpn_rockets_max_ammo);

        item_ammo_snd();
        gui_do_game_effect(ITEM_AMMO_COLOR);
        gui_history_add_message(item_ammo_pack_str);
        break;

    case ITEM_AMMO_BULLETS:
        if (player_ammo_bullets >= wpn_bullets_max_ammo)
        {
            my->emask |= (ENABLE_PUSH);
            return;
        }

        // add bullets !
        wpn_add_ammo(&player_ammo_bullets, item_bullets_small_add, wpn_bullets_max_ammo);

        item_ammo_snd();
        gui_do_game_effect(ITEM_AMMO_COLOR);
        gui_history_add_message(item_ammo_bullets_str);
        break;

    case ITEM_AMMO_SHELLS:
        if (player_ammo_shells >= wpn_shells_max_ammo)
        {
            my->emask |= (ENABLE_PUSH);
            return;
        }

        // add shells !
        wpn_add_ammo(&player_ammo_shells, item_shells_small_add, wpn_shells_max_ammo);

        item_ammo_snd();
        gui_do_game_effect(ITEM_AMMO_COLOR);
        gui_history_add_message(item_ammo_shells_str);
        break;

    case ITEM_AMMO_ROCKETS:
        if (player_ammo_rockets >= wpn_rockets_max_ammo)
        {
            my->emask |= (ENABLE_PUSH);
            return;
        }

        // add rockets !
        wpn_add_ammo(&player_ammo_rockets, item_rockets_small_add, wpn_rockets_max_ammo);

        item_ammo_snd();
        gui_do_game_effect(ITEM_AMMO_COLOR);
        gui_history_add_message(item_ammo_rockets_str);
        break;

    case ITEM_KEY_RED:
        player_has_red_key = true;
        item_key_snd();
        gui_do_game_effect(ITEM_KEY_COLOR);
        gui_history_add_message(item_key_red_str);
        break;

    case ITEM_KEY_YELLOW:
        player_has_yellow_key = true;
        item_key_snd();
        gui_do_game_effect(ITEM_KEY_COLOR);
        gui_history_add_message(item_key_yellow_str);
        break;

    case ITEM_KEY_BLUE:
        player_has_blue_key = true;
        item_key_snd();
        gui_do_game_effect(ITEM_KEY_COLOR);
        gui_history_add_message(item_key_blue_str);
        break;
    }
    my->OBJ_HEALTH = -1;
}

// main event function for all items
void item_event_function()
{
    if (event_type == EVENT_PUSH)
    {
        // player is that you ?
        if (you->OBJ_TYPE != TYPE_PLAYER)
        {
            return;
        }

        // if you are dead
        if(ent_is_alive(you) == false)
        {
            return;
        }

        // only once !
        my->emask &= ~ENABLE_PUSH;

        // pickup function
        item_pickup(you, my->ID);
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

// function for all items
void item_init(var num)
{
    vec_set(&my->scale_x, vector(0.5, 0.5, 1));
    c_setminmax(my);
    ent_place_on_ground(my);
    set(my, POLYGON | INVISIBLE);

    my->group = SWITCH_ITEM_GROUP;
    my->push = SWITCH_ITEM_GROUP;

    my->ID = num;
    my->OBJ_HEALTH = 100;
    my->OBJ_TYPE = TYPE_PICKABLE_ITEM;

    item_create_sprite();

    my->emask |= (ENABLE_PUSH | ENABLE_FRAME);
    my->event = item_event_function;
}

// items (used in WED)
action item_health_small()
{
    item_init(ITEM_HEALTH_SMALL);
}

action item_health_big()
{
    item_init(ITEM_HEALTH_BIG);
}

action item_food_small()
{
    item_init(ITEM_FOOD_SMALL);
}

action item_food_big()
{
    item_init(ITEM_FOOD_BIG);
}

action item_gold_small()
{
    level_gold_total += item_gold_small_add;
    item_init(ITEM_GOLD_SMALL);
}

action item_gold_big()
{
    level_gold_total += item_gold_big_add;
    item_init(ITEM_GOLD_BIG);
}

action item_ammo_pack()
{
    item_init(ITEM_AMMO_PACK);
}

action item_ammo_bullets()
{
    item_init(ITEM_AMMO_BULLETS);
}

action item_ammo_shells()
{
    item_init(ITEM_AMMO_SHELLS);
}

action item_ammo_rockets()
{
    item_init(ITEM_AMMO_ROCKETS);
}

action item_key_red()
{
    item_init(ITEM_KEY_RED);
}

action item_key_yellow()
{
    item_init(ITEM_KEY_YELLOW);
}

action item_key_blue()
{
    item_init(ITEM_KEY_BLUE);
}