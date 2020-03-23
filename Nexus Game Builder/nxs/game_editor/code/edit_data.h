/*#########################################################################################################################################################
NEXUS A8 : GAME BUILDER :: By Brian Pressley (Evo) (Evoeon) :::: Popup Editing Menu HEADER :: Lite-C :: 3DGamestudio A8
#########################################################################################################################################################*/


//POPUP MENU : BMAPS
BMAP* popup_overlay = "popup_overlay.png";
BMAP* popup_set_id = "popup_set_id.png";
BMAP* popup_use_id = "popup_use_id.png";
BMAP* bu_rotate = "bu_rotate.png";
BMAP* bu_rotate_ov = "bu_rotate_ov.png";
BMAP* highlight_cell = "highlight_cell.png";


//BG POPUP OVERLAY FOR THE MODIFY MENU
PANEL* show_popup_overlay = 
{
	bmap=popup_overlay;
	pos_x=0;	pos_y=0;	layer = 20;
}


//POPUP MENU TO SET IDS AND ROTATION FOR SWITCH AND TRIGGER EVENTS (SET IDs)
PANEL* show_popup_set_id = 
{
	bmap=popup_set_id;
	
	//Set Switch ID
	button(110,34,sm_bu_minus_over,sm_bu_minus,sm_bu_minus_over,modify_swt_minus,NULL,NULL);
	digits(143,35, -2, small_fontD, 1, popup_swt_id);
	button(167,34,sm_bu_plus_over,sm_bu_plus,sm_bu_plus_over,modify_swt_plus,NULL,NULL);
	
	//Set Trigger ID
	button(110,59,sm_bu_minus_over,sm_bu_minus,sm_bu_minus_over,modify_tri_minus,NULL,NULL);
	digits(143,60, -2, small_fontD, 1, popup_tri_id);
	button(167,59,sm_bu_plus_over,sm_bu_plus,sm_bu_plus_over,modify_tri_plus,NULL,NULL);
	
	//Set Rotation
	button(48,91,bu_rotate_ov,bu_rotate,bu_rotate_ov,modify_popup_rotation,NULL,NULL);
	
	//Save and Exit popup menu
	button(71,132,ch_save_bu_over,ch_save_bu,ch_save_bu_over,modify_popup_close,NULL,NULL);
	
	red=1; green=1; blue=1;
	pos_x=-500;	pos_y=0;	layer = 21;
}


//POPUP MENU TO SET IDS AND ROTATION FOR SECRET WALLS AND DOORS (USE IDs)
PANEL* show_popup_use_id = 
{
	bmap=popup_use_id;
	
	//Set USE Switch ID
	button(110,34,sm_bu_minus_over,sm_bu_minus,sm_bu_minus_over,modify_swt_minus,NULL,NULL);
	digits(143,35, -2, small_fontD, 1, popup_swt_id);
	button(167,34,sm_bu_plus_over,sm_bu_plus,sm_bu_plus_over,modify_swt_plus,NULL,NULL);
	
	//Set USE Trigger ID
	button(110,59,sm_bu_minus_over,sm_bu_minus,sm_bu_minus_over,modify_tri_minus,NULL,NULL);
	digits(143,60, -2, small_fontD, 1, popup_tri_id);
	button(167,59,sm_bu_plus_over,sm_bu_plus,sm_bu_plus_over,modify_tri_plus,NULL,NULL);
	
	//Set Rotation
	button(48,91,bu_rotate_ov,bu_rotate,bu_rotate_ov,modify_popup_rotation,NULL,NULL);
	
	//Save and Exit popup menu
	button(71,132,ch_save_bu_over,ch_save_bu,ch_save_bu_over,modify_popup_close,NULL,NULL);
	
	red=1; green=1; blue=1;
	pos_x=-500;	pos_y=0;	layer = 21;
}


//CURSOR TO IDENTIFY THE TILE BEING MODIFIED : SHOWN ON TILE (POPUP MENU ONLY)
PANEL* show_highlight = 
{
	bmap=highlight_cell;
	pos_x=0;	pos_y=0; alpha=40; layer = 19;
	flags=LIGHT | UNTOUCHABLE;
	red=128; green=128; blue=128;
}


//POPUP MENU TO SET SWITCH IDS, TRIGGER IDS AND ROTATION (EVENT MODE ONLY)
//PRESSING MOUSE LEFT WHILE THE MOUSE IS OVER A TILE ON THE GRID WILL OPEN THIS MENU
//Secret walls, doors, switches and triggers have a popup menu for IDs and Rotation.
//All other types except standard walls and floors have rotation only.
//Standard walls and floors do not have any popup options to modify.
void modify_tiles();


//SET SWITCH ID
void modify_swt_minus();
void modify_swt_plus();


//SET TRIGGER ID
void modify_tri_minus();
void modify_tri_plus();


//SET ROTATION
void modify_popup_rotation();


//EXIT POPUP MENU
void modify_popup_close();