#ifndef GRAPH_PROP_H
#define GRAPH_PROP_H


#include <string>

#include "comm_const.h"


struct Stru_graph_prop {

	std::string s_sprite;		//file name with pictures

	int i_num_sprite;			//number of pictures. They are used for motion efect.

	//int *arr_sprite_dim[i_num_sprite];
	int ** arr_sprite_dim;		//array for storing position and dimensions of pictures of an object
								//it must be dynamic allocated as there can be objects which change their look

	int actual_sprite;			//actual image which is shown on the display

	int i_width;				//object dimensions on the screen
	int i_height;


	void show();

						//before doing anything with the structure you must call the function. It is for initialize 'arr_sprite_dim
	void init_arr( Point_type _pt = Point_type::neutral );

	Stru_graph_prop & operator=(const Stru_graph_prop & _str_);
};

class Graph_prop {

	private:
		Stru_graph_prop	grap_prop;
		Point_type p_type;

	protected:

	public:

		Graph_prop( const Point_type & _pt = Point_type::neutral );

		Graph_prop( Point_type & _pt, std::string _str, int & _wid, int & _hig);

		Graph_prop( Point_type & _pt, Stru_graph_prop & _gprop );

		~Graph_prop();

		void setSpriteFile( const std::string & str ) { grap_prop.s_sprite = str; }
		void setSpriteNumber( int num ) { grap_prop.i_num_sprite = num; }
		void setActualSprite( int ac );
		void setSpriteWidth( int w ) 	{ grap_prop.i_width = w; }
		void setSpriteHeight( int h ) 	{ grap_prop.i_height = h; }

		const int & get_graph_width() 		{ return grap_prop.i_width; }
		const int & get_graph_height() 		{ return grap_prop.i_height; }
		int * get_graph_width_p()			{ return &grap_prop.i_width; }
		int * get_graph_height_p()			{ return &grap_prop.i_height; }
		std::string get_graph_sprite() const	{return grap_prop.s_sprite; }
		const int & getActualSprite( )			{ return grap_prop.actual_sprite; };

		void print() ;
};

#endif
