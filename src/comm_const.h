#ifndef COMM_CONST_H_
#define COMM_CONST_H_

#include <SDL2/SDL.h>

#define WIN_WIDTH	720
#define WIN_HEIGHT	450

#define HERO_WIDTH	30
#define HERO_HEIGHT	30

#define BULLET_WIDTH	20
#define BULLET_HEIGHT	10

#define BULLET_SPEED 50

#define PLATFORM_W	135
#define PLATFORM_H	HERO_HEIGHT/2

#define HERO_SPRITES	8

#define BACKGROUND 1

#define GAME_DELAY	20

#define GRAVITY_SPEED 1.7
#define GRAVITY_SPEED_MAX 4

#define OBSTACLE_PLACE	SDLK_p
#define PLATFORM_PLACE	SDLK_l
#define GAME_SPEED_UP	SDLK_KP_PLUS
#define GAME_SPEED_DOWN	SDLK_KP_MINUS
#define BULLET_FIRE		SDLK_k


#include <string>

enum Point_type { neutral = 0, hero = 1, bullet = 2, obstacle = 3 };

enum Obstacle_type { none = -1, box = 0, rock = 1, flower = 2, wall = 3 };

const std::string sprites_files[6] = { //TODO:: put real path to files
	"../fig/xxx.bmp",			//neutral
	"../fig/worms02.bmp",		//hero
	"../fig/bullet01.bmp",		//bullet
	"../fig/worms02.bmp",		//obstacle
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

const int arr_sprite_bullet[4][4] = {
	{17,61,100,39}, 	//bullet left
	{183,60,100,39},	//bullet right
	{0,0,0,0},			//
	{0,0,0,0}			//
};

//rectangle dimensions for obstacle rendering
const int arr_sprite_obstacle[4][4] = {
	{10,113,92,75}, 	//box
	{123,106,82,86},	//rock
	{205,107,141,80},	//flower
	{11,74,616,53}		//wall
};

#endif
