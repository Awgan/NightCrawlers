#ifndef OBSTACLE_WIN_H_
#define OBSTACLE_WIN_H_

#include <SDL2/SDL.h>

#include "win_general.h"

class ObstacleWin : public WinGenSDL {
	
	private:
		SDL_Rect spriteRect{};
		//TODO::const static char * fileSprite;
	protected:
	
	public:
		ObstacleWin();
		~ObstacleWin();
		
		void init( const char * _sprite, SDL_Rect * _spriteRect, SDL_Rect * _winRect );
		
		virtual bool show();
		
		ObstacleWin & operator=( ObstacleWin & ob1 );

		virtual bool test();
};

#endif


