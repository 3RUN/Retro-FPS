/*#########################################################################################################################################################
NEXUS A8 : GAME BUILDER :: By Brian Pressley (Evo) (Evoeon) :::: Chapter Menu FUNCTIONS :: Lite-C :: 3DGamestudio A8
#########################################################################################################################################################*/


//SMALL X BUTTONS TO RESET CHAPTER BOX DATA
void reset_the_ch_link_1(){str_cpy(set_level_link_1," ");}
void reset_the_ch_link_2(){str_cpy(set_level_link_2," ");}
void reset_the_ch_link_3(){str_cpy(set_level_link_3," ");}
void reset_the_ch_link_4(){str_cpy(set_level_link_4," ");}
void reset_the_ch_link_5(){str_cpy(set_level_link_5," ");}
void reset_the_ch_link_6(){str_cpy(set_level_link_6," ");}
void reset_the_ch_link_7(){str_cpy(set_level_link_7," ");}
void reset_the_ch_link_8(){str_cpy(set_level_link_8," ");}
void reset_the_ch_link_9(){str_cpy(set_level_link_9," ");}
void reset_the_ch_link_10(){str_cpy(set_level_link_10," ");}
void reset_the_ch_txt_title(){str_cpy(ch_message_title," "); textbox_active=4;}
void reset_the_ch_txt_msgA(){str_cpy(ch_message_start," "); textbox_active=5;}
void reset_the_ch_txt_msgB(){str_cpy(ch_message_final," "); textbox_active=6;}


//OPEN THE CHAPTER EDITOR
void open_chapter_menu()
{
	set(chapter_menu_bg,SHOW);
	set(show_link_1_name,SHOW);
	set(show_link_2_name,SHOW);
	set(show_link_3_name,SHOW);
	set(show_link_4_name,SHOW);
	set(show_link_5_name,SHOW);
	set(show_link_6_name,SHOW);
	set(show_link_7_name,SHOW);
	set(show_link_8_name,SHOW);
	set(show_link_9_name,SHOW);
	set(show_link_10_name,SHOW);
	set(panTextbox_Title,SHOW);
	set(panTextbox_A,SHOW);
	set(panTextbox_B,SHOW);
	ch_editor_active = true;	
}


//REMOVE THE CHAPTER EDITOR
void close_chapter_menu()
{
	textboxMe = NULL;wait(1);
	textbox_active=3;
	mouse_mode=0;
	reset(panTextbox_Title,SHOW);
	reset(panTextbox_A,SHOW); 
	reset(panTextbox_B,SHOW);
	reset(chapter_menu_bg,SHOW);
	reset(show_link_1_name,SHOW);
	reset(show_link_2_name,SHOW);
	reset(show_link_3_name,SHOW);
	reset(show_link_4_name,SHOW);
	reset(show_link_5_name,SHOW);
	reset(show_link_6_name,SHOW);
	reset(show_link_7_name,SHOW);
	reset(show_link_8_name,SHOW);
	reset(show_link_9_name,SHOW);
	reset(show_link_10_name,SHOW);
	str_cpy(ch_message_title,str_create(" "));
	str_cpy(ch_message_start,str_create(" "));
	str_cpy(ch_message_final,str_create(" "));
	str_cpy(set_level_link_1," ");
	str_cpy(set_level_link_2," ");
	str_cpy(set_level_link_3," ");
	str_cpy(set_level_link_4," ");
	str_cpy(set_level_link_5," ");
	str_cpy(set_level_link_6," ");
	str_cpy(set_level_link_7," ");
	str_cpy(set_level_link_8," ");
	str_cpy(set_level_link_9," ");
	str_cpy(set_level_link_10," ");
	ch_editor_active = false;
	wait(32);
	mouse_mode=4;
}


//IMPORT LEVEL FILES TO LINK THEM TOGETHER AS A CHAPTER FILE
void import_level_name()
{
	int _i = 0;
	int pos = 0;
	int slash_pos = 0;
	
	char* filename = file_dialog("Import Level File",NULL);
	int path_len = str_len(filename);
	if(filename)
	{
		default_handle = file_open_read (filename);
		file_str_read(default_handle,extension_type);
		if(!str_cmp(extension_type, ".nxs")){printf("Wrong file type.\n\nThis is not a Nexus Level File!"); file_close (default_handle); STRING* gotofile = str_create(work_dir); SetCurrentDirectory(_chr(gotofile)); return;}
		file_close (default_handle);
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
		if(chapter_link_id==0){str_cpy(set_level_link_1,filename);}
		if(chapter_link_id==1){str_cpy(set_level_link_2,filename);}
		if(chapter_link_id==2){str_cpy(set_level_link_3,filename);}
		if(chapter_link_id==3){str_cpy(set_level_link_4,filename);}
		if(chapter_link_id==4){str_cpy(set_level_link_5,filename);}
		if(chapter_link_id==5){str_cpy(set_level_link_6,filename);}
		if(chapter_link_id==6){str_cpy(set_level_link_7,filename);}
		if(chapter_link_id==7){str_cpy(set_level_link_8,filename);}
		if(chapter_link_id==8){str_cpy(set_level_link_9,filename);}
		if(chapter_link_id==9){str_cpy(set_level_link_10,filename);}
		STRING* gotofile = str_create(work_dir); SetCurrentDirectory(_chr(gotofile));
	}
}


//BUTTONS FUNCTIONS TO IMPORT UP TO 10 LEVELS TO LINK TOGETHER
void ch_import_bu_id_1(){chapter_link_id=0; import_level_name();}
void ch_import_bu_id_2(){chapter_link_id=1; import_level_name();}
void ch_import_bu_id_3(){chapter_link_id=2; import_level_name();}
void ch_import_bu_id_4(){chapter_link_id=3; import_level_name();}
void ch_import_bu_id_5(){chapter_link_id=4; import_level_name();}
void ch_import_bu_id_6(){chapter_link_id=5; import_level_name();}
void ch_import_bu_id_7(){chapter_link_id=6; import_level_name();}
void ch_import_bu_id_8(){chapter_link_id=7; import_level_name();}
void ch_import_bu_id_9(){chapter_link_id=8; import_level_name();}
void ch_import_bu_id_10(){chapter_link_id=9; import_level_name();}


//SAVES A CHAPTER FILE
void save_chapter_to_file()
{
	textboxMe=NULL;wait(1);
	if(str_cmp(set_level_link_1," ")){printf("Level 1 must have a file imported\nto save a chapter file."); return;}
	char* filename = file_dialog_save("Save Chapter File",NULL);
	if(filename)
	{
		int _i = -1;
		
		if(str_cmp(ch_message_title, "") || str_cmp(ch_message_title, " "))
		{str_cpy(ch_message_title, "Default Ch Name : Was saved with empty name.");}
		if(str_cmp(ch_message_start, "") || str_cmp(ch_message_start, " "))
		{str_cpy(ch_message_start, "Default Msg A : Was saved with empty msg.");}
		if(str_cmp(ch_message_final, "") || str_cmp(ch_message_final, " "))
		{str_cpy(ch_message_final, "Default Msg B : Was saved with empty msg.");}
		
		default_handle = file_open_write(filename);
		file_str_write(default_handle,".xch");next_line();
		file_str_write(default_handle,ch_message_title);next_line();
		file_str_write(default_handle,ch_message_start);next_line();
		file_str_write(default_handle,ch_message_final);next_line();
		file_str_write(default_handle,set_level_link_1);next_line();
	if(!str_cmp(set_level_link_2, " ")){file_str_write(default_handle,set_level_link_2);next_line();}else{_i+=1;}
	if(!str_cmp(set_level_link_3, " ")){file_str_write(default_handle,set_level_link_3);next_line();}else{_i+=1;}
	if(!str_cmp(set_level_link_4, " ")){file_str_write(default_handle,set_level_link_4);next_line();}else{_i+=1;}
	if(!str_cmp(set_level_link_5, " ")){file_str_write(default_handle,set_level_link_5);next_line();}else{_i+=1;}
	if(!str_cmp(set_level_link_6, " ")){file_str_write(default_handle,set_level_link_6);next_line();}else{_i+=1;}
	if(!str_cmp(set_level_link_7, " ")){file_str_write(default_handle,set_level_link_7);next_line();}else{_i+=1;}
	if(!str_cmp(set_level_link_8, " ")){file_str_write(default_handle,set_level_link_8);next_line();}else{_i+=1;}
	if(!str_cmp(set_level_link_9, " ")){file_str_write(default_handle,set_level_link_9);next_line();}else{_i+=1;}
	if(!str_cmp(set_level_link_10, " ")){file_str_write(default_handle,set_level_link_10);next_line();}else{_i+=1;}
		
		int _areEmpty = 0;
		for (; _areEmpty<=_i; _areEmpty++)
		{
			file_str_write(default_handle," "); next_line();
		}
		
		file_close (default_handle);
		STRING* gotofile = str_create(work_dir); SetCurrentDirectory(_chr(gotofile));
	}
	close_chapter_menu();
}


//LOADS A CHAPTER FILE
void load_chapter_from_file()
{
	textboxMe=NULL;wait(1);
	char* filename = file_dialog("Load Chapter File",NULL);
	if(filename)
	{
		str_cpy(ch_message_title,str_create(" "));
		str_cpy(ch_message_start,str_create(" "));
		str_cpy(ch_message_final,str_create(" "));
		str_cpy(set_level_link_1," ");
		str_cpy(set_level_link_2," ");
		str_cpy(set_level_link_3," ");
		str_cpy(set_level_link_4," ");
		str_cpy(set_level_link_5," ");
		str_cpy(set_level_link_6," ");
		str_cpy(set_level_link_7," ");
		str_cpy(set_level_link_8," ");
		str_cpy(set_level_link_9," ");
		str_cpy(set_level_link_10," ");
		
		default_handle = file_open_read (filename);
		file_str_read(default_handle,extension_type);
		if(!str_cmp(extension_type, ".xch")){printf("Wrong file type.\n\nThis is not a Nexus Chapter File!"); file_close (default_handle); STRING* gotofile = str_create(work_dir); SetCurrentDirectory(_chr(gotofile)); return;}
		
		file_str_read(default_handle,ch_message_title);
		file_str_read(default_handle,ch_message_start);
		file_str_read(default_handle,ch_message_final);
		file_str_read(default_handle,set_level_link_1);
		file_str_read(default_handle,set_level_link_2);if(str_cmp(set_level_link_2, " ")){file_close (default_handle);textbox_active = 2;STRING* gotofile = str_create(work_dir); SetCurrentDirectory(_chr(gotofile));return;}
		file_str_read(default_handle,set_level_link_3);if(str_cmp(set_level_link_3, " ")){file_close (default_handle);textbox_active = 2;STRING* gotofile = str_create(work_dir); SetCurrentDirectory(_chr(gotofile));return;}
		file_str_read(default_handle,set_level_link_4);if(str_cmp(set_level_link_4, " ")){file_close (default_handle);textbox_active = 2;STRING* gotofile = str_create(work_dir); SetCurrentDirectory(_chr(gotofile));return;}
		file_str_read(default_handle,set_level_link_5);if(str_cmp(set_level_link_5, " ")){file_close (default_handle);textbox_active = 2;STRING* gotofile = str_create(work_dir); SetCurrentDirectory(_chr(gotofile));return;}
		file_str_read(default_handle,set_level_link_6);if(str_cmp(set_level_link_6, " ")){file_close (default_handle);textbox_active = 2;STRING* gotofile = str_create(work_dir); SetCurrentDirectory(_chr(gotofile));return;}
		file_str_read(default_handle,set_level_link_7);if(str_cmp(set_level_link_7, " ")){file_close (default_handle);textbox_active = 2;STRING* gotofile = str_create(work_dir); SetCurrentDirectory(_chr(gotofile));return;}
		file_str_read(default_handle,set_level_link_8);if(str_cmp(set_level_link_8, " ")){file_close (default_handle);textbox_active = 2;STRING* gotofile = str_create(work_dir); SetCurrentDirectory(_chr(gotofile));return;}
		file_str_read(default_handle,set_level_link_9);if(str_cmp(set_level_link_9, " ")){file_close (default_handle);textbox_active = 2;STRING* gotofile = str_create(work_dir); SetCurrentDirectory(_chr(gotofile));return;}
		file_str_read(default_handle,set_level_link_10);if(str_cmp(set_level_link_10, " ")){file_close (default_handle);textbox_active = 2;STRING* gotofile = str_create(work_dir); SetCurrentDirectory(_chr(gotofile));return;}
		file_close (default_handle);
		textbox_active = 2;
		STRING* gotofile = str_create(work_dir); SetCurrentDirectory(_chr(gotofile));
	}
}