#include "info_win.h"


Info_win::Info_win() {

	event 		= nullptr;
	pointCont 	= nullptr;

	actPoint 	= nullptr;

	win 		= nullptr;
	rend 		= nullptr;
	surf 		= nullptr;
	tex 		= nullptr;

	font 		= nullptr;
	
	font_size	= 0;
	lines		= 0;

	win_posX 	= 0;
	win_posY 	= 0;
	win_width	= 0;
	win_hight	= 0;

}

Info_win::~Info_win() {

	TTF_CloseFont( font );
	SDL_DestroyRenderer( rend );
	SDL_DestroyWindow( win );
}

Info_win::Info_win( SDL_Event * _event, Point_Container * _pCont ) : event(_event), pointCont(_pCont) {

	actPoint 	= nullptr;

	win 		= nullptr;
	rend 		= nullptr;
	surf 		= nullptr;
	tex 		= nullptr;

	font 		= nullptr;

	font_size	= 14;
	lines 		= 4;
	win_posX 	= 0;
	win_posY 	= 0;
	win_width	= 100;
	win_hight	= ( font_size + 2 ) * lines;

}

bool Info_win::isPointed() {

	int ms_x, ms_y;
	ms_x = event->button.x;
	ms_y = event->button.y;

	for ( int i = 0; i < pointCont->get_number_hero(); ++i ) {
		
		if ( 	ms_x >= pointCont->get_point_hero( i )->get_coor_x() && ms_x <= pointCont->get_point_hero( i )->get_coor_x() +
				pointCont->	get_point_hero( i )->get_graph_width() &&
				ms_y >= pointCont->get_point_hero( i )->get_coor_y() && ms_y <= pointCont->get_point_hero( i )->get_coor_y() +
				pointCont->get_point_hero( i )->get_graph_hight()	) {
			
			actPoint = pointCont->get_point_hero( i );

			return true;
		}
	}

	for ( int i = 0; i < pointCont->get_number_obstacle(); ++i ) {
		
		if ( 	ms_x >= pointCont->get_point_obstacle( i )->get_coor_x() && ms_x <= pointCont->get_point_obstacle( i )->get_coor_x() + 
				pointCont->get_point_obstacle( i )->get_graph_width() &&
				ms_y >= pointCont->get_point_obstacle( i )->get_coor_y() && ms_y <= pointCont->get_point_obstacle( i )->get_coor_y() +
				pointCont->get_point_obstacle( i )->get_graph_hight()	) {
			
			actPoint = pointCont->get_point_obstacle( i );
			
			return true;
		}
	}

	actPoint = nullptr;
	return false;
}

void Info_win::show() {

	if ( actPoint ) {
		
		win_posX = actPoint->get_coor_x() + actPoint->get_graph_width();
		win_posY = actPoint->get_coor_y();

		win = SDL_CreateWindow( "Property", win_posX, win_posY, win_width, win_hight, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS | SDL_WINDOW_HIDDEN );

		if ( win == nullptr )
			printf("#Info_win::		no win:	%s\n", SDL_GetError() );


		rend = SDL_CreateRenderer( win, -1, SDL_RENDERER_ACCELERATED );

		if (rend == nullptr )
			printf("#Info_win::		no rend:	%s\n", SDL_GetError() );
		
		SDL_SetRenderDrawColor( rend, 169, 122, 28, 255 );


		TTF_Init();

		font = TTF_OpenFont( "../conf/MicroFLF.ttf", font_size );
		if ( font == nullptr ) {
			printf( "#TTF_OpenFont		%s\n", TTF_GetError() );
		}


		SDL_RenderClear( rend );

		std::string s_tmp; 	
		int 		r_w, r_h;
		SDL_Rect 	r_dim;

		SDL_ShowWindow( win );


		for ( int i = 0; i < lines; ++i ) {
		
			switch (i) {
				case 0:
				s_tmp = "x: " + std::to_string( actPoint->get_coor_x() );
				break;
				
				case 1:
				s_tmp = "y: " + std::to_string( actPoint->get_coor_y() );
				break;
				
				case 2:
				s_tmp = "health: " + std::to_string( actPoint->get_health() );
				break;
				
				case 3:
				s_tmp = "speed: " + std::to_string( actPoint->get_speed() );
				break;
			}
		
			surf = TTF_RenderText_Solid( font, s_tmp.c_str(), { 255, 255, 255 } );
			if ( surf == nullptr )
				printf( "%s\n", TTF_GetError() );

			tex = SDL_CreateTextureFromSurface( rend, surf );

			SDL_FreeSurface( surf );
			
			SDL_QueryTexture( tex, nullptr, nullptr, &r_w, &r_h );
			
			r_dim = { 0, (i*(font_size+2)), r_w, r_h };
		
			SDL_RenderCopy( rend, tex, nullptr, &r_dim );
		}

		SDL_RenderPresent( rend );
	}
}

void Info_win::hide() {

	TTF_Quit();
	
	SDL_DestroyTexture( tex );
	SDL_DestroyRenderer( rend );
	SDL_DestroyWindow( win );

	actPoint = nullptr;
}
