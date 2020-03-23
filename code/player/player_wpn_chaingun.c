
// initialize all chaingun parameters
void player_chaingun_init(PLAYER *hero, var col)
{
    hero->weapon[PLAYER_WPN_CHAINGUN].collected = col;
    hero->weapon[PLAYER_WPN_CHAINGUN].semiauto = false;
    hero->weapon[PLAYER_WPN_CHAINGUN].ammo = player_ammo_bullets;
    hero->weapon[PLAYER_WPN_CHAINGUN].fire_rate = 0.075;
    hero->weapon[PLAYER_WPN_CHAINGUN].recoil_strength = 1;
    hero->weapon[PLAYER_WPN_CHAINGUN].damage = player_bullet_damage;
    hero->weapon[PLAYER_WPN_CHAINGUN].accuracy = 1;
    hero->weapon[PLAYER_WPN_CHAINGUN].projectile_speed = player_bullet_projectile_speed;
    hero->weapon[PLAYER_WPN_CHAINGUN].animate = false;
    hero->weapon[PLAYER_WPN_CHAINGUN].anim_total_frames = 4;
    hero->weapon[PLAYER_WPN_CHAINGUN].snd = weapon_chaingun_shoot_ogg;
}

// chaingun shoot function
void player_chaingun_shoot(ENTITY *ent, PLAYER *hero)
{
    // create bullets here
    var spd = hero->weapon[PLAYER_WPN_CHAINGUN].projectile_speed;
    var dmg = hero->weapon[PLAYER_WPN_CHAINGUN].damage;
    var acc = hero->weapon[PLAYER_WPN_CHAINGUN].accuracy;
    var siz = player_bullet_projectile_size;
    bullet_create(&camera->x, &camera->pan, TYPE_PLAYER_BULLET, PLAYER_GROUP, dmg, spd, acc, siz);
}