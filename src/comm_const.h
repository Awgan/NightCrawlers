#ifndef COMM_CONST_H_
#define COMM_CONST_H_

#define WIN_WIDTH	640
#define WIN_HIGHT	480

#include <string>

enum Point_type { neutral = 0, hero = 1, bullet = 2, obstacle = 3 };

enum Obstacle_type { wall = 0 };

const std::string comm_arr_sprite_files[4] = { //TODO:: put real path to files
	"../fig/xxx.bmp",				//neutral
	"../fig/worms02.bmp",			//hero
	"../fig/xxx.bmp",				//bullet
	"../fig/xxx.bmp"				//obstacle
};

const int comm_arr_sprite_dimensions[4][4] = {
	{0,0,100,100}, //TODO:: put real x,y and width, height values
	{100,0,100,100},
	{200,0,100,100},
	{300,0,100,100}	
};

#endif
