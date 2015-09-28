#ifndef __TOWER_ICE__
#define __TOWER_ICE
#include "Tower.h"
#include <cocos2d.h>

class TowerIce: public Tower
{
protected:

	virtual void onFire();

	bool onChangeLevel(int level);

public:

	explicit TowerIce();

	virtual bool init();

	CREATE_FUNC(TowerIce);


};

#endif
