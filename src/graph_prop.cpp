#include <stdlib.h>
#include <iostream>

#include "graph_prop.h"

void Stru_graph_prop::init_arr( Point_type _pt ) {
	
	/*
	 * Init function for 'arr_sprite_dim'
	 */
	
	s_sprite 		= "none";
	i_num_sprite 	= 0;
	arr_sprite_dim 	= NULL;
	i_width 		= 0;
	i_hight 		= 0;
	
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
			i_num_sprite = 4;
			
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
			
			arr_sprite_dim[i][j] = comm_arr_sprite_dimensions[ _pt ][j];
			//'_pt' is an enum Point_type from "comm_const.h"
			
		}		
	}
}

//end function

void Stru_graph_prop::show() {
	
	std::cout << "\nGRAPH show() :: file: " << s_sprite << " num_sprite: " << i_num_sprite << " width: " << i_width << " hight: " << i_hight << std::endl;
	
}

Stru_graph_prop & Stru_graph_prop::operator=(const Stru_graph_prop & _str_) {
	
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
	
	i_width = _str_.i_width;
	i_hight = _str_.i_hight;
	
	
	return *this;
}

Graph_prop::Graph_prop( Point_type & _pt, std::string _str, int & _wid, int & _hig ) {
	
	p_type = _pt;
		
	grap_prop.init_arr( _pt );
	
	grap_prop.s_sprite 	= _str;
	grap_prop.i_width 	= _wid;
	grap_prop.i_hight 	= _hig;
}

Graph_prop::Graph_prop( Point_type & _pt, Stru_graph_prop & _gprop ) {
	
	p_type = _pt;
	grap_prop.init_arr(  );
	grap_prop = _gprop;
	
}

Graph_prop::~Graph_prop() {
	
	printf( "\nGraph_prop DELETE\n" );
	
	if( grap_prop.i_num_sprite != 0 ) {
		for ( int i = 0; i < grap_prop.i_num_sprite; i++ ) {
			delete [] grap_prop.arr_sprite_dim[i];
		}
		//printf("%p", grap_prop.arr_sprite_dim);
		
		delete [] grap_prop.arr_sprite_dim;
	}
	
}

Graph_prop::Graph_prop() { 

	grap_prop.init_arr( Point_type::neutral );

}

void Graph_prop::print() {
	
	
}
