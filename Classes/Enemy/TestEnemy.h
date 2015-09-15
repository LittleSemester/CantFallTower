// 编码：Utf-8 without BOM
// Created by LuiCat

#ifndef _TESTENEMY_H_
#define _TESTENEMY_H_

#include "Enemy.h"
#include "ui\UITextAtlas.h"

class TestEnemy : public Enemy
{
protected:

	cocos2d::ui::TextAtlas* text;

public:

	explicit TestEnemy();
	virtual ~TestEnemy();

	virtual int maxHP();
	virtual int defence();

	virtual int dealDamage(double damage, bool direct = false);

	virtual bool init();

	CREATE_FUNC(TestEnemy);

};

#endif // _TESTENEMY_H_
