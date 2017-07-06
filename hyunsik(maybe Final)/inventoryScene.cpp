#include "stdafx.h"
#include "inventoryScene.h"


inventoryScene::inventoryScene()
{
}


inventoryScene::~inventoryScene()
{
}

HRESULT inventoryScene::init(void)
{
	_invenUIImg = IMAGEMANAGER->findImage("InventoryUI");
	


	_hs = new hosuk;
	_hs->init("È£¼®", WINSIZEX / 2, WINSIZEY / 2);


	_sceneName;
	return S_OK;
}

void inventoryScene::release(void)
{
	_invenUIImg = NULL;
}

void inventoryScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		EFFECTMANAGER->play("one_Hand_Effect", WINSIZEX /2 , WINSIZEY /2 );
	}
	if (KEYMANAGER->isOnceKeyDown('T'))
	{
		EFFECTMANAGER->play("dagger_Effect", WINSIZEX / 2, WINSIZEY / 2);
	}
	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		EFFECTMANAGER->play("boss_Effect", WINSIZEX / 2, WINSIZEY / 2);
	}
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		EFFECTMANAGER->play("die", WINSIZEX / 2, WINSIZEY / 2);
	}
	EFFECTMANAGER->update();
	_hs->update();

	
}

void inventoryScene::render(void)
{
	//_invenUIImg->render(getMemDC(), 0, 0);
	//IMAGEMANAGER->findImage("½ÇÇè¸Ê")->render(getMemDC(), 0, 0);

	EFFECTMANAGER->render();
	_hs->render();
	
}
