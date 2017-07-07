#include "stdafx.h"
#include "titleScene.h"


titleScene::titleScene()
{
}


titleScene::~titleScene()
{
}



HRESULT titleScene::init()
{

	_image = IMAGEMANAGER->findImage("Start");
	

	SOUNDMANAGER->play("TitleSound",0.3f);


	_start = new animation;
	_start->init(_image->getWidth(), _image->getHeight(), _image->getFrameWidth(), _image->getFrameHeight());
	_start->setDefPlayFrame(false, true);
	_start->setFPS(1);
	_start->start();


	return S_OK;
}
void titleScene::release()
{
	safeDelete(_start);
	IMAGEMANAGER->deleteImage("TitleBackground");
	IMAGEMANAGER->deleteImage("Start");
	_image = NULL;
}
void titleScene::update() 
{
	_start->frameUpdate(TIMEMANAGER->getElapsedTime() * 3);

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		//°ÔÀÓ¾ÀÃß°¡
		SOUNDMANAGER->stop("TitleSound");
		SCENEMANAGER->changeScene("CharScene");
	}
	
	

}
void titleScene::render() 
{
	IMAGEMANAGER->findImage("TitleBackground")->render(getMemDC(), 0, 0);
	_image->aniRender(getMemDC(), WINSIZEX / 2 - 170, WINSIZEY / 2 + 150, _start);

	
		
}