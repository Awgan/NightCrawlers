
#include <iostream>
#include <stdlib.h>

#include "point_container.h"


Point_Container::Point_Container(){

	number_hero		= 0;
	number_bullet 	= 0;
	number_obstacle = 0;
	number_all = 0;

	hero_first 		= nullptr;
	hero_last 		= nullptr;
	hero_active		= nullptr;
	hero_active_numb = 0;

	bullet_first 	= nullptr;
	bullet_last 	= nullptr;

	obstacle_first	= nullptr;
	obstacle_last	= nullptr;

}

Point_Container::~Point_Container(){

	point_stru * temp = nullptr;

	for ( int i = 0; i < number_hero; i++ ) {
		temp = hero_first;
		hero_first = hero_first->next;
		delete temp;

		if ( hero_first == nullptr ) break;

	}
	number_hero = 0;

	for ( int i = 0; i < number_obstacle; i++ ) {
		temp = obstacle_first;
		obstacle_first = obstacle_first->next;
		delete temp;

		if ( obstacle_first == nullptr ) break;

	}
	number_obstacle = 0;


	number_all = 0;
}

bool Point_Container::add( Point * _p ){

//std::cout << "Point_Container::add( Point * _p )\n";
	if ( _p->isCollision( *this ) )
		return false;

	switch ( _p->get_type() ) {

		case Point_type::neutral:
		break;
		/**/
		case Point_type::hero: {

			point_stru * temp = new point_stru;
			//temp->next = new point_stru;
			//temp->prev = new point_stru;
			temp->thing = new Point;

			if ( hero_first == nullptr ) {

				hero_first = temp;
				hero_last = hero_first;

				hero_first->next = nullptr;
				hero_first->prev = nullptr;

				hero_active = hero_first->thing;
				hero_active_numb = 0;
			}
			else
			{
				hero_last->next = temp;
				temp->prev = hero_last;
				hero_last = temp;
				hero_last->next = nullptr;

			}

			*(temp->thing) = *_p;
			//temp->thing = _p;

			temp->thing->add_container( this );

			//temp->thing->print_borders();

			++number_hero;
			++number_all;

			break;
		}

		case Point_type::bullet: {

			point_stru * temp = new point_stru;
			//temp->next = new point_stru;
			//temp->prev = new point_stru;
			temp->thing = new Point;

			if ( bullet_first == nullptr ) {

				bullet_first = temp;
				bullet_last = bullet_first;

				bullet_first->next = nullptr;
				bullet_first->prev = nullptr;

			}
			else
			{
				bullet_last->next = temp;
				temp->prev = bullet_last;
				bullet_last = temp;
				bullet_last->next = nullptr;

			}

			*(temp->thing) = *_p;
			//temp->thing = _p;

			temp->thing->add_container( this );

			//temp->thing->print_borders();

			++number_bullet;
			++number_all;
			/*std::cout << "\nPoint_Container::add( Point * _p ) => " <<
			"\nprev address: " << bullet_last->prev <<
			"\nthis address: " << bullet_last <<
			"\nnext address: " << bullet_last->next <<
			"\nbullet numebr/all: " << number_bullet << '/' << number_all << "\n\n";*/

			break;
		}
		case Point_type::obstacle:	{

			point_stru * temp = new point_stru;
			//temp->next = new point_stru;
			//temp->prev = new point_stru;
			temp->thing = new Point;

			if ( obstacle_first == nullptr ) {

				obstacle_first = temp;
				obstacle_last = obstacle_first;

				obstacle_first->next = nullptr;
				obstacle_first->prev = nullptr;

				//hero_active = hero_first->thing; 	---> there is no similar variable for obstacle, but maybe should be
				//hero_active_numb = 0;				---> there is no similar variable for obstacle, but maybe should be
			}
			else
			{
				obstacle_last->next = temp;
				temp->prev = obstacle_last;
				obstacle_last = temp;
				obstacle_last->next = nullptr;

			}

			*(temp->thing) = *_p;
			//temp->thing = _p;

			temp->thing->add_container( this );

			//temp->thing->print_borders();

			++number_obstacle;
			++number_all;
			/*std::cout << "Point_Container::add( Point * _p ) => " << "address: " << obstacle_last <<
			"\tobstacle numebr/all: " << number_obstacle << '/' << number_all << '\n';*/
			break;
		}

		default:
			break;

	}

	return true;
}


bool Point_Container::add( Point && _p ){

//std::cout << "bool Point_Container::add( Point && _p )\n";

	switch ( _p.get_type() ) {

		case Point_type::neutral:
		break;
		/**/
		case Point_type::hero: {

			point_stru * temp = new point_stru;
			//temp->next = new point_stru;
			//temp->prev = new point_stru;
			temp->thing = new Point;

			if ( hero_first == nullptr ) {

				hero_first = temp;
				hero_last = hero_first;

				hero_first->next = nullptr;
				hero_first->prev = nullptr;

				hero_active = hero_first->thing;
				hero_active_numb = 0;
			}
			else
			{
				hero_last->next = temp;
				temp->prev = hero_last;
				hero_last = temp;
				hero_last->next = nullptr;

			}

			*(temp->thing) = _p;
			//temp->thing = _p;

			temp->thing->add_container( this );

			//temp->thing->print_borders();

			++number_hero;
			++number_all;

			break;
		}
		case Point_type::bullet: {

			point_stru * temp = new point_stru;
			//temp->next = new point_stru;
			//temp->prev = new point_stru;
			temp->thing = new Point;

			if ( bullet_first == nullptr )
			{

				bullet_first = temp;
				bullet_last = bullet_first;

				bullet_first->next = nullptr;
				bullet_first->prev = nullptr;

				//hero_active = hero_first->thing; 	---> there is no similar variable for obstacle, but maybe should be
				//hero_active_numb = 0;				---> there is no similar variable for obstacle, but maybe should be
			}
			else
			{
				bullet_last->next = temp;
				temp->prev = bullet_last;
				bullet_last = temp;
				bullet_last->next = nullptr;

			}

			*(temp->thing) = _p;
			//temp->thing = _p;

			temp->thing->add_container( this );

			//temp->thing->print_borders();

			++number_bullet;
			++number_all;
			/*std::cout << "Point_Container::add( Point * _p )\n" << "address: " << bullet_last->thing <<
			"\tbullet numebr/all: " << number_bullet << '/' << number_all << '\n';*/

			break;
		}

		case Point_type::obstacle:	{

			point_stru * temp = new point_stru;
			//temp->next = new point_stru;
			//temp->prev = new point_stru;
			temp->thing = new Point;

			if ( obstacle_first == nullptr ) {

				obstacle_first = temp;
				obstacle_last = obstacle_first;

				obstacle_first->next = nullptr;
				obstacle_first->prev = nullptr;

				//hero_active = hero_first->thing; 	---> there is no similar variable for obstacle, but maybe should be
				//hero_active_numb = 0;				---> there is no similar variable for obstacle, but maybe should be
			}
			else
			{
				obstacle_last->next = temp;
				temp->prev = obstacle_last;
				obstacle_last = temp;
				obstacle_last->next = nullptr;

			}

			*(temp->thing) = _p;
			//temp->thing = _p;

			temp->thing->add_container( this );

			//temp->thing->print_borders();

			number_obstacle++;
			number_all++;

			break;
		}
		default:
			break;

	}

	return 0;
}



bool Point_Container::del( Point * _p )
{

//std::cout << "Point_Container::del( Point * _p )\n";
	Point_type type = _p->get_point_type();

	point_stru * temp_stru = nullptr;
	Point * temp_thing = nullptr;

	switch( type )
	{
		case neutral:
		{

		}
		break;

		case hero:
		{
			temp_stru = hero_first;
			temp_thing = temp_stru->thing;

			for ( int i = 0; i < number_hero; i++ )
			{
				/* Looking for point */
				if ( _p == temp_thing )
				{
					point_stru * temp_del = temp_stru;

					if( temp_stru != hero_first )
					{

						if ( temp_stru != hero_last )
						{
							temp_stru->next->prev = temp_stru->prev;
							temp_stru->prev->next = temp_stru->next;
						}
						else
						{
							hero_last = hero_last->prev;
							hero_last->next = nullptr;
						}

						delete temp_del->thing;
						delete temp_del;
						--number_hero;
						--number_all;

						return true;

					}
					else //temp_stru == hero_first
					{
						if ( temp_stru->next != nullptr )
						{
							hero_first = hero_first->next;
							hero_first->prev = nullptr;
						}

						delete temp_del->thing;
						delete temp_del;
						--number_hero;
						--number_all;

						if ( number_hero== 0 )
						{
							hero_first = nullptr;
						}

						return true;
					}
				}

				/* Next structure if no found */
				temp_stru = temp_stru->next;

				if ( temp_stru == nullptr )
				{		std::cout << "Point_Container::del( Point * _p ) => next not found\n";
					return false;
				}
				else
				{
					temp_thing = temp_stru->thing;
				}
			}
		}
		break;

		case bullet:
		{
			temp_stru = bullet_first;
			temp_thing = temp_stru->thing;

			for ( int i = 0; i < number_bullet; ++i )
			{
				/* Looking for point */
				if ( _p == temp_thing )
				{
					//std::cout << "Point_Container::del() ==> bullet delete number: " << i << '\n';
					point_stru * temp_del = temp_stru;

					if( temp_stru != bullet_first )
					{
						//std::cout<<"\nbullet not first :: BEFORE\n";
						//list_points_test();

						if ( temp_stru != bullet_last )
						{
							temp_stru->next->prev = temp_stru->prev;
							temp_stru->prev->next = temp_stru->next;
						}
						else
						{
							std::cout<<"bullet last\n";
							bullet_last = bullet_last->prev;
							bullet_last->next = nullptr;
						}



						delete temp_del->thing;
						delete temp_del;
						--number_bullet;
						--number_all;

						//std::cout<<"bullet not first :: AFTER\n";
						list_points_test();

						return true;

					}
					else //temp_stru == bullet_first
					{
						//std::cout<<"\nbullet first :: BEFORE\n";
						//list_points_test();

						if ( temp_stru->next != nullptr )
						{
							bullet_first = bullet_first->next;
							bullet_first->prev = nullptr;
						}

						delete temp_del->thing;
						delete temp_del;
						--number_bullet;
						--number_all;

						if ( number_bullet == 0 )
						{
							bullet_first = nullptr;
						}
//std::cout<<"bullet delete2\n";
						//std::cout<<"bullet first :: AFTER\n";
						//list_points_test();

						return true;
					}
				}

				/* Next structure if no found */
				temp_stru = temp_stru->next;

				if ( temp_stru == nullptr )
				{
					//std::cout << "Point_Container::del( Point * _p ) => END. Bullet not found\n";
					return false;
				}
				else
				{
					temp_thing = temp_stru->thing;
				}
			}
		}
		break;

		case obstacle:
		{
			temp_stru = obstacle_first;
			temp_thing = temp_stru->thing;

			for ( int i = 0; i < number_obstacle; i++ )
			{
				/* Looking for point */
				if ( _p == temp_thing )
				{
					point_stru * temp_del = temp_stru;

					if( temp_stru != obstacle_first )
					{
						if ( temp_stru != obstacle_last )
						{
							temp_stru->next->prev = temp_stru->prev;
							temp_stru->prev->next = temp_stru->next;
						}
						else
						{
							obstacle_last = obstacle_last->prev;
							obstacle_last->next = nullptr;
						}

						delete temp_del;
						--number_obstacle;
						--number_all;
//std::cout<<"obstacle delete\n";
						return true;

					}
					else //temp_stru == obstacle_first
					{
						if ( temp_stru->next != nullptr )
						{
							obstacle_first = obstacle_first->next;
							obstacle_first->prev = nullptr;
						}

						delete temp_del;
						--number_obstacle;
						--number_all;

						if ( number_obstacle == 0 )
						{
							obstacle_first = nullptr;
						}

						return true;
					}
				}

				/* Next structure if no found */
				temp_stru = temp_stru->next;

				if ( temp_stru == nullptr )
				{	//std::cout << "Point_Container::del( Point * _p ) => END. Obstacle not found\n";
					return false;
				}
				else
				{
					temp_thing = temp_stru->thing;
				}
			}
		}
		break;

		default:
		break;
	}

return false;
}

Point * Point_Container::get_point_hero( const int numb ) {
	//not finished

	if ( numb >= 0 && numb < number_hero ) {

		point_stru	* temp = hero_first;

		for( int i = 0; i < numb; ++i ) {

			temp = temp->next;
		}
		if ( temp == nullptr ) {
			//std::cout << "error: no HERO object\n";
		}
		return temp->thing;
	}

return nullptr;
}

Point * Point_Container::get_point_bullet( const int numb )
{

	if ( numb >= 0 && numb < number_bullet )
	{
		point_stru	* temp = bullet_first;

		for( int i = 0; i < numb; ++i )
		{
			temp = temp->next;
		}

		if ( temp == nullptr )
		{
			std::cout << "for no.: " << numb << " is error: no BULLET object\n";
			return nullptr;
		}
		return temp->thing;
	}

return nullptr;
}

Point * Point_Container::get_point_obstacle( const int numb ) {
////std::cout << "Point_Container::get_point_obstacle\n";
	if ( numb >= 0 && numb < number_obstacle ) {
////std::cout << "Point_Container::get_point_obstacle 1\n";
		point_stru	* temp = obstacle_first;

		for( int i = 0; i < numb; ++i ) {

			temp = temp->next;
		}
		if ( temp == nullptr ) {
			//std::cout << "error: no OBSTACLE object\n";
		}
		////std::cout << "Point_Container::get_point_obstacle 2\n";
		return temp->thing;
	}

return nullptr;
}

bool Point_Container::collision_hero_with_hero() {

	for ( int i = 0; i < number_hero; ++i ) {

		if ( (hero_active != get_point_hero(i)) && hero_active->isCollision( get_point_hero(i)) ) {

			return true;
		}
	}
	return false;
}

bool Point_Container::collision_hero_with_obstacle( Point * _p ) {

	for ( int i = 0; i < number_obstacle; ++i ) {

		if ( hero_active->isCollision( get_point_obstacle(i)) ) {

			return true;
		}
	}
	return false;
}


/*
bool collision_hero_with_bullet( Point * _p );
bool collision_bullet_with_obstacle( Point * _p );
*/

Point * Point_Container::select_hero ( SDL_Event & r_event ) {

		if ( r_event.button.button == SDL_BUTTON_LEFT ) {
			int ms_x, ms_y;
			ms_x = r_event.button.x;
			ms_y = r_event.button.y;

			for ( int i = 0; i < number_hero; ++i ) {

				if ( 	ms_x >= get_point_hero( i )->get_coor_x() && ms_x <= get_point_hero( i )->get_coor_x() + get_point_hero( i )->get_graph_width() &&
						ms_y >= get_point_hero( i )->get_coor_y() && ms_y <= get_point_hero( i )->get_coor_y() + get_point_hero( i )->get_graph_height()	) {

					hero_active_numb = i;
					hero_active = get_point_hero( i );

					return hero_active;
				}
			}
		}
		return hero_active;
	}

void Point_Container::status_test() {

	point_stru * temp = nullptr;
	temp = hero_first;

	for( int j = 0; j < number_hero; j++ ) {

		printf("%d\t%p\n",j, temp);
		temp->thing->print_status();
		temp = temp->next;

	}

	printf("\n***** status end *****\n\n");
}

void Point_Container::list_points_test()
{
	std::cout << "Point Container List:\n\n";

	std::cout << "Hero point list:\n";
	int i = 0;
	point_stru * temp = hero_first;

	for ( i = 0; i < number_hero; ++i )
	{
		std::cout << "\tHero no: " << i << " : " << temp << std::endl;
		temp = temp->next;
	}
	std::cout << "\tHero no: " << i << " : " << temp << std::endl;


	std::cout << "Bullet point list:\n";
	temp = bullet_first;
	for ( i = 0; i < number_bullet; ++i )
	{
		std::cout << "\tBullet no: " << i << " : " << temp << std::endl;
		temp = temp->next;
	}
	std::cout << "\tBullet no: " << i << " : " << temp << std::endl;


	std::cout << "Obstacle point list:\n";
	temp = obstacle_first;
	for ( i = 0; i < number_obstacle; ++i )
	{
		std::cout << "\tObstacle no: " << i << " : " << temp << std::endl;
		temp=temp->next;
	}
	std::cout << "\tObstacle no: " << i << " : " << temp << std::endl;

}

