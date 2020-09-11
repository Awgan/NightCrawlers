#ifndef POSITION_H_
#define POSITION_H_

#include <stdlib.h>

#include "comm_const.h"

struct Coordinate {
	
	int x;
	int y;
	int z;
	
	enum Direction { right, up, left, down, deep, shallow };	
	
	Direction dir;	
	
};

typedef Coordinate::Direction	CoorDir;

struct Coord_Limits {
	
	Coordinate min;
	Coordinate max;
};




class Position {
	
	private:
		Coordinate coor;
		Coord_Limits limits;
		int offset;
			
	protected:
		bool within_lim_min( const int & _lim_min, const int & xyz );		
		bool within_lim_max( const int & _lim_max, const int & xyz );
		
	public:
		Position( int _x = 0, int _y = 0, int _z = 0, CoorDir _dir = Coordinate::up );
		Position( Coordinate & _coord );
		Position( const Position & _p ) {printf("Position DEF\n");}
		~Position() {};
		
		const Coordinate & get_coor() const		{ return coor; }
		const int & get_coor_x() const 			{ return coor.x; }
		const int & get_coor_y() const 			{ return coor.y; }
		const int & get_coor_z() const 			{ return coor.z; }
		
		const int * get_coor_x_p() const 			{ return &coor.x; }
		const int * get_coor_y_p() const 			{ return &coor.y; }
		const int * get_coor_z_p() const 			{ return &coor.z; }
		
		void set_coor( int _x, int _y, int _z = 0 );
		void set_coor_x( int _x );
		void set_coor_y( int _y );
		void set_coor_z( int _z );
		
		//add or sub value to/from coor
		void inc_coor_x( int _x );
		void inc_coor_y( int _y );
		void inc_coor_z( int _z );
		
		const CoorDir & get_direction() const 		{ return coor.dir; }
		
		void set_direction( const CoorDir & _dir ) 	{ coor.dir = _dir; }
		
		const Coord_Limits & get_lim()			{ return limits; }
		
		const int & get_lim_min_x()			{ return limits.min.x; }
		const int & get_lim_min_y()			{ return limits.min.y; }
		const int & get_lim_min_z()			{ return limits.min.z; }
		
		const int & get_lim_max_x()			{ return limits.max.x; }
		const int & get_lim_max_y()			{ return limits.max.y; }
		const int & get_lim_max_z()			{ return limits.max.z; }
		
		void set_lim_min( int _x, int _y, int _z = 0 )	{ limits.min = { _x, _y, _z }; }
		void set_lim_max( int _x, int _y, int _z = 0 )	{ limits.max = { _x, _y, _z }; }
		
		//offset is to know what is width of the object for not moving more than right edge of the monitor
		void set_offset( int _off ) { offset = _off; }
		
		void print() const;
};



#endif
