// 编码：Utf-8 without BOM
// Created by LuiCat

#include "Missile.h"
#include "2d/CCSprite.h"

USING_NS_CC;

Missile::Missile()
{
	judgeDistance = 0.0;
	remainTime = 1.0;
	initSpeed = 200.0;
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

	Vec2 vecThis = this->getPosition();
	Vec2 vecTarget = target->getPosition();
	Vec2 vecDist = vecTarget - vecThis;
	double expectSpeed = vecDist.length() / remainTime;
	if (expectSpeed < initSpeed)
		expectSpeed = initSpeed;

	// 剩余飞行时间结束或者到达目标
	if (delta > remainTime || expectSpeed * delta >= vecDist.length())
	{
		targetReached = true;
		// 对target进行一次判定
		remainTime -= delta;
		if (remainTime < 0)
			remainTime = 0;
		setPosition(target->getPosition());
		acquireJudge();
		removeFromParent();
	}
	else
	{
		vecDist.normalize();
		vecDist *= expectSpeed*delta;
		vecThis += vecDist;
		this->setPosition(vecThis);
		remainTime -= delta;
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
	if (enemy == nullptr || enemy == target)
		return;
	if (target != nullptr)
		target->release();
	target = enemy;
	target->retain();
	targetReached = false;
	remainTime = 1.0;
}

#include "MissileStar.h"
#include "FireDir.h"
Missile* Missile::createMissile(MissileType type)
{
	switch (type)
	{
	case MISSILE_STAR:
		return MissileStar::create();
	case MISSILE_FIRE:
		return FireDir::create();
	default:
		return nullptr;
	}
	return nullptr;
}

