#include "collision.h"
#include "position.h"
#include "point.h"

enum limits {lewy = 0, gora = 0, prawy = 100, dol = 100 };

Point::Graphic_Prop proper = {"brak", 15, 15};
Coordinate corod_m = {45, 65, 0, CoorDir::right};
Coordinate corod_k = {40, 60, 0, CoorDir::left};

int main () {
	
	
	Collision kont;
	
	Point mrowka( proper, corod_m );
	mrowka.set_lim_min(lewy, gora);
	mrowka.set_lim_max(prawy, dol);
	mrowka.set_point_type( hero );
	
	Point kolatek( proper, corod_k );
	kolatek.set_lim_min(lewy, gora);
	kolatek.set_lim_max(prawy, dol);
	kolatek.set_point_type( bullet );
	
	Point biedronka( proper, corod_m );
	biedronka.set_lim_min(lewy, gora);
	biedronka.set_lim_max(prawy, dol);
	biedronka.set_point_type( hero );
	
	Point konik( proper, corod_m );
	biedronka.set_lim_min(lewy, gora);
	biedronka.set_lim_max(prawy, dol);
	biedronka.set_point_type( hero );
	
	kont.add( &mrowka );
	kont.add( &kolatek );
	kont.add( &biedronka);
	kont.add( &konik );
	
	kolatek.move_dx(5);
	kolatek.move_dy(5);
	
	kont.list_all();
	kont.check_collision();
	kont.list_all();
	printf("5\n");
	
	
	return 0;
}
