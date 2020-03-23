
// initialize all pistol parameters
void player_pistol_init(PLAYER *hero, var col)
{
    hero->weapon[PLAYER_WPN_PISTOL].collected = col;
    hero->weapon[PLAYER_WPN_PISTOL].semiauto = true;
    hero->weapon[PLAYER_WPN_PISTOL].ammo = player_ammo_bullets;
    hero->weapon[PLAYER_WPN_PISTOL].fire_rate = 0.15;
    hero->weapon[PLAYER_WPN_PISTOL].recoil_strength = 1.5;
    hero->weapon[PLAYER_WPN_PISTOL].damage = player_bullet_damage;
    hero->weapon[PLAYER_WPN_PISTOL].accuracy = 1;
    hero->weapon[PLAYER_WPN_PISTOL].projectile_speed = player_bullet_projectile_speed;
    hero->weapon[PLAYER_WPN_PISTOL].animate = false;
    hero->weapon[PLAYER_WPN_PISTOL].anim_total_frames = 4;
    hero->weapon[PLAYER_WPN_PISTOL].snd = weapon_pistol_shoot_ogg;
}

// pistol shoot function
void player_pistol_shoot(ENTITY *ent, PLAYER *hero)
{
    // create bullets here
    var spd = hero->weapon[PLAYER_WPN_PISTOL].projectile_speed;
    var dmg = hero->weapon[PLAYER_WPN_PISTOL].damage;
    var acc = hero->weapon[PLAYER_WPN_PISTOL].accuracy;
    var siz = player_bullet_projectile_size;
    bullet_create(&camera->x, &camera->pan, TYPE_PLAYER_BULLET, PLAYER_GROUP, dmg, spd, acc, siz);
}