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
	auto Walk = Animation::create();
	for (int i = 1; i <= 10; i++)
	{
		char szName[100];
		sprintf(szName, "gw%d.png", i);
		Walk->addSpriteFrameWithFile(szName);
	}
	for (int i = 9; i >= 4; i--)
	{
		char szName[100];
		sprintf(szName, "gw%d.png", i);
		Walk->addSpriteFrameWithFile(szName);
	}
	Walk->setDelayPerUnit(0.1);

	auto AniWalk = Animate::create(Walk);
	auto RepeatWalk = RepeatForever::create(AniWalk);
	actSprite = Sprite::create();
	actSprite->runAction(RepeatWalk);
	addChild(actSprite);

	return true;
}

void SimpleEnemy::update(float delta)
{
	Enemy::update(delta);

	unsigned int flag = getBuffFlag();
	if (flag&BUFF_FROZEN)
	{
		actSprite->setColor(Color3B(200, 200, 255));
	}
	if (flag&BUFF_DEEPFROZEN)
	{
		actSprite->setColor(Color3B(127, 127, 255));
	}

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
