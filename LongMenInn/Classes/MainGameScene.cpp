#include "MainGameScene.h"
#include <time.h>
#include <string>

using namespace cocos2d;

CCScene* MainGame::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        MainGame *layer = MainGame::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainGame::init()
{
	//初始化桌子数目
	desk_col = desk_row = 4;
    bool bRet = false;
	//初始化顾客数量
	customerNum = 0;
	customerList = new Customer[6 * 6];
	money = 10000;
	mathGameIsStart = false;
	managerMenuIsStart = false;
	runTime = 0;
	costInfo = NULL;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

        //////////////////////////////////////////////////////////////////////////
        // add your codes below...
        //////////////////////////////////////////////////////////////////////////

        // 1. Add a menu item with "X" image, which is clicked to quit the program.

        // Create a "close" menu item with close icon, it's an auto release object.
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(MainGame::menuCloseCallback));
        CC_BREAK_IF(! pCloseItem);

        // Place the menu item bottom-right conner.
        pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

  
        // 2. Add a label shows "Hello World".

        // Create a label and initialize with string "Hello World".
    

		timeLabel = CCLabelTTF::create("Time:", "Arial", 24);
		CC_BREAK_IF(! timeLabel);

		char moneyLeft[20] = "Money: ";
		sprintf(moneyLeft, "%s%d", moneyLeft, money);

		moneyLabel = CCLabelTTF::create(moneyLeft, "Arial", 24);
		CC_BREAK_IF(! moneyLabel);

        // Get window size and place the label upper. 
        size = CCDirector::sharedDirector()->getWinSize();
        //pLabel->setPosition(ccp(size.width / 2, size.height - 50));
		timeLabel->setPosition(ccp(50, size.height - 50));
		moneyLabel->setPosition(ccp(size.width / 2, size.height - 50));

        // Add the label to HelloWorld layer as a child layer.
		this->addChild(timeLabel, 1);
		this->addChild(moneyLabel, 1);

		//生成地板
		map = CCTMXTiledMap::create("floor.tmx");
		this->addChild(map);

		//人物
		int col = 4, row = 4;
		cache = CCSpriteFrameCache::sharedSpriteFrameCache();
		cache->addSpriteFramesWithFile("coordinates.plist", "texture.png");
		CCSpriteFrame *strip = cache->spriteFrameByName("miku.png");
		CCTexture2D *texture = strip->getTexture();
		CCSize originalSize = strip->getOriginalSizeInPixels();
		CCRect stripRect = strip->getRect();
		float w = originalSize.width/col;
		float h = originalSize.height/row;
		float x = stripRect.origin.x;
		float y = stripRect.origin.y;

		CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(texture, CCRectMake(1, 1, w, h));

		//生成跑堂列表
		waiters = CCArray::create();
		waiters->retain();
		for (int i = 0 ;i < 1;i++)
		{
			Waiter *temp = new Waiter(5,5,1000);
			temp->pSprite = CCSprite::createWithSpriteFrame(frame);
			temp->pSprite->setPosition(ccp(size.width - 320, size.height - 50 * (i+1)));
			this->addChild(temp->pSprite, 1);
			temp->loc = temp->pSprite->getPosition();
			waiters->addObject((CCObject *)temp);
			temp->setId(i);		
		}	
		//生成厨师列表
		cooks = CCArray::create();
		cooks->retain();


		//生成人物
		//waiter = new Waiter(5, 5, 1500);
		manager = new Manager(5, 5, 1000);
		cook = new Cook(5, 5, 1000);
		//waiter->pSprite = CCSprite::createWithSpriteFrame(frame);
		frame = CCSpriteFrame::createWithTexture(texture, CCRectMake(128, 1, w, h));
		cook->pSprite = CCSprite::createWithSpriteFrame(frame);
		frame = CCSpriteFrame::createWithTexture(texture, CCRectMake(250, 1, w, h));
		manager->pSprite = CCSprite::createWithSpriteFrame(frame);
		
		//waiter->pSprite->setPosition(ccp(size.width - 320, size.height - 220));
		cook->pSprite->setPosition(ccp(size.width - 100, size.height - 120));
		manager->pSprite->setPosition(ccp(size.width - 100,size.height - 400));
		
		//this->addChild(waiter->pSprite, 1);
		this->addChild(cook->pSprite, 1);
		this->addChild(manager->pSprite, 1);
		cooks->addObject((CCObject*)cook);
		//生成桌子
		deskList = new Desk[6 * 6];
		for(int i = 0; i < desk_row; ++i){
			for(int j = 0; j < desk_col; ++j){
				deskList[i*6 + j].deskSprite = CCSprite::create("desk.png");
				deskList[i*6 + j].loc.setPoint(i*90 + 90, j*90 + 90);
				deskList[i*6 + j].deskSprite->setPosition(deskList[i*6 + j].loc);
				this->addChild(deskList[i*6 + j].deskSprite, 2);
			}
		}
		//生成厨房
		CCSprite *kitchenSprite = CCSprite::create("kitchen.jpg");
		kitchenSprite->setPosition(ccp(size.width - 150, size.height - 120));
		this->addChild(kitchenSprite);
		//生成柜台
		CCSprite *counterSprite = CCSprite::create("counter.jpg");
		counterSprite->setPosition(ccp(size.width - 100, size.height - 400));
		this->addChild(counterSprite, 0);

		CCMenuItemImage *menuItem = CCMenuItemImage::create(
			"menu1.png",
			"menu2.png",
			this,
			menu_selector(MainGame::callMenu));
		menuItem->setPosition(ccp(size.width - menuItem->getContentSize().width,menuItem->getContentSize().height));
		// Create a menu with the "close" menu item, it's an auto release object.
		CCMenu* pMenu = CCMenu::create(pCloseItem, menuItem, NULL);
		pMenu->setPosition(CCPointZero);
		CC_BREAK_IF(! pMenu);

		foodMenu = CCMenu::create();
		foodMenu->setPosition(CCPointZero);
		this->addChild(foodMenu,3);

		this->addChild(pMenu, 1);
        bRet = true;

    } while (0);
	//调用定时器
	this->schedule(schedule_selector(MainGame::tick),5.0f);
	this->schedule(schedule_selector(MainGame::tick2),1.0f);
	//设置屏幕可触屏
	this->setTouchEnabled(true);
    return bRet;
}

void MainGame::tick2( float dt )
{
	if(money < 0){
		CCScene *pScene = EndScene::scene();
		CCDirector::sharedDirector()->replaceScene(pScene);;
	}
	runTime++;
	char timeRun[20] = "Time: ";
	sprintf(timeRun, "%s%d", timeRun, runTime);
	timeLabel->setString(timeRun);
	//每隔一段时间支付工资
	int totalCost = 0;
	for(unsigned int i = 0; i < waiters->count(); ++i){
		Waiter *w = (Waiter*)waiters->objectAtIndex(i);
		totalCost += w->getSalary();
	}
	for(unsigned int i = 0 ; i < cooks->count(); ++i){
		Cook *c = (Cook*)cooks->objectAtIndex(i);
		totalCost += c->getSalary();
	}
	totalCost += manager->getSalary();
	if(runTime % 60 == 0){
		money -= totalCost;
		updateMoney();
	}
	//显示需要扣除的工资
	char strCost[50] = "Pay for the salary per minute: ";
	sprintf(strCost, "%s%d", strCost, totalCost);
	if(costInfo == NULL){
		costInfo = CCLabelTTF::create(strCost, "Arial", 24);
		costInfo->setPosition(ccp(200, 20));
		this->addChild(costInfo, 1);
	}
	else
		costInfo->setString(strCost);

	//在随机时间内生成一个顾客,根据厨师的厨艺和卫生情况决定
	srand((unsigned)time(NULL));
	int skill = 0;
	for(unsigned int i = 0; i < cooks->count(); ++i){
		Cook *c = (Cook*)cooks->objectAtIndex(i);
		skill += c->getCookingSkiil() + c->getHealth();
	}
	float t = (rand()%30 + 5) / skill;
	this->scheduleOnce(schedule_selector(MainGame::generateCustomer), t);
}

void MainGame::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

void MainGame::tick( float dt )
{
	//遍历一次顾客列表,让用餐完毕的顾客离开桌子
	for(int i = 0; i < desk_col; ++i)
		for(int j = 0; j < desk_row; ++j){
			if(deskList[i*6 + j].isTaken)
				customerList[i*6 + j].stayTime += 5;
			//顾客的用餐时间,由服务员的速度决定
			int speed = 0;
			for(unsigned int k = 0; k < waiters->count(); ++k){
				Waiter *w = (Waiter*)waiters->objectAtIndex(k);
				speed += w->getSpeed();
			}
			float eatTime = 100 / speed;
			if(!customerList[i*6 + j].isLeave && customerList[i*6 + j].stayTime - customerList[i*6 + j].runTime > eatTime){
				customerList[i*6 + j].isLeave = true;
				moveToLoc(i*6 + j, ccp(20,600), true);
			}
		}
}

void MainGame::generateCustomer( float time )
{
	//获得一个空桌子
	int deskId = getEmptyDesk();
	if(deskId != -1){
		//生成一个顾客
		CCSpriteFrame *strip = cache->spriteFrameByName("len.png");
		CCTexture2D *texture = strip->getTexture();
		CCSize originalSize = strip->getOriginalSizeInPixels();
		CCRect stripRect = strip->getRect();
		float w = originalSize.width/4;
		float h = originalSize.height/4;
		float x = stripRect.origin.x;
		float y = stripRect.origin.y;
		CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(texture, CCRectMake(x, y + h*3, w, h));
		customerList[deskId].pSprite = CCSprite::createWithSpriteFrame(frame);
		customerList[deskId].isLeave = false;
		customerList[deskId].stayTime = 0;
		customerList[deskId].runTime = 0;
		customerList[deskId].pSprite->setPosition(ccp(600,50));
		this->addChild(customerList[deskId].pSprite, 1);
		//移动到相应的空桌子
		CCPoint loc = deskList[deskId].deskSprite->getPosition();
		loc.y += 30;
		moveToLoc(deskId, loc, false);
	}
}

//获得空桌子ID
int MainGame::getEmptyDesk()
{
	for(int i = 0; i < desk_col; ++i)
		for(int j = 0; j < desk_row; ++j){
			if(!deskList[i * 6 + j].isTaken){
				deskList[i * 6 + j].isTaken = true;
				return i * 6 + j;
			}
		}
	return -1;
}

//顾客移动到相应地点
void MainGame::moveToLoc( int deskId , CCPoint loc, bool isLeave)
{
	CCPoint customerLoc = customerList[deskId].pSprite->getPosition();
	float yTime = fabs(loc.y - customerLoc.y)/SPEED;
	float xTime = fabs(loc.x - customerLoc.x)/SPEED;
	customerList[deskId].runTime = yTime + xTime;
	//获得对应图片
	CCSpriteFrame *strip = cache->spriteFrameByName("len.png");
	CCTexture2D *texture = strip->getTexture();
	CCSize originalSize = strip->getOriginalSizeInPixels();
	CCRect stripRect = strip->getRect();
	float w = originalSize.width/4;
	float h = originalSize.height/4;
	float x = stripRect.origin.x;
	float y = stripRect.origin.y;
	//生成y方向的动作
	CCArray *animFramesY = new CCArray(4);
	for (int j = 0; j < 4; j++)
	{
		CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(texture, CCRectMake(x, y + h*3, w, h));
		animFramesY->addObject(frame);
		x += w;
	}
	CCAnimation *animationY = CCAnimation::createWithSpriteFrames(animFramesY, 0.1f);
	CCActionInterval *stepActionY = CCAnimate::create(animationY);
	CCActionInterval *movetoActionY = CCMoveTo::create(yTime, ccp(customerLoc.x, loc.y));
	int repeatTimeY = yTime/0.4;
	CCRepeat *repeatY = CCRepeat::create(stepActionY, repeatTimeY);
	//生成x方向的动作
	x = stripRect.origin.x;
	CCArray *animFramesX = new CCArray(4);
	for (int j = 0; j < 4; j++)
	{
		CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(texture, CCRectMake(x, y + h, w, h));
		animFramesX->addObject(frame);
		x += w;
	}
	CCAnimation *animationX = CCAnimation::createWithSpriteFrames(animFramesX, 0.1f);
	CCActionInterval *stepActionX = CCAnimate::create(animationX);
	CCActionInterval *movetoActionX = CCMoveTo::create(xTime, loc);
	int repeatTimeX = xTime/0.4;
	CCRepeat *repeatX = CCRepeat::create(stepActionX, repeatTimeX);
	//完成移动后转向
	x = stripRect.origin.x;
	CCArray *animFrames = new CCArray(3);
	for (int j = 0; j < 3; j++)
	{
		CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(texture, CCRectMake(x, y, w, h));
		animFrames->addObject(frame);
		x += w;
	}
	CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1f);
	CCActionInterval *face = CCAnimate::create(animation);
	//执行移动动作
	if(!isLeave){
		CCSequence *sequenceMove = CCSequence::create(movetoActionY, movetoActionX, face,
			CCCallFuncND::create(this, callfuncND_selector(MainGame::addFood), (void*)deskId), NULL);
		customerList[deskId].pSprite->runAction(sequenceMove);
		CCSequence *sequenceStep = CCSequence::createWithTwoActions(repeatY, repeatX);
		customerList[deskId].pSprite->runAction(sequenceStep);
	}
	//离开的动作
	else{
		movetoActionX = CCMoveTo::create(xTime, ccp(loc.x, customerLoc.y));
		movetoActionY = CCMoveTo::create(yTime, loc);
		CCSequence *sequenceMove = CCSequence::create(movetoActionX, movetoActionY, 
			CCCallFuncND::create(this, callfuncND_selector(MainGame::deleteSprite), (void*)deskId), NULL);
		customerList[deskId].pSprite->runAction(sequenceMove);
		CCSequence *sequenceStep = CCSequence::createWithTwoActions(repeatX, repeatY);
		customerList[deskId].pSprite->runAction(sequenceStep);
	}
}

//离开之后的回调函数,删除精灵,获得金钱
void MainGame::deleteSprite( CCNode* sender, void* deskId )
{
	this->removeChild(customerList[(int)deskId].pSprite);
	//this->removeChild(deskList[(int)deskId].foodSprite);
	//foodMenu->removeChildByTag((int)deskId);
	//deskList[(int)deskId].isTaken = false;
	money += 100;
	char moneyLeft[20] = "Money: ";
	sprintf(moneyLeft, "%s%d", moneyLeft, money);
	moneyLabel->setString(moneyLeft);
}

//就坐后的回调函数,放置食物
void MainGame::addFood( CCNode* sender, void* deskId )
{
	//std::string food = "food" + ".jpg";
	int randNum = rand() % 4 + 1;
	char str[20];
	sprintf(str,"food%d.png",randNum);
	deskList[(int)deskId].foodSprite = CCSprite::create(str);
	CCPoint loc = deskList[(int)deskId].deskSprite->getPosition();
	loc.y += 10;
	CCMenuItemSprite *foodItem = CCMenuItemSprite::create(deskList[(int)deskId].foodSprite,NULL,NULL,this,menu_selector(MainGame::cleanFood));
	
	foodItem->setPosition(loc);
	foodMenu->addChild(foodItem,0,(int)deskId);
// 	deskList[(int)deskId].foodSprite->setPosition(loc);
// 	this->addChild(deskList[(int)deskId].foodSprite, 3);
}

void MainGame::callMathGame(CCObject* pSender)
{
	
	//调用算术小游戏
	if(!mathGameIsStart){
		mathGameLayer = MathGameLayer::create();
		this->addChild(mathGameLayer, 4);
		mathGameIsStart = true;
	}
}

void MainGame::trainStaff(CCObject* pSender)
{
	background = CCSprite::create("numBackground.jpg");
	background->setPosition(ccp(size.width/2, size.height/2));
	this->addChild(background, 3);
	CCMenuItemImage *trianW = CCMenuItemImage::create(
		"trainWaiter.png",
		"trainWaiter1.png",
		this,
		menu_selector(MainGame::trainWaiter));
	CCMenuItemImage *trianC = CCMenuItemImage::create(
		"trainCook.png",
		"trainCook1.png",
		this,
		menu_selector(MainGame::trainCook));
	CCMenuItemImage *trianM = CCMenuItemImage::create(
		"trainManager.png",
		"trainManager1.png",
		this,
		menu_selector(MainGame::trainManager));
	trianW->setPosition(ccp(size.width/2, size.height/2 + 150));
	trianC->setPosition(ccp(size.width/2, size.height/2));
	trianM->setPosition(ccp(size.width/2, size.height/2 - 150));
	trainMenu = CCMenu::create(trianW, trianC, trianM, NULL);
	trainMenu->setPosition(CCPointZero);


	this->addChild(trainMenu, 3);
}

void MainGame::trainWaiter( CCObject* pSender )
{
	for(unsigned int i = 0; i < waiters->count(); ++i){
		Waiter *w = (Waiter*)waiters->objectAtIndex(i);
		w->train(2);
	}
	money -= 1000;
	updateMoney();
	this->removeChild(background);
	this->removeChild(trainMenu);
}

void MainGame::trainCook( CCObject* pSender )
{
	for(unsigned int i = 0; i < cooks->count(); ++i){
		Cook *c = (Cook*)cooks->objectAtIndex(i);
		c->train(2);
	}
	money -= 1000;
	updateMoney();
	this->removeChild(background);
	this->removeChild(trainMenu);
}

void MainGame::trainManager( CCObject* pSender )
{
	manager->train();
	money -= 1000;
	updateMoney();
	this->removeChild(background);
	this->removeChild(trainMenu);
}

void MainGame::updateMoney()
{
	char moneyLeft[20] = "Money: ";
	sprintf(moneyLeft, "%s%d", moneyLeft, money);
	moneyLabel->setString(moneyLeft);
}

void MainGame::callMenu( CCObject* pSender )
{
	if(!managerMenuIsStart)
	{
		managerMenuLayer = ManagerMenu::create();
		this->addChild(managerMenuLayer,4);
		managerMenuIsStart = true;
	}

}

void MainGame::cleanFood( CCObject* pSender )
{
	CCMenuItem* item =(CCMenuItem *)(pSender);
	int deskId = item->getTag();
	if(!customerList[deskId].isLeave)
		return;
	CCPoint loc = item->getPosition();
	loc.y += 20;

	//指定一个空闲的跑堂去清理
	for(unsigned int i = 0; i < waiters->count(); ++i)
	{
		Waiter *aWaiter = (Waiter*)waiters->objectAtIndex(i);
		//正在忙着清洁的跑堂不能再次清洁
		if(!aWaiter->isBusy()){
			aWaiter->setBusy(true);
			MoveWaiterToLoc(aWaiter, loc, false, deskId);
			break;
		}
		
	}
}

void MainGame::removeFood( CCNode* sender, void* deskId )
{
	foodMenu->removeChildByTag((int)deskId);
	deskList[(int)deskId].isTaken = false;
}

void MainGame::onEnter()
{
	CCLayer::onEnter();
	CCNotificationCenter::sharedNotificationCenter()->addObserver(
		this,                         
		callfuncO_selector(MainGame::managerMenuFunc),  // 处理的消息的回调函数
		"ManagerMenuSelected",                    // 感兴趣的消息名称
		NULL);    
	CCNotificationCenter::sharedNotificationCenter()->addObserver(
		this,                         
		callfuncO_selector(MainGame::closeTrainCookGame),  // 处理的消息的回调函数
		"CloseTrainCookGame",                    // 感兴趣的消息名称
		NULL);    
	CCNotificationCenter::sharedNotificationCenter()->addObserver(
		this,                         
		callfuncO_selector(MainGame::closeMathGame),  // 处理的消息的回调函数
		"CloseMathGame",                    // 感兴趣的消息名称
		NULL);   
}

void MainGame::onExit()
{
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(
		this,
		"ManagerMenuSelected");  // 消息名称
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(
		this,
		"CloseTrainCookGame");  // 消息名称

	CCNotificationCenter::sharedNotificationCenter()->removeObserver(
		this,
		"CloseMathGame");  // 消息名称

	CCLayer::onExit();
}

void MainGame::managerMenuFunc( CCObject *pSender )
{
	int num = ManagerMenu::selectMenuNum;
	Waiter *temp;
	Cook *c;
	CCSpriteFrame *strip = cache->spriteFrameByName("miku.png");
	CCTexture2D *texture = strip->getTexture();
	CCSize originalSize = strip->getOriginalSizeInPixels();
	CCRect stripRect = strip->getRect();
	float w = originalSize.width/4;
	float h = originalSize.height/4;
	float x = stripRect.origin.x;
	float y = stripRect.origin.y;

	CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(texture, CCRectMake(1, 1, w, h));

	switch(num)
	{
		//扩大规模
	case 0:
		managerMenuIsStart = false;
		if(desk_col == 6)
			break;
		if(desk_row == desk_col){	
			for(int i = 0; i < desk_col; ++i){
				deskList[i*6 + desk_col].deskSprite = CCSprite::create("desk.png");
				deskList[i*6 + desk_col].loc.setPoint(i*90 + 90, desk_row*90 + 90);
				deskList[i*6 + desk_col].deskSprite->setPosition(deskList[i*6 + desk_col].loc);
				this->addChild(deskList[i*6 + desk_col].deskSprite, 2);
			}
			desk_row++;
		}
		else{
			for(int i = 0; i < desk_row; ++i){
				deskList[(desk_row-1)*6 + i].deskSprite = CCSprite::create("desk.png");
				deskList[(desk_row-1)*6 + i].loc.setPoint(desk_col*90 + 90, i*90 + 90);
				deskList[(desk_row-1)*6 + i].deskSprite->setPosition(deskList[(desk_row-1)*6 + i].loc);
				this->addChild(deskList[(desk_row-1)*6 + i].deskSprite, 2);
			}
			desk_col++;
		}

		break;
		//雇用跑堂
	case 1:
		managerMenuIsStart = false;
		temp = new Waiter(5,5,1000);
		temp->pSprite = CCSprite::createWithSpriteFrame(frame);
		temp->pSprite->setPosition(ccp(size.width - 320, size.height - 50 * (waiters->count()+1)));
		this->addChild(temp->pSprite, 1);
		temp->loc = temp->pSprite->getPosition();
		temp->setId(waiters->count());
		waiters->addObject((CCObject *)temp);
		break;
		//雇用厨师
	case 2:
		managerMenuIsStart = false;
		c = new Cook(5, 5, 1000);
		frame = CCSpriteFrame::createWithTexture(texture, CCRectMake(128, 1, w, h));
		c->pSprite = CCSprite::createWithSpriteFrame(frame);
		c->pSprite->setPosition(ccp(size.width - 100 - cooks->count()*25, size.height - 120));
		this->addChild(c->pSprite, 1);
		cooks->addObject((CCObject*)c);
		break;
	case 3:
		callMathGame(NULL);
		break;
	case 4:
		trainCookGame = TrainCookGame::create();
		this->addChild(trainCookGame,4,500);
		break;
	case 5:
		managerMenuIsStart = false;
		break;
	}
	
	this->removeChild(managerMenuLayer);
}

void MainGame::MoveWaiterToLoc( Waiter* aWaiter, CCPoint loc, bool isLeave, int deskId )
{
	CCPoint waiterLoc = aWaiter->pSprite->getPosition();
	float yTime = fabs(loc.y - waiterLoc.y)/SPEED;
	float xTime = fabs(loc.x - waiterLoc.x)/SPEED;
	//获得对应图片
	CCSpriteFrame *strip = cache->spriteFrameByName("kaito.PNG");
	CCTexture2D *texture = strip->getTexture();
	CCSize originalSize = strip->getOriginalSizeInPixels();
	CCRect stripRect = strip->getRect();
	float w = originalSize.width/4;
	float h = originalSize.height/4;
	float x = stripRect.origin.x;
	float y = stripRect.origin.y;
	//生成y方向的动作
	CCArray *animFramesY = new CCArray(4);
	for (int j = 0; j < 4; j++)
	{
		CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(texture, CCRectMake(x, y, w, h));
		animFramesY->addObject(frame);
		x += w;
	}
	CCAnimation *animationY = CCAnimation::createWithSpriteFrames(animFramesY, 0.1f);
	CCActionInterval *stepActionY = CCAnimate::create(animationY);
	CCActionInterval *movetoActionY = CCMoveTo::create(yTime, ccp(waiterLoc.x, loc.y));
	int repeatTimeY = yTime/0.4;
	CCRepeat *repeatY = CCRepeat::create(stepActionY, repeatTimeY);
	//生成x方向的动作
	x = stripRect.origin.x;
	CCArray *animFramesX = new CCArray(4);
	for (int j = 0; j < 4; j++)
	{
		CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(texture, CCRectMake(x, y + h, w, h));
		animFramesX->addObject(frame);
		x += w;
	}
	CCAnimation *animationX = CCAnimation::createWithSpriteFrames(animFramesX, 0.1f);
	CCActionInterval *stepActionX = CCAnimate::create(animationX);
	CCActionInterval *movetoActionX = CCMoveTo::create(xTime, loc);
	int repeatTimeX = xTime/0.4;
	CCRepeat *repeatX = CCRepeat::create(stepActionX, repeatTimeX);
	//完成移动后转向
	x = stripRect.origin.x;
	CCArray *animFrames = new CCArray(3);
	for (int j = 0; j < 3; j++)
	{
		CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(texture, CCRectMake(x, y, w, h));
		animFrames->addObject(frame);
		x += w;
	}
	CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1f);
	CCActionInterval *face = CCAnimate::create(animation);
	//执行移动动作
	if(!isLeave){
		CCPlace *place = CCPlace::create(aWaiter->loc);
		CCSequence *sequenceMove = CCSequence::create(movetoActionY, movetoActionX, face,
			CCCallFuncND::create(this, callfuncND_selector(MainGame::removeFood), (void*)deskId),
			CCCallFuncND::create(this, callfuncND_selector(MainGame::setWaiterFree), (void*)aWaiter->getId()), place, NULL);
		aWaiter->pSprite->runAction(sequenceMove);
		CCSequence *sequenceStep = CCSequence::createWithTwoActions(repeatY, repeatX);
		aWaiter->pSprite->runAction(sequenceStep);
	}
	//离开的动作
	else{
		movetoActionX = CCMoveTo::create(xTime, ccp(loc.x, waiterLoc.y));
		movetoActionY = CCMoveTo::create(yTime, loc);
		CCSequence *sequenceMove = CCSequence::create(movetoActionX, movetoActionY, 
			CCCallFuncND::create(this, callfuncND_selector(MainGame::deleteSprite), (void*)deskId), NULL);
		aWaiter->pMenuItem->runAction(sequenceMove);
		CCSequence *sequenceStep = CCSequence::createWithTwoActions(repeatX, repeatY);
		aWaiter->pMenuItem->runAction(sequenceStep);
	}
}

void MainGame::setWaiterFree( CCNode* sender, void* waiterId )
{
	Waiter *w = (Waiter*)waiters->objectAtIndex((int)waiterId);
	w->setBusy(false);
}

void MainGame::closeTrainCookGame( CCObject *pSender )
{
	managerMenuIsStart = false;
	float score = 0;
	int gameTime = (int)pSender;
	if(gameTime != -1)                           //-1为退出游戏
		score = 200.0f / gameTime;               //游戏获得的分数

	//训练厨师技能
	for(int i = 0; i < cooks->count(); ++i){
		Cook *c = (Cook*)cooks->objectAtIndex(i);
		c->train((int)score / 5);
	}
	this->removeChildByTag(500);
}

void MainGame::closeMathGame( CCObject *pSender )
{
	managerMenuIsStart = false;
	int score = (int)pSender;
	//if(mathGameIsStart && mathGameLayer->getRound() <= 0){
	money += score * 100;
	removeChild(mathGameLayer);
	mathGameIsStart = false;
	char moneyLeft[20] = "Money: ";
	sprintf(moneyLeft, "%s%d", moneyLeft, money);
	moneyLabel->setString(moneyLeft);
	//}
}




