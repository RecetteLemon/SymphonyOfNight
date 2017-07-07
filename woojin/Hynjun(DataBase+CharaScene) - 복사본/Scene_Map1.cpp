#include "stdafx.h"
#include "Scene_Map1.h"

Scene_Map1::Scene_Map1()
{
}


Scene_Map1::~Scene_Map1()
{
}

HRESULT Scene_Map1::init(void)
{
	//pc_Map1 : pixel collision_map1 ÀÇ¹ÌÀÓ
	_castle = IMAGEMANAGER->addImage("castle", "Image/Background2-1.bmp", 800, 322, true, RGB(255, 0, 255));
	_cloud = IMAGEMANAGER->addImage("cloud", "introImage/backGround1.bmp", 2400, 1800, true, RGB(255, 0, 255));
	_pixelImage = IMAGEMANAGER->addImage("pc_Map1", "image/Map1_C.bmp", 800, 1373, true, RGB(255, 0, 255));

	_backImage = IMAGEMANAGER->addImage("backImageSCN1", "backImage.bmp", 800, 1373, false, RGB(255, 0, 255));
	_realBackImage = IMAGEMANAGER->addImage("map1", "image/Map1-1.bmp", 800, 1373, true, RGB(255, 0, 255));

	ALUCARD_INFO->setX(10);
	ALUCARD_INFO->setY(1246);

	_player = new player;
	_player->init(ALUCARD_INFO->getStats().x, ALUCARD_INFO->getStats().y, _pixelImage, false);

	_map = new MapManager;
	_map->init(_backImage, _player);

	

	return S_OK;
}
void Scene_Map1::release()
{
	SAFE_DELETE(_map);

	_player->release();
	SAFE_DELETE(_player);


}
void Scene_Map1::update()
{
	_map->update();
	_player->update();
	
	KEYANIMANAGER->update();

	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		ALUCARD_INFO->setX(_player->getPlayerPosX());
		ALUCARD_INFO->setY(_player->getPlayerPosY());
		ALUCARD_INFO->setMapDirection(0);
		SCENEMANAGER->changeScene("CharScene");
	}

	if ((_player->getPlayerPosX() > 650 && _player->getPlayerPosX() < 800) &&
		(_player->getPlayerPosY() > 1230 && _player->getPlayerPosY() < 1246))
	{
		ALUCARD_INFO->setX(10);
		ALUCARD_INFO->setY(394);
		SCENEMANAGER->changeScene("Scene_Map2");
	}
}
void Scene_Map1::render()
{
	_cloud->render(getFieldDC(), 0, 0);
	_castle->render(getFieldDC(), 0, 924);
	_realBackImage->render(getFieldDC(), 0, 0);
	_player->render(getFieldDC());
	
	_map->render();
}