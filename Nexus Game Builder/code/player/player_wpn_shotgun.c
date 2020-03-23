
// initialize all shotgun parameters
void player_shotgun_init(PLAYER *hero, var col)
{
    hero->weapon[PLAYER_WPN_SHOTGUN].collected = col;
    hero->weapon[PLAYER_WPN_SHOTGUN].semiauto = true;
    hero->weapon[PLAYER_WPN_SHOTGUN].ammo = player_ammo_shells;
    hero->weapon[PLAYER_WPN_SHOTGUN].fire_rate = 0.75;
    hero->weapon[PLAYER_WPN_SHOTGUN].recoil_strength = 2;
    hero->weapon[PLAYER_WPN_SHOTGUN].damage = player_shell_damage;
    hero->weapon[PLAYER_WPN_SHOTGUN].accuracy = 4;
    hero->weapon[PLAYER_WPN_SHOTGUN].projectile_speed = player_shell_projectile_speed;
    hero->weapon[PLAYER_WPN_SHOTGUN].animate = false;
    hero->weapon[PLAYER_WPN_SHOTGUN].anim_total_frames = 8;
    hero->weapon[PLAYER_WPN_SHOTGUN].snd = weapon_shotgun_shoot_ogg;
}

// shotgun shoot function
void player_shotgun_shoot(ENTITY *ent, PLAYER *hero)
{
    // create bullets here
    var spd = hero->weapon[PLAYER_WPN_SHOTGUN].projectile_speed;
    var dmg = hero->weapon[PLAYER_WPN_SHOTGUN].damage;
    var acc = hero->weapon[PLAYER_WPN_SHOTGUN].accuracy;
    var siz = player_shell_projectile_size;
    var i = 0;
    for (i = 0; i < 8; i++)
    {
        bullet_create(&camera->x, &camera->pan, TYPE_PLAYER_BULLET, PLAYER_GROUP, dmg, spd, acc, siz);
    }
}