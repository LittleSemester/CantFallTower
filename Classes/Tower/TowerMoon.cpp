#include "TowerMoon.h"
#include "Entity/MoonSword.h"
USING_NS_CC;

void TowerMoon::onFire()
{
	Enemy* p = nullptr;
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
		auto moon = MoonSword::create();
		moon->setPosition(this->getPosition());
		moon->setTarget(p);
		moon->setJump(3);
		moon->setBaseDamage(this->attack);
		mainScene->addChild(moon);
	}
}

bool TowerMoon::onChangeLevel(int level)
{
	switch (level)
	{
	case 2:
	{
		attack = 20;
		radius = 180;
		interval = 0.9;
		break;
	}
	case 3:
	{
		attack = 40;
		radius = 210;
		interval = 0.8;
		break;
	}
	default:
		break;
	}
	return Tower::onChangeLevel(level);
}

TowerMoon::TowerMoon()
{
	radius = 150;
	attack = 10.0;
	interval = 1.0;
	//����������Ҫ��Ǯ
	cost[1] = 200;
	cost[2] = 240;
	cost[3] = 280;
	sell[1] = 100;
	sell[2] = 220;
	sell[3] = 360;
	currLevel = 1;
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

	//����֡���м��
	aniTower->setDelayPerUnit(0.1);

	//����֡����
	auto ani = Animate::create(aniTower);
	auto repeatT = RepeatForever::create(ani);
	spriteTD->runAction(repeatT);
	spriteTD->setScale(0.45);
	this->addChild(spriteTD);

	return true;
}


