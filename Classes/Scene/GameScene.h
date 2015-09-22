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

	static cocos2d::Vector<TDPoint*> allPoint;//��������·��ת���

	int EnemyCount;//��������
	int CreatedEnemy = 0;//�Ѳ����Ĺ���
	
	void EnemyCreat(float dt);//����һ������

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