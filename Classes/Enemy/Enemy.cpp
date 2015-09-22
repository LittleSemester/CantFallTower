#include <cmath>

#include "Enemy.h"
#include ".\Scene\GameScene.h"
using namespace cocos2d;

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
	Enemy * newEnemy = Enemy::create();
	//���ù�������
	newEnemy->type = type;
	//���ó�ʼ����λ��
	TDPoint * initPoint = (TDPoint *)GameScene::allPoint.at(0);
	newEnemy->setPosition(initPoint->px, initPoint->py);
	switch (type)
	{
		//���ݹ������Ͳ�����Ӧ�Ĺ���
	case 1://��һ�ֹ���
	{
		//�������߶���
		auto Walk = Animation::create();
		for (int i = 1; i <= 10; i++)
		{
			char szName[100];
			sprintf(szName, "gw%d.png", i);
			Walk->addSpriteFrameWithFile(szName);
		}
		//����֡���м��
		Walk->setDelayPerUnit(0.1);
		//����֡����
		auto AniWalk = Animate::create(Walk);
		auto RepeatWalk = RepeatForever::create(AniWalk);
		newEnemy->ActSprite= Sprite::create();
		newEnemy->ActSprite->runAction(RepeatWalk);

		newEnemy->addChild(newEnemy->ActSprite);
		newEnemy->ActSprite->retain();
		//��������������������Ŀǰ��δ֪����
		
		newEnemy->runAction(FadeIn::create(2.0));
		newEnemy->nextPoint = 1;
		newEnemy->speed = 2;
		newEnemy->healthPoint = 100;
		newEnemy->changeDir = 0;
		newEnemy->lastdir.x = 1;
	}
	default:
		break;
	}
	//�øõ���ִ���ƶ��Ļص�����
	newEnemy->schedule(schedule_selector(Enemy::EnemyMove, 1.0 / 60));

	return newEnemy;
}

//�����ƶ��ص�����
void Enemy::EnemyMove(float dt)
{
	//��ȡ��ǰ����λ��
	Vec2 nowPos = this->getPosition();
	//��ȡ��һ�����λ��
	TDPoint* nextTDP = GameScene::allPoint.at(nextPoint);
	Vec2 nextPos = Vec2(nextTDP->px, nextTDP->py);
	//�������������
	Vec2 dir = (nextPos - nowPos) / sqrt((nextPos.x - nowPos.x)*(nextPos.x - nowPos.x) + (nextPos.y - nowPos.y)*(nextPos.y - nowPos.y));
	//�����ٶ����Ÿ÷���ȥ����һ������
	this->setPosition(nowPos + dir*speed);
	//�����ǰ����ʸ��x��������һ�β�ͬ����ת��
	if (lastdir.x*dir.x < 0)
	{
		this->changeDir = 1 - this->changeDir;
		this->ActSprite->setFlippedX(this->changeDir);
	}
	//������һ�η�������
	lastdir = dir;
	//�����������һ����
	if (sqrt((nextPos.x - nowPos.x)*(nextPos.x - nowPos.x) + (nextPos.y - nowPos.y)*(nextPos.y - nowPos.y)) < 3)
	{
		nextPoint++;
	}
	//����������յ�
	if (nextPoint == GameScene::allPoint.size())
	{
		log("Escape successfully");
		//ɾ������
		this->ActSprite->release();
		this->removeFromParent();
	}

	//�����������
	if (this->healthPoint <= 0)
	{
		//�Ƚ�����ʧ����ɾ��
		auto dead = FadeOut::create(1.0);
		auto deadFunc = CallFunc::create([this]() {this->removeFromParent(); });
		auto deadSeq = Sequence::create(dead, deadFunc, NULL);
		this->ActSprite->release();
		this->runAction(deadSeq);
	}
}

