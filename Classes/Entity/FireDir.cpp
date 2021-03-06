#include "FireDir.h"
#include <cocos2d.h>
#include "FireAOE.h"

USING_NS_CC;



FireDir::FireDir()
{
	fireDir = Vec2(0, -1.0);
}

bool FireDir::init()
{
	if (!Missile::init())
		return false;

	//火焰动画
	auto aniFire = Animation::create();

	for (int i = 0; i < 5; i++)
	{
		char szName[100];
		sprintf(szName, "Fire_Attack_ball_%02d.png", i);
		aniFire->addSpriteFrameWithFile(szName);
	}

	//设置帧序列间隔
	aniFire->setDelayPerUnit(0.1);

	//创建帧动画
	auto ani = Animate::create(aniFire);
	auto repeatFire = RepeatForever::create(ani);

	sprite = Sprite::create();
	sprite->setScale(0.7);
	sprite->runAction(repeatFire);
	this->addChild(sprite);

	this->baseDamage = 10.0;
	this->initSpeed = 250.0;

	return true;
}

void FireDir::update(float delta)
{
	Missile::update(delta);

	if (isFinished())
		return;

	//根据方向改变火球飞行
	Vec2 tarPos = target->getPosition();
	Vec2 nowPos = this->getPosition();
	Vec2 dis = tarPos - nowPos;
	sprite->setRotation(-180*dis.getAngle()/M_PI-90);
	fireDir = dis;

}

bool FireDir::judgeSingleEnemy(Enemy * enemy)
{
	if (enemy == nullptr || enemy != target)
		return false;
	//生成爆炸AOE并计算伤害
	auto boom = FireAOE::createFireAOE();
	boom->setPosition(enemy->getPosition());
	boom->setBaseDamage(this->baseDamage);
	mainScene->addChild(boom);
	return true;
}

void FireDir::setBoom(float rad)
{
	this->boomRadius = rad;
}
