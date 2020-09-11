#ifndef MOVE_FUNCTION_H_
#define MOVE_FUNCTION_H_

#include <SDL2/SDL.h>

#include "point.h"

namespace move_control {
	
	bool move_keyboard( Point * _point, SDL_Event * _event) {
		
		switch ( _event->type ) {
			case SDL_KEYDOWN: 
				switch ( _event->key.keysym.sym ) {
					
					case SDLK_UP:
						_point->set_move_y(-5);
						break;
					
					case SDLK_DOWN:
						_point->set_move_y(5);
						break;
					
					case SDLK_LEFT:
						_point->set_move_x(-5);
						break;
					
					case SDLK_RIGHT:
						_point->set_move_x(5);
						break;
					
					default:
						return false;
						break;
				}
				return true;				
		
			case SDL_KEYUP:
				
				switch ( _event->key.keysym.sym ) {
					
					case SDLK_UP:
						_point->set_move_y(0);
						break;
					
					case SDLK_DOWN:
						_point->set_move_y(0);
						break;
					
					case SDLK_LEFT:
						_point->set_move_x(0);
						break;
					
					case SDLK_RIGHT:
						_point->set_move_x(0);
						break;
					
					default:
						return false;
						break;
				}
				return true;
		}
	return false;
	}
}
#endif
