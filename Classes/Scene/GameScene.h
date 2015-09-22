#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__
#include <cocos2d.h>
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Scene\TDPoint.h"



using namespace cocostudio::timeline;
class GameScene:public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	
	virtual bool init();

	CREATE_FUNC(GameScene);

	static cocos2d::Vector<TDPoint*> allPoint;//保存所有路径转弯点

	int EnemyCount;//敌人数量
	int CreatedEnemy = 0;//已产生的怪物
	
	void EnemyCreat(float dt);//产生一波怪物

	void initAllPoints();//加载敌人行走路径点

	void addTDSelect(int r, int c);//添加塔的选择面板

	void selectTD(cocos2d::Ref* obj);//建塔的回调

	int nowRow, nowCol;//点击处的行列信息，供造塔过程使用

	int towerInfo[11][17];//建塔信息,行列信息完全和二维数组相同，左上角为原点，屏幕原点,11行，17列

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
};

#endif