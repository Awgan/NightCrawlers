#include <cstdio>
#include <iostream>

#include "point.h"


Point::Point( const Point_type & _pt ) : Graph_prop( _pt )
{

	const_move_x = 0;
	const_move_y = 0;
	const_move_z = 0;

	borders.x = get_coor_x_p();
	borders.y = get_coor_y_p();
	borders.z = get_coor_z_p();

	borders.width = get_graph_width_p();
	borders.height = get_graph_height_p();

	pointCont = nullptr;

	collision_with = nullptr;

	standing = false;

}

Point::Point( Coordinate _cord, Stru_property _prop, Stru_graph_prop &_gprop ) : Position( _cord ), Property( _prop ), Graph_prop( _prop.type, _gprop ) {

	const_move_x = 0;
	const_move_y = 0;
	const_move_z = 0;

	borders.x = get_coor_x_p();
	borders.y = get_coor_y_p();
	borders.z = get_coor_z_p();

	borders.width = get_graph_width_p();
	borders.height = get_graph_height_p();

	pointCont = nullptr;

	collision_with = nullptr;

	standing = false;

}

Point::Point( const Point & _p ) : Position( _p ), Property( _p ), Graph_prop( _p ) {

	const_move_x = _p.const_move_x;
	const_move_y = _p.const_move_y;
	const_move_z = _p.const_move_z;

	borders.x = get_coor_x_p();
	borders.y = get_coor_y_p();
	borders.z = get_coor_z_p();

	borders.width = get_graph_width_p();
	borders.height = get_graph_height_p();

	pointCont = _p.pointCont;

	collision_with = _p.collision_with;

	standing = false;

}

Point::Point ( Point && _p ) : Position( _p ), Property( _p ), Graph_prop( _p ) {

	std::cout << "Point ( Point && _p ): r-value reference ctor\n";

	const_move_x = _p.const_move_x;
	const_move_y = _p.const_move_y;
	const_move_z = _p.const_move_z;

	borders.x = get_coor_x_p();
	borders.y = get_coor_y_p();
	borders.z = get_coor_z_p();

	borders.width = get_graph_width_p();
	borders.height = get_graph_height_p();

	pointCont = _p.pointCont;

	collision_with = _p.collision_with;

	standing = false;

}

Point::~Point() {

}

void Point::init_borders()
{
	borders.x = get_coor_x_p();
	borders.y = get_coor_y_p();
	borders.z = get_coor_z_p();

	borders.width = get_graph_width_p();
	borders.height = get_graph_height_p();
}

void Point::move_dx( int _dx ) {

	if ( is_mobile() != true )
		return;

	int temp = get_coor_x() + _dx * DEF_SPEED;
	int before = get_coor_x();


		/* Change direction and sprite (if it is possible for an object) */
		int actSpr = getActualSprite();


		if ( _dx < 0 /*&& get_direction() != CoorDir::left*/ ) {
			set_direction( CoorDir::left );

			if ( this->get_point_type() == Point_type::hero )
			{
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
		}
		else if ( _dx > 0 /*&& get_direction() != CoorDir::right*/ ) {
			set_direction( CoorDir::right );

			if ( this->get_point_type() == Point_type::hero )
			{
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
		}


		/* Set new position and place object as close as it is possible to the collision object */
		set_coor_x( temp );

		while ( isCollision( *pointCont ) == true && _dx != 0 )
		{
			/* Hit object */
			if ( get_point_type() == Point_type::bullet )
			{
				collision_with->change_health( -10 );	//Demage object
				set_health( 0 );						//Delete bullet
				return;
			}


			/* Push object */
			if ( collision_with->get_point_type() == Point_type::obstacle )
			{
				push( collision_with );
			}


			/* Reduce distance */
			_dx > 0 ? --_dx : ++_dx;
			temp = before + _dx * DEF_SPEED;
			set_coor_x ( temp );


		}


		/* self moving counter */
		isSelfMoving();
}

void Point::move_dy( double _dy )
{
	if ( is_mobile() != true )
		{
			return;
		}

	double temp = get_coor_y() + _dy * DEF_SPEED;
	double before = get_coor_y();


	/* changing direction and sprite (if it is possible for an object) */
	//if ( _dy < 0 && get_direction() != CoorDir::up )
	//{
		//set_direction( CoorDir::up );
	//}
	//else if ( _dy > 0 && get_direction() != CoorDir::down )
	//{
		//set_direction( CoorDir::down );
	//}


	/* set new position */
	set_coor_y( temp );

	/*check collision and place object as close as it is possible to the collision object */
	while ( isCollision( *pointCont ) == true && _dy != 0 )
	{
		if ( _dy > 0 )		//reducing distance
			{
				--_dy;
			}
			else
			{
				++_dy;
				set_move_y(0);
			}

		temp = before + _dy * DEF_SPEED;
		set_coor_y ( temp );

		if ( collision_with->get_point_type() == Point_type::obstacle )
		{
			push( collision_with );
		}
/*
		if ( standing == false && _dy > 0 )
		{
			std::cout << "Point::move_dy( int _dy ) :: object gets ground\n";
			standing = true;
		}*/
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
			_dz > 0 ? --_dz : ++_dz;		//reducing distance
			temp = before + _dz * DEF_SPEED;
			set_coor_z ( temp );

			if ( collision_with->get_point_type() == Point_type::obstacle )
			{
				push( collision_with );
			}
		}
}

bool Point::move() {
//std::cout << "bool Point::move() => x: " << get_move_x() << " | y: " << get_move_y() << " | z: " << get_move_z() << '\n';
	bool flag = false;


	if ( const_move_x != 0 ) {
		move_dx( const_move_x );
		flag |= true;
	}
	if ( const_move_y != 0  ) {
		move_dy( const_move_y );
		flag |= true;
	}
	if ( const_move_z != 0 ) {
		move_dz( const_move_z );
		flag |= true;
	}

	checkStanding();

return flag;
}

void Point::push( Point * _p )
{
	if ( _p->is_mobile() ) {

		CoorDir cd = this->get_direction();
		switch( cd ) {

			case CoorDir::left:
			case CoorDir::right:
				_p->set_move_y( 0 );
				_p->set_move_z( 0 );

				_p->set_move_x( _p->get_speed() * (cd == CoorDir::left ? -1 : 1) );
				//_p->set_self_move_distance( 0 );
				//std::cout << "obstacle is pushing X : " << const_move_x << '\n';
			break;

			case CoorDir::up:
			case CoorDir::down:
				_p->set_move_x( 0 );
				_p->set_move_z( 0 );

				_p->set_move_y( _p->get_speed() * (cd == CoorDir::up ? -1 : 1) );
				//_p->set_self_move_distance( 0 );
				//std::cout << "obstacle is pushing Y : " << const_move_y << '\n';
			break;

			default:
			break;
		}
	}
}

bool Point::isMoving() {

	if ( const_move_x != 0 || const_move_y != 0 || const_move_z != 0 ) {
		return true;
	}

return false;
}

bool Point::isSelfMoving() {

	int moveSelf = get_self_move_distance();
//std::cout << "#debug isSelMoving => move_distance: " << get_self_move_distance() << '\n';
	/* '-1' value means that object can't be pushed */
	if ( moveSelf == -1 )
		return false;


	/* self moving counter for pushed object */
	int maxDistance = get_speed() * get_move_points();

	if ( moveSelf >= 0 && moveSelf < maxDistance )
	{
		//std::cout << "Point::isSelfMoving() :: is self moving: " << this << '\n';
		increas_self_move_distance( get_speed() );		//variable is increasing and when overflow max posible distance then object is stopped

		return true;
	}
	else
	{
		//std::cout << "isSelMoving problem\n";
		/* stop self move object */
		set_self_move_distance( 0 );

		set_move_x( 0 );
		if ( standing == true )
			set_move_y( 0 );
		set_move_z( 0 );

		return false;
	}

return false;
}

void Point::checkStanding() {

	if ( !is_mobile() )
		return;

	double temp = get_coor_y() + 1 * DEF_SPEED;
	double before = get_coor_y();				//saving variable data

	Point * collWith = collision_with;		//saving variable data

	set_coor_y ( temp );

	//if object does not touch game borders or does not collide than standing is set to false;
	if ( within_lim_max_y( temp ) && isCollision( *pointCont ) == false )
	{
		standing = false;

		//std::cout << "Point::checkStanding() :: "; print_type(); std::cout << " losts ground\n";
	}
	else
	{
		standing = true;
		const_move_y = 0;
		//std::cout << "Point::checkStanding() :: "; print_type(); std::cout << " gets ground\n";
	}

	collision_with = collWith;	//returning to previous state

	set_coor_y( before );

	//std::cout << "Point::checkStanding() => before: " << before << '\n';
}

bool Point::isCollision( Point * sP) {

	if
	( 	(sP != nullptr)
			&&
		(this != sP)
			&&
		( *borders.x + *borders.width >= *sP->borders.x )
			&&
		( *borders.x <= *sP->borders.x + *sP->borders.width )
			&&
		(*borders.y + *borders.height >= *sP->borders.y)
			&&
		(*borders.y <= *sP->borders.y + *sP->borders.height)
	)
	{
		collision_with = sP;
		//std::cout << "collision\n";
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

	/* checking if there is collision with bullet */
	numb = pc.get_number_bullet();

	for ( int i = 0; i < numb; ++i ) {

		if ( pc.get_point_bullet(i) && isCollision( pc.get_point_bullet(i) ) ) {
			//std::cout << "i : " << i << '\n';

			return true;
		}
	}


	/* checking if there is collision with obstacle */
	numb = pc.get_number_obstacle();

	for ( int i = 0; i < numb; ++i ) {

		if ( isCollision( pc.get_point_obstacle(i) ) ) {
			//std::cout << "i : " << i << '\n';

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
	*(borders.height) = *(_p.borders.height);

	const_move_x = _p.const_move_x;
	const_move_y = _p.const_move_y;
	const_move_z = _p.const_move_z;

	pointCont = _p.pointCont;

	collision_with = _p.collision_with;

	standing = _p.standing;

	Position::operator =( _p );
	Graph_prop::operator =( _p );
	Property::operator =( _p );

	return *this;
}

Point & Point::operator=( Point && _p ) {

	//TODO:: project
	std::cout << "r_value assigment operator\n";
	return *this;
}

void Point::print_status() {

	Position::print();

	printf( "Health: %d, speed: %d, is_visible: %d, is_mobile: %d, sprite: %s, width: %d, height: %d, standing: %d\n",
			get_health(), get_speed(), is_visible(), is_mobile(), get_graph_sprite().c_str(), get_graph_width(), get_graph_height(), isStanding() );

}

const std::string Point::print_info() {

	std::string s_tmp;

	s_tmp = "Health: " + std::to_string(get_health()) + "\nSpeed: " + std::to_string(get_speed())
	+ "\nx: " + std::to_string(get_coor_x()) + "\ny: " + std::to_string(get_coor_y()) + "\nz: " + std::to_string(get_coor_z() + '\n');

	return s_tmp;

}

void Point::print_borders() {

	printf("po:	 	%p	 %p	 %p\n", borders.x, borders.y, borders.z);
	printf("po:	 	%d	 %f	 %d\n", *borders.x, *borders.y, *borders.z);

}
