// 编码：Utf-8 without BOM
// Created by LuiCat

#include "BuffList.h"

BuffList::BuffList()
{

}

BuffList::~BuffList()
{
	clear();
}

void BuffList::pushBuff(Buff* buff)
{
	if (buff != nullptr)
		buffs.emplace_back(buff);
}

double BuffList::calcBuffedValue(double (Buff::*func)(double), double origin)
{
	if (func != nullptr)
		return origin;
	for (Buff* buff : buffs)
	{
		if (!buff->isFinished())
			origin=(buff->*func)(origin);
	}
	return origin;
}

void BuffList::clear()
{
	Buff* buff = 0;
	while (!buffs.empty())
	{
		buff = buffs.front();
		buffs.pop_front();
		if (buff != nullptr)
			delete buff;
	}
	buffs.clear();
}
