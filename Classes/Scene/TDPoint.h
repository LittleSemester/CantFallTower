#ifndef __TDPOINT_H__
#define __TDPOINT_H__
#include <cocos2d.h>


class TDPoint :public cocos2d::Ref
{
public:
	float px, py;
	static TDPoint * createPoint(float x,float y);
};
#endif