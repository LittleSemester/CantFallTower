// 编码：Utf-8 without BOM
// Created by LuiCat

#include "FastFreeze.h"

USING_NS_CC;

FastFreeze::FastFreeze()
{

}

FastFreeze::~FastFreeze()
{

}

bool FastFreeze::init()
{
	if(!Skill::init())
		return false;

	return true;
}

double FastFreeze::getCoolDown()
{
	return 20.0;
}

int FastFreeze::getMaxCount()
{
	return 10;
}

bool FastFreeze::onTouchBegan(const cocos2d::Vec2& touchPos)
{
	return true;
}

bool FastFreeze::onTouchMoved(const cocos2d::Vec2& touchPos)
{
	return true;
}

bool FastFreeze::onTouchEnded(const cocos2d::Vec2& touchPos)
{
	Enemy* enemy = mainScene->getNearestEnemy(touchPos, 30);
	if (enemy == nullptr)
		return false;

	auto buff = new SimpleBuff(3, 1.0, 1.0, 2.0, 0.0);
	buff->setFlag(BUFF_DEEPFROZEN);
	enemy->pushBuff(buff);

	return true;
}

bool FastFreeze::needSelectPos()
{
	return true;
}
