// 编码：Utf-8 without BOM
// Created by LuiCat

#ifndef _SKILL_HURRICANE_H_
#define _SKILL_HURRICANE_H_

#include "Skill.h"

class Hurricane : public Skill
{
protected:

	cocos2d::Vec2 touchBeganPos;
	bool vertical;

	void triggleSkill();
	void createHurricane(const cocos2d::Vec2& beginPos, float angle);

public:

	virtual bool onTouchBegan(const cocos2d::Vec2& touchPos);
	virtual bool onTouchMoved(const cocos2d::Vec2& touchPos);
	virtual bool onTouchEnded(const cocos2d::Vec2& touchPos);

	virtual bool needSelectPos();

	virtual double getCoolDown();

	CREATE_FUNC(Hurricane);

};


#endif // _SKILL_HURRICANE_H_