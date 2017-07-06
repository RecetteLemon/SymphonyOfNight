#include "stdafx.h"
#include "Scene_Map2.h"


Scene_Map2::Scene_Map2()
{
}


Scene_Map2::~Scene_Map2()
{
}

HRESULT Scene_Map2::init(void)
{
	_pixelImage = IMAGEMANAGER->addImage("pc_Map2", "image/Map2_C.bmp", 5194, 600, true, RGB(255, 0, 255));

	_backImage = IMAGEMANAGER->addImage("backImageSCN2", "backImage.bmp", 5194, 600, false, RGB(255, 0, 255));
	_realBackImage = IMAGEMANAGER->addImage("map2", "image/Map2.bmp", 5194, 600, true, RGB(255, 0, 255));

	_player = new player;
	_player->init(10, 394, _pixelImage, false);

	_map = new MapManager;
	_map->init(_backImage, _player);

	return S_OK;
}
void Scene_Map2::release()
{
	SAFE_DELETE(_map);

	_player->release();
	SAFE_DELETE(_player);

	IMAGEMANAGER->deleteImage("pc_Map2");
	IMAGEMANAGER->deleteImage("backImageSCN2");
	IMAGEMANAGER->deleteImage("map2");

	_backImage = NULL;
	_realBackImage = NULL;
}
void Scene_Map2::update()
{
	_map->update();
	_player->update();
	KEYANIMANAGER->update();

	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		//ALUCARD_INFO->setX(_x);
		//ALUCARD_INFO->setY(_y);
		SCENEMANAGER->changeScene("CharScene");
	}

	if ((_player->getPlayerPosX() > 5055 && _player->getPlayerPosX() < 5194) &&
		(_player->getPlayerPosY() > 300 && _player->getPlayerPosY() < 394))
	{
		SCENEMANAGER->changeScene("Scene_Map3");
	}
}
void Scene_Map2::render()
{
	RECT rc = { _player->getPlayerPosX(), 0, _player->getPlayerPosX() + WINSIZEX, WINSIZEY };
	_realBackImage->render(getFieldDC(), 0, 0);
	_player->render(getFieldDC());
	_map->render();
}