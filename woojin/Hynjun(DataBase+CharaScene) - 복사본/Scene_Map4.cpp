#include "stdafx.h"
#include "Scene_Map4.h"


Scene_Map4::Scene_Map4()
{
}


Scene_Map4::~Scene_Map4()
{
}

HRESULT Scene_Map4::init(void)
{
	//pc_Map1 : pixel collision_map1 ÀÇ¹ÌÀÓ
	_pixelImage = IMAGEMANAGER->addImage("pc_Map4", "image/BossMap_C.bmp", 2784, 1200, true, RGB(255, 0, 255));

	_backImage = IMAGEMANAGER->addImage("backImageSCN4", "backImage.bmp", 2784, 1200, false, RGB(255, 0, 255));
	_realBackImage = IMAGEMANAGER->addImage("map4", "image/BossMap.bmp", 2784, 1200, true, RGB(255, 0, 255));

	_player = new player;
	_player->init(2762, 854, _pixelImage, false);

	_map = new MapManager;
	_map->init(_backImage, _player);

	return S_OK;
}
void Scene_Map4::release()
{
	SAFE_DELETE(_map);

	_player->release();
	SAFE_DELETE(_player);

	IMAGEMANAGER->deleteImage("pc_Map4");
	IMAGEMANAGER->deleteImage("backImageSCN4");
	IMAGEMANAGER->deleteImage("map4");

	_backImage = NULL;
	_realBackImage = NULL;
}
void Scene_Map4::update()
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

	if (_player->getPlayerPosX() < 1890)
	{
		_map->setPosY(0);
	}
	/*if ((_player->getPlayerPosX() > 0 && _player->getPlayerPosX() < 100) &&
	(_player->getPlayerPosY() > 150 && _player->getPlayerPosY() < 212))
	{
	SCENEMANAGER->changeScene("Scene_Map4");
	}*/
}
void Scene_Map4::render()
{
	RECT rc = { _player->getPlayerPosX(), 0, _player->getPlayerPosX() + WINSIZEX, WINSIZEY };
	_realBackImage->render(getFieldDC(), 0, 0);
	_player->render(getFieldDC());
	_map->render();
}
