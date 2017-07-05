#include "stdafx.h"
#include "Dracula.h"


Dracula::Dracula()
{
}


Dracula::~Dracula()
{
}

HRESULT Dracula::init(const char* imageName, float x, float y)
{
	enemy::init(imageName, x, y);

	_enemyInfo.enemyImage = IMAGEMANAGER->addFrameImage("Dracula", "CounterDracula_r2.bmp", 510, 570, 6, 6, true, RGB(255, 0, 255));

	_enemyInfo.MonsterImage = IMAGEMANAGER->addFrameImage("MonsterDracula", "CounterDracula_Monster.bmp", 1395, 700,9, 4, true, RGB(255, 0, 255));

	_DraculaDirection = DRACULA_RIGHT_IDLE;

	_enemyInfo.rc = RectMakeCenter(_enemyInfo.x, _enemyInfo.y, _enemyInfo.enemyImage->getFrameWidth(), _enemyInfo.enemyImage->getFrameHeight());

	// 변신 전 드라큘라에 대한 키 애니 정의를 내려주자~
	int rightIdle[] = { 11 }; //오른쪽 정지모션
	KEYANIMANAGER->addArrayFrameAnimation("DraculaRightIdle", "Dracula", rightIdle, 1, 6, true);

	int leftIdle[] = { 0 }; //왼쪽 정지모션
	KEYANIMANAGER->addArrayFrameAnimation("DraculaLeftIdle", "Dracula", leftIdle, 1, 6, true);

	int rightBulletFire[] = { 10,9,8,7,6 }; //오른편 불꽃 파이어모션
	KEYANIMANAGER->addArrayFrameAnimation("DraculaRightBulletFire", "Dracula", rightBulletFire, 5, 8, false, cbRightBulletFire,this);

	int leftBulletFire[] = { 1,2,3,4,5 }; //왼편 불꽃 파이어모션
	KEYANIMANAGER->addArrayFrameAnimation("DraculaLeftBulletFire", "Dracula", leftBulletFire, 5, 8, false, cbLeftBulletFire,this);

	int rightBallFire[] = { 18,19,20,21,22 }; //오른편 파이어볼 파이어 모션
	KEYANIMANAGER->addArrayFrameAnimation("DraculaRightBallFire", "Dracula", rightBallFire, 5, 8, false, cbRightBallFire,this);

	int leftBallFire[] = { 12,13,14,15,16 }; //왼편 파이어볼 파이어 모션
	KEYANIMANAGER->addArrayFrameAnimation("DraculaLeftBallFire", "Dracula", leftBallFire, 5, 8, false, cbLeftBallFire, this);

	int rightChange[] = { 35,34,33,32,31,30 }; //오른편 몬스터로 변신 모션
	KEYANIMANAGER->addArrayFrameAnimation("DraculaRightChange", "Dracula", rightChange, 6, 15, true);

	int leftChange[] = { 24,25,26,27,28,29 }; //왼편 몬스터로 변신 모션
	KEYANIMANAGER->addArrayFrameAnimation("DraculaLeftChange", "Dracula", leftChange, 6, 15, true);

	// 변신 후 드라큘라 몬스터에 대한 키 애니 정의를 내려주자~
	int Monster_right[] = { 17,16,15,14,13,12,11,10,9 }; //오른쪽 모션
	KEYANIMANAGER->addArrayFrameAnimation("MonsterStandR", "MonsterDracula", Monster_right, 9, 8, true);

	int Monster_Left[] = { 0,1,2,3,4,5,6,7,8 }; //왼쪽 모션
	KEYANIMANAGER->addArrayFrameAnimation("MonsterStandL", "MonsterDracula", Monster_Left, 9, 8, true);

	int MonsterJump_right[] = { 32, 31, 30, 29, 28, 27 }; //오른쪽 점프모션
	KEYANIMANAGER->addArrayFrameAnimation("MonsterJumpR", "MonsterDracula", MonsterJump_right, 6, 8, true);

	int MonsterJump_Left[] = { 18,19,20,21,22,23 };  //왼쪽 점프모션
	KEYANIMANAGER->addArrayFrameAnimation("MonsterJumpL", "MonsterDracula", MonsterJump_Left, 6, 8, true);

	int MonsterFire_right[] = {11}; //오른쪽 파이어
	KEYANIMANAGER->addArrayFrameAnimation("MonsterFireR", "MonsterDracula", MonsterFire_right, 1, 10, true);

	int MonsterFire_left[] = { 2 };  //왼쪽 파이어
	KEYANIMANAGER->addArrayFrameAnimation("MonsterFireL", "MonsterDracula", MonsterFire_left, 1, 10, true);

	_enemyInfo.enemyAni = KEYANIMANAGER->findAnimation("MonsterJumpR");
	_enemyInfo.enemyAni->start();

	//드라큘라 보스의 HP
	_MaxHP = /*_currentHP =*/ 1000;
	_currentHP = 440;
	//불꽃에 대한 초기화
	_Bullet = new Bullet;
	_Bullet->init("DraculaFireBullet");
	_fireCount = 0;
	_fireSpeed = 3;
	
	//파이어볼에 대한 초기화
	_Bullet = new Bullet;
	_Bullet->init("DraculaFireBall");
	//_fireCount = 0;
	//_fireSpeed = 0;

	//순간이동에 관한 초기값
	Appear = true;
	
	//순간이동에 관한 시간
	_maxReAppearTime = 2;
	_reAppearTime = 0;
	
	
	//--------------
	_bCount = 0;

	_isLeft = false;
	// 렉트의 초기화
	_Playerrc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 80, 100, 100);
	
	return S_OK;
}

void Dracula::release()
{

}

void Dracula::update()
{
	enemy::update();

	if(KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_Playerrc.left -= 3;
		_Playerrc.right -= 3;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_Playerrc.right += 3;
		_Playerrc.left += 3;
	}


	KEYANIMANAGER->update();

	//총알 값에 대한 업데이트
	
	_Bullet->update();
	//fire();
	appear();
}

void Dracula::render()
{
	enemy::render();

	

	//_Bullet->getVBullet().size();

	_Bullet->render();

	if (Appear == true)
	{
		Rectangle(getMemDC(), _enemyInfo.rc.left, _enemyInfo.rc.top, _enemyInfo.rc.right, _enemyInfo.rc.bottom);
		/*_enemyInfo.enemyImage->aniRender(getMemDC(), _enemyInfo.rc.left, _enemyInfo.rc.top, _enemyInfo.enemyAni);*/
		
	}

	Rectangle(getMemDC(), _Playerrc.left, _Playerrc.top, _Playerrc.right, _Playerrc.bottom);

	_enemyInfo.MonsterImage->aniRender(getMemDC(), _enemyInfo.rc.left, _enemyInfo.rc.top, _enemyInfo.enemyAni);

}

void Dracula::appear()
{

	/*if (Appear == false)
	{
		_reAppearTime += TIMEMANAGER->getElapsedTime();
		if (_reAppearTime > _maxReAppearTime)
		{
			Appear = true;
			_enemyInfo.x = RND->getFromIntTo(30, 550);
			_reAppearTime = 0;
			
			if (_enemyInfo.x <= _Playerrc.left) 
			{
				if (_bCount < 3)
				{
					_DraculaDirection = DRACULA_RIGHT_BULLETATTK;
					_enemyInfo.enemyAni = KEYANIMANAGER->findAnimation("DraculaRightBulletFire");
					_enemyInfo.enemyAni->start();
				}
				else if (_bCount >= 3)
				{
					_DraculaDirection = DRACULA_RIGHT_BALLATTK;
					_enemyInfo.enemyAni = KEYANIMANAGER->findAnimation("DraculaRightBallFire");
					_enemyInfo.enemyAni->start();
				}
			}
			else
			{
				if (_bCount < 3)
				{
					_DraculaDirection = DRACULA_LEFT_BULLETATTK;
					_enemyInfo.enemyAni = KEYANIMANAGER->findAnimation("DraculaLeftBulletFire");
					_enemyInfo.enemyAni->start();
				}
				else if (_bCount >= 3)
				{
					_DraculaDirection = DRACULA_LEFT_BALLATTK;
					_enemyInfo.enemyAni = KEYANIMANAGER->findAnimation("DraculaLeftBallFire");
					_enemyInfo.enemyAni->start();
				}

			}
				
		}

	}
	else
	{
		_reAppearTime += TIMEMANAGER->getElapsedTime();
		if (_reAppearTime > _maxReAppearTime)
		{
			Appear = false;
			_reAppearTime = 0;
		}
	}
*/
	//보스 렉트
	if (_DraculaPhase == 1)
	{
	    _enemyInfo.rc = RectMakeCenter(_enemyInfo.x, _enemyInfo.y, _enemyInfo.enemyImage->getFrameWidth(), _enemyInfo.enemyImage->getFrameHeight());
	}
	else if (_DraculaPhase == 2)
	{
		_enemyInfo.rc = RectMakeCenter(_enemyInfo.x, _enemyInfo.y, _enemyInfo.MonsterImage->getFrameWidth(), _enemyInfo.MonsterImage->getFrameHeight());
	}
	
}

void Dracula::fire()
{
	//bool fire;
	//_fireCount % _fireSpeed == 0 ? fire = true : fire = false;

	//if (_fireCount / _fireSpeed > 10 && _bCount == 0)  
	//{
	//	_DraculaDirection = DRACULA_RIGHT_BULLETATTK;
	//	_enemyInfo.enemyAni = KEYANIMANAGER->findAnimation("DraculaRightBulletFire");
	//	_enemyInfo.enemyAni->start();
	//	_fireCount = 0;
	//	_enemyInfo.fire = true;
	//	_Bullet->fire("DraculaFireBullet", _enemyInfo.x + 20, _enemyInfo.y, 0, 3);
	//	_Bullet->fire("DraculaFireBullet", _enemyInfo.x + 20, _enemyInfo.y + 30, 0, 3);
	//	_Bullet->fire("DraculaFireBullet", _enemyInfo.x + 20, _enemyInfo.y + 30 * 2, 0, 3);
	//	
	//}
	//else if (_fireCount % 3 == 0 && _bCount == 0)
	//{
	//	_DraculaDirection = DRACULA_RIGHT_BALLATTK;
	//	_enemyInfo.enemyAni = KEYANIMANAGER->findAnimation("DraculaRightBulletFire");
	//	_enemyInfo.enemyAni->start();
	//	//_fireCount += 1;
	//	_enemyInfo.fire = true;
	//	_Bullet->fire("DraculaFireBall", _enemyInfo.x + 20, _enemyInfo.y, 0, 3);
	//	_Bullet->fire("DraculaFireBall", _enemyInfo.x + 20, _enemyInfo.y + 30, 0, 3);
	//	_bCount = 1;
	//}
	//
	//
	//if (_frameCount + FRAMECOUNT > GetTickCount())
	//{
	//	_frameCount = GetTickCount();
	//	_fireCount += 1;
	//	_bCount = 0;
	//}

	if (_Playerrc.right - _enemyInfo.x < 0) _isLeft = true;
	else if (_Playerrc.left - _enemyInfo.x >= 0) _isLeft = false;
	
	float fireX;
	//float fireY;
	float fireAngle;



	if (_DraculaPhase == 1)
	{

		if (_bCount < 3)
		{
			if (_isLeft)
			{
				fireX = _enemyInfo.x - (_enemyInfo.rc.right - _enemyInfo.rc.left) / 2;
				fireAngle = PI;
			}
			else
			{
				fireX = _enemyInfo.x + 20;
				fireAngle = 0;
			}

			_Bullet->fire("DraculaFireBullet", fireX, _enemyInfo.y - 50, fireAngle, 3, _isLeft);
			_Bullet->fire("DraculaFireBullet", fireX, _enemyInfo.y - 20, fireAngle, 3, _isLeft);
			_Bullet->fire("DraculaFireBullet", fireX, _enemyInfo.y + 10, fireAngle, 3, _isLeft);

			++_bCount;
		}
		else if (_bCount >= 3)
		{
			_Bullet->fire("DraculaFireBall", _enemyInfo.x + 20, _enemyInfo.y - 40, 0, 3, _isLeft);
			_Bullet->fire("DraculaFireBall", _enemyInfo.x, _enemyInfo.y, 0, 3, _isLeft);
			_bCount = 0;
		}
	}
	else if (_DraculaPhase == 2)
	{

	}

	

}

void Dracula::setDraculaDirection()
{
	//드라큘라의 상태
	switch (_DraculaDirection)
	{
	case DRACULA_RIGHT_IDLE:
		_enemyInfo.enemyAni = KEYANIMANAGER->findAnimation("DraculaRightIdle");
		break;

	case DRACULA_LEFT_IDLE:
		_enemyInfo.enemyAni = KEYANIMANAGER->findAnimation("DraculaLeftIdle");
		break;

	case DRACULA_RIGHT_BULLETATTK:
		_enemyInfo.enemyAni = KEYANIMANAGER->findAnimation("DraculaRightBulletFire");
		if (!_enemyInfo.enemyAni->isPlay()) _enemyInfo.enemyAni->start();
		break;

	case DRACULA_LEFT_BULLETATTK:
		_enemyInfo.enemyAni = KEYANIMANAGER->findAnimation("DraculaLeftBulletFire");
		if (!_enemyInfo.enemyAni->isPlay()) _enemyInfo.enemyAni->start();
		break;

	case DRACULA_RIGHT_BALLATTK:
		_enemyInfo.enemyAni = KEYANIMANAGER->findAnimation("DraculaRightBallFire");
		if (!_enemyInfo.enemyAni->isPlay()) _enemyInfo.enemyAni->start();
		break;

	case DRACULA_LEFT_BALLATTK:
		_enemyInfo.enemyAni = KEYANIMANAGER->findAnimation("DraculaLeftBallFire");
		if (!_enemyInfo.enemyAni->isPlay()) _enemyInfo.enemyAni->start();
		break;

	case DRACULA_RIGHT_CHANGE:
		_enemyInfo.enemyAni = KEYANIMANAGER->findAnimation("DraculaRightChange");
		if (!_enemyInfo.enemyAni->isPlay()) _enemyInfo.enemyAni->start();
		break;

	case DRACULA_LEFT_CHANGE:
		_enemyInfo.enemyAni = KEYANIMANAGER->findAnimation("DraculaLeftChange");
		if (!_enemyInfo.enemyAni->isPlay()) _enemyInfo.enemyAni->start();
		break;
	}



}

void Dracula::setDraculaPhase()
{
	if (_currentHP >= 1000)  _DraculaPhase = PHASE1;
	if (_currentHP <= 500)  _DraculaPhase = PHASE2;

}

void Dracula::cbRightBulletFire(void* obj)
{
	Dracula* dr = (Dracula*)obj;

	dr->setDraculaDirection(DRACULA_RIGHT_IDLE);
	dr->_enemyInfo.enemyAni = KEYANIMANAGER->findAnimation("DraculaRightIdle");
	dr->_enemyInfo.enemyAni->start();
	dr->fire();

}

void Dracula::cbLeftBulletFire(void* obj)
{
	Dracula* dr = (Dracula*)obj;

	dr->setDraculaDirection(DRACULA_LEFT_IDLE);
	dr->_enemyInfo.enemyAni = KEYANIMANAGER->findAnimation("DraculaLeftIdle");
	dr->_enemyInfo.enemyAni->start();
	dr->fire();
}

void Dracula::cbRightBallFire(void* obj)
{
	Dracula* dr = (Dracula*)obj;

	dr->setDraculaDirection(DRACULA_RIGHT_IDLE);
	dr->_enemyInfo.enemyAni = KEYANIMANAGER->findAnimation("DraculaRightIdle");
	dr->_enemyInfo.enemyAni->start();
	dr->fire();
}
	 
void Dracula::cbLeftBallFire(void* obj)
{
	Dracula* dr = (Dracula*)obj;

	dr->setDraculaDirection(DRACULA_LEFT_IDLE);
	dr->_enemyInfo.enemyAni = KEYANIMANAGER->findAnimation("DraculaRightIdle");
	dr->_enemyInfo.enemyAni->start();
	dr->fire();
}
