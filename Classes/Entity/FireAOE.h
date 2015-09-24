#ifndef __FIREAOE_H__
#define __FIREAOE_H__
#include "AOEArea.h"
#include "cocos2d.h"
class FireAOE:public AOEArea
{
protected:
	virtual bool isPositionInArea(const cocos2d::Vec2& relativePos);

	virtual void onDealDamage(Enemy* enemy);

public:
	explicit FireAOE();
	~FireAOE();

	virtual bool init();

	CREATE_FUNC(FireAOE);

	virtual void update(float delta);



	float radius;//AOE·¶Î§

	static FireAOE * createFireAOE();
	
};

#endif