
// initialize all levels
void init_levels()
{
    level_setup(0, "map.wmb", "", 128, 1024, 10, 40);
    level_setup(1, "map2.wmb", "", 128, 1024, 2, 35);
}

// set level settings (such as fog, clipping etc)
void set_level_settings()
{
    vec_set(&d3d_lodfactor, vector(12.5, 25, 50));

    sun_light = 0;
    vec_set(&sun_angle, vector(0, 90, 0));

    camera->clip_near = 0.1;
    camera->clip_far = map[level_id].fog_end + 512;

    camera->fog_start = map[level_id].fog_start;
    camera->fog_end = map[level_id].fog_end;

    fog_color = 4;
    vec_set(&d3d_fogcolor4.blue, COLOR_FOG);
    vec_set(&sky_color.blue, COLOR_SKY);
}

// reset some global level variables
void level_reset()
{
    // stop sounds/music
    snd_stopall(4);
    music_stop();

    // reset gui
    gui_reset();
    
    // stop our timer
    level_timer_reset();

    // level isn't loaded any more
    level_is_loaded = false;
    level_secrets_found = 0;
    level_secrets_total = 0;
    level_gold_collected = 0;
    level_gold_total = 0;
    level_enemies_killed = 0;
    level_enemies_total = 0;
    game_state = GAME_LEVEL_LOADING;
}

// restart current level
void level_restart()
{
    if (game_state != GAME_LEVEL_RUNNING)
    {
        return;
    }
    level_load(level_id);
}

// load level with the given id
void level_load(var num)
{
    // don't allow to load twice at the same time
    if (proc_status(level_load) > 0)
    {
        return;
    }

    // no name was given for the level ?
    // don't allow for weird things to happen...
    if (str_len(map[level_id].map_name) <= 0)
    {
        diag("\nCRITICAL ERROR! No level name was given OR no level was setup to be loaded!");
        sys_exit(NULL);
        return; // terminate function as well
    }

    reset(camera, SHOW);

    level_reset();
    wait_for(level_reset);

    freeze_mode = true;
    level_load(map[level_id].map_name);
    freeze_mode = false;

    // level wasn't loaded ?
    if (!level_ent)
    {
        diag("\n\nCRITICAL ERROR! Level couldn't be loaded!\n");
        return;
    }

    set(level_ent, NOFILTER);
    level_ent->group = OBSTACLE_GROUP;
    level_ent->push = OBSTACLE_GROUP;

    set_level_settings();
    music_start();
    set(camera, SHOW);
}