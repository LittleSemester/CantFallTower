// 编码：Utf-8 without BOM
// Created by LuiCat

#include "StageData.h"

StageData* StageData::m_instance = nullptr;
StageData::SingletonRelease StageData::autorelease;

StageData* StageData::getInstance()
{
	if (m_instance == nullptr)
		m_instance = new StageData();
	return m_instance;
}

StageData::StageData()
{
	currStage = 0;
}

StageData::~StageData()
{

}

const char* StageData::getCurrentStageFileName()
{
	if (nameStages.empty())
		return nullptr;
	return nameStages[currStage].c_str();
}

bool StageData::toggleNextStage()
{
	if (nameStages.empty())
		return false;
	++currStage;
	if (currStage < nameStages.size())
		return true;
	currStage = 0;
	return false;
}

void StageData::toggleStage(int i)
{
	if (nameStages.empty())
		return;
	if (i < 0)
		i = 0;
	currStage = i % nameStages.size();
}

void StageData::pushStageFileName(const char* filename)
{
	nameStages.emplace_back(filename);
}
