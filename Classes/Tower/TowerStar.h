#ifndef __TOWERSTAR_H__
#define __TOWERSTAR_H__
#include "Tower/Tower.h"
#include "cocos2d.h"
class TowerStar:public Tower
{
protected:

	virtual void onFire();

	bool onChangeLevel(int level);
public:
	explicit TowerStar();
	~TowerStar();

	virtual bool init();

	CREATE_FUNC(TowerStar);
};

#endif