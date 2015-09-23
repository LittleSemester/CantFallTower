// 编码：Utf-8 without BOM
// Created by LuiCat

#ifndef _BULLET_H_
#define _BULLET_H_

#include "Entity.h"
#include "Enemy/Enemy.h"

enum MissileType
{
	MISSILE_UNKNOWN = -1,
	MISSILE_STAR = 0
};

class Missile : public Entity
{
protected:

	double remainTime;
	double judgeDistance;
	double speedGradient;

	Enemy* target;

	bool targetReached;

public:

	explicit Missile();
	virtual ~Missile();

	inline bool isFinished() const
	{
		return target == nullptr || targetReached;
	}

	virtual bool init();
	virtual void update(float delta); // 飞弹用update进行判定和移动处理

	virtual bool judgeSingleEnemy(Enemy* enemy);

	void setTarget(Enemy* enemy);

	static Missile* createMissile(MissileType type);

};


#endif //_BULLET_H_
