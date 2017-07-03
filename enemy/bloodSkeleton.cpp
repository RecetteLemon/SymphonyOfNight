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

	// ���࿡ �׾�����
	if (_enemyInfo.die && _enemyInfo.stat != ENEMY_LEFT_REVIVE && _enemyInfo.stat != ENEMY_RIGHT_REVIVE)
	{
		// ������ �ð��� �þ
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

	// �ִ� �ð��� ������ �ٽ� ��Ƴ�
	if (_reviveTime > _maxReviveTime)
	{
		// �����϶���
		if (_direction == ENEMY_LEFT && _enemyInfo.stat == ENEMY_LEFT_DIE)
		{
			_enemyInfo.stat = ENEMY_LEFT_REVIVE;			
		}
		// �������϶�
		if (_direction == ENEMY_RIGHT && _enemyInfo.stat == ENEMY_RIGHT_DIE)
		{
			_enemyInfo.stat = ENEMY_RIGHT_REVIVE;
		}
		// ���� ������ �ٽ� �ʱ�ȭ, �ִ� ����
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

// �̹��� �ʱ�ȭ
void bloodSkeleton::imageInit()
{
	// ���� �����ӵ�
	int arrLeftMove[] = { 0, 1, 2, 3, 4, 3, 2, 1 };
	KEYANIMANAGER->addArrayFrameAnimation("leftSkeleMove", "bloodSkeleton", arrLeftMove, 8, 3, true); // �̵�

	int arrLeftRevive[] = { 13, 12, 11, 10, 9, 8, 7 };
	KEYANIMANAGER->addArrayFrameAnimation("leftSkeleRevive", "bloodSkeleton", arrLeftRevive, 7, 1, false, leftRevive, this); // ��Ƴ��� �����̵� �ִϸ��̼����� �ٲ�

	int arrLeftDie[] = { 8, 9, 10, 11, 12 };
	_enemyInfo.enemyAni[ENEMY_LEFT_DIE]->setPlayFrame(arrLeftDie, 5, false, false);

	KEYANIMANAGER->addArrayFrameAnimation("leftSkeleDie", "bloodSkeleton", arrLeftDie, 5, 1, false); // ����


	// ������ �����ӵ�
	int arrRightMove[] = { 15, 16, 17, 18, 19, 18, 17, 16 };
	KEYANIMANAGER->addArrayFrameAnimation("rightSkeleMove", "bloodSkeleton", arrRightMove, 8, 3, true); // �̵�

	int arrRightRevive[] = { 28, 27, 26 ,25, 24, 23, 22 };
	KEYANIMANAGER->addArrayFrameAnimation("rightSkeleRevive", "bloodSkeleton", arrRightRevive, 7, 1, false, rightRevive, this); // ��Ƴ��� �����ʿ��������� �ٲ�

	int arrRightDie[] = { 23, 24, 25, 26, 27, 28 };
	KEYANIMANAGER->addArrayFrameAnimation("rightSkeleDie", "bloodSkeleton", arrRightDie, 6, 1, false); // ����

	// �ִϸ��̼� ����
	_enemyInfo.enemyAni = KEYANIMANAGER->findAnimation("rightSkeleMove");
	_enemyInfo.enemyAni->start();
	_enemyInfo.stat = ENEMY_RIGHT_MOVE;
	_direction = ENEMY_RIGHT;
}

// ���°� ����(����)
void bloodSkeleton::statChange()
{

	RECT temp; // InterSectRect(_temp) < �̺κп� �̿�

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