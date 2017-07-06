#include "stdafx.h"
#include "familiarGhost.h"


familiarGhost::familiarGhost()
{
}


familiarGhost::~familiarGhost()
{
}

HRESULT familiarGhost::init(const char* imageName, float x, float y, float* playerPosX, float* playerPosY)
{
	familiar::init(imageName, x, y, playerPosX, playerPosY);

	_body = IMAGEMANAGER->findImage(imageName);

	int arrRight[] = { 4, 5, 6, 7 };
	KEYANIMANAGER->addArrayFrameAnimation("GHOST_RIGHT", "familiarGhost", arrRight, 4, 6, true);

	int arrLeft[] = { 0, 1, 2, 3 };
	KEYANIMANAGER->addArrayFrameAnimation("GHOST_LEFT", "familiarGhost", arrLeft, 4, 6, true);

	if (_x - *_playerPosX > 0) _direction = FAMILIAR_DIRECTION_LEFT;
	if (_x - *_playerPosX <= 0) _direction = FAMILIAR_DIRECTION_RIGHT;

	return S_OK;
}
void familiarGhost::update(void)
{
	move();
}

void familiarGhost::render(HDC hdc)
{
	_body->aniRender(getMemDC(), _rc.left, _rc.top, _bodyMotion);
}

void familiarGhost::move(void)
{
	familiar::move();

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

	_rc = RectMakeCenter(_x, _y, _body->getFrameWidth(), _body->getFrameHeight());

	if (_direction != FAMILIAR_DIRECTION_RIGHT_ATTACK || _direction != FAMILIAR_DIRECTION_LEFT_ATTACK)
	{
		if (_x - *_playerPosX > 0) _direction = FAMILIAR_DIRECTION_LEFT;
		if (_x - *_playerPosX <= 0) _direction = FAMILIAR_DIRECTION_RIGHT;
	}
}