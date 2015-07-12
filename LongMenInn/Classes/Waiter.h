#pragma once
#include "staff.h"
#include "cocos2d.h"

using namespace cocos2d;

class Waiter :
	public Staff
{
public:
	Waiter(void);
	Waiter(int s, int q, int sa);
	~Waiter(void);
	int getSpeed();
	int getQuality();
	int getId();
	void setId(int i);
	bool isBusy();
	void setBusy(bool b);
	void train(int v);
	CCMenuItemSprite *pMenuItem;
	CCPoint loc;
private:
	int speed;
	int quality;
	int id;
	bool busy;
};

