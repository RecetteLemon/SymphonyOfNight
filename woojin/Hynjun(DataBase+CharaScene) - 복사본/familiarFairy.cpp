#include "stdafx.h"
#include "familiarFairy.h"


familiarFairy::familiarFairy()
{
}


familiarFairy::~familiarFairy()
{
}

HRESULT familiarFairy::init(image* img, float x, float y, float* playerPosX, float* playerPosY)
{
	familiar::init(img, x, y, playerPosX, playerPosY);

	_body = img;
	_wing = img;
	_hair = img;

	//bodyMotion frame
	int arrStand[] = { 0, 1 };
	KEYANIMANAGER->addArrayFrameAnimation("FAIRY_STAND", "familiarFairy", arrStand, 2, 1, true);

	int arrRight[] = { 24, 25, 26, 27 };
	KEYANIMANAGER->addArrayFrameAnimation("FAIRY_RIGHT", "familiarFairy", arrRight, 4, 10, true);

	int arrLeft[] = { 16, 17, 18, 19 };
	KEYANIMANAGER->addArrayFrameAnimation("FAIRY_LEFT", "familiarFairy", arrLeft, 4, 10, true);

	int arrSkillMotion[] = { 28, 29, 30, 31 };
	KEYANIMANAGER->addArrayFrameAnimation("FAIRY_SKILL", "familiarFairy", arrSkillMotion, 4, 10, false);

	//wingMotion frame
	int arrWingStand[] = { 2, 3 };
	KEYANIMANAGER->addArrayFrameAnimation("FAIRY_WING_STAND", "familiarFairy", arrWingStand, 2, 8, true);

	int arrWingRight[] = { 10, 11 };
	KEYANIMANAGER->addArrayFrameAnimation("FAIRY_WING_RIGHT", "familiarFairy", arrWingRight, 2, 8, true);

	int arrWingLeft[] = { 8, 9 };
	KEYANIMANAGER->addArrayFrameAnimation("FAIRY_WING_LEFT", "familiarFairy", arrWingLeft, 2, 8, true);

	//hairMotion frame
	int arrHairStand[] = { 4, 5, 6, 7 };
	KEYANIMANAGER->addArrayFrameAnimation("FAIRY_HAIR_STAND", "familiarFairy", arrHairStand, 4, 5, true);

	int arrHairRight[] = { 20, 21, 22, 23 };
	KEYANIMANAGER->addArrayFrameAnimation("FAIRY_HAIR_RIGHT", "familiarFairy", arrHairRight, 4, 5, true);

	int arrHairLeft[] = { 12, 13, 14, 15 };
	KEYANIMANAGER->addArrayFrameAnimation("FAIRY_HAIR_LEFT", "familiarFairy", arrHairLeft, 4, 5, true);
	
	if (_x - *_playerPosX > 2) _direction = FAMILIAR_DIRECTION_LEFT;
	if (_x - *_playerPosX < 2) _direction = FAMILIAR_DIRECTION_RIGHT;
	if (_x - *_playerPosX <= 2 && _x - *_playerPosX > -2) _direction = FAMILIAR_DIRECTION_STAND;

	return S_OK;
}

void familiarFairy::update()
{
	move();

}

void familiarFairy::render(HDC hdc)
{
	if (_direction != FAMILIAR_DIRECTION_CASTSKILL)
	{
		_wing->aniRender(hdc, _rc.left, _rc.top, _wingMotion);
		_hair->aniRender(hdc, _rc.left, _rc.top, _hairMotion);
		_body->aniRender(hdc, _rc.left, _rc.top, _bodyMotion);
	}
	else _body->aniRender(hdc, _rc.left, _rc.top, _bodyMotion);

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