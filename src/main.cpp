
#include <string.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "comm_const.h"
#include "graph_prop.h"
#include "info_win.h"
#include "move_function.h"
#include "point.h"
#include "point_container.h"
#include "position.h"
#include "property.h"
#include "read_file.h"
	

void speed_changing ( SDL_Event & r_event, Uint32 & i_time , int & i_delay );



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
		rect_pos[i].w = point_box.get_point_hero(i)->get_graph_width();
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
	
	
	active_hero = point_box.get_active_hero();
	
	Info_win infWin( &event, &point_box );
	
//***********
//MAIN LOOP//
//***********
		
	while( event.type != SDL_QUIT ) {
		
		SDL_PollEvent(&event);
		
		time(&timer);
			
		if ( event.type == SDL_QUIT )
			break;
			
		SDL_RenderClear(rend);
		
		//choosing sprite for hero eye movment. If time elapses than change picture
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
		rect_pos[point_box.get_active_hero_numb()].x = active_hero->get_coor_x();
		rect_pos[point_box.get_active_hero_numb()].y = active_hero->get_coor_y();
		
		point_box.collision_hero_with_hero();	
		
		//rendering the frame
		for ( int i = 0; i < gpp_obj.numb; ++i ) { 
		
			SDL_RenderCopy( rend, *(tex+i), &rect, (rect_pos + i) );
		}
		
		SDL_RenderPresent(rend);
		SDL_Delay( game_delay );
	
		switch (event.type) {
			
			case SDL_KEYDOWN:
			case SDL_KEYUP:
			//move function which use keybord entry
			move_control::move_keyboard( active_hero, &event );
			
			speed_changing ( event, time_st, game_delay );
			break;
			
			case SDL_MOUSEBUTTONDOWN :
						//object selecting function
				
				active_hero = point_box.select_hero( event );
				
						//showing window with properties; right click
				if ( event.button.button == SDL_BUTTON_RIGHT ) {
				
					if ( infWin.isPointed() ) {
						infWin.show();
				
						while ( event.type != SDL_MOUSEBUTTONUP ) {
							SDL_PollEvent( &event );
						}				
				
						infWin.hide();
					}
				}
					
			break;
			
			default :
			break;
			
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


//game speed changing
void speed_changing ( SDL_Event & r_event, Uint32 & i_time , int & i_delay ) {
			
		if ( r_event.type ==  SDL_KEYDOWN || r_event.type == SDL_KEYUP ) {
			
			//changing game speed; FASTER
			if ( r_event.key.timestamp - i_time > 300 && r_event.key.keysym.sym == SDLK_KP_MINUS)  {
				if ( i_delay < 100 )
					i_delay += 10;
				i_time = r_event.key.timestamp;
				//event.key.keysym.sym = SDLK_KP_MULTIPLY;
				printf("%d >> %d\n", i_delay, r_event.key.timestamp);
			}
			
			else 
			//changing game speed; SLOWER
			if ( r_event.key.timestamp - i_time > 300 && r_event.key.keysym.sym == SDLK_KP_PLUS )  {
				if( i_delay > 0 ) {
					i_delay -= 10;
					if ( i_delay < 0 ) i_delay = 0;
				}
				i_time = r_event.key.timestamp;
				//event.key.keysym.sym = SDLK_KP_MULTIPLY;
				printf("%d >> %d\n", i_delay, r_event.key.timestamp);
			}							
		}		
	}
//END : game speed changing
