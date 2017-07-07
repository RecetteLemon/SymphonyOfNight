#include "stdafx.h"
#include "symphonyOfNight.h"


symphonyOfNight::symphonyOfNight()
{
}


symphonyOfNight::~symphonyOfNight()
{
}

//초기화 해주는 함수
HRESULT symphonyOfNight::init(void)
{
	gameNode::init(true);
	

	SCENEMANAGER->addScene("LoadingScene", new loadingScene);
	SCENEMANAGER->addScene("TitleScene", new titleScene);
	SCENEMANAGER->addScene("InventoryScene", new inventoryScene);
	SCENEMANAGER->addScene("ObjTest", new objTest);
	SCENEMANAGER->addScene("CharScene", new characterScene);
	SCENEMANAGER->addScene("FamiliarScene", new familiarScene);
	
	SCENEMANAGER->changeScene("LoadingScene");

	// 게임전용 싱글톤
	
	return S_OK;
}

//메모리 해제 함수
void symphonyOfNight::release(void)
{
	this->deleteImage();
	IMAGEMANAGER->deleteImage("PixelTest");

	gameNode::release();

	

}

//연산해주는 곳
void symphonyOfNight::update(void)
{
	gameNode::update();

	SCENEMANAGER->update();
	EFFECTMANAGER->update();
}

//여기가 그려주는 곳
void symphonyOfNight::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============================================================================
	

	SCENEMANAGER->render();
	
	EFFECTMANAGER->render();

	//================================================================================
	//건들지마라 이거도
	//TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
