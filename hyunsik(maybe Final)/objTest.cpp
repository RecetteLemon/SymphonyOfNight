#include "stdafx.h"
#include "objTest.h"


objTest::objTest()
{
}


objTest::~objTest()
{
}


HRESULT objTest::init(void)
{
	
	_x = 500;
	_y = 600;

	_obj = new objectCreate;
	_obj->init(WINSIZEX / 2 - 100, WINSIZEY / 2 - 100);
	


	

	_rc = RectMakeBottomCenter(_x, _y, 80, 100);


	return S_OK;
}

//메모리 해제 함수
void objTest::release(void)
{
	_obj->release();
	safeDelete(_obj);

}

//연산해주는 곳
void objTest::update(void)
{



	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_x -= 3;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_x += 3;
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_y -= 3;
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_y += 3;
	}


	_rc = RectMakeBottomCenter(_x, _y, 80, 100);
	_obj->update();


	RECT temp;
	if (IntersectRect(&temp, &_rc, &_obj->getRect()))
	{
		_obj->setOnDropItem(true);
	}
}

//여기가 그려주는 곳
void objTest::render(void)
{
	
	IMAGEMANAGER->findImage("PixelTest")->render(getMemDC(), 0, 0);



	SelectObject(getMemDC(), GetStockObject(NULL_BRUSH));
	Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);

	char str[128];

	sprintf_s(str, "%d", ITEM->getData("파란포션")->HP_);
	TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY / 2, str, strlen(str));

	_obj->render();

}