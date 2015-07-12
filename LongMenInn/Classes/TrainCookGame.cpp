#include "TrainCookGame.h"

#include <ctime>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace cocos2d;

long millisecondNow()  
{ 
	struct cc_timeval now; 
	CCTime::gettimeofdayCocos2d(&now, NULL); 
	return (now.tv_sec * 1000 + now.tv_usec / 1000); 
} 

// on "init" you need to initialize your instance
bool TrainCookGame::init()
{


	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(0, 0, 0, 125)));

		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////

		this->setTouchEnabled(true);
		//////////////////////////////////////////////////////////////////////////
		// add your codes below...
		//////////////////////////////////////////////////////////////////////////

		// Get window size and place the label upper. 
		CCSize size = CCDirector::sharedDirector()->getWinSize();

		// Add the label to TrainCookGame layer as a child layer.	

		CCSprite* pSprite = CCSprite::create("numBackground.jpg");
		CC_BREAK_IF(! pSprite);

		// Place the sprite on the center of the screen
		pSprite->setPosition(ccp(size.width/2, size.height/2));

		// Add the sprite to TrainCookGame layer as a child layer.
		this->addChild(pSprite, 0);

		CCMenuItemFont *pCloseItem = CCMenuItemFont::create(
			"QUIT",
			this,
			menu_selector(TrainCookGame::menuCloseCallback));
		CC_BREAK_IF(! pCloseItem);

		pCloseItem->setFontSize(30);
		pCloseItem->setColor(ccc3(0,0,0));
		// Place the menu item bottom-right conner.
		pCloseItem->setPosition(ccp(pSprite->getContentSize().width - pCloseItem->getContentSize().width / 2, 
			pCloseItem->getContentSize().width / 2));

		// Create a menu with the "close" menu item, it's an auto release object.
		CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
		pMenu->setPosition(CCPointZero);
		CC_BREAK_IF(! pMenu);

		// Add the menu to TrainCookGame layer as a child layer.
		pSprite->addChild(pMenu, 1);

		// 2. Add a label shows "Hello World".

		struct cc_timeval now; 
		CCTime::gettimeofdayCocos2d(&now, NULL); 

		gameTime = -1;
		startTime = now.tv_sec;
		char str[40];
		sprintf(str,"%d",startTime);

		// Create a label and initialize with string "Hello World".
		// 		CCLabelTTF* pLabel = CCLabelTTF::create("Score:0", "Arial", 24);
		// 		CC_BREAK_IF(! pLabel);
		// 		pLabel->setPosition(ccp(pSprite->getContentSize().width / 2, pSprite->getContentSize().height - 50));
		// 		pSprite->addChild(pLabel, 1,1);

		CCSprite *p = CCSprite::create("q1.png");
		picWidth = p->getContentSize().width;
		picHeight = p->getContentSize().height;
		picScale = 1.0;

		picNum = 6;
		reNum = 6;
		verNum = horNum = picNum;
		isFirst = 1;
		remainNum = picNum * reNum;
		score = 0;
		isEnd = false;

		RandVal();
		getPicArr();
		bRet = true;
	} while (0);



	return bRet;
}

void TrainCookGame::menuCloseCallback(CCObject* pSender)
{
	// "close" menu item clicked
	//this->removeFromParentAndCleanup(true);
	CCNotificationCenter::sharedNotificationCenter()->postNotification("CloseTrainCookGame", (CCObject*)gameTime);
}


//生成随机数组存放图片位置
void TrainCookGame::RandVal()
{
	int nVer = (picNum*reNum)/horNum; 
	verNum = nVer;
	RanArr = new int* [nVer+2];
	isExist = new bool* [nVer+2];
	for (int i=0;i<nVer+2;i++)
	{
		RanArr[i] = new int [horNum+2];
		isExist[i] = new bool[horNum + 2];
	}

	for (int j=0;j<nVer+2;j++)
	{
		RanArr[j][0] = -1;
		RanArr[j][horNum+1] = -1;
		isExist[j][0] = false;
		isExist[j][horNum+1] = false;
	}
	for (int j=0;j<horNum+2;j++)
	{
		RanArr[0][j] = -1;
		RanArr[nVer + 1][j] = -1;
		isExist[0][j] = false;
		isExist[nVer + 1][j] = false;
	}


	int NeedRanNum;
	int* NumTim;

	NumTim = new int[picNum+1];
	for (int k=1;k<=picNum;k++)
	{
		NumTim[k] = 0;
	}
	NeedRanNum = picNum;


	//保证每种图片重复次数为偶数
	srand(unsigned(time(0)));
	for (int j=1;j<nVer+1;j++)
	{
		for (int k=1;k<horNum+1;k++)
		{

			int RandNum = rand() % NeedRanNum + 1;
			while(NumTim[RandNum] >= reNum)
			{
				RandNum = rand() % NeedRanNum + 1;
			}
			RanArr[j][k] = RandNum;
			isExist[j][k] = true;
			NumTim[RandNum]++;
		}
	}

}

//通过产生的随机数组载入相应图片，绘制精灵
void TrainCookGame::getPicArr()
{
	picArr = new CCSprite** [verNum+2];
	for (int i=0;i<verNum+2;i++)
	{
		picArr[i] = new CCSprite* [horNum+2];
	}

	char picName[40];
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	float kx = size.width/2.0 - (verNum / 2.0 - 0.5)* picWidth * picScale;
	float ky = size.height /2.0 - (horNum / 2.0 - 0.5)* picHeight * picScale ;

	for (int i=1;i<horNum+1;i++)
	{
		for (int j=1;j<verNum+1;j++)
		{
			sprintf(picName,"q%d.png",RanArr[i][j]);
			CCSprite* pPic = CCSprite::create(picName);
			picArr[i][j] = pPic;

			//pPic->retain();
			CC_BREAK_IF(! pPic);


			pPic->setScale(picScale);
			pPic->setPosition(ccp(kx,ky));
			this->addChild(pPic, 0);

			kx += picWidth * picScale;
		}
		ky += picHeight * picScale;
		kx = size.width/2.0 - (verNum / 2.0 - 0.5)* picWidth * picScale;

	}


}

void TrainCookGame::touchDelegateRetain()
{
	//this->retain();
}

void TrainCookGame::touchDelegateRelease()
{
	//this->release();
}


//获取鼠标的位置
void TrainCookGame::ccTouchesEnded( cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent )
{
	CCSetIterator it = pTouches->begin();
	CCTouch* pTouch = (CCTouch*)(*it);

	CCPoint touchLocation = pTouch->getPreviousLocationInView();
	touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
	mouseLoc = touchLocation;

	this->update(0.1f);
}

//更新，当游戏结束时给出游戏提示
void TrainCookGame::update(float dt)
{
	int x,y;
	getTouchPicXY(x,y);
	getClickXYs(x,y);

	char str[80];
	sprintf(str,"Score:%d",score);

	// Create a label and initialize with string "Hello World".
	// 	CCLabelTTF* pLabel = (CCLabelTTF*)getChildByTag(1);
	// 	removeChild(pLabel);
	// 	pLabel = CCLabelTTF::create(str, "Arial", 24);
	// 	// Get window size and place the label upper. 
	// 	CCSize size = CCDirector::sharedDirector()->getWinSize();
	// 	pLabel->setPosition(ccp(size.width / 2, size.height - 50));
	// 
	// 	// Add the label to TrainCookGame layer as a child layer.
	// 	this->addChild(pLabel, 1,1);

	if(remainNum <= 0)
	{
		struct cc_timeval now; 
		CCTime::gettimeofdayCocos2d(&now, NULL); 
		gameTime = now.tv_sec - startTime;
		CCNotificationCenter::sharedNotificationCenter()->postNotification("CloseTrainCookGame",(CCObject *)gameTime);
	}
}


//获取鼠标相对于的图片数组的位置
void TrainCookGame::getTouchPicXY( int &touchX,int &touchY )
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	float startX = size.width /2.0 - (verNum / 2.0 )* picWidth * picScale ;
	float startY = size.height /2.0 - (horNum / 2.0 )* picHeight * picScale ;

	touchY = (mouseLoc.x - startX) / (picWidth * picScale) + 1;
	touchX = (mouseLoc.y - startY) / (picHeight * picScale)  + 1;

}

//获取鼠标连续2次点击的坐标并判断是否可以消除
void TrainCookGame::getClickXYs( int x,int y)
{
	if(x >= 1 && x <= verNum && y >= 1 && y <= horNum && isExist[x][y])
	{
		if (isFirst)
		{	
			x1 = x;
			y1 = y;		
			isFirst = 0;
			turnGray(x1,y1);
		}
		else
		{
			if(RanArr[x1][y1] != RanArr[x][y])
			{
				turnColor(x1,y1);
				x1 = x;
				y1 = y;
				turnGray(x1,y1);
			}
			else if(!(x1 == x && y1 == y))
			{
				x2 = x;
				y2 = y;
				if (canBeDelete())
				{
					isFirst = 1;
					isExist[x1][y1] = false;
					isExist[x2][y2] = false;
					score += 2;
					remainNum -= 2;
					this->removeChild(picArr[x1][y1]);
					this->removeChild(picArr[x2][y2]);
				}
				else
				{
					turnColor(x1,y1);
					x1 = x;
					y1 = y;
					turnGray(x1,y1);
				}

			}
		}
	}
}

//将图片变灰色
void TrainCookGame::turnGray( int x,int y )
{
	int curX = picArr[x][y]->getPositionX();
	int curY = picArr[x][y]->getPositionY();
	picArr[x][y]->setColor(ccc3(128,128,128));
}

//将图片变彩色
void TrainCookGame::turnColor( int x,int y )
{
	int curX = picArr[x][y]->getPositionX();
	int curY = picArr[x][y]->getPositionY();
	this->removeChild(picArr[x][y]);

	char picName[40];
	sprintf(picName,"q%d.png",RanArr[x][y]);
	CCSprite* pPic = CCSprite::create(picName);
	picArr[x][y] = pPic;

	pPic->retain();
	pPic->setScale(picScale);
	pPic->setPosition(ccp(curX,curY));
	this->addChild(pPic, 0);

}

//判断是否可以消除
bool TrainCookGame::canBeDelete()
{

	//判断有以下几种情况：
	//1.x、y轴水平可消
	//2.通过(x1,y2)或(x2,y1)一点可以分别相连可消
	//3.通过((z,y1)与(z,y2)）或((x1,z)与(x2,z))两点作为转点相连可消


	//第一种特殊情况
	if ((x1 == x2&&IsEmptyLine(y1,y2,x1,1))||(y1 == y2&&IsEmptyLine(x1,x2,y1,0)))
	{
		return true;
	}
	//第二种情况
	if (IsEmptyLine(x1,x2,y2,0)&&IsEmptyLine(y1,y2,x1,1))
	{
		//折点必须为空
		if (!isExist[x1][y2])
		{
			return true;
		}
	}
	if (IsEmptyLine(x1,x2,y1,0)&&IsEmptyLine(y1,y2,x2,1))
	{			
		//折点必须为空
		if (!isExist[x2][y1])
		{
			return true;
		}
	}
	//第三种情况
	for (int i=0;i<=verNum+1;i++)
	{
		if (i == x2||i == x1||y1 == y2)
		{
			continue;
		}
		if (IsEmptyLine(i,x2,y2,0,1)&&IsEmptyLine(y1,y2,i,1,1)&&IsEmptyLine(i,x1,y1,0,1))
		{
			if (!isExist[i][y2] &&!isExist[i][y1])
			{
				return true;
			}
		}
	}
	for (int i=0;i<=horNum+1;i++)
	{
		if (i == y1||i == y2 || x1 == x2)
		{
			continue;
		}
		if (IsEmptyLine(i,y1,x1,1,1)&&IsEmptyLine(x1,x2,i,0,1)&&IsEmptyLine(i,y2,x2,1,1))
		{
			if (!isExist[x1][i]|| !isExist[x2][i])
			{
				return true;
			}
		}
	}

	return false;

}

//判断路径是否没有障碍
bool TrainCookGame::IsEmptyLine( const int a,const int b,const int FixXY,const int RgtXY /*= 0*/,const int Rgt /*= 0*/ ) const
{
	if ((a == b||a == b+1 || b == a+1)&&Rgt == 0)
	{
		return true;
	}
	int Min = a<b?a:b;
	int Max = a>b?a:b;
	for (int i = Min+1;i < Max;i++)
	{
		if (RgtXY == 0&&isExist[i][FixXY])
		{
			return false;
		}
		if (RgtXY == 1&&isExist[FixXY][i])
		{
			return false;
		}
	}
	return true;
}

















