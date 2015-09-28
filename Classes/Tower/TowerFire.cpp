#include "TowerFire.h"
#include "Entity/Missile.h"

USING_NS_CC;


TowerFire::TowerFire()
{
	attack = 15;
	radius = 150;
	interval = 0.7;
	cost[1] = 180;
	cost[2] = 220;
	cost[3] = 260;
	sell[1] = 90;
	sell[2] = 200;
	sell[3] = 330;
	currLevel = 1;
}

void TowerFire::onFire()
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
		auto fire = Missile::createMissile(MISSILE_FIRE);
		Vec2 pos = this->getPosition();
		fire->setPosition(Vec2(pos.x,pos.y+20));
		fire->setTarget(p);
		fire->setBaseDamage(this->attack);
		mainScene->addChild(fire);
	}
}

bool TowerFire::onChangeLevel(int level)
{
	switch (level)
	{
	case 2:
	{
		attack = 30;
		radius = 180;
		interval = 0.6;
		break;
	}
	case 3:
	{
		attack = 50;
		radius = 210;
		interval = 0.5;
		break;
	}
	default:
		break;
	}
	return Tower::onChangeLevel(level);
}


bool TowerFire::init()
{
	if (!Tower::init())
		return false;

	auto spriteTD = Sprite::create();
	auto aniTower = Animation::create();

	for (int i = 0; i < 4; i++)
	{
		char szName[100];
		sprintf(szName, "Fire_Tower_%02d.png", i);
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

