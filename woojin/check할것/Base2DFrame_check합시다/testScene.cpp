#include "stdafx.h"
#include "testScene.h"


testScene::testScene()
{
}


testScene::~testScene()
{
}

HRESULT testScene::init()
{
	IMAGEMANAGER->addImage("map", "image/Map3_C.bmp", 512 * 2, 1231 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("map2", "image/Map3.bmp", 512 * 2, 1231 * 2, true, RGB(255, 0, 255));

	/*_player = new player;
	_player->init(WINSIZEX / 2, WINSIZEY / 2, "map");
*/
	return S_OK;
}

void testScene::release()
{

}

void testScene::update() 
{
	//_player->update();

}

void testScene::render() 
{
	IMAGEMANAGER->findImage("map")->render(getMemDC(), 0, 0);
	IMAGEMANAGER->findImage("map2")->render(getMemDC(), 0, 0);

//	_player->render();
}
