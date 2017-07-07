#pragma once
#include "gameNode.h"
#include "player.h"
#include "MapManager.h"

class Scene_Map2 : public gameNode
{
private:
	MapManager* _map;
	player* _player;

	image* _pixelImage;
	image* _backImage;
	image* _realBackImage;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	HDC getFieldDC(void) { return _backImage->getMemDC(); }

	Scene_Map2();
	~Scene_Map2();
};

