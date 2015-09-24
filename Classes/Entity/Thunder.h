// 编码：Utf-8 without BOM
// Created by LuiCat

#ifndef _THUNDER_H_
#define _THUNDER_H_

#include "Entity.h"

class Thunder : public Entity
{
protected:

	Enemy* target;

public:

	explicit Thunder();

	virtual bool init();
	virtual void update(float delta);

	virtual void onEnter();

	void setTarget(Enemy* enemy);

	virtual bool judgeSingleEnemy(Enemy* enemy);

	CREATE_FUNC(Thunder);


};

#endif // _THUNDER_H_
