#include "stdafx.h"
#include "pixelCollision.h"


pixelCollision::pixelCollision():
	_color(NULL),
	_r(0), _g(0), _b(0),
	_probeX(0), _probeY(0)
{
}


pixelCollision::~pixelCollision()
{
}


void pixelCollision::pixelColliTop(int fromCheckX, int fromCheckY, image* pixelImage, float& checkX, float& checkY, int scale)
{
	_probeY = checkY + fromCheckY; // fromCheckY는 탐색 지점을 임의 조절

	for (int i = _probeY; i < _probeY + scale; i++) // 탐색 지점으로부터 아래로 스케일 범위까지 탐색
	{
		_color = GetPixel(pixelImage->getMemDC(), (int)checkX + fromCheckX, i);

		_r = GetRValue(_color);
		_g = GetGValue(_color);
		_b = GetBValue(_color);

		if (_r == 0 && _g == 255 && _b == 0) // 스케일 안에 픽셀 값이 들어있으면 좌표 보정
		{
			_colli[TOP] = true;
			checkY = i - fromCheckY;
			return;
		}
	}

	_colli[TOP] = false;

	//이하 픽셀충돌 함수 원리 동
}

void pixelCollision::pixelColliBottom(int fromCheckX, int fromCheckY, image* pixelImage, float& checkX, float& checkY, int scale)
{
	_probeY = checkY + fromCheckY;

	for (int i = _probeY - scale; i < _probeY; i++)
	{
		_color = GetPixel(pixelImage->getMemDC(), (int)checkX + fromCheckX, i);

		_r = GetRValue(_color);
		_g = GetGValue(_color);
		_b = GetBValue(_color);

		if (_r == 255 && _g == 0 && _b == 0)
		{
			_colli[BOTTOM] = true;
			checkY = i - fromCheckY;
			return;
		}
	}

	_colli[BOTTOM] = false;
}

void pixelCollision::pixelColliRight(int fromCheckX, int fromCheckY, image* pixelImage, float& checkX, float& checkY, int scale)
{
	_probeX = checkX + fromCheckX;

	for (int i = _probeX; i > _probeX - scale; i--)
	{
		_color = GetPixel(pixelImage->getMemDC(), (int)i, checkY + fromCheckY);

		_r = GetRValue(_color);
		_g = GetGValue(_color);
		_b = GetBValue(_color);

		if (_r == 255 && _g == 255 && _b == 0)
		{
			_colli[RIGHT] = true;
			checkX = i - fromCheckX;
			return;
		}

	}

	_colli[RIGHT] = false;
}

void pixelCollision::pixelColliLeft(int fromCheckX, int fromCheckY, image* pixelImage, float& checkX, float& checkY, int scale)
{
	_probeX = checkX + fromCheckX;

	for (int i = _probeX; i < _probeX + scale; i++)
	{
		_color = GetPixel(pixelImage->getMemDC(), (int)i, checkY + fromCheckY);

		_r = GetRValue(_color);
		_g = GetGValue(_color);
		_b = GetBValue(_color);

		if (_r == 0 && _g == 0 && _b == 255)
		{
			_colli[LEFT] = true;
			checkX = i - fromCheckX;
			return;
		}

	}

	_colli[LEFT] = false;
}