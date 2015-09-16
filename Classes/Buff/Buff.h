// 编码：Utf-8 without BOM
// Created by LuiCat

#ifndef _BUFF_H_
#define _BUFF_H_

class Buff
{
protected:

	double timeLeft;
	bool finished;

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

	virtual double cureIn(double origin);

};

class SimpleBuff : public Buff
{
public:

	struct BuffMultiplier
	{
		double defence;
		double damageOut;
		double damageIn;
		double cureIn;
	};

	SimpleBuff(double timeSec, const BuffMultiplier& multiplier);

	template<typename... Args>
	SimpleBuff(double timeSec, Args... multipliers)
		: Buff(timeSec)
	{
		setMultiplier(0, multipliers...);
	}

protected:

	BuffMultiplier mul;

	virtual double defence(double origin);

	virtual double damageOut(double origin);
	virtual double damageIn(double origin);

	virtual double cureIn(double origin);

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
