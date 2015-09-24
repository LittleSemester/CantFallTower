#include "FireAOE.h"
#include "cocos2d.h"
#include "Buff/Buff.h"

USING_NS_CC;


bool FireAOE::isPositionInArea(const cocos2d::Vec2 & relativePos)
{
	return relativePos.getLength()<radius;

}

void FireAOE::onDealDamage(Enemy * enemy)
{
	enemy->dealDamage(baseDamage);
}

FireAOE::FireAOE()
{
	radius = 100;
	baseDamage = 10;
}


FireAOE::~FireAOE()
{
}

bool FireAOE::init()
{
	if (!AOEArea::init())
	{
		return false;
	}
	auto fireS = Sprite::create();

	auto boom = Animation::create();
	for (int i = 0; i < 6; i++)
	{
		char szName[100];
		sprintf(szName, "Fire_Attack_Boom_%02d.png", i);
		boom->addSpriteFrameWithFileName(szName);
	}
	boom->setDelayPerUnit(0.1);
	boom->setRestoreOriginalFrame(true);
	auto aniBoom = Animate::create(boom);
	fireS->runAction(aniBoom);
	fireS->setOpacity(150);
	this->addChild(fireS);
	

	this->scheduleOnce(schedule_selector(FireAOE::update), 0.2);
	return true;
}

void FireAOE::update(float delta)
{
	acquireJudge();
}

FireAOE * FireAOE::createFireAOE()
{
	FireAOE* fire = FireAOE::create();
	return fire;
}
