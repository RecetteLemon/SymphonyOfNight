#include "stdafx.h"
#include "Scene_Map3.h"


Scene_Map3::Scene_Map3()
{
}


Scene_Map3::~Scene_Map3()
{
}

HRESULT Scene_Map3::init(void)
{
	//pc_Map1 : pixel collision_map1 ÀÇ¹ÌÀÓ
	_pixelImage = IMAGEMANAGER->addImage("pc_Map3", "image/Map3_C.bmp", 800, 1923, true, RGB(255, 0, 255));

	_backImage = IMAGEMANAGER->addImage("backImageSCN3", "backImage.bmp", 800, 1923, false, RGB(255, 0, 255));
	_realBackImage = IMAGEMANAGER->addImage("map3", "image/Map3.bmp", 800, 1923, true, RGB(255, 0, 255));

	_player = new player;
	_player->init(ALUCARD_INFO->getStats().x, ALUCARD_INFO->getStats().y, _pixelImage, false);

	_map = new MapManager;
	_map->init(_backImage, _player);

	return S_OK;
}
void Scene_Map3::release()
{
	SAFE_DELETE(_map);

	_player->release();
	SAFE_DELETE(_player);
}
void Scene_Map3::update()
{
	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		ALUCARD_INFO->setX(_player->getPlayerPosX());
		ALUCARD_INFO->setY(_player->getPlayerPosY());
		ALUCARD_INFO->setMapDirection(2);
		SCENEMANAGER->changeScene("CharScene");
	}

	if (_player)
	{
		_map->update();
		_player->update();
		KEYANIMANAGER->update();

		if ((_player->getPlayerPosX() > 0 && _player->getPlayerPosX() < 100) &&
			(_player->getPlayerPosY() > 150 && _player->getPlayerPosY() < 212))
		{
			ALUCARD_INFO->setX(2762);
			ALUCARD_INFO->setY(854);
			SCENEMANAGER->changeScene("Scene_Map4");
		}
	}
}
void Scene_Map3::render()
{
	RECT rc = { _player->getPlayerPosX(), 0, _player->getPlayerPosX() + WINSIZEX, WINSIZEY };
	_realBackImage->render(getFieldDC(), 0, 0);
	_player->render(getFieldDC());
	_map->render();
}
