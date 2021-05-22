#include <cstdio>
#include <iostream>

#include "position.h"

/* Coordinate members definition */

void Coordinate::show() {

	std::cout << "COORDINATE show() > x: " << x << " y: " << y << " z: " << z << "angle: " << angle << " dir: " << (int)dir << std::endl;

}

Coordinate & Coordinate::operator=(const Coordinate & _coor ) {

	x = _coor.x;
	y = _coor.y;
	z = _coor.z;
	angle = _coor.angle;
	dir = _coor.dir;

	return *this;
}

Coordinate::Direction dir_conv( const std::string & _str ) {

	//Direction -->{ right, up, left, down, deep, shallow }

	if ( _str == "right" ) {
		return Coordinate::Direction::right;
	}
	else if ( _str == "up" ) {
		return Coordinate::Direction::up;
	}
	else if ( _str == "left" ) {
		return Coordinate::Direction::left;
	}
	else if ( _str == "down" ) {
		return Coordinate::Direction::down;
	}
	else if ( _str == "deep" ) {
		return Coordinate::Direction::deep;
	}
	else if ( _str == "shallow" ) {
		return Coordinate::Direction::shallow;
	}

	return Coordinate::Direction::right;
}

/* Position members definition */

Position::Position ( int _x, int _y, int _z, CoorDir _dir ) {

	//50s are dimensions of displayed hero

	limits.min = { 0, 0, 0 };
	limits.max = { WIN_WIDTH, WIN_HEIGHT, 0 };

	if ( _x >= limits.min.x && _x <= limits.max.x )
		coord.x = _x;
	else {

		if ( _x <= limits.min.x )
			coord.x = limits.min.x;
		if ( _x >= limits.max.x )
			coord.x = limits.max.x;// - HERO_WIDTH;
	}

	if ( _y >= limits.min.y && _y <= limits.max.y )
		coord.y = _y;
	else {

		if ( _y <= limits.min.y )
			coord.y = limits.min.y;
		if ( _y >= limits.max.y )
			coord.y= limits.max.y;// - HERO_HEIGHT;
	}

	//
	//it can be use for 3D, if at all it happens
	/*
	if ( _z >= limits.min.z && _x <= limits.max.z )
		coord.z = _z;
	else {

		if ( _z <= limits.min.z )
			coord.z = limits.min.z;
		if ( _z >= limits.max.z )
			coord.z = limits.max.z;
	}
	*/
	coord.z = 0;


	coord.dir = _dir;


}

Position::Position( Coordinate & _coord ) {

	limits.min = { 0, 0, 0 };
	limits.max = { WIN_WIDTH, WIN_HEIGHT, 0 };

	if ( _coord.x >= limits.min.x && _coord.x <= limits.max.x )
		coord.x = _coord.x;
	else {

		if ( _coord.x <= limits.min.x )
			coord.x = limits.min.x;
		if ( _coord.x >= limits.max.x )
			coord.x = limits.max.x - HERO_WIDTH;
	}

	if ( _coord.y >= limits.min.y && _coord.y <= limits.max.y )
		coord.y = _coord.y;
	else {

		if ( _coord.y <= limits.min.y )
			coord.y = limits.min.y;
		if ( _coord.y >= limits.max.y )
			coord.y= limits.max.y - HERO_HEIGHT;
	}

	//
	//it can be use for 3D, if at all it happens
	/*
	if ( _coord.z >= limits.min.z && _coord.x <= limits.max.z )
		coord.z = _coord.z;
	else {

		if ( _coord.z <= limits.min.z )
			coord.z = limits.min.z;
		if ( _coord.z >= limits.max.z )
			coord.z = limits.max.z;
	}
	*/
	coord.z = 0;


	coord.dir = _coord.dir;

}

Position::Position( const Position & _p ) {

	coord = _p.coord;
	limits = _p.limits;
}

bool Position::within_lim_min_x( const int & xyz ) {

	return ( xyz >= limits.min.x );
}

bool Position::within_lim_max_x( const int & xyz ) {

	return ( xyz <= limits.max.x - 1);// - HERO_WIDTH );
}

bool Position::within_lim_min_y( const double & xyz ) {

	return ( xyz >= limits.min.y );
}

bool Position::within_lim_max_y( const double & xyz ) {

	return ( xyz <= limits.max.y - (2*PLATFORM_H) );
}

bool Position::within_lim_min_z( const int & xyz ) {

	return ( xyz >= limits.min.z );
}

bool Position::within_lim_max_z( const int & xyz ) {

	return ( xyz <= limits.max.z );
}

void Position::set_coor( int _x, double _y, int _z ) {

	//checking limits
	if ( within_lim_min_x( _x ) && within_lim_min_y( _y ) && within_lim_min_z( _z )
	&& within_lim_max_x( _x ) && within_lim_max_y( _y ) && within_lim_max_z( _z ) ) {

		coord = { _x, _y, _z };
	}
}

bool Position::set_coor_x( int _x )	{

	/* check limits */
	if ( !within_lim_min_x( _x ) )
	{
		coord.x = limits.min.x;
		return false;
	}
	else if ( !within_lim_max_x( _x ) )
	{
		coord.x = limits.max.x - 1;// -HERO_WIDTH;
		return false;
	}

	coord.x = _x;
	return true;
}

bool Position::set_coor_y( double _y )	{

	/* checking limits */
	if ( !within_lim_min_y( _y ) )
	{
		coord.y = limits.min.y;
		return false;
	}
	else if ( !within_lim_max_y( _y ) )
	{
		coord.y = limits.max.y;
		return false;
	}

	coord.y = (int)_y;
	return true;
}

bool Position::set_coor_z( int _z )	{

	return false;
}

void Position::setAngle( const int ang )
{
	coord.angle = ang;

	if( coord.angle < 0 )
	{
		coord.angle = 360 + coord.angle;
	}
	else if( coord.angle >359 )
	{
		coord.angle = coord.angle - 360;
	}
}

void Position::inc_coor_x( int _x )
{

	set_coor_x( coord.x + _x );
}

void Position::inc_coor_y( double _y )
{

	set_coor_y( coord.y + _y );
}

void Position::inc_coor_z( int _z )
{

	set_coor_z( coord.z + _z );
}

void Position::print() const
{

	printf( "Coordinates: x: %d, y: %f, z: %d, angle: %d\n", coord.x, coord.y, coord.z, coord.angle );

}
