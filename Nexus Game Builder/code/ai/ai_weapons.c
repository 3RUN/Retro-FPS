
// create projectile
void npc_create_projectile(ENTITY *ent, NPC *npc)
{
    npc->animator.anim_attack = 1;
    switch (npc->animator.sprite_type)
    {
    case AI_PISTOL_WEAPON:
        ent_playsound(ent, weapon_pistol_shoot_ogg, weapon_npc_shoot_volume);
        var spd = npc_bullet_speed;
        var dmg = npc_bullet_damage;
        var acc = npc_pistol_accuracy;
        var siz = npc_bullet_size;
        bullet_create(&ent->x, vector(npc->cct.rotaton_pan, 0, 0), TYPE_NPC_BULLET, NPC_GROUP, dmg, spd, acc, siz);
        break;

    case AI_SHOTGUN_WEAPON:
        ent_playsound(ent, weapon_shotgun_shoot_ogg, weapon_npc_shoot_volume);
        var spd = npc_shell_speed;
        var dmg = npc_shell_damage;
        var acc = npc_shotgun_accuracy;
        var siz = npc_shell_size;
        var i = 0;
        for (i = 0; i < 8; i++)
        {
            bullet_create(&ent->x, vector(npc->cct.rotaton_pan, 0, 0), TYPE_NPC_BULLET, NPC_GROUP, dmg, spd, acc, siz);
        }
        break;

    case AI_CHAINGUN_WEAPON:
        ent_playsound(ent, weapon_chaingun_shoot_ogg, weapon_npc_shoot_volume);
        var spd = npc_bullet_speed;
        var dmg = npc_bullet_damage;
        var acc = npc_pistol_accuracy;
        var siz = npc_bullet_size;
        bullet_create(&ent->x, vector(npc->cct.rotaton_pan, 0, 0), TYPE_NPC_BULLET, NPC_GROUP, dmg, spd, acc, siz);
        break;

    case AI_ROCKETL_WEAPON:
        ent_playsound(ent, weapon_rocketl_shoot_ogg, weapon_npc_shoot_volume);
        var spd = npc_rocketl_speed;
        var dmg = 999;
        var siz = npc_rocketl_size;
        rocket_create(&ent->x, vector(npc->cct.rotaton_pan, 0, 0), TYPE_NPC_ROCKET, NPC_GROUP, dmg, spd, siz);
        break;
    }
}

// create melee attack
void npc_create_melee(ENTITY *ent, NPC *npc)
{
    npc->animator.anim_attack = 1;
    ent_playsound(ent, weapon_knife_stab_ogg, weapon_npc_shoot_volume);
    var dmg = npc->melee_damage;
    melee_create(&ent->x, vector(npc->cct.rotaton_pan, 0, 0), TYPE_NPC_MELEE, NPC_GROUP, dmg);
}