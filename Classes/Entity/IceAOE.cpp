#include "IceAOE.h"

#include "cocos2d.h"
#include "Buff/Buff.h"

USING_NS_CC;

IceAOE::IceAOE()
{
	radius = 100;
	baseDamage = 7;
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

	auto splash = Sprite::create("Ice/Ice_Attack_05.png");
	splash->setScale(0.0);
	auto scale = ScaleTo::create(0.6, 3.0);
	splash->runAction(scale);
	auto fade = FadeOut::create(0.1);
	splash->runAction(Sequence::create(DelayTime::create(0.3), fade, NULL));
	addChild(splash);

	auto par = ParticleSystemQuad::create("Ice_Attack.plist");
	par->setTexture(Director::getInstance()->getTextureCache()->addImage("penquan.png"));
	//设置粒子发射时长
	par->setDuration(0.01);
	//设置粒子速度，可改变范围
	par->setSpeed(260);
	par->setSpeedVar(80);
	par->setTotalParticles(200);
	addChild(par);

	auto dead = CallFunc::create([this](){this->removeFromParent(); });
	this->runAction(Sequence::create(DelayTime::create(1.0), dead, NULL));

	this->scheduleOnce(CC_SCHEDULE_SELECTOR(IceAOE::update), 0.3);
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


void IceAOE::onDealDamage(Enemy * enemy)
{
	enemy->dealDamage(baseDamage);
	auto buff = new SimpleBuff(2, 1.0, 1.0, 1.0, 0.5);
	buff->setFlag(BUFF_FROZEN);
	enemy->pushBuff(buff);
}