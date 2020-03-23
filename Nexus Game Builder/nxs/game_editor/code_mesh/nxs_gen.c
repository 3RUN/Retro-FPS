/*#########################################################################################################################################################
NEXUS A8 : GAME BUILDER :: By Brian Pressley (Evo) (Evoeon) :::: NEXUS GENERATION CODE :: Lite-C :: 3DGamestudio A8
#########################################################################################################################################################*/


//LOADS THE CONTENT MANAGER DATA
void nxs_load_editor_cm_data()
{
	//Nexus Init : Set Empty Strings
	int _x = 0;
	for (; _x<600; _x++)
	{
		str_cpy((nxs_actions->pstring)[_x], "EMPTY");
		str_cpy((nxs_files->pstring)[_x], "EMPTY"); 
		str_cpy((nxs_skins->pstring)[_x], "EMPTY"); 
		str_cpy((nxs_tex_strings->pstring)[_x], "EMPTY"); 
	}
	
	nxs_assign_pointers();
	
	//Load Content creation file
	STRING* gotofile = str_create(work_dir); str_cat(gotofile, "\\nxs\\game_editor\\"); SetCurrentDirectory(_chr(gotofile));
	dataHandle = file_open_read(nxs_game_content);
	if(dataHandle)
	{
		int _x = 0;
		for (; _x<600; _x++)
		{
			nxsCmData[_x].content = file_var_read (dataHandle);
			nxsCmData[_x].doorFlag1 = file_var_read (dataHandle);
			nxsCmData[_x].doorFlag2 = file_var_read (dataHandle);
			nxsCmData[_x].doorFlag3 = file_var_read (dataHandle);
			nxsCmData[_x].doorFlag4 = file_var_read (dataHandle);
			nxsCmData[_x].doorFlag5 = file_var_read (dataHandle);
			nxsCmData[_x].propFlag1 = file_var_read (dataHandle);
			nxsCmData[_x].propFlag2 = file_var_read (dataHandle);
			nxsCmData[_x].propFlag3 = file_var_read (dataHandle);
			nxsCmData[_x].propFlag4 = file_var_read (dataHandle);
			nxsCmData[_x].propFlag5 = file_var_read (dataHandle);
			nxsCmData[_x].bonusFlag1 = file_var_read (dataHandle);
			nxsCmData[_x].bonusFlag2 = file_var_read (dataHandle);
			nxsCmData[_x].useSwitch = file_var_read (dataHandle);
			nxsCmData[_x].useTrigger = file_var_read (dataHandle);
			file_str_read(dataHandle,(nxs_actions->pstring)[_x]);
			file_str_read(dataHandle,(nxs_files->pstring)[_x]);
			file_str_read(dataHandle,(nxs_skins->pstring)[_x]);
		}
		file_close (dataHandle);
	}
	else{sys_exit("bye");}
	gotofile = str_create(work_dir); SetCurrentDirectory(_chr(gotofile));
}


//LOADS A CHAPTER FILE
void nxs_load_chapter()
{
	STRING* gotofile = str_create(work_dir); str_cat(gotofile, "\\nxs\\game_editor\\chapters\\"); str_cat(gotofile, nxs_game_chapter); 
	SetCurrentDirectory(_chr(gotofile));
	
	dataHandle = file_open_read(gotofile);
	if(dataHandle)
	{
		file_str_read(dataHandle,nxs_extension_type);
		file_str_read(dataHandle,nxs_ch_message_title);
		file_str_read(dataHandle,nxs_ch_message_start);
		file_str_read(dataHandle,nxs_ch_message_final);
		file_str_read(dataHandle,nxs_set_level_link_1);
		file_str_read(dataHandle,nxs_set_level_link_2);
		file_str_read(dataHandle,nxs_set_level_link_3);
		file_str_read(dataHandle,nxs_set_level_link_4);
		file_str_read(dataHandle,nxs_set_level_link_5);
		file_str_read(dataHandle,nxs_set_level_link_6);
		file_str_read(dataHandle,nxs_set_level_link_7);
		file_str_read(dataHandle,nxs_set_level_link_8);
		file_str_read(dataHandle,nxs_set_level_link_9);
		file_str_read(dataHandle,nxs_set_level_link_10);
		file_close (dataHandle);
	}
	gotofile = str_create(work_dir); SetCurrentDirectory(_chr(gotofile));
}


//LOADS A SAVED LEVEL FILE (SETTINGS ONLY)
void nxs_load_level_settings()
{
	STRING* gotofile = str_create(work_dir); str_cat(gotofile, "\\nxs\\game_editor\\levels\\"); str_cat(gotofile, nxstemp_str); 
	SetCurrentDirectory(_chr(gotofile));
	
	dataHandle = file_open_read(gotofile);
	if(dataHandle)
	{
		file_str_read(dataHandle,nxs_extension_type);
		file_str_read(dataHandle,nxs_set_skybox_name);
		file_str_read(dataHandle,nxs_set_audio_name);
		file_str_read(dataHandle,nxs_set_floor_name);
		file_str_read(dataHandle,nxs_set_ceiling_name);
		nxs_settings_val_near = file_var_read (dataHandle);
		nxs_settings_val_far = file_var_read (dataHandle);
		nxs_settings_val_min = file_var_read (dataHandle);
		nxs_settings_val_sec = file_var_read (dataHandle);
		nxs_settings_weather = file_var_read (dataHandle);
		file_close (dataHandle);
	}
	gotofile = str_create(work_dir); SetCurrentDirectory(_chr(gotofile));
}


//GENERATE : LOAD ALL LEVEL DATA AND CALL GENERATION CODE
void nxs_generation_init()
{
	//Load all level data
	STRING* gotofile = str_create(work_dir); str_cat(gotofile, "\\nxs\\game_editor\\levels\\"); str_cat(gotofile, nxstemp_str); 
	SetCurrentDirectory(_chr(gotofile));
	
	dataHandle = file_open_read(gotofile);
	if(dataHandle)
	{
		file_str_read(dataHandle,nxs_extension_type);
		file_str_read(dataHandle,nxs_set_skybox_name);
		file_str_read(dataHandle,nxs_set_audio_name);
		file_str_read(dataHandle,nxs_set_floor_name);
		file_str_read(dataHandle,nxs_set_ceiling_name);
		nxs_settings_val_near = file_var_read (dataHandle);
		nxs_settings_val_far = file_var_read (dataHandle);
		nxs_settings_val_min = file_var_read (dataHandle);
		nxs_settings_val_sec = file_var_read (dataHandle);
		nxs_settings_weather = file_var_read (dataHandle);
		int _x = 0;
		for (; _x<LEVEL_X_MAX; _x++)
		{
			int _y = 0;
			for (; _y<LEVEL_Y_MAX; _y++)
			{
				tiles[_x][_y].type = file_var_read (dataHandle);
				tiles[_x][_y].tileset = file_var_read (dataHandle);
				tiles[_x][_y].switchID = file_var_read (dataHandle);
				tiles[_x][_y].triggerID = file_var_read (dataHandle);
				tiles[_x][_y].rotation = file_var_read (dataHandle);
				
				tilesB[_x][_y].type = file_var_read (dataHandle);
				tilesB[_x][_y].tileset = file_var_read (dataHandle);
				tilesB[_x][_y].switchID = file_var_read (dataHandle);
				tilesB[_x][_y].triggerID = file_var_read (dataHandle);
				tilesB[_x][_y].rotation = file_var_read (dataHandle);
				
				tilesC[_x][_y].type = file_var_read (dataHandle);
				tilesC[_x][_y].tileset = file_var_read (dataHandle);
				tilesC[_x][_y].switchID = file_var_read (dataHandle);
				tilesC[_x][_y].triggerID = file_var_read (dataHandle);
				tilesC[_x][_y].rotation = file_var_read (dataHandle);
			}
		}
		file_close (dataHandle);
	}
	gotofile = str_create(work_dir); SetCurrentDirectory(_chr(gotofile));
	nxs_generation_build();
}


// Action for generated walls
action fps_wall_action()
{
	my->material = mtl_z_write;
	my->z-=0.2;
	set(my, POLYGON);
	set(my, NOFILTER);
	my->group = WALL_GROUP;
	my->push = WALL_GROUP;
}


// Action for generated floors
action fps_floor_action()
{
	my->material = mtl_z_write;
	my->z-=0.2;
	set(my, PASSABLE);
	set(my, NOFILTER);
}


// Action for generated Ceilings (Ceilings should be set as a primary floor type that uses a different model and placed on layer 3)
action fps_ceiling_action()
{
	my->material = mtl_z_write;
	my->z-=0.2;
	set(my, PASSABLE);
	set(my, NOFILTER);
}


//GENERATE : 3D MESH GENERATION CODE
void nxs_generation_build()
{
	nxsGen_complete = false;
	sys_marker("gen");
	set(nxs_loading_pan,SHOW);
	wait(3);//Wait for loop to be closed and regenerate the level
	
	//Identify wall and floor/ceiling textures
	//All models that use the same wall or floor/ceiling texture will be merged together
	int nxs_tex_count = 0;
	int nxs_tex_countB = 0;
	int nxs_tex_countC = 0;
	int _x = 0;
	for (; _x<600; _x++)
	{
		if(!str_cmp((nxs_skins->pstring)[_x], "EMPTY") && nxsCmData[_x].content==2)
		{
			str_cpy((nxs_tex_strings->pstring)[nxs_tex_count],(nxs_skins->pstring)[_x]); nxs_tex_count+=1;
		}
	}	
	
	int _x = 0;
	for (; _x<600; _x++)
	{
		if(!str_cmp((nxs_skins->pstring)[_x], "EMPTY") && nxsCmData[_x].content==9)
		{
			str_cpy((nxs_tex_stringsB->pstring)[nxs_tex_countB],(nxs_skins->pstring)[_x]); nxs_tex_countB+=1;
		}
	}
	
	int _x = 0;
	for (; _x<600; _x++)
	{
		if(!str_cmp((nxs_skins->pstring)[_x], "EMPTY") && nxsCmData[_x].content==9)
		{
			str_cpy((nxs_tex_stringsC->pstring)[nxs_tex_countC],(nxs_skins->pstring)[_x]); nxs_tex_countC+=1;
		}
	}
	
	//Generate BMAPS for merged group skins
	BMAP* merged_skin_set[74];
	BMAP* merged_skin_setB[74];
	BMAP* merged_skin_setC[74];
	int _x = 0;
	for (; _x<nxs_tex_count; _x++)
	{
		merged_skin_set[_x] = bmap_create((nxs_tex_strings->pstring)[_x]);
	}
	int _x = 0;
	for (; _x<nxs_tex_countB; _x++)
	{
		merged_skin_setB[_x] = bmap_create((nxs_tex_stringsB->pstring)[_x]);
	}
	int _x = 0;
	for (; _x<nxs_tex_countC; _x++)
	{
		merged_skin_setC[_x] = bmap_create((nxs_tex_stringsC->pstring)[_x]);
	}
	
	//Generate DYNAMIC MODELS for merged groups
	DynamicModel* merge_walls[74];
	DynamicModel* merge_floor[74];
	DynamicModel* merge_ceiling[74];
	int _x = 0;
	for (; _x<nxs_tex_count; _x++)
	{
		merge_walls[_x] = dmdl_create();
	}
	
	int _x = 0;
	for (; _x<nxs_tex_countB; _x++)
	{
		merge_floor[_x] = dmdl_create();
	}
	
	int _x = 0;
	for (; _x<nxs_tex_countC; _x++)
	{
		merge_ceiling[_x] = dmdl_create();
	}
	
	ENTITY* gen_ent_countA[LEVEL_X_MAX][LEVEL_Y_MAX];
	ENTITY* gen_ent_countB[LEVEL_X_MAX][LEVEL_Y_MAX];
	ENTITY* gen_ent_countC[LEVEL_X_MAX][LEVEL_Y_MAX];
	int cm_id_actA = 0;
	int cm_id_actB = 0;
	int cm_id_actC = 0;
	//GENERATE LAYER 1
	int step_x = -32;
	int step_y = 32;
	int _x = 0;
	for (; _x<LEVEL_X_MAX; _x++)
	{
		int _y = 0;
		for (; _y<LEVEL_Y_MAX; _y++)
		{
			//Building Objects on the level boundary is not allowed
			if(_y==0){continue;}
			if(_x==0){continue;}
			if(_y==LEVEL_Y_MAX){continue;}
			if(_x==LEVEL_X_MAX){continue;}
			
			//#####GENERATE#######
			int _st = 0;
			if(tiles[_x][_y].tileset==1){_st = 0 + tiles[_x][_y].type;}
			if(tiles[_x][_y].tileset==2){_st = 75 + tiles[_x][_y].type;}
			if(tiles[_x][_y].tileset==3){_st = 150 + tiles[_x][_y].type;}
			if(tiles[_x][_y].tileset==4){_st = 225 + tiles[_x][_y].type;}
			if(tiles[_x][_y].tileset==5){_st = 300 + tiles[_x][_y].type;}
			if(tiles[_x][_y].tileset==6){_st = 375 + tiles[_x][_y].type;}
			if(tiles[_x][_y].tileset==7){_st = 450 + tiles[_x][_y].type;}
			if(tiles[_x][_y].tileset==8){_st = 525 + tiles[_x][_y].type;}
			cm_id = _st;
			cm_XY[0] = _x;
			cm_XY[1] = _y;
			
			if(cm_id==0 || cm_id==75 || cm_id==150 || cm_id==225 || cm_id==300 || cm_id==375 || cm_id==450 || cm_id==525){continue;}
			nxs_layer=1;
			
			//#####IDENTIFY NEARBY CONTENT FOR WALL CREATION AND MERGE THEM BY THEIR SKIN ID#######
			if(nxsCmData[cm_id].content==2)
			{
				int save_near_ids[4] = {false,false,false,false};
				int find_groups = 0;
				
				int near_idA = tiles[_x][_y-1].tileset * tiles[_x][_y-1].type; 
				int near_idB = tiles[_x][_y+1].tileset * tiles[_x][_y+1].type;
				int near_idC = tiles[_x+1][_y].tileset * tiles[_x+1][_y].type;  
				int near_idD = tiles[_x-1][_y].tileset * tiles[_x-1][_y].type;  
				
				//				int check_boundary[4];
				//				if(_y==0){check_boundary[0]=true;}
				//				if(_y==LEVEL_Y_MAX){check_boundary[1]=true;}
				
				int _c = 0;
				for (; _c<nxs_tex_count; _c++)
				{
					if(str_cmp((nxs_tex_strings->pstring)[_c], (nxs_skins->pstring)[cm_id]))
					{
						find_groups = _c; 
						merged_acts[_c] = action_control[cm_id];
						break;
					}
				}
				
				//#####GENERATE WALLS#######
				if(nxsCmData[near_idA].content==9)
				{
					ENTITY* mdlTempA;
					mdlTempA = ent_create("bbox_wall_S.mdl", vector(_x*step_x, _y*step_y, 0), action_control[cm_id]); dmdl_add_entity(merge_walls[find_groups], mdlTempA);
					ptr_remove(mdlTempA);
				}
				if(nxsCmData[near_idB].content==9)
				{
					ENTITY* mdlTempB;
					mdlTempB = ent_create("bbox_wall_N.mdl", vector(_x*step_x, _y*step_y, 0), action_control[cm_id]); dmdl_add_entity(merge_walls[find_groups], mdlTempB); 
					ptr_remove(mdlTempB);
				}
				if(nxsCmData[near_idC].content==9)
				{
					ENTITY* mdlTempC;
					mdlTempC = ent_create("bbox_wall_E.mdl", vector(_x*step_x, _y*step_y, 0), action_control[cm_id]); dmdl_add_entity(merge_walls[find_groups], mdlTempC); 
					ptr_remove(mdlTempC);
				}
				if(nxsCmData[near_idD].content==9)
				{
					ENTITY* mdlTempD;
					mdlTempD = ent_create("bbox_wall_W.mdl", vector(_x*step_x, _y*step_y, 0), action_control[cm_id]); dmdl_add_entity(merge_walls[find_groups], mdlTempD); 
					ptr_remove(mdlTempD);
				}
				
				//#####SET GROUP SKINS#######
				merge_walls[find_groups]->skin[0] = merged_skin_set[find_groups];
			}
			
			//#####IDENTIFY NEARBY CONTENT FOR FLOOR CREATION AND MERGE THEM BY THEIR SKIN ID#######
			if(nxsCmData[cm_id].content==9)
			{
				int find_groups = 0;
				
				int _c = 0;
				for (; _c<nxs_tex_countB; _c++)
				{
					if(str_cmp((nxs_tex_stringsB->pstring)[_c], (nxs_skins->pstring)[cm_id]))
					{
						find_groups = _c; 
						merged_actsB[_c] = action_control[cm_id];
						break;
					}
				}
				
				ENTITY* mdlTempF;
				mdlTempF = ent_create((nxs_files->pstring)[cm_id], vector(_x*step_x, _y*step_y, 0), action_control[cm_id]); dmdl_add_entity(merge_floor[find_groups], mdlTempF); 
				merge_floor[find_groups]->skin[0] = merged_skin_setB[find_groups];
				ptr_remove(mdlTempF);
			}
			
			//			#####CREATE DEFINED CONTENT IF ITS NOT A WALL OR FLOOR TYPE#######
			if(nxsCmData[cm_id].content!=2 && nxsCmData[cm_id].content!=9 && nxsCmData[cm_id].content!=0)
			{
				gen_ent_countA[_x][_y] = ent_create((nxs_files->pstring)[cm_id], vector(_x*step_x, _y*step_y, 0), action_control[cm_id]);
				if(!str_cmp((nxs_skins->pstring)[cm_id], "EMPTY")){ ent_morphskin(gen_ent_countA[_x][_y],(nxs_skins->pstring)[cm_id]); }
			}
		}
	}
	
	
	//GENERATE LAYER 2
	int step_x = -32;
	int step_y = 32;
	int _x = 0;
	for (; _x<LEVEL_X_MAX; _x++)
	{
		int _y = 0;
		for (; _y<LEVEL_Y_MAX; _y++)
		{
			if(_y==0){continue;}
			if(_x==0){continue;}
			if(_y==LEVEL_Y_MAX){continue;}
			if(_x==LEVEL_X_MAX){continue;}
			
			//Set Tileset ID and Tile ID
			int _st = 0;
			if(tilesB[_x][_y].tileset==1){_st = 0 + tilesB[_x][_y].type;}
			if(tilesB[_x][_y].tileset==2){_st = 75 + tilesB[_x][_y].type;}
			if(tilesB[_x][_y].tileset==3){_st = 150 + tilesB[_x][_y].type;}
			if(tilesB[_x][_y].tileset==4){_st = 225 + tilesB[_x][_y].type;}
			if(tilesB[_x][_y].tileset==5){_st = 300 + tilesB[_x][_y].type;}
			if(tilesB[_x][_y].tileset==6){_st = 375 + tilesB[_x][_y].type;}
			if(tilesB[_x][_y].tileset==7){_st = 450 + tilesB[_x][_y].type;}
			if(tilesB[_x][_y].tileset==8){_st = 525 + tilesB[_x][_y].type;}
			cm_id_B = _st;
			cm_XY[0] = _x;
			cm_XY[1] = _y;
			
			if(cm_id_B==0 || cm_id_B==75 || cm_id_B==150 || cm_id_B==225 || cm_id_B==300 || cm_id_B==375 || cm_id_B==450 || cm_id_B==525){continue;}
			
			nxs_layer=2;
			gen_ent_countB[_x][_y] = ent_create((nxs_files->pstring)[cm_id_B], vector(_x*step_x, _y*step_y, 0), action_control[cm_id_B]);
			if(!str_cmp((nxs_skins->pstring)[cm_id_B], "EMPTY")){ ent_morphskin(gen_ent_countB[_x][_y],(nxs_skins->pstring)[cm_id_B]); }
		}
	}
	
	
	//GENERATE LAYER 3
	int step_x = -32;
	int step_y = 32;
	int _x = 0;
	for (; _x<LEVEL_X_MAX; _x++)
	{
		int _y = 0;
		for (; _y<LEVEL_Y_MAX; _y++)
		{
			if(_y==0){continue;}
			if(_x==0){continue;}
			if(_y==LEVEL_Y_MAX){continue;}
			if(_x==LEVEL_X_MAX){continue;}
			
			//Set Tileset ID and Tile ID
			int _st = 0;
			if(tilesC[_x][_y].tileset==1){_st = 0 + tilesC[_x][_y].type;}
			if(tilesC[_x][_y].tileset==2){_st = 75 + tilesC[_x][_y].type;}
			if(tilesC[_x][_y].tileset==3){_st = 150 + tilesC[_x][_y].type;}
			if(tilesC[_x][_y].tileset==4){_st = 225 + tilesC[_x][_y].type;}
			if(tilesC[_x][_y].tileset==5){_st = 300 + tilesC[_x][_y].type;}
			if(tilesC[_x][_y].tileset==6){_st = 375 + tilesC[_x][_y].type;}
			if(tilesC[_x][_y].tileset==7){_st = 450 + tilesC[_x][_y].type;}
			if(tilesC[_x][_y].tileset==8){_st = 525 + tilesC[_x][_y].type;}
			cm_id_C = _st;
			cm_XY[0] = _x;
			cm_XY[1] = _y;
			
			if(cm_id_C==0 || cm_id_C==75 || cm_id_C==150 || cm_id_C==225 || cm_id_C==300 || cm_id_C==375 || cm_id_C==450 || cm_id_C==525){continue;}
			nxs_layer=3;
			
			//#####IDENTIFY NEARBY CONTENT FOR CEILING CREATION AND MERGE THEM BY THEIR SKIN ID#######
			if(nxsCmData[cm_id_C].content==9)
			{
				int find_groups = 0;
				
				int _c = 0;
				for (; _c<nxs_tex_countC; _c++)
				{
					if(str_cmp((nxs_tex_stringsC->pstring)[_c], (nxs_skins->pstring)[cm_id_C]))
					{
						find_groups = _c; 
						merged_actsC[_c] = action_control[cm_id_C];
						break;
					}
				}
				
				ENTITY* mdlTempG;
				mdlTempG = ent_create((nxs_files->pstring)[cm_id_C], vector(_x*step_x, _y*step_y, 0), action_control[cm_id_C]);	dmdl_add_entity(merge_ceiling[find_groups], mdlTempG);
				merge_ceiling[find_groups]->skin[0] = merged_skin_setC[find_groups];
				ptr_remove(mdlTempG);
			}
			
			//#####CREATE DEFINED CONTENT IF ITS NOT A FLOOR TYPE (CEILINGS)#######
			if(nxsCmData[cm_id_C].content!=9 && nxsCmData[cm_id_C].content!=0)
			{
				gen_ent_countC[_x][_y] = ent_create((nxs_files->pstring)[cm_id_C], vector(_x*step_x, _y*step_y, 0), action_control[cm_id_C]);
				if(!str_cmp((nxs_skins->pstring)[cm_id_C], "EMPTY")){ ent_morphskin(gen_ent_countC[_x][_y],(nxs_skins->pstring)[cm_id_C]); }
			}
		}
	}
	
	//CREATE THE MERGED ENTITIES
	ENTITY* lv_construct_walls[74];
	ENTITY* lv_construct_floors[74];
	ENTITY* lv_construct_ceiling[74];
	int _c = 0;
	for (; _c<nxs_tex_count; _c++)
	{
		lv_construct_walls[_c] = dmdl_create_instance(merge_walls[_c],vector(0,0,0), merged_acts[_c]);
	}
	
	int _c = 0;
	for (; _c<nxs_tex_countB; _c++)
	{
		lv_construct_floors[_c] = dmdl_create_instance(merge_floor[_c],vector(0,0,0), merged_actsB[_c]);
	}
	
	int _c = 0;
	for (; _c<nxs_tex_countC; _c++)
	{
		lv_construct_ceiling[_c] = dmdl_create_instance(merge_ceiling[_c],vector(0,0,0), merged_actsC[_c]);
	}
	
	//ALL DYNAMIC MODELS ARE NOW CONVERTED TO MERGED ENTITYS
	//DELETE ALL DYNAMIC MODELS - THEY WILL NO LONGER BE NEEDED
	int _x = 0;
	for (; _x<nxs_tex_count; _x++)
	{
		dmdl_delete(merge_walls[_x]);
	}
	
	int _x = 0;
	for (; _x<nxs_tex_countB; _x++)
	{
		dmdl_delete(merge_floor[_x]);
	}
	
	int _x = 0;
	for (; _x<nxs_tex_countC; _x++)
	{
		dmdl_delete(merge_ceiling[_x]);
	}
	
	reset(nxs_loading_pan,SHOW);
	sys_marker(NULL);
	nxsGen_complete = true;
	
	while(1)
	{
		//Wait until level is closed and remove all entities and bmaps
		if(nxsGen_complete==false)
		{
			int _c = 0;
			for (; _c<nxs_tex_count; _c++)
			{
				ptr_remove(lv_construct_walls[_c]);
			}
			int _c = 0;
			for (; _c<nxs_tex_countB; _c++)
			{
				ptr_remove(lv_construct_floors[_c]);
			}
			int _c = 0;
			for (; _c<nxs_tex_countC; _c++)
			{
				ptr_remove(lv_construct_ceiling[_c]);
			}
			
			//////
			
			int _x = 0;
			for (; _x<nxs_tex_count; _x++)
			{
				bmap_remove(merged_skin_set[_x]);
			}
			int _x = 0;
			for (; _x<nxs_tex_countB; _x++)
			{
				bmap_remove(merged_skin_setB[_x]);
			}
			int _x = 0;
			for (; _x<nxs_tex_countC; _x++)
			{
				bmap_remove(merged_skin_setC[_x]);
			}
			
			break;
		}
		wait(1);
	}
}