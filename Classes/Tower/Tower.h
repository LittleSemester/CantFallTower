#ifndef __TOWER_H__
#define __TOWER_H__

#include <cocos2d.h>

class Tower:public cocos2d::Node
{
public:
	Tower();
	~Tower();
	Tower(int type, int row, int col);
	bool init();

	int tx, ty;//位置
	int trow, tcol;//所在行列
	int type;//塔的类型
	int price;//价格
	int attack;//攻击力
	int radius;//攻击范围



	CREATE_FUNC(Tower);

	static Tower* create(int type, int row, int col);

	static Tower* createTower(int type, int row, int col);

	void fire();
};

#endif