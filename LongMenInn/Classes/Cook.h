#pragma once
#include "Staff.h"
class Cook :
	public Staff
{
public:
	Cook(void);
	Cook(int cook, int h, int sa);
	~Cook(void);
	int getCookingSkiil();
	int getHealth();
	void train(int v);
private:
	int cookingSkill;
	int health;
};

