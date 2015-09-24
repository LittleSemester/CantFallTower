#ifndef __TOWERFIRE_H__
#define __TOWERFIRE_H__

#include "Tower/Tower.h"
#include "cocos2d.h"

class TowerFire:public Tower
{
protected:

	virtual void onFire();

public:
	explicit TowerFire();

	virtual bool init();

	CREATE_FUNC(TowerFire);

};

#endif