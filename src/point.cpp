#include <cstdio>

#include "point.h"

Point::Point( int _x, int _y, int _z, CoorDir _dir ) : Position( _x, _y, _z, _dir ) {
	
	prop.b_mobile = true;
	prop.b_visible = true;
	
	prop.health = DEF_HEALTH;
	prop.speed	= DEF_SPEED;
	
}

Point::Point( const Graphic_Prop & _g_prop, Coordinate & _coor ) : Position( _coor.x, _coor.y, _coor.z, _coor.dir ) {
	
	prop.type = neutral;

	prop.b_mobile = true;
	prop.b_visible = true;
	
	prop.health = DEF_HEALTH;
	prop.speed	= DEF_SPEED;

	grap_prop = _g_prop;
	
}

void Point::change_health( int _dh ) {
	
	prop.health += _dh;
	
	if ( prop.health <= 0 ) {
		
		prop.health 	= 0;
		prop.b_visible 	= false;
		prop.b_mobile 	= false;
	}
}
void Point::set_healt( int _h ) {
	
	if ( _h >= 0 ) {
		prop.health = _h;
	}
	
	if ( prop.health <= 0 ) {
		
		prop.health 	= 0;
		prop.b_visible 	= false;
		prop.b_mobile 	= false;
	}	
}

void Point::change_speed( int _ds ) {
	
	prop.speed += _ds;
	
	if ( prop.speed < 0 ) {
		prop.speed = 0;
	}
	
}
void Point::set_speed( int _s ) {
	
	prop.speed = _s;
	
	if ( prop.speed < 0 ) {
		prop.speed = 0;
	}
}


void Point::move_dx( int _dx ) {
	int temp = get_coor_x() + _dx * DEF_SPEED;
	
	//checking limits
	if ( check_lim_min( get_lim_min_x(), temp ) && check_lim_max( get_lim_max_x(), temp ) ) {
		
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
	if ( check_lim_min( get_lim_min_y(), temp ) && check_lim_max( get_lim_max_y(), temp ) ) {
		
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
	if ( check_lim_min( get_lim_min_z(), temp ) && check_lim_max( get_lim_max_z(), temp ) ) {
		
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

void Point::print_status() const {
	
	Position::print_status();
	
	printf( "Health: %d, speed: %d, is_visible: %d, is_mobile: %d, sprite: %s, width: %d, hight: %d\n", 
			prop.health, prop.speed, prop.b_visible, prop.b_mobile, grap_prop.sprite, grap_prop.width, grap_prop.hight ); 

}
