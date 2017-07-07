#include "stdafx.h"
#include "familiar.h"


familiar::familiar()
{
}

familiar::~familiar()
{
}

HRESULT familiar::init(image* img, float x, float y, float* playerPosX, float* playerPosY)
{
	_x = x;
	_y = y - WINSIZEY / 2;

	_playerPosX = playerPosX;
	_playerPosY = playerPosY;

	return S_OK;
}

void familiar::release(void)
{
}

void familiar::update(void)
{

}

void familiar::render(HDC hdc)
{
	
}

void familiar::move(void)
{
	float tempDist = getDistance(_x, _y, *_playerPosX, *_playerPosY);
	
	_angle = getAngle(_x, _y, *_playerPosX, *_playerPosY);

	if (tempDist > 0.1)
	{
		if (abs(_x - *_playerPosX) > 0) _x += cosf(_angle) * tempDist * TIMEMANAGER->getElapsedTime();
		if (abs(_y - *_playerPosY) > 0) _y += -sinf(_angle) * tempDist * TIMEMANAGER->getElapsedTime();
	}
}

void familiar::setDirection(int direction)
{

}