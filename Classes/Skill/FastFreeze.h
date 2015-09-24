// 编码：Utf-8 without BOM
// Created by LuiCat

#ifndef _SKILL_FASTFREEZE_H_
#define _SKILL_FASTFREEZE_H_

#include "Skill.h"

class FastFreeze : public Skill
{
private:

public:

	explicit FastFreeze();
	virtual ~FastFreeze();

	virtual bool init();

	virtual bool onTouchBegan(const cocos2d::Vec2& touchPos);
	virtual bool onTouchMoved(const cocos2d::Vec2& touchPos);
	virtual bool onTouchEnded(const cocos2d::Vec2& touchPos);

	virtual bool needSelectPos();

	virtual double getCoolDown();
	virtual int getMaxCount();

	CREATE_FUNC(FastFreeze);


};

#endif // _SKILL_FASTFREEZE_H_


