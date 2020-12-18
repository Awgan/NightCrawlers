#include <iostream>

#include "cursor_picture.h"

CursorPicture::CursorPicture( const int & w, const int & h, const Obstacle_type & typ, const char * bckg ) {
	
	setWidthAndHight( w, h );
		
	type = typ;
	
	bck = bckg;
}

bool CursorPicture::show( const int & x, const int & y) {
	
	initWin( x, y );
	
	initTex( bck.c_str() );	

	if ( tex == nullptr )
		return false;
	
	SDL_Rect boxRect;
	switch ( type ) {
		case box:
			boxRect.x = comm_arr_sprite_obstacle[0][0];
			boxRect.y = comm_arr_sprite_obstacle[0][1];
			boxRect.w = comm_arr_sprite_obstacle[0][2];
			boxRect.h = comm_arr_sprite_obstacle[0][3];			
		break;
		case rock:
			boxRect.x = comm_arr_sprite_obstacle[1][0];
			boxRect.y = comm_arr_sprite_obstacle[1][1];
			boxRect.w = comm_arr_sprite_obstacle[1][2];
			boxRect.h = comm_arr_sprite_obstacle[1][3];	
		break;
		case flower:
			boxRect.x = comm_arr_sprite_obstacle[2][0];
			boxRect.y = comm_arr_sprite_obstacle[2][1];
			boxRect.w = comm_arr_sprite_obstacle[2][2];
			boxRect.h = comm_arr_sprite_obstacle[2][3];	
		break;
		default:
		break;		
	}
	
	if ( SDL_RenderCopy( rend, tex, &boxRect, nullptr ) != 0 )
		return false;	
	
	if ( rend == nullptr )
		return false;
	
	SDL_RenderPresent( rend );
	
	std::cout << "CurPic show()\n";
	
	return true;
}

