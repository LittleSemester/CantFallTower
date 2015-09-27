#ifndef __MOONSWORD_H__
#define __MOONSWORD_H__
#include "Missile.h"
#include "cocos2d.h"
class MoonSword:public Missile
{
private:

	cocos2d::Sprite* sprite;

	cocos2d::Vec2 moonDir;

	cocos2d::Vector<Enemy*> enemyInRange;

	int jumpTimes;
public:
	explicit MoonSword();
	~MoonSword();

	virtual bool init();
	virtual void update(float delta);

	virtual bool judgeSingleEnemy(Enemy* enemy);

	void setJump(int time);

	CREATE_FUNC(MoonSword);
};

#endif 