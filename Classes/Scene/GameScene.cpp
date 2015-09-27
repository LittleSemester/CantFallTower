#include "GameScene.h"
#include "Enemy/SimpleEnemy.h"
#include "Tower/Tower.h"
#include "Skill/Hurricane.h"
#include "Skill/FastFreeze.h"
#include "Skill/ShakingWave.h"
#include "Scene/WinScene.h"
#include "Scene/MainScene.h"

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

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	GameScene::getScheduler()->setTimeScale(1.0);

	//娣诲姞鑳屾櫙鍥剧墖
	auto spriteBG = Sprite::create("Map_Ground_02.jpg");
	addChild(spriteBG);
	spriteBG->setPosition(Vec2(480, 320));

	//娣诲姞鍦板浘鏂囦欢
	auto Map = TMXTiledMap::create("map_0.tmx");
	addChild(Map);
	Map->setTag(0);//灏嗗湴鍥炬枃浠禩ag璁剧疆涓?

	//鍔犺浇鏁屼汉琛岃蛋璺緞鐐?
	initAllPoints();
	//初始化建塔信息
	memset(towerInfo, 0, sizeof(towerInfo));

	//设置敌人数量
	enemyMaxCount = 20;
	//产生一大波怪物
	enemyCreated = 0;

	schedule(schedule_selector(GameScene::EnemyCreat),1 );

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

	

	
	return true;
}


//鍔犺浇鏁屼汉琛岃蛋璺緞鐐?
void GameScene::initAllPoints()
{
	if (allPoint.size() > 0)
	{
		allPoint.clear();
	}
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


void GameScene::EnemyCreat(float dt)
{
	if (enemyCreated < enemyMaxCount)
	{
		//产生的敌人未达到最大数量则继续产生
		++enemyCreated;
		auto newEnemy = SimpleEnemy::create("enemy_1");
		addChild(newEnemy);
		enemyList.pushBack(newEnemy);
	}
	clearRemovedEnemyFromList();
	if (enemyList.size() == 0)
	{
		//一波敌人结束后
		enemyCreated = 0;
		int nextWave = getWave() + 1;
		if (nextWave > sumWave)
		{
			//消灭了全部敌人，转场胜利
			auto nextScene = WinScene::createScene();
			auto Trans = TransitionFadeTR::create(1.0, nextScene);
			Director::getInstance()->replaceScene(Trans);
		}
		else
		{
			setWave(nextWave);
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
	skillMenu->setTag(30);
	this->addChild(skillMenu);
}

void GameScene::loadStatus()
{
	stopTouch = false;
	auto box = Sprite::create("ui_longbox.png");
	box->setScaleY(1.3);

	auto money = Sprite::create("GamesScreen_money.png");
	money->setScale(0.9);

	auto hp = Sprite::create("GamesScreen_live.png");
	hp->setScale(0.7);

	auto wave = Sprite::create("GamesScreen_enemy.png");

	Button * set = Button::create("ui_set.png");;
	set->setPosition(Vec2(400, 0));
	set->setScale(0.8);
	set->setOpacity(225);
	set->addTouchEventListener(CC_CALLBACK_2(GameScene::setCallBack, this));

	CheckBox * speed = CheckBox::create();
	speed->loadTextureBackGround("ui_x1.png");
	speed->loadTextureFrontCross("ui_x2.png");
	speed->setPosition(Vec2(275, 0));
	speed->setScale(0.7);
	speed->addEventListener(CC_CALLBACK_2(GameScene::speedCallBack, this));
	speed->setName("speed");

	CheckBox * pause = CheckBox::create();
	pause->loadTextureBackGround("ui_pause.png");
	pause->loadTextureFrontCross("ui_begin.png");
	pause->setPosition(Vec2(150, 0));
	pause->setScale(0.7);
	pause->addEventListener(CC_CALLBACK_2(GameScene::pauseCallBack, this));
	pause->setName("pause");

	//初始化状态
	this->ourHealth = 20;
	this->money = 400;
	this->nowWave = 1;
	this->sumWave = 2;

	TTFConfig myTTF;
	myTTF.fontFilePath = "fonts/Marker Felt.ttf";
	myTTF.fontSize = 28;
	myTTF.glyphs = GlyphCollection::DYNAMIC;
		
	labHealth = (Label*)Label::createWithTTF(myTTF, "20");
	labMoney = (Label*)Label::createWithTTF(myTTF,"20");
	labWave = (Label*)Label::createWithTTF(myTTF, "20");
	labHealth->setName("health");
	labMoney->setName("money");
	labWave->setName("wave");

	//状态栏容器
	auto status = Layout::create();
	status->setName("status");
	addChild(status);

	//加入各个图标
	labHealth->setPosition(Vec2(-210, 0));
	labMoney->setPosition(Vec2(-360, 0));
	status->setPosition(Vec2(480, 610));
	money->setPosition(Vec2(-400, 0));
	hp->setPosition(Vec2(-250, 0));
	wave->setPosition(Vec2(-100, 0));


	status->addChild(box);
	status->addChild(money);
	status->addChild(hp);
	status->addChild(wave);
	status->addChild(set);
	status->addChild(speed);
	status->addChild(pause);
	status->addChild(labMoney);
	status->addChild(labHealth);
	status->addChild(labWave);
	this->setMoney(this->money);
	this->setWave(this->nowWave);
	this->setHealth(this->ourHealth);

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
		//再次点击相同技能则取消释放
		item->setScale(1.0);

		selectedSkill = -1;
		currSkill = nullptr;
		return;
	}
	item->setScale(1.1);
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
	if (stopTouch)
		return false;
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
		//使用完技能图标还原
		auto menu = this->getChildByTag(30);
		auto skill = menu->getChildByTag(selectedSkill);
		skill->setScale(1.0);
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

	//星落之塔
	auto bt04 = Sprite::create("Star/Star Tower/Star_Tower_02.png");
	auto bt04_sel = Sprite::create("Star/Star Tower/Star_Tower_02.png");
	bt04->setScale(0.6);
	bt04_sel->setScale(0.66);

	//月刃之塔
	auto bt05 = Sprite::create("Moon/Moon Tower/Moon_Tower_00.png");
	auto bt05_sel = Sprite::create("Moon/Moon Tower/Moon_Tower_00.png");
	bt05->setScale(0.5);
	bt05_sel->setScale(0.55);

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

	auto menuItem04 = MenuItemSprite::create(bt04, bt04_sel, CC_CALLBACK_1(GameScene::selectTD, this));
	menuItem04->setTag(13);
	menuItem04->setAnchorPoint(Vec2(0,0));

	auto menuItem05 = MenuItemSprite::create(bt05, bt05_sel, CC_CALLBACK_1(GameScene::selectTD, this));
	menuItem05->setTag(14);
	menuItem05->setAnchorPoint(Vec2(1, 0));

	//用menu容纳menuItem
	auto menuTD = Menu::create(menuItem01, menuItem02, menuItem03, menuItem04, menuItem05, nullptr);
	
	menuTD->setPosition(Vec2::ZERO);
	tPos->addChild(menuTD);

	menuItem01->setPosition(Vec2(nowSize.x / 2, nowSize.y));
	menuItem02->setPosition(Vec2(nowSize.x, nowSize.y));
	menuItem03->setPosition(Vec2(0, nowSize.y));
	menuItem04->setPosition(Vec2(2*nowSize.x, nowSize.y));
	menuItem05->setPosition(Vec2(-nowSize.x/2, 1*nowSize.y));
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
	case 13:
		
	{
		Tower * TD = Tower::createTower(TOWER_ARROW, nowRow, nowCol);
		this->addChild(TD);
		//标记该位置已经建塔
		towerInfo[nowCol][nowRow] = true;
		break;
	}
	case 14:
	{
		Tower * TD = Tower::createTower(TOWER_KNIFE, nowRow, nowCol);
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


int GameScene::getMoney()
{
	return money;
}

int GameScene::getHealth()
{
	return ourHealth;
}

int GameScene::getWave()
{
	return nowWave;
}

void GameScene::setHealth(int newHealth)
{
	ourHealth = newHealth;
	if (labHealth != nullptr)
	{
		std::string str = Value(ourHealth).asString();
		labHealth->setString(str);
	}
}

void GameScene::setMoney(int newMoney)
{
	money = newMoney;
	if (labMoney != nullptr)
	{
		auto str = Value(money).asString();
		labMoney->setString(str);
	}
}

void GameScene::setWave(int newWave)
{
	nowWave = newWave;
	if (labWave != nullptr)
	{
		auto str1 = Value(nowWave).asString();
		auto str2 = Value(sumWave).asString();

		labWave->setString(str1+"/"+str2);
	}
}

void GameScene::speedCallBack(Ref* pSender, CheckBox::EventType type)
{
	if (stopTouch)
		return;
	CheckBox* pauseItem = (CheckBox*)getChildByName("status")->getChildByName("pause");
	if (pauseItem->getSelectedState())
		return;
	switch (type)
	{
	case CheckBox::EventType::SELECTED:
		GameScene::getScheduler()->setTimeScale(2.0);
		break;
	case CheckBox::EventType::UNSELECTED:
	{
		GameScene::getScheduler()->setTimeScale(1.0);
		break;
	}
	default:
		break;
	}
}

void GameScene::pauseCallBack(Ref* pSender, CheckBox::EventType type)
{
	if (stopTouch)
		return;
	switch (type)
	{
	case CheckBox::EventType::SELECTED:
		GameScene::getScheduler()->setTimeScale(0.0);
		break;
	case CheckBox::EventType::UNSELECTED:
	{
		CheckBox* speedItem = (CheckBox*)getChildByName("status")->getChildByName("speed");
		if (speedItem->getSelectedState())
		{
			GameScene::getScheduler()->setTimeScale(2.0);
		}
		else
		{
			GameScene::getScheduler()->setTimeScale(1.0);
		}
		break;
	}
	default:
		break;
	}
}

void GameScene::setCallBack(cocos2d::Ref* pSender, Widget::TouchEventType type)
{
	if (stopTouch)
		return;
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
	{
		GameScene::getScheduler()->setTimeScale(0.0);
		auto black = Sprite::create("black.png");
		black->setOpacity(200);
		black->setPosition(Vec2(480, 320));
		black->setName("black");
		addChild(black);
		stopTouch = true;
		
		auto box = Layout::create();
		box->setName("backBox");
		auto backbox = Sprite::create("ui_setbox.png");
		box->setPosition(Vec2(480, 320));
		box->addChild(backbox);
		Button* ret = Button::create("GameScreen_backmenu.png");
		box->addChild(ret);

		Button* again = Button::create("GameScreen_tryagain.png");
		box->addChild(again);

		Button* conti = Button::create("GameScreen_win_goon.png");
		box->addChild(conti);
		
		conti->addTouchEventListener(CC_CALLBACK_2(GameScene::contiCallBack, this));
		ret->addTouchEventListener(CC_CALLBACK_2(GameScene::retCallBack, this));
		again->addTouchEventListener(CC_CALLBACK_2(GameScene::againCallBack, this));

		addChild(box);
		conti->setPosition(Vec2(0, 130));
		ret->setPosition(Vec2(0, -130));

	}
		break;
	case Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void GameScene::contiCallBack(cocos2d::Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
	{
		auto backBox = this->getChildByName("backBox");
		auto vecChild = backBox->getChildren();
		for (auto eachChild : vecChild)
		{
			eachChild->removeFromParent();
		}
		backBox->removeFromParent();
		auto black = this->getChildByName("black");
		black->removeFromParent();

		CheckBox* speedItem = (CheckBox*)getChildByName("status")->getChildByName("speed");
		if (speedItem->getSelectedState())
		{
			GameScene::getScheduler()->setTimeScale(2.0);
		}
		else
		{
			GameScene::getScheduler()->setTimeScale(1.0);
		}

		stopTouch = false;
		
		break;
	}
	case Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void GameScene::againCallBack(cocos2d::Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
	{
		auto backBox = this->getChildByName("backBox");
		auto vecChild = backBox->getChildren();
		for (auto eachChild : vecChild)
		{
			eachChild->removeFromParent();
		}
		backBox->removeFromParent();
		auto black = this->getChildByName("black");
		black->removeFromParent();

		CheckBox* speedItem = (CheckBox*)getChildByName("status")->getChildByName("speed");
		if (speedItem->getSelectedState())
		{
			GameScene::getScheduler()->setTimeScale(2.0);
		}
		else
		{
			GameScene::getScheduler()->setTimeScale(1.0);
		}

		stopTouch = false;
		auto nextScene = GameScene::createScene();
		auto Trans = TransitionFadeTR::create(1.0, nextScene);
		Director::getInstance()->replaceScene(Trans);
		break;
	}
	case Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void GameScene::retCallBack(cocos2d::Ref * pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
	{
		auto backBox = this->getChildByName("backBox");
		auto vecChild = backBox->getChildren();
		for (auto eachChild : vecChild)
		{
			eachChild->removeFromParent();
		}
		backBox->removeFromParent();
		auto black = this->getChildByName("black");
		black->removeFromParent();

		CheckBox* speedItem = (CheckBox*)getChildByName("status")->getChildByName("speed");
		if (speedItem->getSelectedState())
		{
			GameScene::getScheduler()->setTimeScale(2.0);
		}
		else
		{
			GameScene::getScheduler()->setTimeScale(1.0);
		}

		stopTouch = false;

		auto nextScene = MainScene::createScene();
		auto Trans = TransitionFadeTR::create(1.0, nextScene);
		Director::getInstance()->replaceScene(Trans);
		break;
	}
	case Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}
