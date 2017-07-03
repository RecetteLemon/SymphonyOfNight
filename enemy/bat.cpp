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
	Rectangle(getMemDC(), _comeRange.left, _comeRange.top, _comeRange.right, _comeRange.bottom);
	// �׷��ִ°�
	_enemyInfo.enemyImage->aniRender(getMemDC(), _enemyInfo.x, _enemyInfo.y,
		_enemyInfo.enemyAni);
}

// �̹��� �ʱ�ȭ
void bat::imageInit()
{
	// �ִϸ��̼� �ʱ�ȭ�� ���� �����Ӱ� ������ ������, ���� ������ �ִ°Ŷ� ������ ������ �ִ°�
	int arrLeftMove[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	KEYANIMANAGER->addArrayFrameAnimation("leftBatMove", "bat", arrLeftMove, 10, 5, true);

	int arrRightMove[] = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
	KEYANIMANAGER->addArrayFrameAnimation("rightBatMove", "bat", arrRightMove, 10, 5, true);

	int arrLeftStay[] = { 20, 21 };
	KEYANIMANAGER->addArrayFrameAnimation("leftBatStay", "bat", arrLeftStay, 2, 3, true);

	int arrRightStay[] = { 22, 23 };
	KEYANIMANAGER->addArrayFrameAnimation("rightBatStay", "bat", arrRightStay, 2, 3, true);

	_enemyInfo.enemyAni = KEYANIMANAGER->findAnimation("leftBatStay");
	_enemyInfo.enemyAni->start();

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
			if (_playerX <= _enemyInfo.x)
			{
				_moveLeft = true;
				_enemyInfo.stat = ENEMY_LEFT_MOVE;
			}

			// ������
			if (_playerX > _enemyInfo.x)
			{
				_moveLeft = false;
				_enemyInfo.stat = ENEMY_RIGHT_MOVE;
			}

			// ���� �÷��̾� ��ġ�� ������
			if (_enemyInfo.y >= _playerY)
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
		case ENEMY_LEFT_MOVE:
			_enemyInfo.enemyAni = KEYANIMANAGER->findAnimation("leftBatMove");
			_enemyInfo.x -= _enemyInfo.speed;

			if (!_enemyInfo.enemyAni->isPlay())
			{
				_enemyInfo.enemyAni->start();
			}
			break;

		case ENEMY_RIGHT_MOVE:
			_enemyInfo.enemyAni = KEYANIMANAGER->findAnimation("rightBatMove");
			_enemyInfo.x += _enemyInfo.speed;

			if (!_enemyInfo.enemyAni->isPlay())
			{
				_enemyInfo.enemyAni->start();
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

// �׽�Ʈ ��
void bat::getPlayerXY(float x, float y)
{
	_playerX = x;
	_playerY = y;
}
