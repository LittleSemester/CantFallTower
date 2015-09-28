#include "SkillCD.h"

USING_NS_CC;


SkillCD::SkillCD()
{
}


SkillCD::~SkillCD()
{
}

bool SkillCD::init()
{
	if (!Node::init())
	{
		return false;
	}
	startCal = 0;
	

	spriteCD = Sprite::create("skillCD.png");
	spriteCD->setAnchorPoint(Vec2(0.5, 0));
	addChild(spriteCD);
	schedule(schedule_selector(SkillCD::updateCD), 1.0, -1, 0.0);
	return true;
}

void SkillCD::updateCD(float dt)
{
	if (startCal == 0)
	{
		startCal = 1;
		nowTime = 0;
	}
	else
	{
		nowTime++;
	}
	if (nowTime >= 30)
	{
		spriteCD->removeFromParent();
		this->removeFromParent();
		return;
	}
	float dark = 1.0*(30 - nowTime) / 30;
	spriteCD->setScaleY(dark);

}
