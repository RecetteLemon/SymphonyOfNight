#include "stdafx.h"
#include "player.h"


player::player()
{
}


player::~player()
{
}

HRESULT player::init(float x, float y, image* img, bool isOp)
{
	_isOp = isOp;

	// �÷��̾� �̹��� �ҷ�����~
	_image[0] = IMAGEMANAGER->addFrameImage("player_movement", "image/AlucardPosition.bmp", 4000, 4000, 20, 20, true, RGB(255, 0, 255));
	_image[1] = IMAGEMANAGER->addFrameImage("player_act", "image/AlucardAct.bmp", 0, 0, 4000, 4000, 20, 20, true, RGB(255, 0, 255));

	// �ൿ �ʱ�ȭ
	_playerDir = DIR_RIGHT_STOP;

	// ��ǥ �ʱ�ȭ
	_x = x;
	_y = y;

	_gravity = 0;
	_jumpForce = 0;
	isDjump = false;

	_imageName = NULL;
	_imageName = img;

	// �ǰݹڽ� �ʱ�ȭ ���ְ�
	_rc_Hit = RectMakeCenter(_x, _y - 50, 50, 100);
	// ���ݹڽ� �ʱ�ȭ ���ְ�
	_rc_Atk = RectMake(0, 0, 0, 0);

	// Ŀ�ǵ� �ʱ�ȭ
	ZeroMemory(&_vCommand, sizeof(_vCommand));
	ZeroMemory(&_viCommand, sizeof(_viCommand));
	_currentInput = _prevInput = INPUT_NOT;
	keyTimer = 0;
	
	// Ű �ִ� ���� �����ֱ� ����

	// ������

	// ���ִºκ�
	int rightStop[] = { 0, 1, 2, 3, 4, 5, 6 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightStop", "player_movement", rightStop, 7, 10, true);

	int rightStairsStop[] = { 40, 41, 42, 43 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightStairsStop", "player_movement", rightStairsStop, 4, 10, true);

	// �ȴºκ�
	if (!_isOp)
	{
		int rightMoveStart[] = { 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74 };
		KEYANIMANAGER->addArrayFrameAnimation("playerRightMoveStart", "player_movement", rightMoveStart, 15, 20, false, rightMoving, this);
	}
	else
	{
		int rightMoveStart[] = { 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74 };
		KEYANIMANAGER->addArrayFrameAnimation("playerRightMoveStart", "player_movement", rightMoveStart, 15, 10, false, rightMoving, this);
	}

	int rightTurn[] = { 140, 141, 142, 143, 144, 145, 146, 147, 148, 149 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightTurn", "player_movement", rightTurn, 10, 15, false, rightMoving, this);

	int rightMove[] = { 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightMove", "player_movement", rightMove, 16, 20, true);

	int rightStopStart[] = { 20, 21, 22, 23, 24, 25, 26, 27 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightStopStart", "player_movement", rightStopStart, 8, 15, false, rightStopping, this);

	// �ɴºκ�
	int rightSitDown[] = { 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightSitDown", "player_movement", rightSitDown, 13, 20, false);

	int rightStandUp[] = { 193, 194, 195, 196 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightStandUp", "player_movement", rightStandUp, 4, 10, false, rightStopping, this);

	// �����κ�
	int rightNormalJump[] = { 260, 261, 262, 263, 264, 265 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightNormalJump", "player_movement", rightNormalJump, 6, 15, false, rightFalling, this);

	int rightMoveJump[] = { 280, 281, 282, 283 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightMoveJump", "player_movement", rightMoveJump, 4, 10, false, rightFalling, this);

	int rightDoubleJump[] = { 288, 289, 290, 291, 292 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightDoubleJump", "player_movement", rightDoubleJump, 5, 25, false, rightFalling, this);

	int rightFall[] = { 320, 321, 322, 323, 324, 325, 326, 327, 328 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightFall", "player_movement", rightFall, 9, 20, false);

	// ��������
	int rightSuperJump[] = { 300, 301, 302 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightSuperJump", "player_movement", rightSuperJump, 3, 10, false, rightFalling, this);

	int rightCrash[] = { 303, 304, 305 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightCrash", "player_movement", rightCrash, 3, 10, false, rightFalling, this);

	int rightLanding[] = { 329, 330, 331, 332, 333 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightLanding", "player_movement", rightLanding, 5, 15, false, rightStopping, this);

	// ��뽬
	int rightBackDash[] = { 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightBackDash", "player_movement", rightBackDash, 13, 25, false, rightStopping, this);

	// ����!
	int rightStandAttack[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightStandAttack", "player_act", rightStandAttack, 11, 20, false, rightStopping, this);

	int rightSitAttack[] = { 40, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightSitAttack", "player_act", rightSitAttack, 11, 20, false, rightSitting, this);

	int rightAirAttack[] = { 80, 81, 82, 83 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightAirAttack", "player_act", rightAirAttack, 4, 15, false, rightFalling, this);

	// ����

	// ���ִºκ�
	int leftStop[] = { 7, 8, 9, 10, 11, 12, 13 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftStop", "player_movement", leftStop, 7, 10, true);

	int leftStairsStop[] = { 44, 45, 46, 47 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftStairsStop", "player_movement", leftStairsStop, 4, 10, true);

	// �ȴºκ�
	int leftMoveStart[] = { 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftMoveStart", "player_movement", leftMoveStart, 15, 20, false, leftMoving, this);

	int leftTurn[] = { 160, 161, 162, 163, 164, 165, 166, 167, 168, 169 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftTurn", "player_movement", leftTurn, 10, 15, false, leftMoving, this);

	int leftMove[] = { 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftMove", "player_movement", leftMove, 16, 20, true);

	int leftStopStart[] = { 28, 29, 30, 31, 32, 33, 34, 35 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftStopStart", "player_movement", leftStopStart, 8, 15, false, leftStopping, this);

	// �ɴºκ�
	int leftSitDown[] = { 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftSitDown", "player_movement", leftSitDown, 13, 20, false);

	int leftStandUp[] = { 213, 214, 215, 216 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftStandUp", "player_movement", leftStandUp, 4, 10, false, leftStopping, this);

	// �����κ�
	int leftNormalJump[] = { 266, 267, 268, 269, 270, 271 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftNormalJump", "player_movement", leftNormalJump, 6, 15, false, leftFalling, this);

	int leftMoveJump[] = { 284, 285, 286, 287 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftMoveJump", "player_movement", leftMoveJump, 4, 10, false, leftFalling, this);

	int leftDoubleJump[] = { 293, 294, 295, 296, 297 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftDoubleJump", "player_movement", leftDoubleJump, 5, 25, false, leftFalling, this);

	int leftFall[] = { 340, 341, 342, 343, 344, 345, 346, 347, 348 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftFall", "player_movement", leftFall, 9, 20, false);

	// ��������
	int leftSuperJump[] = { 306, 307, 308 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftSuperJump", "player_movement", leftSuperJump, 3, 10, false, leftFalling, this);

	int leftCrash[] = { 309, 310, 311 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftCrash", "player_movement", leftCrash, 3, 10, false, leftFalling, this);

	int leftLanding[] = { 349, 350, 351, 352, 353 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftLanding", "player_movement", leftLanding, 5, 15, false, leftStopping, this);

	// ��뽬
	int leftBackDash[] = { 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftBackDash", "player_movement", leftBackDash, 13, 25, false, leftStopping, this);

	// ����!
	int leftStandAttack[] = { 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftStandAttack", "player_act", leftStandAttack, 11, 20, false, leftStopping, this);

	int leftSitAttack[] = { 60, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftSitAttack", "player_act", leftSitAttack, 11, 20, false, leftSitting, this);

	int leftAirAttack[] = { 84, 85, 86, 87 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftAirAttack", "player_act", leftAirAttack, 4, 15, false, leftFalling, this);
	

	// �۹и��� ����
	switch (_playerDir)
	{
	case DIR_RIGHT_STOP: case DIR_RIGHT_MOVE: case DIR_RIGHT_SIT: case DIR_RIGHT_BACKDASH:
	case DIR_RIGHT_JUMP: case DIR_RIGHT_MOVE_JUMP: case DIR_RIGHT_SUPER_JUMP: case DIR_RIGHT_FALL:
	case DIR_RIGHT_ATK: case DIR_RIGHT_AIR_ATK: case DIR_RIGHT_HIT: case DIR_RIGHT_SKILL:
		_fX = _x - _image[0]->getFrameWidth() / 4;
		break;
	case DIR_LEFT_STOP: case DIR_LEFT_MOVE: case DIR_LEFT_SIT: case DIR_LEFT_BACKDASH:
	case DIR_LEFT_JUMP: case DIR_LEFT_MOVE_JUMP: case DIR_LEFT_SUPER_JUMP: case DIR_LEFT_FALL:
	case DIR_LEFT_ATK: case DIR_LEFT_AIR_ATK: case DIR_LEFT_HIT: case DIR_LEFT_SKILL:
		_fX = _x + _image[0]->getFrameWidth() / 4;
		break;
	}

	if (!_isOp)
	{
		// ��� �ʱ�ȭ
		_playerMotion = KEYANIMANAGER->findAnimation("playerRightStop");
		_playerMotion->start();

		_fY = _y - 120;

		_fm = new familiarManager;
		_fm->init(&_fX, &_fY);

		setFamiliarDirection();
	}
	else
	{
		_playerMotion = KEYANIMANAGER->findAnimation("playerRightMoveStart");
		_playerMotion->start();
	}

	return S_OK;
}

void player::release()
{
	if (!_isOp)
	{
		_fm->release();
		SAFE_DELETE(_fm);
	}
}

void player::update() 
{
	// �÷��̾� �´� ��Ʈ�� �׻� ����
	_rc_Hit = RectMakeCenter(_x, _y - 50, 50, 100);

	if (_isOp)
	{
		opening();
	}
	else
	{
		setFamiliarDirection();

		// ���� ����Ű�� ��������
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			// �÷��̾ ���� ���°� �ƴϸ� ������ �� �ִ� ����
			if (_playerDir != DIR_RIGHT_SIT && _playerDir != DIR_LEFT_SIT && _playerDir != DIR_RIGHT_BACKDASH && _playerDir != DIR_LEFT_BACKDASH &&
				_playerDir != DIR_RIGHT_SUPER_JUMP && _playerDir != DIR_LEFT_SUPER_JUMP && _playerDir != DIR_RIGHT_ATK && _playerDir != DIR_LEFT_ATK)
			{
				// ���� ���� �ȴ������ �����̰� ����
				if (_collision.HorizontalCollision(_rc_Hit, _x, _y, _imageName) != LEFT) _x -= MOVESPEED;
			}

			// ���������� �ɾҴµ� ���� ����Ű ��������
			if (_playerDir == DIR_RIGHT_SIT)
			{
				// ���� ���� ���·� �ٲ�����
				_playerDir = DIR_LEFT_SIT;
				_playerMotion = KEYANIMANAGER->findAnimation("playerLeftSitDown");
				_playerMotion->start();
			}

			// �������� �����ִ� ���¸� �����̰� ����
			if (_playerDir == DIR_LEFT_STOP)
			{
				_playerMotion->stop();
				_playerDir = DIR_LEFT_MOVE;
				_playerMotion = KEYANIMANAGER->findAnimation("playerLeftMoveStart");
				_playerMotion->start();

			}
			// ���� ���������� �����ִ� ���¸�
			else if (_playerDir == DIR_RIGHT_STOP)
			{
				// �ڵ��Ƽ��� ���� ����� ���ϰ� �������� �����̴� ���·� ������
				_playerMotion->stop();
				_playerDir = DIR_LEFT_MOVE;
				_playerMotion = KEYANIMANAGER->findAnimation("playerLeftTurn");
				_playerMotion->start();
			}

			if (_playerDir == DIR_RIGHT_FALL)
			{
				DWORD num;

				_playerDir = DIR_LEFT_FALL;
				num = _playerMotion->getNowFrame();
				_playerMotion = KEYANIMANAGER->findAnimation("playerLeftFall");
				_playerMotion->start();
				_playerMotion->setNowFrame(num);
			}
			else if (_playerDir == DIR_RIGHT_JUMP)
			{
				DWORD num;

				_playerDir = DIR_LEFT_JUMP;
				num = _playerMotion->getNowFrame();
				_playerMotion = KEYANIMANAGER->findAnimation("playerLeftNormalJump");
				_playerMotion->start();
				_playerMotion->setNowFrame(num);
			}
			else if (_playerDir == DIR_RIGHT_MOVE_JUMP)
			{
				DWORD num;

				_playerDir = DIR_LEFT_MOVE_JUMP;
				num = _playerMotion->getNowFrame();
				_playerMotion = KEYANIMANAGER->findAnimation("playerLeftMoveJump");
				_playerMotion->start();
				_playerMotion->setNowFrame(num);
			}
		}
		// Ű �ȴ����µ� �������� �����̴� ���¸�
		else if (!KEYMANAGER->isStayKeyDown(VK_LEFT) && _playerDir == DIR_LEFT_MOVE)
		{
			// ��������
			_playerMotion->stop();
			_playerDir = DIR_LEFT_STOP;
			_playerMotion = KEYANIMANAGER->findAnimation("playerLeftStopStart");
			_playerMotion->start();
		}


		// ������ ����Ű�� ��������
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			// �ɾ��ִ� ���°� �ƴ϶��
			if (_playerDir != DIR_RIGHT_SIT && _playerDir != DIR_LEFT_SIT && _playerDir != DIR_RIGHT_BACKDASH && _playerDir != DIR_LEFT_BACKDASH &&
				_playerDir != DIR_RIGHT_SUPER_JUMP && _playerDir != DIR_LEFT_SUPER_JUMP && _playerDir != DIR_RIGHT_ATK && _playerDir != DIR_LEFT_ATK)
			{
				// ������ ���� �ε����� �ʴ� ���¸� �����̰� ������
				if (_collision.HorizontalCollision(_rc_Hit, _x, _y, _imageName) != RIGHT) _x += MOVESPEED;
			}

			// �������� �ɾ��ִ� ���¸�
			if (_playerDir == DIR_LEFT_SIT)
			{
				// ���������� �ɾƼ� ��������
				_playerDir = DIR_RIGHT_SIT;
				_playerMotion = KEYANIMANAGER->findAnimation("playerRightSitDown");
				_playerMotion->start();
			}

			// ���������� ���ִ� ���¸�
			if (_playerDir == DIR_RIGHT_STOP)
			{
				// �����̴� ���·� �ٲ�����
				_playerMotion->stop();
				_playerMotion = KEYANIMANAGER->findAnimation("playerRightMoveStart");
				_playerMotion->start();
				_playerDir = DIR_RIGHT_MOVE;

			}
			// �������� ���ִ� ���¸�
			else if (_playerDir == DIR_LEFT_STOP)
			{
				// ���������� ���Ƽ��� ����� ���ϰ� ���������� �����̴� ���·� �ٲ�����
				_playerMotion->stop();
				_playerMotion = KEYANIMANAGER->findAnimation("playerRightTurn");
				_playerMotion->start();
				_playerDir = DIR_RIGHT_MOVE;
			}

			if (_playerDir == DIR_LEFT_FALL)
			{
				DWORD num;

				_playerDir = DIR_RIGHT_FALL;
				num = _playerMotion->getNowFrame();
				_playerMotion = KEYANIMANAGER->findAnimation("playerRightFall");
				_playerMotion->start();
				_playerMotion->setNowFrame(num);
			}
			else if (_playerDir == DIR_LEFT_JUMP)
			{
				DWORD num;

				_playerDir = DIR_RIGHT_JUMP;
				num = _playerMotion->getNowFrame();
				_playerMotion = KEYANIMANAGER->findAnimation("playerRightNormalJump");
				_playerMotion->start();
				_playerMotion->setNowFrame(num);
			}
			else if (_playerDir == DIR_LEFT_MOVE_JUMP)
			{
				DWORD num;

				_playerDir = DIR_RIGHT_MOVE_JUMP;
				num = _playerMotion->getNowFrame();
				_playerMotion = KEYANIMANAGER->findAnimation("playerRightMoveJump");
				_playerMotion->start();
				_playerMotion->setNowFrame(num);
			}
		}
		// Ű �ȴ����µ� ���������� �����̴� ���¸�
		else if (!KEYMANAGER->isStayKeyDown(VK_RIGHT) && _playerDir == DIR_RIGHT_MOVE)
		{
			// ��������
			_playerDir = DIR_RIGHT_STOP;
			_playerMotion->stop();
			_playerMotion = KEYANIMANAGER->findAnimation("playerRightStopStart");
			_playerMotion->start();
		}


		// �Ʒ� ����Ű�� ��������
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			// ���⸶�� ���ִ� ���¸� �ɰ� ������
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
		// �Ʒ� ����Ű�� ������
		else if (!KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			// ���⸶�� ���ִ� ���·� �ٲ�����
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

		// ����Ű ��������
		if (KEYMANAGER->isOnceKeyDown('Z') && !isDjump)
		{
			// �������� ������!
			if (_playerDir == DIR_RIGHT_STOP)
			{
				_jumpForce = JUMPFORCE;
				_playerMotion->stop();
				_playerDir = DIR_RIGHT_JUMP;
				_playerMotion = KEYANIMANAGER->findAnimation("playerRightNormalJump");
				_playerMotion->start();
			}
			else if (_playerDir == DIR_LEFT_STOP)
			{
				_jumpForce = JUMPFORCE;
				_playerMotion->stop();
				_playerDir = DIR_LEFT_JUMP;
				_playerMotion = KEYANIMANAGER->findAnimation("playerLeftNormalJump");
				_playerMotion->start();
			}
			// �ƴ� �����̸鼭 ������!
			else if (_playerDir == DIR_RIGHT_MOVE)
			{
				_jumpForce = JUMPFORCE;
				_playerMotion->stop();
				_playerDir = DIR_RIGHT_MOVE_JUMP;
				_playerMotion = KEYANIMANAGER->findAnimation("playerRightMoveJump");
				_playerMotion->start();
			}
			else if (_playerDir == DIR_LEFT_MOVE)
			{
				_jumpForce = JUMPFORCE;
				_playerMotion->stop();
				_playerDir = DIR_LEFT_MOVE_JUMP;
				_playerMotion = KEYANIMANAGER->findAnimation("playerLeftMoveJump");
				_playerMotion->start();
			}
			// �������� �Ҳ���!
			else if ((_playerDir == DIR_RIGHT_FALL || _playerDir == DIR_RIGHT_JUMP || _playerDir == DIR_RIGHT_MOVE_JUMP))
			{
				_jumpForce = JUMPFORCE;
				_gravity = 0;
				isDjump = true;

				_playerDir = DIR_RIGHT_MOVE_JUMP;
				_playerMotion = KEYANIMANAGER->findAnimation("playerRightDoubleJump");
				_playerMotion->start();
			}
			else if ((_playerDir == DIR_LEFT_FALL || _playerDir == DIR_LEFT_JUMP || _playerDir == DIR_LEFT_MOVE_JUMP))
			{
				_jumpForce = JUMPFORCE;
				_gravity = 0;
				isDjump = true;

				_playerDir = DIR_LEFT_MOVE_JUMP;
				_playerMotion = KEYANIMANAGER->findAnimation("playerLeftDoubleJump");
				_playerMotion->start();
			}
		}
		// �߰��� ������ ������
		else if (KEYMANAGER->isOnceKeyUp('Z'))
		{
			if (_playerDir == DIR_RIGHT_JUMP || _playerDir == DIR_RIGHT_MOVE_JUMP)
			{
				_jumpForce = 0;
				_playerMotion->stop();
				_playerDir = DIR_RIGHT_FALL;
				_playerMotion = KEYANIMANAGER->findAnimation("playerRightFall");
				_playerMotion->start();
			}
			else if (_playerDir == DIR_LEFT_JUMP || _playerDir == DIR_LEFT_MOVE_JUMP)
			{
				_jumpForce = 0;
				_playerMotion->stop();
				_playerDir = DIR_LEFT_FALL;
				_playerMotion = KEYANIMANAGER->findAnimation("playerLeftFall");
				_playerMotion->start();
			}
		}

		// ����Ű�� ��������
		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			if (_playerDir == DIR_RIGHT_STOP || _playerDir == DIR_RIGHT_MOVE)
			{
				_playerMotion->stop();
				_playerDir = DIR_RIGHT_ATK;
				_playerMotion = KEYANIMANAGER->findAnimation("playerRightStandAttack");
				_playerMotion->start();
			}
			else if (_playerDir == DIR_LEFT_STOP || _playerDir == DIR_LEFT_MOVE)
			{
				_playerMotion->stop();
				_playerDir = DIR_LEFT_ATK;
				_playerMotion = KEYANIMANAGER->findAnimation("playerLeftStandAttack");
				_playerMotion->start();
			}
			else if (_playerDir == DIR_RIGHT_SIT)
			{
				_playerDir = DIR_RIGHT_ATK;
				_playerMotion = KEYANIMANAGER->findAnimation("playerRightSitAttack");
				_playerMotion->start();
			}
			else if (_playerDir == DIR_LEFT_SIT)
			{
				_playerDir = DIR_LEFT_ATK;
				_playerMotion = KEYANIMANAGER->findAnimation("playerLeftSitAttack");
				_playerMotion->start();
			}
			else if (_playerDir == DIR_RIGHT_JUMP ||
				_playerDir == DIR_RIGHT_MOVE_JUMP ||
				_playerDir == DIR_RIGHT_FALL)
			{
				_playerDir = DIR_RIGHT_AIR_ATK;
				_playerMotion = KEYANIMANAGER->findAnimation("playerRightAirAttack");
				_playerMotion->start();
			}
			else if (_playerDir == DIR_LEFT_JUMP ||
				_playerDir == DIR_LEFT_MOVE_JUMP ||
				_playerDir == DIR_LEFT_FALL)
			{
				_playerDir = DIR_LEFT_AIR_ATK;
				_playerMotion = KEYANIMANAGER->findAnimation("playerLeftAirAttack");
				_playerMotion->start();
			}
		}

		// ��뽬 Ű�� ��������
		if (KEYMANAGER->isOnceKeyDown('D'))
		{
			if (_playerDir == DIR_RIGHT_STOP || _playerDir == DIR_RIGHT_MOVE)
			{
				_playerMotion->stop();
				_playerDir = DIR_RIGHT_BACKDASH;
				_playerMotion = KEYANIMANAGER->findAnimation("playerRightBackDash");
				_playerMotion->start();
			}
			else if (_playerDir == DIR_LEFT_STOP || _playerDir == DIR_LEFT_MOVE)
			{
				_playerMotion->stop();
				_playerDir = DIR_LEFT_BACKDASH;
				_playerMotion = KEYANIMANAGER->findAnimation("playerLeftBackDash");
				_playerMotion->start();
			}
			else if (_playerDir == DIR_RIGHT_BACKDASH)
			{
				_playerMotion = KEYANIMANAGER->findAnimation("playerRightBackDash");
				_playerMotion->start();
			}
			else if (_playerDir == DIR_LEFT_BACKDASH)
			{
				_playerMotion = KEYANIMANAGER->findAnimation("playerLeftBackDash");
				_playerMotion->start();
			}
		}

		if (KEYMANAGER->isOnceKeyDown('I'))
		{
			//ALUCARD_INFO->setX(_x);
			//ALUCARD_INFO->setY(_y);
			SCENEMANAGER->changeScene("CharScene");
		}

		// �÷��̾� ���°�
		playerDirection();
		// �÷��̾� Ŀ�ǵ�
		keyInput();
		checkCommand();

		//// �۹и��� ����
		//if (KEYMANAGER->isOnceKeyDown('1'))
		//{
		//	_fm->selectFamailiar(0);
		//}
		//if (KEYMANAGER->isOnceKeyDown('2'))
		//{
		//	_fm->selectFamailiar(1);
		//}
		//if (KEYMANAGER->isOnceKeyDown('3'))
		//{
		//	_fm->selectFamailiar(2);
		//}
		//if (KEYMANAGER->isOnceKeyDown('4'))
		//{
		//	_fm->selectFamailiar(3);
		//}

		//if(_fm) _fm->update();
	}
}

void player::render(HDC hdc) 
{
//	Rectangle(getMemDC(), _rc_Hit.left, _rc_Hit.top, _rc_Hit.right, _rc_Hit.bottom);
	if (!_isOp)
	{
		_fm->render(hdc);
	}

#ifdef _DEBUG
//	char str[500];
//	sprintf(str, "%.2f %.2f / %d %d", _x, _y, _image[0]->getFrameWidth(), _image[0]->getFrameHeight());
//	TextOut(getMemDC(), _x - 75, _y - 100, str, strlen(str));
#endif

	showInput();

	switch (_playerDir)
	{
		case DIR_RIGHT_STOP: case DIR_LEFT_STOP: case DIR_RIGHT_MOVE: case DIR_LEFT_MOVE:
		case DIR_RIGHT_SIT: case DIR_LEFT_SIT: case DIR_RIGHT_BACKDASH: case DIR_LEFT_BACKDASH:
		case DIR_RIGHT_JUMP: case DIR_LEFT_JUMP: case DIR_RIGHT_MOVE_JUMP: case DIR_LEFT_MOVE_JUMP:
		case DIR_RIGHT_SUPER_JUMP: case DIR_LEFT_SUPER_JUMP: case DIR_RIGHT_FALL: case DIR_LEFT_FALL:
			_image[0]->aniRender(hdc, _x - _image[0]->getFrameWidth() / 2, _y - _image[0]->getFrameHeight(), _playerMotion);
		break;

		case DIR_RIGHT_ATK: case DIR_LEFT_ATK: case DIR_RIGHT_AIR_ATK: case DIR_LEFT_AIR_ATK:
		case DIR_RIGHT_HIT: case DIR_LEFT_HIT: case DIR_RIGHT_SKILL: case DIR_LEFT_SKILL:
			_image[1]->aniRender(hdc, _x - _image[0]->getFrameWidth() / 2, _y - _image[0]->getFrameHeight(), _playerMotion);
		break;
	}
	

	// �÷��̾� ��ġ �����ؾߵ�.
//	if (KEYANIMANAGER->findAnimation("playerRightMove"))
}

void player::showInput()
{
	if (_vCommand.size() != NULL)
	{
		for (int i = 0; i < _vCommand.size(); ++i)
		{
			if (_vCommand[i] == INPUT_LEFT)
			{
				TextOut(getMemDC(), 50, 100 + i * 25, TEXT("LEFT"), strlen("LEFT"));
			}
			else if (_vCommand[i] == INPUT_LEFT_DOWN)
			{
				TextOut(getMemDC(), 50, 100 + i * 25, TEXT("LEFT_DOWN"), strlen("LEFT_DOWN"));
			}
			else if (_vCommand[i] == INPUT_DOWN)
			{
				TextOut(getMemDC(), 50, 100 + i * 25, TEXT("DOWN"), strlen("DOWN"));
			}
			else if (_vCommand[i] == INPUT_RIGHT_DOWN)
			{
				TextOut(getMemDC(), 50, 100 + i * 25, TEXT("RIGHT_DOWN"), strlen("RIGHT_DOWN"));
			}
			else if (_vCommand[i] == INPUT_RIGHT)
			{
				TextOut(getMemDC(), 50, 100 + i * 25, TEXT("RIGHT"), strlen("RIGHT"));
			}
			else if (_vCommand[i] == INPUT_UP)
			{
				TextOut(getMemDC(), 50, 100 + i * 25, TEXT("UP"), strlen("UP"));
			}
			else if (_vCommand[i] == INPUT_Z)
			{
				TextOut(getMemDC(), 50, 100 + i * 25, TEXT("Z"), strlen("Z"));
			}
			else if (_vCommand[i] == INPUT_X)
			{
				TextOut(getMemDC(), 50, 100 + i * 25, TEXT("X"), strlen("X"));
			}
			else if (_vCommand[i] == INPUT_S)
			{
				TextOut(getMemDC(), 50, 100 + i * 25, TEXT("S"), strlen("S"));
			}
			else if (_vCommand[i] == INPUT_D)
			{
				TextOut(getMemDC(), 50, 100 + i * 25, TEXT("D"), strlen("D"));
			}
		}
	}
}

void player::playerDirection()
{
	switch (_playerDir)
	{
		case DIR_RIGHT_BACKDASH:
			_x -= MOVESPEED * 1.5f;

		case DIR_RIGHT_MOVE:

		case DIR_RIGHT_STOP:
			if (_collision.VerticalCollision(_rc_Hit, _x, _y, _imageName) != BOTTOM)
			{
				_playerMotion->stop();
				_playerDir = DIR_RIGHT_FALL;
				_playerMotion = KEYANIMANAGER->findAnimation("playerRightFall");
				_playerMotion->start();
			}
			else
			{
				// y ��ǥ �ٴڿ� ����
				_y = _collision.setPlayerVertical(_rc_Hit, _x, _y, _imageName);
			}
		break;

		case DIR_LEFT_BACKDASH:
			_x += MOVESPEED * 1.5f;

		case DIR_LEFT_STOP:

		case DIR_LEFT_MOVE:
			if (_collision.VerticalCollision(_rc_Hit, _x, _y, _imageName) != BOTTOM)
			{
				_playerMotion->stop();
				_playerDir = DIR_LEFT_FALL;
				_playerMotion = KEYANIMANAGER->findAnimation("playerLeftFall");
				_playerMotion->start();
			}
			else
			{
				// y ��ǥ �ٴڿ� ����
				_y = _collision.setPlayerVertical(_rc_Hit, _x, _y, _imageName);
			}
		break;

		case DIR_RIGHT_MOVE_JUMP:

		case DIR_RIGHT_JUMP:
			if (_collision.VerticalCollision(_rc_Hit, _x, _y, _imageName) != TOP)
			{
				
			}
			else
			{
				_jumpForce = 0;
			}

			_gravity += GRAVITYPOWER * TIMEMANAGER->getElapsedTime();
			_jumpForce -= _gravity;
			_y -= _jumpForce;
		break;

		case DIR_RIGHT_AIR_ATK:

		case DIR_RIGHT_FALL:
		{
			if (_collision.VerticalCollision(_rc_Hit, _x, _y, _imageName) == TOP && _jumpForce > 0)
			{
				_jumpForce = 0;
			}

			_gravity += GRAVITYPOWER * TIMEMANAGER->getElapsedTime();
			_jumpForce -= _gravity;
			_y -= _jumpForce;

			// ���⿡ �ȼ��浹 �ߴ��� ���ߴ��� ������ ��
			if (_collision.VerticalCollision(_rc_Hit, _x, _y, _imageName) == BOTTOM)
			{
				_gravity = 0;
				_jumpForce = 0;
				isDjump = false;

				_playerMotion->stop();
				_playerDir = DIR_RIGHT_STOP;
				_playerMotion = KEYANIMANAGER->findAnimation("playerRightLanding");
				_playerMotion->start();
			}
		}
		break;

		case DIR_LEFT_MOVE_JUMP:

		case DIR_LEFT_JUMP:
			if (_collision.VerticalCollision(_rc_Hit, _x, _y, _imageName) != TOP)
			{
				
			}
			else
			{
				_jumpForce = 0;
			}

			_gravity += GRAVITYPOWER * TIMEMANAGER->getElapsedTime();
			_jumpForce -= _gravity;
			_y -= _jumpForce;
		break;

		case DIR_LEFT_AIR_ATK:

		case DIR_LEFT_FALL:
		{
			if (_collision.VerticalCollision(_rc_Hit, _x, _y, _imageName) == TOP && _jumpForce > 0)
			{
				_jumpForce = 0;
			}

			_gravity += GRAVITYPOWER * TIMEMANAGER->getElapsedTime();
			_jumpForce -= _gravity;
			_y -= _jumpForce;

			// ���⿡ �ȼ��浹 �ߴ��� ���ߴ��� ������ ��
			if (_collision.VerticalCollision(_rc_Hit, _x, _y, _imageName) == BOTTOM)
			{
				_gravity = 0;
				_jumpForce = 0;
				isDjump = false;

				_playerMotion->stop();
				_playerDir = DIR_LEFT_STOP;
				_playerMotion = KEYANIMANAGER->findAnimation("playerLeftLanding");
				_playerMotion->start();
			}
		}
		break;

		// **** �������� **** //
		case DIR_RIGHT_SUPER_JUMP:
			if (_collision.VerticalCollision(_rc_Hit, _x, _y, _imageName) != TOP)
			{
				_gravity += GRAVITYPOWER * TIMEMANAGER->getElapsedTime();
				_jumpForce -= _gravity;
				_y -= _jumpForce;
			}
			else if (_collision.VerticalCollision(_rc_Hit, _x, _y, _imageName) == TOP && _jumpForce > 0)
			{
				_gravity = 0;
				_jumpForce = 0;
				_playerMotion->stop();
				_playerMotion = KEYANIMANAGER->findAnimation("playerRightCrash");
				_playerMotion->start();
			}
		break;

		case DIR_LEFT_SUPER_JUMP:
			if (_collision.VerticalCollision(_rc_Hit, _x, _y, _imageName) != TOP)
			{
				_gravity += GRAVITYPOWER * TIMEMANAGER->getElapsedTime();
				_jumpForce -= _gravity;
				_y -= _jumpForce;
			}
			else if (_collision.VerticalCollision(_rc_Hit, _x, _y, _imageName) == TOP && _jumpForce > 0)
			{
				_gravity = 0;
				_jumpForce = 0;
				_playerMotion->stop();
				_playerMotion = KEYANIMANAGER->findAnimation("playerLeftCrash");
				_playerMotion->start();
			}
		break;
	}
}

void player::rightMoving(void* obj)
{
	player* p = (player*)obj;

	p->setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightMove"));
	p->getPlayerMotion()->start();
}

void player::leftMoving(void* obj)
{
	player* p = (player*)obj;

	p->setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftMove"));
	p->getPlayerMotion()->start();
}

void player::rightStopping(void* obj)
{
	player* p = (player*)obj;

	p->_playerDir = DIR_RIGHT_STOP;

	if (p->_collision.VerticalCollision(p->_rc_Hit, (p->_x - 5), (p->_y - 15), p->_imageName) == BOTTOM ||
		p->_collision.VerticalCollision(p->_rc_Hit, (p->_x + 5), (p->_y - 15), p->_imageName) == BOTTOM)
	{
		p->setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightStairsStop"));
		p->getPlayerMotion()->start();
	}
	else
	{
		p->setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightStop"));
		p->getPlayerMotion()->start();
	}
}

void player::leftStopping(void* obj)
{
	player* p = (player*)obj;

	p->_playerDir = DIR_LEFT_STOP;

	if (p->_collision.VerticalCollision(p->_rc_Hit, (p->_x - 5), (p->_y - 15), p->_imageName) == BOTTOM ||
		p->_collision.VerticalCollision(p->_rc_Hit, (p->_x + 5), (p->_y - 15), p->_imageName) == BOTTOM)
	{
		p->setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftStairsStop"));
		p->getPlayerMotion()->start();
	}
	else
	{
		p->setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftStop"));
		p->getPlayerMotion()->start();
	}
}

void player::rightSitting(void* obj)
{
	player* p = (player*)obj;

	p->_playerDir = DIR_RIGHT_SIT;
	p->setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightSitDown"));
}

void player::leftSitting(void* obj)
{
	player* p = (player*)obj;

	p->_playerDir = DIR_LEFT_SIT;
	p->setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftSitDown"));
}

void player::rightFalling(void* obj)
{
	player* p = (player*)obj;

	p->_playerDir = DIR_RIGHT_FALL;
	p->setPlayerMotion(KEYANIMANAGER->findAnimation("playerRightFall"));
	p->getPlayerMotion()->start();
}

void player::leftFalling(void* obj)
{
	player* p = (player*)obj;

	p->_playerDir = DIR_LEFT_FALL;
	p->setPlayerMotion(KEYANIMANAGER->findAnimation("playerLeftFall"));
	p->getPlayerMotion()->start();
}

void player::keyInput()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) &&
		!KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_currentInput = INPUT_LEFT;
		if (_prevInput != _currentInput)
		{
			_prevInput = _currentInput;
			_vCommand.push_back(INPUT_LEFT);
			keyTimer = 0;
		}
	}
	else if (KEYMANAGER->isStayKeyDown(VK_LEFT) &&
		KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_currentInput = INPUT_LEFT_DOWN;
		if (_prevInput != _currentInput)
		{
			_prevInput = _currentInput;
			_vCommand.push_back(INPUT_LEFT_DOWN);
			keyTimer = 0;
		}
	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT) &&
		KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_currentInput = INPUT_RIGHT_DOWN;
		if (_prevInput != _currentInput)
		{
			_prevInput = _currentInput;
			_vCommand.push_back(INPUT_RIGHT_DOWN);
			keyTimer = 0;
		}
	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT) &&
		!KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_currentInput = INPUT_RIGHT;
		if (_prevInput != _currentInput)
		{
			_prevInput = _currentInput;
			_vCommand.push_back(INPUT_RIGHT);
			keyTimer = 0;
		}
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN) &&
		!KEYMANAGER->isStayKeyDown(VK_LEFT) &&
		!KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_currentInput = INPUT_DOWN;
		if (_prevInput != _currentInput)
		{
			_prevInput = _currentInput;
			_vCommand.push_back(INPUT_DOWN);
			keyTimer = 0;
		}
	}
	else if (KEYMANAGER->isStayKeyDown(VK_UP) &&
		KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_currentInput = INPUT_UP;
		if (_prevInput != _currentInput)
		{
			_prevInput = _currentInput;
			_vCommand.push_back(INPUT_UP);
			keyTimer = 0;
		}
	}
	else if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_currentInput = INPUT_UP;
		if (_prevInput != _currentInput)
		{
			_prevInput = _currentInput;
			_vCommand.push_back(INPUT_UP);
			keyTimer = 0;
		}
	}
	else if (KEYMANAGER->isStayKeyDown('Z'))
	{
		_currentInput = INPUT_Z;
		if (_prevInput != _currentInput)
		{
			_prevInput = _currentInput;
			_vCommand.push_back(INPUT_Z);
			keyTimer = 0;
		}
	}
	else if (KEYMANAGER->isStayKeyDown('X'))
	{
		_currentInput = INPUT_X;
		if (_prevInput != _currentInput)
		{
			_prevInput = _currentInput;
			_vCommand.push_back(INPUT_X);
			keyTimer = 0;
		}
	}
	else if (KEYMANAGER->isStayKeyDown('S'))
	{
		_currentInput = INPUT_S;
		if (_prevInput != _currentInput)
		{
			_prevInput = _currentInput;
			_vCommand.push_back(INPUT_S);
			keyTimer = 0;
		}
	}
	else if (KEYMANAGER->isStayKeyDown('D'))
	{
		_currentInput = INPUT_D;
		if (_prevInput != _currentInput)
		{
			_prevInput = _currentInput;
			_vCommand.push_back(INPUT_D);
			keyTimer = 0;
		}
	}
	else
	{
		_currentInput = INPUT_NOT;
		_prevInput = INPUT_NOT;
	}

	keyTimer += TIMEMANAGER->getElapsedTime();

	if (_vCommand.size() != NULL)
	{
		if (keyTimer >= 0.2f)
		{
			keyTimer = 0;
			_vCommand.clear();
		}
	}
}

void player::checkCommand()
{
	for (int i = 0; i < _vCommand.size(); ++i)
	{
		// Ŀ�ǵ� 4��
		if (_vCommand.size() > 2 && i < (int)_vCommand.size() - 2)
		{
			if (_vCommand[i] == INPUT_DOWN &&
				_vCommand[i + 1] == INPUT_UP &&
				_vCommand[i + 2] == INPUT_Z)
			{
				if (_playerDir == DIR_RIGHT_STOP || 
					_playerDir == DIR_RIGHT_FALL || 
					_playerDir == DIR_RIGHT_JUMP || 
					_playerDir == DIR_RIGHT_MOVE_JUMP)
				{
					_jumpForce = JUMPFORCE * 3;
					_playerMotion->stop();
					_playerDir = DIR_RIGHT_SUPER_JUMP;
					_playerMotion = KEYANIMANAGER->findAnimation("playerRightSuperJump");
					_playerMotion->start();
				}
				else if (_playerDir == DIR_LEFT_STOP ||
					_playerDir == DIR_LEFT_FALL ||
					_playerDir == DIR_LEFT_JUMP ||
					_playerDir == DIR_LEFT_MOVE_JUMP)
				{
					_jumpForce = JUMPFORCE * 3;
					_playerMotion->stop();
					_playerDir = DIR_LEFT_SUPER_JUMP;
					_playerMotion = KEYANIMANAGER->findAnimation("playerLeftSuperJump");
					_playerMotion->start();
				}

				_vCommand.clear();
				keyTimer = 0;
				break;
			}
		}
	}
}

void player::setFamiliarDirection(void)
{
	switch (_playerDir)
	{
	case DIR_RIGHT_STOP: case DIR_RIGHT_MOVE: case DIR_RIGHT_SIT: case DIR_RIGHT_BACKDASH:
	case DIR_RIGHT_JUMP: case DIR_RIGHT_MOVE_JUMP: case DIR_RIGHT_SUPER_JUMP: case DIR_RIGHT_FALL:
	case DIR_RIGHT_ATK: case DIR_RIGHT_AIR_ATK: case DIR_RIGHT_HIT: case DIR_RIGHT_SKILL:
		_fm->setPlayerDirect(0);
		_fX = _x - _image[0]->getFrameWidth() / 4;
		break;
	case DIR_LEFT_STOP: case DIR_LEFT_MOVE: case DIR_LEFT_SIT: case DIR_LEFT_BACKDASH:
	case DIR_LEFT_JUMP: case DIR_LEFT_MOVE_JUMP: case DIR_LEFT_SUPER_JUMP: case DIR_LEFT_FALL:
	case DIR_LEFT_ATK: case DIR_LEFT_AIR_ATK: case DIR_LEFT_HIT: case DIR_LEFT_SKILL:
		_fX = _x + _image[0]->getFrameWidth() / 4;
		_fm->setPlayerDirect(1);
		break;
	}

	_fY = _y - 120;
}

void player::opening()
{
//	_x += MOVESPEED;

	// ������ �뽬�ߴٰ�

	//if (TIMEMANAGER->getWorldTime() < 8.5f)
	if (TIMEMANAGER->getElapsedTime() * 60 < 8.5f)
	{
		if (_playerMotion == KEYANIMANAGER->findAnimation("playerRightMoveStart"))
		{
			_x += MOVESPEED * 4;
		}
		else
		{
			if (_x > WINSIZEX / 2) _x -= MOVESPEED;
		}
	}

	//if (TIMEMANAGER->getWorldTime() >= 8.7f && TIMEMANAGER->getWorldTime() < 8.8f)
	if (TIMEMANAGER->getElapsedTime() * 60 >= 8.7f && TIMEMANAGER->getElapsedTime() * 60  < 8.8f)
	{
		if (_playerMotion == KEYANIMANAGER->findAnimation("playerRightMove"))
		{
			_jumpForce = 6.5f;
			_playerMotion = KEYANIMANAGER->findAnimation("playerRightMoveJump");
			_playerMotion->start();
			_y -= _jumpForce;
		}
	}

	//if (TIMEMANAGER->getWorldTime() >= 8.7f && TIMEMANAGER->getWorldTime() < 9.15f)
	if (TIMEMANAGER->getElapsedTime() * 60 >= 8.7f && TIMEMANAGER->getElapsedTime() * 60 < 9.15f)
	{
		if (_y <= WINSIZEY - 210)
		{
			_gravity += 0.5f * TIMEMANAGER->getElapsedTime();
			_jumpForce -= _gravity;
			_y -= _jumpForce;
		}
	}

	//if (TIMEMANAGER->getWorldTime() >= 9.15f)
	if (TIMEMANAGER->getElapsedTime() * 60 >= 9.15f)
	{
//		if (_playerMotion == KEYANIMANAGER->findAnimation("playerRightFall"))
//		{
//			_playerMotion = KEYANIMANAGER->findAnimation("playerRightMove");
//			_playerMotion->start();
//		}

		if (_y <= WINSIZEY - 210)
		{
			_y += 2.0f;
		}
	}

	//if (TIMEMANAGER->getWorldTime() >= 9.4f)
	if (TIMEMANAGER->getElapsedTime() * 60 >= 9.4f)
	{
		_x += MOVESPEED * 5;
	}

	

	// �ٴ¸�� �����鼭 ���� �ڷΰ��� ���ڸ����� �ٴ¸��

	// �ð� ������� ������ ������� �����鼭 y��ǥ ���ִ� ���ݾ� �����ְ� ����
	
}