#include <cstdio>
#include <iostream>

#include "point.h"


Point::Point() {

	const_move_x = 0;
	const_move_y = 0;
	const_move_z = 0;
	
	borders.x = get_coor_x_p();
	borders.y = get_coor_y_p();
	borders.z = get_coor_z_p();
	
	borders.width = get_graph_width_p();
	borders.hight = get_graph_hight_p();
	
	pointCont = nullptr;
	
	collision_with = nullptr;
	
}

Point::Point( Coordinate _cord, Stru_property _prop, Stru_graph_prop &_gprop ) : Position( _cord ), Property( _prop ), Graph_prop( _prop.type, _gprop ) {
	
	const_move_x = 0;
	const_move_y = 0;
	const_move_z = 0;
	
	borders.x = get_coor_x_p();
	borders.y = get_coor_y_p();
	borders.z = get_coor_z_p();
	
	borders.width = get_graph_width_p();
	borders.hight = get_graph_hight_p();
	
	pointCont = nullptr;
	
	collision_with = nullptr;
	
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
	
	pointCont = _p.pointCont;
	
	collision_with = _p.collision_with;
	
}

Point::Point ( Point && _p ) {
	
	std::cout << "r-value reference ctor\n";
	
}

Point::~Point() {
	
}

void Point::move_dx( int _dx ) {
	
	if ( is_mobile() != true )
		return;
	
	int temp = get_coor_x() + _dx * DEF_SPEED;
	int before = get_coor_x();
	
	/* checking limits */
	if (  within_lim_min_x( temp ) && within_lim_max_x( temp )  ) {
		
		
		/* changing direction and sprite (if it is possible for an object) */
		int actSpr = getActualSprite();
		
		if ( _dx < 0 && get_direction() != CoorDir::left ) {
			set_direction( CoorDir::left );
			
			switch ( actSpr ) {
				
				case 4:
				setActualSprite( 3 );
				break;
				case 5:
				setActualSprite( 2 );
				break;
				case 6:
				setActualSprite( 1 );
				break;
				case 7:
				setActualSprite( 0 );
				break;
				
				default:
				break;
			}				
		}
		else if ( _dx > 0 && get_direction() != CoorDir::right ) {
			set_direction( CoorDir::right );
			
			switch ( actSpr ) {
				
				case 0:
				setActualSprite( 7 );
				break;
				case 1:
				setActualSprite( 6 );
				break;
				case 2:
				setActualSprite( 5 );
				break;
				case 3:
				setActualSprite( 4 );
				break;
				
				default:
				break;
			}
		}
		
		
		/* set new position and place object as close as it is possible to the collision object */
		set_coor_x( temp );		
		
		while ( isCollision( *pointCont ) == true && _dx != 0 ) 
		{
			_dx > 0 ? --_dx : ++_dx;
			temp = before + _dx * DEF_SPEED;
			set_coor_x ( temp );			
		}	
	}
	
	
	/* self moving counter */		
		isSelfMoving();			
}

void Point::move_dy( int _dy )
{
	if ( is_mobile() != true )
		return;
	
	int temp = get_coor_y() + _dy * DEF_SPEED;
	int before = get_coor_y();
	
		/* checking limits */
		if (  within_lim_min_y( temp ) && within_lim_max_y( temp )  )
		{
			
			
			/* changing direction and sprite (if it is possible for an object) */
			if ( _dy < 0 && get_direction() != CoorDir::up )
			{
				set_direction( CoorDir::up );
			}
			else if ( _dy > 0 && get_direction() != CoorDir::down )
			{
				set_direction( CoorDir::down );
			}
			
			
			/* set new position and place object as close as it is possible to the collision object */
			set_coor_y( temp );
			
			while ( isCollision( *pointCont ) == true && _dy != 0 ) 
			{
				_dy > 0 ? --_dy : ++_dy;
				temp = before + _dy * DEF_SPEED;
				set_coor_y ( temp );				
			}	
		}
		
	
	/* self moving counter */		
		isSelfMoving();		
}

void Point::move_dz( int _dz ) {
	
	if ( is_mobile() != true )
		return;
	
	int temp = get_coor_z() + _dz * DEF_SPEED;
	int before = get_coor_z();
	
	/* checking limits */
	if (  within_lim_min_z( temp ) && within_lim_max_z( temp )  ) {
		
	
		/* changing direction and sprite (if it is possible for an object) */
		if ( _dz < 0 && get_direction() != CoorDir::deep ) {
			set_direction( CoorDir::deep );
		}
		else if ( _dz > 0 && get_direction() != CoorDir::shallow ) {
			set_direction( CoorDir::shallow );
		}
		
		
		/* set new position and place object as close as it is possible to the collision object */
		set_coor_z( temp );
		
		while ( isCollision( *pointCont ) == true ) 
		{
			_dz > 0 ? --_dz : ++_dz;
			temp = before + _dz * DEF_SPEED;
			set_coor_z ( temp );					
		}			
	}
}

bool Point::move() {
	
	if ( const_move_x != 0 ) {
		move_dx( const_move_x );
		return true;
	}
	if ( const_move_y != 0  ) {
		move_dy( const_move_y );
		return true;
	}
	if ( const_move_z != 0 ) {
		
		move_dz( const_move_z );
		return true;
	}
	
return false;
}

bool Point::isMoving() {
	
	if ( const_move_x != 0 || const_move_y != 0 || const_move_z != 0 ) {
		return true;
	}
	
return false;	
}

bool Point::isSelfMoving() {
	
	int moveDistance = get_move_distance();
	
	/* '-1' value means that object can't be pushed */
	if ( moveDistance == -1 )
		return false;
	
	
	/* self moving counter for pushed object */
	int maxDistance = get_speed() * get_move_points();
	
	if ( moveDistance < maxDistance && get_move_distance() >= 0 ) {
		
		change_move_distance( get_speed() );		
		return true;
		
	} else {
	
		/* stopping self move object */
		set_move_distance( 0 );
		
		set_move_x( 0 );
		set_move_y( 0 );
		set_move_z( 0 );
		
		return false;
	}


return false;
}

bool Point::isCollision( Point * sP) {

	//switch (point type)
	
	//for hero check obstacle and bullet
	
	//for bullet check hero and obstacle
	
	//for obstacle do nothing
	//printf("\n%d	%d\n", *(borders.x), *(borders.width));
	//printf("1.Point::isCollision(Point* sP) :: this: %p		sP: %p\n",this, sP);
	
	
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
			collision_with = sP;
			std::cout << "collision\n";
			return true;
		}	

	return false;
}

bool Point::isCollision( Point_Container & pc ) {

	/* checking if there is collision with another hero */
	int numb = pc.get_number_hero();
		
	for ( int i = 0; i < numb; ++i ) {
		if ( isCollision( pc.get_point_hero(i) ) ) {
			
			/* return; no more action */
			return true;
		}	
	}
	
	/* checking if there is collision with obstacle */
	numb = pc.get_number_obstacle();
	
	for ( int i = 0; i < numb; ++i ) {
		
		if ( isCollision( pc.get_point_obstacle(i) ) ) {
			std::cout << "i : " << i << '\n';
			if ( pc.get_point_obstacle(i)->is_mobile() ) {
				
				CoorDir cd = this->get_direction();
				switch( cd ) {
					
					case CoorDir::left:
					case CoorDir::right:
						pc.get_point_obstacle(i)->set_move_y( 0 );
						pc.get_point_obstacle(i)->set_move_z( 0 );
						
						pc.get_point_obstacle(i)->set_move_x( pc.get_point_obstacle(i)->get_speed() * (cd == CoorDir::left ? -1 : 1) );
						pc.get_point_obstacle(i)->set_move_distance( 0 );
						std::cout << "obstacle is moving X : " << const_move_x << '\n';
					break;
					
					case CoorDir::up:
					case CoorDir::down:
						pc.get_point_obstacle(i)->set_move_x( 0 );
						pc.get_point_obstacle(i)->set_move_z( 0 );
						
						pc.get_point_obstacle(i)->set_move_y( pc.get_point_obstacle(i)->get_speed() * (cd == CoorDir::up ? -1 : 1) );
						pc.get_point_obstacle(i)->set_move_distance( 0 );
						std::cout << "obstacle is moving Y : " << const_move_y << '\n';
					break;
					
					default:
					break;
				}
			}
			
			return true;
		
		}	
	}
	
	collision_with = nullptr;
	return false;
}

Point & Point::operator=( const Point & _p ) {
	
	if ( &_p == this )
		return *this;
		
	*(borders.x) = *(_p.borders.x);
	*(borders.y) = *(_p.borders.y);
	*(borders.z) = *(_p.borders.z);
	
	/* DEBUG
	printf("\nPoint & Point::operator=( const Point & _p )");
	printf("\npo:	 	%p	 %p	 %p", borders.x, borders.y, borders.z);
	printf("\npo:	 	%d	 %d	 %d", *borders.x, *borders.y, *borders.z);
	*/
	
	*(borders.width) = *(_p.borders.width);
	*(borders.hight) = *(_p.borders.hight);
	
	const_move_x = _p.const_move_x;
	const_move_y = _p.const_move_y;
	const_move_z = _p.const_move_z;
	
	pointCont = _p.pointCont;
	
	collision_with = _p.collision_with;
	
	Position::operator =( _p );
	Graph_prop::operator =( _p );
	Property::operator =( _p );
		
	return *this;
}

Point & Point::operator=( Point && _p ) {
	
	std::cout << "r_value assigment operator\n";
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
	+ "\nx: " + std::to_string(get_coor_x()) + "\ny: " + std::to_string(get_coor_y()) + "\nz: " + std::to_string(get_coor_z() + '\n');
	
	return s_tmp;
	
}

void Point::print_borders() {
	
	printf("po:	 	%p	 %p	 %p\n", borders.x, borders.y, borders.z);
	printf("po:	 	%d	 %d	 %d\n", *borders.x, *borders.y, *borders.z);

}
