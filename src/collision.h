#ifndef COLLISION_H_
#define COLLISION_H_

#include "point.h"

class Collision {
	
	public:
	
		struct coll_dim {
			const int * x;
			const int * y;
			const int * w;
			const int * h;
		};
	
		struct coll_node {	
		
			coll_node * prev;
			coll_node * next;
				
			Point *	 	point;
			coll_dim	co_di;
		};		
		
	
	private:
		
		coll_node * first;
		coll_node * last;
		int number;
		
	protected:
	
	
	public:
		Collision();
		~Collision();
		
		void add( Point * _p );
	
		void check_collision();		//methode for using the class for every grph_object on the screen
		
		bool check_collision( const Collision & _coll );//prototype for using when there are separet class for each Point_type type

		void list_all() const;
		
};

#endif
