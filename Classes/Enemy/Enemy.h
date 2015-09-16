#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <cocos2d.h>
#include <math\CCGeometry.h>

#include "buff/BuffList.h"

class Enemy : public cocos2d::Node, public BuffList
{
protected:

	int healthPoint;

	static double calcDefencedDamage(double damage, double defence);

public:

	explicit Enemy();
	virtual ~Enemy();
	
	virtual bool init();
	virtual void update(float delta);

	virtual int maxHP()=0;
	virtual int defence();

	// 对该敌人造成伤害，期间检查敌人各项属性和buff，指定direct=true造成直伤；返回最终伤害量
	virtual int dealDamage(double damage, bool direct=false);

	inline int getHP() const
	{
		return healthPoint;
	}

	inline bool isDead() const
	{
		return healthPoint == 0;
	}

};

#endif // _ENEMY_H_
