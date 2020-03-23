//#########################################################################################################################################################
//CREATE AUTO-BIND SCRIPT (NEEDS UPDATED)
//By : Brian Pressley (EVO)

//This script is standalone and must stay in the main folder. This file is not included in a published project.
//Run this script whenever you need to update you resources and bind them.
//This will re-generate the games bind script with all included resources from the folders listed below.
//#########################################################################################################################################################

#include <acknex.h>
#include <strio.c>

var nms_default_handle;
var counter;
void nms_line_space(){file_asc_write (nms_default_handle, 13); file_asc_write (nms_default_handle, 10);}

void nms_autobind()
{
	var bind_counter = 0;
	STRING* gotofile;
	TEXT* index_a = { strings = 1000;}
	TEXT* index_b = { strings = 1000;}
	TEXT* index_c = { strings = 1000;}
	TEXT* index_d = { strings = 1000;}
	TEXT* index_e = { strings = 1000;}
	TEXT* index_f = { strings = 1000;}
	TEXT* index_g = { strings = 1000;}
	TEXT* index_h = { strings = 1000;}
	TEXT* index_i = { strings = 1000;}
	TEXT* index_j = { strings = 1000;}
	while (bind_counter <= 999){(index_a.pstring)[bind_counter] = str_create("                  ");bind_counter += 1;} bind_counter=0;
	while (bind_counter <= 999){(index_b.pstring)[bind_counter] = str_create("                  ");bind_counter += 1;} bind_counter=0;
	while (bind_counter <= 999){(index_c.pstring)[bind_counter] = str_create("                  ");bind_counter += 1;} bind_counter=0;
	while (bind_counter <= 999){(index_d.pstring)[bind_counter] = str_create("                  ");bind_counter += 1;} bind_counter=0;
	while (bind_counter <= 999){(index_e.pstring)[bind_counter] = str_create("                  ");bind_counter += 1;} bind_counter=0;
	while (bind_counter <= 999){(index_f.pstring)[bind_counter] = str_create("                  ");bind_counter += 1;} bind_counter=0;
	while (bind_counter <= 999){(index_g.pstring)[bind_counter] = str_create("                  ");bind_counter += 1;} bind_counter=0;
	while (bind_counter <= 999){(index_h.pstring)[bind_counter] = str_create("                  ");bind_counter += 1;} bind_counter=0;
	while (bind_counter <= 999){(index_i.pstring)[bind_counter] = str_create("                  ");bind_counter += 1;} bind_counter=0;
	while (bind_counter <= 999){(index_j.pstring)[bind_counter] = str_create("                  ");bind_counter += 1;} bind_counter=0;
	
	STRING* gotofile = str_create(work_dir); str_cat(gotofile,"resources"); SetCurrentDirectory(_chr(gotofile));txt_for_dir(index_a, "*.*");
	gotofile = str_create(work_dir); str_cat(gotofile,"resources\\ai"); SetCurrentDirectory(_chr(gotofile));txt_for_dir(index_b, "*.*");
	gotofile = str_create(work_dir); str_cat(gotofile,"resources\\items"); SetCurrentDirectory(_chr(gotofile));txt_for_dir(index_c, "*.*");
	gotofile = str_create(work_dir); str_cat(gotofile,"resources\\props"); SetCurrentDirectory(_chr(gotofile));txt_for_dir(index_d, "*.*");
	gotofile = str_create(work_dir); str_cat(gotofile,"resources\\props\\foliage"); SetCurrentDirectory(_chr(gotofile));txt_for_dir(index_e, "*.*");
	gotofile = str_create(work_dir); str_cat(gotofile,"resources\\props\\indoor"); SetCurrentDirectory(_chr(gotofile));txt_for_dir(index_f, "*.*");
	gotofile = str_create(work_dir); str_cat(gotofile,"resources\\props\\others"); SetCurrentDirectory(_chr(gotofile));txt_for_dir(index_g, "*.*");
	gotofile = str_create(work_dir); str_cat(gotofile,"nxs\\game_editor\\chapters"); SetCurrentDirectory(_chr(gotofile));txt_for_dir(index_h, "*.*");
	gotofile = str_create(work_dir); str_cat(gotofile,"nxs\\game_editor\\levels"); SetCurrentDirectory(_chr(gotofile));txt_for_dir(index_i, "*.*");
	gotofile = str_create(work_dir); str_cat(gotofile,"textures"); SetCurrentDirectory(_chr(gotofile));txt_for_dir(index_j, "*.*");
	STRING* gotofile = str_create(work_dir); SetCurrentDirectory(_chr(gotofile));
	
	nms_default_handle = file_open_write ("code\\nxs_autobind.h");
	file_str_write (nms_default_handle, "//Auto-bind Files");nms_line_space();
	file_str_write (nms_default_handle, "//Nothing to modify. This file is already included");nms_line_space();nms_line_space();
	
	file_str_write (nms_default_handle, "//BIND RESOURCES");nms_line_space();
	while (bind_counter <= 999)
	{
		if(str_cmpi((index_a.pstring)[bind_counter],"                  ")){bind_counter += 1; continue;}
		else
		{
			file_str_write (nms_default_handle, "#define PRAGMA_BIND ");
			file_asc_write(nms_default_handle,34); 
			file_str_write (nms_default_handle, (index_a.pstring)[bind_counter]);
			file_asc_write(nms_default_handle,34);
			file_asc_write(nms_default_handle,59);
			nms_line_space();
			bind_counter += 1;
		}
	}
	
	nms_line_space();
	bind_counter=0;
	
	file_str_write (nms_default_handle, "//BIND RESOURCES AI");nms_line_space();
	while (bind_counter <= 999)
	{
		if(str_cmpi((index_b.pstring)[bind_counter],"                  ")){bind_counter += 1; continue;}
		else
		{
			file_str_write (nms_default_handle, "#define PRAGMA_BIND ");
			file_asc_write(nms_default_handle,34); 
			file_str_write (nms_default_handle, (index_b.pstring)[bind_counter]);
			file_asc_write(nms_default_handle,34);
			file_asc_write(nms_default_handle,59);
			nms_line_space();
			bind_counter += 1;
		}
	} 
	
	nms_line_space();
	bind_counter=0;
	
	file_str_write (nms_default_handle, "//BIND RESOURCES ITEMS");nms_line_space();
	while (bind_counter <= 999)
	{
		if(str_cmpi((index_c.pstring)[bind_counter],"                  ")){bind_counter += 1; continue;}
		else
		{
			file_str_write (nms_default_handle, "#define PRAGMA_BIND ");
			file_asc_write(nms_default_handle,34); 
			file_str_write (nms_default_handle, (index_c.pstring)[bind_counter]);
			file_asc_write(nms_default_handle,34);
			file_asc_write(nms_default_handle,59);
			nms_line_space();
			bind_counter += 1;
		}
	} 
	
	nms_line_space();
	bind_counter=0;
	
	file_str_write (nms_default_handle, "//BIND RESOURCES PROPS");nms_line_space();
	while (bind_counter <= 999)
	{
		if(str_cmpi((index_d.pstring)[bind_counter],"                  ")){bind_counter += 1; continue;}
		else
		{
			file_str_write (nms_default_handle, "#define PRAGMA_BIND ");
			file_asc_write(nms_default_handle,34); 
			file_str_write (nms_default_handle, (index_d.pstring)[bind_counter]);
			file_asc_write(nms_default_handle,34);
			file_asc_write(nms_default_handle,59);
			nms_line_space();
			bind_counter += 1;
		}
	} 
	
	nms_line_space();
	bind_counter=0;
	
	file_str_write (nms_default_handle, "//BIND RESOURCES PROPS FOLIAGE");nms_line_space();
	while (bind_counter <= 999)
	{
		if(str_cmpi((index_e.pstring)[bind_counter],"                  ")){bind_counter += 1; continue;}
		else
		{
			file_str_write (nms_default_handle, "#define PRAGMA_BIND ");
			file_asc_write(nms_default_handle,34); 
			file_str_write (nms_default_handle, (index_e.pstring)[bind_counter]);
			file_asc_write(nms_default_handle,34);
			file_asc_write(nms_default_handle,59);
			nms_line_space();
			bind_counter += 1;
		}
	} 
	
	nms_line_space();
	bind_counter=0;
	
	file_str_write (nms_default_handle, "//BIND RESOURCES PROPS INDOOR");nms_line_space();
	while (bind_counter <= 999)
	{
		if(str_cmpi((index_f.pstring)[bind_counter],"                  ")){bind_counter += 1; continue;}
		else
		{
			file_str_write (nms_default_handle, "#define PRAGMA_BIND ");
			file_asc_write(nms_default_handle,34); 
			file_str_write (nms_default_handle, (index_f.pstring)[bind_counter]);
			file_asc_write(nms_default_handle,34);
			file_asc_write(nms_default_handle,59);
			nms_line_space();
			bind_counter += 1;
		}
	} 
	
	nms_line_space();
	bind_counter=0;
	
	file_str_write (nms_default_handle, "//BIND RESOURCES PROPS OTHERS");nms_line_space();
	while (bind_counter <= 999)
	{
		if(str_cmpi((index_g.pstring)[bind_counter],"                  ")){bind_counter += 1; continue;}
		else
		{
			file_str_write (nms_default_handle, "#define PRAGMA_BIND ");
			file_asc_write(nms_default_handle,34); 
			file_str_write (nms_default_handle, (index_g.pstring)[bind_counter]);
			file_asc_write(nms_default_handle,34);
			file_asc_write(nms_default_handle,59);
			nms_line_space();
			bind_counter += 1;
		}
	} 
	
	nms_line_space();
	bind_counter=0;
	
	file_str_write (nms_default_handle, "//BIND CHAPTER FILES");nms_line_space();
	while (bind_counter <= 999)
	{
		if(str_cmpi((index_h.pstring)[bind_counter],"                  ")){bind_counter += 1; continue;}
		else
		{
			file_str_write (nms_default_handle, "#define PRAGMA_BIND ");
			file_asc_write(nms_default_handle,34); 
			file_str_write (nms_default_handle, (index_h.pstring)[bind_counter]);
			file_asc_write(nms_default_handle,34);
			file_asc_write(nms_default_handle,59);
			nms_line_space();
			bind_counter += 1;
		}
	} 
	
	nms_line_space();
	bind_counter=0;
	
	file_str_write (nms_default_handle, "//BIND LEVEL FILES");nms_line_space();
	while (bind_counter <= 999)
	{
		if(str_cmpi((index_i.pstring)[bind_counter],"                  ")){bind_counter += 1; continue;}
		else
		{
			file_str_write (nms_default_handle, "#define PRAGMA_BIND ");
			file_asc_write(nms_default_handle,34); 
			file_str_write (nms_default_handle, (index_i.pstring)[bind_counter]);
			file_asc_write(nms_default_handle,34);
			file_asc_write(nms_default_handle,59);
			nms_line_space();
			bind_counter += 1;
		}
	} 
	
	nms_line_space();
	bind_counter=0;
	
	file_str_write (nms_default_handle, "//BIND GAME TEXTURES");nms_line_space();
	while (bind_counter <= 999)
	{
		if(str_cmpi((index_j.pstring)[bind_counter],"                  ")){bind_counter += 1; continue;}
		else
		{
			file_str_write (nms_default_handle, "#define PRAGMA_BIND ");
			file_asc_write(nms_default_handle,34); 
			file_str_write (nms_default_handle, (index_j.pstring)[bind_counter]);
			file_asc_write(nms_default_handle,34);
			file_asc_write(nms_default_handle,59);
			nms_line_space();
			bind_counter += 1;
		}
	}
	
	file_close (nms_default_handle);
	/////////////////////////////
}

void main()
{
	nms_autobind();
	sys_exit("bye");
}