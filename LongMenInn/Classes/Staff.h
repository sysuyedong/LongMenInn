#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class Staff
{
public:
	Staff(void);
	~Staff(void);
	int getSalary();
	CCSprite *pSprite;
protected:
	int salary;
};

