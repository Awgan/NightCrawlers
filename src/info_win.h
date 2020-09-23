#ifndef INFO_WIN_H_
#define INFO_WIN_H_

#include <cstdlib>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "point.h"
#include "point_container.h"


class Info_win {
	
	public:

	
	private:
		SDL_Event * event;
		Point_Container * pointCont;
		
		Point * actPoint;
		
		SDL_Window * win;
		SDL_Renderer * rend;
		SDL_Surface * surf;
		SDL_Texture * tex;
		
		TTF_Font * font;
		
		int font_size;
		int lines;
		
		int win_posX;
		int win_posY;
		int win_widht;
		int win_hight;
		
	public:
		
		Info_win();
		~Info_win();
		Info_win( SDL_Event * _event, Point_Container * _pCont );
		
		void show();
		void hide();
		bool isPointed();
};


#endif
