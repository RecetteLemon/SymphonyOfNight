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
	SAFE_DELETE(_loading);
}
void loadingScene::update()	
{
	_loading->update();

	if (_loading->loadingDone())
	{
		SCENEMANAGER->changeScene("타이틀씬");
	}
}
void loadingScene::render()	
{
	_loading->render();
	
}


void loadingScene::loadingImage()
{
	//이미지추가
	for (int i = 0; i < 100; i++)
	{
		_loading->loadFrameImage("푸드", "image/item/Food.bmp", 380, 104, 10, 4, true, RGB(255, 0, 255));
	}
	_loading->loadImage("타이틀배경", "image/loading/titleBackground.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("테스트배경", "image/Map1.bmp", 416, 714, true, RGB(255, 0, 255));
	
}
void loadingScene::loadingSound()
{
	//사운드추가
	_loading->loadsound("타이틀사운드", "sound/titleSound.mp3", true, true);
	


}