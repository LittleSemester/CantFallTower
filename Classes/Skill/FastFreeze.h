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

	virtual double getCoolDown();
	virtual int getMaxCount();

};

#endif // _SKILL_FASTFREEZE_H_


