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
	_pixelImage = IMAGEMANAGER->addImage("pc_Map1", "image/Map1_C.bmp", 800, 1373, true, RGB(255, 0, 255));

	_backImage = IMAGEMANAGER->addImage("backImageSCN1", "backImage.bmp", 800, 1373, false, RGB(255, 0, 255));
	_realBackImage = IMAGEMANAGER->addImage("map1", "image/Map1.bmp", 800, 1373, false, RGB(255, 0, 255));

	_player = new player;
	_player->init(10, 1246, _pixelImage, false);

	_map = new MapManager;
	_map->init(_backImage, _player);

	return S_OK;
}
void Scene_Map1::release()
{
	SAFE_DELETE(_map);

	_player->release();
	SAFE_DELETE(_player);

	IMAGEMANAGER->deleteImage("pc_Map1");
	IMAGEMANAGER->deleteImage("backImageSCN1");
	IMAGEMANAGER->deleteImage("map1");

	_backImage = NULL;
	_realBackImage = NULL;
}
void Scene_Map1::update()
{
	_map->update();
	_player->update();
	KEYANIMANAGER->update();
}
void Scene_Map1::render()
{
	_realBackImage->render(getFieldDC(), 0, 0);
	_player->render(getFieldDC());
	_map->render();
}