#include "stdafx.h"
#include "bloodSkeleton.h"


bloodSkeleton::bloodSkeleton()
{
}


bloodSkeleton::~bloodSkeleton()
{
}

// ���� ��ϵ�
// ���� ������ �ִϸ��̼��� ��� �����
// ���� �װ� ��Ƴ��� ��� ��Ƴ�
// ��Ƴ��� 3��° ��Ƴ������� �̹��� ������ �ӵ� ����



HRESULT bloodSkeleton::init(const char* imageName, RECT leftRect, RECT rightRect, float x, float y)
{
	enemy::init(imageName, x, y, 1);

	// ������ ����, ����ġ, ü���� �ʱ�ȭ
	_enemyInfo.atk = 4;
	_enemyInfo.hp = 1;
	_enemyInfo.die = false;
	_isLeft = false;

	_enemyInfo.speed = 0.5f;
	_maxReviveTime = 5;
	_reviveTime = 0;

	_comeRange = RectMakeCenter(_enemyInfo.x, _enemyInfo.y,
		_enemyInfo.enemyImage->getFrameWidth() * 2, _enemyInfo.enemyImage->getFrameHeight());

	_leftRect = leftRect;
	_rightRect = rightRect;

	imageInit();


	return S_OK;
}

void bloodSkeleton::release()
{
	_enemyInfo.enemyImage->release();
}

void bloodSkeleton::update()
{
	enemy::update();
	move();



	// ���࿡ �׾�����
	if (_enemyInfo.die && _enemyInfo.stat != ENEMY_LEFT_REVIVE && _enemyInfo.stat != ENEMY_RIGHT_REVIVE)
	{
		// ������ �ð��� �þ
		_reviveTime += TIMEMANAGER->getElapsedTime();
		if (_enemyInfo.stat == ENEMY_LEFT_MOVE)
		{
			_enemyInfo.stat = ENEMY_LEFT_DIE;
			_enemyInfo.enemyAni[ENEMY_LEFT_DIEANI]->start();
		}
		if (_enemyInfo.stat == ENEMY_RIGHT_MOVE)
		{
			_enemyInfo.stat = ENEMY_RIGHT_DIE;
			_enemyInfo.enemyAni[ENEMY_RIGHT_DIEANI]->start();

		}
		
	}

	// �ִ� �ð��� ������ �ٽ� ��Ƴ�
	if (_reviveTime > _maxReviveTime)
	{
		// �����϶���
		if (_direction == ENEMY_LEFT && _enemyInfo.stat == ENEMY_LEFT_DIE)
		{
			_enemyInfo.stat = ENEMY_LEFT_REVIVE;
			_enemyInfo.enemyAni[ENEMY_LEFT_REVIVEANI]->start();
		}
		// �������϶�
		if (_direction == ENEMY_RIGHT && _enemyInfo.stat == ENEMY_RIGHT_DIE)
		{
			_enemyInfo.stat = ENEMY_RIGHT_REVIVE;
			_enemyInfo.enemyAni[ENEMY_RIGHT_REVIVEANI]->start();
		}
		// ���� ������ �ٽ� �ʱ�ȭ, �ִ� ����
		_reviveTime = 0;
		_enemyInfo.hp = 1;
	}

	_enemyInfo.rc = RectMake(_enemyInfo.x, _enemyInfo.y,
		_enemyInfo.enemyImage->getFrameWidth(), _enemyInfo.enemyImage->getFrameHeight());

	_comeRange = RectMakeCenter(_enemyInfo.x + _enemyInfo.enemyImage->getFrameWidth() / 2,
		_enemyInfo.y + _enemyInfo.enemyImage->getFrameHeight() / 2,
		100, _enemyInfo.enemyImage->getFrameHeight());

	KEYANIMANAGER->update();

}

void bloodSkeleton::render()
{
	enemy::render();
	Rectangle(getMemDC(), _comeRange.left, _comeRange.top, _comeRange.right, _comeRange.bottom);
	// ���°��� ���� �ִϸ��̼�, �ൿ ����
	switch (_enemyInfo.stat)
	{
	case ENEMY_LEFT_MOVE:
		_enemyInfo.enemyImage->aniRender(getMemDC(), _enemyInfo.x, _enemyInfo.y, _enemyInfo.enemyAni[ENEMY_LEFT_MOVEANI]);

		break;

	case ENEMY_RIGHT_MOVE:
		_enemyInfo.enemyImage->aniRender(getMemDC(), _enemyInfo.x, _enemyInfo.y, _enemyInfo.enemyAni[ENEMY_RIGHT_MOVEANI]);

		break;

	case ENEMY_LEFT_REVIVE:
		_enemyInfo.enemyImage->aniRender(getMemDC(), _enemyInfo.x, _enemyInfo.y, _enemyInfo.enemyAni[ENEMY_LEFT_REVIVEANI]);

		break;

	case ENEMY_RIGHT_REVIVE:
		_enemyInfo.enemyImage->aniRender(getMemDC(), _enemyInfo.x, _enemyInfo.y, _enemyInfo.enemyAni[ENEMY_RIGHT_REVIVEANI]);

		break;

	case ENEMY_LEFT_DIE:
		_enemyInfo.enemyImage->aniRender(getMemDC(), _enemyInfo.x, _enemyInfo.y, _enemyInfo.enemyAni[ENEMY_LEFT_DIEANI]);

		break;

	case ENEMY_RIGHT_DIE:
		_enemyInfo.enemyImage->aniRender(getMemDC(), _enemyInfo.x, _enemyInfo.y, _enemyInfo.enemyAni[ENEMY_RIGHT_DIEANI]);

		break;
	
	}
	
}

// �̹��� �ʱ�ȭ
void bloodSkeleton::imageInit()
{
	for (int i = 0; i < ENEMY_ANI_AND; i++)
	{
		_enemyInfo.enemyAni[i] = new animation;
		_enemyInfo.enemyAni[i]->init(_enemyInfo.enemyImage->getWidth(), _enemyInfo.enemyImage->getHeight()
			, _enemyInfo.enemyImage->getFrameWidth(), _enemyInfo.enemyImage->getFrameHeight());
	}



	// ���� �����ӵ�
	int arrLeftMove[] = { 0, 1, 2, 3, 4, 3, 2, 1 };
	_enemyInfo.enemyAni[ENEMY_LEFT_MOVEANI]->setPlayFrame(arrLeftMove, 8, true);
	_enemyInfo.enemyAni[ENEMY_LEFT_MOVEANI]->setFPS(5);

	int arrLeftRevive[] = { 13, 12, 11, 10, 9, 8, 7 };
	_enemyInfo.enemyAni[ENEMY_LEFT_REVIVEANI]->setPlayFrame(arrLeftRevive, 7, false, leftRevive, this);
	_enemyInfo.enemyAni[ENEMY_LEFT_REVIVEANI]->setFPS(7);

	int arrLeftDie[] = { 8, 9, 10, 11, 12, 13 };
	_enemyInfo.enemyAni[ENEMY_LEFT_DIEANI]->setPlayFrame(arrLeftDie, 6, false, false);
	_enemyInfo.enemyAni[ENEMY_LEFT_DIEANI]->setFPS(8);

	// ������ �����ӵ�
	int arrRightMove[] = { 15, 16, 17, 18, 19, 18, 17, 16 };
	_enemyInfo.enemyAni[ENEMY_RIGHT_MOVEANI]->setPlayFrame(arrRightMove, 8, true);
	_enemyInfo.enemyAni[ENEMY_RIGHT_MOVEANI]->setFPS(2);

	int arrRightRevive[] = { 28, 27, 26 ,25, 24, 23, 22 };
	_enemyInfo.enemyAni[ENEMY_RIGHT_REVIVEANI]->setPlayFrame(arrRightRevive, 7, false, rightRevive, this);
	_enemyInfo.enemyAni[ENEMY_RIGHT_REVIVEANI]->setFPS(7);

	int arrRightDie[] = { 23, 24, 25, 26, 27, 28 };
	_enemyInfo.enemyAni[ENEMY_RIGHT_DIEANI]->setPlayFrame(arrRightDie, 6, false, false);
	_enemyInfo.enemyAni[ENEMY_RIGHT_DIEANI]->setFPS(8);

	_enemyInfo.stat = ENEMY_RIGHT_MOVE;
	_enemyInfo.enemyAni[ENEMY_RIGHT_MOVE]->start();
	_direction = ENEMY_RIGHT;
}

// ���°� ����(����)
void bloodSkeleton::move()
{

	RECT temp; // InterSectRect(_temp) < �̺κп� �̿�

	if (IntersectRect(&temp, &_comeRange, &_enemyInfo.playerRc))
	{
		if (_enemyInfo.x < _enemyInfo.playerRc.left)
		{
			_isLeft = false;
		}
		if (_enemyInfo.x > _enemyInfo.playerRc.left)
		{
			_isLeft = true;
		}
	}

	// ���� �� ��ȯ  
	// ���ʿ� �׸� ������ ���°��� ����������
	if (IntersectRect(&temp, &_enemyInfo.rc, &_rightRect) && !_isLeft)
	{
		_isLeft = true;
	}
	// ���� �ݴ�
	if (IntersectRect(&temp, &_enemyInfo.rc, &_leftRect) && _isLeft)
	{
		_isLeft = false;
	}

	if (!_enemyInfo.die && (_enemyInfo.stat != ENEMY_LEFT_DIE && _enemyInfo.stat != ENEMY_RIGHT_DIE))
	{
		// �������� ���°Ŷ��
		if (_isLeft)
		{
			_direction = ENEMY_LEFT;
			_enemyInfo.stat = ENEMY_LEFT_MOVE;
		}

		// ������
		else
		{
			_direction = ENEMY_RIGHT;
			_enemyInfo.stat = ENEMY_RIGHT_MOVE;
		}
	}

	// ���°��� ���� �ִϸ��̼�, �ൿ ����
	switch (_enemyInfo.stat)
	{
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
	case ENEMY_LEFT_DIE:
		_enemyInfo.enemyAni[ENEMY_LEFT_DIEANI]->frameUpdate(TIMEMANAGER->getElapsedTime());

		break;
	
	case ENEMY_RIGHT_DIE:
		_enemyInfo.enemyAni[ENEMY_RIGHT_DIEANI]->frameUpdate(TIMEMANAGER->getElapsedTime());

		break;
	case ENEMY_LEFT_REVIVE:
		_enemyInfo.enemyAni[ENEMY_LEFT_REVIVEANI]->frameUpdate(TIMEMANAGER->getElapsedTime());

		break;

	case ENEMY_RIGHT_REVIVE:
		_enemyInfo.enemyAni[ENEMY_RIGHT_REVIVEANI]->frameUpdate(TIMEMANAGER->getElapsedTime());

		break;
	}
}


void bloodSkeleton::leftRevive(void* obj)
{
	bloodSkeleton* skeleton = (bloodSkeleton*)obj;

	skeleton->setSkeletonDie(false);
	skeleton->setSkeletonDirection(true);
	skeleton->setSkeletonStat(ENEMY_LEFT_MOVE);
}

void bloodSkeleton::rightRevive(void* obj)
{
	bloodSkeleton* skeleton = (bloodSkeleton*)obj;

	skeleton->setSkeletonDie(false);
	skeleton->setSkeletonDirection(false);
	skeleton->setSkeletonStat(ENEMY_RIGHT_MOVE);
}