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
//�����ٶ�
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
	//�ذ���Ƭ��ͼ
	CCTMXTiledMap *map;
	//�����б�
	Desk *deskList;
	//����
	Waiter *waiter;
	//��ʦ
	Cook *cook;
	//�ƹ�
	Manager *manager;
	//�˿��б�
	Customer *customerList;
	//�˿�����
	int customerNum;
	//��Ǯ
	int money;
	//ʱ��
	int runTime;
	//ʱ���
	CCLabelTTF* timeLabel;
	//��Ǯ
	CCLabelTTF* moneyLabel;
	CCSpriteFrameCache *cache;
	CCLabelTTF *costInfo;

	//����С��Ϸ
	MathGameLayer *mathGameLayer;
	bool mathGameIsStart;


	//ѵ��
	CCSprite *background;
	CCMenu* trainMenu;

	CCMenu *foodMenu;				//��ʳ��Ū�ɲ˵��Ա�ѡ��
	ManagerMenu *managerMenuLayer;  //����˵���
	TrainCookGame *trainCookGame;
	CCMenu *waiterMenu;
	CCArray *waiters;               //�����б�
	CCArray *cooks;                 //��ʦ�б�   
	int activeWaiterId;    //���������id

	//������Ŀ
	int desk_row;
	int desk_col;

	bool managerMenuIsStart;
};

#endif  // __MAINGAME_SCENE_H__