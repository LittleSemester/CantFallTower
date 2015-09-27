// 编码：Utf-8 without BOM
// Created by LuiCat

#include "SimpleEnemy.h"

USING_NS_CC;


SimpleEnemy::SimpleEnemy(const std::string& type)
{
	this->type = type;
}

bool SimpleEnemy::init()
{
	// 这里plist属性的读取要先于Enemy::init，以便各属性能正常通过虚函数被基类读取
	auto dict = Dictionary::createWithContentsOfFile("enemies.plist");
	auto props = dynamic_cast<Dictionary*>(dict->objectForKey(type));
	if (props == nullptr)
		return false;

	this->maxhp = props->valueForKey("maxHp")->intValue();
	this->def = props->valueForKey("defence")->intValue();
	this->speed = props->valueForKey("speed")->doubleValue();
	this->height = props->valueForKey("height")->doubleValue();

	// 基类初始化
	if (!Enemy::init())
		return false;

	//这里要统一好动画的形式，要么用plist要么用统一命名的图片序列
	auto arrPic = dynamic_cast<Array*>(props->objectForKey("animpic"));
	if (arrPic == nullptr)
		return false;

	walk = Animation::create();
	int sizeAnim = arrPic->count();
	for (int i = 0; i < sizeAnim; ++i)
	{
		auto frame=SpriteFrameCache::getInstance()->getSpriteFrameByName(
			dynamic_cast<String*>(arrPic->getObjectAtIndex(i))->getCString());
		walk->addSpriteFrame(frame);
	}

// 	for (int i = 1; i <= 10; i++)
// 	{
// 		char szName[100];
// 		sprintf(szName, "gw%d.png", i);
// 		walk->addSpriteFrameWithFile(szName);
// 	}
// 	for (int i = 9; i >= 4; i--)
// 	{
// 		char szName[100];
// 		sprintf(szName, "gw%d.png", i);
// 		walk->addSpriteFrameWithFile(szName);
// 	}
	walk->setDelayPerUnit(0.05);

	aniWalk = Animate::create(walk);
	auto repeatWalk = RepeatForever::create(aniWalk);
	repeatWalk->setTag(52013);
	actSprite = Sprite::create();
	actSprite->runAction(repeatWalk);
	actSprite->setAnchorPoint(Vec2(0.5, 0.0));
	actSprite->setPositionY(-20.0);
	addChild(actSprite);

	// 初始化Buff
	auto arrbuff = dynamic_cast<Array*>(props->objectForKey("buffs"));
	if (arrbuff != nullptr)
	{
		int sizeBuff = arrbuff->count();
		for (int i = 0; i < sizeBuff; ++i)
		{
			auto dictBuff = dynamic_cast<Dictionary*>(arrbuff->getObjectAtIndex(i));
			double timeLimit = dictBuff->valueForKey("time")->doubleValue();
			auto effectString = dictBuff->valueForKey("effects");
			const char* c = effectString->getCString();
			int maxEffects = SimpleBuff::maxMultiplier();
			SimpleBuff::BuffMultiplier mul;
			double* p = (double*)&mul;
			for (int j = 0; j < maxEffects; ++j)
			{
				if (sscanf(c, "%lf", p) != 1)
					break;
				++p;
				while ((*c != ',') && (*c != 0))++c;
				if (*c == ',')++c;
			}
			auto buff = new SimpleBuff(timeLimit, mul);
			buff->setFlag(dictBuff->valueForKey("flag")->uintValue());
			this->pushBuff(buff);
		}
	}

	return true;
}

void SimpleEnemy::update(float delta)
{
	Enemy::update(delta);


}

int SimpleEnemy::maxHP()
{
	return maxhp;
}

int SimpleEnemy::defence()
{
	return def;
}

SimpleEnemy* SimpleEnemy::create(const std::string& type)
{
	SimpleEnemy *pRet = new(std::nothrow) SimpleEnemy(type);
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

void SimpleEnemy::updateBuffState()
{
	Enemy::updateBuffState();

	double playSpeed = calcBuffedValue(&Buff::speed, 1.0);
	walk->setDelayPerUnit(playSpeed < 1e-7 ? INFINITY : 0.05 / playSpeed); 

	aniWalk = Animate::create(walk);

	//aniWalk->retain();

	auto repeatWalk = RepeatForever::create(aniWalk);
	actSprite->stopActionByTag(52013);
	repeatWalk->setTag(52013);
	actSprite->runAction(repeatWalk);

	//aniWalk->release();

}

void SimpleEnemy::onBuffBegin(Buff* buff)
{
	Enemy::onBuffBegin(buff);
	unsigned int flag = buff->getFlag();
	if (flag & BUFF_DIZZY)
	{
		doBuffDizzy();
	}
	if (flag & BUFF_RUSH)
	{
		doBuffRush(true);
	}
	if (flag & BUFF_DEFUP)
	{
		doBuffDef(true);
	}
	if (flag & BUFF_CURED)
	{
		doBuffCured(true);
	}
}

void SimpleEnemy::onBuffEnd(Buff* buff)
{
	Enemy::onBuffEnd(buff);
	unsigned int flag = getBuffFlag();
	if (!(flag & BUFF_RUSH))
	{
		doBuffRush(false);
	}
	if (!(flag & BUFF_DEFUP))
	{
		doBuffDef(false);
	}
	if (!(flag & BUFF_CURED))
	{
		doBuffCured(false);
	}
}

void SimpleEnemy::doBuffDizzy()
{
	frameFly = 0;
	actSprite->schedule([this](float){
		actSprite->setPositionY(0.2 * (frameFly - 10) * (frameFly - 10));
		++frameFly;
	}, 1.0 / 60, 20, 0.0, "fly");
	actSprite->scheduleOnce([this](float){actSprite->setPositionY(-20.0); }, 0.34, "flystop");

	auto dizzy = Sprite::create();
	auto ani = Animation::create();

	char szName[100];
	for (int i = 0; i <= 2; ++i)
	{
		sprintf(szName, "Yun/Dizzy_Buff_%02d.png", i);
		ani->addSpriteFrameWithFile(szName);
	}

	ani->setDelayPerUnit(0.095);
	dizzy->runAction(Sequence::create(
		Repeat::create(Animate::create(ani), 7),
		CallFunc::create([dizzy](){dizzy->removeFromParent(); }),
		nullptr));

	Size s = actSprite->getContentSize();
	dizzy->setPosition(s.width*0.5, s.height);
	dizzy->setScale(0.6);
	//dizzy->setLocalZOrder(10);

	actSprite->addChild(dizzy);
}

void SimpleEnemy::doBuffRush(bool on)
{
	if (!on)
	{
		removeChildByTag(BUFF_TAG_RUSH);
		return;
	}

	if(getChildByTag(BUFF_TAG_RUSH) != nullptr)
		return;

	auto rush = Sprite::create();
	auto ani = Animation::create();

	char szName[100];
	for (int i = 0; i <= 4; ++i)
	{
		sprintf(szName, "Jiasu/Rush_Buff_%02d.png", i);
		ani->addSpriteFrameWithFile(szName);
	}

	ani->setDelayPerUnit(0.16);
	rush->runAction(RepeatForever::create(Animate::create(ani)));
	rush->setScale(0.8, 0.5);
	rush->setOpacity(120);
	rush->setAnchorPoint(Vec2(0.45, 0.4));
	rush->setTag(BUFF_TAG_RUSH);

	this->addChild(rush);
}

void SimpleEnemy::doBuffDef(bool on)
{
	if (!on)
	{
		removeChildByTag(BUFF_TAG_DEF);
		return;
	}

	if (getChildByTag(BUFF_TAG_DEF) != nullptr)
		return;

	auto def = Sprite::create("Jianshang/Jianshang_Buff_00.png");
	def->runAction(RepeatForever::create(Sequence::create(FadeTo::create(1, 130), FadeTo::create(1, 255), nullptr)));
	def->setPositionY(height);
	def->setScale(0.5);
	def->setTag(BUFF_TAG_DEF);

	this->addChild(def);
}

void SimpleEnemy::doBuffCured(bool on)
{
	if (!on)
	{
		removeChildByTag(BUFF_TAG_CURED);
		return;
	}

	if (getChildByTag(BUFF_TAG_CURED) != nullptr)
		return;

	auto cure = Sprite::create();
	auto ani = Animation::create();

	char szName[100];
	for (int i = 0; i <= 24; ++i)
	{
		sprintf(szName, "Jiaxue/Jiaxue_Buff_%02d.png", i);
		ani->addSpriteFrameWithFile(szName);
	}

	ani->setDelayPerUnit(0.05);
	cure->runAction(RepeatForever::create(Animate::create(ani)));
	cure->setScale(1.5);
	//cure->setOpacity(200);
	//cure->setAnchorPoint(Vec2(0.45, 0.4));
	cure->setTag(BUFF_TAG_CURED);

	this->addChild(cure);
}
