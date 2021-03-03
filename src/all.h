#ifndef ALL_H_
#define ALL_H_

#include <vector>

#include <SDL2/SDL.h>

#include "all_SDL.h"
#include "bullet.h"
#include "comm_const.h"
#include "gunpoint.h"
#include "obstacle_box_win.h"
#include "point.h"
#include "point_container.h"
#include "texture_cont.h"

namespace allFunction {

	bool move_keyboard( Point * _point, SDL_Event * _event);							//handling with move control

	void aim( SDL_Event & event, SDL_Renderer * rend, Point_Container & point_cont, std::vector< SDL_Rect > (& rect_cont)[3], Text_Cont < Text_Objt > & tex_cont, Point * active_hero );

	void speed_changing ( SDL_Event & r_event, Uint32 & i_time , int & i_delay );	//game speed changing

	bool obstacle_place ( SDL_Event & event, SDL_Renderer * rend, Point_Container & point_cont, std::vector< SDL_Rect > (& rect_cont)[3], Text_Cont < Text_Objt > & tex_cont );

	bool platform_place( SDL_Event & event, SDL_Renderer * rend, Point_Container & point_cont, std::vector< SDL_Rect > (& rect_cont)[3], Text_Cont < Text_Objt > & tex_cont );

	Obstacle_type Obstacle_type_select( const int & mx, const int & my);

	void fromArrtoRect( const int n, const int arr[][4], SDL_Rect & rect );			//passing data from array to SDL_Rect struct

	void gravity_move( Point_Container & _pc );										//doing move when object is not standing

	Point create_wall( const SDL_Event * eve );

	void bullet_move( Point_Container & _pc );

	void check_health( Point_Container & _pc, Text_Cont < Text_Objt > & _tc, std::vector< SDL_Rect > (& _rect)[ 3 ] );
}


#endif
