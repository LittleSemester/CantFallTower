// 编码：Utf-8 without BOM
// Created by LuiCat

#include "Buff.h"

Buff::Buff(double timeSec)
	: timeLeft(timeSec)
	, finished(false)
	, flag(BUFF_NONE)
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
	if (timeLeft <= 0)
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

double Buff::speed(double origin)
{
	return origin;
}

double Buff::damageOnce()
{
	return 0.0;
}

double Buff::cureOnce()
{
	return 0.0;
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

double SimpleBuff::speed(double origin)
{
	return origin*mul.speed;
}

double SimpleBuff::damageOnce()
{
	return mul.damageOnce;
}

double SimpleBuff::cureOnce()
{
	return mul.cureOnce;
}

void SimpleBuff::setMultiplier(int curr)
{
	if (curr < sizeof(BuffMultiplier) / sizeof(double))
	{
		*((double*)&mul + curr) = 1.0;
		setMultiplier(curr + 1);
	}
}
