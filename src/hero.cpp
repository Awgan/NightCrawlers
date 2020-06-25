#include <SDL2/SDL.h>

#include "hero.h"

Hero::Hero( SDL_Renderer * _rend, Coordinate & _coor ) : Point( _coor ) {

	SDL_th.rend = _rend;
	
}
