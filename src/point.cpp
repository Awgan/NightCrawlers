#include <cstdio>

#include "point.h"
#include "terminal_info.h"

Point::Point() {
	
	
}

Point::Point( Coordinate _cord, Stru_property _prop, Stru_graph_prop _gprop ) : Position( _cord ), Property( _prop ), Graph_prop( _prop.type, _gprop ){
	
		
}

Point::Point( const Point & _p ) : Position( _p ), Property( _p ), Graph_prop( _p ) {
	
	const_move_x = _p.const_move_x;
	const_move_y = _p.const_move_y;
	const_move_z = _p.const_move_z;
	
	komun("class Point, copy constructor");
}

Point::~Point() {
	
}




void Point::move_dx( int _dx ) {
	int temp = get_coor_x() + _dx * DEF_SPEED;
	
	//checking limits
	if ( within_lim_min( get_lim_min_x(), temp ) && within_lim_max( get_lim_max_x(), temp ) ) {
		
		set_coor_x( temp );
	}
	
	//changing direction
	if ( _dx < 0 && get_direction() != CoorDir::left ) {
		set_direction( CoorDir::left );
	}
	else if ( _dx > 0 && get_direction() != CoorDir::right ) {
		set_direction( CoorDir::right );
	}
	
}

void Point::move_dy( int _dy ) {
	int temp = get_coor_y() + _dy * DEF_SPEED;
	
	//checking limits
	if ( within_lim_min( get_lim_min_y(), temp ) && within_lim_max( get_lim_max_y(), temp ) ) {
		
		set_coor_y( temp );
	}
	
	//changing direction
	if ( _dy < 0 && get_direction() != CoorDir::up ) {
		set_direction( CoorDir::up );
	}
	else if ( _dy > 0 && get_direction() != CoorDir::down ) {
		set_direction( CoorDir::down );
	}
	
}

void Point::move_dz( int _dz ) {
	int temp = get_coor_z() + _dz * DEF_SPEED;
	
	//checking limits
	if ( within_lim_min( get_lim_min_z(), temp ) && within_lim_max( get_lim_max_z(), temp ) ) {
		
		set_coor_z( temp );
	}
	
	//changing direction
	if ( _dz < 0 && get_direction() != CoorDir::deep ) {
		set_direction( CoorDir::left );
	}
	else if ( _dz > 0 && get_direction() != CoorDir::shallow ) {
		set_direction( CoorDir::shallow );
	}
	
}

bool Point::move() {
	
	if ( const_move_x != 0 || const_move_y != 0 || const_move_z != 0 ) {
		
		move_dx( const_move_x );
		move_dy( const_move_y );
		move_dz( const_move_z );
		return true;
	}
	
	return false;
}

bool Point::check_collision() {
	
	//switch (point type)
	
	//for hero check obstacle and bullet
	
	//for bullet check hero and obstacle
	
	//for obstacle do nothing
	
	
	return false;
}


void Point::print_status() {
	
	Position::print();
	
	printf( "Health: %d, speed: %d, is_visible: %d, is_mobile: %d, sprite: %s, width: %d, hight: %d\n", 
			get_health(), get_speed(), is_visible(), is_mobile(), get_graph_sprite().c_str(), get_graph_widht(), get_graph_hight() ); 

}
