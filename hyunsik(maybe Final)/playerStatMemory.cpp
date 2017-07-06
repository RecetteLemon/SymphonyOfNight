#include "stdafx.h"
#include "playerStatMemory.h"


playerStatMemory::playerStatMemory()
{
	_alucardStat.HP = 125;
	_alucardStat.HPMax = 125;
	_alucardStat.heart = 100;
	_alucardStat.str = 5;
	_alucardStat.con = 5;
	_alucardStat.int_ = 5;
	_alucardStat.lck = 5;
	_alucardStat.gold = 0;
	_alucardStat.atk = 0;
	_alucardStat.def = 0;
	_alucardStat.familiar = 3;
	_alucardStat.x = 0;
	_alucardStat.y = 0;
}


playerStatMemory::~playerStatMemory()
{
}

void playerStatMemory::statUpdate()
{
	_alucardStat.HPMax = _alucardStat.con * 20 + _alucardStat.str * 5;
	_alucardStat.atk = _alucardStat.str * 3 + _alucardStat.con * 2;
	_alucardStat.def = _alucardStat.lck * 2 + _alucardStat.int_;
}