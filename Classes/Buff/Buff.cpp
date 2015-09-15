// 编码：Utf-8 without BOM
// Created by LuiCat

#include "Buff.h"

Buff::Buff(double timeSec)
	: timeLeft(timeSec)
	, finished(false)
{

}

Buff::Buff(const Buff& buff)
	: timeLeft(buff.timeLeft)
	, finished(buff.finished)
{

}

Buff::~Buff()
{

}

bool Buff::isFinished() const
{
	return finished;
}

void Buff::update(double deltaSec)
{
	timeLeft -= deltaSec;
	if (deltaSec <= 0)
		finished = true;
}


double Buff::defence(double origin)
{
	return origin;
}

double Buff::damageOut(double origin)
{
	return origin;
}

double Buff::damageIn(double origin)
{
	return origin;
}

double Buff::cureIn(double origin)
{
	return origin;
}
