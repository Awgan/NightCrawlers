#include <iostream>


#include "all.h"

/* Hero Move */
bool allFunction::move_keyboard( Point * _point, SDL_Event * _event)
{
std::cout << "allFunction:: Move Keyboard\n";
//TODO:: flush event; SDL remamber last event; when it is KEYUP and one of the arrows, code comes here constatly
					//TODO:: BUG: when moving key is pressed and you change selected hero then new hero move normaly but old one is
					//		moving without stop until edge of the display; And sprite is not updated

					////std::cout << "moving... \n";

	SDL_Keycode & key = _event->key.keysym.sym;

	if ( (key == SDLK_SPACE || key == SDLK_UP || key == SDLK_DOWN || key == SDLK_LEFT || key == SDLK_RIGHT) && _point->is_mobile() )
	{
		switch ( _event->type )
		{
			case SDL_KEYDOWN:
				switch ( _event->key.keysym.sym )
				{
					case SDLK_SPACE:
					case SDLK_UP:
						if ( _point->isStanding() )
							_point->set_move_y( -15 );
						break;

					case SDLK_DOWN:
						if ( _point->isStanding() )
							_point->set_move_y( 5 );
						break;

					case SDLK_LEFT:
						if ( _point->isStanding() )		//Object is moving slover when it is not standing
							_point->set_move_x( -5 );
						else
							_point->set_move_x( -2 );
						break;

					case SDLK_RIGHT:
						if ( _point->isStanding() )
							_point->set_move_x( 5 );
						else
							_point->set_move_x( 2 );
						break;

					default:
						return false;
						break;
				}
				return true;
				break;

			case SDL_KEYUP:

				switch ( _event->key.keysym.sym )
				{

					case SDLK_SPACE:
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
				break;
		}
	}
	return false;
}

void allFunction::aim( SDL_Window * win, SDL_Event & event, SDL_Renderer * rend, Point_Container & point_cont, std::vector< SDL_Rect > (& rect_cont)[3], Text_Cont < Text_Objt > & tex_cont, Point * active_hero )
{
	std::cout << "allFunction:: Aim\n";
	SDL_Keycode & key = event.key.keysym.sym;

	if( active_hero->isStanding() && key == SDLK_a && event.type == SDL_KEYDOWN )
	{
		Gunpoint gpp;

		Coordinate::Direction dir = active_hero->get_direction();

		gpp.setcenterposition
		(
			active_hero->get_coor_x() + HERO_WIDTH/2 - 10,
			active_hero->get_coor_y() + HERO_HEIGHT/2 - 10
		);

		gpp.setcenterangle( dir == Coordinate::Direction::left ? 180 : 0  );

		gpp.updateposition();

		/* Flush event queue */
		while( event.key.keysym.sym == SDLK_a )
		{
			SDL_PollEvent( &event );
		}

		while( key != SDLK_w )
		{
			SDL_RenderClear(rend);

			all_SDL::render_all( rend, &tex_cont, rect_cont, &point_cont );

			SDL_RenderPresent(rend);

			SDL_PollEvent( &event );


			/* Show gunpoint window */ //DELETE

			gpp.show();

			SDL_SetWindowInputFocus( win );

			if ( event.key.keysym.sym == BULLET_FIRE )
			{
				/*time_t timer;
				time( &timer );*/
				// TODO:: bullet firing

				Bullet bullet( active_hero, gpp.getcenterangle() );

				if ( point_cont.add( &bullet ) == true )
				{

					tex_cont.add( &bullet );

					all_SDL::rect_position_add( rect_cont, &bullet );

				}

				gpp.hide();

				break;
			}



			/* Move gunpointer */
			if ( event.type == SDL_KEYDOWN )
			{
				switch (key)
				{
					case SDLK_UP:
					{
						gpp.changecenterangle( dir == Coordinate::Direction::left ? 5 : -5 );
						gpp.updateposition();

						SDL_FlushEvent( SDL_KEYDOWN );
					}
					break;

					case SDLK_DOWN:
					{
						gpp.changecenterangle( dir == Coordinate::Direction::left ? -5 : 5 );
						gpp.updateposition();

						SDL_FlushEvent( SDL_KEYDOWN );
					}
					break;

					case SDLK_LEFT:
						//active_hero->inc_coor_x( -5 );
					break;

					case SDLK_RIGHT:
						//active_hero->inc_coor_x( 5 );
					break;

					default:
					break;
				}
			}
			else if ( event.type == SDL_WINDOWEVENT_MOVED )
			{
				/* Change the window storred possition */
			}


			/* Change hero direction if gunpoint change direction too */
			std::cout << "Actual sprite: " << active_hero->getActualSprite() << '\n';

			if ( dir == Coordinate::Direction::left && ((gpp.getcenterangle() > 270 && gpp.getcenterangle() < 359) || (gpp.getcenterangle() < 90 && gpp.getcenterangle() > 0)) )
			{
				active_hero->set_direction( CoorDir::right );

				active_hero->setActualSprite(4);

				dir = active_hero->get_direction();

			}
			else if ( dir == Coordinate::Direction::right && (gpp.getcenterangle() < 270 && gpp.getcenterangle() > 90) )
			{
				active_hero->set_direction( CoorDir::left );

				active_hero->setActualSprite(0);

				dir = active_hero->get_direction();

			}

			std::cout << "Actual sprite AFTER: " << active_hero->getActualSprite() << '\n';

			/* Filter events for multipressed key */
			time_t timer;
			time( &timer );

			SDL_FilterEvents( all_SDL::SDL_EventFilter_gunpointer, &timer );

		}

		/* Hide the window */
		gpp.hide();
		SDL_FlushEvents( SDL_QUIT, SDL_LASTEVENT );
	}


}


/* Game Speed changing */
void allFunction::speed_changing ( SDL_Event & r_event, Uint32 & i_time , int & i_delay )
{
	std::cout << "allFunction:: Speed Change\n";
	SDL_Keycode & key = r_event.key.keysym.sym;

	if ( key == GAME_SPEED_UP || key == GAME_SPEED_DOWN )
	{

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



/* Put Obstacle*/
bool allFunction::obstacle_place( SDL_Event & event, SDL_Renderer * rend, Point_Container & point_cont, std::vector< SDL_Rect > (& rect_cont)[3], Text_Cont < Text_Objt > & tex_cont )
{
	std::cout << "allFunction:: Obstacle Place\n";
	SDL_Keycode & key = event.key.keysym.sym;

	if ( key == OBSTACLE_PLACE && event.type == SDL_KEYDOWN )
	{

		/* Show obstacle window */
		ObstacleBoxWin<SDL_Rect, ObstacleWin> obw( &event, 3, sprites_files[1].c_str() );
		obw.setVisibility( true );
		obw.show();

		Obstacle_type selection = none;


		/* Select obstacle */
		while( event.key.keysym.sym != SDLK_q && event.type != SDL_MOUSEBUTTONDOWN )
		{
			SDL_PollEvent( &event );

			if ( event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT )
			{
				selection = allFunction::Obstacle_type_select( event.button.x, event.button.y );
				//std::cout << "sellection\n";
			}
		}


		/* Hide obstacle window */
		obw.hide();
		obw.setVisibility(false);



		/* Show game board without obstacle box */
		SDL_RenderClear( rend );
			all_SDL::render_all( rend, &tex_cont, rect_cont, &point_cont );
		SDL_RenderPresent( rend );

		SDL_PollEvent( &event );



		/* Change mouse cursor */
		if ( selection == none )
		{
			//std::cout << "none selection\n";
			return false;
		}
		else
		{

		/* Change mouse cursor: creat empty surface to use it for cursor */
			SDL_Surface * surf_sour = SDL_LoadBMP( sprites_files[1].c_str() );

			SDL_Surface * surf_dest = SDL_CreateRGBSurface
			(
				surf_sour->flags,
				30, 30,
				surf_sour->format->BitsPerPixel,
				surf_sour->format->Rmask,
				surf_sour->format->Gmask,
				surf_sour->format->Bmask,
				surf_sour->format->Amask
			);

			SDL_Rect rect_dest = {0, 0, 30, 30};

			SDL_Rect rect_sour;

			/* Change mouse cursor: select new picture for cursor */
			switch(selection) //TODO:: function <fromArrtoRect can be change to take ENUM of obstacle
			{
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
				/* Change mouse cursor: flush mouse button events; one mouse click generated many mouse button events */
				while ( event.type == SDL_MOUSEBUTTONDOWN )
				{
					SDL_PollEvent( &event );
					//std::cout << "Mouse flush \n";
				}

				/* Change mouse cursor: wait for mouse button down */
				while( event.key.keysym.sym != SDLK_q && event.type != SDL_MOUSEBUTTONDOWN )
				{
					SDL_PollEvent( &event );
				}

				/* Change mouse cursor: break loop when 'q' key pressed or 'right' mouse button pressed */
				if ( event.key.keysym.sym == SDLK_q || event.button.button == SDL_BUTTON_RIGHT )
					break;

				/* Change mouse cursor: create new object at board game */
				Coordinate selected_coor;
					selected_coor.x = event.button.x;
					selected_coor.y = event.button.y;
					selected_coor.z = 0;
					selected_coor.dir = Coordinate::Direction::up;

				Stru_property selected_prop;
					selected_prop.type = Point_type::obstacle;
					selected_prop.b_mobile = true;
					selected_prop.b_visible = true;
					selected_prop.i_health = 25;
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

				if ( point_cont.add( &selected_obstacle ) == true )
				{
					//all_SDL::texture_add( &tex, rend, &selected_obstacle );
					tex_cont.add( &selected_obstacle );

					//all_SDL::rect_position_add( &rect_pos, &selected_obstacle );
					all_SDL::rect_position_add( rect_cont, &selected_obstacle );
				}

				SDL_RenderClear(rend);

				all_SDL::render_all( rend, &tex_cont, rect_cont, &point_cont );

				SDL_RenderPresent(rend);
			}

			SDL_FreeCursor ( curs );
		}
	}
	else
		return false;

	return true;
}

bool allFunction::platform_place( SDL_Event & event, SDL_Renderer * rend, Point_Container & point_cont, std::vector< SDL_Rect > (& rect_cont)[3], Text_Cont < Text_Objt > & tex_cont )
{
	std::cout << "allFunction:: Platform Place\n";
	SDL_Keycode & key = event.key.keysym.sym;

	if ( key == PLATFORM_PLACE and event.type == SDL_KEYDOWN )
	{

		/* Place platform for walking */

		SDL_Cursor * curs = nullptr;

		try
		{
			all_SDL::cursor_change( &sprites_files[ 5 ], curs );
		}
		catch(std::string ssttrr)
		{ std::cout << ssttrr << std::endl; }

		//SDL_SetCursor( curs );

		while( key != SDLK_q && event.button.button != SDL_BUTTON_RIGHT )
		{
			/* mouse event flush */
			while ( event.type == SDL_MOUSEBUTTONDOWN )
			{
				SDL_PollEvent( &event );
			}

			/* wait for event */
			while ( event.key.keysym.sym != SDLK_q && event.type != SDL_MOUSEBUTTONDOWN )
			{
				SDL_PollEvent( &event );
			}

			/* break if 'q' key or right mouse butto */
			if ( event.key.keysym.sym == SDLK_q || event.button.button == SDL_BUTTON_RIGHT )
			{
				SDL_FreeCursor( curs );
				SDL_SetCursor( SDL_GetDefaultCursor() );
				std::cout << "#allFunction::platform_place :: quit without placing\n";
				return false;
			}

			Point wall_temp = allFunction::create_wall( & event );

			if ( wall_temp == true && point_cont.add( &wall_temp ) )
			{
				//all_SDL::texture_add( &tex, rend, &selected_obstacle );
				tex_cont.add( &wall_temp );

				//all_SDL::rect_position_add( &rect_pos, &selected_obstacle );
				all_SDL::rect_position_add( rect_cont, &wall_temp );
			}

			SDL_RenderClear( rend );

			all_SDL::render_all( rend, &tex_cont, rect_cont, &point_cont );

			SDL_RenderPresent( rend );

		}

		SDL_FreeCursor( curs );

		SDL_SetCursor( SDL_GetDefaultCursor() );
	}
	else
		return false;

	return true;
}

bool allFunction::platform_place_file( const char * _file, SDL_Renderer * rend, Point_Container & point_cont, std::vector< SDL_Rect > (& rect_cont)[3], Text_Cont < Text_Objt > & tex_cont )
{

	/* Open file with coordinates for platforms */
	std::fstream file_in;
	file_in.open( "test.txt", std::fstream::in );

	if ( file_in.is_open() != 1 )
		return false;


	/* Get all data to one variable */
	std::string lines, all;
	int size = 0;

	while ( std::getline( file_in, lines ) )
	{
		all += lines + '\n';
		++size;
	}

	if ( size == 0 )
		return false;


	/* Change string to int and save in array */
	unsigned int pos_s = 0;
	unsigned int pos_e = all.find_first_of( ",\n", 0 );
	int arr_pos[ size ] [ 3 ];
	int count = 0;

	while ( pos_e < all.size() )
	{

		char temp_char[ 4 ];
		all.copy( temp_char, pos_e - pos_s, pos_s );
		arr_pos[ count / 3 ] [ count % 3 ] = std::atoi( temp_char );

		pos_s = pos_e + 1;
		pos_e = all.find_first_of( ",\n", pos_s );

		++count;
	}


	/* Create platforms */
	for ( int i = 0; i < size; ++i )
	{
		Coordinate selected_coor;
			selected_coor.x = arr_pos[i][0];
			selected_coor.y = arr_pos[i][1];
			selected_coor.z = arr_pos[i][2];
			selected_coor.dir = Coordinate::Direction::up;

		Stru_property selected_prop;
			selected_prop.type = Point_type::obstacle;
			selected_prop.b_mobile = false;
			selected_prop.b_visible = true;
			selected_prop.i_health = 100;
			selected_prop.i_speed = 0;
			selected_prop.i_move_points = 0;
			selected_prop.i_self_move_distance = 0;
			selected_prop.i_strenght = 100;
			selected_prop.i_fire_accuracy = 0;

		Stru_graph_prop selected_graph;
			selected_graph.init_arr( Point_type::obstacle );
			selected_graph.s_sprite = sprites_files[5];
			selected_graph.i_num_sprite = 1;
			selected_graph.arr_sprite_dim[0][0] = arr_sprite_obstacle[3][0];
			selected_graph.arr_sprite_dim[0][1] = arr_sprite_obstacle[3][1];
			selected_graph.arr_sprite_dim[0][2] = arr_sprite_obstacle[3][2];
			selected_graph.arr_sprite_dim[0][3] = arr_sprite_obstacle[3][3];
			selected_graph.actual_sprite = 3;
			selected_graph.i_width = PLATFORM_W;
			selected_graph.i_height = PLATFORM_H;


		Point wall_temp( selected_coor, selected_prop, selected_graph );

		if ( wall_temp == true && point_cont.add( &wall_temp ) )
		{
			//all_SDL::texture_add( &tex, rend, &selected_obstacle );
			tex_cont.add( &wall_temp );

			//all_SDL::rect_position_add( &rect_pos, &selected_obstacle );
			all_SDL::rect_position_add( rect_cont, &wall_temp );
		}
	}


	/* Render all */
	SDL_RenderClear( rend );

	all_SDL::render_all( rend, &tex_cont, rect_cont, &point_cont );

	SDL_RenderPresent( rend );


return true;

}


Obstacle_type allFunction::Obstacle_type_select(const int & mx, const int & my)
{

//TODO :: it is only quick fix

	Obstacle_type type;

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



void allFunction::gravity_move( Point_Container & _pc )
{
	std::cout << "allFunction:: Gravity Move\n";
	Point * object = nullptr;



	for ( int i = 0; i < _pc.get_number_hero(); i++ )
	{
		object = _pc.get_point_hero( i );

		if ( object->isStanding() == false )
		{
			//std :: cout << "void allFunction::gravity_move => gravity works for hero: " << &object << '\n';
			object->set_move_y( object->get_move_y() < GRAVITY_SPEED_MAX ? object->get_move_y() + GRAVITY_SPEED : GRAVITY_SPEED_MAX );
		}
	}



	for ( int i = 0; i < _pc.get_number_obstacle(); i++ )
	{
		object = _pc.get_point_obstacle( i );

		if ( object->isStanding() == false && object->is_mobile())
		{
			//std :: cout << "void allFunction::gravity_move => gravity works for obstacle: " << &object << '\n';
			object->set_move_y( object->get_move_y() < GRAVITY_SPEED_MAX ? object->get_move_y() + GRAVITY_SPEED : GRAVITY_SPEED_MAX );
		}
	}
}



Point allFunction::create_wall( const SDL_Event * eve )
{
	Coordinate selected_coor;
		selected_coor.x = eve->button.x;
		selected_coor.y = eve->button.y;
		selected_coor.z = 0;
		selected_coor.dir = Coordinate::Direction::up;

	Stru_property selected_prop;
		selected_prop.type = Point_type::obstacle;
		selected_prop.b_mobile = false;
		selected_prop.b_visible = true;
		selected_prop.i_health = 100;
		selected_prop.i_speed = 0;
		selected_prop.i_move_points = 0;
		selected_prop.i_self_move_distance = 0;
		selected_prop.i_strenght = 100;
		selected_prop.i_fire_accuracy = 0;

	Stru_graph_prop selected_graph;
		selected_graph.init_arr( Point_type::obstacle );
		selected_graph.s_sprite = sprites_files[5];
		selected_graph.i_num_sprite = 1;
		selected_graph.arr_sprite_dim[0][0] = arr_sprite_obstacle[3][0];
		selected_graph.arr_sprite_dim[0][1] = arr_sprite_obstacle[3][1];
		selected_graph.arr_sprite_dim[0][2] = arr_sprite_obstacle[3][2];
		selected_graph.arr_sprite_dim[0][3] = arr_sprite_obstacle[3][3];
		selected_graph.actual_sprite = 3;
		selected_graph.i_width = PLATFORM_W;
		selected_graph.i_height = PLATFORM_H;

	return Point( selected_coor, selected_prop, selected_graph );
}

void allFunction::bullet_move( Point_Container & _pc )
{
	std::cout << "allFunction:: Bullet Move\n";
	std::cout << "\tBullet Number: " << _pc.get_number_bullet() << '\n';
	Point * object = nullptr;

	for ( int i = 0; i < _pc.get_number_bullet(); ++i )
	{
		object = _pc.get_point_bullet( i );

		if ( object != nullptr && object->isMoving() )
		{
			/* bullet is already moving */;
		}
		else if ( object != nullptr )
		{
			/* Give bullet a move */
			if ( object->get_direction() == Coordinate::Direction::left )
			{
				object->set_move_x( -1 * BULLET_SPEED );
			}
			else
			if ( object->get_direction() == Coordinate::Direction::right )
			{
				object->set_move_x( 1 * BULLET_SPEED );
			}
		}

	}
}

void allFunction::check_health( Point_Container & _pc, Text_Cont< Text_Objt > & _tc, std::vector< SDL_Rect > (& _rect)[ 3 ] )
{
	std::cout << "allFunction:: Check Health\n";
	/* Check hero health */
	int numb = _pc.get_number_hero();

	for ( int i = 0; i < numb; ++i )
	{
		if ( _pc.get_point_hero(i)->get_health() <= 0 )
		{
			/* delete point and associated elements */
			_tc.del( _pc.get_point_hero(i), i );
			all_SDL::rect_position_del(_rect, _pc.get_point_hero(i), i );
			_pc.del( _pc.get_point_hero(i) );
			numb = _pc.get_number_hero();
			--i;		//One object has been deleted and next object takes its place, so you must check this place again;
		}
	}

	/* Check bullet health */
	numb = _pc.get_number_bullet();

	for ( int i = 0; i < numb; ++i )
	{
		if ( _pc.get_point_bullet(i)->get_health() <= 0 )
		{
			/* delete point and associated elements */
			_tc.del( _pc.get_point_bullet(i), i );
			all_SDL::rect_position_del(_rect, _pc.get_point_bullet(i), i );
			_pc.del( _pc.get_point_bullet(i) );
			numb = _pc.get_number_bullet();
			--i;		//One object has been deleted and next object takes its place, so you must check this place again;
		}
	}


	/* Check obstacle health */
	numb = _pc.get_number_obstacle();

	for ( int i = 0; i < numb; ++i )
	{
		if ( _pc.get_point_obstacle(i)->get_health() <= 0 )
		{
			/* delete point and associated elements */
			_tc.del( _pc.get_point_obstacle(i), i );
			all_SDL::rect_position_del(_rect, _pc.get_point_obstacle(i), i );
			_pc.del( _pc.get_point_obstacle(i) );
			numb = _pc.get_number_obstacle();
			--i;		//One object has been deleted and next object takes its place, so you must check this place again;
		}
	}
}

void allFunction::dump_platform_position( const char * _plik, Point_Container * _pc )
{

	std::fstream dump_file;

	dump_file.open( _plik, std::fstream::out | std::fstream::trunc );

	if ( dump_file.fail() )
	{
		std::cout << "dump position::File open error\n";
		return;
	}

	for ( int i = 0; i < _pc->get_number_obstacle(); ++i )
	{
		Point * p = _pc->get_point_obstacle( i );

		dump_file << p->get_coor_x() << "," << p->get_coor_y() << "," << p->get_coor_z() << '\n';
	}

	if ( dump_file.eof() )
	{
		std::cout << "dump position::End of file\n";
	}

	dump_file.close();

}

void allFunction::dump( const char * _plik, Point_Container * _pc, SDL_Event * _event )
{
		if ( _event->key.keysym.sym == SDLK_d )
		{

			dump_platform_position( _plik, _pc );

		}
}
