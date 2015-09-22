#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <cocos2d.h>
#include <math\CCGeometry.h>

#include "buff/BuffList.h"

class Enemy : public cocos2d::Node, public BuffList
{
protected:

	int healthPoint;
	int type;//怪物类型
	double speed;//怪物速度
	int nextPoint;//下一个移动目标点
	cocos2d::Sprite* ActSprite;//建立一个成员变量精灵承载行走动画
	cocos2d::Vec2 lastdir;//上次移动方向
	int changeDir;//改变方向
	bool finished;//是否正在播放死亡动画或正在删除该Enemy
	static double calcDefencedDamage(double damage, double defence);

public:

	explicit Enemy();
	//带参数的构造函数，初始化对应的怪物
	explicit Enemy(int type);
	virtual ~Enemy();

	virtual bool init();

	virtual void update(float delta);

	int maxHP();
	virtual int defence();

	// 对该敌人造成伤害，期间检查敌人各项属性和buff，指定direct=true造成直伤；返回最终伤害量
	virtual int dealDamage(double damage, bool direct=false);

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


	CREATE_FUNC(Enemy);

	//带参数的create函数,对应怪物类型
	static Enemy* create(int type);

	static int nowCount;//当前敌人数量


	//生成敌人
	static Enemy* createEnemy(int type);

	//敌人移动回调函数
	void EnemyMove(float dt);


};

#endif // _ENEMY_H_
