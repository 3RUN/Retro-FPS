
// player's info init function
void gui_player_info_init()
{
    layer_sort(health_pan, GUI_PLAYER_INFO_LAYER);
    layer_sort(ammo_pan, GUI_PLAYER_INFO_LAYER);
    pan_setdigits(health_pan, 0, 0, 0, "%0.f", player_font, 1, &player_health);
    pan_setdigits(ammo_pan, 0, 0, 0, "%0.f", player_font, 1, &player_ammo);
}

// create player's font
void gui_player_font_create()
{
    player_font = font_create("Karma Suture [RUS by Daymarius]#64");
}

// update player's info
void gui_player_info_update()
{
    health_pan->pos_x = 16;
    health_pan->pos_y = screen_size.y - 76;

    ammo_pan->pos_x = screen_size.x - 16;
    ammo_pan->pos_y = screen_size.y - 76;

    if (game_state == GAME_LEVEL_RUNNING)
    {
        if (weapon_id == PLAYER_WPN_KNIFE)
        {
            if (is(ammo_pan, SHOW))
            {
                reset(ammo_pan, SHOW);
            }
        }
        else
        {
            if (!is(ammo_pan, SHOW))
            {
                set(ammo_pan, SHOW);
            }
        }
    }
}

// show/hide info visibility
void gui_player_info_show(var show)
{
    if (show == false)
    {
        if (is(health_pan, SHOW))
        {
            reset(health_pan, SHOW);
        }
        if (is(ammo_pan, SHOW))
        {
            reset(ammo_pan, SHOW);
        }
    }
    else
    {
        if (!is(health_pan, SHOW))
        {
            set(health_pan, SHOW);
        }
        if (!is(ammo_pan, SHOW) && weapon_id != PLAYER_WPN_KNIFE)
        {
            set(ammo_pan, SHOW);
        }
    }
}