#ifndef _TRAINCOOK_GAME_H__
#define _TRAINCOOK_GAME_H__

#include "cocos2d.h"
USING_NS_CC;

class TrainCookGame : public cocos2d::CCLayerColor
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	//´¥Ãþ
	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	virtual void touchDelegateRetain();
	virtual void touchDelegateRelease();

	//Ã¿Ö¡¸üÐÂ
	void update(float dt); 

	// a selector callback
	void menuCloseCallback(CCObject* pSender);
	void menuRestartCallback(CCObject* pSender);

	// implement the "static node()" method manually
	CREATE_FUNC(TrainCookGame);

	void RandVal();
	void getPicArr();

	void getTouchPicXY(int &touchX,int &touchY);
	void getClickXYs(int x,int y);
	void turnGray(int x,int y);
	void turnColor(int x,int y);

	bool canBeDelete();
	bool IsEmptyLine(const int a,const int b,const int FixXY,const int RgtXY,const int Rgt = 0)const;
private:
	int **RanArr;
	bool **isExist;
	cocos2d::CCSprite*** picArr;
	int picNum;
	int reNum;
	int horNum;
	int verNum;
	int x1,y1;
	int x2,y2;
	int isFirst;
	int startTime;
	int gameTime;
	bool isEnd;
	int score;
	int remainNum;
	float picWidth;
	float picHeight;
	float picScale;
	cocos2d::CCPoint mouseLoc;

};

#endif  