#pragma once
#include "gameNode.h"
#include "player.h"


class testScene : public gameNode
{
private:
	player* _player;
	player* _player2;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	testScene();
	~testScene();
};

