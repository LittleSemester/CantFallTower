#include "GameScene.h"
#include "Enemy\Enemy.h"
Vector<TDPoint*> GameScene::allPoint;//��������·��ת���

Scene * GameScene::createScene()
{
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//��ӱ���ͼƬ
	auto spriteBG = Sprite::create("Map_Ground_02.jpg");
	addChild(spriteBG);
	spriteBG->setPosition(Vec2(480, 320));

	//��ӵ�ͼ�ļ�
	auto Map = TMXTiledMap::create("map_0.tmx");
	addChild(Map);
	Map->setTag(0);//����ͼ�ļ�Tag����Ϊ0

	//���ص�������·����
	initAllPoints();
	//���õ�������
	EnemyCount = 20;
	//����һ�󲨹���
	schedule(schedule_selector(GameScene::EnemyCreat),1 );

	return true;
}


//���ص�������·����
void GameScene::initAllPoints()
{
	//�õ�tmx��ͼ
	TMXTiledMap* ourMap = (TMXTiledMap*)this->getChildByTag(0);
	auto Group = ourMap->getObjectGroup("Obj1");//��ȡ���������
	auto Objs = Group->getObjects();

	for (auto &eachObj : Objs)
	{
		ValueMap& dict = eachObj.asValueMap();
		float x = dict["x"].asFloat();
		float y = dict["y"].asFloat();
		//��������������ȡ������TDPoint
		TDPoint * newPoint = TDPoint::createPoint(x, y);
		//�������ɵ�TDPoint����ջ
		allPoint.pushBack(newPoint);
	}
}


void GameScene::EnemyCreat(float dt)
{
	if (CreatedEnemy < EnemyCount)
	{
		//�����ĵ���δ�ﵽ����������������
		CreatedEnemy++;
		auto newEnemy = Enemy::creatEnemy(1);
		addChild(newEnemy);
	}
	if (Enemy::nowCount == 0)
	{
		//�������Ĺ���ȫ���������ù�������
		CreatedEnemy = 0;
	}
}
