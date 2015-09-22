#include "TDPoint.h"

TDPoint* TDPoint::createPoint(float x,float y)
{
	TDPoint * td = new TDPoint();
	td->autorelease();
	td->px = x;
	td->py = y;
	return td;
}