// 编码：Utf-8 without BOM
// Created by LuiCat

#ifndef _SKILL_ROW_H_
#define _SKILL_ROW_H_

#include "Skill.h"

class RowSkill : public Skill
{
protected:

	cocos2d::Vec2 touchBeganPos;
	int direction;
	bool vertical;
	float alignedAngle;

	virtual void triggleSkill()=0;

public:

	virtual bool onTouchBegan(const cocos2d::Vec2& touchPos);
	virtual bool onTouchMoved(const cocos2d::Vec2& touchPos);
	virtual bool onTouchEnded(const cocos2d::Vec2& touchPos);

	virtual bool needSelectPos();

};


#endif // _SKILL_ROW_H_
