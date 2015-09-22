// 编码：Utf-8 without BOM
// Created by LuiCat

#include "AOEArea.h"

bool AOEArea::judgeSingleEnemy(Enemy* enemy)
{
	if (enemy == nullptr)
		return false;

	Vec2 vecEnemy = enemy->getPosition();
	vecEnemy -= this->getPosition();
	if (isPositionInArea(vecEnemy))
	{
		enemy->dealDamage(baseDamage);
		return true;
	}

	return false;
}
