#include <iostream>

#include "win_general.h"


WinGenSDL::WinGenSDL() :win(nullptr), tex(nullptr), rend(nullptr), surf(nullptr) {

	width = 0;
	height = 0;
}

WinGenSDL::~WinGenSDL() {

}

void WinGenSDL::setWidthAndHight( const int & _w, const int & _h ) {

	width = _w;
	height = _h;
}

void WinGenSDL::initWin( const int & pos_x, const int & pos_y ) {
	if ( win == nullptr ) {

		int wFlags = ( SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS | SDL_WINDOW_MOUSE_FOCUS | SDL_WINDOW_OPENGL );

		win = SDL_CreateWindow( "Obstacle Box", pos_x, pos_y, width, height, wFlags );

		rend = SDL_CreateRenderer( win, -1, SDL_RENDERER_ACCELERATED );
	}
}

void WinGenSDL::initTex( const char * background ) {

	if ( tex == nullptr ) {

		fBaGr = (std::string)background;
		if( fBaGr != "brak" ) {
			surf = SDL_LoadBMP( fBaGr.c_str() );

			if ( surf == nullptr )
			{
				std::cout << "Error : WinGenSDL::initTex : surface not created\n";
				return;
			}

			tex = SDL_CreateTextureFromSurface( rend, surf );

			if ( tex == nullptr )
			{
				std::cout << "Error : WinGenSDL::initTex : texture not created\n";
				return;
			}

			SDL_FreeSurface ( surf );
		}
	}
}

bool WinGenSDL::show() {

	if ( tex == nullptr )
		return false;

	if ( SDL_RenderCopy( rend, tex, nullptr, nullptr ) )
		return false;

	if ( rend == nullptr )
		return false;

	SDL_RenderPresent( rend );

	return true;
}

void WinGenSDL::hide() {

	SDL_DestroyTexture( tex );
	SDL_DestroyRenderer( rend );
	SDL_DestroyWindow( win );

	tex 	= nullptr;
	rend 	= nullptr;
	win 	= nullptr;
}

WinGenSDL & WinGenSDL::operator=(WinGenSDL & wgs) {

	if ( this == &wgs )
		return *this;

	SDL_DestroyTexture( tex );		tex 	= nullptr;
	SDL_DestroyRenderer( rend );	rend 	= nullptr;
	SDL_DestroyWindow( win );		win 	= nullptr;

	width = wgs.width;
	height = wgs.height;

	win = SDL_CreateWindow("ObstacleBoxWin_test", 0, 0, width, height, SDL_WINDOW_OPENGL );

	if ( win == nullptr )
		{
			std::cout << "win is : nullptr : " << SDL_GetError() << std::endl;
			std::abort();
		}

	rend = SDL_CreateRenderer( win, -1, SDL_RENDERER_ACCELERATED );

	fBaGr = wgs.fBaGr;
	surf = SDL_LoadBMP( fBaGr.c_str() );

	tex = SDL_CreateTextureFromSurface( rend, surf );

	SDL_FreeSurface( surf );


	return *this;
}

bool WinGenSDL::test() {

	struct Result{
		bool testConstructor;
		bool testSetWidthandHight;
		bool testInitWinBox;
		bool testInitTex;
		bool testShow;
		bool testHide;
		//bool testOper_eq;
	} result {false};

	if( win == nullptr && tex == nullptr && rend == nullptr && surf == nullptr &&
	width == 0 && height == 0 ) {
		result.testConstructor = true;}
	else {result.testConstructor = false;}



	int a = {45}, b = {65};

	setWidthAndHight( a, b );

	if( width != 0 && height != 0 && width == a && height == b )
	{ result.testSetWidthandHight = true; }
	else
	{ result.testSetWidthandHight = false; }

	a = 600;
	b = 800;
	initWin(a , b);

	if( win != nullptr && rend != nullptr )
	{ result.testInitWinBox = true;}
	else
	{ result.testInitWinBox = false;}

	const char * file = "../fig/worms02.bmp";

	initTex(file);

	if( tex != NULL )
	{ result.testInitTex = true;}
	else
	{ result.testInitTex = false;}

	if( show() )
	{ result.testShow = true;}
	else
	{ result.testShow = false;}

	hide();

	if( tex == nullptr && rend == nullptr && win == nullptr )
	{ result.testHide = true;}
	else
	{ result.testHide = false;}

	/*
	WinGenSDL t_wgs1, t_wgs2;
	a = 189; b = 141;
	t_wgs1.setWidthAndHight( a , b );
	t_wgs1.initWin( 4, 9 );
	t_wgs2 = t.wgs1;
	if ( a == t_wgs2.get_win_width && b == t_wgs2.get_win_height )
	{ result.testOper_eq = true; }
	else
	{ result.testOper_eq = false; }
	*/
	std::cout << "\nWINGENSDL test()\n";
	std::cout << "testConstructor: " 		<< result.testConstructor << std::endl;
	std::cout << "testSetWidthandHight: " 	<< result.testSetWidthandHight << std::endl;
	std::cout << "testInitWinBox: " 		<< result.testInitWinBox << std::endl;
	std::cout << "testInitTex: " 			<< result.testInitTex << std::endl;
	std::cout << "testShow: "				<< result.testShow << std::endl;
	std::cout << "testHide: " 				<< result.testHide << std::endl;
	//std::cout << "testOperator=: "			<< result.testOper_eq << std::endl;

	if( result.testConstructor &&
	result.testSetWidthandHight &&
	result.testInitWinBox &&
	result.testInitTex &&
	result.testShow &&
	result.testHide )
	//&& result.testOper_eq )
	{ std::cout << "Test: passed\n"; return true;}
	else
	{ std::cout << "Test: failed\n"; return false;}

	return false;
}





