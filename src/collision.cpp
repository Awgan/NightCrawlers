#include "collision.h"

Collision::Collision(){
	
	first = last = NULL;
	number = 0;
	
}

Collision::~Collision() { 
printf("del1\n");
	coll_node * temp = NULL;
	
	while ( first != NULL ) {
		temp = first;
			
		first = first->next;
			
		delete temp;
		
		number--;
	}
	
	

}

void Collision::add( Point * _p ) {
	
	coll_node * add = new coll_node;

	add->next = NULL;
	add->point = _p;
	number++;

	add->co_di.x = add->point->get_coor_x_p();
	add->co_di.y = add->point->get_coor_y_p();
	add->co_di.w = add->point->get_graph_widht_p();
	add->co_di.h = add->point->get_graph_hight_p();

	if ( first == NULL ) {
		printf("x3\n");
		
		add->prev = NULL;
		first = add;
		last = add;

	}
	else {
		printf("x4\n");
		
		last->next = add;
		add->prev = last;
		last = add;
		

	}
}

void Collision::check_collision() { //sprawdzenie kolizji
	//wskazanie obiektu kolidującego
	//usunięcie wskazanego obiektu.
	
	coll_node * f1 = first;
	coll_node * f2 = first;
	
	int rightA, topA, leftA, bottomA;
	int rightB, topB, leftB, bottomB;
	
	for ( int i = 0; i < number; i++ ) {
		
		if ( f1->point->get_point_type() != Point_type::bullet ) {
			f1 = f1->next;
			continue;}
		printf("Bullet\n");
		leftA = *f1->co_di.x;
		topA = *f1->co_di.y;
		rightA = leftA + *f1->co_di.w;
		bottomA = topA + *f1->co_di.h;
		
		f2 = first;
		for ( int j = 0; j < number; j++ ) {
			printf("%d Checking...\n", j);
			
			
			if ( f1->point->get_point_type() == f2->point->get_point_type() ) {
				f2 = f2->next;
				printf("Not type\n");
				continue;
			}
			
			leftB = *f2->co_di.x;			
			topB = *f2->co_di.y;			
			rightB = leftB + *f2->co_di.w;			
			bottomB = topB + *f2->co_di.h;			
				
				
			if ( rightA < leftB ) {
				f2 = f2->next;
				printf("Not right\n");
				continue;
				
			}
			if ( leftA > rightB ) {
				f2 = f2->next;
				printf("Not left\n");
				continue;
			}
			if ( bottomA < topB ) {
				f2 = f2->next;
				printf("Not bottom\n");
				continue;
			}
			if ( topA > bottomB ) {
				f2 = f2->next;
				printf("Not top\n");
				continue;
			}
			
			//#
			//#f: erase object
			//#
			printf("Hit !\n");
			coll_node * temp; temp = f2;
			f2->point->set_visible( false );
			
			if ( f2 == first ) {
				first = first->next;
				first->prev = NULL;
				printf("Hit1 !\n");
			}
			else if ( f2 == last ) {
				last = last->prev;
				last->next = NULL;
				printf("Hit2 !\n");
			}
			else {
				f2->prev->next = f2->next;
				f2->next->prev = f2->prev;
				printf("Hit3 !\n");	
				
			}
			
			number--;
			j--;			
			
			f2 = f2->next;
			delete temp;
			
			list_all();
		}
		f1 = f1->next;
	}
		
}

bool Collision::check_collision( const Collision & _coll ){ return false;};


void Collision::list_all() const {
	coll_node * f1 = NULL;
	f1 = first;
	for ( int i = 0 ; i < number; i++ ) {
		
		printf("%d	--> %p\n", i, f1);
		printf("%p\n", f1->point);
		if ( f1->next != NULL )
			f1 = f1->next;
		
	}
}
		



