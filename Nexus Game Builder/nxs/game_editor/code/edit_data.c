/*#########################################################################################################################################################
NEXUS A8 : GAME BUILDER :: By Brian Pressley (Evo) (Evoeon) :::: Popup Editing Menu FUNCTIONS :: Lite-C :: 3DGamestudio A8
#########################################################################################################################################################*/


//POPUP MENU TO SET SWITCH IDS, TRIGGER IDS AND ROTATION (EVENT MODE ONLY)
//PRESSING MOUSE LEFT WHILE THE MOUSE IS OVER A TILE ON THE GRID WILL OPEN THIS MENU
//Secret walls, doors, switches and triggers have a popup menu for IDs and Rotation.
//All other types except standard walls and floors have rotation only.
//Standard walls and floors do not have any popup options to modify.
void modify_tiles()
{
	if(editor_mode!=1){return;}
	mod_pan_active = true;
	over_pan_id = mouse_panel;
	
	if(Set_toggle_layers==0)
	{
		cm_tileset_id = tiles[over_pan_id->skill_x][over_pan_id->skill_y].tileset;
		cm_tile_id = tiles[over_pan_id->skill_x][over_pan_id->skill_y].type;
		cm_identify_tile = pan_arrayA[over_pan_id->skill_x][over_pan_id->skill_y];
	}
	if(Set_toggle_layers==1)
	{
		cm_tileset_id = tilesB[over_pan_id->skill_x][over_pan_id->skill_y].tileset;
		cm_tile_id = tilesB[over_pan_id->skill_x][over_pan_id->skill_y].type;
		cm_identify_tile = pan_arrayB[over_pan_id->skill_x][over_pan_id->skill_y];
	}
	if(Set_toggle_layers==2)
	{
		cm_tileset_id = tilesC[over_pan_id->skill_x][over_pan_id->skill_y].tileset;
		cm_tile_id = tilesC[over_pan_id->skill_x][over_pan_id->skill_y].type;
		cm_identify_tile = pan_arrayC[over_pan_id->skill_x][over_pan_id->skill_y];
	}
	overpanPos[0] = over_pan_id->skill_x;
	overpanPos[1] = over_pan_id->skill_y;
	
	int _st = 0;
	if(cm_tileset_id==1){_st = 0 + cm_tile_id;}
	if(cm_tileset_id==2){_st = 75 + cm_tile_id;}
	if(cm_tileset_id==3){_st = 150 + cm_tile_id;}
	if(cm_tileset_id==4){_st = 225 + cm_tile_id;}
	if(cm_tileset_id==5){_st = 300 + cm_tile_id;}
	if(cm_tileset_id==6){_st = 375 + cm_tile_id;}
	if(cm_tileset_id==7){_st = 450 + cm_tile_id;}
	if(cm_tileset_id==8){_st = 525 + cm_tile_id;}
	tempTYPE_cm = _st;
	
	//If its not a primary type that needs modified : Do nothing.
	if(cm_tile_id == 0 || nxsCmData[tempTYPE_cm].content == 0 || nxsCmData[tempTYPE_cm].content == 2 || nxsCmData[tempTYPE_cm].content == 9)
	{mod_pan_active = false; return;}
	
	//Check primary content type (If no IDs are needed, then just rotate if allowed)
	if(nxsCmData[tempTYPE_cm].content == 1 || nxsCmData[tempTYPE_cm].content == 4 || nxsCmData[tempTYPE_cm].content == 8)//ONLY ROTATION
	{	
		cm_identify_tile.center_x = cm_identify_tile.size_x * 0.490; cm_identify_tile.center_y = cm_identify_tile.size_y * 0.490;
		cm_identify_tile.angle+=90; if(cm_identify_tile.angle>=360){cm_identify_tile.angle=0;}
		if(Set_toggle_layers==0){tiles[over_pan_id->skill_x][over_pan_id->skill_y].rotation = cm_identify_tile.angle;}
		if(Set_toggle_layers==1){tilesB[over_pan_id->skill_x][over_pan_id->skill_y].rotation = cm_identify_tile.angle;}
		if(Set_toggle_layers==2){tilesC[over_pan_id->skill_x][over_pan_id->skill_y].rotation = cm_identify_tile.angle;}
		edit_cell_tile();
		wait(16);
		mod_pan_active = false;
		return;
	}
	
	//Check primary content type (If switch or trigger, open popup menu to set IDs and rotation)
	if(nxsCmData[tempTYPE_cm].content == 3 || nxsCmData[tempTYPE_cm].content == 6)
	{
		if(nxsCmData[tempTYPE_cm].content == 3 && Set_toggle_layers==0)
		{popup_swt_id = tiles[overpanPos[0]][overpanPos[1]].switchID; tiles[overpanPos[0]][overpanPos[1]].triggerID = 0; popup_tri_id = 0;}
		if(nxsCmData[tempTYPE_cm].content == 6 && Set_toggle_layers==0)
		{popup_tri_id = tiles[overpanPos[0]][overpanPos[1]].triggerID; tiles[overpanPos[0]][overpanPos[1]].switchID = 0; popup_swt_id = 0;}
		if(nxsCmData[tempTYPE_cm].content == 3 && Set_toggle_layers==1)
		{popup_swt_id = tilesB[overpanPos[0]][overpanPos[1]].switchID; tilesB[overpanPos[0]][overpanPos[1]].triggerID = 0; popup_tri_id = 0;}
		if(nxsCmData[tempTYPE_cm].content == 6 && Set_toggle_layers==1)
		{popup_tri_id = tilesB[overpanPos[0]][overpanPos[1]].triggerID; tilesB[overpanPos[0]][overpanPos[1]].switchID = 0; popup_swt_id = 0;}
		if(nxsCmData[tempTYPE_cm].content == 3 && Set_toggle_layers==2)
		{popup_swt_id = tilesC[overpanPos[0]][overpanPos[1]].switchID; tilesC[overpanPos[0]][overpanPos[1]].triggerID = 0; popup_tri_id = 0;}
		if(nxsCmData[tempTYPE_cm].content == 6 && Set_toggle_layers==2)
		{popup_tri_id = tilesC[overpanPos[0]][overpanPos[1]].triggerID; tilesC[overpanPos[0]][overpanPos[1]].switchID = 0; popup_swt_id = 0;}
		set(show_popup_overlay,SHOW);
		set(show_popup_set_id,SHOW);
		set(show_highlight,SHOW);
		show_highlight.pos_x = over_pan_id.pos_x - 4;
		show_highlight.pos_y = over_pan_id.pos_y - 4;
		show_highlight.red=50; show_highlight.green=200; show_highlight.blue=100;
		if(mouse_pos.x<=640 && mouse_pos.y<=360){show_popup_set_id.pos_x=mouse_pos.x+20; show_popup_set_id.pos_y=mouse_pos.y+20;}
		if(mouse_pos.x<=640 && mouse_pos.y>=361){show_popup_set_id.pos_x=mouse_pos.x+20; show_popup_set_id.pos_y=mouse_pos.y-183;}
		if(mouse_pos.x>=641 && mouse_pos.y<=360){show_popup_set_id.pos_x=mouse_pos.x-220; show_popup_set_id.pos_y=mouse_pos.y+20;}
		if(mouse_pos.x>=641 && mouse_pos.y>=361){show_popup_set_id.pos_x=mouse_pos.x-220; show_popup_set_id.pos_y=mouse_pos.y-183;}
	}	
	
	//Check primary content type (If secret wall or door, open popup menu to set IDs and rotation)
	//Only allowed to set IDs if USE_SWITCH or USE_TRIGGER flags are enabled.
	if(nxsCmData[tempTYPE_cm].content == 5 || nxsCmData[tempTYPE_cm].content == 7)
	{
		if(Set_toggle_layers==0){popup_swt_id = tiles[overpanPos[0]][overpanPos[1]].switchID; popup_tri_id = tiles[overpanPos[0]][overpanPos[1]].triggerID;}
		if(Set_toggle_layers==1){popup_swt_id = tilesB[overpanPos[0]][overpanPos[1]].switchID; popup_tri_id = tilesB[overpanPos[0]][overpanPos[1]].triggerID;}
		if(Set_toggle_layers==2){popup_swt_id = tilesC[overpanPos[0]][overpanPos[1]].switchID; popup_tri_id = tilesC[overpanPos[0]][overpanPos[1]].triggerID;}
		set(show_popup_overlay,SHOW);
		set(show_popup_use_id,SHOW);
		set(show_highlight,SHOW);
		show_highlight.pos_x = over_pan_id.pos_x - 4;
		show_highlight.pos_y = over_pan_id.pos_y - 4;
		show_highlight.red=128; show_highlight.green=128; show_highlight.blue=128;
		if(mouse_pos.x<=640 && mouse_pos.y<=360){show_popup_use_id.pos_x=mouse_pos.x+20; show_popup_use_id.pos_y=mouse_pos.y+20;}
		if(mouse_pos.x<=640 && mouse_pos.y>=361){show_popup_use_id.pos_x=mouse_pos.x+20; show_popup_use_id.pos_y=mouse_pos.y-183;}
		if(mouse_pos.x>=641 && mouse_pos.y<=360){show_popup_use_id.pos_x=mouse_pos.x-220; show_popup_use_id.pos_y=mouse_pos.y+20;}
		if(mouse_pos.x>=641 && mouse_pos.y>=361){show_popup_use_id.pos_x=mouse_pos.x-220; show_popup_use_id.pos_y=mouse_pos.y-183;}
	}	
}


//SET SWITCH ID
void modify_swt_minus()
{
	if(nxsCmData[tempTYPE_cm].content != 3 && nxsCmData[tempTYPE_cm].content != 5 && nxsCmData[tempTYPE_cm].content != 7){return;}
	if(Set_toggle_layers==0)
	{
		if(nxsCmData[tempTYPE_cm].content == 5 && nxsCmData[tempTYPE_cm].useSwitch != 1){popup_swt_id=0; tiles[overpanPos[0]][overpanPos[1]].switchID = 0; return;}
		if(nxsCmData[tempTYPE_cm].content == 7 && nxsCmData[tempTYPE_cm].useSwitch != 1){popup_swt_id=0; tiles[overpanPos[0]][overpanPos[1]].switchID = 0; return;}
		popup_swt_id-=1; 
		tiles[overpanPos[0]][overpanPos[1]].switchID = popup_swt_id;
		if(popup_swt_id<=0){popup_swt_id=0; tiles[overpanPos[0]][overpanPos[1]].switchID = 0;}
	}
	if(Set_toggle_layers==1)
	{
		if(nxsCmData[tempTYPE_cm].content == 5 && nxsCmData[tempTYPE_cm].useSwitch != 1){popup_swt_id=0; tilesB[overpanPos[0]][overpanPos[1]].switchID = 0; return;}
		if(nxsCmData[tempTYPE_cm].content == 7 && nxsCmData[tempTYPE_cm].useSwitch != 1){popup_swt_id=0; tilesB[overpanPos[0]][overpanPos[1]].switchID = 0; return;}
		popup_swt_id-=1; 
		tilesB[overpanPos[0]][overpanPos[1]].switchID = popup_swt_id;
		if(popup_swt_id<=0){popup_swt_id=0; tilesB[overpanPos[0]][overpanPos[1]].switchID = 0;}
	}
	if(Set_toggle_layers==2)
	{
		if(nxsCmData[tempTYPE_cm].content == 5 && nxsCmData[tempTYPE_cm].useSwitch != 1){popup_swt_id=0; tilesC[overpanPos[0]][overpanPos[1]].switchID = 0; return;}
		if(nxsCmData[tempTYPE_cm].content == 7 && nxsCmData[tempTYPE_cm].useSwitch != 1){popup_swt_id=0; tilesC[overpanPos[0]][overpanPos[1]].switchID = 0; return;}
		popup_swt_id-=1; 
		tilesC[overpanPos[0]][overpanPos[1]].switchID = popup_swt_id;
		if(popup_swt_id<=0){popup_swt_id=0; tilesC[overpanPos[0]][overpanPos[1]].switchID = 0;}
	}
}
void modify_swt_plus()
{
	if(nxsCmData[tempTYPE_cm].content != 3 && nxsCmData[tempTYPE_cm].content != 5 && nxsCmData[tempTYPE_cm].content != 7){return;}
	if(Set_toggle_layers==0)
	{
		if(nxsCmData[tempTYPE_cm].content == 5 && nxsCmData[tempTYPE_cm].useSwitch != 1){popup_swt_id=0; tiles[overpanPos[0]][overpanPos[1]].switchID = 0; return;}
		if(nxsCmData[tempTYPE_cm].content == 7 && nxsCmData[tempTYPE_cm].useSwitch != 1){popup_swt_id=0; tiles[overpanPos[0]][overpanPos[1]].switchID = 0; return;}
		popup_swt_id+=1; 
		tiles[overpanPos[0]][overpanPos[1]].switchID = popup_swt_id;
		if(popup_swt_id>=10){popup_swt_id=10; tiles[overpanPos[0]][overpanPos[1]].switchID = 10;}
	}
	if(Set_toggle_layers==1)
	{
		if(nxsCmData[tempTYPE_cm].content == 5 && nxsCmData[tempTYPE_cm].useSwitch != 1){popup_swt_id=0; tilesB[overpanPos[0]][overpanPos[1]].switchID = 0; return;}
		if(nxsCmData[tempTYPE_cm].content == 7 && nxsCmData[tempTYPE_cm].useSwitch != 1){popup_swt_id=0; tilesB[overpanPos[0]][overpanPos[1]].switchID = 0; return;}
		popup_swt_id+=1; 
		tilesB[overpanPos[0]][overpanPos[1]].switchID = popup_swt_id;
		if(popup_swt_id>=10){popup_swt_id=10; tilesB[overpanPos[0]][overpanPos[1]].switchID = 10;}
	}
	if(Set_toggle_layers==2)
	{
		if(nxsCmData[tempTYPE_cm].content == 5 && nxsCmData[tempTYPE_cm].useSwitch != 1){popup_swt_id=0; tilesC[overpanPos[0]][overpanPos[1]].switchID = 0; return;}
		if(nxsCmData[tempTYPE_cm].content == 7 && nxsCmData[tempTYPE_cm].useSwitch != 1){popup_swt_id=0; tilesC[overpanPos[0]][overpanPos[1]].switchID = 0; return;}
		popup_swt_id+=1; 
		tilesC[overpanPos[0]][overpanPos[1]].switchID = popup_swt_id;
		if(popup_swt_id>=10){popup_swt_id=10; tilesC[overpanPos[0]][overpanPos[1]].switchID = 10;}
	}
}


//SET TRIGGER ID
void modify_tri_minus()
{
	if(nxsCmData[tempTYPE_cm].content != 6 && nxsCmData[tempTYPE_cm].content != 5 && nxsCmData[tempTYPE_cm].content != 7){return;}
	if(Set_toggle_layers==0)
	{
		if(nxsCmData[tempTYPE_cm].content == 5 && nxsCmData[tempTYPE_cm].useTrigger != 1){popup_tri_id=0; tiles[overpanPos[0]][overpanPos[1]].triggerID = 0; return;}
		if(nxsCmData[tempTYPE_cm].content == 7 && nxsCmData[tempTYPE_cm].useTrigger != 1){popup_tri_id=0; tiles[overpanPos[0]][overpanPos[1]].triggerID = 0; return;}
		popup_tri_id-=1; 
		tiles[overpanPos[0]][overpanPos[1]].triggerID = popup_tri_id;
		if(popup_tri_id<=0){popup_tri_id=0; tiles[overpanPos[0]][overpanPos[1]].triggerID = 0;}
	}
	if(Set_toggle_layers==1)
	{
		if(nxsCmData[tempTYPE_cm].content == 5 && nxsCmData[tempTYPE_cm].useTrigger != 1){popup_tri_id=0; tilesB[overpanPos[0]][overpanPos[1]].triggerID = 0; return;}
		if(nxsCmData[tempTYPE_cm].content == 7 && nxsCmData[tempTYPE_cm].useTrigger != 1){popup_tri_id=0; tilesB[overpanPos[0]][overpanPos[1]].triggerID = 0; return;}
		popup_tri_id-=1; 
		tilesB[overpanPos[0]][overpanPos[1]].triggerID = popup_tri_id;
		if(popup_tri_id<=0){popup_tri_id=0; tilesB[overpanPos[0]][overpanPos[1]].triggerID = 0;}
	}
	if(Set_toggle_layers==2)
	{
		if(nxsCmData[tempTYPE_cm].content == 5 && nxsCmData[tempTYPE_cm].useTrigger != 1){popup_tri_id=0; tilesC[overpanPos[0]][overpanPos[1]].triggerID = 0; return;}
		if(nxsCmData[tempTYPE_cm].content == 7 && nxsCmData[tempTYPE_cm].useTrigger != 1){popup_tri_id=0; tilesC[overpanPos[0]][overpanPos[1]].triggerID = 0; return;}
		popup_tri_id-=1; 
		tilesC[overpanPos[0]][overpanPos[1]].triggerID = popup_tri_id;
		if(popup_tri_id<=0){popup_tri_id=0; tilesC[overpanPos[0]][overpanPos[1]].triggerID = 0;}
	}
}
void modify_tri_plus()
{
	if(nxsCmData[tempTYPE_cm].content != 6 && nxsCmData[tempTYPE_cm].content != 5 && nxsCmData[tempTYPE_cm].content != 7){return;}
	if(Set_toggle_layers==0)
	{
		if(nxsCmData[tempTYPE_cm].content == 5 && nxsCmData[tempTYPE_cm].useTrigger != 1){popup_tri_id=0; tiles[overpanPos[0]][overpanPos[1]].triggerID = 0; return;}
		if(nxsCmData[tempTYPE_cm].content == 7 && nxsCmData[tempTYPE_cm].useTrigger != 1){popup_tri_id=0; tiles[overpanPos[0]][overpanPos[1]].triggerID = 0; return;}
		popup_tri_id+=1; 
		tiles[overpanPos[0]][overpanPos[1]].triggerID = popup_tri_id;
		if(popup_tri_id>=10){popup_tri_id=10; tiles[overpanPos[0]][overpanPos[1]].triggerID = 10;}
	}
	if(Set_toggle_layers==1)
	{
		if(nxsCmData[tempTYPE_cm].content == 5 && nxsCmData[tempTYPE_cm].useTrigger != 1){popup_tri_id=0; tilesB[overpanPos[0]][overpanPos[1]].triggerID = 0; return;}
		if(nxsCmData[tempTYPE_cm].content == 7 && nxsCmData[tempTYPE_cm].useTrigger != 1){popup_tri_id=0; tilesB[overpanPos[0]][overpanPos[1]].triggerID = 0; return;}
		popup_tri_id+=1; 
		tilesB[overpanPos[0]][overpanPos[1]].triggerID = popup_tri_id;
		if(popup_tri_id>=10){popup_tri_id=10; tilesB[overpanPos[0]][overpanPos[1]].triggerID = 10;}
	}
	if(Set_toggle_layers==2)
	{
		if(nxsCmData[tempTYPE_cm].content == 5 && nxsCmData[tempTYPE_cm].useTrigger != 1){popup_tri_id=0; tilesC[overpanPos[0]][overpanPos[1]].triggerID = 0; return;}
		if(nxsCmData[tempTYPE_cm].content == 7 && nxsCmData[tempTYPE_cm].useTrigger != 1){popup_tri_id=0; tilesC[overpanPos[0]][overpanPos[1]].triggerID = 0; return;}
		popup_tri_id+=1; 
		tilesC[overpanPos[0]][overpanPos[1]].triggerID = popup_tri_id;
		if(popup_tri_id>=10){popup_tri_id=10; tilesC[overpanPos[0]][overpanPos[1]].triggerID = 10;}
	}
}


//SET ROTATION
void modify_popup_rotation()
{
	cm_identify_tile.center_x = cm_identify_tile.size_x * 0.490; cm_identify_tile.center_y = cm_identify_tile.size_y * 0.490;
	cm_identify_tile.angle+=90; if(cm_identify_tile.angle>=360){cm_identify_tile.angle=0;}
	if(Set_toggle_layers==0){tiles[overpanPos[0]][overpanPos[1]].rotation = cm_identify_tile.angle;}
	if(Set_toggle_layers==1){tilesB[overpanPos[0]][overpanPos[1]].rotation = cm_identify_tile.angle;}
	edit_cell_tile();
}


//EXIT POPUP MENU
void modify_popup_close()
{
	mouse_mode=0;
	reset(show_popup_overlay,SHOW);
	reset(show_popup_set_id,SHOW);
	reset(show_popup_use_id,SHOW);
	reset(show_highlight,SHOW);
	while(mouse_left==1){wait(1);}
	wait(16);
	mouse_mode=4;
	mod_pan_active = false;
}
