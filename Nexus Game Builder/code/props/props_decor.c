

// sprites event function
void sprite_event_function()
{
	if (event_type == EVENT_FRAME)
	{		
		// does it needs to be rotated to the camera ?
		if (is(my, ROTATE_TO_CAM))
		{
			ent_rotate_to_camera(my);
		}
		
		
		// we should be attached to the wall ?
		if (is(my, ATTACH_TO_WALL))
		{
			ent_attach_to_near_wall(my);
		}
		
		if (my->parent)
		{
			vec_set(&my->parent->x, &my->x);
		}
		
		if (my->pan == 0)
		{
			my->pan = 0.01;
		}
	}
}

// uses: ROTATE_TO_CAM, IS_OBSTACLE, SHOOT_THROUGH, ATTACH_TO_WALL
// FLAG3: ROTATE_TO_CAM 1
action props_sprite()
{	
	if(nxs_layer == 1)
	{
		if(nxsCmData[cm_id].propFlag1 == 1){set(my, ROTATE_TO_CAM);}
		if(nxsCmData[cm_id].propFlag2 == 1){set(my, IS_OBSTACLE);}
		if(nxsCmData[cm_id].propFlag3 == 1){set(my, ATTACH_TO_WALL);}
		if(nxsCmData[cm_id].propFlag4 == 1){set(my, SHOOT_THROUGH);}
		if(nxsCmData[cm_id].propFlag5 == 1){}
		my->pan = tiles[cm_XY[0]][cm_XY[1]].rotation + 90;
	}
	if(nxs_layer == 2)
	{
		if(nxsCmData[cm_id_B].propFlag1 == 1){set(my, ROTATE_TO_CAM);}
		if(nxsCmData[cm_id_B].propFlag2 == 1){set(my, IS_OBSTACLE);}
		if(nxsCmData[cm_id_B].propFlag3 == 1){set(my, ATTACH_TO_WALL);}
		if(nxsCmData[cm_id_B].propFlag4 == 1){set(my, SHOOT_THROUGH);}
		if(nxsCmData[cm_id_B].propFlag5 == 1){}
		my->pan = tilesB[cm_XY[0]][cm_XY[1]].rotation + 90;
	}
	if(nxs_layer == 3)
	{
		if(nxsCmData[cm_id_C].propFlag1 == 1){set(my, ROTATE_TO_CAM);}
		if(nxsCmData[cm_id_C].propFlag2 == 1){set(my, IS_OBSTACLE);}
		if(nxsCmData[cm_id_C].propFlag3 == 1){set(my, ATTACH_TO_WALL);}
		if(nxsCmData[cm_id_C].propFlag4 == 1){set(my, SHOOT_THROUGH);}
		if(nxsCmData[cm_id_C].propFlag5 == 1){}
		my->pan = tilesC[cm_XY[0]][cm_XY[1]].rotation + 90;
	}
	
	// correct our Z position
	my->z = WORLD_Z_POS - 0.2;
	
	// sprite is always passable
	// for collisions we use bboxes !
	set(my, PASSABLE | NOFILTER);

	// not rotating to camera
	if (!is(my, ROTATE_TO_CAM))
	{
		if (my->pan == 0)
		{
			my->pan += 0.01;
		}
	}
	
	// we should be attached to the wall ?
	if (is(my, ATTACH_TO_WALL))
	{
		ent_attach_to_near_wall(my);
	}

	// create bbox model
	my->parent = ent_create(bbox_props_mdl, &my->x, NULL);
	set(my->parent, INVISIBLE);
	vec_set(&my->parent->scale_x, vector(0.49, 0.49, 1));
	c_setminmax(my->parent);

	// if we aren't passable
	if (is(my, IS_OBSTACLE))
	{      
		set(my->parent, POLYGON);

		// set ground depending on
		// can we shoot through this obstacle or not
		if (is(my, SHOOT_THROUGH))
		{
			my->parent->group = SHOOT_THROUGH_GROUP;
			my->parent->push = SHOOT_THROUGH_GROUP;
		}
		else
		{
			my->parent->group = OBSTACLE_GROUP;
			my->parent->push = OBSTACLE_GROUP;
		}
	}
	else
	{
		set(my->parent, PASSABLE);
		my->parent->group = SWITCH_ITEM_GROUP;
		my->parent->push = SWITCH_ITEM_GROUP;
	}
	
	my->emask |= (ENABLE_FRAME);
	my->event = sprite_event_function;
}