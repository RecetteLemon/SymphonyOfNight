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
	SCENEMANAGER->addScene("InventoryScene", new inventoryScene);
	SCENEMANAGER->addScene("ObjTest", new objTest);
	SCENEMANAGER->addScene("CharScene", new characterScene);
	SCENEMANAGER->addScene("FamiliarScene", new familiarScene);
	SCENEMANAGER->addScene("openingScene", new openingScene);
	SCENEMANAGER->addScene("Scene_Map1", new Scene_Map1);
	SCENEMANAGER->addScene("Scene_Map2", new Scene_Map2);
	SCENEMANAGER->addScene("Scene_Map3", new Scene_Map3);
	SCENEMANAGER->addScene("Scene_Map4", new Scene_Map4);
	
	SCENEMANAGER->changeScene("Scene_Map4");

	// �������� �̱���
	
	return S_OK;
}

//�޸� ���� �Լ�
void symphonyOfNight::release(void)
{
	this->deleteImage();
	IMAGEMANAGER->deleteImage("PixelTest");

	gameNode::release();

	

}

//�������ִ� ��
void symphonyOfNight::update(void)
{
	gameNode::update();

	SCENEMANAGER->update();
	EFFECTMANAGER->update();
}

//���Ⱑ �׷��ִ� ��
void symphonyOfNight::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============================================================================
	

	SCENEMANAGER->render();
	
	EFFECTMANAGER->render();

	//================================================================================
	//�ǵ������� �̰ŵ�
	//TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
