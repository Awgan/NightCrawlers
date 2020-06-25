#ifndef HERO_H_
#define HERO_H_

#include <string>

#include <SDL2/SDL.h>

#include "comm_const.h"
#include "point.h"

class Hero : public Point {
	
	public:
	
			
	private:
	
		
	protected:
	
	public:
		Hero( SDL_Renderer * _rend, Coordinate & _coor );
		~Hero() {};
		
		void show();
		
	
};


#endif
