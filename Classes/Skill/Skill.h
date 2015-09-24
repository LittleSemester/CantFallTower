// 编码：Utf-8 without BOM
// Created by LuiCat

#ifndef _SKILL_H_
#define _SKILL_H_

#include <cocos2d.h>
#include "Scene/GameScene.h"

class GameScene;

class Skill : public cocos2d::Node
{
protected:

	GameScene* mainScene;

public:

	explicit Skill();
	virtual ~Skill()=0;

	virtual void onEnter();

	// 返回false以意外结束选择技能释放位置，技能将不释放；三者全部返回true则触摸结束时技能将被释放
	virtual bool onTouchBegan(const cocos2d::Vec2& touchPos);
	virtual bool onTouchMoved(const cocos2d::Vec2& touchPos);
	virtual bool onTouchEnded(const cocos2d::Vec2& touchPos);

	// 派生类技能是否需要选择释放位置，返回true则GameScene会通过三个onTouch函数传递位置信息
	virtual bool needSelectPos();

	virtual double getCoolDown();
	virtual int getMaxCount();

	virtual void setLevel(int level);

};


#endif // _SKILL_H_

