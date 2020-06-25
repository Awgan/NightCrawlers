#ifndef POINT_H_
#define POINT_H_


#include "graph_prop.h"
#include "position.h"
#include "property.h"

class Point : public Position, public Property, public Graph_prop {
	
	private:
	
	protected:
	
	public:
		Point( );
		~Point() {};
		
		void move_dx( int _dx );
		void move_dy( int _dy );
		void move_dz( int _dz );
		
		//Function for checking if points collide
		//void check_collision(); ???
		
		
		void print_status() const;
	
};

#endif
