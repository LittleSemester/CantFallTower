// 编码：Utf-8 without BOM
// Created by LuiCat

#ifndef _SIMPLE_ENTITY_H_
#define _SIMPLE_ENTITY_H_

#include "Enemy.h"

class SimpleEnemy : public Enemy
{
protected:

	int type;//怪物类型
	int maxhp;
	int def;

	int frameFly;

	cocos2d::Animation* walk;
	cocos2d::Animate* aniWalk;

	virtual void onBuffBegin(Buff* buff);

	virtual void updateBuffState();

public:

	explicit SimpleEnemy(int type);

	virtual bool init();
	virtual void update(float delta);

	virtual int maxHP();
	virtual int defence();

	static SimpleEnemy* create(int type);

};


#endif
