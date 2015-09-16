// 编码：Utf-8 without BOM
// Created by LuiCat

#include "2d\CCDrawNode.h"
#include "TestEnemy.h"
#include "ui\UITextAtlas.h"

USING_NS_CC;

TestEnemy::TestEnemy()
{

}

TestEnemy::~TestEnemy()
{

}


int TestEnemy::maxHP()
{
	return 100;
}

int TestEnemy::defence()
{
	return 10;
}

int TestEnemy::dealDamage(double damage, bool direct /*= false*/)
{
	int res = Enemy::dealDamage(damage, direct);
	char str[210];
	sprintf(str, "def10,200%%\nhp:%d/%d\n%.1lf,-%d", healthPoint, maxHP(), damage, res);
	text->setString(str);
	return res;
}

bool TestEnemy::init()
{
	if (!Enemy::init())
		return false;

	setAnchorPoint(Vec2(0.5, 0.5));

	auto draw = DrawNode::create();
	addChild(draw);

	draw->drawRect(Vec2(-40, -40), Vec2(40, 40), Color4F(1.0, 1.0, 1.0, 1.0));

	text = ui::TextAtlas::create();
	addChild(text);

	text->setAnchorPoint(Vec2(0.5, 0.5));
	text->setPosition(Vec2(0, 0));
	text->setString("Fxxk\nYeah");

	auto td = EventListenerTouchOneByOne::create();
	td->onTouchBegan = [this](Touch* touch, Event* event)
	{
		this->dealDamage(rand() % 20);
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(td, draw);

	this->newBuff<SimpleBuff>(10.0, 1.0, 1.0, 2.0, 1.0);

	return true;
}
