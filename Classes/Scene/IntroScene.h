#ifndef __INTROSCENE_H__
#define __INTROSCENE_H__
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

class IntroScene:public cocos2d::Layer
{
public:
	IntroScene();
	~IntroScene();

	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(IntroScene);

	void btnRetCalback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

	
};

#endif