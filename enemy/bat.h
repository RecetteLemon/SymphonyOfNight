#pragma once
#include "enemy.h"
class bat : public enemy
{
public:
	HRESULT init();
	void release();
	void update();
	void render();


	// ������
	int getBatAtk() { return _enemyInfo.atk; }
	int getBatEXP() { return _enemyInfo.exp; }

	// ������
	void setSkeletonHP(int HP) { _enemyInfo.hp = HP; }

	bat();
	~bat();
};

