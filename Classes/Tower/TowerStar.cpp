#include "TowerStar.h"
#include "Entity/StarFall.h"
USING_NS_CC;


void TowerStar::onFire()
{
	Enemy* p = nullptr;
	//攻击范围内的所有敌人
	float dist = -INFINITY, t;
	for (Enemy* enemy : enemyInRange)
	{
		auto star = StarFall::create();
		star->setPosition(enemy->getPosition());
		star->setTarget(enemy);
		star->setBaseDamage(this->attack);
		mainScene->addChild(star);
	}

	//if (p != nullptr)
	//{
	//	/*auto thunder = Thunder::create();
	//	thunder->setPosition(p->getPosition());
	//	thunder->setTarget(p);
	//	mainScene->addChild(thunder);*/
	//}
}

bool TowerStar::onChangeLevel(int level)
{
	switch (level)
	{
	case 2:
	{
		attack = 25;
		radius = 140;
		interval = 0.7;
		break;
	}
	case 3:
	{
		attack = 40;
		radius = 180;
		interval = 0.6;
		break;
	}
	default:
		break;
	}
	return Tower::onChangeLevel(level);
}

TowerStar::TowerStar()
{
	radius = 100;
	attack = 15;
	interval = 0.8;
	//各个级别需要金钱
	cost[1] = 220;
	cost[2] = 260;
	cost[3] = 300;
	sell[1] = 110;
	sell[2] = 240;
	sell[3] = 390;
	currLevel = 1;
}


TowerStar::~TowerStar()
{
}

bool TowerStar::init()
{
	if (!Tower::init())
		return false;

	auto spriteTD = Sprite::create();
	auto aniTower = Animation::create();

	for (int i = 0; i <= 4; i++)
	{
		char szName[100];
		sprintf(szName, "Star/Star Tower/Star_Tower_%02d.png", i);
		aniTower->addSpriteFrameWithFile(szName);
	}

	//设置帧序列间隔
	aniTower->setDelayPerUnit(0.1);

	//创建帧动画
	auto ani = Animate::create(aniTower);
	auto repeatT = RepeatForever::create(ani);
	spriteTD->runAction(repeatT);
	spriteTD->setScale(0.6);
	this->addChild(spriteTD);

	return true;
}
