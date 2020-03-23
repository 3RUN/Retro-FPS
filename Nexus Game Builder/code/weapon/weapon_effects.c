
// impact sounds
// MAX 4 sounds at the same time !
void projectie_impact_snd()
{
    if (proc_status(projectie_impact_snd) > 4 || vec_dist(&my->x, &camera->x) > 128)
    {
        ptr_remove(my);
        return;
    }

    set(my, PASSABLE | INVISIBLE);

    var rnd = integer(random(3));
    if (rnd == 0)
    {
        my->OBJ_SND_HANDLE = ent_playsound(my, weapon_impact01_ogg, projectile_impact_snd_volume);
    }
    if (rnd == 1)
    {
        my->OBJ_SND_HANDLE = ent_playsound(my, weapon_impact02_ogg, projectile_impact_snd_volume);
    }
    if (rnd == 2)
    {
        my->OBJ_SND_HANDLE = ent_playsound(my, weapon_impact03_ogg, projectile_impact_snd_volume);
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

// impact animated sprite
void projectie_impact_sprite()
{
    vec_fill(&my->scale_x, 0.5);
    reset(my, DYNAMIC);
    set(my, PASSABLE | NOFILTER);
    my->ambient = 100;
    my->frame = 0;

    while (my)
    {
        my->skill1 += 0.5 * time_step;
        my->frame = my->skill1 + 1;
        if (my->skill1 > 4)
        {
            break;
        }

        // rotate towards the camera
        ent_rotate_to_camera(my);

        wait(1);
    }
    ent_delete(my);
}

// function to handle impact effects
void projectile_impact_fx(var num, VECTOR *hit_vector, VECTOR *surf_angle)
{
    VECTOR temp_vec;
    VECTOR impact_vec;
    vec_set(&impact_vec, vector(0.5, 0, 0));
    vec_to_angle(&temp_vec, surf_angle);
    vec_rotate(&impact_vec, &temp_vec);
    vec_add(&impact_vec, hit_vector);

    // play impact sound effect
    ent_create(NULL, hit_vector, projectie_impact_snd);

    // hit something alive ?
    if (num == IMPCT_ALIVE)
    {
        ent_create(blood_impact_tga, &impact_vec, projectie_impact_sprite);
    }
    else // hit something static
    {
        ent_create(bullet_impact_tga, &impact_vec, projectie_impact_sprite);
    }
}

// handle impact on different surfaces
void projectile_impact_function(ENTITY *ent)
{
    if (ent)
    {
        // we hit player ?
        if (ent->OBJ_TYPE == TYPE_PLAYER)
        {
            VECTOR temp_vec;
            vec_set(&temp_vec, vector(1, random(4) - 2, random(4) - 2));
            vec_rotate(&temp_vec, &camera->pan);
            vec_add(&temp_vec, &hit->x);
            projectile_impact_fx(IMPCT_ALIVE, &temp_vec, &normal);
        }
        else if (ent->OBJ_TYPE == TYPE_NPC) // hit enemy
        {
            projectile_impact_fx(IMPCT_ALIVE, &hit->x, &normal);
        }
        else // hit something static
        {
            projectile_impact_fx(IMPCT_STATIC, &hit->x, &normal);
        }
    }
    else
    {
        // hit something static
        projectile_impact_fx(IMPCT_STATIC, &hit->x, &normal);
    }
}