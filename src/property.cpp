#include <cstdio>
#include <iostream>

#include "property.h"

Stru_property & Stru_property::operator=( const Stru_property & _sgp ) {
	
	if ( this == &_sgp )
		return *this;
		
	type = _sgp.type;	
	
	b_mobile = _sgp.b_mobile;
	b_visible = _sgp.b_visible;
	
	i_health = _sgp.i_health;			
	i_speed = _sgp.i_speed;
	i_move_points = _sgp.i_move_points;
	i_move_distance	= _sgp.i_move_distance;
	i_strenght = _sgp.i_strenght;
	i_fire_accuracy = _sgp.i_fire_accuracy;
	
	return *this;
}

void Stru_property::show() {
	
	std::cout << "PROPERTY show() > type: " << (int)type << " mobile: " << b_mobile << " visible: " << b_visible << " health: " << i_health << " speed: " << i_speed << " move_p: " << i_move_points << " strenght: " << i_strenght << " fire: " << i_fire_accuracy << std::endl;
}


Property::Property() {
	
	prop.type				= Point_type::hero;
	
	prop.b_mobile 			= true;
	prop.b_visible 			= true;

	prop.i_health 			= 100;
	prop.i_speed 			= 15;
	prop.i_move_points 		= 45;
	prop.i_move_distance	= 0;
	prop.i_strenght 		= 60;
	prop.i_fire_accuracy 	= 46;
	
}


Property::Property( Stru_property & _prop ) {

		prop.type				= _prop.type;

		prop.b_mobile 			= _prop.b_mobile;
		prop.b_visible 			= _prop.b_visible;
		
//TODO:: add condition for eliminate values out of range
		prop.i_health 			= _prop.i_health;
		prop.i_speed 			= _prop.i_speed;
		prop.i_move_points 		= _prop.i_move_points;
		prop.i_move_distance	= _prop.i_move_distance;
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


//move distance
void Property::set_move_distance( int _md ) {
	
	prop.i_move_distance = _md;
	if ( prop.i_move_distance < 0 )
		prop.i_move_distance = 0;
}

void Property::change_move_distance( int _d_md ) {
	
	prop.i_move_distance += _d_md;
	if ( prop.i_move_distance < 0 )
		prop.i_move_distance = 0;
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

Property & Property::operator=( const Property & _prop ) {
	
	if ( this == &_prop )
		return *this;
	
	prop = _prop.prop;
	
	return *this;
	
}


void Property::print() const {
	
	printf("mobile: %d\nvisible: %d\nhealth: %d\nspeed: %d\nmove points: %d\nstenght: %d\nfire accuracy: %d\n",
	prop.b_mobile, prop.b_visible, prop.i_health, prop.i_speed,	prop.i_move_points, prop.i_strenght, prop.i_fire_accuracy);
	print_type();
}

void Property::print_type() const {
	
	std::cout << "type: ";
	
	switch(prop.type) {
		case neutral:
			std::cout << "neutral\n";
		break;
		case hero:
			std::cout << "hero\n";
		break;
		case bullet:
			std::cout << "bullet\n";
		break;
		case obstacle:
			std::cout << "obstacle\n";
		break;
		default:
		break;		
	}
}
