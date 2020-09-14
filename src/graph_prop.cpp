#include <stdlib.h>
#include <iostream>

#include "graph_prop.h"

//function for creating sprite array dimension

void create_arr_sprite( Point_type & _pt, Stru_graph_prop & _gp) {
	
	/*
	 * find out what point type is and put proper "i_num_sprite" value and
	 * "arr_sprite_dim" dimenison values
	 */
	
	switch (_pt) {
		
		//NEUTRAL
		case Point_type::neutral:
			_gp.i_num_sprite = 1;
			
			_gp.arr_sprite_dim = new int * [_gp.i_num_sprite];
			for ( int i = 0; i < _gp.i_num_sprite; i++ ) {
				_gp.arr_sprite_dim[i] = new int[4];
			}
			
			_gp.s_sprite = comm_arr_sprite_files[0];
			break;
		
		//HERO
		case Point_type::hero:
			_gp.i_num_sprite = 4;
			
			_gp.arr_sprite_dim = new int * [_gp.i_num_sprite];
			for ( int i = 0; i < _gp.i_num_sprite; i++ ) {
				_gp.arr_sprite_dim[i] = new int[4];
			}
				
			_gp.s_sprite = comm_arr_sprite_files[1];
			break;
		
		//BULLET
		case Point_type::bullet:
			_gp.i_num_sprite = 4;
			
			_gp.arr_sprite_dim = new int * [_gp.i_num_sprite];
			for ( int i = 0; i < _gp.i_num_sprite; i++ ) {
				_gp.arr_sprite_dim[i] = new int[4];
			}
			
			_gp.s_sprite = comm_arr_sprite_files[2];
			break;
		
		//OBSTACLE
		case Point_type::obstacle:
			_gp.i_num_sprite = 1;
			
			_gp.arr_sprite_dim = new int * [_gp.i_num_sprite];
			for ( int i = 0; i < _gp.i_num_sprite; i++ ) {
				_gp.arr_sprite_dim[i] = new int[4];
			}
				
			_gp.s_sprite = comm_arr_sprite_files[3];
			break;
		
		
		default:
			break;	
	
	};
	
	//getting sprite DIMENSIONS of the object from "coom_const.h" file
	
	for ( int i = 0; i < _gp.i_num_sprite; i++ ) {
		
		for ( int j = 0; j < 4; j++ ) {
			
			_gp.arr_sprite_dim[i][j] = comm_arr_sprite_dimensions[ _pt ][j];
			//'_pt' is an enum Point_type from "comm_const.h"
			
		}
		
	}
}

//end function

void Stru_graph_prop::show() {
	
	std::cout << "sprite: " << s_sprite << " num_sprite: " << i_num_sprite << " width: " << i_width << " i_hight: " << i_hight << std::endl;

	
}

Graph_prop::Graph_prop( Point_type & _pt, std::string _str, int & _wid, int & _hig ) {
	
	grap_prop.s_sprite 	= _str;
	grap_prop.i_width 	= _wid;
	grap_prop.i_hight 	= _hig;
	
	p_type = _pt;
	
	
	
	create_arr_sprite( _pt, grap_prop );
	
	}

Graph_prop::Graph_prop( Point_type & _pt, Stru_graph_prop & _gprop ) {
	
	grap_prop.s_sprite 	= _gprop.s_sprite;
	grap_prop.i_width 	= _gprop.i_width;
	grap_prop.i_hight 	= _gprop.i_hight;
	
	p_type = _pt;
	
	create_arr_sprite( _pt, grap_prop );
	
}

Graph_prop::~Graph_prop() {
	
	if( grap_prop.i_num_sprite != 0 ) {
		for ( int i = 0; i < grap_prop.i_num_sprite; i++ ) {
			delete [] grap_prop.arr_sprite_dim[i];
		}
		//printf("%p", grap_prop.arr_sprite_dim);
		
		delete [] grap_prop.arr_sprite_dim;
	}
	
}

Graph_prop::Graph_prop() { 

//for test only, delet at the end
	grap_prop.s_sprite = "demo.metal";
	grap_prop.i_hight = 123;
	grap_prop.i_width = 321;
	grap_prop.i_num_sprite = 0;
//end for tests
}

void Graph_prop::print() {
	
	
}
