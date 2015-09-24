// 编码：Utf-8 without BOM
// Created by LuiCat

#include "Hurricane.h"

USING_NS_CC;

bool Hurricane::onTouchBegan(const cocos2d::Vec2& touchPos)
{
	touchBeganPos = touchPos;
	return true;
}

bool Hurricane::onTouchMoved(const cocos2d::Vec2& touchPos)
{
	return true;
}

bool Hurricane::onTouchEnded(const cocos2d::Vec2& touchPos)
{
	Vec2 vec = touchPos - touchBeganPos;
	vertical = ((int)(vec.getAngle() * 2 / M_PI + 2.5) & 1);
	mainScene->alignPosition(touchBeganPos);
	triggleSkill();
	return true;
}

bool Hurricane::needSelectPos()
{
	return true;
}

double Hurricane::getCoolDown()
{
	return 20.0;
}

void Hurricane::triggleSkill()
{
	Size s=Director::getInstance()->getWinSizeInPixels();
	Vector<Enemy*> hitList;
	if (vertical)
	{
		createHurricane(Vec2(touchBeganPos.x + 10, -100), M_PI_2);
		createHurricane(Vec2(touchBeganPos.x - 10, s.height + 100), -M_PI_2);
		mainScene->getEnemyInArea(hitList, [this](const Vec2& pos){return fabs(pos.x - touchBeganPos.x) < 30.0; });
	}
	else
	{
		createHurricane(Vec2(-50, touchBeganPos.y + 10), 0);
		createHurricane(Vec2(s.width + 50, touchBeganPos.y - 10), M_PI);
		mainScene->getEnemyInArea(hitList, [this](const Vec2& pos){return fabs(pos.y - touchBeganPos.y) < 30.0; });
	}
	for (Enemy* enemy : hitList)
	{
		enemy->dealDamage(50);
	}
}

void Hurricane::createHurricane(const cocos2d::Vec2& beginPos, float angle)
{
	auto spriteHrc = Sprite::create();
	auto aniHrc = Animation::create();

	spriteHrc->setPosition(beginPos);
	spriteHrc->setPositionZ(-3.0);
	spriteHrc->setAnchorPoint(Vec2(0.5, 0.25));
	
	char szName[100];
	for (int i = 0; i <= 7; ++i)
	{
		sprintf(szName, "Wind/Wind_Skill_%02d.png", i);
		aniHrc->addSpriteFrameWithFile(szName);
	}

	aniHrc->setDelayPerUnit(0.05);
	spriteHrc->runAction(RepeatForever::create(Animate::create(aniHrc)));

	spriteHrc->runAction(Sequence::create(
		MoveBy::create(1, Vec2::forAngle(angle) * 1100),
		CallFunc::create([spriteHrc](){spriteHrc->removeFromParent(); }),
		nullptr));

	auto repeatAir = RepeatForever::create(Sequence::create(CallFunc::create([this, spriteHrc]()
	{
		auto air = Sprite::create("Wind/air.png");
		air->setPosition(spriteHrc->getPosition() + 
			Vec2(RandomHelper::random_real(-40.0, 40.0), RandomHelper::random_real(-40.0, 40.0)));
		air->setScale(RandomHelper::random_real(0.5, 0.8));
		air->setRotation(RandomHelper::random_real(0.0, M_PI * 2));
		air->runAction(RotateBy::create(1.0, RandomHelper::random_real(-120.0, 120.0)));
		air->runAction(ScaleTo::create(1.0, RandomHelper::random_real(0.8, 1.2)));
		air->runAction(MoveBy::create(1.0, Vec2(
			RandomHelper::random_real(-10.0, 10.0),
			RandomHelper::random_real(-10.0, 10.0))));
		air->runAction(Sequence::create(
			FadeIn::create(0.2),
			DelayTime::create(0.3),
			FadeOut::create(0.5),
			CallFunc::create([air](){air->removeFromParent(); }),
			nullptr));
		this->addChild(air);
	}), DelayTime::create(0.03), nullptr));
	spriteHrc->runAction(repeatAir);

	auto repeatFeather = RepeatForever::create(Sequence::create(CallFunc::create([this, spriteHrc]()
	{
		auto feather = Sprite::create("Wind/feather.png");
		feather->setAnchorPoint(Vec2(0.5, 0.8));
		int type = random(0, 1);
		feather->setPosition(spriteHrc->getPosition() +
			Vec2(RandomHelper::random_real(-40.0, 40.0), RandomHelper::random_real(-40.0, 40.0)));
		feather->setScale(RandomHelper::random_real(0.9, 1.0));
		feather->setRotation(RandomHelper::random_real(0.0, M_PI * 2));
		feather->runAction(RotateBy::create(0.5, (type == 0 ? 360 : -360)));
		feather->runAction(ScaleTo::create(0.5, RandomHelper::random_real(1.0, 1.2)));
		feather->runAction(Sequence::create(
			FadeIn::create(0.1),
			DelayTime::create(0.1),
			FadeOut::create(0.3),
			CallFunc::create([feather](){feather->removeFromParent(); }),
			nullptr));
		this->addChild(feather);
	}), DelayTime::create(0.04), nullptr));
	spriteHrc->runAction(repeatFeather);

	addChild(spriteHrc);

}
