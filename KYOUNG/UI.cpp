#include "stdafx.h"
#include "UI.h"


UI::UI()
{
}


UI::~UI()
{
}

HRESULT UI::init(int x, int y, int width, int height, const char* topBar, const char* backBar, const char* magic)
{
	_x = x;
	_y = y;

	_rcprogress = RectMake(x, y, width, height);

	progressBottom = IMAGEMANAGER->addImage(backBar, "HUD.bmp", x, y, width, height, true, RGB(255, 0, 255));
	progressTOP = IMAGEMANAGER->addFrameImage(topBar, "ManaUI.bmp", x, y, width, height, true, RGB(255, 0, 255));
	heart = IMAGEMANAGER->addFrameImage(magic, "heart.bmp", x, y, width, height, true, RGB(255, 0, 255));
	currentWidth = width;
	currentHeight = height;

	_count = 0;

	_currentFrameX = 0;

	return S_OK;

}
void UI::release()
{


}
void UI::update()
{
	_rcprogress = RectMakeCenter(_x, _y, width, height);

	_count++;

	if (_count % 2 == 0)
	{
		progressTOP->setFrameX(progressTOP->getFrameX() + 0);
		_currentFrameX++;

		if (_currentFrameX > progressTOP->getMaxFrameX()) _currentFrameX = 0;
	}

	if (_count % 8 == 0)
	{
		heart->setFrameX(heart->getFrameX() + 1);
		_currentFrameX++;

		if (_currentFrameX > heart->getFrameX()) _currentFrameX = 0;
	}

}
void UI::render(const char* topBar, const char* backBar,const char* magic)
{
	//IMAGEMANAGER->render(backBar,getMemDC(),0,0 /*_rcprogress.left + currentWidth / 2, _y + currentHeight / 2, 0, 0, currentWidth, currentHeight*/);
	//IMAGEMANAGER->render(topBar, getMemDC(),0,0 /*_rcprogress.left + currentWidth / 2, _y + currentHeight / 2, 0, 0, currentWidth, currentHeight*/);
	IMAGEMANAGER->findImage("뒷게이지")->render(getMemDC(), 0, 0);
	IMAGEMANAGER->findImage("앞게이지")->frameRender(getMemDC(), 60, 10, _currentFrameX, 0);
	IMAGEMANAGER->findImage("하트")->frameRender(getMemDC(), 97, 22, _currentFrameX, 0);
}

void UI::setGauge(float currentGauge, float maxGauge)
{
	width = (currentGauge / maxGauge) * progressBottom->getWidth();

}