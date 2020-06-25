#ifndef POINT_CONTAINER_H_
#define POINT_CONTAINER_H_


#include "point.h"

class Point_Container {

	private:
		int number;
		
		//there will be 3 diffrent subgroups for 3 diffrent point types
		Point * hero_first;
		Point * bullet_first;
		Point * obstacle_first;

	protected:

	public:
		Point_Container();
		~Point_Container();
		
		void add( Point _p );
		
		

};

#endif
