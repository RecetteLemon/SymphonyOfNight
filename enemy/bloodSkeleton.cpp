#include "stdafx.h"
#include "bloodSkeleton.h"


bloodSkeleton::bloodSkeleton()
{
}


bloodSkeleton::~bloodSkeleton()
{
}

HRESULT bloodSkeleton::init(const char* imageName, RECT leftRect, RECT rightRect, float x, float y)
{
	enemy::init(imageName, x, y);
	IMAGEMANAGER->addFrameImage("bloodSkeleton", "image/bloodSkeleton.bmp", 23 * 5 * 2, 47 * 6 * 2, 5, 6, true, RGB(0xff, 0, 0xff));

	// ������ ����, ����ġ, ü���� �ʱ�ȭ
	_enemyInfo.atk = 4;
	_enemyInfo.exp = 20;
	_enemyInfo.hp = 10000;
	_enemyInfo.die = false;
	_isLeft = false;

	_speed = 1.5f;
	_maxReviveTime = 5;
	_reviveTime = 0;

	_leftRect = leftRect;
	_rightRect = rightRect;

	imageInit();


	return S_OK;
}

void bloodSkeleton::release()
{

}

void bloodSkeleton::update()
{
	enemy::update();
	statChange();

	//_enemyInfo.hp -= 200;


	// ���࿡ �׾�����
	if (_enemyInfo.die)
	{
		// ������ �ð��� �þ
		_reviveTime += TIMEMANAGER->getElapsedTime();
		if (_direction == ENEMY_LEFT)
		{
			_enemyInfo.stat = ENEMY_LEFT_DIE;
		}
		if (_direction == ENEMY_RIGHT)
		{
			_enemyInfo.stat = ENEMY_RIGHT_DIE;
		}
	}
	// �ִ� �ð��� ������ �ٽ� ��Ƴ�
	if (_reviveTime > _maxReviveTime)
	{
		// �����϶���
		if (_direction == ENEMY_LEFT)
		{
			_enemyInfo.stat = ENEMY_LEFT_REVIVE;
			_enemyInfo.enemyAni = KEYANIMANAGER->findAnimation("leftRevive");
		}
		// �������϶�
		if (_direction == ENEMY_RIGHT)
		{
			_enemyInfo.stat = ENEMY_RIGHT_REVIVE;
			_enemyInfo.enemyAni = KEYANIMANAGER->findAnimation("rightRevive");
		}
		// ���� ������ �ٽ� �ʱ�ȭ, �ִ� ����
		_enemyInfo.hp = 10000;
		_enemyInfo.enemyAni->start();
		_reviveTime = 0;
		_enemyInfo.die = false;
	}

	KEYANIMANAGER->update();
	_enemyInfo.rc = RectMake(_enemyInfo.x, _enemyInfo.y,
		_enemyInfo.enemyImage->getFrameWidth(), _enemyInfo.enemyImage->getFrameHeight());

}

void bloodSkeleton::render()
{
	enemy::render();
	Rectangle(getMemDC(), _enemyInfo.rc.left, _enemyInfo.rc.top, _enemyInfo.rc.right, _enemyInfo.rc.bottom);
	_enemyInfo.enemyImage->aniRender(getMemDC(), _enemyInfo.x, _enemyInfo.y, _enemyInfo.enemyAni);
}

void bloodSkeleton::imageInit()
{
	// ���� �����ӵ�
	int arrLeftMove[] = { 0, 1, 2, 3, 4, 3, 2, 1 };
	KEYANIMANAGER->addArrayFrameAnimation("leftMove", "bloodSkeleton", arrLeftMove, 8, 10, true); // �̵�

	int arrLeftRevive[] = { 13, 12, 11, 10, 9, 8, 7, 6, 5 };
	KEYANIMANAGER->addArrayFrameAnimation("leftRevive", "bloodSkeleton", arrLeftRevive, 9, 7, false, leftRevive, this); // ��Ƴ��� �����̵� �ִϸ��̼����� �ٲ�

	int arrLeftDie[] = { 8, 9, 10, 11, 12 };
	KEYANIMANAGER->addArrayFrameAnimation("leftDie", "bloodSkeleton", arrLeftDie, 5, 10, false); // ����


	// ������ �����ӵ�
	int arrRightMove[] = { 15, 16, 17, 18, 19, 18, 17, 16 };
	KEYANIMANAGER->addArrayFrameAnimation("rightMove", "bloodSkeleton", arrRightMove, 8, 10, true); // �̵�

	int arrRightRevive[] = { 28, 27, 26 ,25, 24, 23, 22, 21, 20 };
	KEYANIMANAGER->addArrayFrameAnimation("rightRevive", "bloodSkeleton", arrRightRevive, 9, 10, false, rightRevive, this); // ��Ƴ��� �����ʿ��������� �ٲ�

	int arrRightDie[] = { 23, 24, 25, 26, 27, 28 };
	KEYANIMANAGER->addArrayFrameAnimation("rightDie", "bloodSkeleton", arrRightDie, 6, 7, false); // ����

	// �ִϸ��̼� ����
	_enemyInfo.enemyAni = KEYANIMANAGER->findAnimation("leftMove");
	_enemyInfo.enemyAni->start();
	_enemyInfo.stat = ENEMY_LEFT_MOVE;
}

void bloodSkeleton::statChange()
{
	// ���� �� ��ȯ
	// ���ʿ� �׸� ������ ���°��� ����������
	RECT temp; // InterSectRect(_temp) < �̺κп� �̿�
			   // ���� �ݴ�
	if (IntersectRect(&temp, &_enemyInfo.rc, &_rightRect) && !_isLeft)
	{
		_isLeft = true;
	
	
	}
	if (IntersectRect(&temp, &_enemyInfo.rc, &_leftRect) && _isLeft)
	{
		_isLeft = false;
	}

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

	switch (_enemyInfo.stat)
	{
	case ENEMY_LEFT_MOVE:
		_enemyInfo.enemyAni = KEYANIMANAGER->findAnimation("leftMove");
		_enemyInfo.x -= _speed;
		if (!_enemyInfo.enemyAni->isPlay())
		{
			_enemyInfo.enemyAni->start();
		}
		break;

	case ENEMY_RIGHT_MOVE:
		_enemyInfo.enemyAni = KEYANIMANAGER->findAnimation("rightMove");
		_enemyInfo.x += _speed;
		if (!_enemyInfo.enemyAni->isPlay())
		{
			_enemyInfo.enemyAni->start();
		}
		break;
	case ENEMY_LEFT_DIE:
		_enemyInfo.enemyAni = KEYANIMANAGER->findAnimation("leftDie");
		
		if (!_enemyInfo.enemyAni->isPlay())
		{
			_enemyInfo.enemyAni->start();
		}	
		break;
	
	case ENEMY_RIGHT_DIE:
		_enemyInfo.enemyAni = KEYANIMANAGER->findAnimation("rightDie");
		if (!_enemyInfo.enemyAni->isPlay())
		{
			_enemyInfo.enemyAni->start();
		}
		break;
	}

	if (_enemyInfo.hp < 0)
	{
		_enemyInfo.die = true;
	} 
	
}


void bloodSkeleton::leftRevive(void* obj)
{
	bloodSkeleton* skeleton = (bloodSkeleton*)obj;

	skeleton->setSkeletonDirection(ENEMY_LEFT_MOVE);
	skeleton->setSkeletonAnimation(KEYANIMANAGER->findAnimation("leftMove"));
	skeleton->getSkeletonAnimation()->start();
}

void bloodSkeleton::rightRevive(void* obj)
{
	bloodSkeleton* skeleton = (bloodSkeleton*)obj;

	skeleton->setSkeletonDirection(ENEMY_RIGHT_MOVE);
	skeleton->setSkeletonAnimation(KEYANIMANAGER->findAnimation("rightMove"));
	skeleton->getSkeletonAnimation()->start();
}