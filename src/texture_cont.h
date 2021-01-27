#ifndef TEXTURE_CONT_H_
#define TEXTURE_CONT_H_

#include <SDL2/SDL.h>

#include "comm_const.h"
#include "point.h"



struct Text_Objt
{

	Text_Objt * next;
	Text_Objt * prev;

	SDL_Texture * sdl_tex;

	Point_type p_type;

	Text_Objt & operator=( const Text_Objt & _to );

	Text_Objt & operator=( Text_Objt && _to );

	SDL_Texture * operator[]( int i );

	void print();
};

//DRAFT
/*struct Rect_Objt
{
	Rect_Objt * next;
	Rect_Objt * prev;

	SDL_Rect * sdl_rect;

	Point_type p_type;

};*/
//



/* Texture Container class */
template< typename T >
class Text_Cont
{
	private:

		SDL_Renderer * rend;

		T * hero_head;
		T * hero_tail;
		int hero_count;

		T * bullet_head;
		T * bullet_tail;
		int bullet_count;

		T * obstacle_head;
		T * obstacle_tail;
		int obstacle_count;


	protected:


	public:

		Text_Cont( SDL_Renderer * _rend = nullptr );
		Text_Cont( const Text_Cont & _tc );
		Text_Cont( Text_Cont && _tc );
		~Text_Cont();

		bool add( const Point & _pt );
		bool add( const Point * _pt );

		bool del( const Point * _pt, const int numb );

		Text_Cont & operator=( const Text_Cont & _tc );
		Text_Cont & operator=( Text_Cont && _tc );

		SDL_Texture * get_texture_hero( int i );
		SDL_Texture * get_texture_bullet( int i );
		SDL_Texture * get_texture_obstacle( int i );

		SDL_Texture * get_texture( int i );

		void print();
		bool test();

};

template< typename T >
Text_Cont< T >::Text_Cont( SDL_Renderer * _rend ) : rend(_rend), hero_head(nullptr), hero_tail(nullptr),
													bullet_head(nullptr), bullet_tail(nullptr),
													obstacle_head(nullptr), obstacle_tail(nullptr)
{
	hero_count = 0;
	bullet_count = 0;
	obstacle_count = 0;
}

template< typename T >
Text_Cont< T >::Text_Cont( const Text_Cont & _tc ) : rend( _tc.rend ), hero_head( _tc.hero_head ), hero_tail( _tc.hero_tail ),
														bullet_head( _tc.bullet_head ), bullet_tail( _tc.bullet_tail ),
														obstacle_head( _tc.obstacle_head ),obstacle_tail( _tc.obstacle_tail )
{
	hero_count = _tc.hero_count;
	bullet_count = _tc.bullet_count;
	obstacle_count = _tc.obstacle_count;
}

template< typename T >
Text_Cont< T >::Text_Cont( Text_Cont && _tc )
{
	rend = _tc.rend;
	_tc.rend = nullptr;

	hero_head = _tc.hero_head;
	_tc.hero_head = nullptr;

	hero_tail = _tc.hero_tail;
	_tc.hero_tail = nullptr;

	bullet_head = _tc.bullet_head;
	_tc.bullet_head = nullptr;

	bullet_tail = _tc.bullet_tail;
	_tc.bullet_tail = nullptr;

	obstacle_head = _tc.obstacle_head;
	_tc.obstacle_head = nullptr;

	obstacle_tail = _tc.obstacle_tail;
	_tc.obstacle_tail = nullptr;

	hero_count = _tc.hero_count;
	obstacle_count = _tc.obstacle_count;
}

template< typename T >
Text_Cont< T >::~Text_Cont()
{
	T * temp;
	for( T * h = hero_head; h != nullptr; )
	{
		temp = h;
		h = h->next;
		delete temp;
	}

	for( T * b = bullet_head; b != nullptr; )
	{
		temp = b;
		b = b->next;
		delete temp;
	}

	for( T * o = obstacle_head; o != nullptr; )
	{
		temp = o;
		o = o->next;
		delete temp;
	}
}

template< typename T >
bool Text_Cont< T >::add( const Point & _pt )
{

	T * temp = new ( T );



/* creating new node */
	switch ( _pt.get_point_type() )
	{

//neutral
		case neutral:
		break;

//hero
		case hero:
		{
			if ( hero_head == nullptr )
			{
				temp->p_type = _pt.get_point_type();

				temp->prev = nullptr;
				temp->next = nullptr;

				hero_head = temp;
				hero_tail = temp;

			}
			else
			{
				temp->p_type = _pt.get_point_type();

				temp->prev = hero_tail;
				temp->prev->next = temp;

				temp->next = nullptr;

				hero_tail = temp;

			}
			hero_count++;
		}

		break;

//bullet
		case bullet:
		{
			if ( bullet_head == nullptr )
			{
				temp->p_type = _pt.get_point_type();

				temp->prev = nullptr;
				temp->next = nullptr;

				bullet_head = temp;
				bullet_tail = temp;

			}
			else
			{
				temp->p_type = _pt.get_point_type();

				temp->prev = bullet_tail;
				temp->prev->next = temp;

				temp->next = nullptr;

				bullet_tail = temp;

			}
			bullet_count++;
		}
		break;


//obstacle
		case obstacle:
		{
			if ( obstacle_head == nullptr )
			{
				temp->p_type = _pt.get_point_type();

				temp->prev = nullptr;
				temp->next = nullptr;

				obstacle_head = temp;
				obstacle_tail = temp;

			}
			else
			{
				temp->p_type = _pt.get_point_type();

				temp->prev = obstacle_tail;
				temp->prev->next = temp;

				temp->next = nullptr;

				obstacle_tail = temp;

			}
			obstacle_count++;
		}
		break;

		default:
		break;
	}



/* adding SDL_Texture to Text_Objt object */

	SDL_Surface * surf;

	surf = SDL_LoadBMP( _pt.get_graph_sprite().c_str() );

	if ( surf == nullptr ) {
			printf("Error: there is no surf object; surf == NULL. Function 'texture_cont.h::add' terminated\n");
			return false;
		}

//changing texture background
	if ( BACKGROUND != 1 )
		SDL_SetColorKey( surf, SDL_TRUE, SDL_MapRGB( surf->format, 255, 0, 255 ) );


//adding texture
	SDL_Texture * temp_text = SDL_CreateTextureFromSurface( rend, surf );


	switch ( _pt.get_point_type() )
	{

//neutral
		case neutral:
		break;

//hero
		case hero:
			hero_tail->sdl_tex = temp_text;
		break;

//bullet
		case bullet:
			bullet_tail->sdl_tex = temp_text;
		break;


//obstacle
		case obstacle:
			obstacle_tail->sdl_tex = temp_text;
		break;

		default:
		break;
	}

	SDL_FreeSurface( surf );

return true;
}

template< typename T >
bool Text_Cont< T >::add( const Point * _pt )
{
	T * temp = new ( T );



/* creating new node */
	switch ( _pt->get_point_type() )
	{

//neutral
		case neutral:
		break;

//hero
		case hero:
		{
			if ( hero_head == nullptr )
			{
				temp->p_type = _pt->get_point_type();

				temp->prev = nullptr;
				temp->next = nullptr;

				hero_head = temp;
				hero_tail = temp;

			}
			else
			{
				temp->p_type = _pt->get_point_type();

				temp->prev = hero_tail;
				temp->prev->next = temp;

				temp->next = nullptr;

				hero_tail = temp;

			}
			hero_count++;

		}

		break;

//bullet
		case bullet:
		{
			if ( bullet_head == nullptr )
			{
				temp->p_type = _pt->get_point_type();

				temp->prev = nullptr;
				temp->next = nullptr;

				bullet_head = temp;
				bullet_tail = temp;

			}
			else
			{
				temp->p_type = _pt->get_point_type();

				temp->prev = bullet_tail;
				temp->prev->next = temp;

				temp->next = nullptr;

				bullet_tail = temp;

			}
			bullet_count++;
		}
		break;


//obstacle
		case obstacle:
		{
			if ( obstacle_head == nullptr )
			{
				temp->p_type = _pt->get_point_type();

				temp->prev = nullptr;
				temp->next = nullptr;

				obstacle_head = temp;
				obstacle_tail = temp;

			}
			else
			{
				temp->p_type = _pt->get_point_type();

				temp->prev = obstacle_tail;
				temp->prev->next = temp;

				temp->next = nullptr;

				obstacle_tail = temp;

			}
			obstacle_count++;
		}
		break;

		default:
		break;
	}



/* add SDL_Texture to Text_Objt object */

	SDL_Surface * surf;

	surf = SDL_LoadBMP( _pt->get_graph_sprite().c_str() );

	if ( surf == nullptr ) {
			printf("Error: there is no surf object; surf == NULL. Function 'texture_cont.h::add' terminated\n");
			return false;
		}

//change texture background
	if ( BACKGROUND != 1 )
		SDL_SetColorKey( surf, SDL_TRUE, SDL_MapRGB( surf->format, 255, 0, 255 ) );


//add texture
	SDL_Texture * temp_text = SDL_CreateTextureFromSurface( rend, surf );


	switch ( _pt->get_point_type() )
	{

//neutral
		case neutral:
		break;

//hero
		case hero:
			hero_tail->sdl_tex = temp_text;
		break;

//bullet
		case bullet:
			bullet_tail->sdl_tex = temp_text;
		break;


//obstacle
		case obstacle:
			obstacle_tail->sdl_tex = temp_text;
		break;

		default:
		break;
	}

	SDL_FreeSurface( surf );


	return true;
}

template< typename T>
bool Text_Cont< T >::del ( const Point * _pt, const int numb )
{
debug("bool Text_Cont< T >::del");
	if ( _pt == nullptr )
		return false;

	T * temp_T;

	switch ( _pt->get_point_type() )
	{
		case neutral:
		break;

		case hero:
		{
			debug("bool Text_Cont< T >::del => hero");
			temp_T = hero_head;
			if ( numb != 0 )
			{
				for ( int i = 0; i < numb; ++i )
				{
					temp_T = temp_T->next;
				}
			}

			temp_T->prev->next = temp_T->next;
			temp_T->next->prev = temp_T->prev;

			if ( temp_T == hero_head )
			{
				hero_head = temp_T->next;
			}
			else
			if ( temp_T == hero_tail )
			{
				hero_tail = temp_T->prev;
			}

			delete temp_T;
			--hero_count;
			debug("bool Text_Cont< T >::del => hero deleted");
		}
		return true;
		break;

		case bullet:
		{
			debug("bool Text_Cont< T >::del => bullet");
			temp_T = bullet_head;
			if ( numb != 0 )
			{
				for ( int i = 0; i < numb; ++i )
				{
					temp_T = temp_T->next;
				}
			}

			temp_T->prev->next = temp_T->next;
			temp_T->next->prev = temp_T->prev;

			if ( temp_T == bullet_head )
			{
				bullet_head = temp_T->next;
			}
			else
			if ( temp_T == hero_tail )
			{
				hero_tail = temp_T->prev;
			}

			delete temp_T;
			--hero_count;
			debug("bool Text_Cont< T >::del => bullet deleted");
		}
		return true;
		break;

		case obstacle:
		{
			debug("bool Text_Cont< T >::del => bullet");
			temp_T = obstacle_head;
			if ( numb != 0 )
			{
				for ( int i = 0; i < numb; ++i )
				{
					temp_T = temp_T->next;
				}
			}

			temp_T->prev->next = temp_T->next;
			temp_T->next->prev = temp_T->prev;

			if ( temp_T == obstacle_head )
			{
				obstacle_head = temp_T->next;
			}
			else
			if ( temp_T == hero_tail )
			{
				hero_tail = temp_T->prev;
			}

			delete temp_T;
			--hero_count;
			debug("bool Text_Cont< T >::del => bullet deleted");
		}
		return true;
		break;

		default:
		break;

	}


	return false;
}

template< typename T >
Text_Cont< T > & Text_Cont< T >::operator=( const Text_Cont & _tc )
{
	std::cout << "operator= 1\n";

	if ( &_tc == this )
		return *this;



/* SDL_Renderer copy */
	rend = _tc.rend;



/* hero texture copy */
	for ( T * p = hero_head; p != nullptr; p++ )
	{
		T * temp = hero_head->next;
		delete hero_head;
		hero_head = temp;
	}

	hero_count = _tc.hero_count;

	for ( T* p = _tc.hero_head; p != nullptr; p++ )
	{
		T * temp = new T;
		temp->p_type = p->p_type;

		if ( hero_head == nullptr )
		{
			temp = p;

			temp->prev = nullptr;
			temp->next = nullptr;

			hero_head = temp;
			hero_tail = temp;

		}
		else
		{
			temp = p;

			temp->prev = hero_head;
			temp->prev->next = temp;

			temp->next = nullptr;

			hero_head->next = temp;
			hero_tail = temp;

		}
	}



/* bullet texture copy */
	for ( T * p = bullet_head; p != nullptr; p++ )
	{
		T * temp = bullet_head->next;
		delete bullet_head;
		bullet_head = temp;
	}

	bullet_count = _tc.bullet_count;

	for ( T * p = _tc.bullet_head; p != nullptr; p++ )
	{
		T * temp = new T;
		temp->p_type = p->p_type;

		if ( bullet_head == nullptr )
		{
			temp = p;

			temp->prev = nullptr;
			temp->next = nullptr;

			bullet_head = temp;
			bullet_tail = temp;

		}
		else
		{
			temp = p;

			temp->prev = bullet_head;
			temp->prev->next = temp;

			temp->next = nullptr;

			bullet_head->next = temp;
			bullet_tail = temp;

		}
	}



/* obstacle texture copy */
for ( T * p = obstacle_head; p != nullptr; p++ )
	{
		T * temp = obstacle_head->next;
		delete obstacle_head;
		obstacle_head = temp;
	}

	obstacle_count = _tc.obstacle_count;

	for ( T * p = _tc.obstacle_head; p != nullptr; p++ )
	{
		T * temp = new T;
		temp->p_type = p->p_type;

		if ( obstacle_head == nullptr )
		{
			temp = p;

			temp->prev = nullptr;
			temp->next = nullptr;

			obstacle_head = temp;
			obstacle_tail = temp;

		}
		else
		{
			temp = p;

			temp->prev = obstacle_head;
			temp->prev->next = temp;

			temp->next = nullptr;

			obstacle_head->next = temp;
			obstacle_tail = temp;

		}
	}

	return *this;
}

template< typename T >
Text_Cont< T > & Text_Cont< T >::operator=( Text_Cont && _tc )
{
std::cout << "operator= 2\n";
	return *this;
}

template< typename T >
SDL_Texture * Text_Cont< T >::get_texture_hero( int i )
{
	return hero_head->operator[]( i );	//TODO:: How to create template function for typename T which return SDL_Texture?
}

/*
		//TODO:: can't overload opertaor[] for Text_Objt; this is only shortcut; there must be the way to overload the operator
		//	SDL_Texture * temp = hero_head[ i ];	should be valid; but 'hero-head[ i ]' always returns Text_Objt;why?
		template<>
		SDL_Texture * Text_Cont< Text_Objt >::get_texture_hero( int i )
		{
			std::cout << "taking: " << i << '\n';
			std::cout << "address: " << hero_head << '\n';
			//return hero_head[ i ];
			return hero_head->operator[](i);		//is it only way to do this?

		}
*/

template< typename T >
SDL_Texture * Text_Cont< T >::get_texture_bullet( int i )
{
	return bullet_head->operator[]( i );
}

template< typename T >
SDL_Texture * Text_Cont< T >::get_texture_obstacle( int i )
{
	return obstacle_head->operator[]( i );
}

/* This function gives one interface for getting all SDL_Texture for 3 kind of Point_type
 * It is organized that first go hero's texture then bullet's and obstacle in the end
 */
template< typename T >
SDL_Texture * Text_Cont< T >::get_texture( int i )
{
	const int SUM = hero_count + bullet_count + obstacle_count ;


	if ( i < 0 || i >= SUM )
		return nullptr;

	if ( i < hero_count )
	{
		return get_texture_hero( i );
	}

	if ( i >= hero_count && i < hero_count + bullet_count )
	{
		return get_texture_bullet( i - hero_count );
	}

	if ( i >= hero_count + obstacle_count && i < SUM )
	{
		return get_texture_obstacle( i - hero_count - bullet_count );
	}


	return nullptr;
}

template< typename T >
void Text_Cont< T >::print()
{
	std::cout << "\n\nhero_head: " << hero_head << "\thero_tail: " << hero_tail << "\thero_count: " << hero_count;
	hero_head->print();

	std::cout << "\n\nbullet_head: " << bullet_head << "\tbullet_tail: " << bullet_tail << "\tbullet_count: " << bullet_count;
	bullet_head->print();

	std::cout << "\n\nobstacle_head: " << obstacle_head << "\tobstacle_tail: " << obstacle_tail << "\tobstacle_count: " << obstacle_count;
	obstacle_head->print();

	std::cout << std::endl;
}


#endif
