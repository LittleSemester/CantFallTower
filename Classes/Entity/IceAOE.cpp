#include "IceAOE.h"

#include "cocos2d.h"
#include "Buff/Buff.h"

USING_NS_CC;

IceAOE::IceAOE()
{
	radius = 100;
	baseDamage = 10;
}


IceAOE::~IceAOE()
{
}

bool IceAOE::isPositionInArea(const cocos2d::Vec2 & relativePos)
{
	return relativePos.getLength()<100;
}

bool IceAOE::init()
{
	if (!AOEArea::init())
	{
		return false;
	}
	auto par = ParticleSystemQuad::create("Ice_Attack.plist");
	par->setTexture(Director::getInstance()->getTextureCache()->addImage("penquan.png"));
	//设置粒子发射时长
	par->setDuration(0.01);
	//设置粒子速度，可改变范围
	par->setSpeed(300);
	addChild(par);

	this->scheduleOnce(schedule_selector(IceAOE::update), 0.5);
	return true;
}

IceAOE * IceAOE::createIceAOE()
{
	IceAOE * ice = IceAOE::create();
	
	
	return ice;
}

void IceAOE::update(float delta)
{
	acquireJudge();
}

void IceAOE::onEnter()
{
	Entity::onEnter();
}

void IceAOE::onDealDamage(Enemy * enemy)
{
	enemy->dealDamage(baseDamage);
	auto buff = new SimpleBuff(2, 1.0, 1.0, 1.0, 0.5);
	buff->setFlag(BUFF_FROZEN);
	enemy->pushBuff(buff);
}