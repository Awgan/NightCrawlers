#ifndef PROPERTY_H_
#define PROPERTY_H_

#define DEF_HEALTH 			1
//#define DEF_MOVE_POINTS		5
#define DEF_SPEED 			1

#include "comm_const.h"


struct Stru_property {
	
	Point_type	type;	
	
	bool 	b_mobile;
	bool 	b_visible;
	
	int 	i_health;			
	int 	i_speed;
	int 	i_move_points;
	int		i_move_distance;	// indicates distance which an object can move after pushing; '-1' value means that an object can't be pushed
	int 	i_strenght;
	int 	i_fire_accuracy;
	
	//int ...
	void show();
	
	Stru_property & operator=( const Stru_property & _sgp );
};



class Property {

	private:
		Stru_property prop;
		
	protected:

	public:
		Property();
		Property( Stru_property & _prop );
		~Property();

		//point type
		void set_point_type( const Point_type & _pt ) 	{ prop.type = _pt; };
		const Point_type & get_point_type() 			{ return prop.type; };
		
		//mobile
		bool is_mobile() const					{ return prop.b_mobile; }
		void set_mobile( bool _b ) 				{ prop.b_mobile = _b; }
		
		//visible
		bool is_visible() const					{ return prop.b_visible; }		
		void set_visible( bool _b )				{ prop.b_visible = _b; }
		
		//health
		void set_healt( int _h );
		void change_health( int _dh );
		const int & get_health() const			{ return prop.i_health; }
		
		//speed
		void set_speed( int _s );
		void change_speed( int _ds );
		const int & get_speed() const			{ return prop.i_speed; }
		
		//move points
		void set_move_points( int _mp );
		void change_move_points( int _dm );
		const int & get_move_points() const		{ return prop.i_move_points; }
		
		//move distance
		void set_move_distance( int _md );
		void change_move_distance( int _d_md );
		const int & get_move_distance() const	{ return prop.i_move_distance; }
		
		//strenght
		void set_strenght( int _s );
		void change_strenght( int _ds );
		const int & get_strenght() const		{ return prop.i_strenght; }
		
		//fire accuracy
		void set_fire_accuracy( int _fa );
		void change_fire_accuracy( int _dfa );
		const int & get_fire_accuracy() const	{ return prop.i_fire_accuracy; }
		
		
		Property & operator=( const Property & _prop );
		
		//metody typu get
		
		//metody typu set
		
		//metody typu  
		
		void print() const;
		
		void print_type() const ;
		
};

#endif
