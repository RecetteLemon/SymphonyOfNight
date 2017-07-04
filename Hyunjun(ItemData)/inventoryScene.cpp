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

	return S_OK;
}

void inventoryScene::release(void)
{
	_invenUIImg = NULL;
}

void inventoryScene::update(void)
{

}

void inventoryScene::render(void)
{
	_invenUIImg->render(getMemDC(), 0, 0);
}
