#ifndef _PLAYER_H_
#define _PLAYER_H_

// enable/disable camera tilt angle
//#define CAM_ALLOW_TILT

// enable/disable GOD MODE
#define PLAYER_IMMORTAL

// weapon types
#define PLAYER_WPN_KNIFE 0
#define PLAYER_WPN_PISTOL 1
#define PLAYER_WPN_SHOTGUN 2
#define PLAYER_WPN_CHAINGUN 3
#define PLAYER_WPN_ROCKETL 4

// weapon state machine
#define PLAYER_WPN_WAIT_STATE 0
#define PLAYER_WPN_DRAW_STATE 1
#define PLAYER_WPN_IDLE_STATE 2
#define PLAYER_WPN_SHOOT_STATE 3
#define PLAYER_WPN_HIDE_STATE 4

// player's stuff
var player_health = 0;             // player's current health
var player_always_run = false;     // true - if we always run, otherwise - false
var player_allow_move = false;     // true - if player is allowed to move, otherwise - false
var player_snd_volume = 75;        // volume for player made sound effects
var player_pick_snd_handle = 0;    // handle for player's pickup sound effects
var player_has_red_key = false;    // true if player has red key, otherwise - false
var player_has_yellow_key = false; // same as above for yellow key
var player_has_blue_key = false;   // same as above for blue key

// camera stuff
var cam_mouse_sensitivity = 1; // mouse sensitivity
var cam_fov = 95;              // camera default fov value

// player's weapon stuff
var player_knife_damage = 25;             // default knife damage
var player_ammo = 0;                      // stores equiped weapon's ammo
var player_ammo_bullets = 20;             // total amount of bullets
var player_bullet_damage = 15;            // default damage per bullet
var player_bullet_projectile_size = 0.25; // size for fired bullets
var player_bullet_projectile_speed = 100; // default speed for bullets
var player_ammo_shells = 0;               // total amount of shells
var player_shell_damage = 15;             // default damage per shotgun projectile
var player_shell_projectile_size = 0.5;   // size for fired shotgun bullets
var player_shell_projectile_speed = 65;   // default speed for shotgun bullets
var player_ammo_rockets = 0;              // total amount of rockets
var player_rocket_projectile_size = 0.75; // size for fired rockets
var player_rocket_projectile_speed = 45;  // default speed for rockets
var weapon_id = PLAYER_WPN_KNIFE;         // currently equiped weapon's ID
var weapon_bob_y = 0;                     // weapon's sway effect (left/right)
var weapon_bob_z = 0;                     // weapon's sway effect (up/down)
var weapon_do_recoil = false;             // true - if we need to have recoil effect, otherwise - false
var weapon_in_use = false;                // true - if player's has equiped weapon, otherwise - false
var weapon_fire_key_busy = false;         // true - if fire button is busy, otherwise - false
var weapon_draw_volume = 25;              // volume for player's weapon drawing sound effect
var weapon_shoot_volume = 65;             // volume for player's weapon shoot sound effect
var weapon_draw_time = 0.25;              // default drawing time for weapons

// variables to save weapons at start of the level and at the end of it
var wpn_info_save = false;                   // true - if we need to save weapons info at level change, otherwise false
var wpn_used_at_start = PLAYER_WPN_KNIFE;    // start by default with knife
var wpn_used_at_end = PLAYER_WPN_KNIFE;      // same as above (by default)
var wpn_pistol_collected_at_start = false;   // if true, then pistol was collected, otherwise - false
var wpn_pistol_collected_at_end = false;     // same as above (by default)
var wpn_shotgun_collected_at_start = false;  // if true, then shotgun was collected, otherwise - false
var wpn_shotgun_collected_at_end = false;    // same as above (by default)
var wpn_chaingun_collected_at_start = false; // if true, then chaingun was collected, otherwise - false
var wpn_chaingun_collected_at_end = false;   // same as above (by default)
var wpn_rocketl_collected_at_start = false;  // if true, then rocket launcher was collected, otherwise - false
var wpn_rocketl_collected_at_end = false;    // same as above (by default)
var wpn_bullets_ammo_at_start = 0;           // ammount of bullets collected
var wpn_bullets_ammo_at_end = 0;             // same as above (by default)
var wpn_shells_ammo_at_start = 0;            // amount of shells collected
var wpn_shells_ammo_at_end = 0;              // same as above (by default)
var wpn_rocketl_ammo_at_start = 0;           // amount of rockets collected
var wpn_rocketl_ammo_at_end = 0;             // same as above (by default)

// player's weapon
typedef struct PLAYER_WEAPON
{
    var collected;
    var semiauto;

    var ammo;
    var fire_rate;
    var recoil_strength;
    var damage;
    var accuracy;
    var projectile_speed;

    var animate;
    var anim_frame;
    var anim_total_frames;

    SOUND *snd;
} PLAYER_WEAPON;

// player's camera
typedef struct CAMERA
{
    VECTOR position;
    ANGLE angle;
    var height;
    var fov;

    var bob;
    var bob_z_offset;
    var bob_speed;
    var bob_speed_factor;

    VECTOR recoil_vector;
    var recoil_arc;
    var recoil_power;

    VECTOR explo_vector;
    var explo_power;

    ANGLE damage_offset;
} CAMERA;

// player's main structure
typedef struct PLAYER
{
    CCT cct;
    CAMERA cam;
    PLAYER_WEAPON weapon[MAX_WEAPONS];
    ENTITY *weapon_ent;
    var weapon_snd_switch;
    var weapon_draw_counter;

    VECTOR interact_pos;
    var interact_once;

    var shoot;
    var interact;
    var weapon_1;
    var weapon_2;
    var weapon_3;
    var weapon_4;
    var weapon_5;

} PLAYER;

// register player on the level
PLAYER *register_player_structure(ENTITY *ent);

// get player's structure from the given entity
PLAYER *get_player_structure(ENTITY *ent);

// unregister/delete player from the level
var delete_player_structure(ENTITY *ent);

#endif