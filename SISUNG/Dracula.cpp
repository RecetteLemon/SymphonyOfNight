#include "stdafx.h"
#include "Dracula.h"


Dracula::Dracula()
{
}


Dracula::~Dracula()
{
}

HRESULT Dracula::init()
{
	_Draculaimage = IMAGEMANAGER->addFrameImage("µå¶óÅ§¶ó", "CounterDracula.bmp", WINSIZEX / 2,WINSIZEY/2, 510, 570, 6, 6, true, RGB(255, 0, 255));

	_DraculaDirection = DRACULA_LEFT_STOP;

	_DraculaInfo.x = WINSIZEX / 2;
	_DraculaInfo.y = WINSIZEY /2;

	_DraculaInfo.rc = RectMakeCenter(_DraculaInfo.x, _DraculaInfo.y, _Draculaimage->getFrameWidth(), _Draculaimage->getFrameHeight());
	
	int leftStop[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("DraculaLeftStop", "µå¶óÅ§¶ó", leftStop, 1, 10, true);

	_DraculaMotion = KEYANIMANAGER->findAnimation("DraculaLeftStop");



	return S_OK;
}

void Dracula::release()
{

}

void Dracula::update()
{
	KEYANIMANAGER->update();
}

void Dracula::render()
{
	_Draculaimage->aniRender(getMemDC(), _DraculaInfo.rc.left, _DraculaInfo.rc.top, _DraculaMotion);

}

void Dracula::move()
{

}