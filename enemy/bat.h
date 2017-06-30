#pragma once
#include "enemy.h"
class bat : public enemy
{
public:
	HRESULT init();
	void release();
	void update();
	void render();


	// 접근자
	int getBatAtk() { return _enemyInfo.atk; }
	int getBatEXP() { return _enemyInfo.exp; }

	// 설정자
	void setSkeletonHP(int HP) { _enemyInfo.hp = HP; }

	bat();
	~bat();
};

