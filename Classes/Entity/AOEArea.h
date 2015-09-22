// 编码：Utf-8 without BOM
// Created by LuiCat

#ifndef _AOE_AREA_H_
#define _AOE_AREA_H_

#include "Entity.h"

class AOEArea : public Entity
{
protected:

	virtual bool isPositionInArea(const cocos2d::Vec2 relativePos)=0;

public:

	virtual bool judgeSingleEnemy(Enemy* enemy);

};


#endif // _AOE_AREA_H_
