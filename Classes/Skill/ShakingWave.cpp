// 编码：Utf-8 without BOM
// Created by LuiCat

#include "ShakingWave.h"

USING_NS_CC;

void ShakingWave::triggleSkill()
{
	Size s = Director::getInstance()->getWinSizeInPixels();
	switch (direction%4)
	{
	case 0:
		createWave(Vec2(s.width + 50, touchBeganPos.y), alignedAngle);
		break;
	case 1:
		createWave(Vec2(touchBeganPos.x, s.height + 100), alignedAngle);
		break;
	case 2:
		createWave(Vec2(-50, touchBeganPos.y), alignedAngle);
		break;
	case 3:
		createWave(Vec2(touchBeganPos.x, -100), alignedAngle);
		break;
	default:
		break;
	}

}

void ShakingWave::createWave(const cocos2d::Vec2& beginPos, float angle)
{
	auto spriteWave = Sprite::create();
	auto aniWave = Animation::create();

	spriteWave->setPosition(beginPos);
	spriteWave->setRotation(-180 * angle / M_PI - 90);
	spriteWave->setAnchorPoint(Vec2(0.5, 0.25));

	char szName[100];
	for (int i = 0; i <= 2; ++i)
	{
		sprintf(szName, "Wave/Wave_Skill_%02d.png", i);
		aniWave->addSpriteFrameWithFile(szName);
	}

	aniWave->setDelayPerUnit(0.1);
	spriteWave->runAction(RepeatForever::create(Animate::create(aniWave)));

	spriteWave->runAction(Sequence::create(
		MoveBy::create(2.5, Vec2::forAngle(angle) * 1300),
		CallFunc::create([spriteWave](){spriteWave->removeFromParent(); }),
		nullptr));

	spriteWave->schedule([spriteWave, this](float){
		int begin = hitEnemy.size();
		mainScene->getEnemyInDistance(hitEnemy, spriteWave->getPosition(), 30.0);
		int total = hitEnemy.size();
		for (int i = begin; i < total; ++i)
		{
			auto buff = new SimpleBuff(2.0, 1.0, 1.0, 1.0, 0.0);
			buff->setFlag(BUFF_DIZZY);
			hitEnemy.at(i)->pushBuff(buff);
		}
	}, 1.0 / 60, "judgeEnemy");

	addChild(spriteWave);

}

double ShakingWave::getCoolDown()
{
	return 40.0;
}
