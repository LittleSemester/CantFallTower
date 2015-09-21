#include <cmath>

#include "Enemy.h"
#include ".\Scene\GameScene.h"
using namespace cocos2d;

int Enemy::nowCount = 0;
//Vec2 Enemy::lastdir;
Enemy::Enemy()
{

}

Enemy::~Enemy()
{

}

bool Enemy::init()
{
	if (!Node::init())
	{
		return false;
	}
	healthPoint = maxHP();
	return true;
}

void Enemy::update(float delta)
{
	updateBuff(delta);
}

int Enemy::maxHP()
{
	return 0;
}

int Enemy::defence()
{
	return 0;
}

int Enemy::dealDamage(double damage, bool direct/*=false*/)
{
	if (!direct)
	{
		double bufDef = calcBuffedValue(&Buff::defence, defence());
		damage = calcDefencedDamage(damage, bufDef);
		damage = calcBuffedValue(&Buff::damageIn, damage);
	}

	int finalDamage = (int)round(damage);
	if (finalDamage < 1)
		finalDamage = 1;

	healthPoint -= finalDamage;
	if (healthPoint < 0)
		healthPoint = 0;

	return finalDamage;
}



double Enemy::calcDefencedDamage(double damage, double defence)
{
	return damage > defence ? damage - defence : 0.0;
}

Enemy * Enemy::creatEnemy(int type)
{
	nowCount++;
	Enemy * newEnemy = Enemy::create();
	//设置怪物类型
	newEnemy->type = type;
	//设置初始出现位置
	TDPoint * initPoint = (TDPoint *)GameScene::allPoint.at(0);
	newEnemy->setPosition(initPoint->px, initPoint->py);
	switch (type)
	{
		//根据怪物类型产生对应的怪物
	case 1://第一种怪物
	{
		//怪物行走动画
		auto Walk = Animation::create();
		for (int i = 1; i <= 10; i++)
		{
			char szName[100];
			sprintf(szName, "gw%d.png", i);
			Walk->addSpriteFrameWithFile(szName);
		}
		//设置帧序列间隔
		Walk->setDelayPerUnit(0.1);
		//创建帧动画
		auto AniWalk = Animate::create(Walk);
		auto RepeatWalk = RepeatForever::create(AniWalk);
		auto newSprite = Sprite::create();
		newSprite->runAction(RepeatWalk);
		newEnemy->addChild(newSprite);

		//上述动画纹理设置有误，目前有未知错误
		
		newEnemy->runAction(FadeIn::create(2.0));
		newEnemy->nextPoint = 1;
		newEnemy->speed = 2;
		newEnemy->healthPoint = 100;
	}
	default:
		break;
	}
	//让该敌人执行移动的回调函数
	newEnemy->schedule(schedule_selector(Enemy::EnemyMove, 1.0 / 60));

	return newEnemy;
}

//怪物移动回调函数
void Enemy::EnemyMove(float dt)
{
	//获取当前敌人位置
	Vec2 nowPos = this->getPosition();
	//获取下一个点的位置
	TDPoint* nextTDP = GameScene::allPoint.at(nextPoint);
	Vec2 nextPos = Vec2(nextTDP->px, nextTDP->py);
	//计算出方向向量
	Vec2 dir = (nextPos - nowPos) / sqrt((nextPos.x - nowPos.x)*(nextPos.x - nowPos.x) + (nextPos.y - nowPos.y)*(nextPos.y - nowPos.y));
	this->setPosition(nowPos + dir*speed);

	//如果到达了下一个点
	if (sqrt((nextPos.x - nowPos.x)*(nextPos.x - nowPos.x) + (nextPos.y - nowPos.y)*(nextPos.y - nowPos.y)) < 5)
	{
		nextPoint++;
	}
	//如果到达了终点
	if (nextPoint == GameScene::allPoint.size())
	{
		log("Escape successfully");
		//删除怪物
		this->removeFromParent();
		nowCount--;
	}

	//如果怪物死了
	if (this->healthPoint <= 0)
	{
		//先渐隐消失，再删除
		auto dead = FadeOut::create(1.0);
		auto deadFunc = CallFunc::create([this]() {this->removeFromParent(); });
		auto deadSeq = Sequence::create(dead, deadFunc, NULL);
		this->runAction(deadSeq);
		nowCount--;
	}
}

