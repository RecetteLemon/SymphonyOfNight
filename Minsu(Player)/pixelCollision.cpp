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
	// 상단
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

	// 하단
	for (int i = rc.bottom - ((rc.bottom - rc.top) / 4); i < rc.bottom; ++i)
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

}