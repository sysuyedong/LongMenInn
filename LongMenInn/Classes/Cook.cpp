#include "Cook.h"


Cook::Cook(void)
{
}

Cook::Cook( int cook, int h, int sa )
{
	cookingSkill = cook;
	health = h;
	salary = sa;
	pSprite = NULL;
}


Cook::~Cook(void)
{
}

int Cook::getCookingSkiil()
{
	return cookingSkill;
}

int Cook::getHealth()
{
	return health;
}

void Cook::train(int v)
{
	cookingSkill += v;
	health += v;
}
