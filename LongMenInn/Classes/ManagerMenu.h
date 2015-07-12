
#ifndef _MANAGERMENU_H
#define _MANAGERMENU_H

#include "cocos2d.h"
#include <string>
#include <vector>

using namespace std;
USING_NS_CC;

class ManagerMenu: public CCLayerColor
{
private:
	// 模态对话框菜单
	CCMenu *m_pMenu;
	CCSize size;
	

public:
	ManagerMenu();
	~ManagerMenu();

	virtual bool init();
	CREATE_FUNC(ManagerMenu);

	void menuFunc(CCObject *pSender);
	static int getSelelctNum();
	static int selectMenuNum;
};

#endif
