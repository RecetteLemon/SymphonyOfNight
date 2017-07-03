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

	_image = IMAGEMANAGER->addFrameImage("스타트버튼", "image/loading/start.bmp", 712, 21, 2, 1, true, RGB(255, 0, 255));
	

	SOUNDMANAGER->play("타이틀사운드",0.3f);


	_start = new animation;
	_start->init(_image->getWidth(), _image->getHeight(), _image->getFrameWidth(), _image->getFrameHeight());
	_start->setDefPlayFrame(false, true);
	_start->setFPS(1);
	_start->start();


	return S_OK;
}
void titleScene::release()
{

}
void titleScene::update() 
{
	_start->frameUpdate(TIMEMANAGER->getElapsedTime() * 3);

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		//게임씬추가
		SOUNDMANAGER->stop("타이틀사운드");
		SCENEMANAGER->changeScene("테스트씬");
	}
	
	

}
void titleScene::render() 
{
	IMAGEMANAGER->findImage("타이틀배경")->render(getMemDC(), 0, 0);
	_image->aniRender(getMemDC(), WINSIZEX / 2 - 170, WINSIZEY / 2 + 150, _start);

}