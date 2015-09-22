#include "Tower.h"

USING_NS_CC;

#include "TowerThunder.h"

Tower::Tower()
{
	trow = tcol = 0;
	attack = 50;
	radius = 100;
	interval = 1.0;
}


Tower::~Tower()
{
}

bool Tower::init()
{
	if (!Node::init())
		return false;

	this->schedule(CC_SCHEDULE_SELECTOR(Tower::doFire), interval);

	return true;
}

Tower * Tower::createTower(int type, int row, int col)
{
	Tower* newTD = nullptr;

	switch (type)
	{
	case TOWER_THUNDER:
		newTD = TowerThunder::create();
		break;
	default:
		break;
	}

	if (newTD != nullptr)
		newTD->setRowColumn(row, col);

	return newTD;
}

void Tower::setRowColumn(int row, int col)
{
	this->trow = row;
	this->tcol = col;
	this->setPosition(Vec2(row*56.9 + 28.45, (10 - col)*56.9 + 28.45));
}

void Tower::fire()
{
	if (enemyInRange.size() > 0)
		onFire();
}

void Tower::doFire(float delta)
{
	fire();
}
