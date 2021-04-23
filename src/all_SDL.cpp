#include <iostream>
#include <time.h>

#include <SDL2/SDL.h>

#include "all_SDL.h"


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
			printf("Error: there is no surf object; surf == NULL. Function 'all_SDL::texture_add' terminated\n");
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

/*bool all_SDL::rect_position_add ( SDL_Rect ** _rect, Point * _poi ) {

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
		(*_rect)[mem_cur].h = _poi->get_graph_height();
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
*/

bool all_SDL::rect_position_add ( std::vector< SDL_Rect > (& _rect)[3], Point * _poi ) {

	if ( _poi == nullptr )
	{
		std::cout << "Point object 'nullptr'. Function 'all_SDL::rect_position_add' terminated\n";
		return false;
	}

	//set object place on the boardgame

	SDL_Rect rect_temp;

	rect_temp.x = _poi->get_coor_x();
	rect_temp.y = _poi->get_coor_y();
	rect_temp.w = _poi->get_graph_width();
	rect_temp.h = _poi->get_graph_height();

	switch ( _poi->get_point_type() )
	{
		break;

		case hero:
			_rect[0].push_back( rect_temp );
		break;

		case bullet:
			_rect[1].push_back( rect_temp );
		break;

		case obstacle:
			_rect[2].push_back( rect_temp );
		break;

		default:
			return false;
		break;
	}

	return true;
}

bool all_SDL::rect_position_del ( std::vector< SDL_Rect > (& _rect)[ 3 ], Point * _poi, const int & numb )
{
	//debug("all_SDL::rect_position_del");
	if ( _poi == nullptr )
		return false;

	switch ( _poi->get_point_type() )
	{
		case neutral:
		break;

		case hero:
		{
			_rect[ 0 ].erase( _rect[ 0 ].begin() + numb );
			//debug("all_SDL::rect_position_del ==> hero erased");
		}
		return true;
		break;

		case bullet:
		{
			_rect[ 1 ].erase( _rect[ 1 ].begin() + numb );
			//debug("all_SDL::rect_position_del ==> bullet erased");
		}
		return true;
		break;

		case obstacle:
		{
			_rect[ 2 ].erase( _rect[ 2 ].begin() + numb );
			//debug("all_SDL::rect_position_del ==> obstacle erased");
		}
		return true;
		break;

		default:
		break;

	}
	//debug("all_SDL::rect_position_del ==> nothing erased");
	return false;
}

bool all_SDL::render( SDL_Renderer * _rend, SDL_Texture * _tex, const SDL_Rect * _rect, Point * _poi )
{

	/* change sprite if object is in idle state */
	_poi->changeIdleSprite();

	/* Dimensions of the picture from sprite */
		SDL_Rect rect_sprite;

	if ( _poi->get_type() == Point_type::hero )
	{
	//select sprite
		rect_sprite.x = arr_sprite_dimensions[ (int)_poi->getActualSprite() ][0];
		rect_sprite.y = arr_sprite_dimensions[ (int)_poi->getActualSprite() ][1];
		rect_sprite.w = arr_sprite_dimensions[ (int)_poi->getActualSprite() ][2];
		rect_sprite.h = arr_sprite_dimensions[ (int)_poi->getActualSprite() ][3];

	}
	else
	if ( _poi->get_type() == Point_type::obstacle )
	{
		rect_sprite.x = arr_sprite_obstacle[ (int)_poi->getActualSprite() ][0];
		rect_sprite.y = arr_sprite_obstacle[ (int)_poi->getActualSprite() ][1];
		rect_sprite.w = arr_sprite_obstacle[ (int)_poi->getActualSprite() ][2];
		rect_sprite.h = arr_sprite_obstacle[ (int)_poi->getActualSprite() ][3];

	}
	else
	if ( _poi->get_type() == Point_type::bullet )
	{
		rect_sprite.x = arr_sprite_bullet[ (int)_poi->getActualSprite() ][0];
		rect_sprite.y = arr_sprite_bullet[ (int)_poi->getActualSprite() ][1];
		rect_sprite.w = arr_sprite_bullet[ (int)_poi->getActualSprite() ][2];
		rect_sprite.h = arr_sprite_bullet[ (int)_poi->getActualSprite() ][3];
	}
		SDL_RenderCopy( _rend, _tex, &rect_sprite, _rect );


	return true;
}

bool all_SDL::render_background( SDL_Renderer * _rend )
{
	//Create texture for background

	static SDL_Texture * tex_background = nullptr;

	if ( tex_background == nullptr )
	{
		SDL_Surface * surf;

		surf = SDL_LoadBMP( sprites_files[7].c_str() );

		if ( surf == nullptr )
			return false;

		tex_background = SDL_CreateTextureFromSurface( _rend, surf );
		if ( tex_background == nullptr )
			return false;

		SDL_FreeSurface( surf );
	}

		SDL_RenderCopy( _rend, tex_background, nullptr, nullptr );

	return true;
}

bool all_SDL::render_all( SDL_Renderer * _rend, Text_Cont< Text_Objt >  * _tex, const std::vector< SDL_Rect > (& _rect)[3], Point_Container * _poi )
{
	all_SDL::render_background( _rend );

	for ( int i = 0; i < _poi->get_number_hero(); ++i ) {

		all_SDL::render( _rend, _tex->get_texture_hero( i ), &_rect[0][i], _poi->get_point_hero(i) );

	}

	for ( int i = 0; i < _poi->get_number_bullet(); ++i ) {

		all_SDL::render( _rend, _tex->get_texture_bullet( i ), &_rect[1][i], _poi->get_point_bullet(i) );

	}


	for ( int i = 0; i < _poi->get_number_obstacle(); ++i ) {

		all_SDL::render( _rend, _tex->get_texture_obstacle( i ), &_rect[2][i], _poi->get_point_obstacle(i) );

	}

	return true;
}

bool all_SDL::cursor_change( const std::string * pic, SDL_Cursor * cur )
{

//Change mouse cursor: creat empty surface to use it for cursor
	SDL_Surface * surf_sour = SDL_LoadBMP( (*pic).c_str() );

	if ( surf_sour == nullptr )
		throw(std::string("błąd ładowania BMP") );

	SDL_Surface * surf_dest = SDL_CreateRGBSurface
	(
		surf_sour->flags,
		PLATFORM_W, PLATFORM_H,
		surf_sour->format->BitsPerPixel,
		surf_sour->format->Rmask,
		surf_sour->format->Gmask,
		surf_sour->format->Bmask,
		surf_sour->format->Amask
	);

	SDL_Rect rect_dest = { 0, 0, PLATFORM_W, PLATFORM_H };

	SDL_Rect rect_sour;

	allFunction::fromArrtoRect( 3, arr_sprite_obstacle, rect_sour );

	SDL_BlitScaled( surf_sour, &rect_sour, surf_dest, &rect_dest );

	cur = SDL_CreateColorCursor( surf_dest, 0, 0);

	if ( cur == nullptr )
		throw(std::string("błąd ładowania kursora") );

	SDL_SetCursor( cur );

	SDL_FreeSurface( surf_sour );
	SDL_FreeSurface( surf_dest );

return true;

}

int all_SDL::SDL_EventFilter_gunpointer( void* userdata, SDL_Event* event )
{
	time_t * time_01 = (time_t*)userdata;

	if ( event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_a && difftime( time(nullptr), *time_01 ) < 0.350 )
	{
		std::cout << "GUNPOINT out!\n";
		return 0;
	}
	return 1;
}

int all_SDL::SDL_EventFilter_bullet( void* userdata, SDL_Event* event )
{
	//time_t * time_01 = (time_t*)userdata;

	if ( event == nullptr )
		std::cout << "Event is nullptr!\n";

	std::cout << "Many times I'm here\n";
	std::cout << SDL_GetKeyName( event->key.keysym.sym );

	SDL_Keycode kkk = event->key.keysym.sym;

	if ( kkk == SDLK_k /* && difftime( time(nullptr), *time_01 ) < 10.250 */ )
	{
		std::cout << "BULLET out!!!\n";
		return 0;
	}
	return 1;
}

int all_SDL::SDL_EventFilter_any( void* userdata, SDL_Event* event )
{
	SDL_Keycode * ky;

	if ( userdata != nullptr )
		ky = (SDL_Keycode*)userdata;
	else
		return 1;

	if ( event->key.keysym.sym == *ky )
	{
		std::cout << "KEY out!!!\n";
		return 0;
	}
	return 1;
}
