#include <iostream>


#include "all.h"

bool allFunction::move_keyboard( Point * _point, SDL_Event * _event) {
		
		switch ( _event->type ) {
			case SDL_KEYDOWN: 
				switch ( _event->key.keysym.sym ) {
					
					case SDLK_UP:
						_point->set_move_y( -5 );
						break;
					
					case SDLK_DOWN:
						_point->set_move_y( 5 );
						break;
					
					case SDLK_LEFT:
						_point->set_move_x( -5 );
						break;
					
					case SDLK_RIGHT:
						_point->set_move_x( 5 );
						break;
					
					default:
						return false;
						break;
				}
				return true;				
		
			case SDL_KEYUP:
				
				switch ( _event->key.keysym.sym ) {
					
					case SDLK_UP:
						_point->set_move_y(0);
						break;
					
					case SDLK_DOWN:
						_point->set_move_y(0);
						break;
					
					case SDLK_LEFT:
						_point->set_move_x(0);
						break;
					
					case SDLK_RIGHT:
						_point->set_move_x(0);
						break;
					
					default:
						return false;
						break;
				}
				return true;
		}
	return false;
	}


//game speed changing
void allFunction::speed_changing ( SDL_Event & r_event, Uint32 & i_time , int & i_delay ) {
			
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


Obstacle_type allFunction::Obstacle_type_select(const int & mx, const int & my) {

	Obstacle_type type;	
	
	std::cout << "mx: " << mx << '\n';
	
	if ( mx >= 0 && mx <= 50 )
		type = box;
	else if ( 51 && mx <= 100 )
		type = rock;
	else if ( mx >= 101 && mx <= 150 )
		type = flower;
	else
		type = none;
	
	return type;
}

void allFunction::fromArrtoRect( const int n, const int arr[][4], SDL_Rect & rect ) {
	
	rect.x = arr[n][0];
	rect.y = arr[n][1];
	rect.w = arr[n][2];
	rect.h = arr[n][3];
}
