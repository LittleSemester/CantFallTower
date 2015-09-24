// 编码：Utf-8 without BOM
// Created by LuiCat

#ifndef _SKILL_H_
#define _SKILL_H_

#include <cocos2d.h>

class Skill : public cocos2d::Node
{
public:

	explicit Skill();
	virtual ~Skill()=0;

	virtual double getCoolDown();
	virtual int getMaxCount();

	virtual void setLevel(int level);

};


#endif // _SKILL_H_

