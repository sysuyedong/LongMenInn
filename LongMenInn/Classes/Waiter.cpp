#include "Waiter.h"


Waiter::Waiter(void)
{
}

Waiter::Waiter( int s, int q, int sa)
{
	speed = s;
	quality = q;
	salary = sa;
	pSprite = NULL;
	pMenuItem = NULL;
	id = 0;
	busy = false;
}


Waiter::~Waiter(void)
{
}

int Waiter::getSpeed()
{
	return speed;
}

int Waiter::getQuality()
{
	return quality;
}

void Waiter::train(int v)
{
	speed += v;
	quality += v;
}

int Waiter::getId()
{
	return id;
}

bool Waiter::isBusy()
{
	return busy;
}

void Waiter::setBusy( bool b )
{
	busy = b;
}

void Waiter::setId( int i )
{
	id = i;
}
