#ifndef __ICEAOE_H__
#define __ICEAOE_H__
#include "AOEArea.h"
#include "cocos2d.h"
class IceAOE:public AOEArea
{
protected:

	virtual bool isPositionInArea(const cocos2d::Vec2& relativePos);

	virtual void onDealDamage(Enemy* enemy);


public:
	explicit IceAOE();
	~IceAOE();

	virtual bool init();

	CREATE_FUNC(IceAOE);

	virtual void update(float delta); 
	virtual void onEnter();
	

	float radius;//AOE·¶Î§

	static IceAOE * createIceAOE();


};

#endif