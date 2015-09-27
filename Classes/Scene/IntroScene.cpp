#include "IntroScene.h"
#include "MainScene.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;

IntroScene::IntroScene()
{
}


IntroScene::~IntroScene()
{
}

cocos2d::Scene * IntroScene::createScene()
{
	auto scene = Scene::create();

	auto layer = IntroScene::create();

	scene->addChild(layer);

	return scene;
}

bool IntroScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("MainScene.csb");

	addChild(rootNode);

	PageView* Intro = (PageView*)rootNode->getChildByName("introduce");

	Layout* panel = (Layout *)Intro->getChildByName("buff");

	Button* btn_Ret = (Button *)Helper::seekWidgetByName(panel, "Button_Ret");

	btn_Ret->addTouchEventListener(CC_CALLBACK_2(IntroScene::btnRetCalback, this));

	return true;
}

void IntroScene::btnRetCalback(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{

	case Widget::TouchEventType::ENDED:
	{
		auto nextScene = MainScene::createScene();
		//auto Trans = TransitionFadeTR::create(1.0, nextScene);
		Director::getInstance()->replaceScene(nextScene);
		break;
	}
	default:
		break;
	}
}
