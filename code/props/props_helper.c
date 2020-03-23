
// barrel check for walls
void props_check_walls(ENTITY *ent, VECTOR *from, VECTOR *to, var dmg)
{
    // save input
    VECTOR you_pos;
    VECTOR my_pos;
    vec_set(&you_pos, from);
    vec_set(&my_pos, to);
    var temp_damage = dmg;

    wait(1); // because in called in event function !

    // if we are close enough ?
    if (vec_dist(&you_pos, &my_pos) > explo_default_range)
    {
        return;
    }

    c_ignore(SWITCH_ITEM_GROUP, PROJECTILE_GROUP, PLAYER_GROUP, NPC_GROUP, SHOOT_THROUGH_GROUP, 0);
    if (c_trace(&you_pos, &my_pos, TRACE_FLAGS))
    {
        return;
    }

    // calculate damage
    // 128 quants (by default), because it's the closes range
    var damage = (1 - (vec_dist(&you_pos, &my_pos) / explo_default_range)) * temp_damage;
    ent->OBJ_HEALTH -= damage + 32; // to make sure, that you will die, if very close

    // if your health is too low, then you need to spawn gibs
    if (ent->OBJ_HEALTH <= -20)
    {
        ent->OBJ_DEATH_TYPE = TYPE_SMASHED;
    }

    // push away
    VECTOR push_vec;
    vec_diff(&push_vec, &my_pos, &you_pos);
    vec_normalize(&push_vec, damage * 0.5);

    PROPS *props = get_props(ent);
    vec_set(&props->origin, &push_vec);
}

// init visual model for props
// ent - is the bbox model
// ghost - is the visual model, which will change it's skin
// bmap - bmap which will replace skin of ghost ent
void props_visual_ent(ENTITY *ent, ENTITY *ghost, BMAP *bmp)
{
    vec_set(&ghost->pan, &ent->pan);
    ent_cloneskin(ghost);
    ent_setskin(ghost, bmp, 1);
    set(ghost, PASSABLE | NOFILTER);
    ghost->material = mtl_z_write;
}

// check if entity needs to be smashed or not (f.e. by door on close etc)
var props_vs_npc_check(ENTITY *prop, ENTITY *npc, var scale)
{
    if (!prop)
    {
        diag("\nERROR! Can't perform props vs npc check, props doesn't exist!");
        return false;
    }

    if (!npc)
    {
        diag("\nERROR! Can't perform props vs npc check, npc doesn't exist!");
        return false;
    }

    // we need to check for collision ?
    if (prop->OBJ_CHECK == 1)
    {
        return is_cct_in_rect(npc, prop, scale);
        prop->OBJ_CHECK = 0;
    }
}