/*
 * Idea is that the class consists of smaller windows
 * which contain objects/elements for choosing
 *
 */

#ifndef OBSTACLE_BOX_WIN_H_
#define OBSTACLE_BOX_WIN_H_

#include <iostream>
#include <string>
#include <vector>

#include <SDL2/SDL.h>

#include "obstacle_win.h"
#include "win_general.h"



template<class T, class U>
class ObstacleBoxWin : public WinGenSDL {

	public:
		/*struct spriteDetails {

				std::string name;
				int number;
				SDL_Rect * rect;
		};*/

	private:
		std::string fName;

		T * dimBox;			//SDL_Rect;
		U * obstacleBox;	//ObstacleWin
		int boxElements;	//number of elements
		int top;			//

		bool visible;

		const SDL_Event * event;

		void addDimBox( T & _boxelement );
		void addObstacleBox( U & _obst );


	public:

		ObstacleBoxWin();
		ObstacleBoxWin( const SDL_Event * _event, const int & no_elements, const char * _fName );

		~ObstacleBoxWin();

		virtual bool show();

		void copyDimBox( const T * _box, const int & _numb );
		void copyObstacleBox( U * _obstBox, const int & _numb );

		void addBox( T & _dim, U & _obWin );


		void getDimBox( T * _box, const int & _elements) const;
		void getObstacleBox( U * _obstBox, const int & _elements );

		T getDimBoxElement( const int & _numb ) const;
		U getObstacleBoxElement( const int & _numb ) const;

		void resetTop() { top = 0; }

		void setVisibility( bool b ) {visible = b;};

		const int & getElementsNumber() const;

		T operator[](const int & _numb);

		ObstacleBoxWin<T,U> & operator=( const ObstacleBoxWin<T,U> & _obw );

};



template<class T, class U>
ObstacleBoxWin<T,U>::ObstacleBoxWin() {

	fName = std::string( "brak" );
	top = 0;
	visible = false;

}

template<class T, class U>
ObstacleBoxWin<T,U>::ObstacleBoxWin( const SDL_Event * _event, const int & no_elements, const char * _fName) : WinGenSDL() {

	fName = std::string( _fName );

	boxElements = no_elements;
	top = 0;
	visible = false;
	dimBox = new T [ boxElements ];
	obstacleBox = new U [ boxElements ];

	event = _event;
}

template<class T, class U>
ObstacleBoxWin<T,U>::~ObstacleBoxWin() {
	delete [] dimBox;
	delete [] obstacleBox;
}

template<class T, class U>
bool ObstacleBoxWin<T,U>::show() {

	if ( visible == true ) {

		if ( fName == "brak" ) {
			std::cout << "File name is not known\n";
			return false;
		}

		//TODO::establishe width and height of obstacle windows
		setWidthAndHight(150, 100);

		int mx, my;
		SDL_GetMouseState(&mx, &my);

		initWin( mx, my );

		initTex( fName.c_str() );

		constexpr SDL_Rect obsty { 10, 107, 338, 86 };

		SDL_RenderCopy( rend, tex, &obsty, NULL );

		if ( rend == nullptr || tex == nullptr )
			return false;

		SDL_SetWindowGrab(win,SDL_FALSE);
		SDL_RenderPresent( rend );


		//TODO:: loop for rendering all obstacle_win from obstacleBox
	}
	else
		this->hide();

	return true;
}

template<class T, class U>
void ObstacleBoxWin<T,U>::copyDimBox( const T * _box, const int & _numb ) {

	if ( boxElements >= _numb ) {
		for ( int i = 0; i < _numb; ++i ) {
			dimBox[i] = _box[i];

		}
		top = _numb;
	}
	else
		return;
}

template<class T, class U>
void ObstacleBoxWin<T,U>::copyObstacleBox( U * _obstBox, const int & _numb ) {

	if ( boxElements >= _numb ) {
		for ( int i = 0; i < _numb; ++i ) {
			obstacleBox[i] = _obstBox[i];

		}
		top = _numb;
	}
	else
		return;
}

template<class T, class U>
void ObstacleBoxWin<T,U>::addBox( T & _dim, U & _obWin ) {

	if ( top + 1 <= boxElements ) {

		dimBox[top] = _dim;
		obstacleBox[top] = _obWin;

		top++;
	}
}

template<class T, class U>
void ObstacleBoxWin<T,U>::addDimBox( T & _boxElement ) {

	if ( top + 1 <= boxElements ) {
		dimBox[top] = _boxElement;

		++top;
	}
	else
		return;
}

template<class T, class U>
void ObstacleBoxWin<T,U>::addObstacleBox( U & _obst ) {

	if ( top + 1 <= boxElements ) {
		obstacleBox[top] = _obst;

		++top;
	}
	else
		return;
}

template<class T, class U>
void ObstacleBoxWin<T,U>::getDimBox( T * _box, const int & _elements ) const {

	for ( int i = 0; i < _elements && i < boxElements; ++i ) {

		_box[i] = dimBox[i];
	}
}

template<class T, class U>
void ObstacleBoxWin<T,U>::getObstacleBox( U * _obstBox, const int & _elements ) {

	for ( int i = 0; i < _elements && i < boxElements; ++i ) {

		_obstBox[i] = obstacleBox[i];
	}
}

template<class T, class U>
T ObstacleBoxWin<T,U>::getDimBoxElement( const int & _numb ) const {

	T temp;
	if ( _numb >= 0 && _numb < top ) {
		temp = dimBox[ _numb ];
	}
	else {
		temp = dimBox[ top - 1 ];
	}

	return temp;
}

template<class T, class U>
U ObstacleBoxWin<T,U>::getObstacleBoxElement( const int & _numb ) const {

	T temp;
	if ( _numb >= 0 && _numb < top ) {
		temp = obstacleBox[ _numb ];
	}
	else {
		temp = obstacleBox[ top - 1 ];
	}

	return temp;
}

template<class T, class U>
const int & ObstacleBoxWin<T,U>::getElementsNumber() const {

	return boxElements;
}
template<class T, class U>
T ObstacleBoxWin<T,U>::operator[](const int & _numb){

	T temp;
	if ( _numb >= 0 && _numb < top ) {
		temp = dimBox[ _numb ];
	}
	else {
		temp = dimBox[ top - 1 ];
	}

	return temp;
}

template<class T, class U>
ObstacleBoxWin<T,U> & ObstacleBoxWin<T,U>::operator=( const ObstacleBoxWin<T,U> & _obw ) {

	if ( this == &_obw )
		return *this;

	WinGenSDL::operator=( _obw );

	fName = _obw.fName;
	boxElements = _obw.boxElements;
	top = _obw.top;

	delete [] dimBox;
	delete [] obstacleBox;

	dimBox = new T [ boxElements ];
	obstacleBox = new U [ boxElements ];

	for ( int i = 0; i < boxElements; ++i ) {
		dimBox[i] = _obw.dimBox[i];
		obstacleBox[i] = _obw.obstacleBox[i];
	}

	return *this;
}

template<class T>
bool test_ObstacleBoxWin() {

	{
		ObstacleWin ow;
		ow.test();
	}

	struct {
		bool addDimBox {0};
		bool getDimBox {0};
		bool addObstacleBox {0};
		bool getObstacleBox {0};
	}testResult;

	SDL_Init( SDL_INIT_EVERYTHING );
	SDL_Window * t_win = SDL_CreateWindow("ObstacleBoxWin_test", 0, 0, 180, 180, SDL_WINDOW_OPENGL );
	SDL_Renderer * t_rend = SDL_CreateRenderer( t_win, -1, SDL_RENDERER_ACCELERATED );
	SDL_Event * t_eve {nullptr};

	constexpr size_t elem = 9;

	ObstacleBoxWin<SDL_Rect, ObstacleWin> obt( t_eve, elem, "../fig/worms02.bmp" );


	//test: addDimBox
	{

	SDL_Rect t_dimBox {100, 120, 50, 80};

		for( size_t f = 0; f < elem+10; ++f ) {
			obt.addDimBox( t_dimBox );
		}


	size_t td = 5;
	SDL_Rect t_dimBox2[td];

	obt.getDimBox(t_dimBox2, td);

		for ( size_t t = 0; t < td; ++t ) {
			if( t_dimBox2[t].x == t_dimBox.x && t_dimBox2[t].y == t_dimBox.y &&
				t_dimBox2[t].w == t_dimBox.w && t_dimBox2[t].h == t_dimBox.h )
				{
					testResult.addDimBox = true;
					testResult.getDimBox = true;
				}
			else
				{
					testResult.addDimBox = false;
					break;
				}
		}

	} //addDimBox

	obt.resetTop();
	//test: addObstacleBox
	{

		ObstacleWin t_obwin;
		SDL_Rect t_dimBox1 {100, 120, 500, 800};
		SDL_Rect t_dimBox2 {100, 100, 400, 400};

		t_obwin.init( "../fig/worms02.bmp", &t_dimBox1, &t_dimBox2 );

		obt.addObstacleBox( t_obwin );


		ObstacleWin t_obwin2;

		obt.getObstacleBox( &t_obwin2, 1 );

		if( t_obwin2.show() ) {
			testResult.addObstacleBox = true;
			testResult.getObstacleBox = true;
		}
		else {
			testResult.addObstacleBox = false;
			testResult.getObstacleBox = false;
		}

		t_obwin2.hide();
	}//addObstacleBox



	std::cout << "\nOBSTACLE BOX WIN :: test()\n";
	std::cout << "addDimBox:\t" << testResult.addDimBox << std::endl;
	std::cout << "getDimBox:\t" << testResult.getDimBox << std::endl;
	std::cout << "addObstacleBox:\t" << testResult.addObstacleBox << std::endl;
	std::cout << "getObstacleBox:\t" << testResult.getObstacleBox << std::endl;



	return false;
}

#endif
