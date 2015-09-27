#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <cocos2d.h>
#include <math\CCGeometry.h>
#include "ui/UILoadingBar.h"

#include "buff/BuffList.h"

class Enemy : public cocos2d::Node, public BuffList
{
protected:

	int healthPoint;
	double speed;//怪物速度
	
	double height;

	float distance;//已走过的路
	bool finished;//是否正在播放死亡动画或正在删除该Enemy

	int nextPoint; //下一个移动目标点
	int changeDir; //改变方向
	cocos2d::ui::LoadingBar* hpBar;
	cocos2d::Vec2 lastdir;//上次移动方向

	cocos2d::Sprite* actSprite;//建立一个成员变量精灵承载行走动画

	virtual void updateBuffState();

	virtual void onBuffBegin(Buff* buff);
	virtual void onBuffEnd(Buff* buff);

	static double calcDefencedDamage(double damage, double defence);

public:

	explicit Enemy();
	virtual ~Enemy()=0;

	virtual bool init();

	virtual void update(float delta);

	virtual int maxHP();
	virtual int defence();
	virtual int reward();

	// 对该敌人造成伤害，期间检查敌人各项属性和buff，指定direct=true造成直伤；返回最终伤害量
	virtual int dealDamage(double damage, bool direct=false);
	virtual void dealCure(double cure);

	inline int getHP() const
	{
		return healthPoint;
	}

	//判断是否死亡
	inline bool isDead() const
	{
		return healthPoint <= 0;
	}

	inline bool isFinished() const
	{
		return finished;
	}

	inline float getDistance() const
	{
		return this->distance;
	}

private:

	//敌人移动回调函数
	void moveEnemy(float dt);

	//治疗回调函数
	void cureEnemy(float dt);

};

#endif // _ENEMY_H_
