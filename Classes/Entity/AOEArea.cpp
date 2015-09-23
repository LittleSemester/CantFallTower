// 编码：Utf-8 without BOM
// Created by LuiCat

#include "AOEArea.h"

USING_NS_CC;

void AOEArea::onDealDamage(Enemy* enemy)
{
	enemy->dealDamage(baseDamage);
}

bool AOEArea::judgeSingleEnemy(Enemy* enemy)
{
	if (enemy == nullptr)
		return false;

	Vec2 vecEnemy = enemy->getPosition();
	vecEnemy -= this->getPosition();
	if (isPositionInArea(vecEnemy))
	{
		onDealDamage(enemy);
		return true;
	}

	return false;
}
