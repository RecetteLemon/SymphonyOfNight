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
		SCENEMANAGER->changeScene("Ÿ��Ʋ��");
	}
}
void loadingScene::render()	
{
	_loading->render();
	
}


void loadingScene::loadingImage()
{
	//�̹����߰�
	for (int i = 0; i < 100; i++)
	{
		_loading->loadFrameImage("Ǫ��", "image/item/Food.bmp", 380, 104, 10, 4, true, RGB(255, 0, 255));
	}
	_loading->loadImage("Ÿ��Ʋ���", "image/loading/titleBackground.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("�׽�Ʈ���", "image/Map1.bmp", 416, 714, true, RGB(255, 0, 255));
	
}
void loadingScene::loadingSound()
{
	//�����߰�
	_loading->loadsound("Ÿ��Ʋ����", "sound/titleSound.mp3", true, true);
	


}