#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class Customer : public CCNode
{
public:
	Customer(void);
	~Customer(void);
	CCSprite *pSprite;
	float runTime;
	int stayTime;
	bool isLeave;
};