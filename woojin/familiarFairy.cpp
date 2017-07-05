#include "stdafx.h"
#include "familiarFairy.h"


familiarFairy::familiarFairy()
{
}


familiarFairy::~familiarFairy()
{
}

HRESULT familiarFairy::init(const char* imageName, float x, float y, float* playerPosX, float* playerPosY)
{
	familiar::init(imageName, x, y, playerPosX, playerPosY);

	_body = IMAGEMANAGER->findImage(imageName);
	_wing = IMAGEMANAGER->findImage(imageName);
	_hair = IMAGEMANAGER->findImage(imageName);

	//bodyMotion frame
	int arrStand[] = { 0, 1 };
	KEYANIMANAGER->addArrayFrameAnimation("FAIRY_STAND", imageName, arrStand, 2, 1, true);

	int arrRight[] = { 24, 25, 26, 27 };
	KEYANIMANAGER->addArrayFrameAnimation("FAIRY_RIGHT", imageName, arrRight, 4, 10, true);

	int arrLeft[] = { 16, 17, 18, 19 };
	KEYANIMANAGER->addArrayFrameAnimation("FAIRY_LEFT", imageName, arrLeft, 4, 10, true);

	int arrSkillMotion[] = { 28, 29, 30, 31 };
	KEYANIMANAGER->addArrayFrameAnimation("FAIRY_SKILL", imageName, arrSkillMotion, 4, 10, false);

	//wingMotion frame
	int arrWingStand[] = { 2, 3 };
	KEYANIMANAGER->addArrayFrameAnimation("FAIRY_WING_STAND", imageName, arrWingStand, 2, 8, true);

	int arrWingRight[] = { 10, 11 };
	KEYANIMANAGER->addArrayFrameAnimation("FAIRY_WING_RIGHT", imageName, arrWingRight, 2, 8, true);

	int arrWingLeft[] = { 8, 9 };
	KEYANIMANAGER->addArrayFrameAnimation("FAIRY_WING_LEFT", imageName, arrWingLeft, 2, 8, true);

	//hairMotion frame
	int arrHairStand[] = { 4, 5, 6, 7 };
	KEYANIMANAGER->addArrayFrameAnimation("FAIRY_HAIR_STAND", imageName, arrHairStand, 4, 5, true);

	int arrHairRight[] = { 20, 21, 22, 23 };
	KEYANIMANAGER->addArrayFrameAnimation("FAIRY_HAIR_RIGHT", imageName, arrHairRight, 4, 5, true);

	int arrHairLeft[] = { 12, 13, 14, 15 };
	KEYANIMANAGER->addArrayFrameAnimation("FAIRY_HAIR_LEFT", imageName, arrHairLeft, 4, 5, true);
	
	if (_x - *_playerPosX > 2) _direction = FAMILIAR_DIRECTION_LEFT;
	if (_x - *_playerPosX < 2) _direction = FAMILIAR_DIRECTION_RIGHT;
	if (_x - *_playerPosX <= 2 && _x - *_playerPosX > -2) _direction = FAMILIAR_DIRECTION_STAND;

	return S_OK;
}

void familiarFairy::update()
{
	move();

}

void familiarFairy::render(void)
{
	if (_direction != FAMILIAR_DIRECTION_CASTSKILL)
	{
		_wing->aniRender(getMemDC(), _rc.left, _rc.top, _wingMotion);
		_hair->aniRender(getMemDC(), _rc.left, _rc.top, _hairMotion);
		_body->aniRender(getMemDC(), _rc.left, _rc.top, _bodyMotion);
	}
	else _body->aniRender(getMemDC(), _rc.left, _rc.top, _bodyMotion);

	char ptr[32];
	sprintf(ptr, "%5.2f", _x - *_playerPosX);
	TextOut(getMemDC(), 200, 200, ptr, strlen(ptr));

	sprintf(ptr, "%5.2f", _x);
	TextOut(getMemDC(), 200, 220, ptr, strlen(ptr));
}

void familiarFairy::move()
{
	familiar::move();

	switch (_direction)
	{
	case FAMILIAR_DIRECTION_STAND:
		_bodyMotion = KEYANIMANAGER->findAnimation("FAIRY_STAND");
		_wingMotion = KEYANIMANAGER->findAnimation("FAIRY_WING_STAND");
		_hairMotion = KEYANIMANAGER->findAnimation("FAIRY_HAIR_STAND");

		if (!_bodyMotion->isPlay()) _bodyMotion->start();
		if (!_wingMotion->isPlay()) _wingMotion->start();
		if (!_hairMotion->isPlay()) _hairMotion->start();

		break;

	case FAMILIAR_DIRECTION_RIGHT:
		_bodyMotion = KEYANIMANAGER->findAnimation("FAIRY_RIGHT");
		_wingMotion = KEYANIMANAGER->findAnimation("FAIRY_WING_RIGHT");
		_hairMotion = KEYANIMANAGER->findAnimation("FAIRY_HAIR_RIGHT");

		if (!_bodyMotion->isPlay()) _bodyMotion->start();
		if (!_wingMotion->isPlay()) _wingMotion->start();
		if (!_hairMotion->isPlay()) _hairMotion->start();

		break;

	case FAMILIAR_DIRECTION_LEFT:
		_bodyMotion = KEYANIMANAGER->findAnimation("FAIRY_LEFT");
		_wingMotion = KEYANIMANAGER->findAnimation("FAIRY_WING_LEFT");
		_hairMotion = KEYANIMANAGER->findAnimation("FAIRY_HAIR_LEFT");

		if (!_bodyMotion->isPlay()) _bodyMotion->start();
		if (!_wingMotion->isPlay()) _wingMotion->start();
		if (!_hairMotion->isPlay()) _hairMotion->start();

		break;

	case FAMILIAR_DIRECTION_CASTSKILL:
		_bodyMotion = KEYANIMANAGER->findAnimation("FAIRY_SKILL");

		if (!_bodyMotion->isPlay()) _bodyMotion->start();

		break;
	}

	_rc = RectMakeCenter(_x, _y, _body->getFrameWidth(), _body->getFrameHeight());

	if (_direction != FAMILIAR_DIRECTION_CASTSKILL)
	{
		if (_x - *_playerPosX > 2) _direction = FAMILIAR_DIRECTION_LEFT;
		if (_x - *_playerPosX < 2) _direction = FAMILIAR_DIRECTION_RIGHT;
		if (_x - *_playerPosX <= 2 && _x - *_playerPosX > -2) _direction = FAMILIAR_DIRECTION_STAND;
	}
}