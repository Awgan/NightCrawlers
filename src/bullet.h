#ifndef BULLET_H
#define BULLET_H

#include "point.h"
#include "comm_const.h"



class Bullet : public Point
{

protected:

	struct Bulletproperty
	{
		int damage;
		int angle;
	};

private:

	Bulletproperty property;

protected:

	Bullet( const Bullet & __bullet ){}
	Bullet(){}

public:

	Bullet( const Point * __point );
	Bullet( const Point * __point, const int angle );
	~Bullet();

	Bullet & operator=(const Bullet & __bullet);

	void disapear();

};

#endif
