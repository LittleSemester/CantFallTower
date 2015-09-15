#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <cocos2d.h>
#include <math\CCGeometry.h>

#include "buff/Buff.h"

class Enemy : public cocos2d::Node
{
protected:



public:

	Enemy();
	~Enemy();

	virtual void onEnter();
	virtual void onExit();
	
	virtual void update(float delta);

	virtual int maxHP();
	virtual int defence();

	// 对该敌人造成伤害，期间检查敌人各项属性和buff，指定direct=true造成直伤
	virtual void dealDamage(double damage, bool direct=false);

};

#endif // _ENEMY_H_
