
// initialize all knife parameters
void player_knife_init(PLAYER *hero)
{
    hero->weapon[PLAYER_WPN_KNIFE].collected = true;
    hero->weapon[PLAYER_WPN_KNIFE].semiauto = true;
    hero->weapon[PLAYER_WPN_KNIFE].ammo = 1;
    hero->weapon[PLAYER_WPN_KNIFE].fire_rate = 0.15;
    hero->weapon[PLAYER_WPN_KNIFE].recoil_strength = 0.25;
    hero->weapon[PLAYER_WPN_KNIFE].damage = player_knife_damage;
    hero->weapon[PLAYER_WPN_KNIFE].accuracy = 0;
    hero->weapon[PLAYER_WPN_KNIFE].projectile_speed = WPN_MELEE_DISTANCE; // melee distance instead of projectile speed
    hero->weapon[PLAYER_WPN_KNIFE].animate = false;
    hero->weapon[PLAYER_WPN_KNIFE].anim_total_frames = 3.5;
    hero->weapon[PLAYER_WPN_KNIFE].snd = weapon_knife_stab_ogg;
}

// knife attack function
void player_knife_stab(ENTITY *ent, PLAYER *hero)
{
    // create melee attack trace here
    var dmg = hero->weapon[PLAYER_WPN_KNIFE].damage;
    melee_create(&camera->x, &camera->pan, TYPE_PLAYER_MELEE, PLAYER_GROUP, dmg);
}