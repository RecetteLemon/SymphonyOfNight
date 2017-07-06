#include "stdafx.h"
#include "characterScene.h"


characterScene::characterScene()
{
}


characterScene::~characterScene()
{
}


HRESULT characterScene::init(void)
{
	_menuX =  WINSIZEX / 2 + 13;
	_selectX = WINSIZEX / 2 + 13;
	_menu1Y = WINSIZEY / 2 - 20;
	_selectY = WINSIZEY / 2 - 20;
	_menu2Y = WINSIZEY / 2 - 20 + 43;


	_menuRC[0] = RectMakeCenter(_menuX ,_menu1Y , 100, 30);
	_menuRC[1] = RectMakeCenter(_menuX, _menu2Y , 100, 30);
	_selectRC = RectMakeCenter(_selectX, _selectY, 105, 5);
	
	_down = false;
	return S_OK;
}
void characterScene::release(void)
{


}
void characterScene::update(void) 
{
	RECT temp;
	if (IntersectRect(&temp, &_selectRC, &_menuRC[0]) &&KEYMANAGER->isOnceKeyDown(VK_DOWN))_selectY = _menu2Y;
	if (IntersectRect(&temp, &_selectRC, &_menuRC[1]) && KEYMANAGER->isOnceKeyDown(VK_UP))_selectY = _menu1Y;
	if (IntersectRect(&temp, &_selectRC, &_menuRC[0]) && KEYMANAGER->isOnceKeyDown(VK_UP))_selectY = _menu2Y;
	if (IntersectRect(&temp, &_selectRC, &_menuRC[1]) && KEYMANAGER->isOnceKeyDown(VK_DOWN))_selectY = _menu1Y;
	if (IntersectRect(&temp, &_selectRC, &_menuRC[0]) && KEYMANAGER->isOnceKeyDown(VK_SPACE)) SCENEMANAGER->changeScene("InventoryScene");
	if (IntersectRect(&temp, &_selectRC, &_menuRC[1]) && KEYMANAGER->isOnceKeyDown(VK_SPACE)) SCENEMANAGER->changeScene("FamiliarScene");

	_selectRC = RectMakeCenter(_selectX, _selectY, 105, 45);
}

void characterScene::render(void) 
{
	IMAGEMANAGER->findImage("characterBackground")->render(getMemDC(), 0, 0);
	for (int i = 0; i < 2; i++)
	{
		//Rectangle(getMemDC(), _menuRC[i].left, _menuRC[i].top, _menuRC[i].right, _menuRC[i].bottom);
	}
	Rectangle(getMemDC(), _selectRC.left, _selectRC.top, _selectRC.right, _selectRC.bottom);
	IMAGEMANAGER->findImage("character_select")->render(getMemDC(), _selectRC.left, _selectRC.top);
	IMAGEMANAGER->findImage("invenfont")->render(getMemDC(), _menuRC[0].left - 2, _menuRC[0].top - 5);
	IMAGEMANAGER->findImage("familiarfont")->render(getMemDC(), _menuRC[1].left-2,_menuRC[1].top-5);
}