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

//=========SimpleBuff Member Functions===========

SimpleBuff::SimpleBuff(double timeSec, const BuffMultiplier& multiplier)
	:Buff(timeSec)
{
	mul = multiplier;
}

double SimpleBuff::defence(double origin)
{
	return origin*mul.defence;
}

double SimpleBuff::damageOut(double origin)
{
	return origin*mul.damageOut;
}

double SimpleBuff::damageIn(double origin)
{
	return origin*mul.damageIn;
}

double SimpleBuff::cureIn(double origin)
{
	return origin*mul.cureIn;
}

void SimpleBuff::setMultiplier(int curr)
{
	if (curr < sizeof(BuffMultiplier) / sizeof(double))
	{
		*((double*)&mul + curr) = 1.0;
		setMultiplier(curr + 1);
	}
}
