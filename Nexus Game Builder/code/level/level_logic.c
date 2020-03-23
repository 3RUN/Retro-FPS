
// initialize all levels
void init_levels()
{
	nxstempID=0;
	
	//Loads the level settings from the first level on the chapter list
	str_cpy(nxstemp_str, nxs_set_level_link_1); nxs_set_lv_counter = 0;
	nxs_load_level_settings();
	level_setup(0, "world.wmb", nxs_set_audio_name, nxs_settings_val_near, nxs_settings_val_far, nxs_settings_val_min, nxs_settings_val_sec);
	
	if(!str_cmp(nxs_set_level_link_2, " "))
	{
		str_cpy(nxstemp_str, nxs_set_level_link_2); nxs_set_lv_counter = 1;
		nxs_load_level_settings();
		level_setup(1, "world.wmb", nxs_set_audio_name, nxs_settings_val_near, nxs_settings_val_far, nxs_settings_val_min, nxs_settings_val_sec);
	}
	if(!str_cmp(nxs_set_level_link_3, " "))
	{
		str_cpy(nxstemp_str, nxs_set_level_link_3); nxs_set_lv_counter = 2;
		nxs_load_level_settings();
		level_setup(2, "world.wmb", nxs_set_audio_name, nxs_settings_val_near, nxs_settings_val_far, nxs_settings_val_min, nxs_settings_val_sec);
	}
	if(!str_cmp(nxs_set_level_link_4, " "))
	{
		str_cpy(nxstemp_str, nxs_set_level_link_4); nxs_set_lv_counter = 3;
		nxs_load_level_settings();
		level_setup(3, "world.wmb", nxs_set_audio_name, nxs_settings_val_near, nxs_settings_val_far, nxs_settings_val_min, nxs_settings_val_sec);
	}
	if(!str_cmp(nxs_set_level_link_5, " "))
	{
		str_cpy(nxstemp_str, nxs_set_level_link_5); nxs_set_lv_counter = 4;
		nxs_load_level_settings();
		level_setup(4, "world.wmb", nxs_set_audio_name, nxs_settings_val_near, nxs_settings_val_far, nxs_settings_val_min, nxs_settings_val_sec);
	}
	if(!str_cmp(nxs_set_level_link_6, " "))
	{
		str_cpy(nxstemp_str, nxs_set_level_link_6); nxs_set_lv_counter = 5;
		nxs_load_level_settings();
		level_setup(5, "world.wmb", nxs_set_audio_name, nxs_settings_val_near, nxs_settings_val_far, nxs_settings_val_min, nxs_settings_val_sec);
	}
	if(!str_cmp(nxs_set_level_link_7, " "))
	{
		str_cpy(nxstemp_str, nxs_set_level_link_7); nxs_set_lv_counter = 6;
		nxs_load_level_settings();
		level_setup(6, "world.wmb", nxs_set_audio_name, nxs_settings_val_near, nxs_settings_val_far, nxs_settings_val_min, nxs_settings_val_sec);
	}
	if(!str_cmp(nxs_set_level_link_8, " "))
	{
		str_cpy(nxstemp_str, nxs_set_level_link_8); nxs_set_lv_counter = 7;
		nxs_load_level_settings();
		level_setup(7, "world.wmb", nxs_set_audio_name, nxs_settings_val_near, nxs_settings_val_far, nxs_settings_val_min, nxs_settings_val_sec);
	}
	if(!str_cmp(nxs_set_level_link_9, " "))
	{
		str_cpy(nxstemp_str, nxs_set_level_link_9); nxs_set_lv_counter = 8;
		nxs_load_level_settings();
		level_setup(8, "world.wmb", nxs_set_audio_name, nxs_settings_val_near, nxs_settings_val_far, nxs_settings_val_min, nxs_settings_val_sec);
	}
	if(!str_cmp(nxs_set_level_link_10, " "))
	{
		str_cpy(nxstemp_str, nxs_set_level_link_10); nxs_set_lv_counter = 9;
		nxs_load_level_settings();
		level_setup(9, "world.wmb", nxs_set_audio_name, nxs_settings_val_near, nxs_settings_val_far, nxs_settings_val_min, nxs_settings_val_sec);
	}
}


// set level settings (such as fog, clipping etc)
void set_level_settings()
{
	vec_set(&d3d_lodfactor, vector(12.5, 25, 50));

	sun_light = 0;
	vec_set(&sun_angle, vector(0, 90, 0));

	camera->clip_near = 0.1;
	camera->clip_far = map[level_id].fog_end + 512;

	camera->fog_start = map[level_id].fog_start;
	camera->fog_end = map[level_id].fog_end;

	fog_color = 4;
	vec_set(&d3d_fogcolor4.blue, COLOR_FOG);
	//	vec_set(&sky_color.blue, COLOR_SKY);
}


// reset some global level variables
void level_reset()
{
	// stop sounds/music
	snd_stopall(4);
	music_stop();

	// reset gui
	gui_reset();
	
	// stop our timer
	level_timer_reset();

	// level isn't loaded any more
	level_is_loaded = false;
	level_secrets_found = 0;
	level_secrets_total = 0;
	level_gold_collected = 0;
	level_gold_total = 0;
	level_enemies_killed = 0;
	level_enemies_total = 0;
	game_state = GAME_LEVEL_LOADING;
}


// restart current level
void level_restart()
{
	if (game_state != GAME_LEVEL_RUNNING)
	{
		return;
	}
	if(nxstempID>=1){nxstempID -= 1;}
	level_load(level_id);
}

//black_overlay to show chapter title and messages for beginning and end levels
BMAP* nxs_popup_overlay = "popup_overlay.png";
TEXT* nxs_ch_title_display = {string=nxs_ch_message_title; pos_x=400; pos_y=200; layer=10001; red=255; green=255; blue=255; font=ackfont_sm; alpha=100; flags = LIGHT | CENTER_X;}
TEXT* nxs_ch_msgA_display = {string=nxs_ch_message_start; pos_x=400; pos_y=300; layer=10001; red=255; green=255; blue=255; font=nxs_msg_font; alpha=100; flags = LIGHT | CENTER_X;}
TEXT* nxs_ch_msgB_display = {string=nxs_ch_message_final; pos_x=400; pos_y=300; layer=10001; red=255; green=255; blue=255; font=nxs_msg_font; alpha=100; flags = LIGHT | CENTER_X;}
PANEL* nxs_ch_msg_bg =
{
	bmap = nxs_popup_overlay;
	pos_x = 0;
	pos_y = 0;
	layer = 10000;
}


// load level with the given id
int msgA_onceOnly = false;
void level_load(var num)
{
	if(msgA_onceOnly==true && nxstempID!=nxs_set_lv_counter+1){set(nxs_loading_pan,SHOW);}
	while(key_any==1){wait(1);}
	
	//CHAPTER LEVEL 1 MSG
	if(nxstempID==0 && msgA_onceOnly==false)
	{
		set(nxs_popup_overlay,SHOW);
		set(nxs_ch_title_display,SHOW);
		set(panTextbox_msg,SHOW);
		TEXTBOX *_cm_set_textbox = ch_textbox_msg();
		str_cpy(((TEXTBOX*)_cm_set_textbox)->string, nxs_ch_message_start);
		textboxUpdate(_cm_set_textbox);wait(1);
		nxstempID = 0;
		while(key_any==0){wait(1);}
		while(key_any==1){wait(1);}
		reset(panTextbox_msg,SHOW);
		reset(nxs_popup_overlay,SHOW);
		reset(nxs_ch_title_display,SHOW);
		msgA_onceOnly=true;
	}
	
	//CHAPTER ENDING LEVEL MSG
	if(nxstempID==nxs_set_lv_counter+1)
	{
		nxstempID = 0;
		reset(camera, SHOW);
		level_reset();
		set(panTextbox_msg,SHOW);
		set(nxs_popup_overlay,SHOW);
		set(nxs_ch_title_display,SHOW);
		TEXTBOX *_cm_set_textbox = ch_textbox_msg();
		str_cpy(((TEXTBOX*)_cm_set_textbox)->string, nxs_ch_message_final);
		textboxUpdate(_cm_set_textbox);
		textboxMe=NULL;
		while(key_any==1){wait(1);}
		while(key_any==0){wait(1);}
		sys_exit(NULL);
		return;
	}
	
	// don't allow to load twice at the same time
	if (proc_status(level_load) > 0)
	{
		return;
	}
	
	// no name was given for the level ?
	// don't allow for weird things to happen...
	if (str_len(map[level_id].map_name) <= 0)
	{
		diag("\nCRITICAL ERROR! No level name was given OR no level was setup to be loaded!");
		sys_exit(NULL);
		return; // terminate function as well
	}

	reset(camera, SHOW);
	level_reset();
	wait_for(level_reset);

	freeze_mode = true;
	level_load(map[level_id].map_name);
	freeze_mode = false;
	
	// level wasn't loaded ?
	if (!level_ent)
	{
		diag("\n\nCRITICAL ERROR! Level couldn't be loaded!\n");
		return;
	}

	set(level_ent, NOFILTER);
	level_ent->group = OBSTACLE_GROUP;
	level_ent->push = OBSTACLE_GROUP;
	
	//Verify Level_load ID and Generate Correct Chapter Levels
	if(nxstempID==0){str_cpy(nxstemp_str, nxs_set_level_link_1);}
	if(nxstempID==1){str_cpy(nxstemp_str, nxs_set_level_link_2);}
	if(nxstempID==2){str_cpy(nxstemp_str, nxs_set_level_link_3);}
	if(nxstempID==3){str_cpy(nxstemp_str, nxs_set_level_link_4);}
	if(nxstempID==4){str_cpy(nxstemp_str, nxs_set_level_link_5);}
	if(nxstempID==5){str_cpy(nxstemp_str, nxs_set_level_link_6);}
	if(nxstempID==6){str_cpy(nxstemp_str, nxs_set_level_link_7);}
	if(nxstempID==7){str_cpy(nxstemp_str, nxs_set_level_link_8);}
	if(nxstempID==8){str_cpy(nxstemp_str, nxs_set_level_link_9);}
	if(nxstempID==9){str_cpy(nxstemp_str, nxs_set_level_link_10);}
	
	//Generate the correct nexus level based on the level_load ID
	nxs_generation_init();
	wait_for(nxs_generation_init);
	nxstempID += 1;
	
	//Sets the correct sky image for the level
	ent_morph(game_level_skycube, nxs_set_skybox_name); 
	
	//Weather Effects (0 = None)
	if(nxs_settings_weather == 1){ /* CALL WEATHER EFFECT "RAIN" HERE */ }
	if(nxs_settings_weather == 2){ /* CALL WEATHER EFFECT "STORM" HERE */ }
	if(nxs_settings_weather == 3){ /* CALL WEATHER EFFECT "SNOW" HERE */ }
	
	set_level_settings();
	music_start();
	
	//Sets the correct audio track for each level
	music_handle = media_loop(nxs_set_audio_name, NULL, music_volume);
	
	//Camera Settings
	set(camera, SHOW);
	camera->pan=0;
}