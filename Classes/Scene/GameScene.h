#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__
#include <cocos2d.h>
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Util/TDPoint.h"

USING_NS_CC;

using namespace cocostudio::timeline;
class GameScene:public Layer
{
public:
	static Scene* createScene();
	
	virtual bool init();

	CREATE_FUNC(GameScene);

	static Vector<TDPoint*> allPoint;//保存所有路径转弯点

	int EnemyCount;//敌人数量
	int CreatedEnemy = 0;//已产生的怪物
	
	void EnemyCreat(float dt);//产生一波怪物

	void initAllPoints();//加载敌人行走路径点
};

#endif