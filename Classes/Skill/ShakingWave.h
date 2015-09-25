// 编码：Utf-8 without BOM
// Created by LuiCat

#ifndef _SKILL_SHAKINGWAVE_H_
#define _SKILL_SHAKINGWAVE_H_

#include "RowSkill.h"

class ShakingWave : public RowSkill
{
private:

	cocos2d::Vector<Enemy*> hitEnemy;

protected:

	virtual void triggleSkill();

	void createWave(const cocos2d::Vec2& beginPos, float angle);

public:

	virtual double getCoolDown();

	CREATE_FUNC(ShakingWave);

};

#endif // _SKILL_SHAKINGWAVE_H_
