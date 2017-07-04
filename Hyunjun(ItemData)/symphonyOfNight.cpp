#include "stdafx.h"
#include "symphonyOfNight.h"


symphonyOfNight::symphonyOfNight()
{
}


symphonyOfNight::~symphonyOfNight()
{
}

//�ʱ�ȭ ���ִ� �Լ�
HRESULT symphonyOfNight::init(void)
{
	gameNode::init(true);
	
	SCENEMANAGER->addScene("LoadingScene", new loadingScene);
	SCENEMANAGER->addScene("TitleScene", new titleScene);
	SCENEMANAGER->addScene("ObjTest", new objTest);
	
	SCENEMANAGER->changeScene("LoadingScene");
	return S_OK;
}

//�޸� ���� �Լ�
void symphonyOfNight::release(void)
{
	IMAGEMANAGER->deleteImage("PixelTest");

	gameNode::release();

	

}

//�������ִ� ��
void symphonyOfNight::update(void)
{
	gameNode::update();

	SCENEMANAGER->update();
}

//���Ⱑ �׷��ִ� ��
void symphonyOfNight::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============================================================================
	

	SCENEMANAGER->render();
	

	//================================================================================
	//�ǵ������� �̰ŵ�
	TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
