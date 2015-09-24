// 编码：Utf-8 without BOM
// Created by LuiCat

#include "Skill.h"

Skill::Skill()
{

}

Skill::~Skill()
{

}

double Skill::getCoolDown()
{
	return 0.0;
}

int Skill::getMaxCount()
{
	return -1;
}

void Skill::setLevel(int level)
{

}

void Skill::onEnter()
{
	Node::onEnter();
	Node* node = this->getParent();
	mainScene = dynamic_cast<GameScene*>(node);
	if (mainScene == nullptr)
		removeFromParent();
}

bool Skill::needSelectPos()
{
	return false;
}

bool Skill::onTouchBegan(const cocos2d::Vec2& touchPos)
{
	return false;
}

bool Skill::onTouchMoved(const cocos2d::Vec2& touchPos)
{
	return false;
}

bool Skill::onTouchEnded(const cocos2d::Vec2& touchPos)
{
	return false;
}

