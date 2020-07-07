#include <cstdio>

#include "property.h"

Property::Property( Stru_property & _prop ) {



		prop.b_mobile 			= _prop.b_mobile;
		prop.b_visible 			= _prop.b_visible;
		
//TODO:: add condistion for eliminate values out of range
		prop.i_health 			= _prop.i_health;
		prop.i_speed 			= _prop.i_speed;
		prop.i_move_points 		= _prop.i_move_points;
		prop.i_strenght 		= _prop.i_strenght;
		prop.i_fire_accuracy 	= _prop.i_fire_accuracy;
}
Property::~Property() {
	
	
}


//health
void Property::set_healt( int _h ) {
	
	//TODO:: create MAX values for all property in "comm_const.h" file
	prop.i_health = _h;
	if ( prop.i_health < 0 )
		prop.i_health = 0;
	
}
void Property::change_health( int _dh ) {
	
	prop.i_health += _dh;
	if ( prop.i_health < 0 )
		prop.i_health = 0;
}


//speed
void Property::set_speed( int _s ) {
	
	prop.i_speed = _s;
	if ( prop.i_speed < 0 )
		prop.i_speed = 0;
		
}
void Property::change_speed( int _ds ) {
	
	prop.i_speed += _ds;
	if ( prop.i_speed < 0 )
		prop.i_speed = 0;

}


//move points
void Property::set_move_points( int _mp ) {
	
	prop.i_move_points = _mp;
	if ( prop.i_move_points < 0 )
		prop.i_move_points = 0;
		
}
void Property::change_move_points( int _dm ) {
	
	prop.i_move_points += _dm;
	if ( prop.i_move_points < 0 )
		prop.i_move_points = 0;

	
}


//strenght
void Property::set_strenght( int _s ) {
	
	prop.i_strenght = _s;
	if ( prop.i_strenght < 0 )
		prop.i_strenght = 0;
	
}
void Property::change_strenght( int _ds ) {
	
	prop.i_strenght += _ds;
	if ( prop.i_strenght < 0 )
		prop.i_strenght = 0;
	
}


//fire accuracy
void Property::set_fire_accuracy( int _fa )	{
	
	prop.i_fire_accuracy = _fa;
	if ( prop.i_fire_accuracy < 0 )
		prop.i_fire_accuracy = 0;
	
}
void Property::change_fire_accuracy( int _dfa ) {
	
	prop.i_fire_accuracy += _dfa;
	if ( prop.i_fire_accuracy < 0 )
		prop.i_fire_accuracy = 0;
	
}


void Property::print() {
	
	printf("mobile: %d\nvisible: %d\nhealth: %d\nspeed: %d\nmove points: %d\nstenght: %d\nfire accuracy: %d\n",
	prop.b_mobile, prop.b_visible, prop.i_health, prop.i_speed,	prop.i_move_points, prop.i_strenght, prop.i_fire_accuracy);
	
}
