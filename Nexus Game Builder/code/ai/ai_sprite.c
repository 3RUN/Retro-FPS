
// create visual sprite for the given npc
void npc_create_visual_sprite(ENTITY *ent, NPC *npc)
{
    if (!ent)
    {
        diag("\nERROR! No visual sprite for given entity, it doesn't exist!");
        return;
    }

    ent->parent = ent_create(ai_mdl, &ent->x, NULL);
    vec_fill(&ent->parent->scale_x, 0.75);
    set(ent->parent, PASSABLE | NOFILTER);
    ent_cloneskin(ent->parent);
    ent->parent->material = mtl_z_write;

    // set skin depending on the type of the given npc
    switch (npc->weapon_type)
    {
    case AI_SPRITE_HUMAN_MELEE:
        ent_setskin(ent->parent, ai_human_melee_tga, 1);
        break;

    case AI_SPRITE_HUMAN_PISTOL:
        ent_setskin(ent->parent, ai_human_pistol_tga, 1);
        break;

    case AI_SPRITE_HUMAN_SHOTGUN:
        ent_setskin(ent->parent, ai_human_shotgun_tga, 1);
        break;

    case AI_SPRITE_HUMAN_CHAINGUN:
        ent_setskin(ent->parent, ai_human_chaingun_tga, 1);
        break;

    case AI_SPRITE_HUMAN_ROCKETL:
        ent_setskin(ent->parent, ai_human_rocketl_tga, 1);
        break;
    }
}

// handle everything related to the visual sprite (animations, position etc)
void npc_update_visual_sprite(ENTITY *ent, NPC *npc)
{
    if (ent->parent)
    {
        // state machine to animate the visual model
        if (ent->OBJ_STATE == AI_WALK_STATE || ent->OBJ_STATE == AI_CHASE_STATE || ent->OBJ_STATE == AI_RUN_FOR_MELEE || ent->OBJ_STATE == AI_DODGE_STATE)
        {
            npc->animator.anim_row = AI_ANIM_WALK;
            npc->animator.anim_frame += 0.5 * time_step;
            npc->animator.anim_frame -= 4;
        }
        else if (ent->OBJ_STATE == AI_MELEE_STATE)
        {
            npc->animator.anim_row = AI_ANIM_MELEE;
            if (npc->state_timer >= npc->state_def_time * 0.75)
            {
                npc->animator.anim_attack = 0;
            }
            npc->animator.anim_frame = npc->animator.anim_attack + 2;
        }
        else if (ent->OBJ_STATE == AI_ATTACK_STATE)
        {
            npc->animator.anim_row = AI_ANIM_ATTACK;
            if (npc->state_timer >= 0.1)
            {
                npc->animator.anim_attack = 0;
            }
            npc->animator.anim_frame = npc->animator.anim_attack;
        }
        else if (ent->OBJ_STATE == AI_PAIN_STATE)
        {
            npc->animator.anim_row = AI_ANIM_PAIN;
        }
        else if (ent->OBJ_STATE == AI_DEATH_STATE)
        {
            npc->animator.anim_row = AI_ANIM_DEATH;
        }
        else
        {
            npc->animator.anim_row = AI_ANIM_WALK;
        }

        ent->parent->v = 16 * integer(npc->animator.anim_row);
        ent->parent->u = 16 * integer(npc->animator.anim_frame);
        vec_set(&ent->parent->x, &ent->x);
        ent_rotate_to_camera(ent->parent);
    }
}