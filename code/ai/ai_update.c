
// main function to update all npcs
void npc_update()
{
    ENTITY *ent;
    for (ent = ent_next(NULL); ent; ent = ent_next(ent))
    {
        if (ent->OBJ_TYPE == TYPE_NPC)
        {
            update_npc_logic(ent);
        }
    }
}