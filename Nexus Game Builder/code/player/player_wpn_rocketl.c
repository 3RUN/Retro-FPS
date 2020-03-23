
// initialize all rocket launcher parameters
void player_rocketl_init(PLAYER *hero, var col)
{
    hero->weapon[PLAYER_WPN_ROCKETL].collected = col;
    hero->weapon[PLAYER_WPN_ROCKETL].semiauto = true;
    hero->weapon[PLAYER_WPN_ROCKETL].ammo = player_ammo_rockets;
    hero->weapon[PLAYER_WPN_ROCKETL].fire_rate = 0.7;
    hero->weapon[PLAYER_WPN_ROCKETL].recoil_strength = 2;
    hero->weapon[PLAYER_WPN_ROCKETL].damage = 999;
    hero->weapon[PLAYER_WPN_ROCKETL].accuracy = 0;
    hero->weapon[PLAYER_WPN_ROCKETL].projectile_speed = player_rocket_projectile_speed;
    hero->weapon[PLAYER_WPN_ROCKETL].animate = false;
    hero->weapon[PLAYER_WPN_ROCKETL].anim_total_frames = 4;
    hero->weapon[PLAYER_WPN_ROCKETL].snd = weapon_rocketl_shoot_ogg;
}

// rocket launcher shoot function
void player_rocketl_shoot(ENTITY *ent, PLAYER *hero)
{
    // create rocket here
    var spd = hero->weapon[PLAYER_WPN_ROCKETL].projectile_speed;
    var dmg = hero->weapon[PLAYER_WPN_ROCKETL].damage;
    var siz = player_rocket_projectile_size;
    rocket_create(&camera->x, &camera->pan, TYPE_PLAYER_ROCKET, PLAYER_GROUP, dmg, spd, siz);
}