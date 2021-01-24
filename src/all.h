#ifndef ALL_H_
#define ALL_H_

#include <SDL2/SDL.h>

#include "comm_const.h"
#include "point.h"

namespace allFunction {

	bool move_keyboard( Point * _point, SDL_Event * _event);							//handling with move control

	void speed_changing ( SDL_Event & r_event, Uint32 & i_time , int & i_delay );	//game speed changing

	Obstacle_type Obstacle_type_select( const int & mx, const int & my);

	void fromArrtoRect( const int n, const int arr[][4], SDL_Rect & rect );			//passing data from array to SDL_Rect struct

	void gravity_move( Point_Container & _pc );										//doing move when object is not standing

	Point create_wall( const SDL_Event * eve );

	void bullet_move( Point_Container & _pc );

	void check_health( Point_Container & _pc );
}


#endif
