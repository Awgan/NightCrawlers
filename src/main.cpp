
#include <string.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>

#include "all.h"
#include "all_SDL.h"
#include "bullet.h"
#include "comm_const.h"
#include "cursor_picture.h"
#include "graph_prop.h"
#include "info_win.h"
#include "obstacle_box_win.h"
#include "point.h"
#include "point_container.h"
#include "position.h"
#include "property.h"
#include "read_file.h"
#include "texture_cont.h"


int main( int argc, char * argv[] ) {

	SDL_Window * win;
	SDL_Renderer * rend;
	SDL_Event event;
	SDL_EventState( SDL_MOUSEMOTION, SDL_IGNORE);  //SDL_IGNORE;

	SDL_Init( SDL_INIT_EVERYTHING );

	win = SDL_CreateWindow("NightCrawlers", 0, 0, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_OPENGL);

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


//***********
//MAIN LOOP//
//***********

	while( event.type != SDL_QUIT && event.key.keysym.sym != SDLK_q ) {

		//TODO:: flush event; there is issue with KEYUP and arrows; code constatly execute move function
		if ( !SDL_PollEvent(&event) )
			event.type = 0;

		if ( event.type == SDL_QUIT )
			break;


		/* Check gravity */
		allFunction::gravity_move( point_container );


		/* Update obstacle position */
		for ( int i = 0; i < point_container.get_number_obstacle(); ++i ) {

			if ( point_container.get_point_obstacle( i )->move() ) {

				rect_container[2][i].x = point_container.get_point_obstacle( i )->get_coor_x();
				rect_container[2][i].y = point_container.get_point_obstacle( i )->get_coor_y();
			}
		}

		/* Update bullet postion */
		allFunction::bullet_move( point_container );

		for ( int i = 0; i < point_container.get_number_bullet(); ++i ) {

			if ( point_container.get_point_bullet( i )->move() ) {

				rect_container[1][i].x = point_container.get_point_bullet( i )->get_coor_x();
				rect_container[1][i].y = point_container.get_point_bullet( i )->get_coor_y();

			}
		}

		/* check healt after bullets move */
		allFunction::check_health( point_container );


		/* Update hero position */
		for ( int i = 0; i < point_container.get_number_hero(); ++i ) {

			if ( point_container.get_point_hero( i )->move() )
			{
				rect_container[0][i].x = point_container.get_point_hero( i )->get_coor_x();
				rect_container[0][i].y = point_container.get_point_hero( i )->get_coor_y();
			}
		}


	//Main Rendering START
		SDL_RenderClear(rend);

		all_SDL::render_all( rend, &tex_container, rect_container, &point_container );

		SDL_RenderPresent(rend);

		SDL_Delay( game_delay );
	//Main Rendering STOP


		/* Handle events */
		switch (event.type) {

			case SDL_KEYDOWN:
			case SDL_KEYUP:
			{
					//move 		UP DOWN LEFT RIGHT
				SDL_Keycode & key = event.key.keysym.sym;



				if ( (key == SDLK_UP || key == SDLK_DOWN || key == SDLK_LEFT || key == SDLK_RIGHT) /*&& active_hero->isStanding()*/ ) {

					//TODO:: flush event; SDL remamber last event; when it is KEYUP and one of the arrows, code comes here constatly
					//TODO:: BUG: when moving key is pressed and you change selected hero then new hero move normaly but old one is
					//		moving without stop until edge of the display; And sprite is not updated

					//std::cout << "moving... \n";

					allFunction::move_keyboard( active_hero, &event );
				}



					//Speed up / down game
				else
					if ( key == GAME_SPEED_UP || key == GAME_SPEED_DOWN ) {

						allFunction::speed_changing ( event, time_st, game_delay );
					}

				else
					if ( key == OBSTACLE_PLACE && event.type == SDL_KEYDOWN ) {

					//Show window for choosing obstacle
						ObstacleBoxWin<SDL_Rect, ObstacleWin> obw( &event, 3, sprites_files[1].c_str() );
						obw.setVisibility( true );
						obw.show();

						Obstacle_type selection = none;



					//Select obstacle from obstacle window
						while( event.key.keysym.sym != SDLK_q && event.type != SDL_MOUSEBUTTONDOWN ) {

							SDL_PollEvent( &event );

							if ( event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {

								selection = allFunction::Obstacle_type_select(event.button.x, event.button.y);
								std::cout << "sellection\n";
							}
						}



					//Hide obstacle window
						obw.hide();
						obw.setVisibility(false);



					//Show game board without obstacle box
						SDL_RenderClear( rend );
							all_SDL::render_all( rend, &tex_container, rect_container, &point_container );
						SDL_RenderPresent( rend );

						SDL_PollEvent( &event );



					//Change mouse cursor
						if ( selection == none ) {

							std::cout << "none selection\n";
						}
						else {

							//OUT -> SDL_EventState( SDL_MOUSEMOTION, SDL_IGNORE);
						//Change mouse cursor: creat empty surface to use it for cursor
							SDL_Surface * surf_sour = SDL_LoadBMP( sprites_files[1].c_str() );

							SDL_Surface * surf_dest = SDL_CreateRGBSurface (
								surf_sour->flags,
								30, 30,
								surf_sour->format->BitsPerPixel,
								surf_sour->format->Rmask,
								surf_sour->format->Gmask,
								surf_sour->format->Bmask,
								surf_sour->format->Amask );

							SDL_Rect rect_dest = {0, 0, 30, 30};

							SDL_Rect rect_sour;

					//Change mouse cursor: select new picture for cursor
							switch(selection) { //TODO:: function <fromArrtoRect can be change so it take ENUM of obstacle
								case box:
								allFunction::fromArrtoRect( 0, arr_sprite_obstacle, rect_sour );
								break;

								case rock:
								allFunction::fromArrtoRect( 1, arr_sprite_obstacle, rect_sour );
								break;

								case flower:
								allFunction::fromArrtoRect( 2, arr_sprite_obstacle, rect_sour);
								break;

								default:
								break;
							}

							SDL_BlitScaled( surf_sour, &rect_sour, surf_dest, &rect_dest );

							SDL_Cursor * curs = SDL_CreateColorCursor( surf_dest, 0, 0);
							SDL_SetCursor( curs );

							while ( event.key.keysym.sym != SDLK_q )
							{
					//Change mouse cursor: flush mouse button events; one mouse click generates many mouse button events
								while ( event.type == SDL_MOUSEBUTTONDOWN )
								{
									SDL_PollEvent( &event );
									std::cout << "Mouse flush \n";
								}

					//Change mouse cursor: wait for mouse button down
								while( event.key.keysym.sym != SDLK_q && event.type != SDL_MOUSEBUTTONDOWN ) {

									SDL_PollEvent( &event );

								}

					//Change mouse cursor: break loop when 'q' key pressed or 'right' mouse button pressed
								if ( event.key.keysym.sym == SDLK_q || event.button.button == SDL_BUTTON_RIGHT )
									break;

					//Change mouse cursor: create new object at board game
								Coordinate selected_coor;
									selected_coor.x = event.button.x;
									selected_coor.y = event.button.y;
									selected_coor.z = 0;
									selected_coor.dir = Coordinate::Direction::up;

								Stru_property selected_prop;
									selected_prop.type = Point_type::obstacle;
									selected_prop.b_mobile = true;
									selected_prop.b_visible = true;
									selected_prop.i_health = 10;
									selected_prop.i_speed = 3;
									selected_prop.i_move_points = 5;
									selected_prop.i_self_move_distance = 0;
									selected_prop.i_strenght = 50;
									selected_prop.i_fire_accuracy = 0;

								Stru_graph_prop selected_graph;
									selected_graph.init_arr( Point_type::obstacle );
									selected_graph.s_sprite = sprites_files[1];
									selected_graph.i_num_sprite = 1;
									selected_graph.arr_sprite_dim[0][0] = arr_sprite_obstacle[1][0];
									selected_graph.arr_sprite_dim[0][1] = arr_sprite_obstacle[1][1];
									selected_graph.arr_sprite_dim[0][2] = arr_sprite_obstacle[1][2];
									selected_graph.arr_sprite_dim[0][3] = arr_sprite_obstacle[1][3];
									selected_graph.actual_sprite = (int)selection;
									selected_graph.i_width = HERO_WIDTH;
									selected_graph.i_height = HERO_HEIGHT;

								Point selected_obstacle ( selected_coor, selected_prop, selected_graph );

								if ( point_container.add( &selected_obstacle ) == true )
								{
									//all_SDL::texture_add( &tex, rend, &selected_obstacle );
									tex_container.add( &selected_obstacle );

									//all_SDL::rect_position_add( &rect_pos, &selected_obstacle );
									all_SDL::rect_position_add( rect_container, &selected_obstacle );
								}

								SDL_RenderClear(rend);

								all_SDL::render_all( rend, &tex_container, rect_container, &point_container );

								SDL_RenderPresent(rend);

								//OUT -> SDL_EventState( SDL_MOUSEMOTION, SDL_IGNORE);
							}

							SDL_FreeCursor ( curs );


						}//end if
					}
				else
					if ( key == BULLET_FIRE ) {

						// TODO:: bullet firing

						Bullet bullet( active_hero );

						if ( point_container.add( &bullet ) == true )
						{
							tex_container.add( &bullet );

							all_SDL::rect_position_add( rect_container, &bullet );
						}


					}
				else
					if ( key == PLATFORM_PLACE and event.type == SDL_KEYDOWN ) {

					//Place platform for walking

						SDL_Cursor * curs = nullptr;

						try
						{
							all_SDL::cursor_change( &sprites_files[ 5 ], curs );
						}
						catch(std::string ssttrr)
						{ std::cout << ssttrr << std::endl; }

						//SDL_SetCursor( curs );

						while( event.key.keysym.sym != SDLK_q && event.type != SDL_MOUSEBUTTONDOWN ) {

							SDL_PollEvent( &event );

						}

						Point wall_temp = allFunction::create_wall( & event );

						if ( wall_temp == true )
						{
						point_container.add( &wall_temp );

						//all_SDL::texture_add( &tex, rend, &selected_obstacle );
						tex_container.add( &wall_temp );

						//all_SDL::rect_position_add( &rect_pos, &selected_obstacle );
						all_SDL::rect_position_add( rect_container, &wall_temp );

						}

						SDL_RenderClear(rend);

						all_SDL::render_all( rend, &tex_container, rect_container, &point_container );

						SDL_RenderPresent(rend);





						SDL_FreeCursor( curs );
						SDL_SetCursor( SDL_GetDefaultCursor() );
					}
			}
			break;


			case SDL_MOUSEBUTTONDOWN :
			{
			//Select object; left click
				if ( event.button.button == SDL_BUTTON_LEFT )
					active_hero = point_container.select_hero( event );

			//Show window with properties; right click
				else if ( event.button.button == SDL_BUTTON_RIGHT ) {

					if ( infWin.isPointed() ) {

						infWin.show();

			//Show window with properties: Wait for realesing the right mouse butto; game pause
						while ( event.type != SDL_MOUSEBUTTONUP ) {

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



