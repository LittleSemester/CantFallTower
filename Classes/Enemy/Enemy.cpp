#include <cmath>

#include "Enemy.h"

using namespace cocos2d;


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::update(float delta)
{
	updateBuff(delta);
}

int Enemy::defence()
{
	return 0;
}

int Enemy::dealDamage(double damage, bool direct/*=false*/)
{
	double bufDef = calcBuffedValue(&Buff::defence, defence());	
	damage = calcDefencedDamage(damage, bufDef);
	damage = calcBuffedValue(&Buff::damageIn, damage);

	int finalDamage = (int)round(damage);
	if (finalDamage < 1)
		finalDamage = 1;

	healthPoint -= finalDamage;
	if (healthPoint < 0)
		healthPoint = 0;

	return finalDamage;
}

double Enemy::calcDefencedDamage(double damage, double defence)
{
	return damage > defence ? damage - defence : 0.0;
}
