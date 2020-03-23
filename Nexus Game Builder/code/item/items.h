#ifndef _ITEMS_H_
#define _ITEMS_H_

// colors for pickup effects
#define ITEM_HEALTH_COLOR vector(81, 155, 49)
#define ITEM_GOLD_COLOR vector(35, 195, 235)
#define ITEM_AMMO_COLOR vector(158, 82, 59)
#define ITEM_KEY_COLOR vector(248, 73, 107)

// items stuff
#define ITEM_HEALTH_SMALL 1
#define ITEM_HEALTH_BIG 2
#define ITEM_FOOD_SMALL 3
#define ITEM_FOOD_BIG 4
#define ITEM_GOLD_SMALL 5
#define ITEM_GOLD_BIG 6
#define ITEM_AMMO_PACK 7
#define ITEM_AMMO_BULLETS 8
#define ITEM_AMMO_SHELLS 9
#define ITEM_AMMO_ROCKETS 10
#define ITEM_KEY_RED 11
#define ITEM_KEY_YELLOW 12
#define ITEM_KEY_BLUE 13

// strings
STRING *item_health_small_str = "Picked up small health pack.";
STRING *item_health_big_str = "Picked up big health pack.";
STRING *item_food_small_str = "Got a bit of food";
STRING *item_food_big_str = "Got one big and tasty chicken!";
STRING *item_gold_small_str = "Found a small treasure.";
STRING *item_gold_big_str = "Found a big treasure!";
STRING *item_ammo_pack_str = "Got an ammo pack.";
STRING *item_ammo_bullets_str = "Got some bullets.";
STRING *item_ammo_shells_str = "Got shotgun shells.";
STRING *item_ammo_rockets_str = "Got ammo for rocketlauncher.";
STRING *item_key_red_str = "Got a red key.";
STRING *item_key_yellow_str = "Got a yellow key.";
STRING *item_key_blue_str = "Got a blue key.";

// max health for player
var player_hp_max_for_small = 200;
var player_hp_max_for_big = 100;

// item's stuff
var item_pickup_snd_volume = 65; // volume for pickup sfx
var item_health_small_add = 1;   // each small health adds 1 hp
var item_health_big_add = 25;    // big health pack adds 25 hp
var item_food_small_add = 1;     // each small food adds 1 hp
var item_food_big_add = 15;      // each big food adds 15 hp
var item_gold_small_add = 25;    // each small gold adds 25 points
var item_gold_big_add = 50;      // each big gold adds 50 points
var item_bullets_small_add = 15; // each small pistol clip/ammo adds 15
var item_bullets_big_add = 25;   // each big pistol ammo adds 25
var item_shells_small_add = 12;  // each small shell ammo adds 12
var item_shells_big_add = 25;    // each big shell ammo adds 25
var item_rockets_small_add = 1;  // each small rocket launcher ammo adds 1
var item_rockets_big_add = 5;    // each big rocket launcher ammo adds 5

// stop item pick up snd
void item_snd_stop();

// health pickup snd effect
void item_health_up_snd();

// gold pickup snd effect
void item_gold_snd();

// ammo pickup snd effect
void item_ammo_snd();

// key pickup snd effect
void item_key_snd();

// init visual model for item
// ent - is the visual model, which will change it's skin
// bmap - bmap which will replace skin of ghost ent
void item_visual_ent(ENTITY *ent, BMAP *bmp);

// visual sprites function
// create visual sprite for the item
void item_create_sprite();

// pickup item
void item_pickup(ENTITY *ent, var num);

// main event function for all items
void item_event_function();

// function for all items
void item_init(var num);

#endif