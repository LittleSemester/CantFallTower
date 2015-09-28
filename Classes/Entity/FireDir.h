#ifndef __FIREDIR_H__
#define __FIREDIR_H__
#include <cocos2d.h>
#include "Missile.h"
class FireDir : public Missile
{
private:

	cocos2d::Sprite* sprite;

	cocos2d::Vec2 fireDir;

	float boomRadius;

public:
	explicit FireDir();

	virtual bool init();
	virtual void update(float delta);

	virtual bool judgeSingleEnemy(Enemy* enemy);

	void setBoom(float rad);

	CREATE_FUNC(FireDir);

};

#endif