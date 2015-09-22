#include "Tower.h"

USING_NS_CC;


Tower::Tower()
{
}


Tower::~Tower()
{
}

Tower::Tower(int type, int row, int col)
{
	this->trow = row;
	this->type = type;
	this->tcol = col;
	switch (type)
	{
	case 1:
	{
		this->attack = 50;
		this->price = 200;
		this->radius = 100;

	}
	}
}

bool Tower::init()
{
	if (!Node::init())
	{
		return false;
	}
	return true;
}

Tower * Tower::create(int type, int row, int col)
{
	Tower *pRet = new(std::nothrow) Tower(type, row, col);
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

Tower * Tower::createTower(int type, int row, int col)
{
	auto newTD = Tower::create(type, row, col);
	switch (type)
	{
	case 1:
	{
		auto spriteTD = Sprite::create();
		auto aniTower = Animation::create();
		for (int i = 0; i <= 4; i++)
		{
			char szName[100];
			sprintf(szName, "Thunder_Tower_%02d.png", i);
			aniTower->addSpriteFrameWithFile(szName);
		}
		//设置帧序列间隔
		aniTower->setDelayPerUnit(0.1);
		//创建帧动画
		auto ani = Animate::create(aniTower);
		auto repeatT= RepeatForever::create(ani);
		spriteTD->runAction(repeatT);
		newTD->addChild(spriteTD);
		newTD->setPosition(Vec2(row*56.9 + 28.45,(10- col)*56.9 + 28.45));
		break;
	}
	default:
		break;
	}
	return newTD;
}

void Tower::fire()
{
}
