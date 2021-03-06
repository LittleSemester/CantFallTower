#include "MainScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Enemy/TestEnemy.h"
#include "GameScene.h"
#include "IntroScene.h"
#include "audio/include/SimpleAudioEngine.h"

using namespace CocosDenshion;

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;


MainScene::MainScene()
{
	
}


MainScene::~MainScene()
{
}

cocos2d::Scene * MainScene::createScene()
{
	auto scene = Scene::create();

	auto layer = MainScene::create();

	scene->addChild(layer);

	return scene;
}

bool MainScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto backGround = Sprite::create("MainScreen_back.png");
	addChild(backGround);
	backGround->setPosition(Vec2(480, 320));

	Button * btn_Start = Button::create("MainScreen_start_button.png");
	btn_Start->setPosition(Vec2(480, 300));
	btn_Start->setScale(0.8);
	addChild(btn_Start);

	Button * btn_Intro = Button::create("MainScreen_intro_button.png");
	btn_Intro->setPosition(Vec2(480, 200));
	btn_Intro->setScale(0.8);
	addChild(btn_Intro);

	Button * btn_Exit = Button::create("MainScreen_exit_button.png");
	btn_Exit->setPosition(Vec2(480, 100));
	btn_Exit->setScale(0.8);
	addChild(btn_Exit);

	btn_Start->addTouchEventListener(CC_CALLBACK_2(MainScene::btnStartCalback, this));

	btn_Exit->addTouchEventListener(CC_CALLBACK_2(MainScene::btnExitCalback, this));

	btn_Intro->addTouchEventListener(CC_CALLBACK_2(MainScene::btnIntroCalback, this));

	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Bgm/title.mp3", true);

	return true;
}

void MainScene::btnStartCalback(Ref * pSender, Widget::TouchEventType type)
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

void MainScene::btnExitCalback(Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{

	case Widget::TouchEventType::ENDED:
	{
		Director::getInstance()->end();
		break;
	}
	default:
		break;
	}
}

void MainScene::btnIntroCalback(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{

	case Widget::TouchEventType::ENDED:
	{
		auto PlayScene = IntroScene::createScene();
		auto Trans = TransitionFadeTR::create(1.0, PlayScene);
		Director::getInstance()->replaceScene(Trans);
		break;
	}
	default:
		break;
	}
}
