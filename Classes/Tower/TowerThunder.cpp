// 编码：Utf-8 without BOM
// Created by LuiCat

#include "TowerThunder.h"
#include "Entity/Missile.h"

USING_NS_CC;

TowerThunder::TowerThunder()
{
	attack = 50;
	radius = 100;
	interval = 0.5;
}

void TowerThunder::onFire()
{
	Enemy* p = nullptr;
	float dist = INFINITY, t;
	for (Enemy* enemy : enemyInRange)
	{
		t = this->getPosition().distance(enemy->getPosition());
		if (t < dist)
		{
			p = enemy;
			dist = t;
		}
	}

	if (p != nullptr)
	{
		auto star = Missile::createMissile(MISSILE_STAR);
		star->setPosition(this->getPosition());
		star->setTarget(p);
		mainScene->addChild(star);
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

