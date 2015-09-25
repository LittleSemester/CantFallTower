#ifndef __LOSESCENE_H__
#define __LOSESCENE_H__
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
class LoseScene:public cocos2d::Layer
{
public:
	LoseScene();
	~LoseScene();

	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(LoseScene);

	void btnAgainCalback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

	void btnReturnCalback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
};

#endif 