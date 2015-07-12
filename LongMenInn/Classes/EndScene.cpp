#include "EndScene.h"
#include "BeginScene.h"

using namespace cocos2d;

CCScene* EndScene::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		EndScene *layer = EndScene::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

bool EndScene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());
		CCSize size = CCDirector::sharedDirector()->getWinSize();

		//ÏÔÊ¾·ÖÊý
		CCLabelTTF *pLabel = CCLabelTTF::create("Game Over", "Arial", 30);
		CC_BREAK_IF(! pLabel);
		pLabel->setPosition(ccp(120, 500));
		pLabel->setColor(ccc3(0,0,0));
		this->addChild(pLabel, 1);

		CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
			"CloseNormal.png",
			"CloseSelected.png",
			this,
			menu_selector(EndScene::menuCloseCallback));
		CC_BREAK_IF(! pCloseItem);
		pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

		CCMenuItemImage *pReturnItem = CCMenuItemImage::create(
			"return1.png",
			"return2.png",
			this,
			menu_selector(EndScene::menuReturnCallback));
		pReturnItem->setPosition(ccp(150, 250));

		CCMenu* pMenu = CCMenu::create(pCloseItem, pReturnItem, NULL);
		pMenu->setPosition(CCPointZero);
		CC_BREAK_IF(! pMenu);

		// Add the menu to HelloWorld layer as a child layer.
		this->addChild(pMenu, 1);

		CCSprite* pSprite = CCSprite::create("end.png");
		CC_BREAK_IF(! pSprite);

		// Place the sprite on the center of the screen
		pSprite->setPosition(ccp(size.width/2, size.height/2));

		// Add the sprite to HelloWorld layer as a child layer.
		this->addChild(pSprite, 0);	

		bRet = true;
	}while (0);
	return bRet;
}

void EndScene::menuCloseCallback(CCObject* pSender)
{
	// "close" menu item clicked
	CCDirector::sharedDirector()->end();
}

void EndScene::menuReturnCallback( CCObject* pSender )
{
	CCScene *beginScene = BeginScene::scene();
	CCDirector::sharedDirector()->replaceScene(beginScene);
}
