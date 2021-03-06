#include "stdafx.h"
#include "player.h"


player::player()
{
}


player::~player()
{
}

HRESULT player::init(float x, float y)
{
	// 플레이어 이미지 불러오고~
	_image[0] = IMAGEMANAGER->addFrameImage("player_movement", "image/AlucardPosition.bmp", 4000, 4000, 20, 20, true, RGB(255, 0, 255));
	_image[1] = IMAGEMANAGER->addFrameImage("player_act", "image/AlucardAct.bmp", 0, 0, 2000, 2000, 20, 20, true, RGB(255, 0, 255));

	// 행동 초기화
	_playerDir = DIR_RIGHT_STOP;

	// 좌표 초기화
	_x = x;
	_y = y;

	_gravity = 0;

	// 피격박스 초기화 해주공
	_rc_Hit = RectMakeCenter(_x, _y - 50, 50, 100);
	// 공격박스 초기화 해주공
	_rc_Atk = RectMake(0, 0, 0, 0);
	
	// 키 애니 정의 내려주기 시작

	// 오른쪽

	// 걷는부분
	int rightStop[] = { 0, 1, 2, 3, 4, 5, 6 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightStop", "player_movement", rightStop, 7, 10, true);

	int rightMoveStart[] = { 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightMoveStart", "player_movement", rightMoveStart, 15, 20, false, rightMoving, this);

	int rightTurn[] = { 140, 141, 142, 143, 144, 145, 146, 147, 148, 149 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightTurn", "player_movement", rightTurn, 10, 15, false, rightMoving, this);

	int rightMove[] = { 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightMove", "player_movement", rightMove, 16, 20, true);

	int rightStopStart[] = { 20, 21, 22, 23, 24, 25, 26, 27 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightStopStart", "player_movement", rightStopStart, 8, 15, false, rightStopping, this);

	// 앉는부분
	int rightSitDown[] = { 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightSitDown", "player_movement", rightSitDown, 13, 20, false);

	int rightStandUp[] = { 193, 194, 195, 196 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightStandUp", "player_movement", rightStandUp, 4, 10, false, rightStopping, this);

	// 점프부분
	int rightNormalJump[] = { 260, 261, 262, 263, 264, 265 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightNormalJump", "player_movement", rightNormalJump, 6, 10, false, rightFalling, this);

	int rightMoveJump[] = { 280, 281, 282, 283 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightMoveJump", "player_movement", rightMoveJump, 4, 10, false, rightFalling, this);

	int rightFall[] = { 320, 321, 322, 323, 324, 325, 326, 327, 328 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightFall", "player_movement", rightFall, 9, 20, false);

	int rightLanding[] = { 329, 330, 331, 332, 333 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightLanding", "player_movement", rightLanding, 5, 15, false, rightStopping, this);


	// 왼쪽

	// 걷는부분
	int leftStop[] = { 7, 8, 9, 10, 11, 12, 13 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftStop", "player_movement", leftStop, 7, 10, true);

	int leftMoveStart[] = { 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftMoveStart", "player_movement", leftMoveStart, 15, 20, false, leftMoving, this);

	int leftTurn[] = { 160, 161, 162, 163, 164, 165, 166, 167, 168, 169 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftTurn", "player_movement", leftTurn, 10, 15, false, leftMoving, this);

	int leftMove[] = { 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftMove", "player_movement", leftMove, 16, 20, true);

	int leftStopStart[] = { 28, 29, 30, 31, 32, 33, 34, 35 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftStopStart", "player_movement", leftStopStart, 8, 15, false, leftStopping, this);

	// 앉는부분
	int leftSitDown[] = { 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftSitDown", "player_movement", leftSitDown, 13, 20, false);

	int leftStandUp[] = { 213, 214, 215, 216 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftStandUp", "player_movement", leftStandUp, 4, 10, false, leftStopping, this);

	// 점프부분
	int leftNormalJump[] = { 266, 267, 268, 269, 270, 271 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftNormalJump", "player_movement", leftNormalJump, 6, 10, false, leftFalling, this);

	int leftMoveJump[] = { 284, 285, 286, 287 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftMoveJump", "player_movement", leftMoveJump, 4, 10, false, leftFalling, this);

	int leftFall[] = { 340, 341, 342, 343, 344, 345, 346, 347, 348 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftFall", "player_movement", leftFall, 9, 20, false);

	int leftLanding[] = { 349, 350, 351, 352, 353 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftLanding", "player_movement", leftLanding, 5, 15, false, leftStopping, this);


	// 모션 초기화
	_playerMotion = KEYANIMANAGER->findAnimation("playerRightStop");
	_playerMotion->start();

	switch (_playerDir)
	{
	case DIR_RIGHT_STOP: case DIR_RIGHT_MOVE: case DIR_RIGHT_SIT: case DIR_RIGHT_BACKDASH:
	case DIR_RIGHT_JUMP: case DIR_RIGHT_FALL: case DIR_RIGHT_ATK:
	case DIR_RIGHT_HIT: case DIR_RIGHT_SKILL:
		_fX = _x - _image[0]->getFrameWidth() / 4;
		break;
	case DIR_LEFT_STOP: case DIR_LEFT_MOVE: case DIR_LEFT_SIT: case DIR_LEFT_BACKDASH:
	case DIR_LEFT_JUMP: case DIR_LEFT_FALL: case DIR_LEFT_ATK:
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
	// 플레이어 맞는 렉트는 항상 고정
	_rc_Hit = RectMakeCenter(_x, _y - 50, 50, 100);

	// 왼쪽 방향키를 눌렀을때
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		// 플레이어가 앉은 상태가 아니면 움직일 수 있는 상태
		if (_playerDir != DIR_RIGHT_SIT && _playerDir != DIR_LEFT_SIT)
		{
			// 왼쪽 벽에 안닿았으면 움직이게 하자
			if (_collision.HorizontalCollision(_rc_Hit, _x, _y, IMAGEMANAGER->findImage("map")) != LEFT) _x -= MOVESPEED;
		}

		// 오른쪽으로 앉았는데 왼쪽 방향키 눌렀으면
		if (_playerDir == DIR_RIGHT_SIT)
		{
			// 왼쪽 앉은 상태로 바꿔주자
			_playerDir = DIR_LEFT_SIT;
			_playerMotion = KEYANIMANAGER->findAnimation("playerLeftSitDown");
			_playerMotion->start();
		}

		// 왼쪽으로 멈춰있는 상태면 움직이게 하자
		if (_playerDir == DIR_LEFT_STOP)
		{
			_playerMotion->stop();
			_playerDir = DIR_LEFT_MOVE;
			_playerMotion = KEYANIMANAGER->findAnimation("playerLeftMoveStart");
			_playerMotion->start();
			
		}
		// 만약 오른쪽으로 멈춰있는 상태면
		else if (_playerDir == DIR_RIGHT_STOP)
		{
			// 뒤돌아서서 가는 모션을 취하고 왼쪽으로 움직이는 상태로 만들자
			_playerMotion->stop();
			_playerDir = DIR_LEFT_MOVE;
			_playerMotion = KEYANIMANAGER->findAnimation("playerLeftTurn");
			_playerMotion->start();
		}
	}
	// 키 안눌렀는데 왼쪽으로 움직이는 상태면
	else if (!KEYMANAGER->isStayKeyDown(VK_LEFT) && _playerDir == DIR_LEFT_MOVE)
	{
		// 멈춰주자
		_playerMotion->stop();
		_playerDir = DIR_LEFT_STOP;
		_playerMotion = KEYANIMANAGER->findAnimation("playerLeftStopStart");
		_playerMotion->start();
	}


	// 오른쪽 방향키를 눌렀을때
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		// 앉아있는 상태가 아니라면
		if (_playerDir != DIR_RIGHT_SIT && _playerDir != DIR_LEFT_SIT)
		{
			// 오른쪽 벽에 부딪히지 않는 상태면 움직이게 해주자
			if (_collision.HorizontalCollision(_rc_Hit, _x, _y, IMAGEMANAGER->findImage("map")) != RIGHT) _x += MOVESPEED;
		}

		// 왼쪽으로 앉아있는 상태면
		if (_playerDir == DIR_LEFT_SIT)
		{
			// 오른쪽으로 앉아서 보게하자
			_playerDir = DIR_RIGHT_SIT;
			_playerMotion = KEYANIMANAGER->findAnimation("playerRightSitDown");
			_playerMotion->start();
		}
		
		// 오른쪽으로 서있는 상태면
		if (_playerDir == DIR_RIGHT_STOP)
		{
			// 움직이는 상태로 바꿔주자
			_playerMotion->stop();
			_playerMotion = KEYANIMANAGER->findAnimation("playerRightMoveStart");
			_playerMotion->start();
			_playerDir = DIR_RIGHT_MOVE;
			
		}
		// 왼쪽으로 서있는 상태면
		else if (_playerDir == DIR_LEFT_STOP)
		{
			// 오른쪽으로 돌아서는 모션을 취하고 오른쪽으로 움직이는 상태로 바꿔주자
			_playerMotion->stop();
			_playerMotion = KEYANIMANAGER->findAnimation("playerRightTurn");
			_playerMotion->start();
			_playerDir = DIR_RIGHT_MOVE;
		}
	}
	// 키 안눌렀는데 오른쪽으로 움직이는 상태면
	else if (!KEYMANAGER->isStayKeyDown(VK_RIGHT) && _playerDir == DIR_RIGHT_MOVE)
	{
		// 멈춰주자
		_playerDir = DIR_RIGHT_STOP;
		_playerMotion->stop();
		_playerMotion = KEYANIMANAGER->findAnimation("playerRightStopStart");
		_playerMotion->start();
	}


	// 아래 방향키를 눌렀을때
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		// 방향마다 서있는 상태면 앉게 해주자
		if (_playerDir == DIR_RIGHT_STOP)
		{
			_playerMotion->stop();
			_playerDir = DIR_RIGHT_SIT;
			_playerMotion = KEYANIMANAGER->findAnimation("playerRightSitDown");
			_playerMotion->start();
		}
		else if (_playerDir == DIR_LEFT_STOP)
		{
			_playerMotion->stop();
			_playerDir = DIR_LEFT_SIT;
			_playerMotion = KEYANIMANAGER->findAnimation("playerLeftSitDown");
			_playerMotion->start();
		}
	}
	// 아래 방향키를 땠을때
	else if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		// 방향마다 서있는 상태로 바꿔주자
		if (_playerDir == DIR_RIGHT_SIT)
		{
			_playerMotion->stop();
			_playerDir = DIR_RIGHT_STOP;
			_playerMotion = KEYANIMANAGER->findAnimation("playerRightStandUp");
			_playerMotion->start();
		}
		else if (_playerDir == DIR_LEFT_SIT)
		{
			_playerMotion->stop();
			_playerDir = DIR_LEFT_STOP;
			_playerMotion = KEYANIMANAGER->findAnimation("playerLeftStandUp");
			_playerMotion->start();
		}
	}

	// 점프키 눌렀을때
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		// 서있을때 점프냐!
		if (_playerDir == DIR_RIGHT_STOP)
		{
			_playerMotion->stop();
			_playerDir = DIR_RIGHT_JUMP;
			_playerMotion = KEYANIMANAGER->findAnimation("playerRightNormalJump");
			_playerMotion->start();
		}
		else if (_playerDir == DIR_LEFT_STOP)
		{
			_playerMotion->stop();
			_playerDir = DIR_LEFT_JUMP;
			_playerMotion = KEYANIMANAGER->findAnimation("playerLeftNormalJump");
			_playerMotion->start();
		}
		// 아님 움직이면서 점프냐!
		else if (_playerDir == DIR_RIGHT_MOVE)
		{
			_playerMotion->stop();
			_playerDir = DIR_RIGHT_MOVE_JUMP;
			_playerMotion = KEYANIMANAGER->findAnimation("playerRightMoveJump");
			_playerMotion->start();
		}
		else if (_playerDir == DIR_LEFT_MOVE)
		{
			_playerMotion->stop();
			_playerDir = DIR_LEFT_MOVE_JUMP;
			_playerMotion = KEYANIMANAGER->findAnimation("playerLeftMoveJump");
			_playerMotion->start();
		}
	}
	// 중간에 점프를 멈출경우(실제게임도 비슷하게 이럼)
	else if (KEYMANAGER->isOnceKeyUp('Z'))
	{
		if (_playerDir == DIR_RIGHT_JUMP || _playerDir == DIR_RIGHT_MOVE_JUMP)
		{
			_playerMotion->stop();
			_playerDir = DIR_RIGHT_FALL;
			_playerMotion = KEYANIMANAGER->findAnimation("playerRightFall");
			_playerMotion->start();
		}
		else if (_playerDir == DIR_LEFT_JUMP || _playerDir == DIR_LEFT_MOVE_JUMP)
		{
			_playerMotion->stop();
			_playerDir = DIR_LEFT_FALL;
			_playerMotion = KEYANIMANAGER->findAnimation("playerLeftFall");
			_playerMotion->start();
		}
	}


	switch (_playerDir)
	{
		case DIR_RIGHT_STOP:
			if (_collision.VerticalCollision(_rc_Hit, _x, _y, IMAGEMANAGER->findImage("map")) != BOTTOM)
			{
				_playerDir = DIR_RIGHT_FALL;
				setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightFall"));
				getPlayerMotion()->start();
			}
			else
			{
				// y 좌표 바닥에 놓기
				_y = _collision.setPlayerVertical(_rc_Hit, _x, _y, IMAGEMANAGER->findImage("map"));
			}
		break;

		case DIR_LEFT_STOP:
			if (_collision.VerticalCollision(_rc_Hit, _x, _y, IMAGEMANAGER->findImage("map")) != BOTTOM)
			{
				_playerDir = DIR_LEFT_FALL;
				setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftFall"));
				getPlayerMotion()->start();
			}
			else
			{
//				// y 좌표 바닥에 놓기
				_y = _collision.setPlayerVertical(_rc_Hit, _x, _y, IMAGEMANAGER->findImage("map"));
			}
		break;

		case DIR_RIGHT_MOVE:
			if (_collision.VerticalCollision(_rc_Hit, _x, _y, IMAGEMANAGER->findImage("map")) != BOTTOM)
			{
				_playerDir = DIR_RIGHT_FALL;
				setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightFall"));
				getPlayerMotion()->start();
			}
			else
			{
				// y 좌표 바닥에 놓기
				_y = _collision.setPlayerVertical(_rc_Hit, _x, _y, IMAGEMANAGER->findImage("map"));
			}
		break;

		case DIR_LEFT_MOVE:
			if (_collision.VerticalCollision(_rc_Hit, _x, _y, IMAGEMANAGER->findImage("map")) != BOTTOM)
			{
				_playerDir = DIR_LEFT_FALL;
				setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftFall"));
				getPlayerMotion()->start();
			}
			else
			{
				// y 좌표 바닥에 놓기
				_y = _collision.setPlayerVertical(_rc_Hit, _x, _y, IMAGEMANAGER->findImage("map"));
			}
		break;

		case DIR_RIGHT_MOVE_JUMP:
		
		case DIR_RIGHT_JUMP: 
			if (_collision.VerticalCollision(_rc_Hit, _x, _y, IMAGEMANAGER->findImage("map")) != TOP) _y -= JUMPFORCE;
		break;

		case DIR_RIGHT_FALL: 
		{
			_gravity += GRAVITYPOWER * TIMEMANAGER->getElapsedTime();
			_y += _gravity;

			// 여기에 픽셀충돌 했는지 안했는지 넣으면 됨
			if (_collision.VerticalCollision(_rc_Hit, _x, _y, IMAGEMANAGER->findImage("map")) == BOTTOM)
			{
				_gravity = 0;

				_playerMotion->stop();
				_playerDir = DIR_RIGHT_STOP;
				_playerMotion = KEYANIMANAGER->findAnimation("playerRightLanding");
				_playerMotion->start();
			}
		}
		break;

		case DIR_LEFT_MOVE_JUMP:

		case DIR_LEFT_JUMP:
			if (_collision.VerticalCollision(_rc_Hit, _x, _y, IMAGEMANAGER->findImage("map")) != TOP) _y -= JUMPFORCE;
		break;

		case DIR_LEFT_FALL:
		{
			_gravity += GRAVITYPOWER * TIMEMANAGER->getElapsedTime();
			_y += _gravity;

			// 여기에 픽셀충돌 했는지 안했는지 넣으면 됨
			if (_collision.VerticalCollision(_rc_Hit, _x, _y, IMAGEMANAGER->findImage("map")) == BOTTOM)
			{
				_gravity = 0;

				_playerMotion->stop();
				_playerDir = DIR_LEFT_STOP;
				_playerMotion = KEYANIMANAGER->findAnimation("playerLeftLanding");
				_playerMotion->start();
			}
		}
		break;
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

	_fm->update();

	
}

void player::render() 
{
//	Rectangle(getMemDC(), _rc_Hit.left, _rc_Hit.top, _rc_Hit.right, _rc_Hit.bottom);
	_fm->render();

	char str[500];
	sprintf(str, "%.2f %.2f / %d %d", _x, _y, _image[0]->getFrameWidth(), _image[0]->getFrameHeight());
	TextOut(getMemDC(), _x - 75, _y - 100, str, strlen(str));

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

void player::rightStopping(void* obj)
{
	player* p = (player*)obj;

	p->_playerDir = DIR_RIGHT_STOP;
	p->setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightStop"));
	p->getPlayerMotion()->start();
}

void player::leftStopping(void * obj)
{
	player* p = (player*)obj;

	p->_playerDir = DIR_LEFT_STOP;
	p->setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftStop"));
	p->getPlayerMotion()->start();
}

void player::rightFalling(void* obj)
{
	player* p = (player*)obj;

	p->_playerDir = DIR_RIGHT_FALL;
	p->setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightFall"));
	p->getPlayerMotion()->start();
}

void player::leftFalling(void * obj)
{
	player* p = (player*)obj;

	p->_playerDir = DIR_LEFT_FALL;
	p->setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftFall"));
	p->getPlayerMotion()->start();
}

void player::setFamiliarDirection(void)
{
	switch (_playerDir)
	{
	case DIR_RIGHT_STOP: case DIR_RIGHT_MOVE: case DIR_RIGHT_SIT: case DIR_RIGHT_BACKDASH:
	case DIR_RIGHT_JUMP: case DIR_RIGHT_FALL: case DIR_RIGHT_ATK:
	case DIR_RIGHT_HIT: case DIR_RIGHT_SKILL:
		_fm->setPlayerDirect(0);
		_fX = _x - _image[0]->getFrameWidth() / 4;
		break;
	case DIR_LEFT_STOP: case DIR_LEFT_MOVE: case DIR_LEFT_SIT: case DIR_LEFT_BACKDASH:
	case DIR_LEFT_JUMP: case DIR_LEFT_FALL: case DIR_LEFT_ATK:
	case DIR_LEFT_HIT: case DIR_LEFT_SKILL:
		_fX = _x + _image[0]->getFrameWidth() / 4;
		_fm->setPlayerDirect(1);
		break;
	}

	_fY = _y - 120;
}