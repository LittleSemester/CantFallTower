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
	this->addChild(sprite);

	this->baseDamage = 20.0;

	return true;
}

void MissileStar::update(float delta)
{
	Missile::update(delta);

	sprite->setRotation(sprite->getRotation() + delta * M_PI * 2);
}
