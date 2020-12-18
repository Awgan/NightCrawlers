#include <iostream>
#include <time.h>

#include <SDL2/SDL.h>

#include "all_SDL.h"
#include "comm_const.h"



bool all_SDL::texture_add ( SDL_Texture *** _tex , SDL_Renderer * _rend, Point * _poi ) {

	
	if ( _poi == nullptr) {
		std::cout << "Point object 'nullptr'. Function 'all_SDL::texture_add' terminated\n";
		return false;
	}
		
	static int mem_all = 0; //possible slots for texture objects;
	static int mem_cur = 0; //current occupied slots for texture objects;

	
// increasing memory for texture objects
	if ( mem_cur >= mem_all ) {
		
		mem_all += 10;

		SDL_Texture ** temp;
		temp = new SDL_Texture* [ mem_all ];

		for ( int i = 0; i < mem_all; i ++) {
			temp[i] = nullptr;
		}
	
	//coping texture from old array to new bigger array
		for ( int i = 0; i < mem_cur; i++ ) {

			temp[i] = (*_tex)[i];			
		}

		delete [] *_tex;
		*_tex = temp;
		
		if ( *_tex == nullptr ) {
			std::cout << "SDL_Texture* array is nullptr. Function 'all_SDL::texture_add' terminated\n";
			return false;
		}
		
	}
	
	SDL_Surface * surf;
			
	surf = SDL_LoadBMP( _poi->get_graph_sprite().c_str() );
	
	if ( surf == nullptr ) {
			printf("Error: there is no surf object; surf == NULL. . Function 'all_SDL::texture_add' terminated\n");
			return false;
		}
		
//changing texture background	
	if ( BACKGROUND != 1 )
		SDL_SetColorKey( surf, SDL_TRUE, SDL_MapRGB( surf->format, 255, 0, 255 ) );
	

//adding texture to 'texture array'	
	SDL_Texture * ttemp = SDL_CreateTextureFromSurface( _rend, surf );
	
	*((*_tex) + mem_cur)  = ttemp;

	/*for ( int i = 0; i <= mem_cur; i++ ) {
		
		std::cout << "_tex + " << i << " ==> " << *( (*_tex) + i ) << '\n';
	}*/
	
	mem_cur++;
	SDL_FreeSurface( surf );
	
return true;
}

bool all_SDL::rect_position_add ( SDL_Rect ** _rect, Point * _poi ) {
	
	if ( _poi == nullptr) {
		std::cout << "Point object 'nullptr'. Function 'all_SDL::rect_position_add' terminated\n";
		return false;
	}
	
	static int mem_all = 0;
	static int mem_cur = 0;

	if ( mem_cur >= mem_all ) {

		mem_all += 10;
	
		SDL_Rect * temp = new SDL_Rect [ mem_all ];
	
		for ( int i = 0; i < mem_cur; ++i ) {
		
			temp[i] = (*_rect)[i];
		}
	
		delete [] *_rect;
		
		*_rect =  temp;
	
	}

	
	//set object place on the boardgame
		(*_rect)[mem_cur].x = _poi->get_coor_x();
		(*_rect)[mem_cur].y = _poi->get_coor_y();
		(*_rect)[mem_cur].w = _poi->get_graph_width();
		(*_rect)[mem_cur].h = _poi->get_graph_hight();
		//TODO: check if there is free non-occupied place for next object
		//		There shouldn't be situation when two or more objects occupied this same area

	if ( _poi->get_type() == Point_type::hero ) {	
	//setting start direction of the object; choosing suitable sprite
		if ( _poi->get_direction() == Coordinate::Direction::right ) {
			
			_poi->setActualSprite( 4 );
		}
		else { //or point_box.get_point_hero(i)->get_direction() == Coordinate::Direction::left ) {

			_poi->setActualSprite( 0 );
		}		
	}
	else {
		
	}
	
	mem_cur++;
	
return true;
}

bool all_SDL::render( SDL_Renderer * _rend, SDL_Texture * _tex, SDL_Rect * _rect, Point * _poi ) {

	static time_t timer 	= 0;
	static time_t time_eye  = 0;
		
	time(&timer);

	if ( time_eye == 0 )
		time(&time_eye);
	

	//int actSprite = (int)_poi->getActualSprite();

	//choosing sprite for hero eye movement. If time elapses than change next picture
	/*if ( (timer - time_eye) >= 1.5) { 
			
		if (actSprite >= 0 && actSprite < 4) {
			
			++actSprite;
			
			if ( actSprite > 3 )
				actSprite = 0;
				
			_poi->setActualSprite( actSprite );
		}
		else if ( actSprite >= 4 && actSprite < 8 ) {
			
			++actSprite;
			
			if ( actSprite > 7 )
				actSprite = 4;
				
			_poi->setActualSprite( actSprite );
		}				
	}*/		
	
	
	//Dimensions of the picture from sprite
		SDL_Rect rect_sprite;	
	
	if ( _poi->get_type() == Point_type::hero ) {
	//select sprite
		rect_sprite.x = comm_arr_sprite_dimensions[ (int)_poi->getActualSprite() ][0];
		rect_sprite.y = comm_arr_sprite_dimensions[ (int)_poi->getActualSprite() ][1];
		rect_sprite.w = comm_arr_sprite_dimensions[ (int)_poi->getActualSprite() ][2];
		rect_sprite.h = comm_arr_sprite_dimensions[ (int)_poi->getActualSprite() ][3];
		
	}
	else {
		rect_sprite.x = comm_arr_sprite_obstacle[ (int)_poi->getActualSprite() ][0];
		rect_sprite.y = comm_arr_sprite_obstacle[ (int)_poi->getActualSprite() ][1];
		rect_sprite.w = comm_arr_sprite_obstacle[ (int)_poi->getActualSprite() ][2];
		rect_sprite.h = comm_arr_sprite_obstacle[ (int)_poi->getActualSprite() ][3];
		
	}
		SDL_RenderCopy( _rend, _tex, &rect_sprite, _rect );

	if ( (timer - time_eye) >= 2) { 
			time(&time_eye);
		}

	return true;
}

bool all_SDL::render_all( SDL_Renderer * _rend, SDL_Texture ** _tex, SDL_Rect * _rect, Point_Container * _poi ) {
	
	//rendering the frame
		for ( int i = 0; i < _poi->get_number_hero(); ++i ) {
		
			all_SDL::render( _rend, _tex[i], &_rect[i], _poi->get_point_hero(i) );
		}
		
		for ( int i = 0; i < _poi->get_number_obstacle(); ++i ) {
			
			render( _rend, _tex[ _poi->get_number_hero() + i ], &_rect[ _poi->get_number_hero() + i ], _poi->get_point_obstacle(i) );

//TODO:: separate tex array between hero, obstacle, and bullet
		}
	
	return true;
}




