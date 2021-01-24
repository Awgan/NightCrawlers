
#include <SDL2/SDL.h>

#include "texture_cont.h"


Text_Objt & Text_Objt::operator=( const Text_Objt & _to )
{
	std::cout << "Text_Objt::operator=   l-value reference\n";

	if ( this == &_to )
		return *this;

	sdl_tex = _to.sdl_tex;

	p_type = _to.p_type;

	return *this;
}

Text_Objt & Text_Objt::operator=( Text_Objt && _to )
{
	std::cout << "Text_Objt::operator=   r-value reference\n";

	next = _to.next;
	_to.next = nullptr;

	prev = _to.prev;
	_to.prev = nullptr;

	sdl_tex = _to.sdl_tex;
	_to.sdl_tex = nullptr;

	p_type = _to.p_type;

	return *this;
}

SDL_Texture * Text_Objt::operator[]( int i )
{
	Text_Objt * p = this;

	for ( int r = 0; p != nullptr && r < i; r++ )
	{
		p = p->next;
	}

	SDL_Texture * temp = p->sdl_tex;

	return temp;
}

void Text_Objt::print()
{

	std::cout << "\nprev: " << prev << "\tthis: " << this << "\tnext: " << next;
	std::cout << "\ntexture: " << sdl_tex << "\tpoint type: " << p_type << '\n';
}

template<>
bool Text_Cont<Text_Objt>::test()
{
	SDL_Window * win;
	SDL_Renderer * rend;
	SDL_Event event;
	SDL_EventState( SDL_MOUSEMOTION, SDL_IGNORE);  //SDL_IGNORE;

	SDL_Init( SDL_INIT_EVERYTHING );

	win = SDL_CreateWindow("Test: texture_cont.h", 0, 0, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_OPENGL);

	rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);



// test 01

	std::cout << "\nTest 01:";

	Text_Cont< Text_Objt > test01( rend );

	test01.print();



//test 02

	std::cout << "\nTest 02:";



// Point Obstacle creation

Coordinate selected_coor;
	selected_coor.x = event.button.x;
	selected_coor.y = event.button.y;
	selected_coor.z = 0;
	selected_coor.dir = Coordinate::Direction::up;

Stru_property selected_prop;
	selected_prop.type = Point_type::obstacle;
	selected_prop.b_mobile = true;
	selected_prop.b_visible = true;
	selected_prop.i_health = 10;
	selected_prop.i_speed = 2;
	selected_prop.i_move_points = 3;
	selected_prop.i_strenght = 50;
	selected_prop.i_fire_accuracy = 0;

Stru_graph_prop selected_graph;
	selected_graph.init_arr( Point_type::obstacle );
	selected_graph.s_sprite = sprites_files[1];
	selected_graph.i_num_sprite = 1;
	selected_graph.arr_sprite_dim[0][0] = arr_sprite_obstacle[1][0];
	selected_graph.arr_sprite_dim[0][1] = arr_sprite_obstacle[1][1];
	selected_graph.arr_sprite_dim[0][2] = arr_sprite_obstacle[1][2];
	selected_graph.arr_sprite_dim[0][3] = arr_sprite_obstacle[1][3];
	selected_graph.actual_sprite = (int)Obstacle_type::box;
	selected_graph.i_width = 50;
	selected_graph.i_height = 50;



//



	test01.add( Point () );

	test01.print();


	test01.add( Point ( selected_coor, selected_prop, selected_graph ) );
	test01.add( Point ( selected_coor, selected_prop, selected_graph ) );
	test01.add( Point ( selected_coor, selected_prop, selected_graph ) );
	test01.add( Point ( selected_coor, selected_prop, selected_graph ) );
	test01.print();


	for ( Text_Objt * p = test01.obstacle_head; p != test01.obstacle_tail->next; p = p->next )
	{
		p->print();
	}
	std::cout << std::endl;

	Text_Cont<Text_Objt> test02( rend );
	test02.add( Point ( selected_coor, selected_prop, selected_graph ) );
	test02.add( Point ( selected_coor, selected_prop, selected_graph ) );
	test02.add( Point ( selected_coor, selected_prop, selected_graph ) );
	test02.add( Point ( selected_coor, selected_prop, selected_graph ) );

	for ( Text_Objt * p = test02.obstacle_head; p != test02.obstacle_tail->next; p = p->next )
	{
		p->print();
	}

//test 03 :: operator()=( Text_Objt )


	std::cout << "\nTest 03:\n";

	test01.obstacle_tail->prev->next = test02.obstacle_head;
	(test01.obstacle_tail) = (test02.obstacle_head);

	std::cout << "tail->prev after operator=: " << test01.obstacle_tail->prev  << "\ttail: " << test01.obstacle_tail << "\ttail->next after operator=: " << test01.obstacle_tail->next << '\n';

	for ( Text_Objt * p = test01.obstacle_head; p != test01.obstacle_tail->next; p = p->next )
	{
		p->print();
	}

	return true;
}

