
// init level info
void gui_level_info_init()
{
    layer_sort(level_info_pan, GUI_LEVEL_INFO_LAYER);
    pan_setstring(level_info_pan, 0, 0, 0, info_title_font, level_complete_str);
    pan_setcolor(level_info_pan, 1, INFO_TITLE, INFO_TITLE_COLOR);

    STRING *empty_str = "";
    pan_setstring(level_info_pan, 0, 0, 0, info_detail_font, empty_str);
    pan_setstring(level_info_pan, 0, 0, 0, info_detail_font, empty_str);
    pan_setstring(level_info_pan, 0, 0, 0, info_detail_font, empty_str);
    pan_setstring(level_info_pan, 0, 0, 0, info_detail_font, empty_str);

    layer_sort(level_info_input_pan, GUI_LEVEL_INFO_LAYER);
    pan_setstring(level_info_input_pan, 0, 0, 0, info_input_font, press_to_continue_str);
    pan_setstring(level_info_input_pan, 0, 0, 24, info_restart_font, press_to_restart_str);
    pan_setcolor(level_info_input_pan, 1, INFO_INPUT_CONTINUE, INFO_INPUT_CONTINUE_COLOR);
    pan_setcolor(level_info_input_pan, 1, INFO_INPUT_RESTART, INFO_INPUT_RESTART_COLOR);

    layer_sort(level_info_background_pan, GUI_LEVEL_INFO_BACKGROUND_LAYER);
    vec_set(&level_info_background_pan->blue, COLOR_BLACK);
    level_info_background_pan->alpha = 85;
}

// create info elements
void gui_level_info_create(var num)
{
    snd_play(level_info_ogg, info_snd_volume, 0);

    switch (num)
    {
    case INFO_TIME:
        str_cpy(info_time_str, "");
        str_cat_num(info_time_str, "Time: %02.f : ", level_minutes);
        str_cat_num(info_time_str, "%02.f / ", level_seconds);
        str_cat_num(info_time_str, "%02.f : ", map[level_id].minutes);
        str_cat_num(info_time_str, "%02.f", map[level_id].seconds);
        pan_setstring(level_info_pan, INFO_TIME, 0, 96, info_detail_font, info_time_str);
        pan_setcolor(level_info_pan, 1, INFO_TIME, INFO_TIME_COLOR);
        break;

    case INFO_SECRET:
        str_cpy(info_secret_str, "");
        str_cat_num(info_secret_str, "Secrets found: %0.f / ", level_secrets_found);
        str_cat_num(info_secret_str, "%0.f", level_secrets_total);
        pan_setstring(level_info_pan, INFO_SECRET, 0, 144, info_detail_font, info_secret_str);
        pan_setcolor(level_info_pan, 1, INFO_SECRET, INFO_COLLECTABLES_COLOR);
        break;

    case INFO_GOLD:
        str_cpy(info_treasure_str, "");
        str_cat_num(info_treasure_str, "Treasures found: %0.f / ", level_gold_collected);
        str_cat_num(info_treasure_str, "%0.f", level_gold_total);
        pan_setstring(level_info_pan, INFO_GOLD, 0, 176, info_detail_font, info_treasure_str);
        pan_setcolor(level_info_pan, 1, INFO_GOLD, INFO_COLLECTABLES_COLOR);
        break;

    case INFO_ENEMIES:
        str_cpy(info_enemies_str, "");
        str_cat_num(info_enemies_str, "Enemies killed: %0.f / ", level_enemies_killed);
        str_cat_num(info_enemies_str, "%0.f", level_enemies_total);
        pan_setstring(level_info_pan, INFO_ENEMIES, 0, 208, info_detail_font, info_enemies_str);
        pan_setcolor(level_info_pan, 1, INFO_ENEMIES, INFO_ENEMIES_COLOR);
        break;
    }
}

// reset all info elements
void gui_level_info_reset()
{
    STRING *empty_str = "";
    pan_setstring(level_info_pan, 2, 0, 0, info_detail_font, empty_str);
    pan_setstring(level_info_pan, 3, 0, 0, info_detail_font, empty_str);
    pan_setstring(level_info_pan, 4, 0, 0, info_detail_font, empty_str);
    pan_setstring(level_info_pan, 5, 0, 0, info_detail_font, empty_str);

    reset(level_info_input_pan, SHOW);
    level_info_input_pan->alpha = 0;

    info_title_timer = 0;
    info_allow_showing_elements = false;
    info_timer = 0;
    info_counter = INFO_TITLE;
}

// create level info font
void gui_level_info_font_create()
{
    info_title_font = font_create("Karma Suture [RUS by Daymarius]#64");
    info_detail_font = font_create("Karma Suture [RUS by Daymarius]#32");
    info_input_font = font_create("Karma Suture [RUS by Daymarius]#24");
    info_restart_font = font_create("Karma Suture [RUS by Daymarius]#20");
}

// show level info
void gui_level_info_show(var show)
{
    if (show == true)
    {
        if (!is(level_info_pan, SHOW))
        {
            gui_history_reset(); // hide history if any on screen
            hide_message();      // hide messages if any on screen
            snd_play(level_complete_ogg, info_snd_volume, 0);
            set(level_info_pan, SHOW);
            set(level_info_input_pan, SHOW);
            set(level_info_background_pan, SHOW);
            level_info_input_pan->alpha = 0;
        }

        if (info_allow_showing_elements == false)
        {
            info_title_timer += time_frame / 16;
            if (info_title_timer >= info_title_def_time)
            {
                info_allow_showing_elements = true;
            }
        }

        if (info_allow_showing_elements == true && info_counter < INFO_ENEMIES)
        {
            info_timer += time_frame / 16;

            if (info_timer >= info_def_time)
            {
                info_counter += 1;
                gui_level_info_create(info_counter);
                info_timer %= info_def_time;
            }
        }
        else
        {
            // if all elements are visible ?
            if (info_counter >= INFO_ENEMIES)
            {
                // show press to continue or to restart panel here
                level_info_input_pan->alpha += INFO_INPUT_FADING_SPEED * time_step;
                if (level_info_input_pan->alpha > 100)
                {
                    level_info_input_pan->alpha %= 100;
                }

                // we can ask here to continue the game or to restart
                if (key_enter)
                {
                    // we are changing level, sooo...
                    // at the next level load we need to set
                    // all weapon parameters to the ones
                    // we had right at the end of previous level !
                    wpn_info_save = true;

                    level_id += 1;
                    game_state = GAME_LEVEL_LOADING;
                    level_load(level_id);
                }

                if (key_r)
                {
                    game_state = GAME_LEVEL_LOADING;
                    level_load(level_id);
                }
            }
        }
    }
    else
    {
        // hide level info and reset all it's stuff
        if (is(level_info_pan, SHOW))
        {
            gui_level_info_reset();
            reset(level_info_background_pan, SHOW);
            reset(level_info_pan, SHOW);
        }
    }
}

// update level info gui
void gui_level_info_update()
{
    level_info_pan->pos_x = (screen_size.x / 2);
    level_info_pan->pos_y = 128;

    level_info_input_pan->pos_x = (screen_size.x / 2);
    level_info_input_pan->pos_y = screen_size.y - 64;

    level_info_background_pan->size_x = screen_size.x;
    level_info_background_pan->size_y = screen_size.y;
}