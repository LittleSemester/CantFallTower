// 编码：Utf-8 without BOM
// Created by LuiCat

#ifndef _TOWER_THUNDER_H_
#define _TOWER_THUNDER_H_

#include "Tower.h"
#include <cocos2d.h>

class TowerThunder : public Tower
{
protected:

	virtual void onFire();



public:

	explicit TowerThunder();

	virtual bool init();

	CREATE_FUNC(TowerThunder);
	

};


#endif // _TOWER_THUNDER_H_
