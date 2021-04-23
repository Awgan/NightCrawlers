
#include <iomanip>
#include <iostream>
#include <string.h>
#include <time.h>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


#include "all.h"
#include "all_SDL.h"
#include "bullet.h"
#include "comm_const.h"
#include "cursor_picture.h"
#include "graph_prop.h"
#include "gunpoint.h"
#include "info_win.h"
#include "obstacle_box_win.h"
#include "point.h"
#include "point_container.h"
#include "position.h"
#include "property.h"
#include "read_file.h"
#include "texture_cont.h"


int main( int argc, char * argv[] )
{

	SDL_Window * win;
	SDL_Renderer * rend;
	SDL_Event event;
	SDL_EventState( SDL_MOUSEMOTION, SDL_IGNORE);  //SDL_IGNORE;

	SDL_Init( SDL_INIT_EVERYTHING );

	win = SDL_CreateWindow("NightCrawlers", 0, 0, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS);

	rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);


//making points container
	Point_Container point_container;


//GPP constain 3 structures for position, graph and property
	GPP gpp_obj;


//reading data from hero configuration file, where are all information about hero
	read_conf_file( "../conf/start_objects.txt", &gpp_obj );


//creating heroes
	for ( int i = 0; i < gpp_obj.numb; ++i ) {

		/*
		Point Maciek ( gpp_obj.array[i].start_coord, gpp_obj.array[i].start_prop, gpp_obj.array[i].start_graph );
		point_container.add( &Maciek );
		*/

		/* using movment ctor */
		point_container.add( (Point(gpp_obj.array[i].start_coord, gpp_obj.array[i].start_prop, gpp_obj.array[i].start_graph)) );


		//printf("direction : %d\n", point_container.get_point_hero( i )->get_direction());
	}


//loading TEXTURE, RECT_POSITION and doing RENDERING


	Text_Cont< Text_Objt > tex_container( rend );

	std::vector< SDL_Rect > rect_container[ 3 ];


	for ( int i = 0; i < point_container.get_number_all(); ++i ) {


		tex_container.add( point_container.get_point_hero( i ) );


		all_SDL::rect_position_add( rect_container, point_container.get_point_hero(i) );


	}

		all_SDL::render_all( rend, &tex_container, rect_container, &point_container );


//game speed
	int game_delay = GAME_DELAY;

//time variables for making picture dynamic
	Uint32 time_st 	= 0;

//pointer for getting actual choosen object
	Point * active_hero = NULL;
	active_hero = point_container.get_active_hero();


//Information windows of object property; right mouse click
	Info_win infWin( &event, &point_container );


//Default platforms
allFunction::platform_place_file( "test.txt", rend, point_container, rect_container, tex_container );

//***********
//MAIN LOOP//
//***********

	while( event.type != SDL_QUIT && event.key.keysym.sym != SDLK_q )
	{

		//TODO:: flush event; there is issue with KEYUP and arrows; code constatly execute move function
		if ( !SDL_PollEvent(&event) )
			event.type = 0;

		if ( event.type == SDL_QUIT )
			break;


		/* Check gravity */
		allFunction::gravity_move( point_container );


		/* Update obstacle position */
		for ( int i = 0; i < point_container.get_number_obstacle(); ++i )
		{

			if ( point_container.get_point_obstacle( i )->move() ) {

				rect_container[2][i].x = point_container.get_point_obstacle( i )->get_coor_x();
				rect_container[2][i].y = point_container.get_point_obstacle( i )->get_coor_y();

			}
		}

		/* Update bullet postion */
		allFunction::bullet_move( point_container );

		for ( int i = 0; i < point_container.get_number_bullet(); ++i )
		{

			if ( point_container.get_point_bullet( i )->move( point_container.get_point_bullet( i )->getAngle() ) ) {

				rect_container[1][i].x = point_container.get_point_bullet( i )->get_coor_x();
				rect_container[1][i].y = point_container.get_point_bullet( i )->get_coor_y();

			}
		}

		/* Check health after bullets move */
		allFunction::check_health( point_container, tex_container, rect_container );


		/* Update hero position */
		for ( int i = 0; i < point_container.get_number_hero(); ++i )
		{

			if ( point_container.get_point_hero( i )->move() )
			{
				rect_container[0][i].x = point_container.get_point_hero( i )->get_coor_x();
				rect_container[0][i].y = point_container.get_point_hero( i )->get_coor_y();
			}
		}


	//std::cout << "Rendering START\n";
	//Main Rendering START
		SDL_RenderClear( rend );

		all_SDL::render_all( rend, &tex_container, rect_container, &point_container );

		SDL_RenderPresent(rend);

		SDL_Delay( game_delay );
	//Main Rendering STOP


		/* Handle events */
		switch (event.type)
		{

			case SDL_KEYDOWN:
			case SDL_KEYUP:
				/* move 	UP DOWN LEFT RIGHT */
				allFunction::move_keyboard( active_hero, &event );

				/* Speed up - down game */
				allFunction::speed_changing ( event, time_st, game_delay );

				/* Place obstacle: box, rock, flower */
				allFunction::obstacle_place( event, rend, point_container, rect_container, tex_container );

				/* Place platforms */
				allFunction::platform_place( event, rend, point_container, rect_container, tex_container );

				/* Shwo GunPoint and Fire */
				allFunction::aim( win, event, rend, point_container, rect_container, tex_container, active_hero );

				allFunction::dump( "test.txt", &point_container, &event );

			break;


			case SDL_MOUSEBUTTONDOWN :
			{
				/* Select hero; left click */
				if ( event.button.button == SDL_BUTTON_LEFT )
					active_hero = point_container.select_hero( event );

				/* Show window with properties; right click */
				else
				if ( event.button.button == SDL_BUTTON_RIGHT )
				{

					if ( infWin.isPointed() ) {

						infWin.show();

						/* Show window with properties: Wait for realesing the right mouse butto; game pause */
						while ( event.type != SDL_MOUSEBUTTONUP )
						{

							SDL_PollEvent( &event );
						}

						infWin.hide();
					}
				}
			}
			break;

			default :
			break;
		}

	}
//end main loop

	//delete [] tex;
	//delete [] rect_pos;


//Clear all
	for ( int i = 0; i < gpp_obj.numb; ++i ) {

		point_container.del( point_container.get_point_hero(i) );
	}

	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(rend);
	SDL_Quit();

	return 0;
}



