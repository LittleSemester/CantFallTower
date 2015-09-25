// 编码：Utf-8 without BOM
// Created by LuiCat

#include "RowSkill.h"

USING_NS_CC;

bool RowSkill::onTouchBegan(const cocos2d::Vec2& touchPos)
{
	touchBeganPos = touchPos;
	return true;
}

bool RowSkill::onTouchMoved(const cocos2d::Vec2& touchPos)
{
	return true;
}

bool RowSkill::onTouchEnded(const cocos2d::Vec2& touchPos)
{
	Vec2 vec = touchPos - touchBeganPos;
	direction = (int)(vec.getAngle() * 2 / M_PI + 2.5);
	alignedAngle = (direction - 2) * M_PI_2;
	vertical = (direction & 1);
	mainScene->alignPosition(touchBeganPos);
	triggleSkill();
	return true;
}

bool RowSkill::needSelectPos()
{
	return true;
}
