#include <cstdio>

#include "point.h"
#include "point_container.h"

Point::Point() {

	const_move_x = 0;
	const_move_y = 0;
	const_move_z = 0;
	
	borders.x = get_coor_x_p();
	borders.y = get_coor_y_p();
	borders.z = get_coor_z_p();
	
	borders.width = get_graph_width_p();
	borders.hight = get_graph_hight_p();
	
}

Point::Point( Coordinate _cord, Stru_property _prop, Stru_graph_prop _gprop ) : Position( _cord ), Property( _prop ), Graph_prop( _prop.type, _gprop ){
	
	const_move_x = 0;
	const_move_y = 0;
	const_move_z = 0;
	
	borders.x = get_coor_x_p();
	borders.y = get_coor_y_p();
	borders.z = get_coor_z_p();
	
	borders.width = get_graph_width_p();
	borders.hight = get_graph_hight_p();
	
}

Point::Point( const Point & _p ) : Position( _p ), Property( _p ), Graph_prop( _p ) {
	
	const_move_x = _p.const_move_x;
	const_move_y = _p.const_move_y;
	const_move_z = _p.const_move_z;
	
	borders.x = get_coor_x_p();
	borders.y = get_coor_y_p();
	borders.z = get_coor_z_p();
	
	borders.width = get_graph_width_p();
	borders.hight = get_graph_hight_p();
	
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
	
	if ( isCollision( *pointCont ) == false ) {
		
		if ( const_move_x != 0 || const_move_y != 0 || const_move_z != 0 ) {
			
			move_dx( const_move_x );
			move_dy( const_move_y );
			move_dz( const_move_z );
			return true;
		}
	}
	return false;
}

bool Point::isCollision( Point * sP) {
	
	//switch (point type)
	
	//for hero check obstacle and bullet
	
	//for bullet check hero and obstacle
	
	//for obstacle do nothing
	//printf("\n%d	%d\n", *(borders.x), *(borders.width));
	printf("Point::isCollision() :: this: %p		sP: %p\n",this, sP);
	if ( 	(this != sP) &&
			(
			(
				(
					((*borders.x + *borders.width) >= *sP->borders.x) && ((*borders.x + *borders.width) <= (*sP->borders.x + *sP->borders.width))
				)			
				&&				
				(
					((*borders.y + *borders.hight) >= *sP->borders.y) && (*borders.y <= (*sP->borders.y + *sP->borders.hight))
				) 
			)
				||
			(
				( 
					(*borders.x <= (*sP->borders.x + *sP->borders.width)) && (*borders.x >= *sP->borders.x) 
				) 
				&&				
				(
					((*borders.y + *borders.hight) >= *sP->borders.y) && (*borders.y <= (*sP->borders.y + *sP->borders.hight))
				) 
			)
			)
		) {
			return true;
		}	
	return false;
}

bool Point::isCollision( Point_Container & pc ) {
	
	int numb = pc.get_number_hero();
	
	for ( int i = 0; i < numb; ++i ) {
		if ( isCollision( pc.get_point_hero(i) ) ) {
		
			return true;
		}	
	}
	return false;
}

Point & Point::operator=( const Point & _p ) {
	
	if ( &_p == this )
		return *this;
	
	*(borders.x) = *(_p.borders.x);
	*(borders.y) = *(_p.borders.y);
	*(borders.z) = *(_p.borders.z);
	printf("\nPoint & Point::operator=( const Point & _p )");
	printf("\npo:	 	%p	 %p	 %p", borders.x, borders.y, borders.z);
	printf("\npo:	 	%d	 %d	 %d", *borders.x, *borders.y, *borders.z);
	
	*(borders.width) = *(_p.borders.width);
	*(borders.hight) = *(_p.borders.hight);
	
	const_move_x = _p.const_move_x;
	const_move_y = _p.const_move_y;
	const_move_z = _p.const_move_z;
	
	Position::operator =( _p );
	Graph_prop::operator =( _p );
	
	return *this;
}

void Point::print_status() {
	
	Position::print();
	
	printf( "Health: %d, speed: %d, is_visible: %d, is_mobile: %d, sprite: %s, width: %d, hight: %d\n", 
			get_health(), get_speed(), is_visible(), is_mobile(), get_graph_sprite().c_str(), get_graph_width(), get_graph_hight() ); 

}

const std::string Point::print_info() {
	
	std::string s_tmp;
	
	s_tmp = "Health: " + std::to_string(get_health()) + "\nSpeed: " + std::to_string(get_speed()) 
	+ "\nx: " + std::to_string(get_coor_x()) + "\ny: " + std::to_string(get_coor_y()) + "\nz: " + std::to_string(get_coor_z());
	
	return s_tmp;
	
}

void Point::print_borders() {
	
	printf("\npo:	 	%p	 %p	 %p", borders.x, borders.y, borders.z);
	printf("\npo:	 	%d	 %d	 %d", *borders.x, *borders.y, *borders.z);
}
