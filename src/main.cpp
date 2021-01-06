
#include <string.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>

#include "all.h"
#include "all_SDL.h"
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
	
	win = SDL_CreateWindow("NightCrawlers", 0, 0, WIN_WIDTH, WIN_HIGHT, SDL_WINDOW_OPENGL);
	
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
	//SDL_Texture **tex = nullptr;
	//SDL_Rect * rect_pos = nullptr;

	Text_Cont< Text_Objt > tex_container( rend );

	std::vector< SDL_Rect > rect_container[ 3 ];


	for ( int i = 0; i < point_container.get_number_all(); ++i ) {

		//TODO:: delete texture_add() when Text_Cont object takes all work
		//all_SDL::texture_add( &tex, rend, point_container.get_point_hero(i) );
		tex_container.add( point_container.get_point_hero( i ) );

		//all_SDL::rect_position_add( &rect_pos, point_container.get_point_hero(i) );
		all_SDL::rect_position_add( rect_container, point_container.get_point_hero(i) );

		//all_SDL::render( rend, tex_container.get_texture_hero( i ), rect_container, point_container.get_point_hero(i) );
		//OUT::all_SDL::render( rend, tex[i], &rect_pos[i], point_container.get_point_hero(i) );
	}

		all_SDL::render_all( rend, &tex_container, rect_container, &point_container );


//game speed
	int game_delay = 10;
	
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
		
	while( event.type != SDL_QUIT ) {
		
		//TODO:: flush event; there is issue with KEYUP and arrows; code constatly execute move function
		SDL_PollEvent(&event);
			
		if ( event.type == SDL_QUIT )
			break;
		
		
	//Main Rendering START
		SDL_RenderClear(rend);

	//updating hero position. Note: it is not move function which get inf from keyboard. It only updates
		//active_hero->move();
		
//std::cout << "updating position before: " << point_container.get_number_hero() << "\n";
	//updating hero position
	for ( int i = 0; i < point_container.get_number_hero(); ++i ) {

		point_container.get_point_hero( i )->move();

	}
//std::cout << "updating position AFTER: "<< point_container.get_number_hero() << "\n\n";
	//updating obstacle position
	for ( int i = 0; i < point_container.get_number_obstacle(); ++i ) {
		
		if ( point_container.get_point_obstacle( i )->move() ) {

			//rect_pos[ point_container.get_number_hero() + i ].x = point_container.get_point_obstacle( i )->get_coor_x();
			//rect_pos[ point_container.get_number_hero() + i ].y = point_container.get_point_obstacle( i )->get_coor_y();
			rect_container[2][i].x = point_container.get_point_obstacle( i )->get_coor_x();
			rect_container[2][i].y = point_container.get_point_obstacle( i )->get_coor_y();
		
		}
	}

	rect_container[0][point_container.get_active_hero_numb()].x = active_hero->get_coor_x();
	rect_container[0][point_container.get_active_hero_numb()].y = active_hero->get_coor_y();

	//TODO:: update collieded obstacle position

		//all_SDL::render_all( rend, tex, rect_pos, &point_container );
		all_SDL::render_all( rend, &tex_container, rect_container, &point_container );

		SDL_RenderPresent(rend);
		SDL_Delay( game_delay );
	//Main Rendering STOP

		switch (event.type) {
				
			case SDL_KEYDOWN:
			case SDL_KEYUP:
			{
					//move entry	UP DOWN LEFT RIGHT
				SDL_Keycode & key = event.key.keysym.sym;
				if ( key == SDLK_UP || key == SDLK_DOWN || key == SDLK_LEFT || key == SDLK_RIGHT ) {
					//TODO:: flush event; SDL remamber last event; when it is KEYUP and one of the arrows, code comes here constatly
					std::cout << "moving... \n";
					allFunction::move_keyboard( active_hero, &event );
				}
					
					//game speed up / speed down
				else
					if ( key == GAME_SPEED_UP || key == GAME_SPEED_DOWN ) { 
						
						allFunction::speed_changing ( event, time_st, game_delay );
					}		
				
					//obstacle inventory box
				else 
					if ( key == OBSTACLE_PLACE && event.type == SDL_KEYDOWN ) {				
					
							//window for choosing obstacle to put on the map
						ObstacleBoxWin<SDL_Rect, ObstacleWin> obw( &event, 3, comm_arr_sprite_files[1].c_str() );
						obw.setVisibility( true );  
						obw.show();
						
						Obstacle_type selection = none;
						
							//select obstacle from obstacle window
						while( event.key.keysym.sym != SDLK_q && event.type != SDL_MOUSEBUTTONDOWN ) {
							
							SDL_PollEvent( &event );
							
							if ( event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
							
								selection = allFunction::Obstacle_type_select(event.button.x, event.button.y);
								std::cout << "sellection\n";
							}
						}
						
							//clear Obstacle window
						obw.hide();
						obw.setVisibility(false);
						
							//show game board without obstacle box
						SDL_RenderClear( rend );
							//all_SDL::render_all( rend, tex, rect_pos, &point_container );
							//all_SDL::render_all( rend, &tex_container, rect_pos, &point_container );
							all_SDL::render_all( rend, &tex_container, rect_container, &point_container );
						SDL_RenderPresent( rend );
						
						SDL_PollEvent( &event );
						
						
							//changing mouse cursor
						if ( selection == none ) {
							
							std::cout << "none selection\n";
						}
						else {
							
							SDL_EventState( SDL_MOUSEMOTION, SDL_IGNORE);
							
							SDL_Surface * surf_sour = SDL_LoadBMP( comm_arr_sprite_files[1].c_str() );
							
								//creating empty surface to use it for cursor
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
							
							switch(selection) { //TODO:: function <fromArrtoRect can be change so it take ENUM of obstacle
								case box:
								allFunction::fromArrtoRect( 0, comm_arr_sprite_obstacle, rect_sour );
								break;
								
								case rock:
								allFunction::fromArrtoRect( 1, comm_arr_sprite_obstacle, rect_sour );
								break;
								
								case flower:
								allFunction::fromArrtoRect( 2, comm_arr_sprite_obstacle, rect_sour);
								break;
								
								default:
								break;
							}	
							
							SDL_BlitScaled( surf_sour, &rect_sour, surf_dest, &rect_dest );
							
							SDL_Cursor * curs = SDL_CreateColorCursor( surf_dest, 0, 0);
							SDL_SetCursor( curs );
							
							while( event.key.keysym.sym != SDLK_q && event.type != SDL_MOUSEBUTTONDOWN) {

								SDL_PollEvent( &event );
							}
							
							
							/*
							 * 01 add object to point_container
							 * 02 add coordination
							 * 
							 * */
							
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
								selected_prop.i_speed = 2;
								selected_prop.i_move_points = 3;
								selected_prop.i_strenght = 50;
								selected_prop.i_fire_accuracy = 0;
							
							Stru_graph_prop selected_graph;
								selected_graph.init_arr( Point_type::obstacle );
								selected_graph.s_sprite = comm_arr_sprite_files[1];
								selected_graph.i_num_sprite = 1;
								selected_graph.arr_sprite_dim[0][0] = comm_arr_sprite_obstacle[1][0];
								selected_graph.arr_sprite_dim[0][1] = comm_arr_sprite_obstacle[1][1];
								selected_graph.arr_sprite_dim[0][2] = comm_arr_sprite_obstacle[1][2];
								selected_graph.arr_sprite_dim[0][3] = comm_arr_sprite_obstacle[1][3];
								selected_graph.actual_sprite = (int)selection;
								selected_graph.i_width = 50;
								selected_graph.i_hight = 50;
								
							Point selected_obstacle ( selected_coor, selected_prop, selected_graph );
							
							point_container.add( &selected_obstacle );
							
							
							//all_SDL::texture_add( &tex, rend, &selected_obstacle );
							tex_container.add( &selected_obstacle );
							
							//all_SDL::rect_position_add( &rect_pos, &selected_obstacle );
							all_SDL::rect_position_add( rect_container, &selected_obstacle );
							
							SDL_EventState( SDL_MOUSEMOTION, SDL_IGNORE);
							
							SDL_FreeCursor ( curs );
							
						
						}//end if
					}
				else
					if ( key == BULLET_FIRE ) {
						
						// TODO:: bullet firing
						
					}
			}
			break;
			
				
			case SDL_MOUSEBUTTONDOWN :
			{
						//object selecting function
				if ( event.button.button == SDL_BUTTON_LEFT )
					active_hero = point_container.select_hero( event );
				
						//showing window with properties; right click
				if ( event.button.button == SDL_BUTTON_RIGHT ) {
				
					if ( infWin.isPointed() ) {
						
						infWin.show();
						
							//wait for realesing the right mouse butto; game pause
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
std::cout << "MAIN LOOP end\n";
	}
//end main loop
	
	//delete [] tex;
	//delete [] rect_pos;


	for ( int i = 0; i < gpp_obj.numb; ++i ) {

		point_container.del( point_container.get_point_hero(i) );
	}
	
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(rend);
	SDL_Quit();
	
	return 0;
}



