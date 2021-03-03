/*
 * Class for showing gunpoint and choose direction of bullet move
 */


#ifndef GUNPOINT_H_
#define GUNPOINT_H_

#include <SDL2/SDL.h>

#include "comm_const.h"
#include "win_general.h"

class Gunpoint : public WinGenSDL
{
	protected:
		struct gp_position
		{
			int angle;
			int center_x;
			int center_y;
			int distance;
		};

	private:
		gp_position position;

	protected:

	public:
		Gunpoint( const int centerx = 0, const int centery = 0);
		~Gunpoint(){};

		//void calculate();											/* calculate gunpoint's parameter */
		void setcenterposition( const int x, const int y ); 		/* Set position */
		void setcenterangle( const int ang );
		void getcenterposition( int * x, int * y ); 				/* Get position */
		void changecenterposition( const int dx, const int dy );	/* Change center position by adding or subtracting */
		void changecenterangle( const int da );						/* Change angle */
		void updateposition();										/* Update visible position */

		//const int getXmoveinterval();		/* get x interval for moving */
		//const int getYmoveinterval();		/* get y interval for moving */

		virtual bool show();
		bool hide();

};

#endif
