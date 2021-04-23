#include <fstream>
#include <iostream>
#include <stdio.h>

#include <SDL2/SDL.h>

#include "comm_const.h"


int main ()
{

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


	std::fstream file_in;
	file_in.open( "test.txt", std::fstream::in );

	std::cout << "file open? : " << file_in.is_open() << '\n';

	std::string lines, all;
	int size = 0;

	while ( std::getline( file_in, lines ) )
	{
		all += lines + '\n';
		++size;
	}

	unsigned int pos_s = 0;
	unsigned int pos_e = all.find_first_of( ",\n", 0 );
	int arr_pos[ size ] [ 3 ];
	int count = 0;

	while ( pos_e < all.size() )
	{

		char temp_char[ 4 ];
		all.copy( temp_char, pos_e - pos_s, pos_s );
		arr_pos[ count / 3 ] [ count % 3 ] = std::atoi( temp_char );

		pos_s = pos_e + 1;
		pos_e = all.find_first_of( ",\n", pos_s );

		++count;
	}

	for ( int i = 0; i < size; ++i )
	{
		for ( int j = 0; j < 3; ++j )
		{
			std::cout << arr_pos[i][j] << " ";
		}

		std::cout << '\n';
	}

return 0;
}
