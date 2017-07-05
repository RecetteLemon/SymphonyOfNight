#include "stdafx.h"
#include "player.h"


player::player()
{
}


player::~player()
{
}

HRESULT player::init()
{
	// 플레이어 이미지 불러오고~
	_image[0] = IMAGEMANAGER->addFrameImage("player_movement", "image/AlucardPosition_1.bmp", 4000, 4000, 20, 20, true, RGB(255, 0, 255));
	_image[1] = IMAGEMANAGER->addFrameImage("player_act", "image/AlucardAct.bmp", 0, 0, 2000, 2000, 20, 20, true, RGB(255, 0, 255));

	// 행동 초기화
	_playerDir = DIR_RIGHT_STOP;

	// 좌표 초기화
	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;

	// 피격박스 초기화 해주공
	_rc_Hit = RectMakeCenter(_x, _y, _image[0]->getFrameWidth(), _image[0]->getFrameHeight());
	// 공격박스 초기화 해주공
	_rc_Atk = RectMake(0, 0, 0, 0);
	
	// 키 애니 정의 내려주기 시작
	int rightStop[] = { 0, 1, 2, 3, 4, 5, 6 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightStop", "player_movement", rightStop, 7, 10, true);

	int leftStop[] = { 7, 8, 9, 10, 11, 12, 13 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftStop", "player_movement", leftStop, 7, 10, true);

	int rightMoveStart[] = { 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightMoveStart", "player_movement", rightMoveStart, 15, 20, false, rightMoving, this);

	int rightMove[] = { 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightMove", "player_movement", rightMove, 16, 20, true);

	int leftMoveStart[] = { 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftMoveStart", "player_movement", leftMoveStart, 15, 20, false, leftMoving, this);

	int leftMove[] = { 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftMove", "player_movement", leftMove, 16, 20, true);

	_playerMotion = KEYANIMANAGER->findAnimation("playerRightStop");
	_playerMotion->start();

	switch (_playerDir)
	{
	case DIR_RIGHT_STOP: case DIR_RIGHT_MOVE: case DIR_RIGHT_TURN: case DIR_RIGHT_SIT: case DIR_RIGHT_BACKDASH:
	case DIR_RIGHT_JUMP: case DIR_RIGHT_DJUMP: case DIR_RIGHT_SJUMP: case DIR_RIGHT_FALL: case DIR_RIGHT_ATK:
	case DIR_RIGHT_HIT: case DIR_RIGHT_SKILL:
		_fX = _x - _image[0]->getFrameWidth() / 4;
		break;
	case DIR_LEFT_STOP: case DIR_LEFT_MOVE: case DIR_LEFT_TURN: case DIR_LEFT_SIT: case DIR_LEFT_BACKDASH:
	case DIR_LEFT_JUMP: case DIR_LEFT_DJUMP: case DIR_LEFT_SJUMP: case DIR_LEFT_FALL: case DIR_LEFT_ATK:
	case DIR_LEFT_HIT: case DIR_LEFT_SKILL:
		_fX = _x + _image[0]->getFrameWidth() / 4;
		break;
	}

	_fY = _y - 120;

	_fm = new familiarManager;
	_fm->init(&_fX, &_fY);

	setFamiliarDirection();

	return S_OK;
}

void player::release()
{
	_fm->release();
	SAFE_DELETE(_fm);
}

void player::update() 
{
	setFamiliarDirection();

	// 왼쪽으로 움직였을때
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_playerDir = DIR_LEFT_MOVE;
		_playerMotion = KEYANIMANAGER->findAnimation("playerLeftMoveStart");
		_playerMotion->start();
		_fm->setPlayerDirect(1);
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_playerDir = DIR_LEFT_STOP;
		_playerMotion->stop();
		_playerMotion = KEYANIMANAGER->findAnimation("playerLeftStop");
		_playerMotion->start();
		_fm->setPlayerDirect(1);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_playerDir = DIR_RIGHT_MOVE;
		_playerMotion = KEYANIMANAGER->findAnimation("playerRightMoveStart");
		_playerMotion->start();
		_fm->setPlayerDirect(0);
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_playerDir = DIR_RIGHT_STOP;
		_playerMotion->stop();
		_playerMotion = KEYANIMANAGER->findAnimation("playerRightStop");
		_playerMotion->start();
		_fm->setPlayerDirect(0);
	}

	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_fm->selectFamailiar(0);
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		_fm->selectFamailiar(1);
	}
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		_fm->selectFamailiar(2);
	}
	if (KEYMANAGER->isOnceKeyDown('4'))
	{
		_fm->selectFamailiar(3);
	}

	switch (_playerDir)
	{
		case DIR_RIGHT_STOP:

		break;

		case DIR_LEFT_STOP:

		break;

		case DIR_RIGHT_MOVE:
			_x += MOVESPEED;
			_rc_Hit = RectMakeCenter(_x, _y, _image[0]->getFrameWidth(), _image[0]->getFrameHeight());
		break;

		case DIR_LEFT_MOVE:
			_x -= MOVESPEED;
			_rc_Hit = RectMakeCenter(_x, _y, _image[0]->getFrameWidth(), _image[0]->getFrameHeight());
		break;
	}


	_fm->update();
}

void player::render() 
{
	_fm->render();
	_image[0]->aniRender(getMemDC(), _x - _image[0]->getFrameWidth() / 2, _y - _image[0]->getFrameHeight(), _playerMotion);

	// 플레이어 위치 보정해야됨.
//	if (KEYANIMANAGER->findAnimation("playerRightMove"))
}

void player::rightMoving(void* obj)
{
	player* p = (player*)obj;


	p->setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightMove"));
//	p->getPlayerMotion()->setFramePos(2);
	p->getPlayerMotion()->start();
}

void player::leftMoving(void* obj)
{
	player* p = (player*)obj;

	p->setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftMove"));
//	p->getPlayerMotion()->setFramePos(2);
	p->getPlayerMotion()->start();
}

void player::setFamiliarDirection(void)
{
	switch (_playerDir)
	{
	case DIR_RIGHT_STOP: case DIR_RIGHT_MOVE: case DIR_RIGHT_TURN: case DIR_RIGHT_SIT: case DIR_RIGHT_BACKDASH:
	case DIR_RIGHT_JUMP: case DIR_RIGHT_DJUMP: case DIR_RIGHT_SJUMP: case DIR_RIGHT_FALL: case DIR_RIGHT_ATK:
	case DIR_RIGHT_HIT: case DIR_RIGHT_SKILL:
		_fm->setPlayerDirect(0);
		_fX = _x - _image[0]->getFrameWidth() / 4;
		break;
	case DIR_LEFT_STOP: case DIR_LEFT_MOVE: case DIR_LEFT_TURN: case DIR_LEFT_SIT: case DIR_LEFT_BACKDASH:
	case DIR_LEFT_JUMP: case DIR_LEFT_DJUMP: case DIR_LEFT_SJUMP: case DIR_LEFT_FALL: case DIR_LEFT_ATK:
	case DIR_LEFT_HIT: case DIR_LEFT_SKILL:
		_fX = _x + _image[0]->getFrameWidth() / 4;
		_fm->setPlayerDirect(1);
		break;
	}
	
	_fY = _y - 120;
}