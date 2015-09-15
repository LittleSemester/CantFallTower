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



#endif // _BUFF_H_
