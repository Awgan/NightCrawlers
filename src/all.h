#ifndef ALL_H_
#define ALL_H_

#include <SDL2/SDL.h>

#include "comm_const.h"
#include "point.h"

namespace allFunction {
	
	bool 			move_keyboard( Point * _point, SDL_Event * _event);
	
	void 			speed_changing ( SDL_Event & r_event, Uint32 & i_time , int & i_delay );
	
	Obstacle_type 	Obstacle_type_select( const int & mx, const int & my);
	
	void 			fromArrtoRect( const int n, const int arr[][4], SDL_Rect & rect );
}


#endif
