#include "ManagerMenu.h"
#include "MainGameScene.h"
//#include "tools.h"

#define NUMOFMENUITEM 6
string menuItemStr[NUMOFMENUITEM] = {"À©´ó¹æÄ£","¹ÍÓ¶ÅÜÌÃ","¹ÍÓ¶³øÊ¦","ÑµÁ·ÕÆ¹ñ","ÑµÁ·³øÊ¦","ÍË³ö"};
bool flagTurnUTF_8 = true;
int ManagerMenu::selectMenuNum = 0;

ManagerMenu::ManagerMenu()
{

}

ManagerMenu::~ManagerMenu()
{

}

bool ManagerMenu::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(0, 0, 0, 125)));
		size = CCDirector::sharedDirector()->getWinSize();
		CCSprite *background = CCSprite::create("numBackground.jpg");
		background->setPosition(ccp(size.width / 2,size.height / 2));
		this->addChild(background);

// 		if(flagTurnUTF_8)
// 		for(int i = 0 ;i < NUMOFMENUITEM;i++)
// 			GBKToUTF8(menuItemStr[i],"gbk","utf-8");
// 		flagTurnUTF_8 = false;

// 		string str = "ÇëÑ¡Ôñ£º";
// 		GBKToUTF8(str,"gbk","utf-8");
// 		CCLabelTTF *label = CCLabelTTF::create(str.c_str(),"",30);
// 
// 		label->setPosition(ccp(20,background->getContentSize().height - label->getContentSize().height * 2));
// 		label->setColor(ccc3(0,0,0));
// 		label->setAnchorPoint(CCPointZero);
		CCSprite *label = CCSprite::create("please.png");
		label->setPosition(ccp(20,background->getContentSize().height - label->getContentSize().height * 2));
		label->setAnchorPoint(CCPointZero);
		background->addChild(label);

		m_pMenu = CCMenu::create();
		
		char tempStr[30];
		for (int i = 0 ;i < NUMOFMENUITEM;i++)
		{		
			sprintf(tempStr,"managerMenu%d.png",i + 1);
			CCMenuItemImage *menu = CCMenuItemImage::create(tempStr,NULL,this,menu_selector(ManagerMenu::menuFunc));
			//CCMenuItemFont *menu = CCMenuItemFont::create(tempStr,this,menu_selector(ManagerMenu::menuFunc));
			//menu->setFontSize(30);
			//menu->setColor(ccc3(0,0,0));
			menu->setAnchorPoint(CCPointZero);
			m_pMenu->addChild(menu,0,i);
		}

		m_pMenu->alignItemsVerticallyWithPadding(label->getContentSize().height / 2);
		m_pMenu->setPosition(ccpSub(label->getPosition(),ccp(0,(NUMOFMENUITEM / 2 + 2.5) * label->getContentSize().height)));
		m_pMenu->setAnchorPoint(CCPointZero);
		background->addChild(m_pMenu);
		
		bRet = true;
	} while (0);

	return bRet;
}

void ManagerMenu::menuFunc( CCObject *pSender )
{
	CCMenuItem *item = (CCMenuItem *)pSender;
	selectMenuNum = item->getTag();
	CCNotificationCenter::sharedNotificationCenter()->postNotification("ManagerMenuSelected", (CCObject*)pSender);
	
	//this->removeFromParent();
}

int ManagerMenu::getSelelctNum()
{
	return selectMenuNum;
}

