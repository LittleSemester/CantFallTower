// 编码：Utf-8 without BOM
// Created by LuiCat

#include "Thunder.h"

USING_NS_CC;

Thunder::Thunder()
{
	baseDamage = 20.0;
	target = nullptr;
}

bool Thunder::init()
{
	if (!Entity::init())
		return false;

	auto anisprite = Sprite::create("Thunder/Thunder_Picture.png");
	auto animation = Animation::create();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Sprite/Thunder/Thunder_Picture.plist", anisprite->getTexture());

	char szName[100];
	for (int i = 0; i <= 4; i++)
	{
		sprintf(szName, "Thunder Attack/Thunder_Attack_%02d.png", i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(szName);
		animation->addSpriteFrame(frame);
	}

	animation->setDelayPerUnit(0.08);
	animation->setLoops(2);

	auto sprite = Sprite::create();
	auto animate = Animate::create(animation);
	auto deadFunc = CallFunc::create([this]() {this->removeFromParent(); });
	auto sequence = Sequence::create(animate, deadFunc, NULL);
	sprite->setPositionY(20);
	sprite->setScale(1.5);
	sprite->runAction(sequence);

	this->addChild(sprite);

	this->scheduleUpdate();

	return true;
}

void Thunder::update(float delta)
{
	if (target == nullptr)
		return;

	this->setPosition(target->getPosition());

}

void Thunder::onEnter()
{
	Entity::onEnter();
	if (target != nullptr)
		this->acquireJudge(target);
	else
		this->removeFromParent();
}

void Thunder::setTarget(Enemy* enemy)
{
	if (target != nullptr)
		target->release();
	if (enemy != nullptr)
		target = enemy;
	target->retain();
}

bool Thunder::judgeSingleEnemy(Enemy* enemy)
{
	if (enemy == target)
	{
		enemy->dealDamage(baseDamage);
		return true;
	}
	return false;
}
