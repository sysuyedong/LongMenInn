
#ifndef ModalDialogDemo_DialogLayer_h
#define ModalDialogDemo_DialogLayer_h

#include "cocos2d.h"

USING_NS_CC;

class MathGameLayer: public CCLayerColor
{
	// 模态对话框菜单
	CCMenu *m_pMenu;
	// 记录菜单点击
	bool m_bTouchedMenu;

	CCSize size;
	//算术小游戏
	CCSprite *pOperand1;
	CCSprite *pOperand2;
	CCSprite *pOperator;
	CCSprite *pResult;
	int operand1;
	int operand2;
	int op;
	int result;
	int round;
	int score;
	//1:表示计算操作数1, 2:表示计算操作数2, 3:表示计算结果
	int flag;
	//1:表示隐藏操作数1, 2:表示隐藏操作数2, 3:表示隐藏结果
	int hideNum;
	CCSprite *pHide;
	CCSprite *rightSprite;
	CCSprite *wrongSprite;

public:
	MathGameLayer();
	~MathGameLayer();

	virtual bool init();
	// 初始化对话框内容
	//	LAYER_NODE_FUNC(DialogLayer);  
	CREATE_FUNC(MathGameLayer);

	void callMathGame();
	void click(CCObject* pSender);
	void quit(CCObject* pSender);
	void changeOperand1();
	void changeOperand2();
	void changeResult();
	void changeOperator();
	void nextRound();
	void hideOperand1();
	void hideOperand2();
	void hideResult();
	int getScore();
	int getRound();
	void showRight();
	void showWrong();
};

#endif
