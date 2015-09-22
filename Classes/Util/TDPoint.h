#ifndef __TDPOINT_H__
#define __TDPOINT_H__
#include <cocos2d.h>
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class TDPoint :public Ref
{
public:
	float px, py;
	static TDPoint * createPoint(float x,float y);
};
#endif