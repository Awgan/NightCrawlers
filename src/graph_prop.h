#ifndef GRAPH_PROP_H
#define GRAPH_PROP_H


#include <string>

struct Stru_graph_prop {
	std::string s_sprite;
	int arr_sprite_dim[4][4];
	int i_width;
	int i_hight;
};

class Graph_prop {

	private:		
		Stru_graph_prop	grap_prop;
	
	protected:

	
	public:
		Graph_prop( std::string _str, int & _wid, int & _hig);
		~Graph_prop();
		
		
		const int & get_graph_widht()		{ return grap_prop.width; }
		const int & get_graph_hight()		{ return grap_prop.hight; }
		const int * get_graph_widht_p()		{ return &grap_prop.width; }
		const int * get_graph_hight_p()		{ return &grap_prop.hight; }
		
};

#endif
