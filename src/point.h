#ifndef POINT_H_
#define POINT_H_

#include "graph_prop.h"
#include "position.h"

#include "property.h"

class Point : public Position, public Property, public Graph_prop {
	
	private:
		//variable for setting constant move of the object; idea is to make one key pressing to run and one key releasing to stop
		int const_move_x;
		int const_move_y;
		int const_move_z;
		
		
	protected:
	
	public:
		Point ();
		Point( Coordinate _cord, Stru_property _prop, Stru_graph_prop _gprop );
		Point( const Point & _p );
		~Point() ;	
		
		void set_move_x( const int & _m) { const_move_x = _m; }
		void set_move_y( const int & _m) { const_move_y = _m; }
		void set_move_z( const int & _m) { const_move_z = _m; }
		
		void move_dx( int _dx );
		void move_dy( int _dy );
		void move_dz( int _dz );
				
		bool move();
		
		//Function for checking if points collide
		bool check_collision();
		
		const Point_type & get_type() { return get_point_type(); }
		
		void print_status();
		
		//Point & operator=( const Point & _p );
	
};

#endif
