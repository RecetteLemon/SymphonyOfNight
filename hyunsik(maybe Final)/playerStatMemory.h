#pragma once
#include "singletonBase.h"

struct ALUCARD_STATS
{
	int HP;
	int HPMax;
	int heart;
	int str;
	int con;
	int int_;
	int lck;
	int gold;
	int atk;
	int def;
	int familiar;
};

class playerStatMemory : public singletonBase<playerStatMemory>
{
private:

	ALUCARD_STATS _alucardStat;

	

public:

	ALUCARD_STATS getStats() { return _alucardStat; }

	void setHP(int hp) { _alucardStat.HP = hp; }
	void setHPMax(int hpMax) { _alucardStat.HPMax = hpMax; }
	void setHeart(int heart) { _alucardStat.heart = heart; }
	void setStr(int str) { _alucardStat.str = str; }
	void setCon(int con) { _alucardStat.con = con; }
	void setInt(int int_) { _alucardStat.int_ = int_; }
	void setLck(int lck) { _alucardStat.lck = lck; }
	void setGold(int gold) { _alucardStat.gold = gold; }
	void setAtk(int atk) { _alucardStat.atk = atk; }
	void setDef(int def) { _alucardStat.def = def; }
	void setFamiliar(int fm) { _alucardStat.familiar = fm; }

	void statUpdate();
	playerStatMemory();
	~playerStatMemory();
};

