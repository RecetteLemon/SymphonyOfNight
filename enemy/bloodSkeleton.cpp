#include "stdafx.h"
#include "bloodSkeleton.h"


bloodSkeleton::bloodSkeleton()
{
}


bloodSkeleton::~bloodSkeleton()
{
}

// 버그 목록들
// 적이 죽으면 애니메이션이 계속 실행됨
// 적이 죽고 살아나면 계속 살아남
// 살아나면 3번째 살아날때까지 이미지 프레임 속도 증가



HRESULT bloodSkeleton::init(const char* imageName, RECT leftRect, RECT rightRect, float x, float y)
{
	enemy::init(imageName, x, y, 1);

	// 스켈의 공력, 경험치, 체력을 초기화
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



	// 만약에 죽었으면
	if (_enemyInfo.die && _enemyInfo.stat != ENEMY_LEFT_REVIVE && _enemyInfo.stat != ENEMY_RIGHT_REVIVE)
	{
		// 딜레이 시간이 늘어남
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

	// 최대 시간이 지나면 다시 살아남
	if (_reviveTime > _maxReviveTime)
	{
		// 왼쪽일때랑
		if (_direction == ENEMY_LEFT && _enemyInfo.stat == ENEMY_LEFT_DIE)
		{
			_enemyInfo.stat = ENEMY_LEFT_REVIVE;
			_enemyInfo.enemyAni[ENEMY_LEFT_REVIVEANI]->start();
		}
		// 오른쪽일때
		if (_direction == ENEMY_RIGHT && _enemyInfo.stat == ENEMY_RIGHT_DIE)
		{
			_enemyInfo.stat = ENEMY_RIGHT_REVIVE;
			_enemyInfo.enemyAni[ENEMY_RIGHT_REVIVEANI]->start();
		}
		// 적의 정보값 다시 초기화, 애니 시작
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
	// 상태값에 따른 애니메이션, 행동 변경
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

// 이미지 초기화
void bloodSkeleton::imageInit()
{
	for (int i = 0; i < ENEMY_ANI_AND; i++)
	{
		_enemyInfo.enemyAni[i] = new animation;
		_enemyInfo.enemyAni[i]->init(_enemyInfo.enemyImage->getWidth(), _enemyInfo.enemyImage->getHeight()
			, _enemyInfo.enemyImage->getFrameWidth(), _enemyInfo.enemyImage->getFrameHeight());
	}



	// 왼쪽 프레임들
	int arrLeftMove[] = { 0, 1, 2, 3, 4, 3, 2, 1 };
	_enemyInfo.enemyAni[ENEMY_LEFT_MOVEANI]->setPlayFrame(arrLeftMove, 8, true);
	_enemyInfo.enemyAni[ENEMY_LEFT_MOVEANI]->setFPS(5);

	int arrLeftRevive[] = { 13, 12, 11, 10, 9, 8, 7 };
	_enemyInfo.enemyAni[ENEMY_LEFT_REVIVEANI]->setPlayFrame(arrLeftRevive, 7, false, leftRevive, this);
	_enemyInfo.enemyAni[ENEMY_LEFT_REVIVEANI]->setFPS(7);

	int arrLeftDie[] = { 8, 9, 10, 11, 12, 13 };
	_enemyInfo.enemyAni[ENEMY_LEFT_DIEANI]->setPlayFrame(arrLeftDie, 6, false, false);
	_enemyInfo.enemyAni[ENEMY_LEFT_DIEANI]->setFPS(8);

	// 오른쪽 프레임들
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

// 상태값 변경(패턴)
void bloodSkeleton::move()
{

	RECT temp; // InterSectRect(_temp) < 이부분에 이용

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

	// 방향 값 전환  
	// 왼쪽에 네모에 다으면 상태값을 오른쪽으로
	if (IntersectRect(&temp, &_enemyInfo.rc, &_rightRect) && !_isLeft)
	{
		_isLeft = true;
	}
	// 위와 반대
	if (IntersectRect(&temp, &_enemyInfo.rc, &_leftRect) && _isLeft)
	{
		_isLeft = false;
	}

	if (!_enemyInfo.die && (_enemyInfo.stat != ENEMY_LEFT_DIE && _enemyInfo.stat != ENEMY_RIGHT_DIE))
	{
		// 왼쪽으로 가는거라면
		if (_isLeft)
		{
			_direction = ENEMY_LEFT;
			_enemyInfo.stat = ENEMY_LEFT_MOVE;
		}

		// 오른쪽
		else
		{
			_direction = ENEMY_RIGHT;
			_enemyInfo.stat = ENEMY_RIGHT_MOVE;
		}
	}

	// 상태값에 따른 애니메이션, 행동 변경
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