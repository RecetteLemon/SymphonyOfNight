#include "stdafx.h"
#include "bat.h"


bat::bat()
{
}


bat::~bat()
{
}

HRESULT bat::init(const char* imageName, float x, float y)
{
	_enemyInfo.enemyImage = IMAGEMANAGER->findImage(imageName);

	enemy::init(imageName, x, y, 1);

	imageInit();

	_enemyInfo.x = x;
	_enemyInfo.y = y;
	_enemyInfo.atk = 3;
	_enemyInfo.hp = 10;
	_enemyInfo.speed = 1.0f;

	_comePlayerY = _move = _moveLeft = _upDown = false;

	// ������ Y�� �ʱ�ȭ
	_saveY = 0;

	// ������ ���� ����
	_waveRange = WINSIZEY / 5;




	return S_OK;
}

void bat::release()
{
	_enemyInfo.enemyImage->release();
}

void bat::update()
{
	// �浹 ����
	RECT temp;
	if (IntersectRect(&temp, &_enemyInfo.playerRc, &_comeRange))
	{
		_move = true;
	}



	// ������(����) 
	move();
	// �������� �������� ���������� ����� ����.
	if (!_move)
	{
		_comeRange = RectMakeCenter(_enemyInfo.x + _enemyInfo.enemyImage->getFrameWidth() / 2, 
			_enemyInfo.y + _enemyInfo.enemyImage->getFrameHeight() / 2,
			100, 100);
	}
	// ���� �����̸� ������ 0���� �ʱ�ȭ
	else
	{
		_comeRange = RectMake(0, 0, 0, 0);
	}

	// �� ������ ��Ʈ��
	_enemyInfo.rc = RectMake(_enemyInfo.x, _enemyInfo.y,
		_enemyInfo.enemyImage->getFrameWidth(),
		_enemyInfo.enemyImage->getFrameHeight());
}

void bat::render()
{
	// �׷��ִ°�
	// ���°��� ���� �ൿ
	switch (_enemyInfo.stat)
	{
	case ENEMY_LEFT_STAY:
		_enemyInfo.enemyImage->aniRender(getMemDC(), _enemyInfo.x, _enemyInfo.y,
			_enemyInfo.enemyAni[ENEMY_LEFT_STAYANI]);

		break;

	case ENEMY_RIGHT_STAY:
		_enemyInfo.enemyImage->aniRender(getMemDC(), _enemyInfo.x, _enemyInfo.y,
			_enemyInfo.enemyAni[ENEMY_RIGHT_STAYANI]);
		break;
	case ENEMY_LEFT_MOVE:
		_enemyInfo.enemyImage->aniRender(getMemDC(), _enemyInfo.x, _enemyInfo.y,
			_enemyInfo.enemyAni[ENEMY_LEFT_MOVEANI]);

		break;

	case ENEMY_RIGHT_MOVE:
		_enemyInfo.enemyImage->aniRender(getMemDC(), _enemyInfo.x, _enemyInfo.y,
			_enemyInfo.enemyAni[ENEMY_RIGHT_MOVEANI]);
		break;

		// �׾����� �̹����� �����
	case ENEMY_LEFT_DIE:
		release();
		break;

	case ENEMY_RIGHT_DIE:
		release();
		break;
	}
}

// �̹��� �ʱ�ȭ
void bat::imageInit()
{
	for (int i = 0; i < ENEMY_ANI_AND; i++)
	{
		_enemyInfo.enemyAni[i] = new animation;
		_enemyInfo.enemyAni[i]->init(_enemyInfo.enemyImage->getWidth(), _enemyInfo.enemyImage->getHeight()
			, _enemyInfo.enemyImage->getFrameWidth(), _enemyInfo.enemyImage->getFrameHeight());
	}
	// �ִϸ��̼� �ʱ�ȭ�� ���� �����Ӱ� ������ ������, ���� ������ �ִ°Ŷ� ������ ������ �ִ°�
	int arrLeftMove[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	_enemyInfo.enemyAni[ENEMY_LEFT_MOVEANI]->setPlayFrame(arrLeftMove, 10, true);
	_enemyInfo.enemyAni[ENEMY_LEFT_MOVEANI]->setFPS(30);

	int arrRightMove[] = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
	_enemyInfo.enemyAni[ENEMY_RIGHT_MOVEANI]->setPlayFrame(arrRightMove, 10, true);
	_enemyInfo.enemyAni[ENEMY_RIGHT_MOVEANI]->setFPS(30);

	int arrLeftStay[] = { 20, 21 };
	_enemyInfo.enemyAni[ENEMY_LEFT_STAYANI]->setPlayFrame(arrLeftStay, 2, true);
	_enemyInfo.enemyAni[ENEMY_LEFT_STAYANI]->setFPS(5);

	int arrRightStay[] = { 22, 23 };
	_enemyInfo.enemyAni[ENEMY_RIGHT_STAYANI]->setPlayFrame(arrRightStay, 2, true);
	_enemyInfo.enemyAni[ENEMY_RIGHT_STAYANI]->setFPS(5);

	_enemyInfo.stat = ENEMY_LEFT_STAY;
	_enemyInfo.enemyAni[ENEMY_LEFT_STAYANI]->start();

}

// ������(����)
void bat::move()
{
	// �÷��̾ ������ ���� ��Ʈ�� �پ����� �׶� �����δ�.
	if (_move)
	{
		// �÷��̾��� Y��ǥ�� �ٰ����� ���ߴٸ� 
		if (!_comePlayerY)
		{
			// ������ y��ǥ�� �����ش�.
			_enemyInfo.y += _enemyInfo.speed;
			// �÷��̾ �� ���� ���ʿ� ���� ���
			if (_enemyInfo.playerRc.left <= _enemyInfo.x)
			{
				_moveLeft = true;
				_enemyInfo.stat = ENEMY_LEFT_MOVE;
			}

			// ������
			if (_enemyInfo.playerRc.right > _enemyInfo.x)
			{
				_moveLeft = false;
				_enemyInfo.stat = ENEMY_RIGHT_MOVE;
			}

			// ���� �÷��̾� ��ġ�� ������
			if (_enemyInfo.y >= _enemyInfo.playerRc.top)
			{
				// ������ Y��ǥ
				_saveY = _enemyInfo.y;
				_comePlayerY = true;

			}
		}
		// �÷��̾��� y��ǥ ����
		if (_comePlayerY)
		{
			// ����� �÷��̾� ��ġ�� �޾Ƽ� ���� ���������� �̵��Ѵ�
			// ���⼭ ���� �������� �����Ǹ� �ִϸ��̼� ���°��� ����

			// ����� ������
			if (_upDown)
			{
				_enemyInfo.y += 1.5f;
			}
			else
			{
				_enemyInfo.y -= 1.5f;
			}

			// ���࿡ ���� ���� y��ǥ���� ���̺������ŭ ���Ѱ� ���� y��ǥ���� �۾����� �ٽ� ���� �ö󰣴�
			if (_enemyInfo.y + _waveRange / 2 < _saveY)
			{
				_upDown = true;
			}

			// ���࿡ ���� ���� y��ǥ���� ���̺������ ���� ���� y��ǥ���� Ŀ���� �ٽ� �Ʒ��� ��������
			if (_enemyInfo.y - _waveRange / 2 > _saveY)
			{
				_upDown = false;
			}
		}
	}

	// ���°��� ���� �ൿ
	switch (_enemyInfo.stat)
	{
		case ENEMY_LEFT_STAY:
			_enemyInfo.enemyAni[ENEMY_LEFT_STAYANI]->frameUpdate(TIMEMANAGER->getElapsedTime());

			break;

		case ENEMY_RIGHT_STAY:
			_enemyInfo.enemyAni[ENEMY_RIGHT_STAYANI]->frameUpdate(TIMEMANAGER->getElapsedTime());

			break;

		case ENEMY_LEFT_MOVE:
			_enemyInfo.x -= _enemyInfo.speed;
			_enemyInfo.enemyAni[ENEMY_LEFT_MOVEANI]->frameUpdate(TIMEMANAGER->getElapsedTime());

			if (!_enemyInfo.enemyAni[ENEMY_LEFT_MOVEANI]->isPlay())
			{
				_enemyInfo.enemyAni[ENEMY_LEFT_MOVEANI]->start();
			}
			break;

		case ENEMY_RIGHT_MOVE:
			_enemyInfo.x += _enemyInfo.speed;
			_enemyInfo.enemyAni[ENEMY_RIGHT_MOVEANI]->frameUpdate(TIMEMANAGER->getElapsedTime());

			if (!_enemyInfo.enemyAni[ENEMY_RIGHT_MOVEANI]->isPlay())
			{
				_enemyInfo.enemyAni[ENEMY_RIGHT_MOVEANI]->start();
			}
			break;

		// �׾����� �̹����� �����
		case ENEMY_LEFT_DIE:

			release();
			break;

		case ENEMY_RIGHT_DIE:
			release();
			break;
	}	
}