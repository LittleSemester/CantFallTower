// 编码：Utf-8 without BOM
// Created by LuiCat

#include "SimpleEnemy.h"

USING_NS_CC;


SimpleEnemy::SimpleEnemy(int type)
{
	this->type = type;
	switch (type)
	{
	case 1:
		//初始化怪物属性，这里预计改为从plist读取
		this->speed = 2;
		this->maxhp = 100;
		this->def = 0;
		break;
	default:
		break;
	}
}

bool SimpleEnemy::init()
{
	if (!Enemy::init())
		return false;

	//这里要统一好动画的形式，要么用plist要么用统一命名的图片序列
	walk = Animation::create();
	for (int i = 1; i <= 10; i++)
	{
		char szName[100];
		sprintf(szName, "gw%d.png", i);
		walk->addSpriteFrameWithFile(szName);
	}
	for (int i = 9; i >= 4; i--)
	{
		char szName[100];
		sprintf(szName, "gw%d.png", i);
		walk->addSpriteFrameWithFile(szName);
	}
	walk->setDelayPerUnit(0.05);

	aniWalk = Animate::create(walk);
	auto repeatWalk = RepeatForever::create(aniWalk);
	repeatWalk->setTag(52013);
	actSprite = Sprite::create();
	actSprite->runAction(repeatWalk);
	addChild(actSprite);

	return true;
}

void SimpleEnemy::update(float delta)
{
	Enemy::update(delta);


}

int SimpleEnemy::maxHP()
{
	return maxhp;
}

int SimpleEnemy::defence()
{
	return def;
}

SimpleEnemy* SimpleEnemy::create(int type)
{
	SimpleEnemy *pRet = new(std::nothrow) SimpleEnemy(type);
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

void SimpleEnemy::updateBuffState()
{
	Enemy::updateBuffState();

	double playSpeed = calcBuffedValue(&Buff::speed, 1.0);
	walk->setDelayPerUnit(playSpeed < 1e-7 ? INFINITY : 0.05 / playSpeed); 

	aniWalk = Animate::create(walk);

	//aniWalk->retain();

	auto repeatWalk = RepeatForever::create(aniWalk);
	actSprite->stopActionByTag(52013);
	repeatWalk->setTag(52013);
	actSprite->runAction(repeatWalk);

	//aniWalk->release();

}
