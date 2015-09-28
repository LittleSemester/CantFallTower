#include "TowerIce.h"
#include "Entity/Missile.h"
#include "Entity/IceAOE.h"
USING_NS_CC;



TowerIce::TowerIce()
{
	attack = 7;
	radius = 100;
	interval = 1;
	//各个级别需要金钱
	cost[1] = 160;
	cost[2] = 200;
	cost[3] = 240;
	sell[1] = 80;
	sell[2] = 180;
	sell[3] = 300;
	currLevel = 1;
}

bool TowerIce::init()
{
	if (!Tower::init())
		return false;

	auto spriteTD = Sprite::create();
	auto aniTower = Animation::create();
	for (int i = 0; i < 7; i++)
	{
		SpriteFrame *sf = SpriteFrameCache::getInstance()->getSpriteFrameByName(
			StringUtils::format("Ice Tower/Ice_Tower_%02d.png", i));
		aniTower->addSpriteFrame(sf);
	}

	//设置帧序列间隔
	aniTower->setDelayPerUnit(0.1);

	//创建帧动画
	auto ani = Animate::create(aniTower);
	auto repeatT = RepeatForever::create(ani);
	spriteTD->setScale(0.7);
	spriteTD->runAction(repeatT);
	this->addChild(spriteTD);

	return true;
}


void TowerIce::onFire()
{
	//Enemy* p = nullptr;
	////改为选择走过距离最远的敌人攻击
	//float dist = -INFINITY, t;
	//for (Enemy* enemy : enemyInRange)
	//{
	//	t = enemy->getDistance();
	//	if (t > dist)
	//	{
	//		p = enemy;
	//		dist = t;
	//	}
	//}

	//if (p != nullptr)
	//{
	//	auto star = Missile::createMissile(MISSILE_STAR);
	//	star->setPosition(this->getPosition());
	//	star->setTarget(p);
	//	mainScene->addChild(star);
	//}
	auto iceAtk = IceAOE::createIceAOE();
	iceAtk->setPosition(this->getPosition());
	iceAtk->setScale(0.5);
	iceAtk->setBaseDamage(this->attack);
	mainScene->addChild(iceAtk);
}

bool TowerIce::onChangeLevel(int level)
{
	switch (level)
	{
	case 2:
	{
		attack = 10;
		radius = 130;
		interval = 0.8;
		break;
	}
	case 3:
	{
		attack = 15;
		radius = 160;
		interval = 0.7;
		break;
	}
	default:
		break;
	}
	return Tower::onChangeLevel(level);
}
