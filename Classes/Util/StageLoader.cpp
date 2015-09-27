// 编码：Utf-8 without BOM
// Created by LuiCat

#include "StageLoader.h"
#include "Enemy/SimpleEnemy.h"

USING_NS_CC;

StageLoader::StageLoader()
{
	dictStage = nullptr;
	waves = nullptr;
	dictWave = nullptr;
	waveCount = 0;
	currWave = 0;
	nextEnemy = 0;
}

StageLoader::StageLoader(const std::string& plist)
	:StageLoader()
{
	loadStage(plist);
}

StageLoader::~StageLoader()
{
	if (dictStage != nullptr)
	{
		dictStage->release();
		dictStage = 0;
	}
}

bool StageLoader::loadStage(const std::string& plist)
{
	dictStage = Dictionary::createWithContentsOfFile(plist.c_str());
	dictStage->retain();

	waves = dynamic_cast<Array*>(dictStage->objectForKey("waves"));
	waveCount = waves->count();
	currWave = 0;
	nextEnemy = 0;

	if (waveCount>0)
		dictWave = dynamic_cast<Dictionary*>(waves->objectAtIndex(0));

	return true;
}

bool StageLoader::toggleNextWave()
{
	if (currWave + 1 >= waveCount)
		return false;
	++currWave;
	nextEnemy = 0;
	dictWave = dynamic_cast<Dictionary*>(waves->objectAtIndex(currWave));
	return true;
}

double StageLoader::getEnemySpawnDelay()
{
	if (!isAvailable())
		return INFINITY;
	return dictWave->valueForKey("delay")->doubleValue();
}

Enemy* StageLoader::createNextEnemy()
{
	if (!isAvailable())
		return nullptr;

	dictWave = dynamic_cast<Dictionary*>(waves->objectAtIndex(currWave));
	if (nextEnemy >= dictWave->valueForKey("count")->intValue())
		return nullptr;

	auto listEnemy = dynamic_cast<Array*>(dictWave->objectForKey("enemies"));
	int enemyCount = listEnemy->count();
	return SimpleEnemy::create(dynamic_cast<String*>(listEnemy->objectAtIndex(nextEnemy++ % enemyCount))->getCString());
}

const char* StageLoader::getBackGroundFileName()
{
	if (!isAvailable())
		return nullptr;
	return dictStage->valueForKey("background")->getCString();
}

const char* StageLoader::getTileMapFileName()
{
	if (!isAvailable())
		return nullptr;
	return dictStage->valueForKey("tilemap")->getCString();
}

const char* StageLoader::getStageName()
{
	if (!isAvailable())
		return nullptr;
	return dictStage->valueForKey("stagename")->getCString();
}

