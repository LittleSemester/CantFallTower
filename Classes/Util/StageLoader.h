// 编码：Utf-8 without BOM
// Created by LuiCat

#ifndef _STAGGELOADER_H_
#define _STAGGELOADER_H_

#include <string>
#include "Enemy/Enemy.h"
#include <cocos2d.h>

class StageLoader
{
private:

	cocos2d::Dictionary* dictStage;
	cocos2d::Array* waves;

	cocos2d::Dictionary* dictWave;

	int waveCount;
	int currWave;
	int nextEnemy;

public:

	explicit StageLoader();
	explicit StageLoader(const std::string& plist);
	~StageLoader();

	bool loadStage(const std::string& plist);

	inline bool isAvailable() const
	{
		return dictStage != nullptr && waves != nullptr && waveCount>0;
	}

	inline int getWaveCount()
	{
		return waveCount;
	}

	inline int getCurrentWave()
	{
		return currWave;
	}

	bool toggleNextWave();
	double getEnemySpawnDelay();
	Enemy* createNextEnemy();

	const char* getBackGroundFileName();
	const char* getTileMapFileName();
	const char* getStageName();

};


#endif
