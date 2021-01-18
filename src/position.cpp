#include <cstdio>
#include <iostream>

#include "position.h"

//Coordinate members definition

void Coordinate::show() {

	std::cout << "COORDINATE show() > x: " << x << " y: " << y << " z: " << z << " dir: " << (int)dir << std::endl;

}

Coordinate & Coordinate::operator=(const Coordinate & _coor ) {

	x = _coor.x;
	y = _coor.y;
	z = _coor.z;
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

//Position members definition

Position::Position ( int _x, int _y, int _z, CoorDir _dir ) {

	//50s are dimensions of displayed hero

	limits.min = { 0, 0, 0 };
	limits.max = { WIN_WIDTH - HERO_WIDTH, WIN_HIGHT - HERO_HIGHT, 0 };

	if ( _x >= limits.min.x && _x <= limits.max.x )
		coor.x = _x;
	else {

		if ( _x <= limits.min.x )
			coor.x = limits.min.x;
		if ( _x >= limits.max.x )
			coor.x = limits.max.x - HERO_WIDTH;
	}

	if ( _y >= limits.min.y && _y <= limits.max.y )
		coor.y = _y;
	else {

		if ( _y <= limits.min.y )
			coor.y = limits.min.y;
		if ( _y >= limits.max.y )
			coor.y= limits.max.y - HERO_HIGHT;
	}

	//
	//it can be use for 3D, if at all it happens
	/*
	if ( _z >= limits.min.z && _x <= limits.max.z )
		coor.z = _z;
	else {

		if ( _z <= limits.min.z )
			coor.z = limits.min.z;
		if ( _z >= limits.max.z )
			coor.z = limits.max.z;
	}
	*/
	coor.z = 0;


	coor.dir = _dir;

	offset = HERO_WIDTH;

}

Position::Position( Coordinate & _coord ) {

	limits.min = { 0, 0, 0 };
	limits.max = { WIN_WIDTH, WIN_HIGHT, 0 };

	if ( _coord.x >= limits.min.x && _coord.x <= limits.max.x )
		coor.x = _coord.x;
	else {

		if ( _coord.x <= limits.min.x )
			coor.x = limits.min.x;
		if ( _coord.x >= limits.max.x )
			coor.x = limits.max.x - HERO_WIDTH;
	}

	if ( _coord.y >= limits.min.y && _coord.y <= limits.max.y )
		coor.y = _coord.y;
	else {

		if ( _coord.y <= limits.min.y )
			coor.y = limits.min.y;
		if ( _coord.y >= limits.max.y )
			coor.y= limits.max.y - HERO_HIGHT;
	}

	//
	//it can be use for 3D, if at all it happens
	/*
	if ( _coord.z >= limits.min.z && _coord.x <= limits.max.z )
		coor.z = _coord.z;
	else {

		if ( _coord.z <= limits.min.z )
			coor.z = limits.min.z;
		if ( _coord.z >= limits.max.z )
			coor.z = limits.max.z;
	}
	*/
	coor.z = 0;


	coor.dir = _coord.dir;

	offset = HERO_WIDTH;
}

Position::Position( const Position & _p ) {
std::cout << "perfect11\n";
	coor = _p.coor;std::cout << "perfect22\n";
	limits = _p.limits;std::cout << "perfect33\n";
	offset = _p.offset;
std::cout << "perfect44\n";
}

bool Position::within_lim_min_x( const int & xyz ) {

	return ( xyz >= limits.min.x );
}

bool Position::within_lim_max_x( const int & xyz ) {

	return ( xyz <= limits.max.x - HERO_WIDTH );
}

bool Position::within_lim_min_y( const double & xyz ) {

	return ( xyz >= limits.min.y );
}

bool Position::within_lim_max_y( const double & xyz ) {

	return ( xyz <= limits.max.y - HERO_HIGHT );
}

bool Position::within_lim_min_z( const int & xyz ) {

	return ( xyz >= limits.min.z );
}

bool Position::within_lim_max_z( const int & xyz ) {

	return ( xyz <= limits.max.z - HERO_WIDTH );
}

void Position::set_coor( int _x, double _y, int _z ) {

	//checking limits
	if ( within_lim_min_x( _x ) && within_lim_min_y( _y ) && within_lim_min_z( _z )
	&& within_lim_max_x( _x ) && within_lim_max_y( _y ) && within_lim_max_z( _z ) ) {

		coor = { _x, _y, _z };
	}
}

void Position::set_coor_x( int _x )	{

	//checking limits
	if ( !within_lim_min_x( _x ) )
	{
		coor.x = limits.min.x;
		return;
	}
	else if ( !within_lim_max_x( _x ) )
	{
		coor.x = limits.max.x-HERO_WIDTH;
		return;
	}

	coor.x = _x;
}

void Position::set_coor_y( double _y )	{

	//checking limits
	if ( !within_lim_min_y( _y ) )
	{
		coor.y = limits.min.y;
		return;
	}
	else if ( !within_lim_max_y( _y ) )
	{
		coor.y = limits.max.y - HERO_HIGHT;
		return;
	}

	coor.y = _y;
}

void Position::set_coor_z( int _z )	{

	//checking limits
	if ( !within_lim_min_z( _z ) )
	{
		++_z;
		return;
	}
	else if ( !within_lim_max_z( _z ) )
	{
		--_z;
		return;
	}

	coor.z = _z;
}

void Position::inc_coor_x( int _x ) {

	set_coor_x( coor.x + _x);
}

void Position::inc_coor_y( double _y ) {

	set_coor_y( coor.y + _y);
}

void Position::inc_coor_z( int _z ) {

	set_coor_z( coor.z + _z);
}

void Position::print() const {

	printf( "Coordinates: x: %d, y: %f, z: %d\n", coor.x, coor.y, coor.z );

}
