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

	ALUCARD_INFO->statUpdate();
}

void characterScene::render(void) 
{
	IMAGEMANAGER->findImage("characterBackground")->render(getMemDC(), 0, 0);

	
	Rectangle(getMemDC(), _selectRC.left, _selectRC.top, _selectRC.right, _selectRC.bottom);
	IMAGEMANAGER->findImage("character_select")->render(getMemDC(), _selectRC.left, _selectRC.top);
	IMAGEMANAGER->findImage("invenfont")->render(getMemDC(), _menuRC[0].left - 2, _menuRC[0].top - 5);
	IMAGEMANAGER->findImage("familiarfont")->render(getMemDC(), _menuRC[1].left-2,_menuRC[1].top-5);
	


	//350 , 100



	char str[128];
	HFONT font, oldFont;
	font = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "°íµñ");
	oldFont = (HFONT)SelectObject(getMemDC(), font);

	SetTextColor(getMemDC(), RGB(255, 255, 255));
	SetBkMode(getMemDC(), TRANSPARENT);

	/*sprintf(str, "x : %d", _ptMouse.x);
	TextOut(getMemDC(), WINSIZEX - 100, WINSIZEY - 170, str, strlen(str));

	sprintf(str, "y : %d", _ptMouse.y);
	TextOut(getMemDC(), WINSIZEX - 100, WINSIZEY -150, str, strlen(str));*/


	sprintf(str, " %d", ALUCARD_INFO->getStats().HP);
	TextOut(getMemDC(), 310, 95, str, strlen(str));

	sprintf(str, " %d", ALUCARD_INFO->getStats().HPMax);
	TextOut(getMemDC(), 430, 95, str, strlen(str));

	sprintf(str, " %d", ALUCARD_INFO->getStats().heart);
	TextOut(getMemDC(), 380, 165, str, strlen(str));

	sprintf(str, " %d", ALUCARD_INFO->getStats().atk);
	TextOut(getMemDC(), 685, 200, str, strlen(str));

	sprintf(str, " %d", ALUCARD_INFO->getStats().def);
	TextOut(getMemDC(), 685, 260, str, strlen(str));

	sprintf(str, " %d", ALUCARD_INFO->getStats().str);
	TextOut(getMemDC(), 200, 285, str, strlen(str));

	sprintf(str, " %d", ALUCARD_INFO->getStats().con);
	TextOut(getMemDC(), 200, 320, str, strlen(str));

	sprintf(str, " %d", ALUCARD_INFO->getStats().int_);
	TextOut(getMemDC(), 200, 355, str, strlen(str));

	sprintf(str, " %d", ALUCARD_INFO->getStats().lck);
	TextOut(getMemDC(), 200, 390, str, strlen(str));

	DeleteObject(SelectObject(getMemDC(), oldFont));
}