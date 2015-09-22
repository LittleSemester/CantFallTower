#ifndef __TOWER_H__
#define __TOWER_H__

#include <cocos2d.h>

class Tower:public cocos2d::Node
{
public:
	Tower();
	~Tower();
	Tower(int type, int row, int col);
	bool init();

	int tx, ty;//λ��
	int trow, tcol;//��������
	int type;//��������
	int price;//�۸�
	int attack;//������
	int radius;//������Χ



	CREATE_FUNC(Tower);

	static Tower* create(int type, int row, int col);

	static Tower* createTower(int type, int row, int col);

	void fire();
};

#endif