#ifndef POINT_H_
#define POINT_H_

#include <iostream>
#include <string>

#include "graph_prop.h"
#include "position.h"
#include "property.h"

class Point_Container;

class Point : public Position, public Property, public Graph_prop {

	protected:

		/* struct for calculating an object edges */
		struct point_borders {

			int * x;
			double * y;
			int * z;

			int * width;
			int * hight;
		};

	private:

		/* variable for setting constant move of the object; idea is to make one key pressing to run and one key releasing to stop */
		double const_move_x;
		double const_move_y;
		double const_move_z;		//parameter for 3D moving ;)

		point_borders borders;			//information about Point's graphic border

		Point_Container * pointCont;	//pointer to container where the Point is stored

		Point * collision_with;			//pointer to object which is collison with

		bool standing;					//information if the object is standing on something

	public:
		Point();
		Point( Coordinate _cord, Stru_property _prop, Stru_graph_prop & _gprop );
		Point( const Point & _p );
		~Point() ;

		Point ( Point && _p );

		void add_container( Point_Container * pc )	{ pointCont = pc; }

		void set_move_x( const int & _m) { const_move_x = _m; }
		void set_move_y( const double & _m) { const_move_y = _m; }
		void set_move_z( const int & _m) { const_move_z = _m; }

		void move_dx( int _dx );
		void move_dy( double _dy );
		void move_dz( int _dz );

		int get_move_x()	{ return const_move_x; }
		double get_move_y()	{ return const_move_y; }
		int get_move_z()	{ return const_move_z; }

		bool move();

		void push( Point * _p );//pushing object when there is collision

		bool isMoving();		//checking if an object has no zero const_move values

		bool isSelfMoving();	//checking if an object can move itself

		bool isStanding() { return standing; }

		void checkStanding();

		/* Functions for checking if points collide */
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

		Point & operator=( Point && _p ); //under construction

		bool operator == (const bool & b) {return true;}

};

#include "point_container.h"

#endif
