// 编码：Utf-8 without BOM
// Created by LuiCat

#include "FastFreeze.h"

USING_NS_CC;

FastFreeze::FastFreeze()
{

}

FastFreeze::~FastFreeze()
{

}

bool FastFreeze::init()
{
	if(!Skill::init())
		return false;

	return true;
}

double FastFreeze::getCoolDown()
{
	return 20.0;
}

int FastFreeze::getMaxCount()
{
	return 10;
}

bool FastFreeze::onTouchBegan(const cocos2d::Vec2& touchPos)
{
	return true;
}

bool FastFreeze::onTouchMoved(const cocos2d::Vec2& touchPos)
{
	return true;
}

bool FastFreeze::onTouchEnded(const cocos2d::Vec2& touchPos)
{
	Enemy* enemy = mainScene->getNearestEnemy(touchPos, 30);
	if (enemy == nullptr)
		return false;

	auto buff = new SimpleBuff(3, 1.0, 1.0, 2.0, 0.0);
	buff->setFlag(BUFF_DEEPFROZEN);
	enemy->pushBuff(buff);

	char szName[100];

	auto ice2 = Sprite::create();
	auto ani2 = Animation::create();
	for (int i = 0; i <= 4; ++i)
	{
		sprintf(szName, "Ice/Ice_Skill_Rock_%02d.png", i);
		ani2->addSpriteFrameWithFile(szName);
	}
	ani2->setDelayPerUnit(0.1);
	ice2->runAction(Sequence::create(Animate::create(ani2), CallFunc::create([ice2](){ice2->removeFromParent(); }), nullptr));
	ice2->setPosition(enemy->getPosition());
	ice2->setScale(0.6);
	addChild(ice2);

	auto ice1=Sprite::create("Ice/Ice_Skill_05.png");
	auto ani1 = Animation::create();
	for (int i = 0; i <= 5; ++i)
	{
		sprintf(szName, "Ice/Ice_Skill_%02d.png", i);
		ani1->addSpriteFrameWithFile(szName);
	}
	ani1->setDelayPerUnit(0.1);
	ice1->runAction(Animate::create(ani1));
	ice1->runAction(Sequence::create(DelayTime::create(3.0), FadeOut::create(0.5), CallFunc::create([ice1](){ice1->removeFromParent(); }), nullptr));
	ice1->setPosition(enemy->getPosition());
	ice1->setScale(0.6);
	addChild(ice1);

	return true;
}

bool FastFreeze::needSelectPos()
{
	return true;
}
