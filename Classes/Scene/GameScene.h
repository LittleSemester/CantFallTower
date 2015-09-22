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

	static Vector<TDPoint*> allPoint;//��������·��ת���

	int EnemyCount;//��������
	int CreatedEnemy = 0;//�Ѳ����Ĺ���
	
	void EnemyCreat(float dt);//����һ������

	void initAllPoints();//���ص�������·����
};

#endif