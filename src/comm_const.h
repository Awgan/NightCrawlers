#ifndef COMM_CONST_H_
#define COMM_CONST_H_

#define WIN_WIDTH	800
#define WIN_HIGHT	600

#define HERO_WIDTH	50
#define HERO_HIGHT	50

#define HERO_SPRITES	8

#define BACKGROUND 0

#include <string>

enum Point_type { neutral = 0, hero = 1, bullet = 2, obstacle = 3 };

enum Obstacle_type { none = -1, box = 0, rock = 1, flower = 2 };

const std::string comm_arr_sprite_files[5] = { //TODO:: put real path to files
	"../fig/xxx.bmp",				//neutral
	"../fig/worms02.bmp",			//hero
	"../fig/xxx.bmp",				//bullet
	"../fig/xxx.bmp",				//obstacle
	"../fig/xxx.bmp"			//cursor white
};

const int comm_arr_sprite_dimensions[8][4] = {
	{10,6,89,94}, //direction: left
	{110,6,89,94},
	{210,6,89,94},
	{310,6,89,94},
	
	{401,6,89,94}, //direction right
	{501,6,89,94},
	{601,6,89,94},
	{701,6,89,94}
};

//rectangle dimensions to take each type of obstacle to rendering
const int comm_arr_sprite_obstacle[3][4] = {
	{10,113,92,75}, 	//box
	{123,106,82,86},	//rock
	{205,107,141,80}	//flower	
};
#endif
