#include <cstdio>
#include <iostream>

#include "comm_const.h"
#include "position.h"

void Coordinate::show() {
	
	std::cout << "COORDINATE show() > x: " << x << " y: " << y << " z: " << z << " dir: " << (int)dir << std::endl;
	
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


Position::Position ( int _x, int _y, int _z, CoorDir _dir ) {
	
	limits.min = { 0, 0, 0 };
	limits.max = { WIN_WIDTH, WIN_HIGHT, 0 };
	
	if ( _x >= limits.min.x && _x <= limits.max.x )
		coor.x = _x;
	else {
		
		if ( _x <= limits.min.x )
			coor.x = limits.min.x;
		if ( _x >= limits.max.x )
			coor.x = limits.max.x;
	}
	
	if ( _y >= limits.min.y && _y <= limits.max.y )
		coor.y = _y;
	else {
		
		if ( _y <= limits.min.y )
			coor.y = limits.min.y;
		if ( _y >= limits.max.y )
			coor.y= limits.max.y;
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
	
	offset = 0;
	
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
			coor.x = limits.max.x;
	}
	
	if ( _coord.y >= limits.min.y && _coord.y <= limits.max.y )
		coor.y = _coord.y;
	else {
		
		if ( _coord.y <= limits.min.y )
			coor.y = limits.min.y;
		if ( _coord.y >= limits.max.y )
			coor.y= limits.max.y;
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
	
	offset = 0;	
}

bool Position::within_lim_min( const int & _lim_min, const int & xyz ) {
	
	return ( xyz >= _lim_min );
}

bool Position::within_lim_max( const int & _lim_max, const int & xyz ) {
	
	return ( xyz <= _lim_max - offset );
}

void Position::set_coor( int _x, int _y, int _z ) { 
	
	//checking limits
	if ( within_lim_min( limits.min.x, _x ) && within_lim_min( limits.min.y, _y ) && within_lim_min( limits.min.z, _z )
	&& within_lim_max( limits.max.x, _x ) && within_lim_max( limits.max.y, _y ) && within_lim_max( limits.max.z, _z ) ) {
		
		coor = { _x, _y, _z }; 
	}
}
void Position::set_coor_x( int _x )	{ 
	
	//checking limits
	if ( within_lim_min( limits.min.x, _x ) && within_lim_max( limits.max.x, _x ) ) {
		
		coor.x = _x;
	}
}

void Position::set_coor_y( int _y )	{ 
	
	//checking limits
	if ( within_lim_min( limits.min.y, _y ) && within_lim_max( limits.max.y, _y ) ) {
		
		coor.y = _y;
	}
}

void Position::set_coor_z( int _z )	{ 
	
	//checking limits
	if ( within_lim_min( limits.min.z, _z ) && within_lim_max( limits.max.z, _z ) ) {
		
		coor.z = _z;
	}
}

void Position::inc_coor_x( int _x ) {
	
	set_coor_x( coor.x + _x);
}

void Position::inc_coor_y( int _y ) {
	
	set_coor_y( coor.y + _y);
}

void Position::inc_coor_z( int _z ) {
	
	set_coor_z( coor.z + _z);
}


void Position::print() const {
	
	printf( "Coordinates: x: %d, y: %d, z: %d\n", coor.x, coor.y, coor.z );
	
}
