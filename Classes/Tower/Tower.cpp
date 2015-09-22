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
		auto spriteTD = Sprite::create("tower_1.png");
		newTD->addChild(spriteTD);
		newTD->setPosition(Vec2(row*58.9 + 24.5,(10- col)*58.9 + 24.5));
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
