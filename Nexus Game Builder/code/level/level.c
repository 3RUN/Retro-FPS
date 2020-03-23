
// setup parameters for the level with the given id
void level_setup(var id_, STRING *map_name_, STRING *music_, var fog_start_, var fog_end_, var score_m, var score_s)
{
    strcpy(map[id_].map_name, map_name_);
    strcpy(map[id_].music, music_);

    map[id_].fog_start = fog_start_;
    map[id_].fog_end = fog_end_;
    map[id_].minutes = score_m;
    map[id_].seconds = score_s;
}