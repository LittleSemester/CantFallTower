#include "GameScene.h"
#include "Enemy/SimpleEnemy.h"
#include "Tower/Tower.h"
#include "Skill/Hurricane.h"
#include "Skill/FastFreeze.h"
#include "Skill/ShakingWave.h"
USING_NS_CC;
using namespace cocos2d::ui;

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

GameScene::~GameScene()
{
	delete stageLoader;
	stageLoader = nullptr;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	stageLoader = new StageLoader("stagemap.plist");

	//娣诲姞鑳屾櫙鍥剧墖
	auto spriteBG = Sprite::create(stageLoader->getBackGroundFileName());
	addChild(spriteBG);
	spriteBG->setPosition(Vec2(480, 320));

	//娣诲姞鍦板浘鏂囦欢
	auto Map = TMXTiledMap::create(stageLoader->getTileMapFileName());
	addChild(Map);
	Map->setTag(0);//灏嗗湴鍥炬枃浠禩ag璁剧疆涓?

	//鍔犺浇鏁屼汉琛岃蛋璺緞鐐?
	initAllPoints();
	//初始化建塔信息
	memset(towerInfo, 0, sizeof(towerInfo));

	schedule(CC_SCHEDULE_SELECTOR(GameScene::tryCreateEnemy), stageLoader->getEnemySpawnDelay());

	//加载纹理到内存中
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Ice_picture.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Ice_Attack.plist");

	//加入触摸处理
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
	currSkill = nullptr;
	selectedSkill = -1;//初始化已选中技能
	/*
	currSkill = Hurricane::create();
	currSkill->setPositionZ(10);
	addChild(currSkill);*/

	loadSkillPattern();
	loadStatus();

	this->ourHealth = 20;
	this->money = 400;
	this->nowWave = 1;

	this->currentWaveFinished = false;


	return true;
}


//鍔犺浇鏁屼汉琛岃蛋璺緞鐐?
void GameScene::initAllPoints()
{
	//寰楀埌tmx鍦板浘
	TMXTiledMap* ourMap = (TMXTiledMap*)this->getChildByTag(0);
	auto Group = ourMap->getObjectGroup("Obj1");//鑾峰彇瀵硅薄灞傛暟鎹?
	auto Objs = Group->getObjects();

	for (auto &eachObj : Objs)
	{
		ValueMap& dict = eachObj.asValueMap();
		float x = dict["x"].asFloat();
		float y = dict["y"].asFloat();
		//灏嗗悇涓偣鏁版嵁鎻愬彇骞剁敓鎴怲DPoint
		TDPoint * newPoint = TDPoint::createPoint(x, y);
		//灏嗘柊鐢熸垚鐨凾DPoint鍔犲叆鏍?
		allPoint.pushBack(newPoint);
	}
}


void GameScene::tryCreateEnemy(float dt)
{
	if (currentWaveFinished) // 所有的怪都已经出场，判断怪物是否全清
	{
		clearRemovedEnemyFromList();
		if (enemyList.size() == 0)
		{
			if (stageLoader->toggleNextWave())
			{
				// 进入下一波
				currentWaveFinished = false;
				schedule(CC_SCHEDULE_SELECTOR(GameScene::tryCreateEnemy), stageLoader->getEnemySpawnDelay());
			}
			else
			{
				unschedule(CC_SCHEDULE_SELECTOR(GameScene::tryCreateEnemy));
				// todo: 关卡结束
			}
		}
	}
	else
	{
		auto newEnemy = stageLoader->createNextEnemy();
		if (newEnemy == nullptr) // 本波结束
			currentWaveFinished = true;
		else // 产生的敌人未达到最大数量
		{
			addChild(newEnemy);
			enemyList.pushBack(newEnemy);
		}
	}
}

void GameScene::judgeEntityBounding(Entity* entity, Enemy* singleEnemy)
{
	clearRemovedEnemyFromList();

	if (singleEnemy!=nullptr)
	{
		if (singleEnemy->isDead() || !enemyList.contains(singleEnemy))
			return;
		entity->judgeSingleEnemy(singleEnemy);
		return;
	}

	for (Enemy* enemy : enemyList)
	{
		entity->judgeSingleEnemy(enemy);
	}

}

void GameScene::clearRemovedEnemyFromList()
{
	for (auto iter = enemyList.begin(); iter != enemyList.end();)
	{
		if ((*iter)->getParent()==nullptr)
		{
			iter = enemyList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

int GameScene::getEnemyInDistance(Vector<Enemy*>& list, const Vec2& pos, double dist)
{
	int res = 0;
	clearRemovedEnemyFromList();
	for (Enemy* enemy : enemyList)
	{
		if (enemy->isDead())
			continue;
		if (enemy->getPosition().distance(pos) <= dist && !list.contains(enemy))
		{
			list.pushBack(enemy);
			++res;
		}
	}
	return res;
}

Enemy* GameScene::getNearestEnemy(const Vec2& pos, double dist/*=INFINITY*/)
{
	clearRemovedEnemyFromList();
	Enemy* result = nullptr;
	float t;
	for (Enemy* enemy : enemyList)
	{
		if (enemy->isDead())
			continue;
		t = enemy->getPosition().distance(pos);
		if (t <= dist)
		{
			result = enemy;
			dist = t;
		}
	}
	return result;
}

int GameScene::getEnemyInArea(cocos2d::Vector<Enemy*>& list, const std::function<bool(const cocos2d::Vec2&)> inArea)
{
	int res = 0;
	for (Enemy* enemy : enemyList)
	{
		if (enemy->isDead())
			continue;
		if (inArea(enemy->getPosition()) && !list.contains(enemy))
		{
			list.pushBack(enemy);
			++res;
		}
	}
	return res;
}



void GameScene::loadSkillPattern()
{
	auto btn_Ice = Sprite::create("UI_Skill_Ice.png");
	auto btn_Ice_sel = Sprite::create("UI_Skill_Ice.png");
	btn_Ice_sel->setScale(1.1);

	auto btn_Wind = Sprite::create("UI_Skill_Wind.png");
	auto btn_Wind_sel = Sprite::create("UI_Skill_Wind.png");
	btn_Wind_sel->setScale(1.1);

	auto btn_Wave = Sprite::create("UI_Skill_Wave.png");
	auto btn_Wave_sel = Sprite::create("UI_Skill_Wave.png");
	btn_Wave_sel->setScale(1.1);

	Vec2 btn_Size = btn_Ice->getContentSize();

	auto skillIce = MenuItemSprite::create(btn_Ice, btn_Ice_sel, CC_CALLBACK_1(GameScene::selectSkill, this));
	auto skillWind = MenuItemSprite::create(btn_Wind, btn_Wind_sel, CC_CALLBACK_1(GameScene::selectSkill, this));
	auto skillWave = MenuItemSprite::create(btn_Wave, btn_Wave_sel, CC_CALLBACK_1(GameScene::selectSkill, this));
	skillIce->setTag(31);
	skillIce->setPosition(-btn_Size.x, 0);

	skillWind->setTag(32);
	skillWind->setPosition(0, 0);

	skillWave->setTag(33);
	skillWave->setPosition(btn_Size.x, 0);

	Menu * skillMenu = Menu::create(skillIce, skillWind, skillWave, nullptr);
	skillMenu->setPosition(Vec2(800, 50));
	this->addChild(skillMenu);
}

void GameScene::loadStatus()
{
	auto box = Sprite::create("ui_longbox.png");
	box->setPosition(Vec2(480, 610));
	addChild(box);

	auto money = Sprite::create("GamesScreen_money.png");
	money->setPosition(30,23);
	money->setScale(0.9);
	box->addChild(money,100);

	auto hp = Sprite::create("GamesScreen_live.png");
	hp->setPosition(120, 23);
	hp->setScale(0.7);
	box->addChild(hp,100);

}

void GameScene::selectSkill(Ref * obj)
{
	//移除建塔面板
	if (this->getChildByTag(100) != nullptr)
	{
		this->removeChildByTag(100);
	}
	
	auto item = (MenuItemSprite *)obj;
	
	if (selectedSkill == item->getTag() && currSkill!=nullptr)
	{
		
		//item->setOpacity(255);
		selectedSkill = -1;
		currSkill = nullptr;
		return;
	}
	//item->setOpacity(200);
	selectedSkill = item->getTag();
	switch (item->getTag())
	{
	case 31:
	{
		//急速冷却技能
		currSkill = FastFreeze::create();
		addChild(currSkill);
		break;
	}
	case 32:
	{
		//强袭飓风
		currSkill = Hurricane::create();
		addChild(currSkill);
		break;
	}
	case 33:
	{
		//超震声波
		currSkill = ShakingWave::create();
		addChild(currSkill);
		break;
	}
	default:
		break;
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

	if (currSkill != nullptr) // 使用技能
	{
		if (!currSkill->onTouchBegan(now))
			currSkill = nullptr;
		auto menu = this->getChildByTag(selectedSkill);

	}
	else // 建塔
	{

		log("touch %f %f", now.x, now.y);
		TMXTiledMap * ourMap = (TMXTiledMap*)this->getChildByTag(0);
		//row为横坐标，col为纵坐标
		this->nowRow = (int)(now.x / 56.9);
		this->nowCol = 10 - (int)(now.y / 56.9);
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
			if (towerInfo[nowCol][nowRow])
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
			auto tips = Sprite::create("UI_X.png");
			tips->setPosition(Vec2(nowRow * 56.9 + 28.45, (10 - nowCol) * 56.9 + 28.45));
			this->addChild(tips);
			tips->runAction(
				Sequence::create(
				DelayTime::create(0.8),
				CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, tips)), NULL));
		}
	}

	return true;
}

void GameScene::onTouchMoved(Touch * touch, Event * unused_event)
{
	Vec2 now = touch->getLocation();

	if (currSkill != nullptr) // 使用技能
	{
		if (!currSkill->onTouchMoved(now))
			currSkill = nullptr;
	}

}

void GameScene::onTouchEnded(Touch * touch, Event * unused_event)
{
	Vec2 now = touch->getLocation();

	if (currSkill != nullptr) // 使用技能
	{
		currSkill->onTouchEnded(now);
		currSkill = nullptr;
	}

}

//塔的选择
void GameScene::addTDSelect(int r, int c)
{
	//造塔点显示图片做标注
	auto tPos = Sprite::create("towerSel.png");
	Vec2 nowSize = tPos->getContentSize();
	//造塔点上方显示要造的塔
	//设置按钮未选择和选择的图片
	auto bt01 = Sprite::create("Thunder_Tower_00.png");
	auto bt01_sel = Sprite::create("Thunder_Tower_00.png");
	bt01_sel->setScale(1.1);
	
	//冰塔
	SpriteFrame* spF = SpriteFrameCache::getInstance()->getSpriteFrameByName("Ice Tower/Ice_Tower_00.png");
	auto bt02 = Sprite::createWithSpriteFrame(spF);
	auto bt02_sel= Sprite::createWithSpriteFrame(spF);
	bt02->setScale(0.6);
	bt02_sel->setScale(0.66);

	//火焰塔
	auto bt03 = Sprite::create("Fire_Tower_01.png");
	auto bt03_sel= Sprite::create("Fire_Tower_01.png");

	bt03_sel->setScale(1.1);

	//将该sprite转为Menu接收用户事件
	auto menuItem01 = MenuItemSprite::create(bt01, bt01_sel, CC_CALLBACK_1(GameScene::selectTD, this));
	menuItem01->setTag(10);
	menuItem01->setAnchorPoint(Vec2(0.5, 0));
	auto price1 = Sprite::create("ui_towerprice150.png");
	price1->setPosition(Vec2(nowSize.x/2, 65));
	menuItem01->addChild(price1);

	auto menuItem02 = MenuItemSprite::create(bt02, bt02_sel, CC_CALLBACK_1(GameScene::selectTD, this));
	menuItem02->setTag(11);
	menuItem02->setAnchorPoint(Vec2(0, 0));
	auto price2 = Sprite::create("ui_towerprice160.png");
	price2->setPosition(Vec2(nowSize.x / 2, 65));
	menuItem02->addChild(price2);

	auto menuItem03 = MenuItemSprite::create(bt03, bt03_sel, CC_CALLBACK_1(GameScene::selectTD, this));
	menuItem03->setTag(12);
	menuItem03->setAnchorPoint(Vec2(1, 0));
	auto price3 = Sprite::create("ui_towerprice180.png");
	price3->setPosition(Vec2(nowSize.x / 2, 65));
	menuItem03->addChild(price3);

	//用menu容纳menuItem
	auto menuTD = Menu::create(menuItem01, menuItem02, menuItem03, nullptr);
	
	menuTD->setPosition(Vec2::ZERO);
	tPos->addChild(menuTD);

	menuItem01->setPosition(Vec2(nowSize.x / 2, nowSize.y));
	menuItem02->setPosition(Vec2(nowSize.x, nowSize.y));
	menuItem03->setPosition(Vec2(0, nowSize.y));

	tPos->setTag(100);
	this->addChild(tPos);

	tPos->setPosition(r*56.9 + 28.45, c*56.9 + 28.45);
}

void GameScene::selectTD(Ref * obj)
{
	auto item = (MenuItemSprite *)obj;
	switch (item->getTag())
	{
	case 10:
	{
		Tower * TD = Tower::createTower(TOWER_THUNDER, nowRow, nowCol);
		this->addChild(TD);
		//标记该位置已经建塔
		towerInfo[nowCol][nowRow] = true;
		break;
	}
	case 11:
	{
		Tower * TD = Tower::createTower(TOWER_ICE, nowRow, nowCol);
		this->addChild(TD);
		//标记该位置已经建塔
		towerInfo[nowCol][nowRow] = true;
		break;
	}
	case 12:
	{
		Tower * TD = Tower::createTower(TOWER_FIRE, nowRow, nowCol);
		this->addChild(TD);
		//标记该位置已经建塔
		towerInfo[nowCol][nowRow] = true;
		break;
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

void GameScene::alignPosition(cocos2d::Vec2& pos)
{
	int i = (int)(pos.x / 56.9);
	int j = (int)(pos.y / 56.9);
	pos.set((i + 0.5)*56.9, (j + 0.5)*56.9);
}
