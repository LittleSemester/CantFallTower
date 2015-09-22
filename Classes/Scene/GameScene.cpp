#include "GameScene.h"
#include "Enemy\Enemy.h"
#include "Tower\Tower.h"

USING_NS_CC;

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
	//��ʼ��������Ϣ
	memset(towerInfo, 0, sizeof(towerInfo));

	//���õ�������
	EnemyCount = 20;
	//����һ�󲨹���
	schedule(schedule_selector(GameScene::EnemyCreat),1 );

	//���봥������
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
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
		auto newEnemy = Enemy::createEnemy(1);
		addChild(newEnemy);
	}
	if (Enemy::nowCount == 0)
	{
		//�������Ĺ���ȫ���������ù�������
		CreatedEnemy = 0;
	}
}

//�����¼�
bool GameScene::onTouchBegan(Touch * touch, Event * unused_event)
{
	//�Ƴ��������
	if (this->getChildByTag(100) != nullptr)
	{
		this->removeChildByTag(100);
	}

	Vec2 now = touch->getLocation();
	log("touch %f %f", now.x, now.y);
	TMXTiledMap * ourMap = (TMXTiledMap*)this->getChildByTag(0);
	//rowΪ�����꣬colΪ������
	this->nowRow = (int)(now.x / 56.9);
	this->nowCol = 10-(int)(now.y / 56.9);
	log("%d %d", nowRow, nowCol);
	//��ȡ�����id
	int touchID = ourMap->getLayer("Layer1")->getTileGIDAt(Vec2(nowRow, nowCol));
	log("touch ID %d", touchID);
	//��ʼ���ɷ������
	bool canTouch = false;
	//���ÿ��Ƿ���Խ���
	if (!ourMap->getPropertiesForGID(touchID).isNull())
	{
		auto tileTemp = ourMap->getPropertiesForGID(touchID).asValueMap();
		if (!tileTemp.empty())
		{
			canTouch = true;
			log("canTouch");
		}
	}

	if (canTouch)
	{
		//���Խ���������ѡ�����
		if(towerInfo[nowCol][nowRow])
		{
			//����Ѿ�����������������
		}
		else
		{
			addTDSelect(nowRow, 10 - nowCol);
		}
	}
	else
	{
		//���ɽ���������������ʾ
		auto tips = Sprite::create("notips.png");
		tips->setPosition(Vec2(nowRow * 56.9+28.45, (10 - nowCol) * 56.9+28.45));
		this->addChild(tips);
		tips->runAction(
			Sequence::create(
				DelayTime::create(0.8),
				CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, tips)), NULL));
	}
	return true;
}

void GameScene::onTouchMoved(Touch * touch, Event * unused_event)
{
}

void GameScene::onTouchEnded(Touch * touch, Event * unused_event)
{
}

//����ѡ��
void GameScene::addTDSelect(int r, int c)
{
	//��������ʾͼƬ����ע
	auto tPos = Sprite::create("notips.png");
	Vec2 Size = tPos->getContentSize();
	//�������Ϸ���ʾҪ�����
	//���ð�ťδѡ���ѡ���ͼƬ
	auto bt01 = Sprite::create("tower_1.png");
	auto bt01_sel = Sprite::create("tower_1.png");
	bt01_sel->setScale(1.1);
	//����spriteתΪMenu�����û��¼�
	auto menuItem01 = MenuItemSprite::create(bt01, bt01_sel, CC_CALLBACK_1(GameScene::selectTD, this));
	menuItem01->setTag(10);
	menuItem01->setAnchorPoint(Vec2(0.5, 0));
	//��menu����menuItem
	auto menuTD = Menu::create(menuItem01, nullptr);
	
	menuTD->setPosition(Vec2::ZERO);
	tPos->addChild(menuTD);

	menuItem01->setPosition(Vec2(Size.x / 2, Size.y));

	tPos->setTag(100);
	this->addChild(tPos);

	tPos->setPosition(r*58.9 + 24.5, c*58.9 + 24.5);
}

void GameScene::selectTD(Ref * obj)
{
	auto item = (MenuItemSprite *)obj;
	switch (item->getTag())
	{
	case 10:
	{
		Tower * TD = Tower::createTower(1, nowRow, nowCol);
		this->addChild(TD);
		//��Ǹ�λ���Ѿ�����
		towerInfo[nowCol][nowRow] = true;
	}
	default:
		break;
	}
	//�Ƴ��������
	if (this->getChildByTag(100) != nullptr)
	{
		this->removeChildByTag(100);
	}
}
