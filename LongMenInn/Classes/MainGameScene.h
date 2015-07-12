#ifndef __MAINGAME_SCENE_H__
#define __MAINGAME_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Waiter.h"
#include "Cook.h"
#include "Manager.h"
#include "Desk.h"
#include "Customer.h"
#include "MathGameLayer.h"
#include "TrainCookGame.h"
#include "ManagerMenu.h"
#include "EndScene.h"

using namespace cocos2d;

#define DESK_COL 4
#define DESK_ROW 4
//行走速度
#define SPEED 250

class MainGame : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(MainGame);
	void tick(float dt);
	void tick2(float dt);
	void generateCustomer(float time);
	int getEmptyDesk();
	void moveToLoc(int deskId, CCPoint loc, bool isLeave);
	void deleteSprite(CCNode* sender, void* deskId);
	void addFood(CCNode* sender, void* deskId);
	void callMathGame(CCObject* pSender);
	void callMenu(CCObject* pSender);
	void trainStaff(CCObject* pSender);
	void trainWaiter(CCObject* pSender);
	void trainCook(CCObject* pSender);
	void trainManager(CCObject* pSender);
	void updateMoney();

	void cleanFood(CCObject* pSender);
	void removeFood(CCNode* sender, void* deskId);
	void setWaiterFree(CCNode* sender, void* waiterId);

	void onEnter();
	void onExit();
	void managerMenuFunc(CCObject *pSender);
	void closeTrainCookGame(CCObject *pSender);
	void closeMathGame(CCObject *pSender);

	void MoveWaiterToLoc(Waiter* aWaiter, CCPoint loc, bool isLeave, int deskId);
private:
	CCSize size;
	//地板瓦片地图
	CCTMXTiledMap *map;
	//桌子列表
	Desk *deskList;
	//跑堂
	Waiter *waiter;
	//厨师
	Cook *cook;
	//掌柜
	Manager *manager;
	//顾客列表
	Customer *customerList;
	//顾客数量
	int customerNum;
	//金钱
	int money;
	//时间
	int runTime;
	//时间表
	CCLabelTTF* timeLabel;
	//金钱
	CCLabelTTF* moneyLabel;
	CCSpriteFrameCache *cache;
	CCLabelTTF *costInfo;

	//算术小游戏
	MathGameLayer *mathGameLayer;
	bool mathGameIsStart;


	//训练
	CCSprite *background;
	CCMenu* trainMenu;

	CCMenu *foodMenu;				//将食物弄成菜单以便选择
	ManagerMenu *managerMenuLayer;  //管理菜单层
	TrainCookGame *trainCookGame;
	CCMenu *waiterMenu;
	CCArray *waiters;               //跑堂列表
	CCArray *cooks;                 //厨师列表   
	int activeWaiterId;    //激活的跑堂id

	//桌子数目
	int desk_row;
	int desk_col;

	bool managerMenuIsStart;
};

#endif  // __MAINGAME_SCENE_H__