#ifndef POINT_H_
#define POINT_H_

#include <string>

#include "graph_prop.h"
#include "position.h"
#include "property.h"

class Point_Container;

class Point : public Position, public Property, public Graph_prop {
	
	protected:
		
		struct point_borders {
			
			int * x;
			int * y;
			int * z;
			
			int * width;
			int * hight;		
		};
	
	private:
		//variable for setting constant move of the object; idea is to make one key pressing to run and one key releasing to stop
		int const_move_x;
		int const_move_y;
		int const_move_z;
		
		point_borders borders;			//information about Point's graphic border
		
		Point_Container * pointCont;	//pointer to container where the Point is stored
		
		Point * collision_with;			//poiter to object with which is collison
		
	public:
		Point();
		Point( Coordinate _cord, Stru_property _prop, Stru_graph_prop & _gprop );
		Point( const Point & _p );
		~Point() ;	
		
		void add_container( Point_Container * pc )	{ pointCont = pc; }
		
		void set_move_x( const int & _m) { const_move_x = _m; }
		void set_move_y( const int & _m) { const_move_y = _m; }
		void set_move_z( const int & _m) { const_move_z = _m; }
				
		void move_dx( int _dx );
		void move_dy( int _dy );
		void move_dz( int _dz );
		
		int get_move_x()	{ return const_move_x; }
		int get_move_y()	{ return const_move_y; }
		int get_move_z()	{ return const_move_z; }
		
		bool move();
		
		bool isMoving();
		
		//Function for checking if points collide
		bool isCollision( Point * secPoint );
		bool isCollision( Point_Container & pc );
		
		void set_collision_with( Point * cw )	{ collision_with = cw; }
		void reset_collision_with()				{ collision_with = nullptr;; }
		Point * get_collision_with()			{ return collision_with; }
		
		const Point_type & get_type() { return get_point_type(); }
		
		void print_status();
		
		const std::string print_info();
		
		void print_borders();
		
		Point & operator=( const Point & _p );
	
};

#endif
