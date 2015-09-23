// 编码：Utf-8 without BOM
// Created by LuiCat

#ifndef _BUFF_H_
#define _BUFF_H_

enum BuffFlags
{
	BUFF_NONE = 0,
	BUFF_BURNED = 1,
	BUFF_FROZEN = 2,
	BUFF_CURED = 4,
	BUFF_CHEERUP = 8,
	BUFF_DEFDOWN = 16,
	BUFF_RUSH = 32,
	BUFF_INVINCIBLE = 64,
	BUFF_FXXKUP = 0xFFFFFFFF
};

class Buff
{
protected:

	double timeLeft;
	bool finished;
	unsigned int flag;

public:

	Buff(double timeSec);
	Buff(const Buff& buff);
	virtual ~Buff() = 0;

	bool isFinished() const;

	//继承这个函数时记得调用Buff::update(deltaSec)
	virtual void update(double deltaSec);

	virtual double defence(double origin);

	virtual double damageOut(double origin);
	virtual double damageIn(double origin);

	virtual double speed(double origin);

	virtual double damageOnce();
	virtual double cureOnce();

	inline unsigned int getFlag() const
	{
		return flag;
	}

};

class SimpleBuff : public Buff
{
public:

	struct BuffMultiplier
	{
		double defence;
		double damageOut;
		double damageIn;
		double speed;
		double damageOnce;
		double cureOnce;
	};

	SimpleBuff(double timeSec, const BuffMultiplier& multiplier);

	template<typename... Args>
	SimpleBuff(double timeSec, Args... multipliers)
		: Buff(timeSec)
	{
		setMultiplier(0, multipliers...);
	}

	inline void setFlag(unsigned int newflag)
	{
		flag = newflag;
	}

protected:

	BuffMultiplier mul;

	virtual double defence(double origin);

	virtual double damageOut(double origin);
	virtual double damageIn(double origin);

	virtual double speed(double origin);

	virtual double damageOnce();
	virtual double cureOnce();

private:

	template<typename... Args>
	void setMultiplier(int curr, double first, Args... remain)
	{
		if (curr < sizeof(BuffMultiplier) / sizeof(double))
		{
			*((double*)&mul + curr) = first;
			setMultiplier(curr + 1, remain...);
		}

	}

	void setMultiplier(int curr);

};



#endif // _BUFF_H_
