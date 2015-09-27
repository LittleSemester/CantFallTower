#include "Tower.h"

USING_NS_CC;

#include "TowerThunder.h"
#include "TowerIce.h"
#include "TowerFire.h"
#include "TowerStar.h"
#include "TowerMoon.h"
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

	onChangeLevel(1);

	return true;
}

void Tower::onEnter()
{
	Node::onEnter();
	Node* node = this->getParent();
	mainScene = dynamic_cast<GameScene*>(node);
	if (mainScene == nullptr)
		removeFromParent();
}

Tower * Tower::createTower(int type, int row, int col)
{
	Tower* newTD = nullptr;

	switch (type)
	{
	case TOWER_THUNDER:
		newTD = TowerThunder::create();
		break;
	case TOWER_ICE:
		{
			newTD = TowerIce::create();
			break;
		}
	case TOWER_FIRE:
	{
		newTD = TowerFire::create();
		break;
	}
	case TOWER_ARROW:
	{
		newTD = TowerStar::create();
		break;
	}
	case TOWER_KNIFE:
	{
		newTD = TowerMoon::create();
	}
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
	enemyInRange.clear();
	mainScene->getEnemyInDistance(enemyInRange, this->getPosition(), radius);
	fire();
}

void Tower::onBuffBegin(Buff* buff)
{
	this->schedule(CC_SCHEDULE_SELECTOR(Tower::doFire), interval / calcBuffedValue(&Buff::speed, 1.0));
}

void Tower::onBuffEnd(Buff* buff)
{
	this->schedule(CC_SCHEDULE_SELECTOR(Tower::doFire), interval / calcBuffedValue(&Buff::speed, 1.0));
}

bool Tower::upgrate()
{
	if (onChangeLevel(currLevel + 1))
	{
		++currLevel;
		return true;
	}
	return false;
}

bool Tower::onChangeLevel(int level)
{
	//加上等级星数显示
	auto levelstar = Sprite::create("level1.png");
	levelstar->setName("level");
	levelstar->setPosition(Vec2(0, 28));
	levelstar->setLocalZOrder(3);
	addChild(levelstar);
	return true;
}

int Tower::getMoney(int level /*= 1*/)
{
	return 0;
}
