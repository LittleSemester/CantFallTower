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

	return true;
}

void MissileStar::onUpdate(float delta)
{
	sprite->setRotation(sprite->getRotation() + delta * M_PI * 2);
}
