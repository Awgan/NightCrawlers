#include <stdlib.h>

#include "point_container.h"

Point_Container::Point_Container(){
	
	number_hero		= 0;
	number_bullet 	= 0;	
	number_obstacle = 0;

	hero_first 		= NULL;
	hero_last 		= NULL;
	hero_active		= NULL;
	hero_active_numb = 0;
	
	bullet_first 	= NULL;
	bullet_last 	= NULL;
	
	obstacle_first	 = NULL;
	obstacle_last	= NULL;
	
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
			temp->next = new point_stru;
			temp->prev = new point_stru;
			temp->thing = new Point;
						
			if ( hero_first == NULL ) {
				
				hero_first = temp;				
				hero_last = hero_first;
				
				hero_first->next = NULL;
				hero_first->prev = NULL;
				
				hero_active = hero_first->thing;
				hero_active_numb = 0;
			} 
			else
			{
				hero_last->next = temp;
				temp->prev = hero_last;
				hero_last = temp;
				hero_last->next = NULL;
				
			}
				
			*(temp->thing) = *_p;
			//temp->thing = _p;
			temp->thing->add_container( this );
			
			printf("\nbool Point_Container::add( Point * _p )");
			temp->thing->print_borders();
			
			number_hero++;

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

Point * Point_Container::get_point_hero( const int numb ) { 
	//not finish
	
	if ( numb >= 0 && numb < number_hero ) {
		
		point_stru	* temp = hero_first;
		
		for( int i = 0; i < numb; ++i ) {
			
			temp = temp->next;			
		}			
		
		return temp->thing;		
	}
	
return NULL;
}

bool Point_Container::collision_hero_with_hero() {
		
	for ( int i = 0; i < number_hero; ++i ) {
		
		if ( (hero_active != get_point_hero(i)) && hero_active->isCollision( get_point_hero(i) ) ) {
			printf("\nCollision!#	number: %d	hit number: %d \n", get_active_hero_numb(), i );
			return true;
		}		
	}
	return false;
}

Point * Point_Container::select_hero ( SDL_Event & r_event ) {
		
		if ( r_event.button.button == SDL_BUTTON_LEFT ) {
			int ms_x, ms_y;
			ms_x = r_event.button.x;
			ms_y = r_event.button.y;
			
			for ( int i = 0; i < number_hero; ++i ) {
				
				if ( 	ms_x >= get_point_hero( i )->get_coor_x() && ms_x <= get_point_hero( i )->get_coor_x() + get_point_hero( i )->get_graph_width() &&
						ms_y >= get_point_hero( i )->get_coor_y() && ms_y <= get_point_hero( i )->get_coor_y() + get_point_hero( i )->get_graph_hight()	) {
					
					hero_active_numb = i;
					hero_active = get_point_hero( i );
						
					return hero_active;
				}
			}
		}
		return hero_active;		
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



