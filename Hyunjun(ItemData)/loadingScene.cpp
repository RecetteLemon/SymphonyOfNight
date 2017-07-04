#include "stdafx.h"
#include "loadingScene.h"


loadingScene::loadingScene()
{
}


loadingScene::~loadingScene()
{
}


HRESULT loadingScene::init()
{
	_loading = new loading;
	_loading->init();

	this->loadingImage();
	this->loadingSound();

	return S_OK;
}
void loadingScene::release()
{
	_loading->release();
	safeDelete(_loading);
}
void loadingScene::update()	
{
	_loading->update();

	if (_loading->loadingDone())
	{
		SCENEMANAGER->changeScene("TitleScene");
	}
}
void loadingScene::render()	
{
	_loading->render();
	
}


void loadingScene::loadingImage()
{
	_loading->loadImage("TitleBackground", "Image/Loading/titleBackground.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Start", "Image/Loading/Start.bmp", 712, 21, 2, 1, true, RGB(255, 0, 255));
	_loading->loadImage("InventoryUI", "Image/Inventory/InventoryUI.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));

	_loading->loadImage("PixelTest", "Image/pixelTest.bmp", 800, 800, false, RGB(255, 0, 255));
	this->addItemImage();
	
}
void loadingScene::loadingSound()
{
	//사운드추가
	
	_loading->loadsound("TitleSound", "Sound/titleSound.mp3", true, true);
}



void loadingScene::addItemImage()
{
	

}