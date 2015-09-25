#include "WinScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Enemy/TestEnemy.h"
#include "GameScene.h"
#include "MainScene.h"
USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;



WinScene::WinScene()
{
}


WinScene::~WinScene()
{
}

cocos2d::Scene * WinScene::createScene()
{
	auto scene = Scene::create();

	auto layer = WinScene::create();

	scene->addChild(layer);

	return scene;
}

bool WinScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto backGround = Sprite::create("GameScreen_youwin.png");
	backGround->setPosition(Vec2(480, 320));
	addChild(backGround);

	Button * btn_Again = Button::create("GameScreen_win_goon.png");
	btn_Again->setPosition(Vec2(350, 250));
	addChild(btn_Again);
	btn_Again->addTouchEventListener(CC_CALLBACK_2(WinScene::btnStartCalback, this));

	Button * btn_Return = Button::create("GameScreen_backmenu.png");
	btn_Return->setPosition(Vec2(600, 250));
	addChild(btn_Return);
	btn_Return->addTouchEventListener(CC_CALLBACK_2(WinScene::btnExitCalback, this));



	return true;
}

void WinScene::btnStartCalback(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{

	case Widget::TouchEventType::ENDED:
	{
		auto PlayScene = GameScene::createScene();
		auto Trans = TransitionFadeTR::create(1.0, PlayScene);
		Director::getInstance()->replaceScene(Trans);
		break;
	}
	default:
		break;
	}
}

void WinScene::btnExitCalback(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{

	case Widget::TouchEventType::ENDED:
	{
		auto PlayScene = MainScene::createScene();
		auto Trans = TransitionFadeTR::create(1.0, PlayScene);
		Director::getInstance()->replaceScene(Trans);
		break;
	}
	default:
		break;
	}
}
