// 编码：Utf-8 without BOM
// Created by LuiCat

#include "MissileStar.h"
#include <cocos2d.h>

USING_NS_CC;

bool MissileStar::init()
{
	if (!Missile::init())
		return false;
	
	sprite = Sprite::create("bullet.png");
	sprite->setScale(0.5f);
	this->addChild(sprite);

	this->remainTime = 0.3;
	this->baseDamage = 10.0;

	return true;
}

void MissileStar::update(float delta)
{
	Missile::update(delta);

	if (isFinished())
		return;

	sprite->setRotation(sprite->getRotation() + delta * 360);

}
