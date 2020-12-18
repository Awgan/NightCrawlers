#ifndef WIN_GENERAL_H_
#define WIN_GENERAL_H_

#include <string>
#include <SDL2/SDL.h>


class WinGenSDL {
	
	private:
		
		int width;
		int hight;
		
		std::string fBaGr;		//background
		
	protected:
		
		SDL_Window * win;
		SDL_Texture * tex;
		SDL_Renderer * rend;
		SDL_Surface * surf;	
		
		SDL_Texture * getTex() 		{return this->tex;	}		
		SDL_Renderer * getRend() 	{return this->rend;	}		
		SDL_Window * getWin() 		{return this->win;	}		
		SDL_Surface * getSurf() 	{return this->surf;	}
		
		const int & get_win_width() {return this->width; }
		const int & get_win_hight() {return this->hight; }
		
	public:
		
		WinGenSDL();
		~WinGenSDL();
		
		void setWidthAndHight( const int & _w, const int & _h );
		
		void initWin( const int & _x, const int & _y );
		
		void initTex( const char * background = "brak" );
		
		virtual bool show() = 0;
		
		void hide();
		
		WinGenSDL & operator=(WinGenSDL & wgs);
		
		virtual bool test();
	
};

#endif
