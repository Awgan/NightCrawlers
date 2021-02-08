#include <iostream>


#include "all.h"

bool allFunction::move_keyboard( Point * _point, SDL_Event * _event) {
//std::cout << "bool allFunction::move_keyboard\n";
	if ( _point->is_mobile() )
	{
		switch ( _event->type ) {
			case SDL_KEYDOWN:
				switch ( _event->key.keysym.sym ) {

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

	//std::cout << "mx: " << mx << '\n';

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



void allFunction::gravity_move( Point_Container & _pc ) {

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
	Point * object = nullptr;

	for ( int i = 0; i < _pc.get_number_bullet(); ++i )
	{
		object = _pc.get_point_bullet( i );

		if ( object != nullptr && object->isMoving() )
		{
			//std::cout << "bullet is moving\n";
		}
		else if ( object != nullptr )
		{
			if ( object->get_direction() == Coordinate::Direction::left )
			{
				object->set_move_x( -1 * BULLET_SPEED );//std::cout << "bullet moves left\n";
			}
			else
			if ( object->get_direction() == Coordinate::Direction::right )
			{
				object->set_move_x( 1 * BULLET_SPEED );//std::cout << "bullet moves right\n";
			}
		}

	}
}

void allFunction::check_health( Point_Container & _pc, Text_Cont< Text_Objt > & _tc, std::vector< SDL_Rect > (& _rect)[ 3 ] )
{
	/* Check hero health */
	int numb = _pc.get_number_hero();

	for ( int i = 0; i < numb; ++i )
	{
		if ( _pc.get_point_hero(i)->get_health() <= 0 )
		{
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
		if ( _pc.get_point_bullet(i) && (_pc.get_point_bullet(i)->get_health() <= 0) )
		{
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
			_tc.del( _pc.get_point_obstacle(i), i );
			all_SDL::rect_position_del(_rect, _pc.get_point_obstacle(i), i );
			_pc.del( _pc.get_point_obstacle(i) );
			numb = _pc.get_number_obstacle();
			--i;		//One object has been deleted and next object takes its place, so you must check this place again;
		}
	}
}
