// 编码：Utf-8 without BOM
// Created by LuiCat

#ifndef _SKILL_HURRICANE_H_
#define _SKILL_HURRICANE_H_

#include "RowSkill.h"

class Hurricane : public RowSkill
{
protected:

	virtual void triggleSkill();

	void createHurricane(const cocos2d::Vec2& beginPos, float angle);

public:

	virtual double getCoolDown();

	CREATE_FUNC(Hurricane);

};


#endif // _SKILL_HURRICANE_H_