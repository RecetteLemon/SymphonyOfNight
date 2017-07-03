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

	_image = IMAGEMANAGER->addFrameImage("��ŸƮ��ư", "image/loading/start.bmp", 712, 21, 2, 1, true, RGB(255, 0, 255));
	

	SOUNDMANAGER->play("Ÿ��Ʋ����",0.3f);


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
		//���Ӿ��߰�
		SOUNDMANAGER->stop("Ÿ��Ʋ����");
		SCENEMANAGER->changeScene("�׽�Ʈ��");
	}
	
	

}
void titleScene::render() 
{
	IMAGEMANAGER->findImage("Ÿ��Ʋ���")->render(getMemDC(), 0, 0);
	_image->aniRender(getMemDC(), WINSIZEX / 2 - 170, WINSIZEY / 2 + 150, _start);

}