
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
	
//making point container
	Point_Container point_box;

//GPP constain 3 structures for position, graph and property
	GPP gpp_obj;

//reading data from hero configuration file, where are all information about hero		
	read_conf_file( "../conf/start_objects.txt", &gpp_obj );


//creating heroes	
	for ( int i = 0; i < gpp_obj.numb; ++i ) {
		
		Point Maciek ( gpp_obj.array[i].start_coord, gpp_obj.array[i].start_prop, gpp_obj.array[i].start_graph );

		point_box.add( &Maciek );
	}
	
//example of SDL 
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

	//Dimensions of the picture taken from sprite
	SDL_Rect rect;
		rect.x = comm_arr_sprite_dimensions[0][0];
		rect.y = comm_arr_sprite_dimensions[0][1];
		rect.w = comm_arr_sprite_dimensions[0][2];
		rect.h = comm_arr_sprite_dimensions[0][3];

	//dimensions of the displayed picture
	SDL_Rect * rect_pos = new SDL_Rect [gpp_obj.numb];
	
	for ( int i = 0; i < gpp_obj.numb; ++i ) { 
		rect_pos[i].x = point_box.get_point_hero(i)->get_coor_x();
		rect_pos[i].y = point_box.get_point_hero(i)->get_coor_y();
		rect_pos[i].w = point_box.get_point_hero(i)->get_graph_widht();
		rect_pos[i].h = point_box.get_point_hero(i)->get_graph_hight();
		
		SDL_RenderCopy( rend, *(tex+i), &rect, (rect_pos + i) );
	}


	//game speed
	int game_delay = 20;
	
	//time variables for making picture dynamic
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
		
		//choesing sprite for hero eye movment. If time elapses than change picture
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
		
		//updating hero position. Note: it is not move function which get inf from keyboard. It only updates
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
			
			//changing game speed; FASTER
			if ( event.key.timestamp - time_st > 300 && event.key.keysym.sym == SDLK_KP_PLUS )  {
				game_delay += 10;
				time_st = event.key.timestamp;
				//event.key.keysym.sym = SDLK_KP_MULTIPLY;
				printf("%d >> %d\n", game_delay, event.key.timestamp);
			}
			
			else 
			//changing game speed; SLOWER
			if ( event.key.timestamp - time_st > 300 && event.key.keysym.sym == SDLK_KP_MINUS )  {
				if( game_delay > 0 ) {
					game_delay -= 10;
					if ( game_delay < 0 ) game_delay = 0;
				}
				time_st = event.key.timestamp;
				//event.key.keysym.sym = SDLK_KP_MULTIPLY;
				printf("%d >> %d\n", game_delay, event.key.timestamp);
			}
			
			//move function which use keybord entry
			else
				move_control::move_keyboard( point_box.get_point_hero(num_act_hero), &event );				
		}
		
	//selecting a hero; left click
		if ( event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT )		 {
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
					//DEL::rect_pos[num_act_hero].x = ms_x;
					//DEL::rect_pos[num_act_hero].y = ms_y;
					active_hero = point_box.get_point_hero( num_act_hero );
					printf("after:		%p\n", active_hero);
					break;
				}					
			}				
		}
		
	//showing frame with properties; right click
		if ( event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT ) {
			
			//TODO:
			//showing frame with all hero property; helth, position, etc
			
			SDL_Window * win_prop_inf;
			{	
				int ms_x, ms_y;
				ms_x = event.button.x + active_hero->get_graph_widht();
				ms_y = event.button.y + active_hero->get_graph_hight();
						
				win_prop_inf = SDL_CreateWindow( "Property", ms_x, ms_y, 50, 100, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS );
			}
			//1.	conect win_prop_inf with renderer. mabe ther must be second renderer for this.
			//2.	update renderer; SDL_RenderCopy( ... );
			//3. 	show the frame; SDL_RenderPresent( ... );
			//4.	SDL_DestroyWindow( win_prop_inf );
			
		}
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
