// 编码：Utf-8 without BOM
// Created by LuiCat

#ifndef _SIMPLE_ENTITY_H_
#define _SIMPLE_ENTITY_H_

#include "Enemy.h"
#include <string>

#define BUFF_TAG_RUSH 13312
#define BUFF_TAG_DEF 13313
#define BUFF_TAG_CURED 13314

class SimpleEnemy : public Enemy
{
protected:

	std::string type; //怪物类型
	int maxhp;
	int def;
	int money;

	int frameFly;

	cocos2d::Animation* walk;
	cocos2d::Animate* aniWalk;

	virtual void onBuffBegin(Buff* buff);
	virtual void onBuffEnd(Buff* buff);

	virtual void updateBuffState();

	void doBuffDizzy();

	void doBuffRush(bool on = true);
	void doBuffDef(bool on = true);
	void doBuffCured(bool on = true);

public:

	explicit SimpleEnemy(const std::string& type);

	virtual bool init();
	virtual void update(float delta);

	virtual int maxHP();
	virtual int defence();
	virtual int reward();

	static SimpleEnemy* create(const std::string& type);

};


#endif
