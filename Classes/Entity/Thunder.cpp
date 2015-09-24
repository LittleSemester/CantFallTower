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

	auto animation = Animation::create();

	//auto anisprite = Sprite::create("Thunder/Thunder_Picture.png");
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Sprite/Thunder/Thunder_Picture.plist", anisprite->getTexture());

	char szName[100];
	for (int i = 1; i <= 10; ++i)
	{
		sprintf(szName, "Thunder/thunder%02d.png", i);
		animation->addSpriteFrameWithFile(szName);
	}

	animation->setDelayPerUnit(0.05);
	animation->setLoops(1);

	auto sprite = Sprite::create();
	auto animate = Animate::create(animation);
	auto deadFunc = CallFunc::create([this]() {this->removeFromParent(); });
	auto sequence = Sequence::create(animate, deadFunc, NULL);
	sprite->setScale(0.2);
	sprite->setAnchorPoint(Vec2(0.5, 0.05));
	sprite->setPositionY(-20.0);
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
	if (enemy == nullptr)
		return;
	if (target != nullptr)
		target->release();
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
