#include "stdafx.h"
#include "Dracula.h"


Dracula::Dracula()
{
}


Dracula::~Dracula()
{
}

HRESULT Dracula::init(const char* imageName, float x, float y, float moveRange)
{
	enemy::init(imageName, x, y, moveRange);


	_enemyInfo.MonsterImage = IMAGEMANAGER->addFrameImage("MonsterDracula", "image/boss/CounterDracula_Monster.bmp", 1395 * 2, 1400 * 2, 9, 8, true, RGB(255, 0, 255));

	imageInit();

	//드라큘라 보스의 HP
	_MaxHP = _currentHP = 1000;
	
	//불꽃에 대한 초기화
	_Bullet = new Bullet;
	_Bullet->init("DraculaFireBullet");
	_fireCount = 0;
	_fireSpeed = 3;
	
	//파이어볼에 대한 초기화
	_Bullet = new Bullet;
	_Bullet->init("DraculaFireBall");
	//_fireSpeed = 0;

	//몬스터 불꽃에 대한 초기화
	_Bullet = new Bullet;
	_Bullet->init("DraculaMonsterBullet");


//--------------------------//
	//순간이동에 관한 초기값
	Appear = true;
	
	//순간이동에 관한 시간
	_maxReAppearTime = 2;
	_reAppearTime = 0;
//------------------------//
	_bCount = 0;

	_isLeft = false;

	_saveY = y;
	_patternRan = _patternTime = 0;

	_enemyInfo.Jump = false; //점프에 대한 초기값
	// 렉트의 초기화
	_Playerrc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 80, 100, 100);
	_patternRan = 0;
	_gravity =  GRAVITY;

	_DraculaPhase = PHASE1;
	return S_OK;
}

void Dracula::release()
{
	enemy::release();
}

void Dracula::update()
{
	enemy::update();
	move();
	setDraculaDirection();

	_currentHP -= RND->getFromFloatTo(1, 9);

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
	appear();
}

void Dracula::render()
{
	enemy::render();

	/*_Bullet->getVBullet().size();*/

	_Bullet->render();
	if (_DraculaPhase == PHASE1)
	{
		if (Appear == true)
		{
			Rectangle(getMemDC(), _enemyInfo.rc.left, _enemyInfo.rc.top, _enemyInfo.rc.right, _enemyInfo.rc.bottom);
			_enemyInfo.enemyImage->aniRender(getMemDC(), _enemyInfo.x, _enemyInfo.y, _enemyInfo.bossAni);

		}
	}

	else if (_DraculaPhase == PHASE2)
	{
		_enemyInfo.MonsterImage->aniRender(getMemDC(), _enemyInfo.x, _enemyInfo.y, _enemyInfo.bossAni);
	}
	Rectangle(getMemDC(), _Playerrc.left, _Playerrc.top, _Playerrc.right, _Playerrc.bottom);



}

void Dracula::imageInit()
{
	_DraculaDirection = DRACULA_RIGHT_IDLE;

	_enemyInfo.rc = RectMake(_enemyInfo.x, _enemyInfo.y, _enemyInfo.enemyImage->getFrameWidth(), _enemyInfo.enemyImage->getFrameHeight());

	// 변신 전 드라큘라에 대한 키 애니 정의를 내려주자~
	int rightIdle[] = { 11 }; //오른쪽 정지모션
	KEYANIMANAGER->addArrayFrameAnimation("DraculaRightIdle", "Dracula", rightIdle, 1, 6, true);

	int leftIdle[] = { 0 }; //왼쪽 정지모션
	KEYANIMANAGER->addArrayFrameAnimation("DraculaLeftIdle", "Dracula", leftIdle, 1, 6, true);

	int rightBulletFire[] = { 10,9,8,7,6 }; //오른편 불꽃 파이어모션
	KEYANIMANAGER->addArrayFrameAnimation("DraculaRightBulletFire", "Dracula", rightBulletFire, 5, 8, true, cbRightBulletFire, this);

	int leftBulletFire[] = { 1,2,3,4,5 }; //왼편 불꽃 파이어모션
	KEYANIMANAGER->addArrayFrameAnimation("DraculaLeftBulletFire", "Dracula", leftBulletFire, 5, 8, true, cbLeftBulletFire, this);

	int rightBallFire[] = { 18,19,20,21,22 }; //오른편 파이어볼 파이어 모션
	KEYANIMANAGER->addArrayFrameAnimation("DraculaRightBallFire", "Dracula", rightBallFire, 5, 8, false, cbRightBallFire, this);

	int leftBallFire[] = { 12,13,14,15,16 }; //왼편 파이어볼 파이어 모션
	KEYANIMANAGER->addArrayFrameAnimation("DraculaLeftBallFire", "Dracula", leftBallFire, 5, 8, false, cbLeftBallFire, this);

	int rightChange[] = { 35,34,33,32,31,30 }; //오른편 몬스터로 변신 모션
	KEYANIMANAGER->addArrayFrameAnimation("DraculaRightChange", "Dracula", rightChange, 6, 15, true);

	int leftChange[] = { 24,25,26,27,28,29 }; //왼편 몬스터로 변신 모션
	KEYANIMANAGER->addArrayFrameAnimation("DraculaLeftChange", "Dracula", leftChange, 6, 15, true);


	// 변신 후 드라큘라 몬스터에 대한 키 애니 정의를 내려주자~
	int Monster_right[] = { 17,16,15,14,13,12,11,10,9 }; //오른쪽 모션
	KEYANIMANAGER->addArrayFrameAnimation("MonsterStandR", "MonsterDracula", Monster_right, 9, 5, true);

	int Monster_Left[] = { 0,1,2,3,4,5,6,7,8 }; //왼쪽 모션
	KEYANIMANAGER->addArrayFrameAnimation("MonsterStandL", "MonsterDracula", Monster_Left, 9, 5, true);

	int MonsterJump_right[] = { 31, 30, 29, 28, 27}; //오른쪽 점프모션
	KEYANIMANAGER->addArrayFrameAnimation("MonsterJumpR", "MonsterDracula", MonsterJump_right, 5, 5, false);

	int MonsterJump_Left[] = { 18,19,20,21, 22};  //왼쪽 점프모션
	KEYANIMANAGER->addArrayFrameAnimation("MonsterJumpL", "MonsterDracula", MonsterJump_Left, 5, 5, false);

	int MonsterFire_right[] = { 11 }; //오른쪽 파이어
	KEYANIMANAGER->addArrayFrameAnimation("MonsterFireR", "MonsterDracula", MonsterFire_right, 1, 10, false);

	int MonsterFire_left[] = { 2 };  //왼쪽 파이어
	KEYANIMANAGER->addArrayFrameAnimation("MonsterFireL", "MonsterDracula", MonsterFire_left, 1, 10, false);

	int MonsterDead_right[] = { 45 }; //오른쪽 죽는 모션
	KEYANIMANAGER->addArrayFrameAnimation("MonsterDeadR", "MonsterDracula", MonsterDead_right, 1, 10, true);

	int MonsterDead_left[] = { 38 }; //왼쪽 죽는 모션
	KEYANIMANAGER->addArrayFrameAnimation("MonsterDeadL", "MonsterDracula", MonsterDead_left, 1, 10, true);

	int MonsterTurn_right[] = { 54,55,56 }; //오른쪽 전환 모션
	KEYANIMANAGER->addArrayFrameAnimation("MonsterTurnR", "MonsterDracula", MonsterTurn_right, 3, 5, false, cbLeftTurnEnd, this);

	int MonsterTrun_Left[] = { 65,64,63 };  //왼쪽 전환 모션
	KEYANIMANAGER->addArrayFrameAnimation("MonsterTurnL", "MonsterDracula", MonsterTrun_Left, 3, 5, false, cbRightTurnEnd, this);

	_enemyInfo.bossAni = KEYANIMANAGER->findAnimation("MonsterFireR");
	_enemyInfo.bossAni->start();
}

void Dracula::move()
{
	

	//if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	//{
	//	fire();
	//}
}

void Dracula::appear()
{
	if (_DraculaPhase == PHASE1)
	{
		if (Appear == false)
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
						_enemyInfo.bossAni = KEYANIMANAGER->findAnimation("DraculaRightBulletFire");
						_enemyInfo.bossAni->start();
					}
					else if (_bCount >= 3)
					{
						_DraculaDirection = DRACULA_RIGHT_BALLATTK;
						_enemyInfo.bossAni = KEYANIMANAGER->findAnimation("DraculaRightBallFire");
						_enemyInfo.bossAni->start();
					}
				}
				else
				{
					if (_bCount < 3)
					{
						_DraculaDirection = DRACULA_LEFT_BULLETATTK;
						_enemyInfo.bossAni = KEYANIMANAGER->findAnimation("DraculaLeftBulletFire");
						_enemyInfo.bossAni->start();
					}
					else if (_bCount >= 3)
					{
						_DraculaDirection = DRACULA_LEFT_BALLATTK;
						_enemyInfo.bossAni = KEYANIMANAGER->findAnimation("DraculaLeftBallFire");
						_enemyInfo.bossAni->start();
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
		_enemyInfo.rc = RectMake(_enemyInfo.x, _enemyInfo.y, _enemyInfo.enemyImage->getFrameWidth(), _enemyInfo.enemyImage->getFrameHeight());
	}
	else if (_DraculaPhase == PHASE2)
	{
	_enemyInfo.rc = RectMake(_enemyInfo.x, _enemyInfo.y, _enemyInfo.MonsterImage->getFrameWidth(), _enemyInfo.MonsterImage->getFrameHeight());
	}
	
}

void Dracula::fire()
{
	if (!_enemyInfo.fire) return;

	_fireCount += TIMEMANAGER->getElapsedTime();

	if (_frameCount + FRAMECOUNT > GetTickCount())
	{
		_frameCount = GetTickCount();
		_bCount = 0;
	}

	if (_DraculaDirection == DRACULAMONSTER_LEFT_ATTCK || _DraculaDirection == DRACULA_LEFT_BALLATTK || _DraculaDirection == DRACULA_LEFT_BULLETATTK) _isLeft = true;
	else if (_DraculaDirection == DRACULAMONSTER_RIGHT_ATTCK || _DraculaDirection == DRACULA_RIGHT_BALLATTK || _DraculaDirection == DRACULA_RIGHT_BULLETATTK) _isLeft = false;
	
	float fireX;
	/*float fireY;*/
	float fireAngle;

	if (_DraculaPhase == PHASE1)
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

		if (_bCount < 3)
		{
			
	
			_Bullet->fire("DraculaFireBullet", fireX, _enemyInfo.y - 50, fireAngle, 3, _isLeft);
			_Bullet->fire("DraculaFireBullet", fireX, _enemyInfo.y - 20, fireAngle, 3, _isLeft);
			_Bullet->fire("DraculaFireBullet", fireX, _enemyInfo.y + 10, fireAngle, 3, _isLeft);
	
			++_bCount;
		}
		else if (_bCount >= 3)
		{
			_Bullet->fire("DraculaFireBall", _enemyInfo.x + 20, _enemyInfo.y - 40, fireAngle, 3, _isLeft);
			_Bullet->fire("DraculaFireBall", _enemyInfo.x, _enemyInfo.y, fireAngle, 3, _isLeft);
			_bCount = 0;
		}
	
	}
	
	else if (_DraculaPhase == PHASE2 && (_DraculaDirection == DRACULAMONSTER_LEFT_ATTCK || _DraculaDirection == DRACULAMONSTER_RIGHT_ATTCK))
	{
		if (_fireCount > 0.5f)
		{
			if (_bCount == 0)
			{
				if (_DraculaDirection == DRACULAMONSTER_LEFT_ATTCK)
				{
					fireX = _enemyInfo.rc.right - (_enemyInfo.rc.right - _enemyInfo.rc.left) / 2;
					fireAngle = PI + PI / 4;
				}
				else if (_DraculaDirection == DRACULAMONSTER_RIGHT_ATTCK)
				{
					fireX = _enemyInfo.x + _enemyInfo.MonsterImage->getFrameWidth() / 4;
					fireAngle = PI + PI / 2 + PI / 4;
				}

				_Bullet->fire("DraculaMonsterBullet", fireX, _enemyInfo.y + _enemyInfo.MonsterImage->getFrameHeight() / 4, fireAngle, 5, _isLeft);
				_bCount++;
				_fireCount = 0;
			}
		}
		if (_fireCount > 0.5f)
		{
			if (_bCount == 1)
			{
				if (_DraculaDirection == DRACULAMONSTER_LEFT_ATTCK)
				{
					fireX = _enemyInfo.rc.right - (_enemyInfo.rc.right - _enemyInfo.rc.left) / 2;
					fireAngle = PI + PI / 2 - PI / 9;
				}

				else if (_DraculaDirection == DRACULAMONSTER_RIGHT_ATTCK)
				{
					fireX = _enemyInfo.x + _enemyInfo.MonsterImage->getFrameWidth() / 4;
					fireAngle = PI + PI / 2 + PI / 9;
				}

				_Bullet->fire("DraculaMonsterBullet", fireX, _enemyInfo.y + _enemyInfo.MonsterImage->getFrameHeight() / 4, fireAngle, 5, _isLeft);
				_bCount++;
				_fireCount = 0;
			}
		}
		if (_fireCount > 0.5f)
		{
			if (_bCount == 2)
			{
				if (_DraculaDirection == DRACULAMONSTER_LEFT_ATTCK)
				{
					fireX = _enemyInfo.rc.right - (_enemyInfo.rc.right - _enemyInfo.rc.left) / 2;
					fireAngle = PI + PI / 2 - PI / 6;
					_DraculaDirection = DRACULAMONSTER_LEFT_IDLE;
				}
				else if (_DraculaDirection == DRACULAMONSTER_RIGHT_ATTCK)
				{
					fireX = _enemyInfo.x + _enemyInfo.MonsterImage->getFrameWidth() / 4;
					fireAngle = PI + PI / 2 + PI / 6;

					_DraculaDirection = DRACULAMONSTER_RIGHT_IDLE;
				}

				_Bullet->fire("DraculaMonsterBullet", fireX, _enemyInfo.y + _enemyInfo.MonsterImage->getFrameHeight() / 4, fireAngle, 5, _isLeft);
				_bCount = 0;
				_fireCount = 0;
				_enemyInfo.fire = false;

			}
		}
	}
	
}

void Dracula::setDraculaDirection()
{
	//드라큘라의 상태
	switch (_DraculaDirection)
	{
	case DRACULA_RIGHT_IDLE:
		_enemyInfo.bossAni = KEYANIMANAGER->findAnimation("DraculaRightIdle");
		break;

	case DRACULA_LEFT_IDLE:
		_enemyInfo.bossAni = KEYANIMANAGER->findAnimation("DraculaLeftIdle");
		break;

	case DRACULA_RIGHT_BULLETATTK:
		_enemyInfo.bossAni = KEYANIMANAGER->findAnimation("DraculaRightBulletFire");
		if (!_enemyInfo.bossAni->isPlay()) _enemyInfo.bossAni->start();
		break;

	case DRACULA_LEFT_BULLETATTK:
		_enemyInfo.bossAni = KEYANIMANAGER->findAnimation("DraculaLeftBulletFire");
		if (!_enemyInfo.bossAni->isPlay()) _enemyInfo.bossAni->start();
		break;

	case DRACULA_RIGHT_BALLATTK:
		_enemyInfo.bossAni = KEYANIMANAGER->findAnimation("DraculaRightBallFire");
		if (!_enemyInfo.bossAni->isPlay()) _enemyInfo.bossAni->start();
		break;

	case DRACULA_LEFT_BALLATTK:
		_enemyInfo.bossAni = KEYANIMANAGER->findAnimation("DraculaLeftBallFire");
		if (!_enemyInfo.bossAni->isPlay()) _enemyInfo.bossAni->start();
		break;

	case DRACULA_RIGHT_CHANGE:
		_enemyInfo.bossAni = KEYANIMANAGER->findAnimation("DraculaRightChange");
		if (!_enemyInfo.bossAni->isPlay()) _enemyInfo.bossAni->start();
		break;

	case DRACULA_LEFT_CHANGE:
		_enemyInfo.bossAni = KEYANIMANAGER->findAnimation("DraculaLeftChange");
		if (!_enemyInfo.bossAni->isPlay()) _enemyInfo.bossAni->start();
		break;

	case DRACULA_RIGHT_JUMP:
		_enemyInfo.bossAni = KEYANIMANAGER->findAnimation("MonsterJumpR");
		if (!_enemyInfo.bossAni->isPlay()) _enemyInfo.bossAni->start();
		break;

	case DRACULA_LEFT_JUMP:
		_enemyInfo.bossAni = KEYANIMANAGER->findAnimation("MonsterJumpL");
		if (!_enemyInfo.bossAni->isPlay()) _enemyInfo.bossAni->start();
		break;

	case DRACULA_RIGHT_DEAD:
		_enemyInfo.bossAni = KEYANIMANAGER->findAnimation("MonsterDeadR");
		if (!_enemyInfo.bossAni->isPlay()) _enemyInfo.bossAni->start();
		break;
	
	case DRACULA_LEFT_DEAD:
		_enemyInfo.bossAni = KEYANIMANAGER->findAnimation("MonsterDeadL");
		if (!_enemyInfo.bossAni->isPlay()) _enemyInfo.bossAni->start();
		break;

	case DRACULA_RIGHT_TURN:
		_enemyInfo.bossAni = KEYANIMANAGER->findAnimation("MonsterTurnR");
		if (!_enemyInfo.bossAni->isPlay()) _enemyInfo.bossAni->start();
		break;

	case DRACULA_LEFT_TURN:
		_enemyInfo.bossAni = KEYANIMANAGER->findAnimation("MonsterTurnL");
		if (!_enemyInfo.bossAni->isPlay()) _enemyInfo.bossAni->start();
		break;

	case DRACULAMONSTER_RIGHT_IDLE:
		_enemyInfo.bossAni = KEYANIMANAGER->findAnimation("MonsterStandR");

		if (_Playerrc.right < _enemyInfo.x)
		{
			_DraculaDirection = DRACULA_LEFT_TURN;
		}

		if (_patternTime > 3.0f)
		{
			_patternRan = RND->getFromIntTo(0, 3);
			patternSelect();
			_patternTime = 0;
		}

		_patternTime += TIMEMANAGER->getElapsedTime();
		if (!_enemyInfo.bossAni->isPlay()) _enemyInfo.bossAni->start();
		break;

	case DRACULAMONSTER_LEFT_IDLE:
		_enemyInfo.bossAni = KEYANIMANAGER->findAnimation("MonsterStandL");
		if (_Playerrc.left > _enemyInfo.x)
		{
			_DraculaDirection = DRACULA_RIGHT_TURN;
		}
		if (_patternTime > 3.0f)
		{
			_patternRan = RND->getFromIntTo(0, 3);
			patternSelect();
			_patternTime = 0;
		}

		_patternTime += TIMEMANAGER->getElapsedTime();
		if (!_enemyInfo.bossAni->isPlay()) _enemyInfo.bossAni->start();
		break;

	case DRACULAMONSTER_RIGHT_ATTCK:
		_enemyInfo.bossAni = KEYANIMANAGER->findAnimation("MonsterFireR");
		
		_enemyInfo.fire = true;
		

		if (!_enemyInfo.bossAni->isPlay()) _enemyInfo.bossAni->start();
		break;

	case DRACULAMONSTER_LEFT_ATTCK:
		_enemyInfo.bossAni = KEYANIMANAGER->findAnimation("MonsterFireL");    

		_enemyInfo.fire = true;
		fire();

		if (!_enemyInfo.bossAni->isPlay()) _enemyInfo.bossAni->start();
		break;

	case DRACULAMONSTER_RIGHT_JUMP:
		_enemyInfo.bossAni = KEYANIMANAGER->findAnimation("MonsterJumpR");
		_enemyInfo.x += 0.9;
		_enemyInfo.y -= _gravity;
		_gravity -= 0.04;

		if (!_enemyInfo.bossAni->isPlay()) _enemyInfo.bossAni->start();
		break;

	case DRACULAMONSTER_LEFT_JUMP:
		_enemyInfo.bossAni = KEYANIMANAGER->findAnimation("MonsterJumpL");

		_enemyInfo.x -= 0.9;
		_enemyInfo.y -= _gravity;
		_gravity -= 0.04;

		if (!_enemyInfo.bossAni->isPlay()) _enemyInfo.bossAni->start();
		break;

	case DRACULAMONSTER_RIGHT_SUPERJUMP:
		_enemyInfo.bossAni = KEYANIMANAGER->findAnimation("MonsterJumpR");

		_enemyInfo.x += 0.9;
		_enemyInfo.y -= _gravity * 1.5;
		_gravity -= 0.04;

		if (!_enemyInfo.bossAni->isPlay()) _enemyInfo.bossAni->start();
		break;

	case DRACULAMONSTER_LEFT_SUPERJUMP:
		_enemyInfo.bossAni = KEYANIMANAGER->findAnimation("MonsterJumpL");

		_enemyInfo.x += 0.9;
		_enemyInfo.y -= _gravity * 1.5;
		_gravity -= 0.04;

		if (!_enemyInfo.bossAni->isPlay()) _enemyInfo.bossAni->start();
		break;

	}

	if (_saveY < _enemyInfo.y)
	{
		_gravity = GRAVITY;

		if (_DraculaDirection == DRACULAMONSTER_RIGHT_JUMP || _DraculaDirection == DRACULAMONSTER_RIGHT_SUPERJUMP)
		{
			_DraculaDirection = DRACULAMONSTER_RIGHT_IDLE;
		}
		
		
		if (_DraculaDirection == DRACULAMONSTER_LEFT_JUMP || _DraculaDirection == DRACULAMONSTER_LEFT_SUPERJUMP)
		{
			_DraculaDirection = DRACULAMONSTER_LEFT_IDLE;
		}

		_enemyInfo.y = _saveY;
	}

}

void Dracula::setDraculaPhase()
{
	if (_currentHP <= 1000 && _currentHP > 500)
	{
		_DraculaPhase = PHASE1;


	}

	if (_currentHP <= 500)
	{
		if (_isLeft)
		{
			_DraculaDirection = DRACULA_LEFT_CHANGE;
		}
		else
		{
			_DraculaDirection = DRACULA_RIGHT_CHANGE;
		}
		_DraculaPhase = PHASE2;

	}

}

void Dracula::cbRightBulletFire(void* obj)
{
	Dracula* dr = (Dracula*)obj;

	dr->setDraculaDirection(DRACULA_RIGHT_IDLE);
	dr->_enemyInfo.bossAni = KEYANIMANAGER->findAnimation("DraculaRightIdle");
	dr->_enemyInfo.bossAni->start();
	dr->fire();
}

void Dracula::cbLeftBulletFire(void* obj)
{
	Dracula* dr = (Dracula*)obj;

	dr->setDraculaDirection(DRACULA_LEFT_IDLE);
	dr->_enemyInfo.bossAni = KEYANIMANAGER->findAnimation("DraculaLeftIdle");
	dr->_enemyInfo.bossAni->start();
	dr->fire();
}

void Dracula::cbRightBallFire(void* obj)
{
	Dracula* dr = (Dracula*)obj;

	dr->setDraculaDirection(DRACULA_RIGHT_IDLE);
	dr->_enemyInfo.bossAni = KEYANIMANAGER->findAnimation("DraculaRightIdle");
	dr->_enemyInfo.bossAni->start();

}
	 
void Dracula::cbLeftBallFire(void* obj)
{
	Dracula* dr = (Dracula*)obj;

	dr->setDraculaDirection(DRACULA_LEFT_IDLE);
	dr->_enemyInfo.bossAni = KEYANIMANAGER->findAnimation("DraculaRightIdle");
	dr->_enemyInfo.bossAni->start();
}

void Dracula::cbRightMonsterBulletFire(void* obj)
{
	Dracula* dr = (Dracula*)obj;

	dr->setDraculaDirection(DRACULAMONSTER_RIGHT_IDLE);
	dr->setPattern(0);
	dr->_enemyInfo.bossAni = KEYANIMANAGER->findAnimation("MonsterStandR");
	dr->_enemyInfo.bossAni->start();
}

void Dracula::cbLeftMonsterBulletFire(void* obj)
{
	Dracula* dr = (Dracula*)obj;

	dr->setDraculaDirection(DRACULAMONSTER_LEFT_IDLE);
	dr->setPattern(0);
	dr->_enemyInfo.bossAni = KEYANIMANAGER->findAnimation("MonsterStandL");
	dr->_enemyInfo.bossAni->start();
}

void Dracula::cbRightTurnEnd(void* obj)
{
	Dracula* dr = (Dracula*)obj;

	dr->setDraculaDirection(DRACULAMONSTER_LEFT_IDLE);
	dr->_enemyInfo.bossAni = KEYANIMANAGER->findAnimation("MonsterStandL");
	dr->_enemyInfo.bossAni->start();
}

void Dracula::cbLeftTurnEnd(void* obj)
{
	Dracula* dr = (Dracula*)obj;

	dr->setDraculaDirection(DRACULAMONSTER_RIGHT_IDLE);
	dr->_enemyInfo.bossAni = KEYANIMANAGER->findAnimation("MonsterStandR");
	dr->_enemyInfo.bossAni->start();
}

void Dracula::patternSelect(void)
{
	switch (_patternRan)
	{
	case 0:
		if (_Playerrc.right < _enemyInfo.x && _DraculaDirection == DRACULAMONSTER_RIGHT_IDLE)
		{
			_DraculaDirection = DRACULA_LEFT_TURN;
		}

		if (_Playerrc.left > _enemyInfo.x && _DraculaDirection == DRACULAMONSTER_LEFT_IDLE)
		{
			_DraculaDirection = DRACULA_RIGHT_TURN;
		}

		break;

	case 1:
		if (_DraculaDirection == DRACULAMONSTER_LEFT_IDLE)
		{
			_DraculaDirection = DRACULAMONSTER_LEFT_ATTCK;
		}
		if (_DraculaDirection == DRACULAMONSTER_RIGHT_IDLE)
		{
			_DraculaDirection = DRACULAMONSTER_RIGHT_ATTCK;
		}

		break;

	case 2:
		if (_DraculaDirection == DRACULAMONSTER_LEFT_IDLE)
		{
			_DraculaDirection = DRACULAMONSTER_LEFT_JUMP;
		}

		if (_DraculaDirection == DRACULAMONSTER_RIGHT_IDLE)
		{
			_DraculaDirection = DRACULAMONSTER_RIGHT_JUMP;
		}

		break;

	case 3:
		if (_DraculaDirection == DRACULAMONSTER_LEFT_IDLE)
		{
			_DraculaDirection = DRACULAMONSTER_LEFT_SUPERJUMP;
		}

		if (_DraculaDirection == DRACULAMONSTER_RIGHT_IDLE)
		{
			_DraculaDirection = DRACULAMONSTER_RIGHT_SUPERJUMP;
		}
		break;
	}
}