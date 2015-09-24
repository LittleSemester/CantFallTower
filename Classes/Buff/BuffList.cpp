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
	if (buff == nullptr)
		return;
	unsigned int flag = buff->getFlag();
	for (auto iter = buffs.begin(); iter != buffs.end();)
	{
		if ((*iter)->getFlag() == flag)
		{
			Buff* t = *iter;
			iter = buffs.erase(iter);
			if (t != nullptr)
			{
				onBuffEnd(t);
				delete t;
			}
		}
		else
			++iter;
	}
	buffs.emplace_back(buff);
	onBuffBegin(buff);
}

double BuffList::calcBuffedValue(double (Buff::*func)(double), double origin)
{
	if (func == nullptr)
		return origin;
	for (Buff* buff : buffs)
	{
		if (!buff->isFinished())
			origin=(buff->*func)(origin);
	}
	return origin;
}

double BuffList::getBuffValue(double (Buff::*func)())
{
	if (func == nullptr)
		return 0.0;
	double res = 0.0;
	for (Buff* buff : buffs)
	{
		if (!buff->isFinished())
			res += (buff->*func)();
	}
	return res;
}

unsigned int BuffList::getBuffFlag()
{
	unsigned int flag = BUFF_NONE;
	for (Buff* buff : buffs)
	{
		if (!buff->isFinished())
			flag |= buff->getFlag();
	}
	return flag;
}


void BuffList::updateBuff(double deltaSec)
{
	for (auto iter = buffs.begin(); iter != buffs.end();)
	{
		if ((*iter)->isFinished())
		{
			Buff* t = *iter;
			iter = buffs.erase(iter);
			if (t != nullptr)
			{
				onBuffEnd(t);
				delete t;
			}
		}
		else
		{
			(*iter)->update(deltaSec);
			++iter;
		}
	}
}

void BuffList::clear()
{
	Buff* buff = 0;
	while (!buffs.empty())
	{
		buff = buffs.front();
		buffs.pop_front();
		if (buff != nullptr)
		{
			onBuffEnd(buff);
			delete buff;
		}
	}
	buffs.clear();
}

void BuffList::onBuffBegin(Buff* buff)
{

}

void BuffList::onBuffEnd(Buff* buff)
{

}
