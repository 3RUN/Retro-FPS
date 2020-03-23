
// get input from player
void camera_get_input(PLAYER *hero)
{
    hero->cam.angle.pan = cycle(hero->cam.angle.pan - mickey.x / 6.5 * cam_mouse_sensitivity, 0, 360);
#ifdef CAM_ALLOW_TILT
    hero->cam.angle.tilt = clamp(hero->cam.angle.tilt - mickey.y / 6.5 * cam_mouse_sensitivity, -90, 90);
#endif
    hero->cam.angle.roll = 0;
}

// animate camera
void camera_bobbing(PLAYER *hero)
{
    // if we are moving, calculate bobbing effects
    if (hero->cct.is_moving == 1 && hero->cct.moving_speed > 0.5)
    {
        // camera bob effect
        hero->cam.bob_speed = hero->cct.moving_speed * hero->cam.bob_speed_factor;
        hero->cam.bob = (hero->cam.bob + hero->cam.bob_speed * time_step) % 360;

        // weapon bob effect
        weapon_bob_y = sin(hero->cam.bob) * 0.5;
        weapon_bob_z = cos(hero->cam.bob * 2) * 0.25;
    }
    else
    {
        weapon_bob_y -= (weapon_bob_y - 0) * 0.1 * time_step;
        weapon_bob_z -= (weapon_bob_z - 0) * 0.1 * time_step;
    }
}

// reset bobbing effect
void camera_bobbing_reset(PLAYER *hero)
{
    if (hero->cam.bob < 180)
    {
        hero->cam.bob -= (hero->cam.bob - 0) * 0.5 * time_step;
    }
    if (hero->cam.bob > 180)
    {
        hero->cam.bob -= (hero->cam.bob - 182) * 0.5 * time_step;
    }
}

// handle recoil effect
void camera_recoil(ENTITY *ent, PLAYER *hero)
{
    // recoil power
    if (weapon_do_recoil == true && ent_is_alive(ent) == true)
    {
        hero->cam.recoil_vector.x = 0;
        hero->cam.recoil_vector.y = random(hero->cam.recoil_power * 2) - hero->cam.recoil_power;
        hero->cam.recoil_vector.z = hero->cam.recoil_power + random(hero->cam.recoil_power);
    }
    else
    {
        hero->cam.recoil_vector.x -= (hero->cam.recoil_vector.x - 0) * time_step;
        hero->cam.recoil_vector.y -= (hero->cam.recoil_vector.y - 0) * time_step;
        hero->cam.recoil_vector.z -= (hero->cam.recoil_vector.z - 0) * time_step;
    }

    hero->cam.recoil_vector.x = clamp(hero->cam.recoil_vector.x, -8, 8);
    hero->cam.recoil_vector.y = clamp(hero->cam.recoil_vector.y, -8, 8);
    hero->cam.recoil_vector.z = clamp(hero->cam.recoil_vector.z, -8, 8);

    hero->cam.recoil_arc = abs(hero->cam.recoil_vector.z);
    hero->cam.recoil_arc = clamp(hero->cam.recoil_arc, 0, 15);
    weapon_do_recoil = false;
}

// handle camera shaking effect (used for explosions and moving on platforms/elevators)
void camera_explosion_shake(PLAYER *hero)
{
    hero->cam.explo_power -= (hero->cam.explo_power - 0) * 0.1 * time_step;

    if (hero->cam.explo_power > 0.1)
    {
        if (random(1) > 0.5)
        {
            hero->cam.explo_vector.x = random(hero->cam.explo_power);
        }
        else
        {
            hero->cam.explo_vector.x = -random(hero->cam.explo_power);
        }
        if (random(1) > 0.5)
        {
            hero->cam.explo_vector.y = random(hero->cam.explo_power);
        }
        else
        {
            hero->cam.explo_vector.y = -random(hero->cam.explo_power);
        }
    }
    else
    {
        hero->cam.explo_vector.x -= (hero->cam.explo_vector.x - 0) * 0.5 * time_step;
        hero->cam.explo_vector.y -= (hero->cam.explo_vector.y - 0) * 0.5 * time_step;
    }
}

// handle camera damage effect
void camera_add_damage_effect(ENTITY *ent, PLAYER *hero, VECTOR *from)
{
    ANGLE temp_angle;
    vec_fill(&temp_angle, 0);
    vec_to_angle(&temp_angle, vec_diff(NULL, from, &ent->x));
    temp_angle.pan = ang(temp_angle.pan - camera->pan);

    // hit from the back:
    if (temp_angle.pan > 150 || temp_angle.pan < -150)
    {
        hero->cam.damage_offset.tilt -= 10 * time_step;
    }
    else if (temp_angle.pan < -30) // from the right
    {
        hero->cam.damage_offset.roll += 10 * time_step;
    }
    else if (temp_angle.pan > 30) // from the left
    {
        hero->cam.damage_offset.roll -= 10 * time_step;
    }
    else // from the front
    {
        if (random(1) > 0.5)
        {
            hero->cam.damage_offset.tilt += 10 * time_step;
        }
        else
        {
            hero->cam.damage_offset.tilt -= 10 * time_step;
        }
    }

    hero->cam.damage_offset.pan = clamp(hero->cam.damage_offset.pan, -10, 10);
    hero->cam.damage_offset.tilt = clamp(hero->cam.damage_offset.tilt, -10, 10);
    hero->cam.damage_offset.roll = clamp(hero->cam.damage_offset.roll, -10, 10);
}

// update camera damage effect
void camera_update_damage_effect(PLAYER *hero)
{
    hero->cam.damage_offset.pan -= ang(hero->cam.damage_offset.pan - 0) * 0.5 * time_step;
    hero->cam.damage_offset.tilt -= ang(hero->cam.damage_offset.tilt - 0) * 0.5 * time_step;
    hero->cam.damage_offset.roll -= ang(hero->cam.damage_offset.roll - 0) * 0.5 * time_step;
}

// update everything related to the camera
void camera_update(ENTITY *ent, PLAYER *hero)
{
    // alive?
    if (ent_is_alive(ent) == true)
    {
        // allowed to move?
        if (ent->OBJ_ALLOW_MOVE == true)
        {
            // get input from player
            camera_get_input(hero);

            // handle bobbing
            camera_bobbing(hero);
        }
    }
    else
    {
        // lower camera and tilt it a little bit upwards
        hero->cam.height -= (hero->cam.height - (-14)) * 0.5 * time_step;
        hero->cam.angle.tilt -= (hero->cam.angle.tilt - 5) * 0.5 * time_step;

        // reset bobbing effect
        camera_bobbing_reset(hero);
    }

    // handle camera effects
    camera_recoil(ent, hero);
    camera_explosion_shake(hero);
    camera_update_damage_effect(hero);

    // camera FOV
    camera->arc = hero->cam.fov - hero->cam.recoil_arc;
    camera->arc = clamp(camera->arc, 40, hero->cam.fov);

    // set camera angles
    camera->pan = hero->cam.angle.pan + hero->cam.damage_offset.pan;
    camera->tilt = hero->cam.angle.tilt + hero->cam.damage_offset.tilt;
    camera->roll = hero->cam.angle.roll + hero->cam.damage_offset.roll;

    var recoil_x = hero->cam.recoil_vector.x;
    var recoil_y = hero->cam.recoil_vector.y;
    var recoil_z = hero->cam.recoil_vector.z;

    var cam_bobbing = fsin(hero->cam.bob * 2, hero->cam.bob_z_offset);
    var cam_z_height = recoil_z + hero->cam.height - cam_bobbing;

    vec_set(&hero->cam.position, vector(recoil_x + hero->cam.explo_vector.x, recoil_y + hero->cam.explo_vector.y, cam_z_height));
    vec_rotate(&hero->cam.position, vector(hero->cam.angle.pan, 0, 0));
    vec_add(&hero->cam.position, &ent->x);
    vec_set(&camera->x, &hero->cam.position);
}