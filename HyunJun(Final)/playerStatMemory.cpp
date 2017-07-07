#include "stdafx.h"
#include "playerStatMemory.h"


playerStatMemory::playerStatMemory()
{
	_alucardStat.HP = 125;
	_alucardStat.HPMax = 125;
	_alucardStat.heart = 100;
	_alucardStat.str = 0;
	_alucardStat.con = 0;
	_alucardStat.int_ = 0;
	_alucardStat.lck = 0;
	_alucardStat.gold = 0;
	_alucardStat.atk = 0;
	_alucardStat.def = 0;
	_alucardStat.familiar = 3;

	_alucardStat.saveStr = 3;
	_alucardStat.saveCon = 3;
	_alucardStat.saveInt = 3;
	_alucardStat.saveLck = 3;
}


playerStatMemory::~playerStatMemory()
{
}

void playerStatMemory::statUpdate()
{
	int tempAtk = 0, tempDef = 0;
	int tempStr = 0, tempCon = 0, tempInt = 0, tempLck = 0;

	if (ALUCARD->getValucard().size() > 0)
	{
		for (int i = 0; i < ALUCARD->getValucard().size(); i++)
		{
			tempAtk += ALUCARD->getValucard()[i].atk_;
			tempDef += ALUCARD->getValucard()[i].def_;
			tempStr += ALUCARD->getValucard()[i].str_;
			tempCon += ALUCARD->getValucard()[i].con_;
			tempInt += ALUCARD->getValucard()[i].int_;
			tempLck += ALUCARD->getValucard()[i].lck_;
		}
	}

	_alucardStat.str = tempStr + _alucardStat.saveStr;
	_alucardStat.con = tempCon + _alucardStat.saveCon;
	_alucardStat.int_ = tempInt + _alucardStat.saveInt;
	_alucardStat.lck = tempLck + _alucardStat.saveLck;

	_alucardStat.HPMax = _alucardStat.con * 20 + _alucardStat.str * 5;
	_alucardStat.atk = _alucardStat.str * 3 + _alucardStat.con * 2 + tempAtk;
	_alucardStat.def = _alucardStat.lck * 2 + _alucardStat.int_ + tempDef;
	

	if (_alucardStat.HP > _alucardStat.HPMax)  _alucardStat.HP = _alucardStat.HPMax;
}