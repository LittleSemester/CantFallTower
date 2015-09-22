// 编码：Utf-8 without BOM
// Created by LuiCat

#ifndef _MISSILE_STAR_H_
#define _MISSILE_STAR_H_

#include "Missile.h"
#include <cocos2d.h>

class MissileStar : public Missile
{
private:

	cocos2d::Sprite* sprite;

public:

	virtual bool init();
	virtual void onUpdate(float delta);

};

#endif // _MISSILE_STAR_H_
