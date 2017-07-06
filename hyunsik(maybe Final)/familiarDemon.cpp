#include "stdafx.h"
#include "familiarDemon.h"


familiarDemon::familiarDemon()
{
}


familiarDemon::~familiarDemon()
{
}

HRESULT familiarDemon::init(const char* imageName, float x, float y, float* playerPosX, float* playerPosY)
{
	familiar::init(imageName, x, y, playerPosX, playerPosY);
	
	_body = IMAGEMANAGER->findImage(imageName);
	_wing = IMAGEMANAGER->findImage(imageName);

	//bodyMotion frame
	int arrRight[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("DEMON_RIGHT", "familiarDemon", arrRight, 1, 1, false);

	int arrLeft[] = { 1 };
	KEYANIMANAGER->addArrayFrameAnimation("DEMON_LEFT", "familiarDemon", arrLeft, 1, 1, false);

	int arrRightAttack[] = { 15, 16, 17 };
	KEYANIMANAGER->addArrayFrameAnimation("DEMON_RIGHT_ATTACK", "familiarDemon", arrRightAttack, 3, 12, false, cbRightAttack, this);

	int arrLeftAttack[] = { 20, 21, 22 };
	KEYANIMANAGER->addArrayFrameAnimation("DEMON_LEFT_ATTACK", "familiarDemon", arrLeftAttack, 3, 12, false, cbLeftAttack, this);


	//wingMotion frame
	int arrRightWing[] = { 25, 26, 27, 28, 27, 26 };
	KEYANIMANAGER->addArrayFrameAnimation("DEMON_RIGHT_WING", "familiarDemon", arrRightWing, 6, 15, true);

	int arrLeftWing[] = { 30, 31, 32, 33, 32, 31 };
	KEYANIMANAGER->addArrayFrameAnimation("DEMON_LEFT_WING", "familiarDemon", arrLeftWing, 6, 15, true);

	if (_x - *_playerPosX > 0) _direction = FAMILIAR_DIRECTION_LEFT;
	if (_x - *_playerPosX <= 0) _direction = FAMILIAR_DIRECTION_RIGHT;

	return S_OK;
}

void familiarDemon::update()
{
	_direction;

	move();
}

void familiarDemon::render(void)
{
	_wing->aniRender(getMemDC(), _rc.left, _rc.top, _wingMotion);
	_body->aniRender(getMemDC(), _rc.left, _rc.top, _bodyMotion);

	char ptr[32];
	sprintf(ptr, "%5.2f", _x - *_playerPosX);
	TextOut(getMemDC(), 200, 200, ptr, strlen(ptr));

	sprintf(ptr, "%5.2f", _x);
	TextOut(getMemDC(), 200, 220, ptr, strlen(ptr));

	sprintf(ptr, "%5.2f", *_playerPosX);
	TextOut(getMemDC(), 200, 240, ptr, strlen(ptr));
}

void familiarDemon::move()
{
	familiar::move();

	switch (_direction)
	{
	case FAMILIAR_DIRECTION_RIGHT:
		_bodyMotion = KEYANIMANAGER->findAnimation("DEMON_RIGHT");
		_wingMotion = KEYANIMANAGER->findAnimation("DEMON_RIGHT_WING");
		if (!_bodyMotion->isPlay()) _bodyMotion->start();
		if (!_wingMotion->isPlay()) _wingMotion->start();
		break;
	case FAMILIAR_DIRECTION_LEFT:
		_bodyMotion = KEYANIMANAGER->findAnimation("DEMON_LEFT");
		_wingMotion = KEYANIMANAGER->findAnimation("DEMON_LEFT_WING");
		if (!_bodyMotion->isPlay()) _bodyMotion->start();
		if (!_wingMotion->isPlay()) _wingMotion->start();
		break;
	case FAMILIAR_DIRECTION_RIGHT_ATTACK:
		_bodyMotion = KEYANIMANAGER->findAnimation("DEMON_RIGHT_ATTACK");
		if (!_bodyMotion->isPlay()) _bodyMotion->start();
		break;
	case FAMILIAR_DIRECTION_LEFT_ATTACK:
		_bodyMotion = KEYANIMANAGER->findAnimation("DEMON_LEFT_ATTACK");
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

void familiarDemon::cbRightAttack(void* obj)
{
	familiarDemon* fm = (familiarDemon*)obj;

	fm->_direction = FAMILIAR_DIRECTION_RIGHT;
	fm->_bodyMotion = KEYANIMANAGER->findAnimation("DEMON_RIGHT");
	fm->_bodyMotion->start();
}
void familiarDemon::cbLeftAttack(void* obj)
{
	familiarDemon* fm = (familiarDemon*)obj;

	fm->_direction = FAMILIAR_DIRECTION_LEFT;
	fm->_bodyMotion = KEYANIMANAGER->findAnimation("DEMON_LEFT");
	fm->_bodyMotion->start();
}