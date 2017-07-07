#pragma once
#include "gameNode.h"
#include "player.h"
#include "UI.h"

class MapManager : public gameNode
{
private:
	image* _fieldImage;
	player* _player;
	UI* _UI;

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

