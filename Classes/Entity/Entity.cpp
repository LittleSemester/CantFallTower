// 编码：Utf-8 without BOM
// Created by LuiCat

#include "Entity.h"

Entity::Entity()
{
	mainScene = 0;
	baseDamage = 0.0;
}

Entity::~Entity()
{

}

void Entity::acquireJudge(Enemy* enemy)
{
	if (mainScene != nullptr)
		mainScene->judgeEntityBounding(this, enemy);
}

void Entity::onEnter()
{
	Node::onEnter();
	Node* node = this->getParent();
	mainScene = dynamic_cast<GameScene*>(node);
	if (mainScene == nullptr)
		removeFromParent();
}

void Entity::setBaseDamage(int damage)
{
	baseDamage = damage;
}

bool Entity::init()
{
	if (!Node::init())
		return false;
	this->setLocalZOrder(7);
	return true;
}

