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

	_x = 500;
	_y = 600;

	IMAGEMANAGER->addImage("pixelTest", "Image/pixelTest.bmp", 800, 800, false, NULL);

	_image = IMAGEMANAGER->addFrameImage("alucard", "Image/AlucardPosition24Bit.bmp", 4000, 4000, 20, 20, true, RGB(255, 0, 255));

	KEYANIMANAGER->addCoordinateFrameAnimation("Left_Move", "alucard", 120, 135, 30, false, true);

	_playerMotion = KEYANIMANAGER->findAnimation("Left_Move");

	_image->setX(WINSIZEX / 2);
	_image->setY(WINSIZEY / 2);

	_rc = RectMakeBottomCenter(_x, _y, 80, 100);

	return S_OK;
}

//메모리 해제 함수
void symphonyOfNight::release(void)
{
	

	gameNode::release();

	

}

//연산해주는 곳
void symphonyOfNight::update(void)
{
	gameNode::update();

	if (!KEYANIMANAGER->isStart("Left_Move")) KEYANIMANAGER->start("Left_Move");

	KEYANIMANAGER->update();

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_image->setX(_image->getX() - 3);
		_x -= 3;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_image->setX(_image->getX() + 3);
		_x += 3;
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_image->setY(_image->getY() - 3);
		_y -= 3;
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_image->setY(_image->getY() + 3);
		_y += 3;
	}
	
	
	PIXELCOLLISION->pixelColliTop(0, -100, IMAGEMANAGER->findImage("pixelTest"), _x, _y, 10);
	PIXELCOLLISION->pixelColliBottom(0, 0, IMAGEMANAGER->findImage("pixelTest"), _x, _y, 10);
	PIXELCOLLISION->pixelColliRight(40, -30, IMAGEMANAGER->findImage("pixelTest"), _x, _y, 10);
	PIXELCOLLISION->pixelColliLeft(-40, -30, IMAGEMANAGER->findImage("pixelTest"), _x, _y, 10);

	_rc = RectMakeBottomCenter(_x, _y, 80, 100);
}

//여기가 그려주는 곳
void symphonyOfNight::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============================================================================
	
	char str[128];
	sprintf_s(str, "%d", EQUIPDATA->getData("마사무네")->atk_);
	TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY / 2, str, strlen(str));
	
	


	IMAGEMANAGER->findImage("pixelTest")->render(getMemDC(), 0, 0);
	//_image->aniRender(getMemDC(), _image->getX(), _image->getY(), _playerMotion);


	
	SelectObject(getMemDC(), GetStockObject(NULL_BRUSH));
	Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	
	//================================================================================
	//건들지마라 이거도
	TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
