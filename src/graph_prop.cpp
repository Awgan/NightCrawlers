#include <stdlib.h>
#include <iostream>

#include "graph_prop.h"

void Stru_graph_prop::init_arr( Point_type _pt )
{

	/*
	 * Init function for 'arr_sprite_dim'
	 */

	s_sprite 		= "none";
	i_num_sprite 	= 0;
	arr_sprite_dim 	= NULL;
	actual_sprite 	= 0;
	i_width 		= 0;
	i_height 		= 0;

	switch (_pt) {

		//NEUTRAL
		case Point_type::neutral:
			i_num_sprite = 1;

			arr_sprite_dim = new int * [i_num_sprite];
			for ( int i = 0; i < i_num_sprite; i++ ) {
				arr_sprite_dim[i] = new int[4];
			}
		break;

		//HERO
		case Point_type::hero:
			i_num_sprite = HERO_SPRITES;

			arr_sprite_dim = new int * [i_num_sprite];
			for ( int i = 0; i < i_num_sprite; i++ ) {
				arr_sprite_dim[i] = new int[4];
			}
		break;

		//BULLET
		case Point_type::bullet:
			i_num_sprite = 4;

			arr_sprite_dim = new int * [i_num_sprite];
			for ( int i = 0; i < i_num_sprite; i++ ) {
				arr_sprite_dim[i] = new int[4];
			}
		break;

		//OBSTACLE
		case Point_type::obstacle:
			i_num_sprite = 1;

			arr_sprite_dim = new int * [i_num_sprite];
			for ( int i = 0; i < i_num_sprite; i++ ) {
				arr_sprite_dim[i] = new int[4];
			}
		break;

		//DEFAULT
		default:
		break;
	};

	//getting sprite DIMENSIONS of the object from "coom_const.h" file

	for ( int i = 0; i < i_num_sprite; i++ ) {

		for ( int j = 0; j < 4; j++ ) {

			arr_sprite_dim[i][j] = arr_sprite_dimensions[ _pt ][j];
			//'_pt' is an enum Point_type from "comm_const.h"

		}
	}
}

//end function

void Stru_graph_prop::show()
{

	std::cout << "\nGRAPH show() :: file: " << s_sprite << " sprite numbers: " << i_num_sprite <<  " actual sprite: " << actual_sprite << " width: " << i_width << " height: " << i_height << " sprite_dim: " <<
	arr_sprite_dim[0][0] << " " <<
	arr_sprite_dim[0][1] << " " <<
	arr_sprite_dim[0][2] << " " <<
	arr_sprite_dim[0][3] << " " << std::endl;

}

Stru_graph_prop & Stru_graph_prop::operator=(const Stru_graph_prop & _str_)
{

	if( this == & _str_ )
		return *this;

	s_sprite = _str_.s_sprite;

	//delete old
	if ( i_num_sprite > 0 ) {
		for ( int i = 0; i < i_num_sprite; i++ ) {
			delete [] arr_sprite_dim[i];
		}
		delete [] arr_sprite_dim;
	}

	i_num_sprite = _str_.i_num_sprite;

	//create new
	arr_sprite_dim = new int * [i_num_sprite];
	for ( int i = 0; i < i_num_sprite; i++ ) {
		arr_sprite_dim[i] = new int[4];
	}


	//copy new dimenions
	if( _str_.arr_sprite_dim != NULL ) {
		for( int i = 0; i < i_num_sprite; ++i ) {
			for ( int j = 0; j < 4; ++j ) {

				arr_sprite_dim[i][j] = _str_.arr_sprite_dim[i][j];
			}
		}
	}

	actual_sprite = _str_.actual_sprite;

	i_width = _str_.i_width;
	i_height = _str_.i_height;


	return *this;
}

Graph_prop::Graph_prop( Point_type & _pt, std::string _str, int & _wid, int & _hig )
{

	p_type = _pt;

	idleSpriteTime = time( nullptr );

	grap_prop.init_arr( _pt );

	grap_prop.s_sprite 	= _str;
	grap_prop.i_width 	= _wid;
	grap_prop.i_height 	= _hig;
}

Graph_prop::Graph_prop( Point_type & _pt, Stru_graph_prop & _gprop )
{

	grap_prop.init_arr(  );

	p_type = _pt;
	idleSpriteTime = time( nullptr );

	grap_prop = _gprop;
	grap_prop.i_height = _gprop.i_height;
	grap_prop.i_width = _gprop.i_width;

}

Graph_prop::~Graph_prop()
{

	//printf( "\nGraph_prop DELETE\n" );

	if( grap_prop.i_num_sprite != 0 ) {
		for ( int i = 0; i < grap_prop.i_num_sprite; i++ ) {
			delete [] grap_prop.arr_sprite_dim[i];
		}
		//printf("%p", grap_prop.arr_sprite_dim);

		delete [] grap_prop.arr_sprite_dim;
	}

}

Graph_prop::Graph_prop( const Point_type & _pt )
{

	grap_prop.init_arr( _pt );

}

double Graph_prop::diffIdleSpriteTime()
{
	return std::difftime( time( nullptr ), idleSpriteTime );
}

void Graph_prop::changeIdleSprite()
{
	if ( diffIdleSpriteTime() < 1.5 )
	{
		return;
	}

	switch (p_type)
	{
		case Point_type::neutral:
		break;

		case Point_type::hero:

			if ( grap_prop.actual_sprite >= 0 && grap_prop.actual_sprite < 4)
			{

				++grap_prop.actual_sprite;

				if ( grap_prop.actual_sprite > 3 )
					grap_prop.actual_sprite = 0;

			}
			else if ( grap_prop.actual_sprite >= 4 && grap_prop.actual_sprite < 8 )
			{

				++grap_prop.actual_sprite;

				if ( grap_prop.actual_sprite > 7 )
					grap_prop.actual_sprite = 4;

			}

		break;

		case Point_type::bullet:
		break;

		case Point_type::obstacle:
		break;

		default:
		break;

	}

	updateIdleSpriteTime();

}

void Graph_prop::setActualSprite( int ac )
{

	int pointTypeRange;

	switch (p_type)
	{

		case Point_type::neutral:
		pointTypeRange = 1;
		break;

		case Point_type::hero:
		pointTypeRange = HERO_SPRITES;
		break;

		case Point_type::bullet:
		pointTypeRange = 4;
		break;

		case Point_type::obstacle:
		pointTypeRange = 1;
		break;

		default:
		break;
	}

	if ( ac >= 0 && ac < pointTypeRange	)
	{
		grap_prop.actual_sprite = ac;
	}
	else
	{
		grap_prop.actual_sprite = 0;
		printf("Graph_prop::setActualSprite >> Error: parameter is out of range, and set to 0\n");
	}
}

void Graph_prop::print()
{

	printf( "arr sprite dim: %d %d %d %d\n", grap_prop.arr_sprite_dim[0][0], grap_prop.arr_sprite_dim[0][1], grap_prop.arr_sprite_dim[0][2], grap_prop.arr_sprite_dim[0][3] );
	grap_prop.Stru_graph_prop::show();

}
