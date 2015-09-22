#include "GameScene.h"
#include "Enemy\Enemy.h"
#include "Tower\Tower.h"

USING_NS_CC;

Vector<TDPoint*> GameScene::allPoint;//保存所有路径转弯点

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
	//添加背景图片
	auto spriteBG = Sprite::create("Map_Ground_02.jpg");
	addChild(spriteBG);
	spriteBG->setPosition(Vec2(480, 320));

	//添加地图文件
	auto Map = TMXTiledMap::create("map_0.tmx");
	addChild(Map);
	Map->setTag(0);//将地图文件Tag设置为0

	//加载敌人行走路径点
	initAllPoints();
	//初始化建塔信息
	memset(towerInfo, 0, sizeof(towerInfo));

	//设置敌人数量
	EnemyCount = 20;
	//产生一大波怪物
	schedule(schedule_selector(GameScene::EnemyCreat),1 );

	//加入触摸处理
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}


//加载敌人行走路径点
void GameScene::initAllPoints()
{
	//得到tmx地图
	TMXTiledMap* ourMap = (TMXTiledMap*)this->getChildByTag(0);
	auto Group = ourMap->getObjectGroup("Obj1");//获取对象层数据
	auto Objs = Group->getObjects();

	for (auto &eachObj : Objs)
	{
		ValueMap& dict = eachObj.asValueMap();
		float x = dict["x"].asFloat();
		float y = dict["y"].asFloat();
		//将各个点数据提取并生成TDPoint
		TDPoint * newPoint = TDPoint::createPoint(x, y);
		//将新生成的TDPoint加入栈
		allPoint.pushBack(newPoint);
	}
}


void GameScene::EnemyCreat(float dt)
{
	if (CreatedEnemy < EnemyCount)
	{
		//产生的敌人未达到最大数量则继续产生
		CreatedEnemy++;
		auto newEnemy = Enemy::createEnemy(1);
		addChild(newEnemy);
	}
	if (Enemy::nowCount == 0)
	{
		//当产生的怪物全被消灭重置怪物生成
		CreatedEnemy = 0;
	}
}

//触摸事件
bool GameScene::onTouchBegan(Touch * touch, Event * unused_event)
{
	//移除建塔面板
	if (this->getChildByTag(100) != nullptr)
	{
		this->removeChildByTag(100);
	}

	Vec2 now = touch->getLocation();
	log("touch %f %f", now.x, now.y);
	TMXTiledMap * ourMap = (TMXTiledMap*)this->getChildByTag(0);
	//row为横坐标，col为纵坐标
	this->nowRow = (int)(now.x / 56.9);
	this->nowCol = 10-(int)(now.y / 56.9);
	log("%d %d", nowRow, nowCol);
	//获取点击块id
	int touchID = ourMap->getLayer("Layer1")->getTileGIDAt(Vec2(nowRow, nowCol));
	log("touch ID %d", touchID);
	//初始化可放塔标记
	bool canTouch = false;
	//检查该块是否可以建塔
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
		//可以建塔，弹出选择面板
		if(towerInfo[nowCol][nowRow])
		{
			//如果已经有塔，变卖或升级
		}
		else
		{
			addTDSelect(nowRow, 10 - nowCol);
		}
	}
	else
	{
		//不可建塔，弹出错误提示
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

//塔的选择
void GameScene::addTDSelect(int r, int c)
{
	//造塔点显示图片做标注
	auto tPos = Sprite::create("notips.png");
	Vec2 Size = tPos->getContentSize();
	//造塔点上方显示要造的塔
	//设置按钮未选择和选择的图片
	auto bt01 = Sprite::create("tower_1.png");
	auto bt01_sel = Sprite::create("tower_1.png");
	bt01_sel->setScale(1.1);
	//将该sprite转为Menu接收用户事件
	auto menuItem01 = MenuItemSprite::create(bt01, bt01_sel, CC_CALLBACK_1(GameScene::selectTD, this));
	menuItem01->setTag(10);
	menuItem01->setAnchorPoint(Vec2(0.5, 0));
	//用menu容纳menuItem
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
		//标记该位置已经建塔
		towerInfo[nowCol][nowRow] = true;
	}
	default:
		break;
	}
	//移除建塔面板
	if (this->getChildByTag(100) != nullptr)
	{
		this->removeChildByTag(100);
	}
}
