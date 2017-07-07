#pragma once
#include "gameNode.h"
#include "player.h"
#include "MapManager.h"
#include "objectCreate.h"

class Scene_Map4 : public gameNode
{
private:
	MapManager* _map;
	player* _player;
	objectCreate* _oC;

	image* _pixelImage;
	image* _backImage;
	image* _realBackImage;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	HDC getFieldDC(void) { return _backImage->getMemDC(); }

	Scene_Map4();
	virtual ~Scene_Map4();
};

