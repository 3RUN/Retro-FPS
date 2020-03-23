// create game font
void create_fonts()
{
    text_outline = 200;
    message_font_create();
    gui_history_font_create();
    gui_player_font_create();
    gui_level_info_font_create();
}

// show/hide in game gui
void game_gui_show(var show)
{
    gui_player_info_show(show);
}

// initialize gui
void gui_init()
{
    create_fonts();
    message_init();
    gui_history_init();
    gui_player_info_init();
    gui_effects_init();
    gui_level_info_init();
}

// reset gui
void gui_reset()
{
    hide_message();
    gui_history_reset();
}

// update whole game gui
void update_gui()
{
    message_logic_update();
    gui_history_update();
    gui_player_info_update();
    gui_game_effects_update();
    gui_level_info_update();

    if (game_state == GAME_LEVEL_RUNNING && player_health >= 1)
    {
        game_gui_show(true);
    }
    else
    {
        game_gui_show(false);
    }

    if (player_health <= 0 || game_state != GAME_LEVEL_RUNNING)
    {
    }
}