//
//  MathGameLayer.cpp
//  ModalDialogDemo
//
//  Created by Tom on 12-5-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "MathGameLayer.h"

MathGameLayer::MathGameLayer()
{
}

MathGameLayer::~MathGameLayer()
{
}

bool MathGameLayer::init()
{
	bool bRet = false;
	round = 10;
	score = 0;
	do {
		rightSprite = CCSprite::create("right.png");
		wrongSprite = CCSprite::create("false.png");

		rightSprite->setPosition(ccp(500, 500));
		wrongSprite->setPosition(ccp(500, 500));

		this->addChild(rightSprite, 4);
		this->addChild(wrongSprite, 4);

		CCHide *hide1 = CCHide::create();
		CCHide *hide2 = CCHide::create();
		rightSprite->runAction(hide1);
		wrongSprite->runAction(hide2);

		CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(0, 0, 0, 125)));
		size = CCDirector::sharedDirector()->getWinSize();
		callMathGame();
		bRet = true;
	} while (0);

	return bRet;
}

//显示计算小游戏
void MathGameLayer::callMathGame()
{
	CCSprite *numBackground = CCSprite::create("numBackground.jpg");
	numBackground->setPosition(ccp(size.width/2, size.height/2));
	addChild(numBackground, 3);

	CCSprite *pEqual = CCSprite::create("equal.png");
	pEqual->setPosition(ccp(size.width/2 + 120, size.height/2 + 70));
	this->addChild(pEqual, 3);

	//随机生成一个算式
	srand((unsigned)time(NULL));
	op = rand() % 2;
	if(op == 0){    //加法
		operand1 = rand() % 10;
		operand2 = rand() % (10 - operand1);
		result = operand1 + operand2;
	}
	else{    //减法
		operand1 = (rand() % 9) + 1;
		operand2 = rand() % operand1 + 1;
		result = operand1 - operand2;
	}
	flag = 3;    //计算结果
	changeOperand1();
	changeOperand2();
	changeOperator();

	char str[20];
	CCMenu *numsMenu = CCMenu::create();
	for (int i = 0 ;i < 10;i++)
	{
		sprintf(str,"%d.png",i);
		CCMenuItemImage *numItem = CCMenuItemImage::create(str,str,this,
			menu_selector(MathGameLayer::click));
		if(i < 5)
			numItem->setPosition(ccp(size.width / 2 - 80 + i * 40,size.height / 3));
		else
			numItem->setPosition(ccp(size.width / 2 - 80 + (i - 5) * 40,size.height / 2));
		numsMenu->addChild(numItem,0,i);
	}
	numsMenu->setPosition(CCPointZero);
	this->addChild(numsMenu,3);

	CCMenuItemFont *quit = CCMenuItemFont::create("QUIT", this, menu_selector(MathGameLayer::quit));
	quit->setPosition(ccp(750, 150));
	quit->setColor(ccc3(0,0,0));
	numsMenu->addChild(quit);
}


void MathGameLayer::changeOperand1()
{
	char str[20];
	sprintf(str,"%d.png",operand1);
	pOperand1 = CCSprite::create(str);
	pOperand1->setPosition(ccp(size.width/2 - 80, size.height/2 + 70));
	this->addChild(pOperand1, 3);
}

void MathGameLayer::changeOperand2()
{
	char str[20];
	sprintf(str,"%d.png",operand2);
	pOperand2 = CCSprite::create(str);

	pOperand2->setPosition(ccp(size.width/2 + 80, size.height/2 + 70));
	this->addChild(pOperand2, 3);
}

void MathGameLayer::changeResult()
{
	char str[20];
	sprintf(str,"%d.png",result);
	pResult = CCSprite::create(str);
	pResult->setPosition(ccp(size.width/2 + 160, size.height/2 + 70));
	this->addChild(pResult, 3);
}

void MathGameLayer::changeOperator()
{
	switch(op){
	case 0:
		pOperator = CCSprite::create("plus.png");
		break;
	case 1:
		pOperator = CCSprite::create("minus.png");
		break;
	}
	pOperator->setPosition(ccp(size.width/2, size.height/2 + 70));
	this->addChild(pOperator, 3);
}

void MathGameLayer::nextRound()
{
	srand((unsigned)time(NULL));
	hideNum = rand() % 3 + 1;
	op = rand() % 2;
	pHide = CCSprite::create("hide.png");
	pHide->setPosition(ccp(size.width/2 + 200, size.height/2));
	//this->addChild(pHide, 4);
	switch(hideNum){
	case 1:    //隐藏操作数1
		flag = 2;
		if(op == 0){
			operand2 = rand() % (10 - operand1);
			result = operand1 + operand2;
		}
		else{
			if(operand1 == 0)
				operand2 = 0;
			else
				operand2 = rand() % operand1 + 1;
			result = operand1 - operand2;
		}
		hideOperand1();
		hideOperand2();
		hideResult();
		changeOperand1();
		changeResult();
		changeOperator();
		break;
	case 2:    //隐藏操作数2
		flag = 3;
		if(op == 0){
			operand1 = rand() % (10 - operand2);
			result = operand1 + operand2;
		}
		else{
			result = rand() % (10 - operand2);
			operand1 = result + operand2;
		}
		hideOperand1();
		hideOperand2();
		hideResult();
		changeOperand1();
		changeOperand2();
		changeOperator();
		break;
	case 3:    //隐藏结果
		flag = 1;
		if(op == 0){
			if(result == 0)
				operand1 = 0;
			else
				operand1 = rand() % result + 1;
			operand2 = result - operand1;
		}
		else{
			operand2 = rand() % (10 - result);
			operand1 = result + operand2;
		}
		hideOperand1();
		hideOperand2();
		hideResult();
		changeOperand2();
		changeResult();
		changeOperator();
		break;
	}
}

void MathGameLayer::hideOperand1()
{
	this->removeChild(pOperand1);
}

void MathGameLayer::hideOperand2()
{
	this->removeChild(pOperand2);
}

void MathGameLayer::hideResult()
{
	this->removeChild(pResult);
}

int MathGameLayer::getScore()
{
	return score;
}

int MathGameLayer::getRound()
{
	return round;
}

void MathGameLayer::click( CCObject* pSender )
{
	CCMenuItem *item = (CCMenuItem *)pSender;
	int num = item->getTag();
	switch(flag){
	case 1:    //miss operand1
		if(op == 0){
			if(result - operand2 == num){
				score++;
				showRight();
				changeOperand1();
			}
			else
				showWrong();
		}
		else{
			if(operand2 + result == num){
				score++;
				showRight();
				changeOperand1();
			}
			else
				showWrong();
		}
		break;
	case 2:    //miss operand2
		if(op == 0){
			if(result - operand1 == num){
				score++;
				showRight();
				changeOperand2();
			}
			else
				showWrong();
		}
		else{
			if(operand1 - result == num){
				score++;
				showRight();
				changeOperand2();
			}
			else
				showWrong();
		}
		break;
	case 3:    //miss result
		if(op == 0){    //加法
			if(operand1 + operand2 == num){
				score++;
				showRight();
				changeResult();
			}
			else
				showWrong();
		}
		else{
			if(operand1 - operand2 == num){
				score++;
				showRight();
				changeResult();
			}
			else
				showWrong();
		}
		break;
	}
	//进行下一轮算术
	round--;
	if(round <= 0)
	{
		CCNotificationCenter::sharedNotificationCenter()->postNotification("CloseMathGame", (CCObject*)score);
		return;
	}

	nextRound();


}

void MathGameLayer::quit( CCObject* pSender )
{
	CCNotificationCenter::sharedNotificationCenter()->postNotification("CloseMathGame", (CCObject*)score);
}

void MathGameLayer::showRight()
{
	CCShow *show = CCShow::create();
	CCBlink *blink = CCBlink::create(1, 2);
	CCHide *hide = CCHide::create();
	CCSequence *sequence = CCSequence::create(show, blink, hide, NULL);
	rightSprite->runAction(sequence);
}

void MathGameLayer::showWrong()
{
	CCShow *show = CCShow::create();
	CCBlink *blink = CCBlink::create(1, 2);
	CCHide *hide = CCHide::create();
	CCSequence *sequence = CCSequence::create(show, blink, hide, NULL);
	wrongSprite->runAction(sequence);
}
