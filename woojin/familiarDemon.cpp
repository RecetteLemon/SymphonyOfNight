#include "stdafx.h"
#include "familiarDemon.h"


familiarDemon::familiarDemon()
{
}


familiarDemon::~familiarDemon()
{
}

HRESULT familiarDemon::init(const char* imageName, float* x, float* y)
{
	_x = x;
	_y = y;
	
	_body = IMAGEMANAGER->findImage(imageName);
	_wing = IMAGEMANAGER->findImage(imageName);

	//_direction = FAMILIAR_DIRECTION_RIGHT;

	//bodyMotion frame
	int arrRight[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("DEMON_RIGHT", imageName, arrRight, 1, 10, false);

	int arrLeft[] = { 1 };
	KEYANIMANAGER->addArrayFrameAnimation("DEMON_LEFT", imageName, arrLeft, 1, 10, false);

	int arrRightAttack[] = { 15, 16, 17 };
	KEYANIMANAGER->addArrayFrameAnimation("DEMON_RIGHT_ATTACK", imageName, arrRightAttack, 3, 10, false, cbRightAttack, this);

	int arrLeftAttack[] = { 20, 21, 22 };
	KEYANIMANAGER->addArrayFrameAnimation("DEMON_LEFT_ATTACK", imageName, arrLeftAttack, 3, 10, false, cbLeftAttack, this);


	//wingMotion frame
	int arrRightWing[] = { 25, 26, 27, 28, 27, 26 };
	KEYANIMANAGER->addArrayFrameAnimation("DEMON_RIGHT_WING", imageName, arrRightWing, 6, 12, true);

	int arrLeftWing[] = { 30, 31, 32, 33, 32, 31 };
	KEYANIMANAGER->addArrayFrameAnimation("DEMON_LEFT_WING", imageName, arrLeftWing, 6, 12, true);

	return S_OK;
}

void familiarDemon::update()
{
	move();

	KEYANIMANAGER->update();
}

void familiarDemon::render(void)
{
	_wing->aniRender(getMemDC(), *_x, *_y, _wingMotion);
	_body->aniRender(getMemDC(), *_x, *_y, _bodyMotion);
}

void familiarDemon::move()
{
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