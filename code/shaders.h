#ifndef _SHADERS_H_
#define _SHADERS_H_

// this material is needed in order to prevent alpha channel troubles (z-fail ?)
MATERIAL *mtl_z_write = 
{
	ambient_blue = 255;
	ambient_green = 255;
	ambient_red = 255;
	effect = "mtl_z_write.fx";
}

#endif