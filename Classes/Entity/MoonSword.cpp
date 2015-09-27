#include "MoonSword.h"

USING_NS_CC;

MoonSword::MoonSword()
{
	moonDir = Vec2(0, -1.0);

}


MoonSword::~MoonSword()
{
}

bool MoonSword::init()
{
	if (!Missile::init())
		return false;

	//月刃动画
	auto aniMoon = Animation::create();

	
	char szName[100];
	sprintf(szName, "Moon/Moon Attack/Moon_Attack.png");
	aniMoon->addSpriteFrameWithFile(szName);

	//设置帧序列间隔
	aniMoon->setDelayPerUnit(0.1);

	//创建帧动画
	auto ani = Animate::create(aniMoon);
	auto repeatMoon = RepeatForever::create(ani);

	sprite = Sprite::create();
	sprite->setScale(0.7);
	sprite->runAction(repeatMoon);
	this->addChild(sprite);

	this->remainTime = 0.5;
	this->baseDamage = 10.0;

	return true;
}

void MoonSword::update(float delta)
{
	Missile::update(delta);

	if (isFinished())
		return;

	//根据方向改变火球飞行
	Vec2 tarPos = target->getPosition();
	Vec2 nowPos = this->getPosition();
	Vec2 dis = tarPos - nowPos;
	sprite->setRotation(-180 * dis.getAngle() / M_PI - 90);
	moonDir = dis;
}

bool MoonSword::judgeSingleEnemy(Enemy * enemy)
{
	if (enemy == nullptr || enemy != target)
		return false;

	if (targetReached)
	{
		enemy->dealDamage(baseDamage);
		//计算伤害并生成下一个月刃继续弹射
		int nextTime = this->jumpTimes - 1;
		if (nextTime > 0)
		{
			this->enemyInRange.clear();
			mainScene->getEnemyInDistance(this->enemyInRange, this->getPosition(), 100);
			Enemy* nextEnemy;
			if (this->enemyInRange.size() <= 1)
				return true;
			for (Enemy* next : this->enemyInRange)
			{
				if (next != enemy)
				{
					nextEnemy = next;
					break;
				}
			}
			auto moon = MoonSword::create();
			moon->setPosition(this->getPosition());
			moon->setTarget(nextEnemy);
			moon->setJump(nextTime);
			mainScene->addChild(moon);
		}
		return true;
	}
	return false;
	
	
}

void MoonSword::setJump(int time)
{
	this->jumpTimes = time;
}
