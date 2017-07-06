#include "stdafx.h"
#include "familiarScene.h"


familiarScene::familiarScene()
{
}


familiarScene::~familiarScene()
{
}

HRESULT familiarScene::init(void)
{
	_demon.image = IMAGEMANAGER->findImage("on_off");
	_fairy.image = IMAGEMANAGER->findImage("on_off1");
	_ghost.image = IMAGEMANAGER->findImage("on_off2");
	
	_x = 100;
	_y = 150;

	_demon.kind = 0;
	_fairy.kind = 1;
	_ghost.kind = 2;
	_unkown1 = 3;
	
	_demon.x = _ghost.x = 550;
	_fairy.x = 100;
	_fairy.y = _ghost.y = 350;
	_demon.y = 150;

	_selectX = 100;
	_selectY = 150;

	_demon.rc = RectMake(_demon.x, _demon.y, 200, 50);
	_fairy.rc = RectMake(_fairy.x, _fairy.y, 200, 50);
	_ghost.rc = RectMake(_ghost.x, _ghost.y, 200, 50);

	_demon.on = false;
	_fairy.on = false;
	_ghost.on = false;
	_on = false;

	_kind = ALUCARD_INFO->getStats().familiar;

	if (_kind == 0)
	{
		_demon.on = true;
		_fairy.on = false;
		_ghost.on = false;
	}
	if (_kind == 1)
	{
		_demon.on = false;
		_fairy.on = true;
		_ghost.on = false;
	}
	if (_kind == 2)
	{
		_demon.on = false;
		_fairy.on = false;
		_ghost.on = true;
	}
	if (_kind == 3)
	{
		_demon.on = false;
		_fairy.on = false;
		_ghost.on = false;
		_on = true;
	}
	_selectRC = RectMakeCenter(_selectX, _selectY, 250, 50);
	
	_unkown = RectMake(100, 150, 200, 50);

	return S_OK;
}
void familiarScene::release(void)
{
	
	

}
void familiarScene::update(void) 
{
	if (_selectX > 100 && KEYMANAGER->isOnceKeyDown(VK_LEFT))_selectX -= 450;
	if (_selectX < 550 && KEYMANAGER->isOnceKeyDown(VK_RIGHT))_selectX += 450;
	if (_selectY > 150 && KEYMANAGER->isOnceKeyDown(VK_UP))_selectY -= 200;
	if (_selectY < 350 && KEYMANAGER->isOnceKeyDown(VK_DOWN))_selectY += 200;

	if (!_demon.on) _demon.image->setFrameX(0);
	else
	{
		_demon.image->setFrameX(1);
		_fairy.image->setFrameX(0);
		_ghost.image->setFrameX(0);
	}
	if (!_fairy.on) _fairy.image->setFrameX(0);
	else
	{
		_demon.image->setFrameX(0);
		_fairy.image->setFrameX(1);
		_ghost.image->setFrameX(0);
	}
	if (!_ghost.on)_ghost.image->setFrameX(0);
	else
	{
		_demon.image->setFrameX(0);
		_fairy.image->setFrameX(0);
		_ghost.image->setFrameX(1);
	}

	RECT tp;
	if (IntersectRect(&tp,&_selectRC,&_demon.rc) && !_demon.on &&KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_demon.on = true;
		_fairy.on = _ghost.on = false;
		ALUCARD_INFO->setFamiliar(0);
	}
	else if (IntersectRect(&tp, &_selectRC, &_demon.rc) && _demon.on &&KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_demon.on = false;
		ALUCARD_INFO->setFamiliar(3);
	}

	if (IntersectRect(&tp, &_selectRC, &_fairy.rc)&&!_fairy.on && KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{

		_fairy.on = true;
		_demon.on = _ghost.on = false;
		ALUCARD_INFO->setFamiliar(1);
	}
	else if (IntersectRect(&tp, &_selectRC, &_fairy.rc) && _fairy.on && KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_fairy.on = false;
		ALUCARD_INFO->setFamiliar(3);
	}

	if (IntersectRect(&tp, &_selectRC, &_ghost.rc) && !_ghost.on &&KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{

		_ghost.on = true;
		_demon.on = _fairy.on = false;
		ALUCARD_INFO->setFamiliar(2);
	}
	else if (IntersectRect(&tp, &_selectRC, &_ghost.rc) && _ghost.on &&KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_ghost.on = false;
		ALUCARD_INFO->setFamiliar(3);
	}

	if (IntersectRect(&tp, &_selectRC, &_unkown) && KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
	
		_demon.on = _fairy.on = _ghost.on = false;
		ALUCARD_INFO->setFamiliar(3);
	}

	if (KEYMANAGER->isOnceKeyDown('Z')) SCENEMANAGER->changeScene("CharScene");

	_selectRC = RectMakeCenter(_selectX + 65, _selectY + 25, 250, 50);

	ALUCARD_INFO->statUpdate();

}
void familiarScene::render(void) 
{
	IMAGEMANAGER->findImage("familiarBackground")->render(getMemDC(),0,0);
	
	

	//Rectangle(getMemDC(), _demon.rc.left, _demon.rc.top, _demon.rc.right, _demon.rc.bottom);
	//Rectangle(getMemDC(), _fairy.rc.left, _fairy.rc.top, _fairy.rc.right, _fairy.rc.bottom);
	//Rectangle(getMemDC(), _ghost.rc.left, _ghost.rc.top, _ghost.rc.right, _ghost.rc.bottom);

	//Rectangle(getMemDC(), _selectRC.left, _selectRC.top, _selectRC.right, _selectRC.bottom);
	IMAGEMANAGER->findImage("fmiliar_select")->render(getMemDC(), _selectRC.left, _selectRC.top - 15);

	IMAGEMANAGER->findImage("familiarSceneDemon")->frameRender(getMemDC(), _demon.x-60, _demon.y - 10);
	IMAGEMANAGER->findImage("familiarSceneFairy")->frameRender(getMemDC(), _fairy.x-50, _fairy.y + 10);
	IMAGEMANAGER->findImage("familiarSceneGhost")->frameRender(getMemDC(), _ghost.x-50, _ghost.y + 10);

	IMAGEMANAGER->findImage("on_off")->frameRender(getMemDC(), _demon.x, _demon.y);
	IMAGEMANAGER->findImage("on_off1")->frameRender(getMemDC(), _fairy.x, _fairy.y);
	IMAGEMANAGER->findImage("on_off2")->frameRender(getMemDC(), _ghost.x, _ghost.y);
	IMAGEMANAGER->findImage("on_off3")->frameRender(getMemDC(), _x, _y);


	/*char str[8];
	sprintf(str, "%d", ALUCARD_INFO->getStats().familiar);
	TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY / 2, str, strlen(str));*/
}