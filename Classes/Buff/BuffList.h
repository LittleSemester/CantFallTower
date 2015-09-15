// 编码：Utf-8 without BOM
// Created by LuiCat

#include <deque>

#include "Buff.h"

class BuffList
{
private:

	std::deque<Buff*> buffs;

public:

	BuffList();
	~BuffList();

	template <typename T, typename... Args>
	void newBuff(Args... args)
	{
		static_assert(is_base_of<T, Buff>::value,
			"template parameter T in BuffList::newBuff should be implement of class Buff");
		buffs.emplace_back(new T(args));
	}

	// 参数buff必须为new的对象，buff失效时列表将尝试delete
	void pushBuff(Buff* buff);

	// 使用方法举例：double buffedDamage=list.calcBuffedValue(Buff::damageOut, originDamage);
	double calcBuffedValue(double (Buff::*func)(double), double origin);

	void clear();

};
