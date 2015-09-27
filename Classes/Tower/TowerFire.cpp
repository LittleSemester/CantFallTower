#include "TowerFire.h"
#include "Entity/Missile.h"

USING_NS_CC;


TowerFire::TowerFire()
{
	attack = 10;
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
	//��Ϊѡ���߹�������Զ�ĵ��˹���
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
		mainScene->addChild(fire);
	}
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

	//����֡���м��
	aniTower->setDelayPerUnit(0.1);

	//����֡����
	auto ani = Animate::create(aniTower);
	auto repeatT = RepeatForever::create(ani);
	spriteTD->runAction(repeatT);
	this->addChild(spriteTD);

	return true;
}

