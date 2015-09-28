// 编码：Utf-8 without BOM
// Created by LuiCat

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "2d/CCNode.h"
#include "Enemy/Enemy.h"
#include "Scene/GameScene.h"

// 注解：mainScene中不保存Entity列表，Entity在update时自行判断判定时机，需要清除自身时需调用removeFromParant自我清除
// Entity必须为GameScene的child以便获取GameScene进行判定相关操作，否则Entity将清楚自身
// Missile和AOEArea是分开的两个工厂，其他类型自成体系

class GameScene;

class Entity : public cocos2d::Node
{
protected:

	double baseDamage;
	GameScene* mainScene;

	void acquireJudge(Enemy* enemy=nullptr); // 向mainScene申请用自身判定敌人

public:

	explicit Entity();
	virtual ~Entity();

	virtual bool init();

	inline double getBaseDamage() const
	{
		return baseDamage;
	}

	virtual void onEnter() override;

	virtual bool judgeSingleEnemy(Enemy* enemy) = 0;

	//设置子弹伤害
	virtual void setBaseDamage(int damage);
};



#endif // _ENTITY_H_


