
// update all props in this function
void props_update()
{
    ENTITY *ent;
    for (ent = ent_next(NULL); ent; ent = ent_next(ent))
    {
        if (ent->OBJ_TYPE == TYPE_PROPS_DOOR)
        {
            door_update(ent);
        }

        if (ent->OBJ_TYPE == TYPE_PROPS_SECRET)
        {
            secret_wall_update(ent);
        }

        if (ent->OBJ_TYPE == TYPE_PROPS_BARREL)
        {
            barrel_update(ent);
        }
    }
}