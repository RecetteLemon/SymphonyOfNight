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
	_enemyInfo.hp = 10000;
	_enemyInfo.die = false;
	_isLeft = _playCount = false;

	_enemyInfo.speed = 0.5f;
	_maxReviveTime = 5;
	_reviveTime = 0;

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
	statChange();

	_enemyInfo.hp -= RND->getFromFloatTo(0.1, 100.9f);
	if (_enemyInfo.hp < 0)
	{
		_enemyInfo.die = true;
		_playCount = false;
	}

	// 만약에 죽었으면
	if (_enemyInfo.die && _enemyInfo.stat != ENEMY_LEFT_REVIVE && _enemyInfo.stat != ENEMY_RIGHT_REVIVE)
	{
		// 딜레이 시간이 늘어남
		_reviveTime += TIMEMANAGER->getElapsedTime();
		if (_enemyInfo.stat == ENEMY_LEFT_MOVE)
		{
			_enemyInfo.stat = ENEMY_LEFT_DIE;
			_enemyInfo.enemyAni = KEYANIMANAGER->findAnimation("leftSkeleDie");
			_enemyInfo.enemyAni->start();
		}
		if (_enemyInfo.stat == ENEMY_RIGHT_MOVE)
		{
			_enemyInfo.stat = ENEMY_RIGHT_DIE;
			_enemyInfo.enemyAni = KEYANIMANAGER->findAnimation("rightSkeleDie");
			_enemyInfo.enemyAni->start();
		}
		
	}

	// 최대 시간이 지나면 다시 살아남
	if (_reviveTime > _maxReviveTime)
	{
		// 왼쪽일때랑
		if (_direction == ENEMY_LEFT && _enemyInfo.stat == ENEMY_LEFT_DIE)
		{
			_enemyInfo.stat = ENEMY_LEFT_REVIVE;			
		}
		// 오른쪽일때
		if (_direction == ENEMY_RIGHT && _enemyInfo.stat == ENEMY_RIGHT_DIE)
		{
			_enemyInfo.stat = ENEMY_RIGHT_REVIVE;
		}
		// 적의 정보값 다시 초기화, 애니 시작
		_reviveTime = 0;
		_enemyInfo.hp = 10000;
		_playCount = true;
	}

	KEYANIMANAGER->update();

}

void bloodSkeleton::render()
{
	enemy::render();
	Rectangle(getMemDC(), _enemyInfo.rc.left, _enemyInfo.rc.top, _enemyInfo.rc.right, _enemyInfo.rc.bottom);
	_enemyInfo.enemyImage->aniRender(getMemDC(), _enemyInfo.x, _enemyInfo.y, _enemyInfo.enemyAni);
}

// 이미지 초기화
void bloodSkeleton::imageInit()
{
	// 왼쪽 프레임들
	int arrLeftMove[] = { 0, 1, 2, 3, 4, 3, 2, 1 };
	KEYANIMANAGER->addArrayFrameAnimation("leftSkeleMove", "bloodSkeleton", arrLeftMove, 8, 3, true); // 이동

	int arrLeftRevive[] = { 13, 12, 11, 10, 9, 8, 7 };
	KEYANIMANAGER->addArrayFrameAnimation("leftSkeleRevive", "bloodSkeleton", arrLeftRevive, 7, 1, false, leftRevive, this); // 살아나고 왼쪽이동 애니메이션으로 바꿈

	int arrLeftDie[] = { 8, 9, 10, 11, 12 };
	_enemyInfo.enemyAni[ENEMY_LEFT_DIE]->setPlayFrame(arrLeftDie, 5, false, false);

	KEYANIMANAGER->addArrayFrameAnimation("leftSkeleDie", "bloodSkeleton", arrLeftDie, 5, 1, false); // 죽음


	// 오른쪽 프레임들
	int arrRightMove[] = { 15, 16, 17, 18, 19, 18, 17, 16 };
	KEYANIMANAGER->addArrayFrameAnimation("rightSkeleMove", "bloodSkeleton", arrRightMove, 8, 3, true); // 이동

	int arrRightRevive[] = { 28, 27, 26 ,25, 24, 23, 22 };
	KEYANIMANAGER->addArrayFrameAnimation("rightSkeleRevive", "bloodSkeleton", arrRightRevive, 7, 1, false, rightRevive, this); // 살아나고 오른쪽움직임으로 바꿈

	int arrRightDie[] = { 23, 24, 25, 26, 27, 28 };
	KEYANIMANAGER->addArrayFrameAnimation("rightSkeleDie", "bloodSkeleton", arrRightDie, 6, 1, false); // 죽음

	// 애니메이션 시작
	_enemyInfo.enemyAni = KEYANIMANAGER->findAnimation("rightSkeleMove");
	_enemyInfo.enemyAni->start();
	_enemyInfo.stat = ENEMY_RIGHT_MOVE;
	_direction = ENEMY_RIGHT;
}

// 상태값 변경(패턴)
void bloodSkeleton::statChange()
{

	RECT temp; // InterSectRect(_temp) < 이부분에 이용

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
		_enemyInfo.enemyAni = KEYANIMANAGER->findAnimation("leftSkeleMove");
		_enemyInfo.x -= _enemyInfo.speed;
		if (!_enemyInfo.enemyAni->isPlay())
		{
			_enemyInfo.enemyAni->start();
		}
		_enemyInfo.rc = RectMake(_enemyInfo.x, _enemyInfo.y,
			_enemyInfo.enemyImage->getFrameWidth(), _enemyInfo.enemyImage->getFrameHeight());
		break;

	case ENEMY_RIGHT_MOVE:
		_enemyInfo.enemyAni = KEYANIMANAGER->findAnimation("rightSkeleMove");
		_enemyInfo.x += _enemyInfo.speed;

		_enemyInfo.rc = RectMake(_enemyInfo.x, _enemyInfo.y,
			_enemyInfo.enemyImage->getFrameWidth(), _enemyInfo.enemyImage->getFrameHeight());
		break;
	case ENEMY_LEFT_DIE:

		break;
	
	case ENEMY_RIGHT_DIE:
		
		break;
	case ENEMY_LEFT_REVIVE:
		_enemyInfo.enemyAni = KEYANIMANAGER->findAnimation("leftSkeleRevive");
		if (!_enemyInfo.enemyAni->isPlay())
		{
			_enemyInfo.enemyAni->start();
		}

		break;

	case ENEMY_RIGHT_REVIVE:
		_enemyInfo.enemyAni = KEYANIMANAGER->findAnimation("rightSkeleRevive");
		if (!_enemyInfo.enemyAni->isPlay())
		{
			_enemyInfo.enemyAni->start();
		}

		break;
	}
}


void bloodSkeleton::leftRevive(void* obj)
{
	bloodSkeleton* skeleton = (bloodSkeleton*)obj;

	skeleton->setSkeletonDie(false);
	skeleton->setSkeletonDirection(true);
	skeleton->setSkeletonStat(ENEMY_LEFT_MOVE);
	skeleton->setSkeletonAnimation(KEYANIMANAGER->findAnimation("leftSkeleMove"));
	skeleton->getSkeletonAnimation()->start();
}

void bloodSkeleton::rightRevive(void* obj)
{
	bloodSkeleton* skeleton = (bloodSkeleton*)obj;

	skeleton->setSkeletonDie(false);
	skeleton->setSkeletonDirection(false);
	skeleton->setSkeletonStat(ENEMY_RIGHT_MOVE);
	skeleton->setSkeletonAnimation(KEYANIMANAGER->findAnimation("rightSkeleMove"));
	skeleton->getSkeletonAnimation()->start();
}