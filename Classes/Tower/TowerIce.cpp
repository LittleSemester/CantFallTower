#include "TowerIce.h"
#include "Entity/Missile.h"

USING_NS_CC;



TowerIce::TowerIce()
{
	attack = 30;
	radius = 100;
	interval = 1;
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

}