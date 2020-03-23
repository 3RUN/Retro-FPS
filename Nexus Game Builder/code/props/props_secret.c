
// update secret wall
void secret_wall_update(ENTITY *ent)
{
	
	// get props struct
	PROPS *props = get_props(ent);

	// open ?
	if (ent->OBJ_STATE == PROPS_OPEN_STATE)
	{
		ent->max_y *= 0.95;
		ent->min_y *= 0.95;
		ent->max_z *= 0.95;
		ent->min_z *= 0.95;
		// reset polygon flag while moving
//		reset(ent, POLYGON);
		// secret walls will move towards the given direction
		// until it will hit a static wall
		// they will move towards forward according to their PAN angle
		// remember this when building your own levels
		vec_set(&ent->PROPS_OFFSET_X_, vector(WORLD_TILE_SIZE, 0, 0));
		vec_rotate(&ent->PROPS_OFFSET_X_, &ent->pan);
		vec_add(&ent->PROPS_OFFSET_X_, &ent->x);

		// move to target position
		vec_diff(&props->diff, &ent->PROPS_OFFSET_X_, &ent->x);
		var spd = props->movement_speed * time_step;
		if (vec_length(&props->diff) > spd)
		{
			vec_normalize(&props->diff, spd);
		}
		c_ignore(SWITCH_ITEM_GROUP, PROJECTILE_GROUP, 0);
		var move_res = c_move(ent, nullvector, &props->diff, MOVE_FLAGS | IGNORE_PUSH);

		// play start sound
		// armor skill used as a switch, to play sound once
		if (ent->OBJ_HEALTH == 0)
		{
			if (snd_playing(ent->OBJ_SND_HANDLE))
			{
				snd_stop(ent->OBJ_SND_HANDLE);
			}
			ent->OBJ_SND_HANDLE = ent_playloop(ent, props_secret_move_ogg, secret_wall_snd_volume);
			ent->OBJ_HEALTH = 1;
		}

		// check if we can smash someone into the wall
		ent->OBJ_CHECK = false;
		
		// hit something ?
		if (move_res <= 0)
		{
			// stoped sound
			if (ent->OBJ_HEALTH == 1)
			{
				if (snd_playing(ent->OBJ_SND_HANDLE))
				{
					snd_stop(ent->OBJ_SND_HANDLE);
				}
				ent->OBJ_SND_HANDLE = ent_playsound(ent, props_door_shut_ogg, secret_wall_snd_volume);
				ent->OBJ_HEALTH = 0;
			}

			// switch to DEAD (can't be used anymore)
			set(ent, POLYGON);
			ent->OBJ_STATE = PROPS_DEAD_STATE;
			ent->OBJ_CHECK = false;
		}
	}
}

// event function for secret wall
void secret_wall_event_function()
{
	if (event_type == EVENT_SHOOT)
	{
		// not in IDLE state ?
		if (my->OBJ_STATE != PROPS_IDLE_STATE)
		{
			return;
		}

		// player is that you ?
		if (you->OBJ_TYPE != TYPE_PLAYER)
		{
			return;
		}

		// if this door needs to be triggered by switch, don't interact with it
		if (is(my, USE_SWITCH) || is(my, USE_TRIGGER))
		{
			return;
		}

		// only once !
		my->emask &= ~ENABLE_SHOOT;

		// move this secret wall !
		my->OBJ_STATE = PROPS_OPEN_STATE;
	}
}

// simple secret wall
// uses: ID, USE_SWITCH, USE_TRIGGER
action props_secret_wall()
{
	if(nxsCmData[cm_id].useSwitch == 1){set(my, USE_SWITCH); my->skill1 = tiles[cm_XY[0]][cm_XY[1]].switchID;}
	if(nxsCmData[cm_id].useTrigger == 1){set(my, USE_TRIGGER); my->skill1 = tiles[cm_XY[0]][cm_XY[1]].triggerID;}
	if(nxsCmData[cm_id_B].useSwitch == 1){set(my, USE_SWITCH); my->skill1 = tilesB[cm_XY[0]][cm_XY[1]].switchID;}
	if(nxsCmData[cm_id_B].useTrigger == 1){set(my, USE_TRIGGER); my->skill1 = tilesB[cm_XY[0]][cm_XY[1]].triggerID;}
	if(nxsCmData[cm_id_C].useSwitch == 1){set(my, USE_SWITCH); my->skill1 = tilesC[cm_XY[0]][cm_XY[1]].switchID;}
	if(nxsCmData[cm_id_C].useTrigger == 1){set(my, USE_TRIGGER); my->skill1 = tilesC[cm_XY[0]][cm_XY[1]].triggerID;}
	
	if(nxs_layer == 1){my->pan = tiles[cm_XY[0]][cm_XY[1]].rotation + 90;}
	if(nxs_layer == 2){my->pan = tilesB[cm_XY[0]][cm_XY[1]].rotation + 90;}
	if(nxs_layer == 3){my->pan = tilesC[cm_XY[0]][cm_XY[1]].rotation + 90;}
	
	// correct our Z position
	my->z = WORLD_Z_POS - 0.4;

	PROPS *props = register_props(my);
	props->movement_speed = 1.5;

	vec_fill(&my->scale_x, 1);
	c_setminmax(my);

	// we make bbox smaller on Y and Z coordinates
	// so we don't hit walls while moving forward!
	my->max_y *= 0.95;
	my->min_y *= 0.95;
	my->max_z *= 0.95;
	my->min_z *= 0.95;

	// never set POLYGON for moving objects !
	// only when they stopped or static at all !
	set(my, POLYGON | NOFILTER);
	my->material = mtl_z_write;

	my->group = OBSTACLE_GROUP;
	my->push = OBSTACLE_GROUP;

	my->OBJ_STATE = PROPS_IDLE_STATE;
	my->OBJ_TYPE = TYPE_PROPS_SECRET;
	
	my->emask |= (ENABLE_SHOOT);
	my->event = secret_wall_event_function;

	// create secret zone at the same position
	ent_create(bbox_props_mdl, &my->x, props_secret_zone);
}

// event function for secret zone
void secret_zone_event_function()
{
	if (event_type == EVENT_PUSH)
	{
		// player is that you ?
		if (you->OBJ_TYPE != TYPE_PLAYER)
		{
			return;
		}

		// only once !
		my->emask &= ~ENABLE_PUSH;

		// plus 1 secret found on this level
		level_secrets_found++;

		// play secret found snd
		snd_play(props_secret_found_ogg, secret_found_snd_volume, 0);

		// show message
		show_message(you_fond_a_secret_str);

		// remove us
		ent_delete(my);
	}
}

// simple secret zone snd/message trigger
void props_secret_zone()
{
	// correct our Z position
	my->z = WORLD_Z_POS;

	// plus 1 secret created on this level
	level_secrets_total++;

	vec_fill(&my->scale_x, 0.75);
	c_setminmax(my);
	set(my, POLYGON | TRANSLUCENT);

	my->group = SWITCH_ITEM_GROUP;
	my->push = SWITCH_ITEM_GROUP;

	my->OBJ_TYPE = TYPE_PROPS_SECRET_ZOME;

	my->emask |= (ENABLE_PUSH);
	my->event = secret_zone_event_function;
}