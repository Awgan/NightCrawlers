#ifndef POINT_CONTAINER_H_
#define POINT_CONTAINER_H_


#include "point.h"

struct point_stru {

	point_stru * next;
	point_stru * prev;
	
	Point * thing;
};

class Point_Container {
	
	public:
		
		friend bool Point::check_collision();
	
	private:
		int number_hero;
		int number_bullet;	
		int number_obstacle;

		//3 diffrent subgroups for 3 diffrent point types
		point_stru * hero_first;
		point_stru * hero_last;
		
		point_stru * bullet_first;
		point_stru * bullet_last;
		
		point_stru * obstacle_first;
		point_stru * obstacle_last;

	protected:

	public:
		Point_Container();
		~Point_Container();
		
		bool add( Point * _p );
		bool del( Point * _p );
		
		bool add_from_file ( const char * _f_name );
		
		bool collision_hero_with_obstacle( Point * _p );
		bool collision_hero_with_bullet( Point * _p );
		bool collision_bullet_with_obstacle( Point * _p );
		
		void status_test();
		

};

#endif
