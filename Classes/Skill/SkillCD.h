#ifndef __SKILLCD_H__
#define __SKILLCD_H__
#include <cocos2d.h>
class SkillCD:public cocos2d::Node
{
public:
	SkillCD();
	~SkillCD();

	bool init();

	CREATE_FUNC(SkillCD);

	void updateCD(float dt);

	cocos2d::Sprite* spriteCD;

	int nowTime;
	int startCal;
};

#endif