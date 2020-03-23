
// message init
void message_init()
{
    game_info_txt->font = message_font;
    layer_sort(game_info_txt, GUI_PLAYER_MESSAGE_LAYER);
}

// create message font
void message_font_create()
{
    message_font = font_create("Karma Suture [RUS by Daymarius]#48");
}

// show in game message
void show_message(STRING *str)
{
    game_text_fadeaway = false;
    game_text_counter = 0;
    str_cpy(message_str, str);
    str_cpy((game_info_txt->pstring)[0], message_str);
    set(game_info_txt, SHOW | TRANSLUCENT);
    game_info_txt->alpha = MESSAGE_ALPHA;
}

// hide current message
void hide_message()
{
    str_cpy((game_info_txt->pstring)[0], "");
    game_info_txt->alpha = 0;
    reset(game_info_txt, SHOW);
}

// updates all logic related to the in game messages
void message_logic_update()
{
    game_info_txt->pos_x = (screen_size.x / 2);
    game_info_txt->pos_y = (screen_size.y / 2) - 128;

    // game text counter
    if (game_text_fadeaway == false)
    {
        game_text_counter += time_frame / 16;
        if (game_text_counter >= MESSAGE_DELAY)
        {
            game_text_fadeaway = true;
        }
    }
    else
    {
        if (is(game_info_txt, SHOW))
        {
            game_info_txt->alpha -= MESSAGE_FADE_SPEED * time_step;
            if (game_info_txt->alpha <= 0)
            {
                reset(game_info_txt, SHOW);
            }
        }
    }
}