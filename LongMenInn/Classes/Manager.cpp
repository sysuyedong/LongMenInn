#include "Manager.h"


Manager::Manager(void)
{
}

Manager::Manager( int com, int care, int sa )
{
	computation = com;
	carefulness = care;
	salary = sa;
	pSprite = NULL;
}


Manager::~Manager(void)
{
}

int Manager::getComputation()
{
	return computation;
}

int Manager::getCarefulness()
{
	return carefulness;
}

void Manager::train()
{
	carefulness += 2;
	computation += 2;
}
