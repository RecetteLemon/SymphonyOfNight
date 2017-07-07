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
	_pixelImage = IMAGEMANAGER->findImage("pc_Map4");

	_backImage = IMAGEMANAGER->findImage("backImageSCN4");
	_realBackImage = IMAGEMANAGER->findImage("map4");

	
	_player = new player;
	_player->init(ALUCARD_INFO->getStats().x, ALUCARD_INFO->getStats().y, _pixelImage, false);

	_map = new MapManager;
	_map->init(_backImage, _player);

	_oC = new objectCreate;
	_oC->init(1580, 406, _pixelImage, 2);

	return S_OK;
}
void Scene_Map4::release()
{
	SAFE_DELETE(_map);

	_player->release();
	SAFE_DELETE(_player);

	_oC->release();
	SAFE_DELETE(_oC);
}
void Scene_Map4::update()
{
	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		ALUCARD_INFO->setX(_player->getPlayerPosX());
		ALUCARD_INFO->setY(_player->getPlayerPosY());
		ALUCARD_INFO->setMapDirection(3);
		SCENEMANAGER->changeScene("CharScene");
	}

	if (_player)
	{
		_map->update();
		_player->update();
		_oC->update();
		KEYANIMANAGER->update();

		

		if (_player->getPlayerPosX() < 1890)
		{
			_map->setPosY(0);
		}
	}
}
void Scene_Map4::render()
{
	RECT rc = { _player->getPlayerPosX(), 0, _player->getPlayerPosX() + WINSIZEX, WINSIZEY };
	_realBackImage->render(getFieldDC(), 0, 0);
	_oC->render(getFieldDC());
	_player->render(getFieldDC());
	_map->render();
}
