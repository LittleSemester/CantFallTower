#ifndef __TOWER_H__
#define __TOWER_H__

#include <cocos2d.h>
#include "Enemy/Enemy.h"
#include "Scene/GameScene.h"

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
class GameScene;

class Tower : public cocos2d::Node, public BuffList
{
protected:

	int trow, tcol;//所在行列

	double attack;//攻击力
	double radius;//攻击范围
	double interval;//单次攻击时间

	TowerType type;//塔的类型

	int currLevel;

	GameScene* mainScene;

	cocos2d::Vector<Enemy*> enemyInRange;

	virtual void onFire() = 0;

	void doFire(float delta);

	virtual void onBuffBegin(Buff* buff);
	virtual void onBuffEnd(Buff* buff);

	// 重载这个函数以自定义改变级别时的变动
	virtual bool onChangeLevel(int level);

public:

	explicit Tower();
	virtual ~Tower()=0;

	virtual bool init();
	virtual void onEnter();

	void setRowColumn(int row, int col);

	// 重载这个函数以控制建塔或升级塔需要的金币，默认参数level=1表示建塔的费用，其余表示升塔的费用
	virtual int getMoney(int level = 1);
	// 升级塔，onChangeLevel返回false时函数将返回false，表示升级失败或者到达顶级
	bool upgrate();

	static Tower* createTower(int type, int row, int col);

	void fire();

};

#endif