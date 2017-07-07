#pragma once
#include "gameNode.h"

#include "Dracula.h"
#include "bat.h"
#include "bloodskeleton.h"
#include "hosuk.h"
#include <vector>


class enemyManager : public gameNode
{
private:
	vector<enemy*> _vEnemy;
	vector<enemy*>::iterator _viEnemy;

private:
	enemy* _enemy;


public:
	// 자유로운 몹들
	HRESULT init(const char* imageName, float x, float y, float moveRange, int kind);
	void release();
	void update();
	void render();

	enemyManager();
	~enemyManager();
};

