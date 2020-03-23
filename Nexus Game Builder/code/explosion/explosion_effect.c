
// explosion scan
void explosion_scan()
{
    set(my, PASSABLE | INVISIBLE);
    my->OBJ_EXPLO_RANGE = 256;
    my->OBJ_EXPLO_DAMAGE = 100;

    c_scan(&my->x, &my->pan, vector(360, 0, my->OBJ_EXPLO_RANGE), MOVE_FLAGS | SCAN_ENTS | SCAN_LIMIT);

    while (my)
    {
        if (my->skill1 > 4)
        {
            break;
        }
        my->skill1 += time_step;
        wait(1);
    }
    ent_delete(my);
}

// explosion from the player
void explosion_from_player_scan()
{
    my->OBJ_TYPE = TYPE_PLAYER_EXPLOSION;
    explosion_scan();
}

// explosion from the enemies
void explosion_from_npc_scan()
{
    my->OBJ_TYPE = TYPE_NPC_EXPLOSION;
    explosion_scan();
}

// explosion from the props
void explosion_from_props_scan()
{
    my->OBJ_TYPE = TYPE_PROPS_EXPLOSION;
    explosion_scan();
}

// animated explosion sprite on floor (f.e. for barrels)
void explosion_on_floor_sprite()
{
    vec_fill(&my->scale_x, 0.75);
    reset(my, DYNAMIC);
    set(my, PASSABLE | NOFILTER);
    my->ambient = 100;
    my->frame = 0;
    while (my)
    {
        my->skill1 += 1.5 * time_step;
        my->frame = my->skill1 + 1;
        if (my->skill1 > 10)
        {
            break;
        }

        // rotate towards the camera
        ent_rotate_to_camera(my);

        wait(1);
    }
    ent_delete(my);
}

// animated explosion sprite in the air (f.e. for rocket launcher)
void explosion_in_air_sprite()
{
    vec_fill(&my->scale_x, 0.75);
    reset(my, DYNAMIC);
    set(my, PASSABLE | NOFILTER);
    my->ambient = 100;
    my->frame = 0;
    while (my)
    {
        my->skill1 += 1.5 * time_step;
        my->frame = my->skill1 + 1;
        if (my->skill1 > 8)
        {
            break;
        }

        // rotate towards the camera
        ent_rotate_to_camera(my);

        wait(1);
    }
    ent_delete(my);
}

// explosion sound effect
// only 4 explosion snds at the time !
void explosion_snd()
{
    if (proc_status(explosion_snd) > 4 || vec_dist(&my->x, &camera->x) > 512)
    {
        ptr_remove(my);
        return;
    }

    reset(my, DYNAMIC);
    set(my, PASSABLE | INVISIBLE);
    var rnd = integer(random(3));
    if (rnd == 0)
    {
        my->OBJ_SND_HANDLE = ent_playsound(my, explosion01_ogg, explo_snd_volume);
    }
    if (rnd == 1)
    {
        my->OBJ_SND_HANDLE = ent_playsound(my, explosion02_ogg, explo_snd_volume);
    }
    if (rnd == 2)
    {
        my->OBJ_SND_HANDLE = ent_playsound(my, explosion03_ogg, explo_snd_volume);
    }

    while (my)
    {
        if (!snd_playing(my->OBJ_SND_HANDLE))
        {
            break;
        }
        wait(1);
    }

    ent_delete(my);
}

// create explosion at the given position
void explosion_create(VECTOR *pos, var is_on_ground, var type_)
{
    VECTOR spawn_pos;
    vec_set(&spawn_pos, pos);

    // who created this explosion?
    if (type_ == TYPE_PLAYER_ROCKET)
    {
        ent_create(NULL, &spawn_pos, explosion_from_player_scan);
    }
    else if (type_ == TYPE_NPC_ROCKET)
    {
        ent_create(NULL, &spawn_pos, explosion_from_npc_scan);
    }
    else if (type_ == TYPE_PROPS_BARREL)
    {
        ent_create(NULL, &spawn_pos, explosion_from_props_scan);
    }

    ent_create(NULL, &spawn_pos, explosion_snd);

    if (is_on_ground == true)
    {
        ent_create(explosion_on_floor_tga, vector(spawn_pos.x, spawn_pos.y, WORLD_Z_POS + 8), explosion_on_floor_sprite);
    }
    else
    {
        ent_create(explosion_in_air_tga, &spawn_pos, explosion_in_air_sprite);
    }
}