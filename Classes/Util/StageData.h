// 编码：Utf-8 without BOM
// Created by LuiCat

#ifndef _STAGE_DATA_H_
#define _STAGE_DATA_H_

#include <vector>
#include <string>

class StageData
{
private:

	class SingletonRelease
	{
	public:
		~SingletonRelease()
		{
			if (m_instance != nullptr)
			{
				delete m_instance;
				m_instance = nullptr;
			}
		}
	};

	static StageData* m_instance;
	static SingletonRelease autorelease;

	explicit StageData();

	std::vector<std::string> nameStages;
	int currStage;

public:

	static StageData* getInstance();

	virtual ~StageData();

	void pushStageFileName(const char* filename);
	
	const char* getCurrentStageFileName();
	bool toggleNextStage();

	// 参数i自0起，也就是说，第一关i=0，第二关i=1，以此类推
	void toggleStage(int i);

};

#endif
