#ifndef CURSOR_PICTURE_H_
#define CURSOR_PICTURE_H_

#include <string>

#include <SDL2/SDL.h>

#include "comm_const.h"
#include "win_general.h"

class CursorPicture : public WinGenSDL {
	
	private:
		std::string bck;
		
		Obstacle_type type;
	
	public:
		CursorPicture( const int & w = 15, const int & h = 15, const Obstacle_type & typ = none, const char * bckg = "brak" );
		~CursorPicture() {};
		
		virtual bool show() {return true;};
		virtual bool show( const int & x = 0, const int & y = 0 );
		
		
};

#endif
