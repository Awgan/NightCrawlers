#ifndef ALL_SDL_H_
#define ALL_SDL_H_

#include <SDL2/SDL.h>
#include <vector>

#include "all.h"
#include "comm_const.h"
#include "point_container.h"
#include "texture_cont.h"


namespace all_SDL {

	bool texture_add ( SDL_Texture ***_tex, SDL_Renderer * _rend, Point * _poi );

	bool rect_position_add ( SDL_Rect ** _rect, Point * _poi );

	bool rect_position_add ( std::vector< SDL_Rect > (& _rect)[ 3 ], Point * _poi );

	bool render( SDL_Renderer * _rend, SDL_Texture * _tex, const SDL_Rect * _rect, Point * _poi );

	bool render_all( SDL_Renderer * _rend, SDL_Texture ** _tex, SDL_Rect * _rect, Point_Container * _poi );

	bool render_all( SDL_Renderer * _rend, Text_Cont<Text_Objt> * _tex, const std::vector< SDL_Rect > (& _rect)[3], Point_Container * _poi );

	bool cursor_change( const std::string * pic, SDL_Cursor * cur );
}

#endif
