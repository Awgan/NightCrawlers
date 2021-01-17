#ifndef COMM_CONST_H_
#define COMM_CONST_H_

#include <SDL2/SDL.h>

#define WIN_WIDTH	800
#define WIN_HIGHT	600

#define HERO_WIDTH	35
#define HERO_HIGHT	35

#define PLATFORM_W	135
#define PLATFORM_H	HERO_HIGHT/2

#define HERO_SPRITES	8

#define BACKGROUND 1

#define GAME_DELAY	20

#define GRAVITY_SPEED 0.5
#define GRAVITY_SPEED_MAX 8

#define OBSTACLE_PLACE	SDLK_p
#define PLATFORM_PLACE	SDLK_l
#define GAME_SPEED_UP	SDLK_KP_PLUS
#define GAME_SPEED_DOWN	SDLK_KP_MINUS
#define BULLET_FIRE		SDLK_p


#include <string>

enum Point_type { neutral = 0, hero = 1, bullet = 2, obstacle = 3 };

enum Obstacle_type { none = -1, box = 0, rock = 1, flower = 2, wall = 3 };

const std::string arr_sprite_files[6] = { //TODO:: put real path to files
	"../fig/xxx.bmp",				//neutral
	"../fig/worms02.bmp",			//hero
	"../fig/xxx.bmp",				//bullet
	"../fig/worms02.bmp",				//obstacle
	"../fig/xxx.bmp",			//cursor white
	"../fig/wall01.bmp"			//wall/platform
};

const int arr_sprite_dimensions[8][4] = {
	{10,6,89,94}, //direction: left
	{110,6,89,94},
	{210,6,89,94},
	{310,6,89,94},

	{401,6,89,94}, //direction right
	{501,6,89,94},
	{601,6,89,94},
	{701,6,89,94}
};

//rectangle dimensions for obstacle rendering
const int arr_sprite_obstacle[4][4] = {
	{10,113,92,75}, 	//box
	{123,106,82,86},	//rock
	{205,107,141,80},	//flower
	{11,74,616,53}		//wall
};

//rectangle dimensions for wall rendering
const int arr_sprite_wall[3][4] = {
	{0,0,0,0}, 			//
	{11,74,616,53},		//wall
	{0,0,0,0}			//
};
#endif
