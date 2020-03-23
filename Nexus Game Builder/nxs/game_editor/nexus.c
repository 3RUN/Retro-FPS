/*#########################################################################################################################################################
NEXUS A8 : GAME BUILDER :: By Brian Pressley (Evo) (Evoeon) :::: Startup Script
#########################################################################################################################################################*/


//ENGINE SCRIPTS
#include <acknex.h>
#include <windows.h>
#include <strio.c>


//EDITOR PATHS
#define PRAGMA_PATH "editor"
#define PRAGMA_PATH "code"
#define PRAGMA_PATH "code_mesh"
#define PRAGMA_PATH "levels"
#define PRAGMA_PATH "chapters"
#define PRAGMA_PATH "tiles"


//EDITOR INIT
#include "config.h"
#include "nexus.h"


//STARTUP
void main ()
{
	fps_max = 60;
	video_mode = 9;
	max_entities = 0;
	screen_size.x = 1280;
	screen_size.y = 720;
	vec_set(screen_color,vector(1,1,1));
	on_close = exit_editor;
	wait(3);
	video_window(NULL,NULL,16+32+64,"Nexus : Game Builder (Early Prototype)");
	call_mouse();
	while(key_any==0){wait(1);}
	while(key_any==1){wait(1);}
	reset(intro_panel,SHOW);
	init_editor();	
	
	//EDITOR UPDATE LOOP
	while(1)
	{
		if(level_active == true && ch_editor_active == false && content_pan_active==false)
		{			
			//PRESS LEFT MOUSE BUTTON TO DRAW A TILE (MAP ONLY)
			if(mouse_left==1 && mouse_right==0  && mouse_pos.y>=33 && mouse_pos.x<=1079 && mouse_pos.x >= pan_arrayA[0][0]->pos_x && mouse_pos.y >= pan_arrayA[0][0]->pos_y &&
			mouse_pos.x <= pan_arrayA[LEVEL_X_MAX-1][LEVEL_Y_MAX-1]->pos_x+31 && mouse_pos.y <= pan_arrayA[LEVEL_X_MAX-1][LEVEL_Y_MAX-1]->pos_y+31 && content_pan_active == false &&
			editor_mode==0)
			{interactive_grid();}
			
			
			//PRESS RIGHT MOUSE BUTTON TO ERASE A TILE (MAP ONLY)
			if(mouse_right==1 && mouse_left==0 && mouse_pos.y>=33 && mouse_pos.x<=1079 && mouse_pos.x >= pan_arrayA[0][0]->pos_x && mouse_pos.y >= pan_arrayA[0][0]->pos_y &&
			mouse_pos.x <= pan_arrayA[LEVEL_X_MAX-1][LEVEL_Y_MAX-1]->pos_x+31 && mouse_pos.y <= pan_arrayA[LEVEL_X_MAX-1][LEVEL_Y_MAX-1]->pos_y+31 && content_pan_active == false &&
			editor_mode==0)
			{reset_a_tile();}
			
			
			//PRESS RIGHT MOUSE BUTTON ON MENU TILES TO OPEN THE CREATION EDITOR (SIDE MENU ONLY)
			if(mouse_right==1 && mouse_left==0 && mouse_pos.y>=33 && mouse_pos.x>=1080 && over_pan_id->bmap==icon_bu && content_pan_active == false)
			{open_content_menu();}
			
			
			//PRESS MOUSE LEFT WHEN MOUSE IS OVER A TILE ON THE GRID TO EDIT CERTAIN CONTENT TYPES (POPUP MENU)
			if(mouse_left==1 && mouse_right==0 && mouse_pos.y>=33 && mouse_pos.x<=1079 && mouse_pos.x >= pan_arrayA[0][0]->pos_x && mouse_pos.y >= pan_arrayA[0][0]->pos_y &&
			mouse_pos.x <= pan_arrayA[LEVEL_X_MAX-1][LEVEL_Y_MAX-1]->pos_x+31 && mouse_pos.y <= pan_arrayA[LEVEL_X_MAX-1][LEVEL_Y_MAX-1]->pos_y+31 && content_pan_active == false && mod_pan_active == false &&
			editor_mode==1)
			{modify_tiles();}
			
			
			//USE WASD TO EXPLORE THE LEVEL GRID
			if(content_pan_active == false && mod_pan_active == false && ch_editor_active == false)
			{
				int _x = 0;
				if(key_d==1 && pan_arrayA[LEVEL_X_MAX-1][LEVEL_Y_MAX-1]->pos_x>=1050+10){
					for (; _x<LEVEL_X_MAX; _x++) 
					{
						int _y = 0;
						for (; _y<LEVEL_Y_MAX; _y++) 
						{
							pan_arrayA[_x][_y]->pos_x-=pan_speed;
							pan_arrayB[_x][_y]->pos_x=pan_arrayA[_x][_y]->pos_x;
							pan_arrayC[_x][_y]->pos_x=pan_arrayA[_x][_y]->pos_x;
						}
					}
				}
				int _x = 0;
				if(key_a==1 && pan_arrayA[0][0]->pos_x<=-16){
					for (; _x<LEVEL_X_MAX; _x++) 
					{
						int _y = 0;
						for (; _y<LEVEL_Y_MAX; _y++) 
						{
							pan_arrayA[_x][_y]->pos_x+=pan_speed;	
							pan_arrayB[_x][_y]->pos_x=pan_arrayA[_x][_y]->pos_x;	
							pan_arrayC[_x][_y]->pos_x=pan_arrayA[_x][_y]->pos_x;	
						}
					}
				}
				int _x = 0;
				if(key_s==1 && pan_arrayA[LEVEL_X_MAX-1][LEVEL_Y_MAX-1]->pos_y>=690){
					for (; _x<LEVEL_X_MAX; _x++) 
					{
						int _y = 0;
						for (; _y<LEVEL_Y_MAX; _y++) 
						{
							pan_arrayA[_x][_y]->pos_y-=pan_speed;
							pan_arrayB[_x][_y]->pos_y=pan_arrayA[_x][_y]->pos_y;
							pan_arrayC[_x][_y]->pos_y=pan_arrayA[_x][_y]->pos_y;	
						}
					}
				}
				int _x = 0;
				if(key_w==1 && pan_arrayA[0][0]->pos_y<=16){
					for (; _x<LEVEL_X_MAX; _x++) 
					{
						int _y = 0;
						for (; _y<LEVEL_Y_MAX; _y++) 
						{
							pan_arrayA[_x][_y]->pos_y+=pan_speed;	
							pan_arrayB[_x][_y]->pos_y=pan_arrayA[_x][_y]->pos_y;	
							pan_arrayC[_x][_y]->pos_y=pan_arrayA[_x][_y]->pos_y;	
						}
					}
				}
			}
			
			
			//ONLY SHOW VISIBLE TILES ONSCREEN
			int _x = 0;
			for (; _x<LEVEL_X_MAX; _x++) 
			{
				int _y = 0;
				for (; _y<LEVEL_Y_MAX; _y++) 
				{
					if(pan_arrayA[_x][_y]->pos_x>=1080 || pan_arrayA[_x][_y]->pos_x<=-32 || pan_arrayA[_x][_y]->pos_y<=-32 || pan_arrayA[_x][_y]->pos_y>=720)
					{reset(pan_arrayA[_x][_y],SHOW); reset(pan_arrayB[_x][_y],SHOW); reset(pan_arrayC[_x][_y],SHOW);} 
					else{set(pan_arrayA[_x][_y],SHOW); set(pan_arrayB[_x][_y],SHOW); set(pan_arrayC[_x][_y],SHOW);}	
				}
			}
			
			
			//SET ALPHA OF ACTIVE/INACTIVE LAYERS
			int _x = 0;
			for (; _x<LEVEL_X_MAX; _x++) 
			{
				int _y = 0;
				for (; _y<LEVEL_Y_MAX; _y++) 
				{
					if(Set_toggle_layers==0)
					{
						pan_arrayA[_x][_y].alpha=100; pan_arrayB[_x][_y].alpha=30; pan_arrayC[_x][_y].alpha=2;
					} 
					if(Set_toggle_layers==1)
					{
						pan_arrayA[_x][_y].alpha=15; pan_arrayB[_x][_y].alpha=100; pan_arrayC[_x][_y].alpha=2;
					} 
					if(Set_toggle_layers==2)
					{
						pan_arrayA[_x][_y].alpha=20; pan_arrayB[_x][_y].alpha=25; pan_arrayC[_x][_y].alpha=100; 
					} 
				}
			}
		}	
		
		
		//SET VISUAL OF ACTIVE AREA (Blue box outline)
		if(mouse_left==1 && mouse_pos.x<=1079 && content_pan_active == false || mouse_right==1 && mouse_pos.x<=1079 && content_pan_active == false && ch_editor_active == false)
		{
			set(show_active_grid,SHOW); reset(show_active_tileset,SHOW);
		}

		
		wait(1);		
	}
}
