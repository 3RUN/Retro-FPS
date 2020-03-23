///*#########################################################################################################################################################
//NEXUS A8 : GAME BUILDER :: By Brian Pressley (Evo) (Evoeon) :::: Core Script Functions :: Lite-C :: 3DGamestudio A8
//#########################################################################################################################################################*/


//EDITOR MOUSE
void call_mouse(){mouse_mode=4;mouse_map = arrow;while(1){vec_set(&mouse_pos,&mouse_cursor);wait(1);}}


//BREAKS STRINGS INTO SEPARATE LINES WHEN SAVING DATA
void next_line(){file_asc_write (default_handle, 13); file_asc_write (default_handle, 10);}


//TOP MENU ICON BUTTONS :  Layer Toggle - Select build mode - select event mode - Open settings menu
void toggle_layers()
{
	if(Set_toggle_layers==0){str_cpy(editor_layer_txt, "Layer 2 : Objects"); Set_toggle_layers=1;return;}
	if(Set_toggle_layers==1){str_cpy(editor_layer_txt, "Layer 3 : Overlay"); Set_toggle_layers=2;return;}
	if(Set_toggle_layers==2){str_cpy(editor_layer_txt, "Layer 1 : Ground"); Set_toggle_layers=0;return;}
}
void activate_build_mode(){show_active_grid.red=255; show_active_grid.green=128; show_active_grid.blue=128; editor_mode = 0; str_cpy(editor_mode_txt,"Build Mode Enabled");} //TILEMAP EDITING
void activate_event_mode(){show_active_grid.red=255; show_active_grid.green=127; show_active_grid.blue=0; editor_mode = 1; str_cpy(editor_mode_txt,"Event Mode Enabled");} //EVENT EDITING
void open_settings_menu(){set(show_weather_name,SHOW); set(show_settings_menu,SHOW); set(show_weather_name,SHOW);} //SETTINGS MENU


//EDIT FOG SETTING
void change_fognear_minus()   { settings_val_near-=64; if(settings_val_near<=0)    {settings_val_near=0;}    }
void change_fognear_plus()    { settings_val_near+=64; if(settings_val_near>=1024) {settings_val_near=1024;} }
void change_fogfar_minus()    { settings_val_far-=64;  if(settings_val_far<=0)     {settings_val_far=0;}     }
void change_fogfar_plus()     { settings_val_far+=64;  if(settings_val_far>=2048)  {settings_val_far=2048;}  }


//EDIT LEVEL TIME SETTING
void change_timemin_minus()   { settings_val_min-=1;   if(settings_val_min<=-1)    {settings_val_min=60;}    }
void change_timemin_plus()    { settings_val_min+=1;   if(settings_val_min>=61)    {settings_val_min=0;}     }
void change_timesec_minus()   { settings_val_sec-=5;   if(settings_val_sec<=-1)    {settings_val_sec=55;}    }
void change_timesec_plus()    { settings_val_sec+=5;   if(settings_val_sec>=60)    {settings_val_sec=0;}     }


//EDIT LEVEL WEATHER
void set_weather_name()
{
	if(settings_weather==0){str_cpy(weather_name,"Weather : None");}
	if(settings_weather==1){str_cpy(weather_name,"Weather : Rain");}
	if(settings_weather==2){str_cpy(weather_name,"Weather : Storm");}
	if(settings_weather==3){str_cpy(weather_name,"Weather : Snow");}
}
void change_weather_minus(){settings_weather-=1; if(settings_weather<=0){settings_weather=0;} set_weather_name();}
void change_weather_plus(){settings_weather+=1; if(settings_weather>=3){settings_weather=3;} set_weather_name();}


//CLOSE SETTINGS MENU
void close_settings_menu(){mouse_mode=0; reset(show_weather_name,SHOW); reset(show_settings_menu,SHOW); reset(show_weather_name,SHOW); wait(16); mouse_mode=4;}


//SWITCH BETWEEN TILESETS
void identify_tileset()
{
	if(tileset_type==1){tileset_A_panel.bmap = tileset_A;  str_cpy(tileset_names, "Content 1");}
	if(tileset_type==2){tileset_A_panel.bmap = tileset_A1; str_cpy(tileset_names, "Content 2");}
	if(tileset_type==3){tileset_A_panel.bmap = tileset_A2; str_cpy(tileset_names, "Content 3");}
	if(tileset_type==4){tileset_A_panel.bmap = tileset_A3; str_cpy(tileset_names, "Content 4");}
	if(tileset_type==5){tileset_A_panel.bmap = tileset_A4; str_cpy(tileset_names, "Content 5");}
	if(tileset_type==6){tileset_A_panel.bmap = tileset_A5; str_cpy(tileset_names, "Content 6");}
	if(tileset_type==7){tileset_A_panel.bmap = tileset_A6; str_cpy(tileset_names, "Content 7");}
	if(tileset_type==8){tileset_A_panel.bmap = tileset_A7; str_cpy(tileset_names, "Content 8");}
}
void change_tileset_minus()
{
	tileset_type-=1; 
	if(tileset_type<=1){tileset_type=1;}
	identify_tileset();
}
void change_tileset_plus()
{
	tileset_type+=1; 
	if(tileset_type>=8){tileset_type=8;}
	identify_tileset();
}


//LEFT MOUSE BUTTON : WHEN ANY GRID TILE IS CLICKED IT SETS CORRECT TILE DATA THEN CALLS THE DRAW FUNCTION
void interactive_grid()
{
	if(editor_mode!=0){return;}
	over_pan_id = mouse_panel;
	if(over_pan_id->bmap==tile_menu || over_pan_id->bmap==editor_overlay || over_pan_id->bmap==editor_bg_panel || over_pan_id->bmap==intro_panel ||
	over_pan_id->bmap==icon_bu || over_pan_id->bmap==tile_icon_menu || over_pan_id->bmap==content_menu || over_pan_id->bmap==chapter_menu ||
	over_pan_id->bmap==popup_overlay || over_pan_id->bmap==popup_set_id || over_pan_id->bmap==popup_use_id || over_pan_id->bmap==settings_menu){return;}
	tempXY[0] = over_pan_id->skill_x;
	tempXY[1] = over_pan_id->skill_y;
	if(Set_toggle_layers==0)
	{
		tiles[over_pan_id->skill_x][over_pan_id->skill_y].type = build_type;
		tiles[over_pan_id->skill_x][over_pan_id->skill_y].tileset = tileset_type;
		tiles[over_pan_id->skill_x][over_pan_id->skill_y].switchID = 0;
		tiles[over_pan_id->skill_x][over_pan_id->skill_y].triggerID = 0;
		tiles[over_pan_id->skill_x][over_pan_id->skill_y].rotation = 0;
		pan_arrayA[over_pan_id->skill_x][over_pan_id->skill_y].angle=0;
	}
	if(Set_toggle_layers==1)
	{
		tilesB[over_pan_id->skill_x][over_pan_id->skill_y].type = build_type;
		tilesB[over_pan_id->skill_x][over_pan_id->skill_y].tileset = tileset_type;
		tilesB[over_pan_id->skill_x][over_pan_id->skill_y].switchID = 0;
		tilesB[over_pan_id->skill_x][over_pan_id->skill_y].triggerID = 0;
		tilesB[over_pan_id->skill_x][over_pan_id->skill_y].rotation = 0;
		pan_arrayB[over_pan_id->skill_x][over_pan_id->skill_y].angle=0;
	}
	if(Set_toggle_layers==2)
	{
		tilesC[over_pan_id->skill_x][over_pan_id->skill_y].type = build_type;
		tilesC[over_pan_id->skill_x][over_pan_id->skill_y].tileset = tileset_type;
		tilesC[over_pan_id->skill_x][over_pan_id->skill_y].switchID = 0;
		tilesC[over_pan_id->skill_x][over_pan_id->skill_y].triggerID = 0;
		tilesC[over_pan_id->skill_x][over_pan_id->skill_y].rotation = 0;
		pan_arrayC[over_pan_id->skill_x][over_pan_id->skill_y].angle=0;
	}
	edit_cell_tile();
}


//RIGHT MOUSE BUTTON : WHEN ANY GRID TILE IS CLICKED : REMOVE THE TILE
void reset_a_tile()
{
	if(editor_mode!=0){return;}
	over_pan_id = mouse_panel;
	if(over_pan_id->bmap==tile_menu || over_pan_id->bmap==editor_overlay || over_pan_id->bmap==editor_bg_panel || over_pan_id->bmap==intro_panel ||
	over_pan_id->bmap==icon_bu || over_pan_id->bmap==tile_icon_menu || over_pan_id->bmap==content_menu || over_pan_id->bmap==chapter_menu ||
	over_pan_id->bmap==popup_overlay || over_pan_id->bmap==popup_set_id || over_pan_id->bmap==popup_use_id || over_pan_id->bmap==settings_menu){return;}
	tempXY[0] = over_pan_id->skill_x;
	tempXY[1] = over_pan_id->skill_y;
	if(Set_toggle_layers==0)
	{
		tiles[over_pan_id->skill_x][over_pan_id->skill_y].type = 0;
		tiles[over_pan_id->skill_x][over_pan_id->skill_y].tileset = 1;
		tiles[over_pan_id->skill_x][over_pan_id->skill_y].switchID = 0;
		tiles[over_pan_id->skill_x][over_pan_id->skill_y].triggerID = 0;
		tiles[over_pan_id->skill_x][over_pan_id->skill_y].rotation = 0;
		pan_arrayA[over_pan_id->skill_x][over_pan_id->skill_y].angle=0;
		popup_swt_id = 0; popup_tri_id = 0;
	}
	if(Set_toggle_layers==1)
	{
		tilesB[over_pan_id->skill_x][over_pan_id->skill_y].type = 0;
		tilesB[over_pan_id->skill_x][over_pan_id->skill_y].tileset = 1;
		tilesB[over_pan_id->skill_x][over_pan_id->skill_y].switchID = 0;
		tilesB[over_pan_id->skill_x][over_pan_id->skill_y].triggerID = 0;
		tilesB[over_pan_id->skill_x][over_pan_id->skill_y].rotation = 0;
		pan_arrayB[over_pan_id->skill_x][over_pan_id->skill_y].angle=0;
	}
	if(Set_toggle_layers==2)
	{
		tilesC[over_pan_id->skill_x][over_pan_id->skill_y].type = 0;
		tilesC[over_pan_id->skill_x][over_pan_id->skill_y].tileset = 1;
		tilesC[over_pan_id->skill_x][over_pan_id->skill_y].switchID = 0;
		tilesC[over_pan_id->skill_x][over_pan_id->skill_y].triggerID = 0;
		tilesC[over_pan_id->skill_x][over_pan_id->skill_y].rotation = 0;
		pan_arrayC[over_pan_id->skill_x][over_pan_id->skill_y].angle=0;
	}
	edit_cell_tile();
}


//EMPTY LEVEL : RESETS ALL TILES
void reset_the_level()
{
	resetting_the_lv = true;
	Set_toggle_layers = 0;
	int _x = 0;
	for (; _x<LEVEL_X_MAX; _x++) 
	{
		int _y = 0;
		for (; _y<LEVEL_Y_MAX; _y++) 
		{
			tiles[_x][_y].type = 0;
			tiles[_x][_y].tileset = 1;
			tiles[_x][_y].switchID = 0;
			tiles[_x][_y].triggerID = 0;
			tiles[_x][_y].rotation = 0;
			
			tilesB[_x][_y].type = 0;
			tilesB[_x][_y].tileset = 1;
			tilesB[_x][_y].switchID = 0;
			tilesB[_x][_y].triggerID = 0;
			tilesB[_x][_y].rotation = 0;
			
			tilesC[_x][_y].type = 0;
			tilesC[_x][_y].tileset = 1;
			tilesC[_x][_y].switchID = 0;
			tilesC[_x][_y].triggerID = 0;
			tilesC[_x][_y].rotation = 0;
			
			tempXY[0] = _x;  tempXY[1] = _y;  edit_cell_tile();
		}
	}
	resetting_the_lv = false;
	build_type=1;
	cursor_over.pos_x = 1134;
	cursor_over.pos_y = 64;
}


//BUILDS THE INTERACTIVE GRID TILES : LAYERS
void build_grid_layer_A()
{
	var _stepX = 32;
	var _stepY = 32;
	int _x = 0;
	for (; _x<LEVEL_X_MAX; _x++)
	{
		int _y = 0;
		for (; _y<LEVEL_Y_MAX; _y++) 
		{
			pan_arrayA[_x][_y] = pan_create("window(0,0,32,32,tileset_A,pan_arrayA_wx[_x][_y],pan_arrayA_wy[_x][_y]); on_click=interactive_grid;",1);
			pan_arrayA[_x][_y]->pos_x=_x*_stepX;
			pan_arrayA[_x][_y]->pos_y=_y*_stepY;
			pan_arrayA[_x][_y]->size_x=32;
			pan_arrayA[_x][_y]->size_y=32;
			pan_arrayA[_x][_y]->skill_x=_x;
			pan_arrayA[_x][_y]->skill_y=_y;
			pan_arrayA[_x][_y]->pos_y+=32;
			pan_arrayA[_x][_y]->alpha=10;
			set(pan_arrayA[_x][_y],SHOW);
			
			pan_arrayB[_x][_y] = pan_create("window(0,0,32,32,tileset_A,pan_arrayB_wx[_x][_y],pan_arrayB_wy[_x][_y]); on_click=interactive_grid;",3);
			pan_arrayB[_x][_y]->pos_x=_x*_stepX;
			pan_arrayB[_x][_y]->pos_y=_y*_stepY;
			pan_arrayB[_x][_y]->size_x=32;
			pan_arrayB[_x][_y]->size_y=32;
			pan_arrayB[_x][_y]->skill_x=_x;
			pan_arrayB[_x][_y]->skill_y=_y;
			pan_arrayB[_x][_y]->pos_y+=32;
			pan_arrayB[_x][_y]->alpha=10;
			set(pan_arrayB[_x][_y],SHOW);
			
			pan_arrayC[_x][_y] = pan_create("window(0,0,32,32,tileset_A,pan_arrayC_wx[_x][_y],pan_arrayC_wy[_x][_y]); on_click=interactive_grid;",5);
			pan_arrayC[_x][_y]->pos_x=_x*_stepX;
			pan_arrayC[_x][_y]->pos_y=_y*_stepY;
			pan_arrayC[_x][_y]->size_x=32;
			pan_arrayC[_x][_y]->size_y=32;
			pan_arrayC[_x][_y]->skill_x=_x;
			pan_arrayC[_x][_y]->skill_y=_y;
			pan_arrayC[_x][_y]->pos_y+=32;
			pan_arrayC[_x][_y]->alpha=10;
			set(pan_arrayC[_x][_y],SHOW);
		}
	}
	level_active = true;
	reset_the_level();
}


//DELETES THE INTERACTIVE GRID TILES : LAYERS
void delete_grid()
{
	level_active = false;
	int _x = 0;
	for (; _x<LEVEL_X_MAX; _x++) 
	{
		int _y = 0;
		for (; _y<LEVEL_Y_MAX; _y++) 
		{
			ptr_remove(pan_arrayA[_x][_y]);
			ptr_remove(pan_arrayB[_x][_y]);
			ptr_remove(pan_arrayC[_x][_y]);
		}
	}
}


//SIDE MENU TILESET FUNCTIONS : CLICK TO SELECT ANY TILE FROM THE TILESET MENU
void tileset_A_clicked()
{
	over_pan_id = mouse_panel;
	build_type = tileset_A_functions[over_pan_id->skill_x][over_pan_id->skill_y];
	cursor_over.pos_x = tileset_A_buttons[over_pan_id->skill_x][over_pan_id->skill_y]->pos_x;
	cursor_over.pos_y = tileset_A_buttons[over_pan_id->skill_x][over_pan_id->skill_y]->pos_y;
	reset(show_active_grid,SHOW); set(show_active_tileset,SHOW);
	while(mouse_left==1){wait(1);}
}


//BUILD SIDE MENU TILESET BUTTONS : 75 TOTAL
void build_tileset_buttons()
{
	int _y = 0;
	int _c = 0;
	int _posx=32;
	int _posy=32;
	for (; _y<15; _y++)
	{
		int _x = 0;
		for (; _x<5; _x++)
		{
			tileset_A_buttons[_x][_y] = pan_create("bmap=icon_bu; pos_x=1102; pos_y=64; on_click=tileset_A_clicked;",12);
			tileset_A_buttons[_x][_y]->pos_x=1102+_x*_posx;
			tileset_A_buttons[_x][_y]->pos_y=64+_y*_posy;
			tileset_A_buttons[_x][_y]->size_x=32;
			tileset_A_buttons[_x][_y]->size_y=32;
			tileset_A_buttons[_x][_y]->skill_x=_x;
			tileset_A_buttons[_x][_y]->skill_y=_y;
			tileset_A_functions[_x][_y]=_c;
			set(tileset_A_buttons[_x][_y],SHOW);
			_c+=1;
		}
	}
}


//IMPORT A SKYCUBE IMAGE TO SAVE ITS FILE NAME
void import_skybox_name()
{
	int _i = 0;
	int pos = 0;
	int slash_pos = 0;
	char* filename = file_dialog("Set skycube","*.png;*.tga;*.pcx;*.dds");
	int path_len = str_len(filename);
	if(filename)
	{
		for (; _i<path_len; _i++)
		{
			pos = str_stri(filename,"\\");
			if(pos)
			{
				slash_pos = str_chr(filename,pos,'\\'); 
				filename = str_cut(NULL,filename,slash_pos+1,-pos);	
			}
			else{break;}
		}
		str_cpy(set_skybox_name,filename);
	}
	STRING* gotofile = str_create(work_dir); SetCurrentDirectory(_chr(gotofile));
}


//IMPORT AN AUDIO FILE TO SAVE ITS FILE NAME
void import_audio_name()
{
	int _i = 0;
	int pos = 0;
	int slash_pos = 0;
	char* filename = file_dialog("Set audio","*.ogg;*.wav");
	int path_len = str_len(filename);
	if(filename)
	{
		for (; _i<path_len; _i++)
		{
			pos = str_stri(filename,"\\");
			if(pos)
			{
				slash_pos = str_chr(filename,pos,'\\'); 
				filename = str_cut(NULL,filename,slash_pos+1,-pos);	
			}
			else{break;}
		}
		str_cpy(set_audio_name,filename);
	}
	STRING* gotofile = str_create(work_dir); SetCurrentDirectory(_chr(gotofile));
}


//IMPORT A FLOOR TEXTURE TO SAVE ITS FILE NAME
void import_floor_name()
{
	int _i = 0;
	int pos = 0;
	int slash_pos = 0;
	char* filename = file_dialog("Set Floor Texture","*.png;*.tga;*.pcx;*.dds");
	int path_len = str_len(filename);
	if(filename)
	{
		for (; _i<path_len; _i++)
		{
			pos = str_stri(filename,"\\");
			if(pos)
			{
				slash_pos = str_chr(filename,pos,'\\'); 
				filename = str_cut(NULL,filename,slash_pos+1,-pos);	
			}
			else{break;}
		}
		str_cpy(set_floor_name,filename);
	}
	STRING* gotofile = str_create(work_dir); SetCurrentDirectory(_chr(gotofile));
}


//IMPORT A CEILING TEXTURE TO SAVE ITS FILE NAME
void import_ceiling_name()
{
	int _i = 0;
	int pos = 0;
	int slash_pos = 0;
	char* filename = file_dialog("Set Ceiling Texture","*.png;*.tga;*.pcx;*.dds");
	int path_len = str_len(filename);
	if(filename)
	{
		for (; _i<path_len; _i++)
		{
			pos = str_stri(filename,"\\");
			if(pos)
			{
				slash_pos = str_chr(filename,pos,'\\'); 
				filename = str_cut(NULL,filename,slash_pos+1,-pos);	
			}
			else{break;}
		}
		str_cpy(set_ceiling_name,filename);
	}
	STRING* gotofile = str_create(work_dir); SetCurrentDirectory(_chr(gotofile));
}


//LOADS A SAVED LEVEL FILE
void load_level_from_file()
{
	activate_build_mode();
	textboxMe=NULL;wait(1);
	int _i = 0;
	int pos = 0;
	int slash_pos = 0;
	STRING* set_title = "";
	int str_set = 0;
	char* filename = file_dialog("Load Level File",NULL);
	int path_len = str_len(filename);
	if(filename)
	{
		mouse_mode=0;
		str_cpy(set_title,filename);
		load_lv_from_file = true;
		default_handle = file_open_read (filename);
		file_str_read(default_handle,extension_type);
		if(!str_cmp(extension_type, ".nxs")){file_close (default_handle); printf("Wrong file type.\n\nThis is not a Nexus level file!"); STRING* gotofile = str_create(work_dir); SetCurrentDirectory(_chr(gotofile)); mouse_mode=4;return;}
		file_str_read(default_handle,set_skybox_name);
		file_str_read(default_handle,set_audio_name);
		file_str_read(default_handle,set_floor_name);
		file_str_read(default_handle,set_ceiling_name);
		settings_val_near = file_var_read (default_handle);
		settings_val_far = file_var_read (default_handle);
		settings_val_min = file_var_read (default_handle);
		settings_val_sec = file_var_read (default_handle);
		settings_weather = file_var_read (default_handle);
		int _x = 0;
		for (; _x<LEVEL_X_MAX; _x++)
		{
			int _y = 0;
			for (; _y<LEVEL_Y_MAX; _y++)
			{
				tiles[_x][_y].type = file_var_read (default_handle);
				tiles[_x][_y].tileset = file_var_read (default_handle);
				tiles[_x][_y].switchID = file_var_read (default_handle);
				tiles[_x][_y].triggerID = file_var_read (default_handle);
				tiles[_x][_y].rotation = file_var_read (default_handle);
				pan_arrayA[_x][_y].center_x = pan_arrayA[_x][_y].size_x * 0.490; 
				pan_arrayA[_x][_y].center_y = pan_arrayA[_x][_y].size_y * 0.490; 
				pan_arrayA[_x][_y]->angle = tiles[_x][_y].rotation;
				
				tilesB[_x][_y].type = file_var_read (default_handle);
				tilesB[_x][_y].tileset = file_var_read (default_handle);
				tilesB[_x][_y].switchID = file_var_read (default_handle);
				tilesB[_x][_y].triggerID = file_var_read (default_handle);
				tilesB[_x][_y].rotation = file_var_read (default_handle);
				pan_arrayB[_x][_y].center_x = pan_arrayB[_x][_y].size_x * 0.490; 
				pan_arrayB[_x][_y].center_y = pan_arrayB[_x][_y].size_y * 0.490; 
				pan_arrayB[_x][_y]->angle = tilesB[_x][_y].rotation;
				
				tilesC[_x][_y].type = file_var_read (default_handle);
				tilesC[_x][_y].tileset = file_var_read (default_handle);
				tilesC[_x][_y].switchID = file_var_read (default_handle);
				tilesC[_x][_y].triggerID = file_var_read (default_handle);
				tilesC[_x][_y].rotation = file_var_read (default_handle);
				pan_arrayC[_x][_y].center_x = pan_arrayC[_x][_y].size_x * 0.490; 
				pan_arrayC[_x][_y].center_y = pan_arrayC[_x][_y].size_y * 0.490; 
				pan_arrayC[_x][_y]->angle = tilesC[_x][_y].rotation;
				
				tempXY[0] = _x;  tempXY[1] = _y;  edit_cell_tile();
			}
		}
		for (; _i<path_len; _i++)
		{
			pos = str_stri(set_title,"\\");
			if(pos)
			{
				slash_pos = str_chr(set_title,pos,'\\'); 
				set_title = str_cut(NULL,set_title,slash_pos+1,-pos);	
			}
			else{break;}
		}
		str_cpy(lv_nm_on_main,set_title);
		file_close (default_handle);
		STRING* gotofile = str_create(work_dir); SetCurrentDirectory(_chr(gotofile));
	}
	set_weather_name();
	load_lv_from_file = false;
	wait(-2);
	mouse_mode=4;
}


//SAVES A LEVEL TO FILE
void save_level_to_file()
{
	int _len = 0;
	int _i = 0;
	int pos = 0;
	int slash_pos = 0;
	STRING* set_title = "";
	int str_set = 0;
	char* filename = file_dialog_save("Save Level File",NULL);
	int path_len = str_len(filename);
	if(filename)
	{
		mouse_mode=0;
		str_cpy(set_title,filename);
		default_handle = file_open_write(filename);
		file_str_write(default_handle,".nxs");next_line();
		file_str_write(default_handle,set_skybox_name);next_line();
		file_str_write(default_handle,set_audio_name);next_line();
		file_str_write(default_handle,set_floor_name);next_line();
		file_str_write(default_handle,set_ceiling_name);next_line();
		file_var_write (default_handle, settings_val_near);
		file_var_write (default_handle, settings_val_far);
		file_var_write (default_handle, settings_val_min);
		file_var_write (default_handle, settings_val_sec);
		file_var_write (default_handle, settings_weather);next_line();
		int _x = 0;
		for (; _x<LEVEL_X_MAX; _x++)
		{
			int _y = 0;
			for (; _y<LEVEL_Y_MAX; _y++)
			{
				file_var_write (default_handle, tiles[_x][_y].type);
				file_var_write (default_handle, tiles[_x][_y].tileset);
				file_var_write (default_handle, tiles[_x][_y].switchID);
				file_var_write (default_handle, tiles[_x][_y].triggerID);
				file_var_write (default_handle, tiles[_x][_y].rotation);
				
				file_var_write (default_handle, tilesB[_x][_y].type);
				file_var_write (default_handle, tilesB[_x][_y].tileset);
				file_var_write (default_handle, tilesB[_x][_y].switchID);
				file_var_write (default_handle, tilesB[_x][_y].triggerID);
				file_var_write (default_handle, tilesB[_x][_y].rotation);
				
				file_var_write (default_handle, tilesC[_x][_y].type);
				file_var_write (default_handle, tilesC[_x][_y].tileset);
				file_var_write (default_handle, tilesC[_x][_y].switchID);
				file_var_write (default_handle, tilesC[_x][_y].triggerID);
				file_var_write (default_handle, tilesC[_x][_y].rotation);
			}
		}
		for (; _i<path_len; _i++)
		{
			pos = str_stri(set_title,"\\");
			if(pos)
			{
				slash_pos = str_chr(set_title,pos,'\\'); 
				set_title = str_cut(NULL,set_title,slash_pos+1,-pos);	
			}
			else{break;}
		}
		str_cpy(lv_nm_on_main,set_title);
		file_close (default_handle);
		STRING* gotofile = str_create(work_dir); SetCurrentDirectory(_chr(gotofile));
	}
	wait(-2);
	mouse_mode=4;
}


//DRAWS ANY SELECTED TILE ON THE LEVEL GRID
void edit_cell_tile()
{
	//RESET ALL LAYERS
	if(resetting_the_lv == true)
	{
		pan_arrayA_wx[tempXY[0]][tempXY[1]] = 0;	
		pan_arrayA_wy[tempXY[0]][tempXY[1]] = 0; 
		pan_setwindow(pan_arrayA[tempXY[0]][tempXY[1]],1,0,0,32,32,tileset_A,pan_arrayA_wx[tempXY[0]][tempXY[1]],pan_arrayA_wy[tempXY[0]][tempXY[1]]);
		pan_arrayA[tempXY[0]][tempXY[1]]->alpha = 100;
		
		pan_arrayB_wx[tempXY[0]][tempXY[1]] = 0;	
		pan_arrayB_wy[tempXY[0]][tempXY[1]] = 0; 
		pan_setwindow(pan_arrayB[tempXY[0]][tempXY[1]],1,0,0,32,32,tileset_A,pan_arrayB_wx[tempXY[0]][tempXY[1]],pan_arrayB_wy[tempXY[0]][tempXY[1]]);
		pan_arrayB[tempXY[0]][tempXY[1]]->alpha = 100;
		
		pan_arrayC_wx[tempXY[0]][tempXY[1]] = 0;	
		pan_arrayC_wy[tempXY[0]][tempXY[1]] = 0; 
		pan_setwindow(pan_arrayC[tempXY[0]][tempXY[1]],1,0,0,32,32,tileset_A,pan_arrayC_wx[tempXY[0]][tempXY[1]],pan_arrayC_wy[tempXY[0]][tempXY[1]]);
		pan_arrayC[tempXY[0]][tempXY[1]]->alpha = 100;
	}
	
	//DRAW EMPTY TILE IF ID 0
	if(tiles[tempXY[0]][tempXY[1]].type == 0 && Set_toggle_layers == 0)
	{
		pan_arrayA_wx[tempXY[0]][tempXY[1]] = 0;	
		pan_arrayA_wy[tempXY[0]][tempXY[1]] = 0; 
		pan_setwindow(pan_arrayA[tempXY[0]][tempXY[1]],1,0,0,32,32,tileset_A,pan_arrayA_wx[tempXY[0]][tempXY[1]],pan_arrayA_wy[tempXY[0]][tempXY[1]]);
		pan_arrayA[tempXY[0]][tempXY[1]]->alpha = 100;
	}
	if(tilesB[tempXY[0]][tempXY[1]].type == 0 && Set_toggle_layers == 1)
	{
		pan_arrayB_wx[tempXY[0]][tempXY[1]] = 0;	
		pan_arrayB_wy[tempXY[0]][tempXY[1]] = 0; 
		pan_setwindow(pan_arrayB[tempXY[0]][tempXY[1]],1,0,0,32,32,tileset_A,pan_arrayB_wx[tempXY[0]][tempXY[1]],pan_arrayB_wy[tempXY[0]][tempXY[1]]);
		pan_arrayB[tempXY[0]][tempXY[1]]->alpha = 100;
	}
	if(tilesC[tempXY[0]][tempXY[1]].type == 0 && Set_toggle_layers == 2)
	{
		pan_arrayC_wx[tempXY[0]][tempXY[1]] = 0;	
		pan_arrayC_wy[tempXY[0]][tempXY[1]] = 0; 
		pan_setwindow(pan_arrayC[tempXY[0]][tempXY[1]],1,0,0,32,32,tileset_A,pan_arrayC_wx[tempXY[0]][tempXY[1]],pan_arrayC_wy[tempXY[0]][tempXY[1]]);
		pan_arrayC[tempXY[0]][tempXY[1]]->alpha = 100;
	}
	if(resetting_the_lv == true){return;}
	
	//First check which mode is active : Build Mode or Event Mode
	//Build Mode sets selected tileset/tile and draws it on the map
	//Event mode sets the saved tileset/tile IDS and edits the settings of the tile without drawing over it.
	BMAP* selected_tileset;
	BMAP* selected_tilesetB;
	BMAP* selected_tilesetC;
	if(editor_mode==0)//BUILD MODE IS ACTIVE
	{
		//IF LEVEL LOAD : READS FROM LEVEL FILES TO LOAD TILESET IDS AND REDRAWS THE LEVEL
		//ELSE : DRAW MODE IS ACTIVE AND SETS ANY SELECTED TILESET ID
		if(load_lv_from_file == true)
		{
			if(tiles[tempXY[0]][tempXY[1]].tileset==1){selected_tileset = tileset_A;}
			if(tiles[tempXY[0]][tempXY[1]].tileset==2){selected_tileset = tileset_A1;}
			if(tiles[tempXY[0]][tempXY[1]].tileset==3){selected_tileset = tileset_A2;}
			if(tiles[tempXY[0]][tempXY[1]].tileset==4){selected_tileset = tileset_A3;}
			if(tiles[tempXY[0]][tempXY[1]].tileset==5){selected_tileset = tileset_A4;}
			if(tiles[tempXY[0]][tempXY[1]].tileset==6){selected_tileset = tileset_A5;}
			if(tiles[tempXY[0]][tempXY[1]].tileset==7){selected_tileset = tileset_A6;}
			if(tiles[tempXY[0]][tempXY[1]].tileset==8){selected_tileset = tileset_A7;}
			
			if(tilesB[tempXY[0]][tempXY[1]].tileset==1){selected_tilesetB = tileset_A;}
			if(tilesB[tempXY[0]][tempXY[1]].tileset==2){selected_tilesetB = tileset_A1;}
			if(tilesB[tempXY[0]][tempXY[1]].tileset==3){selected_tilesetB = tileset_A2;}
			if(tilesB[tempXY[0]][tempXY[1]].tileset==4){selected_tilesetB = tileset_A3;}
			if(tilesB[tempXY[0]][tempXY[1]].tileset==5){selected_tilesetB = tileset_A4;}
			if(tilesB[tempXY[0]][tempXY[1]].tileset==6){selected_tilesetB = tileset_A5;}
			if(tilesB[tempXY[0]][tempXY[1]].tileset==7){selected_tilesetB = tileset_A6;}
			if(tilesB[tempXY[0]][tempXY[1]].tileset==8){selected_tilesetB = tileset_A7;}
			
			if(tilesC[tempXY[0]][tempXY[1]].tileset==1){selected_tilesetC = tileset_A;}
			if(tilesC[tempXY[0]][tempXY[1]].tileset==2){selected_tilesetC = tileset_A1;}
			if(tilesC[tempXY[0]][tempXY[1]].tileset==3){selected_tilesetC = tileset_A2;}
			if(tilesC[tempXY[0]][tempXY[1]].tileset==4){selected_tilesetC = tileset_A3;}
			if(tilesC[tempXY[0]][tempXY[1]].tileset==5){selected_tilesetC = tileset_A4;}
			if(tilesC[tempXY[0]][tempXY[1]].tileset==6){selected_tilesetC = tileset_A5;}
			if(tilesC[tempXY[0]][tempXY[1]].tileset==7){selected_tilesetC = tileset_A6;}
			if(tilesC[tempXY[0]][tempXY[1]].tileset==8){selected_tilesetC = tileset_A7;}
		}
		else
		{
			if(tileset_type==1){selected_tileset = tileset_A;}
			if(tileset_type==2){selected_tileset = tileset_A1;}
			if(tileset_type==3){selected_tileset = tileset_A2;}
			if(tileset_type==4){selected_tileset = tileset_A3;}
			if(tileset_type==5){selected_tileset = tileset_A4;}
			if(tileset_type==6){selected_tileset = tileset_A5;}
			if(tileset_type==7){selected_tileset = tileset_A6;}
			if(tileset_type==8){selected_tileset = tileset_A7;}
		}
	}
	else //EVENT MODE IS ACTIVE
	{
		if(cm_tileset_id==1){selected_tileset = tileset_A;}
		if(cm_tileset_id==2){selected_tileset = tileset_A1;}
		if(cm_tileset_id==3){selected_tileset = tileset_A2;}
		if(cm_tileset_id==4){selected_tileset = tileset_A3;}
		if(cm_tileset_id==5){selected_tileset = tileset_A4;}
		if(cm_tileset_id==6){selected_tileset = tileset_A5;}
		if(cm_tileset_id==7){selected_tileset = tileset_A6;}
		if(cm_tileset_id==8){selected_tileset = tileset_A7;}
	}
	
	//DRAW SELECTED TILE FROM THE TILESET
	int _y = 0;
	int _c = 0;
	int _step=32;
	for (; _y<15; _y++)
	{
		int _x = 0;
		for (; _x<5; _x++)
		{
			if(tiles[tempXY[0]][tempXY[1]].type == _c && Set_toggle_layers == 0)
			{
				pan_arrayA_wx[tempXY[0]][tempXY[1]] = _x*_step;	
				pan_arrayA_wy[tempXY[0]][tempXY[1]] = _y*_step;
				pan_setwindow(pan_arrayA[tempXY[0]][tempXY[1]],1,0,0,32,32,selected_tileset,pan_arrayA_wx[tempXY[0]][tempXY[1]],pan_arrayA_wy[tempXY[0]][tempXY[1]]);
				if(tiles[tempXY[0]][tempXY[1]].type == 0){pan_arrayA[tempXY[0]][tempXY[1]]->alpha = 2;}else{pan_arrayA[tempXY[0]][tempXY[1]]->alpha = 100;}
			}
			if(tilesB[tempXY[0]][tempXY[1]].type == _c && Set_toggle_layers == 1)
			{
				pan_arrayB_wx[tempXY[0]][tempXY[1]] = _x*_step;	
				pan_arrayB_wy[tempXY[0]][tempXY[1]] = _y*_step;
				if(load_lv_from_file == true){pan_setwindow(pan_arrayB[tempXY[0]][tempXY[1]],1,0,0,32,32,selected_tilesetB,pan_arrayB_wx[tempXY[0]][tempXY[1]],pan_arrayB_wy[tempXY[0]][tempXY[1]]);}
				else{pan_setwindow(pan_arrayB[tempXY[0]][tempXY[1]],1,0,0,32,32,selected_tileset,pan_arrayB_wx[tempXY[0]][tempXY[1]],pan_arrayB_wy[tempXY[0]][tempXY[1]]);}
				if(tilesB[tempXY[0]][tempXY[1]].type == 0){pan_arrayB[tempXY[0]][tempXY[1]]->alpha = 2;}else{pan_arrayB[tempXY[0]][tempXY[1]]->alpha = 100;}
			}
			if(tilesC[tempXY[0]][tempXY[1]].type == _c && Set_toggle_layers == 2)
			{
				pan_arrayC_wx[tempXY[0]][tempXY[1]] = _x*_step;	
				pan_arrayC_wy[tempXY[0]][tempXY[1]] = _y*_step;
				if(load_lv_from_file == true){pan_setwindow(pan_arrayC[tempXY[0]][tempXY[1]],1,0,0,32,32,selected_tilesetC,pan_arrayC_wx[tempXY[0]][tempXY[1]],pan_arrayC_wy[tempXY[0]][tempXY[1]]);}
				else{pan_setwindow(pan_arrayC[tempXY[0]][tempXY[1]],1,0,0,32,32,selected_tileset,pan_arrayC_wx[tempXY[0]][tempXY[1]],pan_arrayC_wy[tempXY[0]][tempXY[1]]);}
				if(tilesC[tempXY[0]][tempXY[1]].type == 0){pan_arrayC[tempXY[0]][tempXY[1]]->alpha = 2;}else{pan_arrayC[tempXY[0]][tempXY[1]]->alpha = 100;}
			}
			
			if(tiles[tempXY[0]][tempXY[1]].type == _c && load_lv_from_file == true)
			{
				pan_arrayA_wx[tempXY[0]][tempXY[1]] = _x*_step;	
				pan_arrayA_wy[tempXY[0]][tempXY[1]] = _y*_step;
				pan_setwindow(pan_arrayA[tempXY[0]][tempXY[1]],1,0,0,32,32,selected_tileset,pan_arrayA_wx[tempXY[0]][tempXY[1]],pan_arrayA_wy[tempXY[0]][tempXY[1]]);
				if(tiles[tempXY[0]][tempXY[1]].type == 0){pan_arrayA[tempXY[0]][tempXY[1]]->alpha = 2;}else{pan_arrayA[tempXY[0]][tempXY[1]]->alpha = 100;}
			}
			if(tilesB[tempXY[0]][tempXY[1]].type == _c && load_lv_from_file == true)
			{
				pan_arrayB_wx[tempXY[0]][tempXY[1]] = _x*_step;	
				pan_arrayB_wy[tempXY[0]][tempXY[1]] = _y*_step;
				pan_setwindow(pan_arrayB[tempXY[0]][tempXY[1]],1,0,0,32,32,selected_tilesetB,pan_arrayB_wx[tempXY[0]][tempXY[1]],pan_arrayB_wy[tempXY[0]][tempXY[1]]);
				if(tilesB[tempXY[0]][tempXY[1]].type == 0){pan_arrayB[tempXY[0]][tempXY[1]]->alpha = 2;}else{pan_arrayB[tempXY[0]][tempXY[1]]->alpha = 100;}
			}
			if(tilesC[tempXY[0]][tempXY[1]].type == _c && load_lv_from_file == true)
			{
				pan_arrayC_wx[tempXY[0]][tempXY[1]] = _x*_step;	
				pan_arrayC_wy[tempXY[0]][tempXY[1]] = _y*_step;
				pan_setwindow(pan_arrayC[tempXY[0]][tempXY[1]],1,0,0,32,32,selected_tilesetC,pan_arrayC_wx[tempXY[0]][tempXY[1]],pan_arrayC_wy[tempXY[0]][tempXY[1]]);
				if(tilesC[tempXY[0]][tempXY[1]].type == 0){pan_arrayC[tempXY[0]][tempXY[1]]->alpha = 2;}else{pan_arrayC[tempXY[0]][tempXY[1]]->alpha = 100;}
			}
			_c+=1;
		}
	}
}


//INIT THE EDITOR
void init_editor()
{
	int _x = 0;
	for (; _x<600; _x++)
	{
		str_cpy((nxs_actions.pstring)[_x], "EMPTY");
		str_cpy((nxs_files.pstring)[_x], "EMPTY"); 
		str_cpy((nxs_skins.pstring)[_x], "EMPTY"); 
	}
	build_grid_layer_A();
	build_tileset_buttons();
	identify_tileset();
	ch_menu_textboxes();
	content_menu_textboxes();
	load_editor_cm_data();
	reset_the_level();
}


//CLOSE THE EDITOR
void exit_editor()
{
	textbox_active = 10;
	content_textbox_active = 10;
	pan_textbox_remove_all();
	wait(3);
	sys_exit("exit");
}