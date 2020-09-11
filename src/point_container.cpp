#include <stdlib.h>

#include "point_container.h"

Point_Container::Point_Container(){
	
	number_hero = 0;
	number_bullet = 0;	
	number_obstacle = 0;

	hero_first = NULL;
	hero_last = NULL;
	
	bullet_first = NULL;
	bullet_last = NULL;
	
	obstacle_first = NULL;
	obstacle_last= NULL;
	
}

Point_Container::~Point_Container(){
	
	point_stru * temp = NULL;
	
	for ( int i = 0; i < number_hero; i++ ) {
		temp = hero_first;
		hero_first = hero_first->next;
		delete temp;
		
		if ( hero_first == NULL ) break;
		
	}
	
	
}

bool Point_Container::add( Point * _p ){
		
	switch ( _p->get_type() ) {
		
		case Point_type::neutral:
		break;
		/**/
		case Point_type::hero: {
			
			point_stru * temp = new point_stru;
			
			/* cheking addresses 
			printf("%p\n",temp->thing);
			printf("%p\n",temp->next);
			printf("%p\n",temp->prev);
			*/
			
			if ( hero_first == NULL ) {
				
				hero_first = temp;				
				hero_last = hero_first;
				
				hero_first->next = NULL;
				hero_first->prev = NULL;
				
			} 
			else
			{
				hero_last->next = temp;
				temp->prev = hero_last;
				hero_last = temp;
				hero_last->next = NULL;
			}
			
			//project
				//Point * pp = new Point( _p);
			//end project
			
			temp->thing = _p; //todo::
			
			number_hero++;
				
		/**/
		break;
			}
		case Point_type::bullet:
		
		
		break;
		
		case Point_type::obstacle:
		break;
		
		default:
		break;
		
	}
	return 0;
}


bool Point_Container::del( Point * _p ) {
	
	point_stru * temp_stru = NULL;
	temp_stru = hero_first;
	
	Point * temp_thing = NULL;
	temp_thing = temp_stru->thing;
	
	
	for ( int i = 0; i < number_hero; i++ ) {
		
		if ( _p == temp_thing ) { //looking for Point to del
			
			point_stru * temp_del = temp_stru;
			
			if( temp_stru != hero_first ) {
				if ( temp_stru->next != NULL )
					temp_stru->next->prev = temp_stru->prev;
				
				temp_stru->prev->next = temp_stru->next; 
				
				delete temp_del;
				number_hero--;
				
				return true;
			} else { //temp_stru == hero_first
				
				if ( temp_stru->next != NULL ) {
					temp_stru->next->prev = NULL;
					hero_first = hero_first->next;
				}
				delete temp_del;
				number_hero--;
				
				return true;
			}
		} //end if
		
		//next structure if not found
		temp_stru = temp_stru->next;
		
		if ( temp_stru == NULL ) { 
			return false;
		} else {
			temp_thing = temp_stru->thing;
		}
		
	}
	 
	return false;
}


void Point_Container::status_test() {
	
	point_stru * temp = NULL;
	temp = hero_first;
	
	for( int j = 0; j < number_hero; j++ ) {
		
		printf("%d\t%p\n",j, temp);
		temp->thing->print_status();
		temp = temp->next;
		
	}	
	
	printf("\n***** status end *****\n\n");
}



