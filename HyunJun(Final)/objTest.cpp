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
	

	_x = 300;
	_y = 300;

	_obj = new objectCreate;
	_obj->init(WINSIZEX / 2 - 100, WINSIZEY / 2 - 100);
	
	_obj1 = new objectCreate;
	_obj1->init(WINSIZEX -300, 100, 1);

	_obj2 = new objectCreate;
	_obj2->init(WINSIZEX - 400, 100, 2);

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
	_obj1->update();
	_obj2->update();

	RECT temp;
	if (IntersectRect(&temp, &_rc, &_obj->getRect()))
	{
		if (!_obj->getOnDropItem())
		{
			for (int i = 0; i < 5; i++)
			{
				EFFECTMANAGER->play("ObjBroken", _obj->getRect().left + RND->getInt(50), _obj->getRect().top + RND->getInt(50));
			}
		}
		_obj->setOnDropItem(true);
	}

	if (IntersectRect(&temp, &_rc, &_obj1->getRect()))
	{
		if (!_obj1->getOnDropItem())
		{
			for (int i = 0; i < 5; i++)
			{
				EFFECTMANAGER->play("ObjBroken", _obj1->getRect().left + RND->getInt(50), _obj1->getRect().top + RND->getInt(50));
			}
		}
		_obj1->setOnDropItem(true);
	}
	if (IntersectRect(&temp, &_rc, &_obj2->getRect()))
	{
		if (!_obj2->getOnDropItem())
		{
			for (int i = 0; i < 5; i++)
			{
				EFFECTMANAGER->play("ObjBroken", _obj2->getRect().left + RND->getInt(50), _obj2->getRect().top + RND->getInt(50));
			}
		}
		_obj2->setOnDropItem(true);
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
	_obj1->render();
	_obj2->render();

	
	
}