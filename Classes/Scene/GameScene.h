#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include <cocos2d.h>
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Util/TDPoint.h"
#include "Entity/Entity.h"
#include "Enemy/Enemy.h"


class Enemy;
class Entity;

using namespace cocostudio::timeline;
class GameScene:public cocos2d::Layer
{
protected:

	cocos2d::Vector<Enemy*> enemyList;

	void clearRemovedEnemyFromList();

public:

	static cocos2d::Scene* createScene();
	
	virtual bool init();

	CREATE_FUNC(GameScene);

	static cocos2d::Vector<TDPoint*> allPoint;//±£´æËùÓÐÂ·¾¶×ªÍäµã

	int enemyMaxCount; //æ•Œäººæœ€å¤§æ•°é‡?
	int enemyCreated;
	
	void EnemyCreat(float dt);//äº§ç”Ÿä¸€æ³¢æ€ªç‰©

	// ç”¨äºŽå•ä¸€Entityè¿›è¡Œåˆ¤å®šæ£€æµ‹ï¼Œä¸€èˆ¬æƒ…å†µä¸‹ç”±Entityè‡ªèº«è°ƒç”¨ï¼ŒæŒ‡å®šsingleEnemyä»¥åˆ¤å®šå•ä¸ªç›®æ ‡ï¼ˆä¼šæ£€æŸ¥ç›®æ ‡æœ‰æ•ˆæ€§ï¼‰
	void judgeEntityBounding(Entity* entity, Enemy* singleEnemy = nullptr);

	void initAllPoints();//¼ÓÔØµÐÈËÐÐ×ßÂ·¾¶µã

	void addTDSelect(int r, int c);//Ìí¼ÓËþµÄÑ¡ÔñÃæ°å

	void selectTD(cocos2d::Ref* obj);//½¨ËþµÄ»Øµ÷

	int nowRow, nowCol;//µã»÷´¦µÄÐÐÁÐÐÅÏ¢£¬¹©ÔìËþ¹ý³ÌÊ¹ÓÃ

	int towerInfo[11][17];//½¨ËþÐÅÏ¢,ÐÐÁÐÐÅÏ¢ÍêÈ«ºÍ¶þÎ¬Êý×éÏàÍ¬£¬×óÉÏ½ÇÎªÔ­µã£¬ÆÁÄ»Ô­µã,11ÐÐ£¬17ÁÐ

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

};

#endif