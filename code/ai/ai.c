
// register and initializes new npc
// and save it's pointer into given entity's obj_struct skill
NPC *register_npc(ENTITY *ent)
{
    if (!ent)
    {
        diag("\nERROR! Can't register npc! Entity doesn't exist!");
        return NULL;
    }

    if (ent->OBJ_STRUCT != 0)
    {
        diag("\nERROR! Npc already exists for given entity!");
        return get_npc(ent);
    }

    NPC *npc = sys_malloc(sizeof(NPC));
    init_npc(ent, npc);
    ent->OBJ_STRUCT = npc;
    return npc;
}

// initialize all major variables for the given npc
// this function called inside of register_npc right after creating new npc
void init_npc(ENTITY *ent, NPC *npc)
{
    npc->cct.rotaton_pan = ent->pan;
    npc->cct.movement_speed = 1;
    npc->cct.walk_speed_factor = 1;
    npc->cct.run_speed_factor = 2;
    npc->accuracy = 20; // this could be changed individually to each npc type
    npc->sensor_distance = 16;
    npc->sensor_width = 8;
    npc->route_def_time = 1.5;
    npc->scan_range = 1024;
}

// returns pointer of the npc from given entity's obj_struct skill
NPC *get_npc(ENTITY *ent)
{
    if (!ent)
    {
        diag("\nERROR! Can't get npc! Entity doesn't exist.");
        return NULL;
    }

    if (ent->OBJ_STRUCT == 0)
    {
        diag("\nERROR! Can't get npc! It doesn't exist.");
        return NULL;
    }

    NPC *npc = ent->OBJ_STRUCT;
    return npc;
}

// removes npc from the memory
// pointer is taken from given entity's obj_struct skill
void delete_npc(ENTITY *ent)
{
    if (!ent)
    {
        diag("\nERROR! Can't free npc! Entity doesn't exist");
        return false;
    }

    NPC *npc = get_npc(ent);

    if (!npc)
    {
        diag("\nERROR! Can't free npc! It already doesn't exist.");
        return false;
    }

    delete_npc(npc);
    return true;
}

// remove given npc from the memory
void delete_npc(NPC *npc)
{
    npc->target_ent = NULL;
    sys_free(npc);
}