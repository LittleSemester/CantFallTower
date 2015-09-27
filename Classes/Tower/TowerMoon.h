#ifndef __TOWERMOON_H__
#define __TOWERMOON_H__
#include "cocos2d.h"
#include "Tower/Tower.h"
class TowerMoon : public Tower
{
protected:

	virtual void onFire();


public:
	TowerMoon();
	~TowerMoon();

	virtual bool init();

	CREATE_FUNC(TowerMoon);
};


#endif