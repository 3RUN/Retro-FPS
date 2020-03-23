#ifndef _GUI_GAME_EFFECTS_H_
#define _GUI_GAME_EFFECTS_H_

// effect consts
#define EFFECT_ALPHA 75
#define EFFECT_FADING_SPEED 16
#define MUSHROOM_EFFECT_ALPHA 50
#define PLAYER_DEAD_ALPHA 50
#define CONST_EFFECT_FADING_SPEED 16

// effect colors
#define PLAYER_DAMAGE_COLOR vector(28, 4, 246)

PANEL *fading_effect_pan =
{
    alpha = 100;
    flags = LIGHT | TRANSLUCENT;
}

PANEL *const_effect_pan =
{
    alpha = 100;
    flags = LIGHT | TRANSLUCENT;
}

// init game effect gui
void gui_effects_init();

// perform pickup/damage etc effects
void gui_do_game_effect(COLOR *color);

// do player death effect
void gui_player_dead_effect();

// update effects
void gui_game_effects_update();

#endif