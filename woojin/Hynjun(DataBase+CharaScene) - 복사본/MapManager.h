#pragma once
#include "gameNode.h"
#include "player.h"

class MapManager : public gameNode
{
private:
	image* _fieldImage;
	player* _player;

	RECT _rc;

public:
	HRESULT init(image* img, player* player);
	void release();
	void update();
	void render();

	void setPosY(float y);

	MapManager();
	~MapManager();
};

