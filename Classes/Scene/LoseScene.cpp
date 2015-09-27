#include "LoseScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Enemy/TestEnemy.h"
#include "GameScene.h"
#include "MainScene.h"
USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;


LoseScene::LoseScene()
{
}


LoseScene::~LoseScene()
{
}

cocos2d::Scene * LoseScene::createScene()
{
	auto scene = Scene::create();

	auto layer = LoseScene::create();

	scene->addChild(layer);

	return scene;
}

bool LoseScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto backGround = Sprite::create("GameScreen_youlose.png");
	backGround->setPosition(Vec2(480, 320));
	addChild(backGround);

	Button * btn_Again = Button::create("GameScreen_lose_tryagain.png");
	btn_Again->setPosition(Vec2(350, 250));
	addChild(btn_Again);
	btn_Again->addTouchEventListener(CC_CALLBACK_2(LoseScene::btnAgainCalback, this));

	Button * btn_Return = Button::create("GameScreen_backmenu.png");
	btn_Return->setPosition(Vec2(600, 250));
	addChild(btn_Return);
	btn_Return->addTouchEventListener(CC_CALLBACK_2(LoseScene::btnReturnCalback, this));



	return true;
}

void LoseScene::btnAgainCalback(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{

	case Widget::TouchEventType::ENDED:
	{
		auto PlayScene = GameScene::createScene();
		auto Trans = TransitionFadeBL::create(1.0, PlayScene);
		Director::getInstance()->replaceScene(Trans);
		break;
	}
	default:
		break;
	}
}

void LoseScene::btnReturnCalback(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{

	case Widget::TouchEventType::ENDED:
	{
		auto PlayScene = MainScene::createScene();
		auto Trans = TransitionFadeBL::create(1.0, PlayScene);
		Director::getInstance()->replaceScene(Trans);
		break;
	}
	default:
		break;
	}
}
