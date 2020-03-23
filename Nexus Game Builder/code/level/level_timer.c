
// start level's timer (needed for level info at the end of each level)
void level_timer_start()
{
    level_milli_seconds += time_step / 16;
    if (level_milli_seconds > 1)
    {
        level_seconds += 1;
        level_milli_seconds -= 1;
    }

    if (level_seconds > 60)
    {
        level_minutes += 1;
        level_seconds -= 60;
    }
}

// reset timer
void level_timer_reset()
{
    level_milli_seconds = 0;
    level_seconds = 0;
    level_minutes = 0;
}