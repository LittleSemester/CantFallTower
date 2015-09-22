// 编码：Utf-8 without BOM
// Created by LuiCat

#ifndef _BULLET_H_
#define _BULLET_H_

#include "Entity.h"
#include "Enemy/Enemy.h"

class Missile : public Entity
{
protected:

	double remainTime;
	double judgeDistance;

	Enemy* target;

	bool targetReached;

public:

	explicit Missile();
	virtual ~Missile();

	virtual bool init();
	virtual void update(float delta); // 飞弹用update进行判定和移动处理

	virtual bool judgeSingleEnemy(Enemy* enemy);

	void setTarget(Enemy* enemy);

};


#endif //_BULLET_H_
