
// init game effect gui
void gui_effects_init()
{
    layer_sort(fading_effect_pan, GUI_PLAYER_PICKUP_LAYER);
    layer_sort(const_effect_pan, GUI_PLAYER_PICKUP_LAYER);
}

// perform pickup/damage etc effects
void gui_do_game_effect(COLOR *color)
{
    vec_set(&fading_effect_pan->blue, color);
    fading_effect_pan->alpha = EFFECT_ALPHA;
    set(fading_effect_pan, SHOW);
}

// do player death effect
void gui_player_dead_effect()
{
    vec_set(&const_effect_pan->blue, PLAYER_DAMAGE_COLOR);
    const_effect_pan->alpha = PLAYER_DEAD_ALPHA;
    set(const_effect_pan, SHOW);
}

// update effects
void gui_game_effects_update()
{
    fading_effect_pan->size_x = screen_size.x;
    fading_effect_pan->size_y = screen_size.y;

    if (is(fading_effect_pan, SHOW))
    {
        fading_effect_pan->alpha -= EFFECT_FADING_SPEED * time_step;
        if (fading_effect_pan->alpha <= 0)
        {
            reset(fading_effect_pan, SHOW);
        }
    }

    const_effect_pan->size_x = screen_size.x;
    const_effect_pan->size_y = screen_size.y;

    if (is(const_effect_pan, SHOW) && player_health > 0)
    {
        const_effect_pan->alpha -= CONST_EFFECT_FADING_SPEED * time_step;
        if (const_effect_pan->alpha <= 0)
        {
            reset(const_effect_pan, SHOW);
        }
    }
}