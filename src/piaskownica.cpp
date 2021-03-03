#include <stdio.h>
#include <iostream>

#include <SDL2/SDL.h>

#include "comm_const.h"


int main () {

	SDL_Window * win;
	SDL_Window * win2;
	SDL_Renderer * rend;
	SDL_Renderer * rend2;

	SDL_Event event;
	SDL_EventState( SDL_MOUSEMOTION, SDL_IGNORE);  //SDL_IGNORE;

	SDL_Init( SDL_INIT_EVERYTHING );

	win = SDL_CreateWindow("NightCrawlers", 0, 0, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_OPENGL);
	win2 = SDL_CreateWindow("WWW", 300, 100, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_OPENGL);

	rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	rend2 = SDL_CreateRenderer(win2, -1, SDL_RENDERER_ACCELERATED);


	while ( 1 )
	{
		SDL_SetRenderDrawColor( rend, 0xad, 0x3f, 0x05, 0xFF );
		SDL_RenderClear( rend );
		SDL_RenderPresent( rend );
		SDL_RenderClear( rend2 );
		SDL_RenderPresent( rend2 );
		SDL_Delay( 1000 );

		SDL_HideWindow( win );

		SDL_Delay( 1000 );

		SDL_ShowWindow( win );
		SDL_RenderPresent( rend );

		SDL_Delay( 1000 );

		SDL_HideWindow( win );

		SDL_Delay( 1000 );

		SDL_ShowWindow( win );
		SDL_RenderPresent( rend );

		SDL_Delay( 1000 );

		break;

	}

	return 0;
}
