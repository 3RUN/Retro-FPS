
// initialize all gui history related stuff
void gui_history_init()
{
    var i = 0;
    for (i = 0; i < MAX_GUI_HISTORY; i++)
    {
        gui_history_str[i] = str_create("");
        gui_history_txt[i] = txt_create(1, GUI_PLAYER_HISTORY_LAYER);
        gui_history_txt[i]->alpha = 100;
        gui_history_txt[i]->font = gui_history_font;
        set(gui_history_txt[i], TRANSLUCENT | OUTLINE | SHADOW);
    }
}

// create history fonts
void gui_history_font_create()
{
    gui_history_font = font_create("Karma Suture [RUS by Daymarius]#24");
}

// reset the history
void gui_history_reset()
{
    var i = 0;
    for (i = 0; i < MAX_GUI_HISTORY; i++)
    {
        reset(gui_history_txt[i], SHOW);
        gui_history_txt[i]->alpha = 0;
        str_cpy((gui_history_txt[i]->pstring)[0], "");
    }
}

// remove all strings and texts
void gui_history_remove_all()
{
    var i = 0;
    for (i = 0; i < MAX_GUI_HISTORY; i++)
    {
        if (gui_history_str[i])
        {
            ptr_remove(gui_history_str[i]);
        }
        if (gui_history_txt[i])
        {
            ptr_remove(gui_history_txt[i]);
        }
    }
}

// add text to the gui history
void gui_history_add_message(STRING *msg)
{
    var i = 0;
    for (i = MAX_GUI_HISTORY - 1; i > 0; i--)
    {
        if (is(gui_history_txt[i - 1], SHOW))
        {
            set(gui_history_txt[i], SHOW);
        }
        gui_history_txt[i]->alpha = gui_history_txt[i - 1]->alpha;
        str_cpy((gui_history_txt[i]->pstring)[0], (gui_history_txt[i - 1]->pstring)[0]);
        gui_history_timer[i] = gui_history_timer[i - 1];
    }
    gui_history_timer[0] = GUI_HISTORY_FADE_TIME;
    str_cpy((gui_history_txt[0]->pstring)[0], msg);
    gui_history_txt[0]->alpha = 100;
    set(gui_history_txt[0], SHOW);
}

// update gui history
void gui_history_update()
{
    var i = 0;
    for (i = 0; i < MAX_GUI_HISTORY; i++)
    {
        gui_history_txt[i]->pos_x = 4;
        gui_history_txt[i]->pos_y = 4 + (24 * i);

        if (is(gui_history_txt[i], SHOW))
        {
            gui_history_timer[i] -= time_frame / 16;
            if (gui_history_timer[i] <= 0)
            {
                gui_history_txt[i]->alpha -= 10 * time_step;
                if (gui_history_txt[i]->alpha <= 0)
                {
                    reset(gui_history_txt[i], SHOW);
                }
            }
        }
    }
}