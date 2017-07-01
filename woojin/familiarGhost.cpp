#include "stdafx.h"
#include "familiarGhost.h"


familiarGhost::familiarGhost()
{
}


familiarGhost::~familiarGhost()
{
}

HRESULT familiarGhost::init(const char* imageName, float* x, float* y)
{
	familiar::init(imageName, x, y);

	_body = IMAGEMANAGER->findImage(imageName);

	int arrRight[] = { 4, 5, 6, 7 };
	KEYANIMANAGER->addArrayFrameAnimation("GHOST_RIGHT", imageName, arrRight, 4, 6, true);

	int arrLeft[] = { 0, 1, 2, 3 };
	KEYANIMANAGER->addArrayFrameAnimation("GHOST_LEFT", imageName, arrLeft, 4, 6, true);

	return S_OK;
}
void familiarGhost::update(void)
{
	KEYANIMANAGER->update();

	move();
}
void familiarGhost::move(void)
{
	//if (_familiarChange)
	//{
	//	if (getDistance(*_x, *_y, _targetX, _targetY) > EPSILON)
	//	{
	//		*_x += ((_targetX - *_x) / getDistance(*_x, *_y, _targetX, _targetY)) * TIMEMANAGER->getElapsedTime();
	//		*_y -= ((_targetY - *_y) / getDistance(*_x, *_y, _targetX, _targetY)) * TIMEMANAGER->getElapsedTime();
	//	}
	//	else _familiarChange = false;
	//}

	switch (_direction)
	{
	case FAMILIAR_DIRECTION_RIGHT:
		_bodyMotion = KEYANIMANAGER->findAnimation("GHOST_RIGHT");
		if (!_bodyMotion->isPlay()) _bodyMotion->start();
		break;
	case FAMILIAR_DIRECTION_LEFT:
		_bodyMotion = KEYANIMANAGER->findAnimation("GHOST_LEFT");
		if (!_bodyMotion->isPlay()) _bodyMotion->start();
		break;
	}
}
void familiarGhost::render(void)
{
	_body->aniRender(getMemDC(), *_x, *_y, _bodyMotion);
}