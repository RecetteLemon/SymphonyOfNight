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
	_probeY = checkY + fromCheckY; // fromCheckY�� Ž�� ������ ���� ����

	for (int i = _probeY; i < _probeY + scale; i++) // Ž�� �������κ��� �Ʒ��� ������ �������� Ž��
	{
		_color = GetPixel(pixelImage->getMemDC(), (int)checkX + fromCheckX, i);

		_r = GetRValue(_color);
		_g = GetGValue(_color);
		_b = GetBValue(_color);

		if (_r == 0 && _g == 255 && _b == 0) // ������ �ȿ� �ȼ� ���� ��������� ��ǥ ����
		{
			_colli[TOP] = true;
			checkY = i - fromCheckY;
			return;
		}
	}

	_colli[TOP] = false;

	//���� �ȼ��浹 �Լ� ���� ��
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