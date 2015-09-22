#include <cmath>

#include "Enemy.h"
#include ".\Scene\GameScene.h"
using namespace cocos2d;

int Enemy::nowCount = 0;
//Vec2 Enemy::lastdir;
Enemy::Enemy()
{
}

Enemy::Enemy(int type)
{
	//设置怪物类型
	this->type = type;
	this->nextPoint = 1;
	this->changeDir = 0;
	this->lastdir.x = 1;
	this->finished = false;
	switch (type)
	{
	case 1:
		//初始化怪物属性
		/*this->nextPoint = 1;
		this->speed = 2;
		this->healthPoint = 100;
		this->changeDir = 0;
		this->lastdir.x = 1;*/
		this->speed = 2;
		this->healthPoint = 100;
		break;
	default:
		break;
	}
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
	return 100;
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

Enemy * Enemy::create(int type)
{
	Enemy *pRet = new(std::nothrow) Enemy(type);
		if (pRet && pRet->init())
		{
			pRet->autorelease();
			return pRet;
		}
		else
		{
			delete pRet;
			pRet = NULL;
			return NULL;
		}
}

Enemy * Enemy::createEnemy(int type)
{
	nowCount++;
	Enemy * newEnemy = Enemy::create(type);
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
		newEnemy->ActSprite= Sprite::create();
		newEnemy->ActSprite->runAction(RepeatWalk);
		newEnemy->addChild(newEnemy->ActSprite);
		
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
	if (this->isFinished())
	{
		return;
	}

	//获取当前敌人位置
	Vec2 nowPos = this->getPosition();
	//获取下一个点的位置
	TDPoint* nextTDP = GameScene::allPoint.at(nextPoint);
	Vec2 nextPos = Vec2(nextTDP->px, nextTDP->py);
	//计算出方向向量
	Vec2 dir = (nextPos - nowPos) / sqrt((nextPos.x - nowPos.x)*(nextPos.x - nowPos.x) + (nextPos.y - nowPos.y)*(nextPos.y - nowPos.y));
	//根据速度沿着该方向去行走一定距离
	this->setPosition(nowPos + dir*speed);
	//如果当前方向矢量x方向与上一次不同，则转向
	if (lastdir.x*dir.x < 0)
	{
		this->changeDir = 1 - this->changeDir;
		this->ActSprite->setFlippedX(this->changeDir);
	}
	//更新上一次方向向量
	lastdir = dir;
	//如果到达了下一个点
	if (sqrt((nextPos.x - nowPos.x)*(nextPos.x - nowPos.x) + (nextPos.y - nowPos.y)*(nextPos.y - nowPos.y)) < 3)
	{
		nextPoint++;
		//如果到达了终点
		if (nextPoint == GameScene::allPoint.size())
		{
			log("Escape successfully");
			//删除怪物
			this->removeFromParent();
			nowCount--;
			this->finished = true;
		}
	}
	

	//如果怪物死了
	if (this->isDead())
	{
		//先渐隐消失，再删除
		
		auto dead = FadeOut::create(0.3);
		auto deadFunc = CallFunc::create([this]() {this->removeFromParent(); });
		auto deadSeq = Sequence::create(dead, deadFunc, NULL);
		this->ActSprite->runAction(deadSeq);
		this->runAction(Sequence::create(DelayTime::create(0.3), deadFunc, NULL));
		nowCount--;
		this->finished = true;
	}
}

