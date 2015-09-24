// 编码：Utf-8 without BOM
// Created by LuiCat

#include "Missile.h"
#include "2d/CCSprite.h"

USING_NS_CC;

Missile::Missile()
{
	judgeDistance = 0.0;
	remainTime = 1.0;
	speedGradient = 1.0;
	target = nullptr;
}

Missile::~Missile()
{
	if (target != nullptr)
		target->release();
}

bool Missile::init()
{
	if (!Entity::init())
		return false;

	targetReached = false;

	Sprite::create();

	this->scheduleUpdate();
	return true;
}

void Missile::update(float delta)
{
	if (isFinished())
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
	vecDist *= (targetReached ? 1.0 : speedGradient) * delta / remainTime;
	vecThis += vecDist;
	this->setPosition(vecThis);

	remainTime -= delta;

	// 如果先前标记了targetReached，则对target进行一次判定
	if (targetReached)
	{
		acquireJudge();
		removeFromParent();
	}

}


bool Missile::judgeSingleEnemy(Enemy* enemy)
{
	if (enemy == nullptr || enemy != target)
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
	if (enemy == nullptr)
		return;
	if (target != nullptr)
		target->release();
	target = enemy;
	target->retain();
	targetReached = false;
	remainTime = 1.0;
}

#include "MissileStar.h"

Missile* Missile::createMissile(MissileType type)
{
	switch (type)
	{
	case MISSILE_STAR:
		return MissileStar::create();
	default:
		return nullptr;
	}
	return nullptr;
}

