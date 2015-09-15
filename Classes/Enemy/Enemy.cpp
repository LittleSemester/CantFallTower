#include "Enemy.h"

using namespace cocos2d;


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::onEnter()
{
	Node::onEnter();
}

void Enemy::onExit()
{
	Node::onExit();
}

void Enemy::update(float delta)
{
	
}

int Enemy::maxHP()
{
	return 100;
}

int Enemy::defence()
{
	return 0;
}

void Enemy::dealDamage(double damage, bool direct/*=false*/)
{

}
