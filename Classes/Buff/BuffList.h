// 编码：Utf-8 without BOM
// Created by LuiCat

#include <deque>

#include "Buff.h"

class BuffList
{
private:

	std::deque<Buff*> buffs;

protected:

	virtual void onBuffBegin(Buff* buff);
	virtual void onBuffEnd(Buff* buff);

public:

	BuffList();
	~BuffList();

	template <typename T, typename... Args>
	void newBuff(Args... args)
	{
		static_assert(std::is_base_of<Buff, T>::value,
			"template parameter T in BuffList::newBuff should be implement of class Buff");
		buffs.emplace_back(new T(args...));
	}

	// 参数buff必须为new的对象，buff失效时列表将尝试delete；相同flag的buff后放入的会替换掉先放入的
	void pushBuff(Buff* buff);

	// 使用方法举例：double buffedDamage=list.calcBuffedValue(&Buff::damageOut, originDamage);
	double calcBuffedValue(double (Buff::*func)(double), double origin);
	// 使用方法举例：double buffDamage=list.getBuffValue(&Buff::damageOnce);
	double getBuffValue(double (Buff::*func)());

	unsigned int getBuffFlag();

	void updateBuff(double deltaSec);

	void clear();
	void clearBuffWithFlag(unsigned int flag);

};
