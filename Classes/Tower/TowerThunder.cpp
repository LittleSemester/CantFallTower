// 编码：Utf-8 without BOM
// Created by LuiCat

#include "TowerThunder.h"
#include "Entity/Thunder.h"

USING_NS_CC;

TowerThunder::TowerThunder()
{
	attack = 20;
	radius = 100;
	interval = 0.5;
	//各个级别需要金钱
	cost[1] = 150;
	cost[2] = 200;
	cost[3] = 250;
	sell[1] = 75;
	sell[2] = 175;
	sell[3] = 300;
	currLevel = 1;
}

void TowerThunder::onFire()
{
	Enemy* p = nullptr;
	//改为选择走过距离最远的敌人攻击
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
		auto thunder = Thunder::create();
		thunder->setPosition(p->getPosition());
		thunder->setTarget(p);
		thunder->setBaseDamage(this->attack);
		mainScene->addChild(thunder);
	}

}



bool TowerThunder::init()
{
	if (!Tower::init())
		return false;

	auto spriteTD = Sprite::create();
	auto aniTower = Animation::create();

	for (int i = 0; i <= 4; i++)
	{
		char szName[100];
		sprintf(szName, "Thunder_Tower_%02d.png", i);
		aniTower->addSpriteFrameWithFile(szName);
	}

	//设置帧序列间隔
	aniTower->setDelayPerUnit(0.1);

	//创建帧动画
	auto ani = Animate::create(aniTower);
	auto repeatT = RepeatForever::create(ani);
	spriteTD->runAction(repeatT);
	this->addChild(spriteTD);

	return true;
}

bool TowerThunder::onChangeLevel(int level)
{
	switch (level)
	{
	case 2:
	{
		attack = 30;
		radius = 130;
		interval = 0.4;
		break;
	}
	case 3:
	{
		attack = 45;
		radius = 160;
		interval = 0.35;
		break;
	}
	default:
		break;
	}
	return Tower::onChangeLevel(level);
}