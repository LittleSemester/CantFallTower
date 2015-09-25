#ifndef __WINSCENE_H__
#define __WINSCENE_H__
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
class WinScene:public cocos2d::Layer
{
public:
	WinScene();
	~WinScene();
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(WinScene);

	void btnStartCalback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

	void btnExitCalback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
};

#endif