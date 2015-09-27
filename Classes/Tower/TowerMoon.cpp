#include "TowerMoon.h"

USING_NS_CC;

void TowerMoon::onFire()
{
	Enemy* p = nullptr;
	//攻击范围内的所有敌人
	float dist = -INFINITY, t;
	for (Enemy* enemy : enemyInRange)
	{
		t = enemy->getDistance();
		if (t > dist)
		{
			p = enemy;
			dist = t;
		}
	}

	if (p != nullptr)
	{
		//auto thunder = Thunder::create();
		/*thunder->setPosition(p->getPosition());
		thunder->setTarget(p);
		mainScene->addChild(thunder);*/
	}
}

TowerMoon::TowerMoon()
{
	radius = 150;
	attack = 9;
	interval = 1.0;
}


TowerMoon::~TowerMoon()
{
}

bool TowerMoon::init()
{
	if (!Tower::init())
		return false;

	auto spriteTD = Sprite::create();
	auto aniTower = Animation::create();

	for (int i = 0; i < 4; i++)
	{
		char szName[100];
		sprintf(szName, "Moon/Moon Tower/Moon_Tower_%02d.png", i);
		aniTower->addSpriteFrameWithFile(szName);
	}

	//设置帧序列间隔
	aniTower->setDelayPerUnit(0.1);

	//创建帧动画
	auto ani = Animate::create(aniTower);
	auto repeatT = RepeatForever::create(ani);
	spriteTD->runAction(repeatT);
	spriteTD->setScale(0.45);
	this->addChild(spriteTD);

	return true;
}
