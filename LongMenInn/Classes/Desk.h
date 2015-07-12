#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class Desk
{
public:
	Desk(void);
	~Desk(void);
	CCSprite *deskSprite;
	CCSprite *foodSprite;
	bool isTaken;
	CCPoint loc;
};

