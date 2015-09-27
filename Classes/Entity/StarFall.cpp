#include "StarFall.h"

USING_NS_CC;

StarFall::StarFall()
{
	baseDamage = 15.0;
	target = nullptr;
}


StarFall::~StarFall()
{
}

bool StarFall::init()
{
	if (!Entity::init())
		return false;

	auto animation = Animation::create();

	//auto anisprite = Sprite::create("Thunder/Thunder_Picture.png");
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Sprite/Thunder/Thunder_Picture.plist", anisprite->getTexture());

	char szName[100];
	for (int i = 0; i < 8; ++i)
	{
		sprintf(szName, "Star/Star Attack/Star_Attack_%02d.png", i);
		animation->addSpriteFrameWithFile(szName);
	}

	animation->setDelayPerUnit(0.1);
	animation->setLoops(1);

	auto sprite = Sprite::create();
	auto animate = Animate::create(animation);
	auto deadFunc = CallFunc::create([this]() {this->removeFromParent(); });
	auto sequence = Sequence::create(animate, deadFunc, NULL);
	sprite->setScale(0.4);
	sprite->setAnchorPoint(Vec2(0.5, 0.05));
	sprite->setPositionY(-20.0);
	sprite->runAction(sequence);

	this->addChild(sprite);

	this->scheduleUpdate();

	return true;
}

void StarFall::update(float delta)
{
	if (target == nullptr)
		return;

	this->setPosition(target->getPosition());
}

void StarFall::onEnter()
{
	Entity::onEnter();
	if (target != nullptr)
		this->acquireJudge(target);
	else
		this->removeFromParent();
}

void StarFall::setTarget(Enemy * enemy)
{
	if (enemy == nullptr || target == enemy)
		return;
	if (target != nullptr)
		target->release();
	target = enemy;
	target->retain();
}

bool StarFall::judgeSingleEnemy(Enemy * enemy)
{
	if (enemy == target)
	{
		enemy->dealDamage(baseDamage);
		return true;
	}
	return false;
}
