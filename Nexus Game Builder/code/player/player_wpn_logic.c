
// function used for all weapon sprites
void player_weapon_fnc()
{
    set(my, PASSABLE | NOFILTER | ZNEAR | INVISIBLE);
    vec_fill(&my->scale_x, 0.25);
    my->ambient = 100;
    my->OBJ_TYPE = TYPE_PLAYER_WEAPON;
    my->OBJ_STATE = PLAYER_WPN_DRAW_STATE;
}

// morph weapon to the one that we've equiped
void player_weapon_morph(PLAYER *hero)
{
    if (weapon_id == PLAYER_WPN_KNIFE)
    {
        ent_morph(hero->weapon_ent, player_view_knife_tga);
    }
    else if (weapon_id == PLAYER_WPN_PISTOL)
    {
        ent_morph(hero->weapon_ent, player_view_pistol_tga);
    }
    else if (weapon_id == PLAYER_WPN_SHOTGUN)
    {
        ent_morph(hero->weapon_ent, player_view_shotgun_tga);
    }
    else if (weapon_id == PLAYER_WPN_CHAINGUN)
    {
        ent_morph(hero->weapon_ent, player_view_chaingun_tga);
    }
    else if (weapon_id == PLAYER_WPN_ROCKETL)
    {
        ent_morph(hero->weapon_ent, player_view_rocketl_tga);
    }
}

// animate equiped weapon
void player_animate_weapons(PLAYER *hero)
{
    if (hero->weapon[weapon_id].animate == true)
    {
        hero->weapon[weapon_id].anim_frame += time_step;
        if (hero->weapon[weapon_id].anim_frame >= hero->weapon[weapon_id].anim_total_frames)
        {
            hero->weapon[weapon_id].animate = false;
            hero->weapon[weapon_id].anim_frame -= hero->weapon[weapon_id].anim_total_frames;
        }
    }
    else
    {
        hero->weapon[weapon_id].anim_frame = 0;
    }

    if (hero->weapon_ent)
    {
        hero->weapon_ent->frame = hero->weapon[weapon_id].anim_frame + 1;
    }
}

// switch to weapon by id
void player_switch_weapon_by_id(PLAYER *hero, var num)
{
    if (hero->weapon[num].collected == 1 && weapon_id != num)
    {
        // reset variables
        hero->weapon[weapon_id].animate = false;
        hero->weapon_draw_counter = 0;
        weapon_in_use = false;
        weapon_do_recoil = false;
        weapon_id = num;

        // reset current weapon
        if (hero->weapon_ent)
        {
            hero->weapon_ent->OBJ_STATE = PLAYER_WPN_HIDE_STATE;
            if (snd_playing(hero->weapon_ent->OBJ_SND_HANDLE))
            {
                snd_stop(hero->weapon_ent->OBJ_SND_HANDLE);
            }
        }
    }
}

// find better weapon
void player_weapon_find_better(PLAYER *hero, var num)
{
    // play 'dry shoot sound'
    snd_play(weapon_no_ammo_ogg, weapon_shoot_volume, 0);

    var i = 0;
    for (i = num; i >= 0; i--)
    {
        if (hero->weapon[i].collected == 1 && weapon_id != i)
        {
            player_switch_weapon_by_id(hero, i);
            return;
        }
    }
}

// save ammo and weapons at the beginning of the level
void player_weapons_save_at_level_start(PLAYER *hero)
{
    wpn_used_at_start = weapon_id;
    wpn_bullets_ammo_at_start = player_ammo_bullets;
    wpn_shells_ammo_at_start = player_ammo_shells;
    wpn_rocketl_ammo_at_start = player_ammo_rockets;
    wpn_pistol_collected_at_start = hero->weapon[PLAYER_WPN_PISTOL].collected;
    wpn_shotgun_collected_at_start = hero->weapon[PLAYER_WPN_SHOTGUN].collected;
    wpn_chaingun_collected_at_start = hero->weapon[PLAYER_WPN_CHAINGUN].collected;
    wpn_rocketl_collected_at_start = hero->weapon[PLAYER_WPN_ROCKETL].collected;
}

// save ammo and weapons at the end of the level
void player_weapons_save_at_level_end(PLAYER *hero)
{
    wpn_used_at_end = weapon_id;
    wpn_bullets_ammo_at_end = player_ammo_bullets;
    wpn_shells_ammo_at_end = player_ammo_shells;
    wpn_rocketl_ammo_at_end = player_ammo_rockets;
    wpn_pistol_collected_at_end = hero->weapon[PLAYER_WPN_PISTOL].collected;
    wpn_shotgun_collected_at_end = hero->weapon[PLAYER_WPN_SHOTGUN].collected;
    wpn_chaingun_collected_at_end = hero->weapon[PLAYER_WPN_CHAINGUN].collected;
    wpn_rocketl_collected_at_end = hero->weapon[PLAYER_WPN_ROCKETL].collected;
}

// get weapons from the previous level OR reset to default ones (from the level start)
void player_weapons_set_param(PLAYER *hero)
{
    // we moved to the next level ?
    // get weapons from the level start !
    if (wpn_info_save == true)
    {
        weapon_id = wpn_used_at_end;
        player_ammo_bullets = wpn_bullets_ammo_at_end;
        player_ammo_shells = wpn_shells_ammo_at_end;
        player_ammo_rockets = wpn_rocketl_ammo_at_end;
        player_knife_init(hero);
        player_pistol_init(hero, wpn_pistol_collected_at_end);
        player_shotgun_init(hero, wpn_shotgun_collected_at_end);
        player_chaingun_init(hero, wpn_chaingun_collected_at_end);
        player_rocketl_init(hero, wpn_rocketl_collected_at_end);
        wpn_info_save = false;
    }
    else // restarted current level ?
    {
        weapon_id = wpn_used_at_start;
        player_ammo_bullets = wpn_bullets_ammo_at_start;
        player_ammo_shells = wpn_shells_ammo_at_start;
        player_ammo_rockets = wpn_rocketl_ammo_at_start;
        player_knife_init(hero);
        player_pistol_init(hero, wpn_pistol_collected_at_start);
        player_shotgun_init(hero, wpn_shotgun_collected_at_start);
        player_chaingun_init(hero, wpn_chaingun_collected_at_start);
        player_rocketl_init(hero, wpn_rocketl_collected_at_start);
    }

    // save stuff !
    player_weapons_save_at_level_start(hero);
    player_weapon_morph(hero);
}

// setup basic weapon settings at start
void player_weapons_init(ENTITY *ent, PLAYER *hero)
{
    // reset weapon parameters
    weapon_fire_key_busy = false;
    weapon_in_use = false;
    hero->weapon_draw_counter = weapon_draw_time;

    // create visual weapon
    hero->weapon_ent = ent_create(player_view_knife_tga, &ent->x, player_weapon_fnc);

    // init all weapons here
    player_weapons_set_param(hero);
}

// update weapon's pos/angle
void player_weapon_view_pos(PLAYER *hero)
{
    var x_offset = 15;
    var z_offset = 16;

    VECTOR position;
    position.x = fcos(0.5 * camera->arc, x_offset) - (hero->cam.explo_vector.x * 0.15);
    position.y = -weapon_bob_y - (hero->cam.explo_vector.y * 0.15);
    position.z = 8 - fsin(0.5 * camera->arc, z_offset) * screen_size.y / screen_size.x + weapon_bob_z - (hero->weapon_draw_counter * 10);

    if (hero->weapon_ent)
    {
        vec_set(&hero->weapon_ent->x, &position);
        vec_rotate(&hero->weapon_ent->x, &camera->pan);
        vec_add(&hero->weapon_ent->x, &camera->x);

        ANGLE temp_angle;
        vec_set(&temp_angle, vector(180, 0, 0));
        ang_add(&temp_angle, &camera->pan);
        vec_set(&hero->weapon_ent->pan, &temp_angle);
    }
}

// switch weapons
void player_switch_weapons(PLAYER *hero)
{
    if (hero->weapon_1 && weapon_in_use == true)
    {
        player_switch_weapon_by_id(hero, PLAYER_WPN_KNIFE);
    }

    if (hero->weapon_2 && weapon_in_use == true)
    {
        player_switch_weapon_by_id(hero, PLAYER_WPN_PISTOL);
    }

    if (hero->weapon_3 && weapon_in_use == true)
    {
        player_switch_weapon_by_id(hero, PLAYER_WPN_SHOTGUN);
    }

    if (hero->weapon_4 && weapon_in_use == true)
    {
        player_switch_weapon_by_id(hero, PLAYER_WPN_CHAINGUN);
    }

    if (hero->weapon_5 && weapon_in_use == true)
    {
        player_switch_weapon_by_id(hero, PLAYER_WPN_ROCKETL);
    }
}

// main function to update all weapons
void player_weapons_update(ENTITY *ent, PLAYER *hero)
{
    // player is dead ?
    // OR finished the level ?
    // terminate
    if (ent_is_alive(ent) == false || game_state == GAME_LEVEL_INFO)
    {
        set(hero->weapon_ent, INVISIBLE);
        return;
    }

    // update recoil
    hero->cam.recoil_power = hero->weapon[weapon_id].recoil_strength;

    // update ammo
    hero->weapon[PLAYER_WPN_PISTOL].ammo = player_ammo_bullets;
    hero->weapon[PLAYER_WPN_CHAINGUN].ammo = player_ammo_bullets;
    hero->weapon[PLAYER_WPN_SHOTGUN].ammo = player_ammo_shells;
    hero->weapon[PLAYER_WPN_ROCKETL].ammo = player_ammo_rockets;
    player_ammo = hero->weapon[weapon_id].ammo;

    // state machine
    // drawing ?
    if (hero->weapon_ent->OBJ_STATE == PLAYER_WPN_DRAW_STATE)
    {
        // run once
        if (hero->weapon_snd_switch != PLAYER_WPN_DRAW_STATE)
        {
            // make us visible
            reset(hero->weapon_ent, INVISIBLE);

            // generic draw sound for all weapons
            snd_play(weapon_draw_ogg, weapon_draw_volume, 0);
            hero->weapon_snd_switch = PLAYER_WPN_DRAW_STATE;
        }

        hero->weapon_draw_counter -= time_frame / 8;
        if (hero->weapon_draw_counter <= 0.01)
        {
            weapon_in_use = true;
            hero->weapon_draw_counter = 0;
            hero->weapon_ent->OBJ_STATE = PLAYER_WPN_IDLE_STATE;
        }
    }

    // idle ?
    if (hero->weapon_ent->OBJ_STATE == PLAYER_WPN_IDLE_STATE)
    {
        // pressed fire button
        if (hero->shoot == true)
        {
            // we have ammo left ?
            if (hero->weapon[weapon_id].ammo >= 1)
            {
                // fully automatic weapon ?
                if (hero->weapon[weapon_id].semiauto == false)
                {
                    weapon_do_recoil = true;
                    weapon_fire_key_busy = true;
                    hero->weapon_ent->OBJ_TIMER = 0;
                    hero->weapon_ent->OBJ_STATE = PLAYER_WPN_SHOOT_STATE;
                }
                else
                {
                    // if this is semiautomatic weapon, wait for it to become 'not busy'
                    // means, till player releases the shoot button
                    if (weapon_fire_key_busy == false)
                    {
                        weapon_do_recoil = true;
                        weapon_fire_key_busy = true;
                        hero->weapon_ent->OBJ_TIMER = 0;
                        hero->weapon_ent->OBJ_STATE = PLAYER_WPN_SHOOT_STATE;
                    }
                }
            }
            else
            {
                // switch for to better weapon
                player_weapon_find_better(hero, weapon_id);
            }
        }
        else
        {
            weapon_fire_key_busy = false;
        }

        // run once
        if (hero->weapon_snd_switch != PLAYER_WPN_IDLE_STATE)
        {
            hero->weapon_snd_switch = PLAYER_WPN_IDLE_STATE;
        }
    }

    // shooting delay ?
    if (hero->weapon_ent->OBJ_STATE == PLAYER_WPN_SHOOT_STATE)
    {
        // not holding down the fire button ?
        // then realese the switch
        if (hero->shoot == false && hero->weapon[weapon_id].semiauto == true)
        {
            weapon_fire_key_busy = false;
        }

        if (hero->weapon_snd_switch != PLAYER_WPN_SHOOT_STATE)
        {
            // other weapons
            if (weapon_id != PLAYER_WPN_KNIFE)
            {
                // decrease ammo here
                if (weapon_id == PLAYER_WPN_PISTOL || weapon_id == PLAYER_WPN_CHAINGUN)
                {
                    player_ammo_bullets -= 1;
                }
                else if (weapon_id == PLAYER_WPN_SHOTGUN)
                {
                    player_ammo_shells -= 1;
                }
                else if (weapon_id == PLAYER_WPN_ROCKETL)
                {
                    player_ammo_rockets -= 1;
                }
            }

            // play shooting sound
            if (hero->weapon[weapon_id].snd)
            {
                hero->weapon_ent->OBJ_SND_HANDLE = snd_play(hero->weapon[weapon_id].snd, weapon_shoot_volume, 0);
            }

            // animate
            hero->weapon[weapon_id].animate = true;
            hero->weapon[weapon_id].anim_frame = 0;

            // change trace indicator to shoot !
            ent->OBJ_C_INDICATOR = C_SHOOT;

            // call shooting function here
            if (weapon_id == PLAYER_WPN_KNIFE)
            {
                player_knife_stab(ent, hero);
            }
            else if (weapon_id == PLAYER_WPN_PISTOL)
            {
                player_pistol_shoot(ent, hero);
            }
            else if (weapon_id == PLAYER_WPN_SHOTGUN)
            {
                player_shotgun_shoot(ent, hero);
            }
            else if (weapon_id == PLAYER_WPN_CHAINGUN)
            {
                player_chaingun_shoot(ent, hero);
            }
            else if (weapon_id == PLAYER_WPN_ROCKETL)
            {
                player_rocketl_shoot(ent, hero);
            }

            hero->weapon_snd_switch = PLAYER_WPN_SHOOT_STATE;
        }

        hero->weapon_ent->OBJ_TIMER += time_frame / 16;
        while (hero->weapon_ent->OBJ_TIMER >= hero->weapon[weapon_id].fire_rate)
        {
            weapon_do_recoil = false;
            hero->weapon_ent->OBJ_STATE = PLAYER_WPN_IDLE_STATE;
            hero->weapon_ent->OBJ_TIMER -= hero->weapon[weapon_id].fire_rate;
        }
    }

    // hide ?
    if (hero->weapon_ent->OBJ_STATE == PLAYER_WPN_HIDE_STATE)
    {
        if (hero->weapon_snd_switch != PLAYER_WPN_HIDE_STATE)
        {
            // holster sound here
            snd_play(weapon_holster_ogg, weapon_draw_volume, 0);

            hero->weapon_snd_switch = PLAYER_WPN_HIDE_STATE;
        }

        hero->weapon_draw_counter += time_frame / 8;
        if (hero->weapon_draw_counter >= weapon_draw_time)
        {
            // activate weapon
            reset(hero->weapon_ent, INVISIBLE);
            hero->weapon_ent->OBJ_TIMER = 0;
            hero->weapon_ent->OBJ_STATE = PLAYER_WPN_DRAW_STATE;
            player_weapon_morph(hero);
            hero->weapon_draw_counter = weapon_draw_time;
        }
    }

    // switch weapons
    player_switch_weapons(hero);

    // handle all weapon animations
    player_animate_weapons(hero);

    // update weapon's position on screen
    player_weapon_view_pos(hero);
}