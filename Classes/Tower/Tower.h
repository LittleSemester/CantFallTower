#ifndef __TOWER_H__
#define __TOWER_H__

#include <cocos2d.h>
#include "Enemy/Enemy.h"

enum TowerType
{
	TOWER_UNKNOWN,
	TOWER_ICE,
	TOWER_FIRE,
	TOWER_THUNDER,
	TOWER_KNIFE,
	TOWER_ARROW,
	TOWER_FIGHT
};

class Enemy;

class Tower : public cocos2d::Node
{
protected:

	int trow, tcol;//所在行列

	double attack;//攻击力
	double radius;//攻击范围
	double interval;//单次攻击时间

	TowerType type;//塔的类型

	cocos2d::Vector<Enemy*> enemyInRange;

	virtual void onFire() = 0;

	void doFire(float delta);

public:

	explicit Tower();
	virtual ~Tower()=0;

	virtual bool init();

	void setRowColumn(int row, int col);
	bool checkEnemyInRange(Enemy* enemy);

	static Tower* createTower(int type, int row, int col);

	void fire();

};

#endif