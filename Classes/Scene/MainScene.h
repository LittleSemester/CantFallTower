#ifndef __MAINSCENE_H__
#define __MAINSCENE_H__
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

class MainScene : public cocos2d::Layer
{
public:
	MainScene();
	~MainScene();

	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(MainScene);

	void btnStartCalback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

	void btnExitCalback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

	void btnIntroCalback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
};

#endif