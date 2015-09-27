#ifndef __STARFALL_H__
#define __STARFALL_H__
#include "cocos2d.h"
#include "Entity.h"

class StarFall:public Entity
{
protected:

	Enemy* target;

public:
	explicit StarFall();
	~StarFall();

	virtual bool init();
	virtual void update(float delta);

	virtual void onEnter();

	void setTarget(Enemy* enemy);

	virtual bool judgeSingleEnemy(Enemy* enemy);

	CREATE_FUNC(StarFall);
};

#endif