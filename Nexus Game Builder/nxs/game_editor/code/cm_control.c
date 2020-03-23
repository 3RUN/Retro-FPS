/*#########################################################################################################################################################
NEXUS A8 : GAME BUILDER :: By Brian Pressley (Evo) (Evoeon) :::: Content Manager Script FUNCTIONS :: Lite-C :: 3DGamestudio A8
#########################################################################################################################################################*/


//SET PRIMARY CONTENT TYPE
void click_primary_bu1(){nxsCmData[tempTYPE_cm].content = 1; set_content_data();}
void click_primary_bu2(){nxsCmData[tempTYPE_cm].content = 2; set_content_data();}
void click_primary_bu3(){nxsCmData[tempTYPE_cm].content = 3; set_content_data();}
void click_primary_bu4(){nxsCmData[tempTYPE_cm].content = 4; set_content_data();}
void click_primary_bu5(){nxsCmData[tempTYPE_cm].content = 5; set_content_data();}
void click_primary_bu6(){nxsCmData[tempTYPE_cm].content = 6; set_content_data();}
void click_primary_bu7(){nxsCmData[tempTYPE_cm].content = 7; set_content_data();}
void click_primary_bu8(){nxsCmData[tempTYPE_cm].content = 8; set_content_data();}
void click_primary_bu9(){nxsCmData[tempTYPE_cm].content = 9; set_content_data();}


//SET DOOR FLAG CHECKBOXES
void set_flag_door_Op_1()
{
	if(nxsCmData[tempTYPE_cm].doorFlag1 == 1)
	{nxsCmData[tempTYPE_cm].doorFlag1 = 0; pan_setbutton(editor_content_panel,12,0,823,367,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_door_Op_1,NULL,NULL);}
	else{nxsCmData[tempTYPE_cm].doorFlag1 = 1; pan_setbutton(editor_content_panel,12,0,823,367,ckbox_bu_on_ov,ckbox_bu_on,ckbox_bu_on_ov,ckbox_bu_on,set_flag_door_Op_1,NULL,NULL);}
}
void set_flag_door_Op_2()
{
	if(nxsCmData[tempTYPE_cm].doorFlag2 == 1)
	{nxsCmData[tempTYPE_cm].doorFlag2 = 0; pan_setbutton(editor_content_panel,13,0,823,390,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_door_Op_2,NULL,NULL);}
	else{nxsCmData[tempTYPE_cm].doorFlag2 = 1; pan_setbutton(editor_content_panel,13,0,823,390,ckbox_bu_on_ov,ckbox_bu_on,ckbox_bu_on_ov,ckbox_bu_on,set_flag_door_Op_2,NULL,NULL);}
}
void set_flag_door_Op_3()
{
	if(nxsCmData[tempTYPE_cm].doorFlag3 == 1)
	{nxsCmData[tempTYPE_cm].doorFlag3 = 0; pan_setbutton(editor_content_panel,14,0,823,413,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_door_Op_3,NULL,NULL);}
	else{nxsCmData[tempTYPE_cm].doorFlag3 = 1; pan_setbutton(editor_content_panel,14,0,823,413,ckbox_bu_on_ov,ckbox_bu_on,ckbox_bu_on_ov,ckbox_bu_on,set_flag_door_Op_3,NULL,NULL);}
}
void set_flag_door_Op_4()
{
	if(nxsCmData[tempTYPE_cm].doorFlag4 == 1)
	{nxsCmData[tempTYPE_cm].doorFlag4 = 0; pan_setbutton(editor_content_panel,15,0,823,436,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_door_Op_4,NULL,NULL);}
	else{nxsCmData[tempTYPE_cm].doorFlag4 = 1; pan_setbutton(editor_content_panel,15,0,823,436,ckbox_bu_on_ov,ckbox_bu_on,ckbox_bu_on_ov,ckbox_bu_on,set_flag_door_Op_4,NULL,NULL);}
}
void set_flag_door_Op_5()
{
	if(nxsCmData[tempTYPE_cm].doorFlag5 == 1)
	{nxsCmData[tempTYPE_cm].doorFlag5 = 0; pan_setbutton(editor_content_panel,16,0,823,459,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_door_Op_5,NULL,NULL);}
	else{nxsCmData[tempTYPE_cm].doorFlag5 = 1; pan_setbutton(editor_content_panel,16,0,823,459,ckbox_bu_on_ov,ckbox_bu_on,ckbox_bu_on_ov,ckbox_bu_on,set_flag_door_Op_5,NULL,NULL);}
}


//SET PROP FLAG CHECKBOXES
void set_flag_prop_Op_1()
{
	if(nxsCmData[tempTYPE_cm].propFlag1 == 1)
	{nxsCmData[tempTYPE_cm].propFlag1 = 0; pan_setbutton(editor_content_panel,17,0,986,367,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_prop_Op_1,NULL,NULL);}
	else{nxsCmData[tempTYPE_cm].propFlag1 = 1; pan_setbutton(editor_content_panel,17,0,986,367,ckbox_bu_on_ov,ckbox_bu_on,ckbox_bu_on_ov,ckbox_bu_on,set_flag_prop_Op_1,NULL,NULL);}
}
void set_flag_prop_Op_2()
{
	if(nxsCmData[tempTYPE_cm].propFlag2 == 1)
	{nxsCmData[tempTYPE_cm].propFlag2 = 0; pan_setbutton(editor_content_panel,18,0,986,390,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_prop_Op_2,NULL,NULL);}
	else{nxsCmData[tempTYPE_cm].propFlag2 = 1; pan_setbutton(editor_content_panel,18,0,986,390,ckbox_bu_on_ov,ckbox_bu_on,ckbox_bu_on_ov,ckbox_bu_on,set_flag_prop_Op_2,NULL,NULL);}
}
void set_flag_prop_Op_3()
{
	if(nxsCmData[tempTYPE_cm].propFlag3 == 1)
	{nxsCmData[tempTYPE_cm].propFlag3 = 0; pan_setbutton(editor_content_panel,19,0,986,413,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_prop_Op_3,NULL,NULL);}
	else{nxsCmData[tempTYPE_cm].propFlag3 = 1; pan_setbutton(editor_content_panel,19,0,986,413,ckbox_bu_on_ov,ckbox_bu_on,ckbox_bu_on_ov,ckbox_bu_on,set_flag_prop_Op_3,NULL,NULL);}
}
void set_flag_prop_Op_4()
{
	if(nxsCmData[tempTYPE_cm].propFlag4 == 1)
	{nxsCmData[tempTYPE_cm].propFlag4 = 0; pan_setbutton(editor_content_panel,20,0,986,436,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_prop_Op_4,NULL,NULL);}
	else{nxsCmData[tempTYPE_cm].propFlag4 = 1; pan_setbutton(editor_content_panel,20,0,986,436,ckbox_bu_on_ov,ckbox_bu_on,ckbox_bu_on_ov,ckbox_bu_on,set_flag_prop_Op_4,NULL,NULL);}
}
void set_flag_prop_Op_5()
{
	if(nxsCmData[tempTYPE_cm].propFlag5 == 1)
	{nxsCmData[tempTYPE_cm].propFlag5 = 0; pan_setbutton(editor_content_panel,21,0,986,459,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_prop_Op_5,NULL,NULL);}
	else{nxsCmData[tempTYPE_cm].propFlag5 = 1; pan_setbutton(editor_content_panel,21,0,986,459,ckbox_bu_on_ov,ckbox_bu_on,ckbox_bu_on_ov,ckbox_bu_on,set_flag_prop_Op_5,NULL,NULL);}
}


//SET CONTROL FLAG CHECKBOXES
void set_flag_swt_Op_1()
{
	if(nxsCmData[tempTYPE_cm].useSwitch == 1)
	{nxsCmData[tempTYPE_cm].useSwitch = 0; pan_setbutton(editor_content_panel,22,0,823,527,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_swt_Op_1,NULL,NULL);}
	else{nxsCmData[tempTYPE_cm].useSwitch = 1; pan_setbutton(editor_content_panel,22,0,823,527,ckbox_bu_on_ov,ckbox_bu_on,ckbox_bu_on_ov,ckbox_bu_on,set_flag_swt_Op_1,NULL,NULL);}
}
void set_flag_swt_Op_2()
{
	if(nxsCmData[tempTYPE_cm].useTrigger == 1)
	{nxsCmData[tempTYPE_cm].useTrigger = 0; pan_setbutton(editor_content_panel,23,0,823,550,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_swt_Op_2,NULL,NULL);}
	else{nxsCmData[tempTYPE_cm].useTrigger = 1; pan_setbutton(editor_content_panel,23,0,823,550,ckbox_bu_on_ov,ckbox_bu_on,ckbox_bu_on_ov,ckbox_bu_on,set_flag_swt_Op_2,NULL,NULL);}
}


//SET BONUS FLAG CHECKBOXES
void set_flag_bonus_Op_1()
{
	if(nxsCmData[tempTYPE_cm].bonusFlag1 == 1)
	{nxsCmData[tempTYPE_cm].bonusFlag1 = 0; pan_setbutton(editor_content_panel,24,0,986,527,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_bonus_Op_1,NULL,NULL);}
	else{nxsCmData[tempTYPE_cm].bonusFlag1 = 1; pan_setbutton(editor_content_panel,24,0,986,527,ckbox_bu_on_ov,ckbox_bu_on,ckbox_bu_on_ov,ckbox_bu_on,set_flag_bonus_Op_1,NULL,NULL);}
}
void set_flag_bonus_Op_2()
{
	if(nxsCmData[tempTYPE_cm].bonusFlag2 == 1)
	{nxsCmData[tempTYPE_cm].bonusFlag2 = 0; pan_setbutton(editor_content_panel,25,0,986,550,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_bonus_Op_2,NULL,NULL);}
	else{nxsCmData[tempTYPE_cm].bonusFlag2 = 1; pan_setbutton(editor_content_panel,25,0,986,550,ckbox_bu_on_ov,ckbox_bu_on,ckbox_bu_on_ov,ckbox_bu_on,set_flag_bonus_Op_2,NULL,NULL);}
}


//SET CORRECT CONTENT DATA FOR THE SELECTED TILE WHEN CONTENT MENU OPENS
void set_content_data()
{	
	//Reset Content
	str_cpy(cm_action_name,"EMPTY");
	str_cpy(content_name_ent,"EMPTY");
	str_cpy(content_name_skin,"EMPTY");
	set(disable_all_options,SHOW);
	reset(disable_ent_options,SHOW);
	reset(disable_skin_options,SHOW);
	reset(disable_door_options,SHOW);
	reset(disable_prop_options,SHOW);
	reset(disable_swt_options,SHOW);
	reset(disable_bonus_options,SHOW);
	pan_setbutton(editor_content_panel,1,0,812,108,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,click_primary_bu1,NULL,NULL);
	pan_setbutton(editor_content_panel,2,0,899,108,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,click_primary_bu2,NULL,NULL);
	pan_setbutton(editor_content_panel,3,0,993,108,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,click_primary_bu3,NULL,NULL);
	pan_setbutton(editor_content_panel,4,0,812,131,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,click_primary_bu4,NULL,NULL);
	pan_setbutton(editor_content_panel,5,0,899,131,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,click_primary_bu5,NULL,NULL);
	pan_setbutton(editor_content_panel,6,0,993,131,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,click_primary_bu6,NULL,NULL);
	pan_setbutton(editor_content_panel,7,0,812,154,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,click_primary_bu7,NULL,NULL);
	pan_setbutton(editor_content_panel,8,0,899,154,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,click_primary_bu8,NULL,NULL);
	pan_setbutton(editor_content_panel,9,0,993,154,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,click_primary_bu9,NULL,NULL);
	pan_setbutton(editor_content_panel,12,0,823,367,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_door_Op_1,NULL,NULL);
	pan_setbutton(editor_content_panel,13,0,823,390,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_door_Op_2,NULL,NULL);
	pan_setbutton(editor_content_panel,14,0,823,413,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_door_Op_3,NULL,NULL);
	pan_setbutton(editor_content_panel,15,0,823,436,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_door_Op_4,NULL,NULL);
	pan_setbutton(editor_content_panel,16,0,823,459,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_door_Op_5,NULL,NULL);
	pan_setbutton(editor_content_panel,17,0,986,367,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_prop_Op_1,NULL,NULL);
	pan_setbutton(editor_content_panel,18,0,986,390,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_prop_Op_2,NULL,NULL);
	pan_setbutton(editor_content_panel,19,0,986,413,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_prop_Op_3,NULL,NULL);
	pan_setbutton(editor_content_panel,20,0,986,436,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_prop_Op_4,NULL,NULL);
	pan_setbutton(editor_content_panel,21,0,986,459,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_prop_Op_5,NULL,NULL);
	pan_setbutton(editor_content_panel,22,0,823,527,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_swt_Op_1,NULL,NULL);
	pan_setbutton(editor_content_panel,23,0,823,550,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_swt_Op_2,NULL,NULL);
	pan_setbutton(editor_content_panel,24,0,986,527,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_bonus_Op_1,NULL,NULL);
	pan_setbutton(editor_content_panel,25,0,986,550,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_bonus_Op_2,NULL,NULL);
	
	//Set Correct Data
	if(nxsCmData[tempTYPE_cm].content == 1)
	{pan_setbutton(editor_content_panel,1,0,812,108,ckbox_bu_star_ov,ckbox_bu_star,ckbox_bu_star_ov,ckbox_bu_star,click_primary_bu1,NULL,NULL);}
	if(nxsCmData[tempTYPE_cm].content == 2)
	{pan_setbutton(editor_content_panel,2,0,899,108,ckbox_bu_star_ov,ckbox_bu_star,ckbox_bu_star_ov,ckbox_bu_star,click_primary_bu2,NULL,NULL);}
	if(nxsCmData[tempTYPE_cm].content == 3)
	{pan_setbutton(editor_content_panel,3,0,993,108,ckbox_bu_star_ov,ckbox_bu_star,ckbox_bu_star_ov,ckbox_bu_star,click_primary_bu3,NULL,NULL);}
	if(nxsCmData[tempTYPE_cm].content == 4)
	{pan_setbutton(editor_content_panel,4,0,812,131,ckbox_bu_star_ov,ckbox_bu_star,ckbox_bu_star_ov,ckbox_bu_star,click_primary_bu4,NULL,NULL);}
	if(nxsCmData[tempTYPE_cm].content == 5)
	{pan_setbutton(editor_content_panel,5,0,899,131,ckbox_bu_star_ov,ckbox_bu_star,ckbox_bu_star_ov,ckbox_bu_star,click_primary_bu5,NULL,NULL);}
	if(nxsCmData[tempTYPE_cm].content == 6)
	{pan_setbutton(editor_content_panel,6,0,993,131,ckbox_bu_star_ov,ckbox_bu_star,ckbox_bu_star_ov,ckbox_bu_star,click_primary_bu6,NULL,NULL);}
	if(nxsCmData[tempTYPE_cm].content == 7)
	{pan_setbutton(editor_content_panel,7,0,812,154,ckbox_bu_star_ov,ckbox_bu_star,ckbox_bu_star_ov,ckbox_bu_star,click_primary_bu7,NULL,NULL);}
	if(nxsCmData[tempTYPE_cm].content == 8)
	{pan_setbutton(editor_content_panel,8,0,899,154,ckbox_bu_star_ov,ckbox_bu_star,ckbox_bu_star_ov,ckbox_bu_star,click_primary_bu8,NULL,NULL);}
	if(nxsCmData[tempTYPE_cm].content == 9)
	{pan_setbutton(editor_content_panel,9,0,993,154,ckbox_bu_star_ov,ckbox_bu_star,ckbox_bu_star_ov,ckbox_bu_star,click_primary_bu9,NULL,NULL);}
	
	//Identify primary type and deactivate all settings and flags of other types
	if(nxsCmData[tempTYPE_cm].content == 1 || nxsCmData[tempTYPE_cm].content == 2 || nxsCmData[tempTYPE_cm].content == 3 || nxsCmData[tempTYPE_cm].content == 4)
	{
		reset(disable_all_options,SHOW);
		reset(disable_ent_options,SHOW); reset(disable_skin_options,SHOW);
		set(disable_door_options,SHOW); set(disable_prop_options,SHOW); 
		set(disable_swt_options,SHOW); set(disable_bonus_options,SHOW);
		nxsCmData[tempTYPE_cm].doorFlag1 = 0;		nxsCmData[tempTYPE_cm].doorFlag2 = 0;
		nxsCmData[tempTYPE_cm].doorFlag3 = 0;		nxsCmData[tempTYPE_cm].doorFlag4 = 0;
		nxsCmData[tempTYPE_cm].doorFlag5 = 0;		nxsCmData[tempTYPE_cm].propFlag1 = 0;
		nxsCmData[tempTYPE_cm].propFlag2 = 0;		nxsCmData[tempTYPE_cm].propFlag3 = 0;
		nxsCmData[tempTYPE_cm].propFlag4 = 0;		nxsCmData[tempTYPE_cm].propFlag5 = 0;
		nxsCmData[tempTYPE_cm].bonusFlag1 = 0;		nxsCmData[tempTYPE_cm].bonusFlag2 = 0;
		nxsCmData[tempTYPE_cm].useSwitch = 0;		nxsCmData[tempTYPE_cm].useTrigger = 0;
	}
	if(nxsCmData[tempTYPE_cm].content == 5)
	{
		reset(disable_all_options,SHOW);
		reset(disable_ent_options,SHOW); reset(disable_skin_options,SHOW);
		reset(disable_door_options,SHOW); set(disable_prop_options,SHOW); 
		reset(disable_swt_options,SHOW); set(disable_bonus_options,SHOW);
		nxsCmData[tempTYPE_cm].propFlag1 = 0;
		nxsCmData[tempTYPE_cm].propFlag2 = 0;		nxsCmData[tempTYPE_cm].propFlag3 = 0;
		nxsCmData[tempTYPE_cm].propFlag4 = 0;		nxsCmData[tempTYPE_cm].propFlag5 = 0;
		nxsCmData[tempTYPE_cm].bonusFlag1 = 0;		nxsCmData[tempTYPE_cm].bonusFlag2 = 0;
	}
	if(nxsCmData[tempTYPE_cm].content == 6)
	{
		reset(disable_all_options,SHOW);
		reset(disable_ent_options,SHOW); set(disable_skin_options,SHOW);
		set(disable_door_options,SHOW); set(disable_prop_options,SHOW); 
		set(disable_swt_options,SHOW); set(disable_bonus_options,SHOW);
		nxsCmData[tempTYPE_cm].doorFlag1 = 0;		nxsCmData[tempTYPE_cm].doorFlag2 = 0;
		nxsCmData[tempTYPE_cm].doorFlag3 = 0;		nxsCmData[tempTYPE_cm].doorFlag4 = 0;
		nxsCmData[tempTYPE_cm].doorFlag5 = 0;		nxsCmData[tempTYPE_cm].propFlag1 = 0;
		nxsCmData[tempTYPE_cm].propFlag2 = 0;		nxsCmData[tempTYPE_cm].propFlag3 = 0;
		nxsCmData[tempTYPE_cm].propFlag4 = 0;		nxsCmData[tempTYPE_cm].propFlag5 = 0;
		nxsCmData[tempTYPE_cm].bonusFlag1 = 0;		nxsCmData[tempTYPE_cm].bonusFlag2 = 0;
		nxsCmData[tempTYPE_cm].useSwitch = 0;		nxsCmData[tempTYPE_cm].useTrigger = 0;
		str_cpy((nxs_skins.pstring)[tempTYPE_cm],"EMPTY"); str_cpy(content_name_skin,"EMPTY");
	}
	if(nxsCmData[tempTYPE_cm].content == 7)
	{
		reset(disable_all_options,SHOW);
		reset(disable_ent_options,SHOW); reset(disable_skin_options,SHOW);
		set(disable_door_options,SHOW); set(disable_prop_options,SHOW); 
		reset(disable_swt_options,SHOW); set(disable_bonus_options,SHOW);
		nxsCmData[tempTYPE_cm].doorFlag1 = 0;		nxsCmData[tempTYPE_cm].doorFlag2 = 0;
		nxsCmData[tempTYPE_cm].doorFlag3 = 0;		nxsCmData[tempTYPE_cm].doorFlag4 = 0;
		nxsCmData[tempTYPE_cm].doorFlag5 = 0;		nxsCmData[tempTYPE_cm].propFlag1 = 0;
		nxsCmData[tempTYPE_cm].propFlag2 = 0;		nxsCmData[tempTYPE_cm].propFlag3 = 0;
		nxsCmData[tempTYPE_cm].propFlag4 = 0;		nxsCmData[tempTYPE_cm].propFlag5 = 0;
		nxsCmData[tempTYPE_cm].bonusFlag1 = 0;		nxsCmData[tempTYPE_cm].bonusFlag2 = 0;
//		str_cpy((nxs_skins.pstring)[tempTYPE_cm],"EMPTY"); str_cpy(content_name_skin,"EMPTY");
	}
	if(nxsCmData[tempTYPE_cm].content == 8)
	{
		reset(disable_all_options,SHOW);
		reset(disable_ent_options,SHOW); reset(disable_skin_options,SHOW);
		set(disable_door_options,SHOW); reset(disable_prop_options,SHOW); 
		set(disable_swt_options,SHOW); set(disable_bonus_options,SHOW);
		nxsCmData[tempTYPE_cm].doorFlag1 = 0;		nxsCmData[tempTYPE_cm].doorFlag2 = 0;
		nxsCmData[tempTYPE_cm].doorFlag3 = 0;		nxsCmData[tempTYPE_cm].doorFlag4 = 0;
		nxsCmData[tempTYPE_cm].doorFlag5 = 0;		
		nxsCmData[tempTYPE_cm].bonusFlag1 = 0;		nxsCmData[tempTYPE_cm].bonusFlag2 = 0;
		nxsCmData[tempTYPE_cm].useSwitch = 0;		nxsCmData[tempTYPE_cm].useTrigger = 0;
	}
	if(nxsCmData[tempTYPE_cm].content == 9)
	{
		reset(disable_all_options,SHOW);
		reset(disable_ent_options,SHOW); reset(disable_skin_options,SHOW);
		set(disable_door_options,SHOW); set(disable_prop_options,SHOW); 
		set(disable_swt_options,SHOW); reset(disable_bonus_options,SHOW);
		nxsCmData[tempTYPE_cm].doorFlag1 = 0;		nxsCmData[tempTYPE_cm].doorFlag2 = 0;
		nxsCmData[tempTYPE_cm].doorFlag3 = 0;		nxsCmData[tempTYPE_cm].doorFlag4 = 0;
		nxsCmData[tempTYPE_cm].doorFlag5 = 0;		nxsCmData[tempTYPE_cm].propFlag1 = 0;
		nxsCmData[tempTYPE_cm].propFlag2 = 0;		nxsCmData[tempTYPE_cm].propFlag3 = 0;
		nxsCmData[tempTYPE_cm].propFlag4 = 0;		nxsCmData[tempTYPE_cm].propFlag5 = 0;
		nxsCmData[tempTYPE_cm].useSwitch = 0;		nxsCmData[tempTYPE_cm].useTrigger = 0;
	}
	
	//Set Door Flag Checkboxes
	if(nxsCmData[tempTYPE_cm].doorFlag1 == 0)
	{pan_setbutton(editor_content_panel,12,0,823,367,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_door_Op_1,NULL,NULL);}
	else{pan_setbutton(editor_content_panel,12,0,823,367,ckbox_bu_on_ov,ckbox_bu_on,ckbox_bu_on_ov,ckbox_bu_on,set_flag_door_Op_1,NULL,NULL);}
	
	if(nxsCmData[tempTYPE_cm].doorFlag2 == 0)
	{pan_setbutton(editor_content_panel,13,0,823,390,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_door_Op_2,NULL,NULL);}
	else{pan_setbutton(editor_content_panel,13,0,823,390,ckbox_bu_on_ov,ckbox_bu_on,ckbox_bu_on_ov,ckbox_bu_on,set_flag_door_Op_2,NULL,NULL);}
	
	if(nxsCmData[tempTYPE_cm].doorFlag3 == 0)
	{pan_setbutton(editor_content_panel,14,0,823,413,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_door_Op_3,NULL,NULL);}
	else{pan_setbutton(editor_content_panel,14,0,823,413,ckbox_bu_on_ov,ckbox_bu_on,ckbox_bu_on_ov,ckbox_bu_on,set_flag_door_Op_3,NULL,NULL);}
	
	if(nxsCmData[tempTYPE_cm].doorFlag4 == 0)
	{pan_setbutton(editor_content_panel,15,0,823,436,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_door_Op_4,NULL,NULL);}
	else{pan_setbutton(editor_content_panel,15,0,823,436,ckbox_bu_on_ov,ckbox_bu_on,ckbox_bu_on_ov,ckbox_bu_on,set_flag_door_Op_4,NULL,NULL);}
	
	if(nxsCmData[tempTYPE_cm].doorFlag5 == 0)
	{pan_setbutton(editor_content_panel,16,0,823,459,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_door_Op_5,NULL,NULL);}
	else{pan_setbutton(editor_content_panel,16,0,823,459,ckbox_bu_on_ov,ckbox_bu_on,ckbox_bu_on_ov,ckbox_bu_on,set_flag_door_Op_5,NULL,NULL);}
	
	//Set Prop Flag Checkboxes
	if(nxsCmData[tempTYPE_cm].propFlag1 == 0)
	{pan_setbutton(editor_content_panel,17,0,986,367,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_prop_Op_1,NULL,NULL);}
	else{pan_setbutton(editor_content_panel,17,0,986,367,ckbox_bu_on_ov,ckbox_bu_on,ckbox_bu_on_ov,ckbox_bu_on,set_flag_prop_Op_1,NULL,NULL);}
	
	if(nxsCmData[tempTYPE_cm].propFlag2 == 0)
	{pan_setbutton(editor_content_panel,18,0,986,390,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_prop_Op_2,NULL,NULL);}
	else{pan_setbutton(editor_content_panel,18,0,986,390,ckbox_bu_on_ov,ckbox_bu_on,ckbox_bu_on_ov,ckbox_bu_on,set_flag_prop_Op_2,NULL,NULL);}
	
	if(nxsCmData[tempTYPE_cm].propFlag3 == 0)
	{pan_setbutton(editor_content_panel,19,0,986,413,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_prop_Op_3,NULL,NULL);}
	else{pan_setbutton(editor_content_panel,19,0,986,413,ckbox_bu_on_ov,ckbox_bu_on,ckbox_bu_on_ov,ckbox_bu_on,set_flag_prop_Op_3,NULL,NULL);}
	
	if(nxsCmData[tempTYPE_cm].propFlag4 == 0)
	{pan_setbutton(editor_content_panel,20,0,986,436,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_prop_Op_4,NULL,NULL);}
	else{pan_setbutton(editor_content_panel,20,0,986,436,ckbox_bu_on_ov,ckbox_bu_on,ckbox_bu_on_ov,ckbox_bu_on,set_flag_prop_Op_4,NULL,NULL);}
	
	if(nxsCmData[tempTYPE_cm].propFlag5 == 0)
	{pan_setbutton(editor_content_panel,21,0,986,459,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_prop_Op_5,NULL,NULL);}
	else{pan_setbutton(editor_content_panel,21,0,986,459,ckbox_bu_on_ov,ckbox_bu_on,ckbox_bu_on_ov,ckbox_bu_on,set_flag_prop_Op_5,NULL,NULL);}
	
	//Set Control Flag Checkboxes
	if(nxsCmData[tempTYPE_cm].useSwitch == 0)
	{pan_setbutton(editor_content_panel,22,0,823,527,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_swt_Op_1,NULL,NULL);}
	else{pan_setbutton(editor_content_panel,22,0,823,527,ckbox_bu_on_ov,ckbox_bu_on,ckbox_bu_on_ov,ckbox_bu_on,set_flag_swt_Op_1,NULL,NULL);}
	
	if(nxsCmData[tempTYPE_cm].useTrigger == 0)
	{pan_setbutton(editor_content_panel,23,0,823,550,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_swt_Op_2,NULL,NULL);}
	else{pan_setbutton(editor_content_panel,23,0,823,550,ckbox_bu_on_ov,ckbox_bu_on,ckbox_bu_on_ov,ckbox_bu_on,set_flag_swt_Op_2,NULL,NULL);}
	
	//Set Bonus Flag Checkboxes
	if(nxsCmData[tempTYPE_cm].bonusFlag1 == 0)
	{pan_setbutton(editor_content_panel,24,0,986,527,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_bonus_Op_1,NULL,NULL);}
	else{pan_setbutton(editor_content_panel,24,0,986,527,ckbox_bu_on_ov,ckbox_bu_on,ckbox_bu_on_ov,ckbox_bu_on,set_flag_bonus_Op_1,NULL,NULL);}
	
	if(nxsCmData[tempTYPE_cm].bonusFlag2 == 0)
	{pan_setbutton(editor_content_panel,25,0,986,550,ckbox_bu,ckbox_bu,ckbox_bu_over,ckbox_bu,set_flag_bonus_Op_2,NULL,NULL);}
	else{pan_setbutton(editor_content_panel,25,0,986,550,ckbox_bu_on_ov,ckbox_bu_on,ckbox_bu_on_ov,ckbox_bu_on,set_flag_bonus_Op_2,NULL,NULL);}
	
	//Set String names
	str_cpy(cm_action_name,(nxs_actions.pstring)[tempTYPE_cm]);
	str_cpy(content_name_ent,(nxs_files.pstring)[tempTYPE_cm]);
	str_cpy(content_name_skin,(nxs_skins.pstring)[tempTYPE_cm]);
}


//AUTO-SAVES CONTENT SETTINGS AND CLOSES THE CONTENT CREATION MENU
void save_cm_slot_data()
{
	textboxMe = NULL;wait(1);
	mouse_mode=0;
	reset(disable_all_options,SHOW);
	reset(disable_ent_options,SHOW); reset(disable_skin_options,SHOW);
	reset(disable_door_options,SHOW); reset(disable_prop_options,SHOW); 
	reset(disable_swt_options,SHOW); reset(disable_bonus_options,SHOW);
	reset(editor_content_panel,SHOW);
	reset(panTextbox_funcName,SHOW);
	reset(show_content_name_ent,SHOW);
	reset(show_content_name_skin,SHOW);
	reset(show_name_door_flag_1,SHOW);
	reset(show_name_door_flag_2,SHOW);
	reset(show_name_door_flag_3,SHOW);
	reset(show_name_door_flag_4,SHOW);
	reset(show_name_door_flag_5,SHOW);
	reset(show_name_prop_flag_1,SHOW);
	reset(show_name_prop_flag_2,SHOW);
	reset(show_name_prop_flag_3,SHOW);
	reset(show_name_prop_flag_4,SHOW);
	reset(show_name_prop_flag_5,SHOW);
	reset(show_name_floor_flag_1,SHOW);
	reset(show_name_floor_flag_2,SHOW);
	content_pan_active = false;
	str_cpy((nxs_actions.pstring)[tempTYPE_cm],cm_action_name);
	str_cpy((nxs_files.pstring)[tempTYPE_cm],content_name_ent);
	str_cpy((nxs_skins.pstring)[tempTYPE_cm],content_name_skin);
	save_editor_cm_data();
	while(mouse_left==1){wait(1);}
	mouse_mode=4;
}


//RESETS CONTENT SETTINGS FOR THE TILE
void reset_cm_slot_data()
{
	set(disable_all_options,SHOW);
	reset(disable_ent_options,SHOW); reset(disable_skin_options,SHOW);
	reset(disable_door_options,SHOW); reset(disable_prop_options,SHOW); 
	reset(disable_swt_options,SHOW); reset(disable_bonus_options,SHOW);
	nxsCmData[tempTYPE_cm].content = 0;
	nxsCmData[tempTYPE_cm].doorFlag1 = 0;
	nxsCmData[tempTYPE_cm].doorFlag2 = 0;
	nxsCmData[tempTYPE_cm].doorFlag3 = 0;
	nxsCmData[tempTYPE_cm].doorFlag4 = 0;
	nxsCmData[tempTYPE_cm].doorFlag5 = 0;
	nxsCmData[tempTYPE_cm].propFlag1 = 0;
	nxsCmData[tempTYPE_cm].propFlag2 = 0;
	nxsCmData[tempTYPE_cm].propFlag3 = 0;
	nxsCmData[tempTYPE_cm].propFlag4 = 0;
	nxsCmData[tempTYPE_cm].propFlag5 = 0;
	nxsCmData[tempTYPE_cm].bonusFlag1 = 0;
	nxsCmData[tempTYPE_cm].bonusFlag2 = 0;
	nxsCmData[tempTYPE_cm].useSwitch = 0;
	nxsCmData[tempTYPE_cm].useTrigger = 0;
	str_cpy((nxs_actions.pstring)[tempTYPE_cm],"EMPTY");
	str_cpy((nxs_files.pstring)[tempTYPE_cm],"EMPTY");
	str_cpy((nxs_skins.pstring)[tempTYPE_cm],"EMPTY");
	str_cpy(cm_action_name,"EMPTY");
	str_cpy(content_name_ent,"EMPTY");
	str_cpy(content_name_skin,"EMPTY");
	content_textbox_active=2;
	set_content_data();
}


//IMPORT AN ENTITY OR SPRITE IMAGE TO SAVE ITS FILE NAME
void import_entity_file()
{
	int _i = 0;
	int pos = 0;
	int slash_pos = 0;
	char* filename = file_dialog("Import Model or Sprite Entity Name","*.mdl;*.png;*.tga;*.pcx;*.dds");
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
		str_cpy(content_name_ent,filename);
	}
	STRING* gotofile = str_create(work_dir); SetCurrentDirectory(_chr(gotofile));
}


//IMPORT MODEL SKIN
void import_entity_skin()
{
	int _i = 0;
	int pos = 0;
	int slash_pos = 0;
	char* filename = file_dialog("Import Skin Texture","*.png;*.tga;*.pcx;*.dds");
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
		str_cpy(content_name_skin,filename);
	}
	STRING* gotofile = str_create(work_dir); SetCurrentDirectory(_chr(gotofile));
}


//RIGHT MOUSE BUTTON : WHEN ANY TILE ON THE SIDE MENU IS CLICKED : OPEN CONTENT MENU TO CONFIG CREATION TYPE
void open_content_menu()
{
	over_pan_id = mouse_panel;
	int slot_zero = tileset_A_functions[over_pan_id->skill_x][over_pan_id->skill_y];
	if(slot_zero==0){reset(show_active_grid,SHOW); set(show_active_tileset,SHOW); return;}
	set(show_name_door_flag_1,SHOW);
	set(show_name_door_flag_2,SHOW);
	set(show_name_door_flag_3,SHOW);
	set(show_name_door_flag_4,SHOW);
	set(show_name_door_flag_5,SHOW);
	set(show_name_prop_flag_1,SHOW);
	set(show_name_prop_flag_2,SHOW);
	set(show_name_prop_flag_3,SHOW);
	set(show_name_prop_flag_4,SHOW);
	set(show_name_prop_flag_5,SHOW);
	set(show_name_floor_flag_1,SHOW);
	set(show_name_floor_flag_2,SHOW);
	set(disable_all_options,SHOW);
	build_type = tileset_A_functions[over_pan_id->skill_x][over_pan_id->skill_y];
	content_pan_active = true;
	cursor_over.pos_x = tileset_A_buttons[over_pan_id->skill_x][over_pan_id->skill_y]->pos_x;
	cursor_over.pos_y = tileset_A_buttons[over_pan_id->skill_x][over_pan_id->skill_y]->pos_y;
	overpanPos[0] = over_pan_id->skill_x;
	overpanPos[1] = over_pan_id->skill_y;
	set(editor_content_panel,SHOW);
	set(panTextbox_funcName,SHOW);
	set(show_content_name_ent,SHOW);
	set(show_content_name_skin,SHOW);
	int _st = 0;
	if(tileset_type==1){_st = 0 + build_type;}
	if(tileset_type==2){_st = 75 + build_type;}
	if(tileset_type==3){_st = 150 + build_type;}
	if(tileset_type==4){_st = 225 + build_type;}
	if(tileset_type==5){_st = 300 + build_type;}
	if(tileset_type==6){_st = 375 + build_type;}
	if(tileset_type==7){_st = 450 + build_type;}
	if(tileset_type==8){_st = 525 + build_type;}
	str_cpy(cm_action_name,(nxs_actions.pstring)[_st]);
	str_cpy(content_name_ent,(nxs_files.pstring)[_st]);
	str_cpy(content_name_skin,(nxs_skins.pstring)[_st]);
	content_textbox_active=2;
	tempTYPE_cm = _st;
	set_content_data();
	cm_tileset_id = tileset_type;
	cm_tile_id = build_type;
	while(mouse_right==1){wait(1);}
}


//EMPTIES A CONTENT MENU STRING WHEN SMALL X IS CLICKED.
void reset_funcname_empty(){str_cpy(cm_action_name,""); content_textbox_active=4;}
void reset_entname_empty(){str_cpy(content_name_ent,"");}
void reset_entskin_empty(){str_cpy(content_name_skin,"");}


//SAVES THE CONTENT MANAGER DATA
void save_editor_cm_data()
{
	STRING* gotofile = str_create(work_dir); SetCurrentDirectory(_chr(gotofile));
	default_handle = file_open_write("cm_build");
	int _x = 0;
	for (; _x<600; _x++)
	{
		if(str_cmp((nxs_actions.pstring)[tempTYPE_cm], "") || str_cmp((nxs_actions.pstring)[tempTYPE_cm], " "))
		{str_cpy((nxs_actions.pstring)[tempTYPE_cm], "EMPTY");}
		if(str_cmp((nxs_files.pstring)[tempTYPE_cm], "") || str_cmp((nxs_files.pstring)[tempTYPE_cm], " "))
		{str_cpy((nxs_files.pstring)[tempTYPE_cm], "EMPTY");}
		if(str_cmp((nxs_skins.pstring)[tempTYPE_cm], "") || str_cmp((nxs_skins.pstring)[tempTYPE_cm], " "))
		{str_cpy((nxs_skins.pstring)[tempTYPE_cm], "EMPTY");}
		file_var_write (default_handle, nxsCmData[_x].content);
		file_var_write (default_handle, nxsCmData[_x].doorFlag1);
		file_var_write (default_handle, nxsCmData[_x].doorFlag2);
		file_var_write (default_handle, nxsCmData[_x].doorFlag3);
		file_var_write (default_handle, nxsCmData[_x].doorFlag4);
		file_var_write (default_handle, nxsCmData[_x].doorFlag5);
		file_var_write (default_handle, nxsCmData[_x].propFlag1);
		file_var_write (default_handle, nxsCmData[_x].propFlag2);
		file_var_write (default_handle, nxsCmData[_x].propFlag3);
		file_var_write (default_handle, nxsCmData[_x].propFlag4);
		file_var_write (default_handle, nxsCmData[_x].propFlag5);
		file_var_write (default_handle, nxsCmData[_x].bonusFlag1);
		file_var_write (default_handle, nxsCmData[_x].bonusFlag2);
		file_var_write (default_handle, nxsCmData[_x].useSwitch);
		file_var_write (default_handle, nxsCmData[_x].useTrigger);next_line();
		file_str_write(default_handle,(nxs_actions.pstring)[_x]);next_line();
		file_str_write(default_handle,(nxs_files.pstring)[_x]);next_line();
		file_str_write(default_handle,(nxs_skins.pstring)[_x]);next_line();
	}
	file_close (default_handle);
	gen_nxs_pointers();
}


//LOADS THE CONTENT MANAGER DATA
void load_editor_cm_data()
{
	STRING* gotofile = str_create(work_dir); SetCurrentDirectory(_chr(gotofile));
	default_handle = file_open_read("cm_build");
	if(default_handle)
	{
		int _x = 0;
		for (; _x<600; _x++)
		{
			nxsCmData[_x].content = file_var_read (default_handle);
			nxsCmData[_x].doorFlag1 = file_var_read (default_handle);
			nxsCmData[_x].doorFlag2 = file_var_read (default_handle);
			nxsCmData[_x].doorFlag3 = file_var_read (default_handle);
			nxsCmData[_x].doorFlag4 = file_var_read (default_handle);
			nxsCmData[_x].doorFlag5 = file_var_read (default_handle);
			nxsCmData[_x].propFlag1 = file_var_read (default_handle);
			nxsCmData[_x].propFlag2 = file_var_read (default_handle);
			nxsCmData[_x].propFlag3 = file_var_read (default_handle);
			nxsCmData[_x].propFlag4 = file_var_read (default_handle);
			nxsCmData[_x].propFlag5 = file_var_read (default_handle);
			nxsCmData[_x].bonusFlag1 = file_var_read (default_handle);
			nxsCmData[_x].bonusFlag2 = file_var_read (default_handle);
			nxsCmData[_x].useSwitch = file_var_read (default_handle);
			nxsCmData[_x].useTrigger = file_var_read (default_handle);
			file_str_read(default_handle,(nxs_actions.pstring)[_x]);
			file_str_read(default_handle,(nxs_files.pstring)[_x]);
			file_str_read(default_handle,(nxs_skins.pstring)[_x]);
		}
	}
	else{save_editor_cm_data();}
	file_close (default_handle);
	STRING* gotofile = str_create(work_dir); SetCurrentDirectory(_chr(gotofile));
}