
// function to set movement for the given npc
void npc_set_movement(ENTITY *ent, NPC *npc, var forward_, var backward_, var left_, var right_, var run_)
{
    // set input
    npc->cct.forward = forward_;
    npc->cct.backward = backward_;
    npc->cct.strafe_left = left_;
    npc->cct.strafe_right = right_;
    npc->cct.run = run_;

    cct_set_movement(ent, &npc->cct);
}

// function to stop all npc's movement
void npc_stop_movement(ENTITY *ent, NPC *npc)
{
    npc->cct.speed.x -= (npc->cct.speed.x - 0) * time_step;
    npc->cct.speed.y -= (npc->cct.speed.y - 0) * time_step;
    npc->cct.speed.z = 0;
    
    cct_stop_movement(ent, &npc->cct);
}

// function to handle all npc's movement
void npc_movement(ENTITY *ent, NPC *npc)
{
    cct_update_movement(ent, &npc->cct);
}