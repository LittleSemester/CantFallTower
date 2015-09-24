#include <cmath>

#include "Enemy.h"
#include "Scene/GameScene.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
using namespace cocos2d;

Enemy::Enemy()
{
	this->nextPoint = 1;
	this->changeDir = 0;
	this->lastdir.x = 1;
	this->finished = false;
	this->distance = 0;
}

Enemy::~Enemy()
{

}

bool Enemy::init()
{
	if (!Node::init())
		return false;

	TDPoint * initPoint = (TDPoint *)GameScene::allPoint.at(0);
	setPosition(initPoint->px, initPoint->py);
	
	//����Ѫ��
	hpBar = LoadingBar::create("loadingBar.png");
	hpBar->setTag(123);
	hpBar->setPercent(100);
	addChild(hpBar, 1);
	hpBar->setPositionY(30);

	actSprite = nullptr;

	healthPoint = maxHP();

	scheduleUpdate();

	return true;
}

void Enemy::update(float delta)
{
	moveEnemy(delta);
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

	hpBar->setPercent(100.0 * healthPoint / maxHP());

	return finalDamage;
}



double Enemy::calcDefencedDamage(double damage, double defence)
{
	return damage > defence ? damage - defence : 0.0;
}

//怪物移动回调函数
void Enemy::moveEnemy(float dt)
{
	if (this->isFinished())
		return;

	double buffedSpeed = calcBuffedValue(&Buff::speed, speed);

	//��ȡ��ǰ����λ��
	Vec2 nowPos = this->getPosition();
	//获取下一个点的位�?
	TDPoint* nextTDP = GameScene::allPoint.at(nextPoint);
	Vec2 nextPos = Vec2(nextTDP->px, nextTDP->py);
	//计算出方向向�?
	Vec2 dir = (nextPos - nowPos) / sqrt((nextPos.x - nowPos.x)*(nextPos.x - nowPos.x) + (nextPos.y - nowPos.y)*(nextPos.y - nowPos.y));
	//根据速度沿着该方向去行走一定距�?
	this->setPosition(nowPos + dir*buffedSpeed);
	this->distance += buffedSpeed;
	//如果当前方向矢量x方向与上一次不同，则转�?
	if (lastdir.x*dir.x < 0)
	{
		this->changeDir = 1 - this->changeDir;
		if (actSprite!=nullptr)
			this->actSprite->setFlippedX(this->changeDir);
	}
	//更新上一次方向向�?
	lastdir = dir;
	//如果到达了下一个点
	if (sqrt((nextPos.x - nowPos.x)*(nextPos.x - nowPos.x) + (nextPos.y - nowPos.y)*(nextPos.y - nowPos.y)) < 3)
	{
		nextPoint++;
		//���ٱ���
		//this->ActSprite->setColor(Color3B(74, 177, 250));
		//����������յ�
		if (nextPoint == GameScene::allPoint.size())
		{
			log("Escape successfully");
			//ɾ������
			this->removeFromParent();
			this->finished = true;
		}
	}

	//�����������
	if (this->isDead())
	{
		//�Ƚ�����ʧ����ɾ��
		auto dead = FadeOut::create(0.3);
		auto deadFunc = CallFunc::create([this]() {this->removeFromParent(); });
		auto deadSeq = Sequence::create(dead, deadFunc, NULL);
		this->actSprite->runAction(deadSeq);
		this->runAction(Sequence::create(DelayTime::create(0.3), deadFunc, NULL));
		this->finished = true;
	}
}

