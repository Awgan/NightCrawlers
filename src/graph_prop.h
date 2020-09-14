#ifndef GRAPH_PROP_H
#define GRAPH_PROP_H


#include <string>

#include "comm_const.h"

struct Stru_graph_prop {
	
	std::string s_sprite;		//file name
	
	int i_num_sprite;			//number of single ascpects/drawings of the object. they are used for motion efect.
	int ** arr_sprite_dim;		//array for storing position and dimensions of an object from sprite file
								//it must be dynamic allocated as there can be objects which change their look
	
	int i_width;				//object dimensions on the screen
	int i_hight;
	
	void show();
};

class Graph_prop {

	private:		
		Stru_graph_prop	grap_prop;
		Point_type p_type;

		
	protected:

	
	public:
		Graph_prop() ;
		Graph_prop( Point_type & _pt, std::string _str, int & _wid, int & _hig );
			/*
			 * constructor should take "i_num_sprite" from <config file> or from "comm_const.h"
			 * and should get sprite dimensions for each aspect from file too
			 *  
			 * */
		
		Graph_prop( Point_type & _pt, Stru_graph_prop & _gprop );
		
		~Graph_prop();
		
		
		const int & get_graph_widht() 		{ return grap_prop.i_width; }
		const int & get_graph_hight() 		{ return grap_prop.i_hight; }
		const int * get_graph_widht_p()		{ return &grap_prop.i_width; }
		const int * get_graph_hight_p()		{ return &grap_prop.i_hight; }
		
		std::string get_graph_sprite() 	{return grap_prop.s_sprite; }
		
		void print() ;
		
};

#endif
