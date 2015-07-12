
#ifndef ModalDialogDemo_DialogLayer_h
#define ModalDialogDemo_DialogLayer_h

#include "cocos2d.h"

USING_NS_CC;

class MathGameLayer: public CCLayerColor
{
	// ģ̬�Ի���˵�
	CCMenu *m_pMenu;
	// ��¼�˵����
	bool m_bTouchedMenu;

	CCSize size;
	//����С��Ϸ
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
	//1:��ʾ���������1, 2:��ʾ���������2, 3:��ʾ������
	int flag;
	//1:��ʾ���ز�����1, 2:��ʾ���ز�����2, 3:��ʾ���ؽ��
	int hideNum;
	CCSprite *pHide;
	CCSprite *rightSprite;
	CCSprite *wrongSprite;

public:
	MathGameLayer();
	~MathGameLayer();

	virtual bool init();
	// ��ʼ���Ի�������
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
