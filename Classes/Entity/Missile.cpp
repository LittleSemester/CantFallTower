// 编码：Utf-8 without BOM
// Created by LuiCat

#include "Missile.h"

USING_NS_CC;

Missile::Missile()
{
	judgeDistance = 0.0;
	remainTime = 1.0;
}

Missile::~Missile()
{

}

bool Missile::init()
{
	targetReached = false;
	this->scheduleUpdate();
	return true;
}

void Missile::update(float delta)
{
	if (target == nullptr || targetReached)
		return;

	// 剩余飞行时间结束！
	if (delta > remainTime)
	{
		targetReached = true;
		delta = remainTime;
	}

	Vec2 vecThis = this->getPosition();
	Vec2 vecTarget = target->getPosition();
	Vec2 vecDist = vecTarget - vecThis;

	// 按时间比例移动到合适地点
	vecDist *= delta / remainTime;
	vecThis += vecDist;
	this->setPosition(vecThis);

	remainTime -= delta;

	// 如果先前标记了targetReached，则对target进行一次判定
	if (targetReached)
	{
		acquireJudge();
	}

}


bool Missile::judgeSingleEnemy(Enemy* enemy)
{
	if (enemy != target)
		return false;

	if (targetReached)
	{
		enemy->dealDamage(baseDamage);
		return true;
	}

	return false;
}

void Missile::setTarget(Enemy* enemy)
{
	if (enemy != nullptr)
		target = enemy;
}

