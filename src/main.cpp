
#include <time.h>

#include <SDL2/SDL.h>

#include "comm_const.h"
#include "graph_prop.h"
#include "move_function.h"
#include "point.h"
#include "point_container.h"
#include "position.h"
#include "property.h"
#include "read_file.h"

int main( int argc, char * argv[] ) {
	
	SDL_Window * win;
	SDL_Renderer * rend;
	SDL_Event event;
	SDL_EventState( SDL_MOUSEMOTION, SDL_IGNORE);
		
	SDL_Init( SDL_INIT_EVERYTHING );
	win = SDL_CreateWindow("NightCrawlers", 0, 0, WIN_WIDTH, WIN_HIGHT, SDL_WINDOW_OPENGL);
	rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	
//makin point container
	Point_Container point_box;
//END

	GPP gpp_obj;
		
	read_conf_file( "../conf/start_objects.txt", &gpp_obj );
/*
//making Maciek
	Coordinate start_coord { 200, 300, 0, Coordinate::Direction::right };
	Stru_property start_prop { Point_type::hero, 1, 1, 10, 15, 23, 50, 65 };
	Stru_graph_prop start_graph { comm_arr_sprite_files[1].c_str(), 1, NULL, 50, 50 };
	
	Point Maciek( start_coord, start_prop, start_graph );
	Maciek.set_offset( 50 );
//END

	point_box.add( &Maciek );
*/	

	Point Maciek;
	
	for ( int i = 0; i < gpp_obj.numb; ++i ) {
		
		Maciek = Point ( gpp_obj.array[i].start_coord, gpp_obj.array[i].start_prop, gpp_obj.array[i].start_graph );

		point_box.add( &Maciek );
		
		Maciek.print_status();
	}
	
	/**/ //example of SDL 
		SDL_Surface * surf;
		SDL_Texture *(*tex);
		tex = new SDL_Texture* [ gpp_obj.numb ];
		
		for ( int i = 0; i < gpp_obj.numb; ++i ) { 
			surf = SDL_LoadBMP( point_box.get_point_hero(i)->get_graph_sprite().c_str() );
			
			SDL_SetColorKey( surf, SDL_TRUE, SDL_MapRGB( surf->format, 255, 0, 255 ) );
		
			//SDL_Texture * tex;
			*(tex+i) = SDL_CreateTextureFromSurface( rend, surf );
			
			SDL_FreeSurface( surf );
		}

		//Dimensions of the sprite graph
		SDL_Rect rect;
		rect.x = comm_arr_sprite_dimensions[0][0];
		rect.y = comm_arr_sprite_dimensions[0][1];
		rect.w = comm_arr_sprite_dimensions[0][2];
		rect.h = comm_arr_sprite_dimensions[0][3];

		//dimensions of the displayed graph
		SDL_Rect * rect_pos = new SDL_Rect [gpp_obj.numb];
		
		for ( int i = 0; i < gpp_obj.numb; ++i ) { 
			rect_pos[i].x = point_box.get_point_hero(i)->get_coor_x();
			rect_pos[i].y = point_box.get_point_hero(i)->get_coor_y();
			rect_pos[i].w = point_box.get_point_hero(i)->get_graph_widht();
			rect_pos[i].h = point_box.get_point_hero(i)->get_graph_hight();
			
			SDL_RenderCopy( rend, *(tex+i), &rect, (rect_pos + i) );
		}
	/**/

	//slow down the game
	int game_delay = 20;
	
	time_t timer 	= 0;
	time_t time_eye = 0;
	time(&time_eye);
	
	Uint32 time_st 	= 0;
	
	int t = 0;
	
	Point * active_hero = NULL;
	int num_act_hero = 3;
	active_hero = point_box.get_point_hero( num_act_hero );
		
	while( event.type != SDL_QUIT ) {
		SDL_PollEvent(&event);
		
		time(&timer);
		
			SDL_PollEvent(&event);
			
			if ( event.type == SDL_QUIT )
				break;
				
			SDL_RenderClear(rend);
			
			//choosing sprite of hero eye movment
			if ( (timer - time_eye) >= 2.0 ) { 
				rect.x = comm_arr_sprite_dimensions[t%4][0];
				rect.y = comm_arr_sprite_dimensions[t%4][1];
				rect.w = comm_arr_sprite_dimensions[t%4][2];
				rect.h = comm_arr_sprite_dimensions[t%4][3];
				
				t++;
				
					if ( t > 3 )
						t = 0;
					
				time(&time_eye);
			}
			
			//TODO:: do for all heroes
			//getting coordinates for the move; ONLY for hero number "0"
			//printf("move:		%p\n", active_hero);
			active_hero->move();
			rect_pos[num_act_hero].x = active_hero->get_coor_x();
			rect_pos[num_act_hero].y = active_hero->get_coor_y();
			
			
			
			
			
			
			
			
			//rendering the frame
			for ( int i = 0; i < gpp_obj.numb; ++i ) { 
			
				SDL_RenderCopy( rend, *(tex+i), &rect, (rect_pos + i) );
			}
			
			SDL_RenderPresent(rend);
			SDL_Delay( game_delay );
			
			
			//moving
			if ( event.type ==  SDL_KEYDOWN || event.type == SDL_KEYUP ) {
				
				if ( event.key.timestamp - time_st > 300 && event.key.keysym.sym == SDLK_KP_PLUS )  {
					game_delay += 10;
					time_st = event.key.timestamp;
					//event.key.keysym.sym = SDLK_KP_MULTIPLY;
					printf("%d >> %d\n", game_delay, event.key.timestamp);
				}
				
				else 
				
				if ( event.key.timestamp - time_st > 300 && event.key.keysym.sym == SDLK_KP_MINUS )  {
					if( game_delay > 0 ) {
						game_delay -= 10;
						if ( game_delay < 0 ) game_delay = 0;
					}
					time_st = event.key.timestamp;
					//event.key.keysym.sym = SDLK_KP_MULTIPLY;
					printf("%d >> %d\n", game_delay, event.key.timestamp);
				}
				
				else
					move_control::move_keyboard( point_box.get_point_hero(num_act_hero), &event );				
			}
			
			if ( event.type == SDL_MOUSEBUTTONDOWN )		 {
				komun("\nSDL_MOUSEBUTTONDOWN\n");
				int ms_x, ms_y;
				ms_x = event.button.x;
				ms_y = event.button.y;
				
				//1. check if cursor is over hero
				//2. change acvtive_hero
				//3. end
				for ( int i = 0; i < gpp_obj.numb; ++i ) { 
				printf( "%p\n", point_box.get_point_hero(i) );
				}
				
				for ( int i = 0; i < gpp_obj.numb; ++i ) { 
					if ( 	ms_x >= rect_pos[i].x && ms_x <= rect_pos[i].x + rect_pos[i].w &&
							ms_y >= rect_pos[i].y && ms_y <= rect_pos[i].y + rect_pos[i].h 		) {
						
						printf("before:		%p\n", active_hero);
						num_act_hero = i;
						//rect_pos[num_act_hero].x = ms_x;
						//rect_pos[num_act_hero].y = ms_y;
						active_hero = point_box.get_point_hero( num_act_hero );
						printf("after:		%p\n", active_hero);
						break;
					}					
				}				
			}
		
		//point_box.status_test();
	}
	//end main loop
	
	delete [] tex;
	delete [] rect_pos;
	
	
	for ( int i = 0; i < gpp_obj.numb; ++i ) {
		
		point_box.del( point_box.get_point_hero(i) );
	}	
	
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(rend);
	SDL_Quit();
	
	return 0;
}
