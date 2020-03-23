
// register player on the level
PLAYER *register_player_structure(ENTITY *ent)
{
    if (!ent)
    {
        error("Can't register player, entity doesn't exist!");
        return NULL;
    }

    PLAYER *hero = sys_malloc(sizeof(PLAYER));
    ent->OBJ_STRUCT = hero;
    return hero;
}

// get player's structure from the given entity
PLAYER *get_player_structure(ENTITY *ent)
{
    if (!ent)
    {
        error("Can't get player's structure! Entity doesn't exist.");
        return NULL;
    }

    if (ent->OBJ_STRUCT == 0)
    {
        error("Can't get player's structure! It doesn't exist.");
        return NULL;
    }

    PLAYER *hero = ent->OBJ_STRUCT;
    return hero;
}

// unregister/delete player from the level
var delete_player_structure(ENTITY *ent)
{
    if (!ent)
    {
        error("Can't free player's structure from memory, entity doesn't exist!");
        return false;
    }

    PLAYER *hero = get_player_structure(ent);

    if (!hero)
    {
        error("Can't free player's structure from memory, couldn't get pointer from entities OBJ_STRUCT skill!");
        return false;
    }

    ptr_remove(hero->weapon_ent);
    sys_free(hero);
    return true;
}