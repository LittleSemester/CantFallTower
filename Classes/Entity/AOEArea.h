// 编码：Utf-8 without BOM
// Created by LuiCat

#ifndef _AOE_AREA_H_
#define _AOE_AREA_H_

#include "Entity.h"

class AOEArea : public Entity
{
protected:

	// 自定义AOE范围，参数relativePos为相对中心的位置
	virtual bool isPositionInArea(const cocos2d::Vec2& relativePos)=0;

	// 继承以自定义造成伤害时的操作
	virtual void onDealDamage(Enemy* enemy);

public:

	// 建议不要继承这个函数
	virtual bool judgeSingleEnemy(Enemy* enemy) override;

};


#endif // _AOE_AREA_H_
