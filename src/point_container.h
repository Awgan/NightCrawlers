#ifndef POINT_CONTAINER_H_
#define POINT_CONTAINER_H_

#include <SDL2/SDL.h>

#include "point.h"

struct point_stru {

	point_stru * next;
	point_stru * prev;
	
	Point * thing;
	//OUT::SDL_Texture * texture;		//pointer for Point texture
	
};


class Point_Container {
	
	public:
		
		//friend bool Point::check_collision();
	
	private:

		int number_all;

		//3 diffrent subgroups for 3 diffrent point types
		point_stru * hero_first;
		point_stru * hero_last;
		int number_hero;
		
		Point * hero_active;
		int 	hero_active_numb;
		
		point_stru * bullet_first;
		point_stru * bullet_last;
		int number_bullet;
		
		point_stru * obstacle_first;
		point_stru * obstacle_last;
		int number_obstacle;

	protected:

	public:
		Point_Container();
		~Point_Container();
		
		bool add( Point * _p );
		bool del( Point * _p );
		
		bool add( Point && _p ); //under construction
		
		Point * select_hero ( SDL_Event & r_event );
		
		bool add_from_file ( const char * _f_name );
		
		
		Point * get_point_hero( const int numb );
		Point * get_active_hero()		{ return hero_active; }
		
		int get_active_hero_numb()		{ return hero_active_numb; }
		int get_number_hero() const		{ return number_hero;}
		
		
		Point * get_point_bullet( const int numb );
		int get_number_bullet() const	{ return number_bullet; }
		
		
		Point * get_point_obstacle( const int numb );
		int get_number_obstacle() const	{ return number_obstacle; }


		int get_number_all() const		{ return number_all; };


		bool collision_hero_with_hero();
		bool collision_hero_with_obstacle( Point * _p );
		bool collision_hero_with_bullet( Point * _p );
		bool collision_bullet_with_obstacle( Point * _p );
		
		
		void status_test();
		
		
		//friend bool Point::isCollision( Point_Container & pc ) ;
		//Point & operator[] (int i) {return this->;
};

#endif
