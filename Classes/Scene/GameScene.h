#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include <cocos2d.h>
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Util/TDPoint.h"
#include "Entity/Entity.h"
#include "Enemy/Enemy.h"


class Enemy;
class Entity;

using namespace cocostudio::timeline;
class GameScene:public cocos2d::Layer
{
protected:

	cocos2d::Vector<Enemy*> enemyList;

	void clearRemovedEnemyFromList();

public:

	static cocos2d::Scene* createScene();
	
	virtual bool init();

	CREATE_FUNC(GameScene);

	static cocos2d::Vector<TDPoint*> allPoint;//��������·��ת���

	int enemyMaxCount; //敌人最大数�?
	int enemyCreated;
	
	void EnemyCreat(float dt);//产生一波怪物

	// 用于单一Entity进行判定检测，一般情况下由Entity自身调用，指定singleEnemy以判定单个目标（会检查目标有效性）
	void judgeEntityBounding(Entity* entity, Enemy* singleEnemy = nullptr);

	void initAllPoints();//���ص�������·����

	void addTDSelect(int r, int c);//�������ѡ�����

	void selectTD(cocos2d::Ref* obj);//�����Ļص�

	int nowRow, nowCol;//�������������Ϣ������������ʹ��

	int towerInfo[11][17];//������Ϣ,������Ϣ��ȫ�Ͷ�ά������ͬ�����Ͻ�Ϊԭ�㣬��Ļԭ��,11�У�17��

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

};

#endif