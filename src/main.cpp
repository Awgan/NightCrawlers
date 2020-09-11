
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

//making Maciek
	Coordinate start_coord { 200, 300, 0, Coordinate::Direction::right };
	Stru_property start_prop { Point_type::hero, 1, 1, 10, 15, 23, 50, 65 };
	Stru_graph_prop start_graph { comm_arr_sprite_files[1].c_str(), 1, NULL, 50, 50 };
	
	Point Maciek( start_coord, start_prop, start_graph );
	Maciek.set_offset( 50 );
//END

	point_box.add( &Maciek );

	/**/ //example of SDL 
		SDL_Surface * surf;
		surf = SDL_LoadBMP( Maciek.get_graph_sprite().c_str() );
		SDL_SetColorKey( surf, SDL_TRUE, SDL_MapRGB( surf->format, 255, 0, 255 ) );

		SDL_Texture * tex;
		tex = SDL_CreateTextureFromSurface( rend, surf );
		SDL_FreeSurface( surf );
		
		//Dimensions of the sprite graph
		SDL_Rect rect;
		rect.x = comm_arr_sprite_dimensions[0][0];
		rect.y = comm_arr_sprite_dimensions[0][1];
		rect.w = comm_arr_sprite_dimensions[0][2];
		rect.h = comm_arr_sprite_dimensions[0][3];
		
		//dimensions of the displayed graph
		SDL_Rect rect_pos;
		rect_pos.x = Maciek.get_coor_x();
		rect_pos.y = Maciek.get_coor_y();
		rect_pos.w = Maciek.get_graph_widht();
		rect_pos.h = Maciek.get_graph_hight();

		SDL_RenderCopy( rend, tex, &rect, &rect_pos );
	/**/
	
	//slow down the game
	int game_delay = 20;
	
	time_t timer = 0;
	time_t time_eye = 0;
	time(&time_eye);
	
	Uint32 time_st = 0;
	
	int t = 0;
		
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
				if ( t > 3 ) t = 0;
					
				time(&time_eye);
			}
			
			
			//getting coordinates for the move
			Maciek.move();
			rect_pos.x = Maciek.get_coor_x();
			rect_pos.y = Maciek.get_coor_y();
			
			
			//rendering the frame
			SDL_RenderCopy( rend, tex, &rect, &rect_pos);
			
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
					move_control::move_keyboard( &Maciek, &event );				
			}
		
		
		//point_box.status_test();
	}
	//end main loop
	
	
	point_box.del( &Maciek );
	
	delete [] arr_objects ;
	
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(rend);
	SDL_Quit();
	
	
	
	return 0;
}
