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

int pixelCollision::VerticalCollision(RECT rc, float destX, float destY, image* sourImage)
{
	// ���
	for (int i = rc.top; i < rc.top + ((rc.bottom - rc.top) / 4); ++i)
	{
		_color = GetPixel(sourImage->getMemDC(), destX, i);

		_r = GetRValue(_color);
		_g = GetGValue(_color);
		_b = GetBValue(_color);

		IF_R
		{
			return TOP;
		}
	}

	// �ϴ�
	for (int i = destY - ((rc.bottom - rc.top) / 4); i < destY + ((rc.bottom - rc.top) / 8); ++i)
	{
		_color = GetPixel(sourImage->getMemDC(), destX, i);

		_r = GetRValue(_color);
		_g = GetGValue(_color);
		_b = GetBValue(_color);

		IF_R
		{
			return BOTTOM;
		}
	}
}

int pixelCollision::HorizontalCollision(RECT rc, float destX, float destY, image* sourImage)
{
	// y����
	for (int j = rc.top + ((rc.bottom - rc.top) / 10); j < rc.top + ((rc.bottom - rc.top) / 2); ++j)
	{
		// ��
		for (int i = rc.left - ((rc.right - rc.left) / 4); i < rc.left; ++i)
		{
			_color = GetPixel(sourImage->getMemDC(), i, j);

			_r = GetRValue(_color);
			_g = GetGValue(_color);
			_b = GetBValue(_color);

			IF_R
			{
				return LEFT;
			}
		}
	}
	
	// y����
	for (int j = rc.top + ((rc.bottom - rc.top) / 10); j < rc.top + ((rc.bottom - rc.top) / 2); ++j)
	{
		// ��
		for (int i = rc.right; i < rc.right + ((rc.right - rc.left) / 4); ++i)
		{
			_color = GetPixel(sourImage->getMemDC(), i, j);

			_r = GetRValue(_color);
			_g = GetGValue(_color);
			_b = GetBValue(_color);

			IF_R
			{
				return RIGHT;
			}
		}
	}
}

float pixelCollision::setPlayerVertical(RECT rc, float destX, float destY, image* sourImage)
{
	// �ϴ�
	for (int i = rc.bottom - ((rc.bottom - rc.top) / 4); i < rc.bottom + ((rc.bottom - rc.top) / 8); ++i)
	{
		_color = GetPixel(sourImage->getMemDC(), destX, i);

		_r = GetRValue(_color);
		_g = GetGValue(_color);
		_b = GetBValue(_color);

		IF_R
		{
			return i + 1;
		}
	}
}