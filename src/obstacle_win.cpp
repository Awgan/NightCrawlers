#include <iostream>

#include "obstacle_win.h"



ObstacleWin::ObstacleWin() : WinGenSDL () {
	
}


ObstacleWin::~ObstacleWin() {
	
	
}

void ObstacleWin::init( const char * _sprite, SDL_Rect * _spriteRect, SDL_Rect * _winRect ) {

	setWidthAndHight( _winRect->w, _winRect->h );
	
	initWin( _winRect->x, _winRect->y );
	
	initTex( _sprite );	
	
	spriteRect = *_spriteRect;
}

bool ObstacleWin::show() {
	std::cout << "ObstacleWin :: show()\n";
	if ( tex == nullptr )
		return false;
	
	if ( SDL_RenderCopy( rend, tex, &spriteRect, nullptr ) != 0 )
		return false;
	
	if ( rend == nullptr )
		return false;
	
	SDL_RenderPresent( rend );
	std::cout << "delay 5sec...\n";
	SDL_Delay(5000);
	return true;	
}

ObstacleWin & ObstacleWin::operator=( ObstacleWin & ob1 ) {
		
	if ( this == &ob1 )
		return *this;

	WinGenSDL::operator=( ob1 );

	spriteRect = ob1.spriteRect;

	return *this;
	
}

bool ObstacleWin::test() {
	
	struct Result {
		bool testWinGenSDL {0};
		bool testSetWidthandHight {0};
		bool testShow {0};
		bool testHide {0};
	} result;

	if ( WinGenSDL::test() )
		result.testWinGenSDL = true;
	else
		result.testWinGenSDL = false;

	SDL_Rect re, wre;
	re.x = 65;
	re.y = 90;
	re.w = 234;
	re.h = 909;
	
	wre.x = 444;
	wre.y = 333;
	wre.w = 222;
	wre.h = 111;
	
	const char * file = "../fig/worms02.bmp";
	
	init(file, &re, &wre );
	
	//ObstacleWin test
	
	
	if( get_win_width() == wre.w && get_win_hight() == wre.h )
	{ result.testSetWidthandHight = true; }
	else
	{ result.testSetWidthandHight = false; }
		
	if( show() )
	{ result.testShow = true;}
	else
	{ result.testShow = false;}

	hide();
		
	if( tex == nullptr && rend == nullptr && win == nullptr )
	{ result.testHide = true;}
	else
	{ result.testHide = false;}
	
	std::cout << "\nOBSTACLE WIN :: test()\n";
	std::cout << "WinGenSDL: " 				<< result.testWinGenSDL	<< std::endl;
	std::cout << "SetWidthandHight: " 		<< result.testSetWidthandHight	<< std::endl;
	std::cout << "testShow: "				<< result.testShow << std::endl;
	std::cout << "testHide: " 				<< result.testHide << std::endl;
	
	if( result.testWinGenSDL &&
	result.testSetWidthandHight &&
	result.testShow &&
	result.testHide ) 
	{ std::cout << "Test: passed\n"; return true;}
	else 
	{ std::cout << "Test: failed\n"; return false;}
	
	return false;
}
