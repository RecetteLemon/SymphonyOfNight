#include "stdafx.h"
#include "hosuk.h"


hosuk::hosuk()
{
}


hosuk::~hosuk()
{
}


HRESULT hosuk::init(const char* imageName, float x, float y, float moveRange)
{
	enemy::init(imageName, x, y, 0);
	imageInit();
	
	_enemyInfo.atk = 10;
	_enemyInfo.die = false;
	_enemyInfo.attack = false;
	_enemyInfo.hp = 30;
	_enemyInfo.speed = 1.0f;


	_enemyInfo.attackTime = _count = 0;

	//실험용
	//playerX = WINSIZEX / 2;
	//playerY = WINSIZEY / 2;
	
	
	
	

	return S_OK;
}
void hosuk::imageInit()
{
	//적애니메이션을 초기화해줌
	for (int i = 0; i < ENEMY_ANI_END; ++i)
	{
		_enemyInfo.enemyAni[i] = new animation;
		_enemyInfo.enemyAni[i]->init(_enemyInfo.enemyImage->getWidth(), _enemyInfo.enemyImage->getHeight(),
			_enemyInfo.enemyImage->getFrameWidth(), _enemyInfo.enemyImage->getFrameHeight());
	}

	//애니메이션배열과 프레임을 저장시켜줌
	int arrLeftMove[] = { 1,2,3,4,5 };
	_enemyInfo.enemyAni[ENEMY_LEFT_MOVEANI]->setPlayFrame(arrLeftMove, 5, true);
	_enemyInfo.enemyAni[ENEMY_LEFT_MOVEANI]->setFPS(6);

	int arrLeftAttack[] = { 6,7,8 };
	_enemyInfo.enemyAni[ENEMY_LEFT_ATTACKANI]->setPlayFrame(arrLeftAttack, 3, false);
	_enemyInfo.enemyAni[ENEMY_LEFT_ATTACKANI]->setFPS(10);

	int arrLeftStay[] = { 1 };
	_enemyInfo.enemyAni[ENEMY_LEFT_STAYANI]->setPlayFrame(arrLeftStay, 1, false);


	int arrRightMove[] = { 16,15,14,13,12 };
	_enemyInfo.enemyAni[ENEMY_RIGHT_MOVEANI]->setPlayFrame(arrRightMove, 5, true);
	_enemyInfo.enemyAni[ENEMY_RIGHT_MOVEANI]->setFPS(6);
	
	int arrRightAttack[] = { 11,10,9 };
	_enemyInfo.enemyAni[ENEMY_RIGHT_ATTACKANI]->setPlayFrame(arrRightAttack, 3, false);
	_enemyInfo.enemyAni[ENEMY_RIGHT_ATTACKANI]->setFPS(10);

	int arrRightStay = { 17 };
	_enemyInfo.enemyAni[ENEMY_RIGHT_STAYANI]->setPlayFrame(arrRightStay, 1, false);

	//처음 호석이의 상태
	_enemyInfo.stat = ENEMY_LEFT_MOVE;
	//호석이 상태별 호석이의 좌우 상태
	/*switch (_enemyInfo.stat)
	{
		case ENEMY_LEFT_STAY: case ENEMY_LEFT_MOVE: case ENEMY_LEFT_DIE: case ENEMY_LEFT_ATTACK:
			_direction = ENEMY_LEFT;
		break;
		case ENEMY_RIGHT_STAY: case ENEMY_RIGHT_MOVE: case ENEMY_RIGHT_DIE: case ENEMY_RIGHT_ATTACK:
			_direction = ENEMY_RIGHT;
		break;
	}*/


	//실험용
	
}
void hosuk::release(void)
{
	enemy::release();

}
void hosuk::update(void)
{
	enemy::update();
	move();


	//호석이의 렉트
	_enemyInfo.rc = RectMakeCenter(_enemyInfo.x, _enemyInfo.y,
		_enemyInfo.enemyImage->getFrameWidth(), _enemyInfo.enemyImage->getFrameHeight());
	
	

	
}
void hosuk::render(void)
{
	
	//실험용 호석이 사각형
	Rectangle(getMemDC(), _enemyInfo.rc.left, _enemyInfo.rc.top, _enemyInfo.rc.right, _enemyInfo.rc.bottom);
	//Rectangle(getMemDC(), _enemyInfo.playerRc.left, _enemyInfo.playerRc.top, _enemyInfo.playerRc.right, _enemyInfo.playerRc.bottom);
	Rectangle(getMemDC(), _enemyInfo.damageRc.left, _enemyInfo.damageRc.top, _enemyInfo.damageRc.right, _enemyInfo.damageRc.bottom);

	//호석이 상태별 애니메이션을 실행시킴
	switch (_enemyInfo.stat)	
	{
		case ENEMY_LEFT_STAY :
			_enemyInfo.enemyImage->aniRender(getMemDC(), _enemyInfo.rc.left, _enemyInfo.rc.top
				, _enemyInfo.enemyAni[ENEMY_LEFT_STAYANI]);
		break;

		case ENEMY_RIGHT_STAY:
			_enemyInfo.enemyImage->aniRender(getMemDC(), _enemyInfo.rc.left, _enemyInfo.rc.top
				, _enemyInfo.enemyAni[ENEMY_RIGHT_STAYANI]);
		break;

		case ENEMY_LEFT_MOVE:
			_enemyInfo.enemyImage->aniRender(getMemDC(), _enemyInfo.rc.left, _enemyInfo.rc.top
				, _enemyInfo.enemyAni[ENEMY_LEFT_MOVEANI]);
		break;

		case ENEMY_RIGHT_MOVE:
			_enemyInfo.enemyImage->aniRender(getMemDC(), _enemyInfo.rc.left, _enemyInfo.rc.top
				, _enemyInfo.enemyAni[ENEMY_RIGHT_MOVEANI]);
		break;
		case ENEMY_LEFT_ATTACK:
			_enemyInfo.enemyImage->aniRender(getMemDC(), _enemyInfo.rc.left, _enemyInfo.rc.top
				, _enemyInfo.enemyAni[ENEMY_LEFT_ATTACKANI]);
		break;

		case ENEMY_RIGHT_ATTACK:
			_enemyInfo.enemyImage->aniRender(getMemDC(), _enemyInfo.rc.left, _enemyInfo.rc.top
				, _enemyInfo.enemyAni[ENEMY_RIGHT_ATTACKANI]);
		break;
	}
}


void hosuk::move()
{
	//플레이어 위치값에따라 변하는 호석이의 상태값
	if (_enemyInfo.x > playerX) _enemyInfo.stat = ENEMY_LEFT_MOVE; // 호석이 왼쪽에 플레이어가있으면 호석이는 왼쪽으로 달려감
	else //호석이 오른쪽에 플레이어가있으면 호석이는 오른쪽으로 달려감
	{
		_enemyInfo.stat = ENEMY_RIGHT_MOVE;	//호석이 상태값을 바꿔줌
		if (!_enemyInfo.enemyAni[ENEMY_RIGHT_MOVEANI]->isPlay())_enemyInfo.enemyAni[ENEMY_RIGHT_MOVEANI]->start();//호석이 왼쪽무브애니가 실행중이아니면 애니메이션 스타트!
	}

	float distance = getDistance(_enemyInfo.x, _enemyInfo.y, playerX, playerY); // 호석이의 중점값과 플레이어의 중점값을 구해줌
	
	//호석이 왼쪽에 적과의 거리가 50보다작으면 호석이의 상태는 왼쪽공격으로 바뀜
	
	if (!_enemyInfo.attack)
	{
		_count += TIMEMANAGER->getElapsedTime();

		if (_count >= 1.0f) _enemyInfo.attack = true;
	}

	if (_enemyInfo.x > playerX && distance <= 80)
	{
		_enemyInfo.attackTime += TIMEMANAGER->getElapsedTime();
		if (_enemyInfo.attackTime >= 2.0f && _enemyInfo.attack == true)
		{
			_enemyInfo.stat = ENEMY_LEFT_ATTACK;
			if (!_enemyInfo.enemyAni[ENEMY_LEFT_ATTACKANI]->isPlay())_enemyInfo.enemyAni[ENEMY_LEFT_ATTACKANI]->start();
		}
		else _enemyInfo.stat = ENEMY_LEFT_STAY;
	}
	else if (_enemyInfo.x > playerX&& distance >= 600)
	{
		_enemyInfo.stat = ENEMY_LEFT_STAY;
	}
	
	if (_enemyInfo.x < playerX && distance <= 40) // 플레이어가 호석이 오른쪽에있고 거리가 40 일때 
	{
		_enemyInfo.attackTime += TIMEMANAGER->getElapsedTime();  //호석이의 공격딜레이가 + 해줌
		if (_enemyInfo.attackTime >= 2.0f && _enemyInfo.attack == true) // 호석이의 공격딜레이가 2초이상이고 호석이 공격이 트루일때.
		{
			_enemyInfo.stat = ENEMY_RIGHT_ATTACK; //호석이 상태를 오른쪽 공격으로 바꿔줌
			if (!_enemyInfo.enemyAni[ENEMY_RIGHT_ATTACKANI]->isPlay())_enemyInfo.enemyAni[ENEMY_RIGHT_ATTACKANI]->start(); 
			// 호석이 공격애니가 실행이 아닐때 애니메이션을 실행시켜줌
		}
		else _enemyInfo.stat = ENEMY_RIGHT_STAY; // 공격딜레이 조건이 불충족일때는 호석이는 오른쪽을바라보고 서있음
	}
	else if (_enemyInfo.x < playerX && distance >= 600)
	{
		_enemyInfo.stat = ENEMY_RIGHT_STAY;
	}

	//호석이 상태별 움직임,애니메이션 플레이
	switch (_enemyInfo.stat)
	{
		case ENEMY_LEFT_MOVE://호석이의 상태값이 왼쪽움직이면.
			_enemyInfo.x -= _enemyInfo.speed; //호석이는 왼쪽으로 움직임
			_enemyInfo.enemyAni[ENEMY_LEFT_MOVEANI]->frameUpdate(TIMEMANAGER->getElapsedTime()); //왼쪽움직임애니메이션 프레임업데이트를 해줌
			if (!_enemyInfo.enemyAni[ENEMY_LEFT_MOVEANI]->isPlay())	_enemyInfo.enemyAni[ENEMY_LEFT_MOVEANI]->start(); //만약 실행중이아니면 실행시켜줌

			_enemyInfo.damageRc = RectMake(0, 0, 0, 0); // 호석이가 공격중이 아닐떄는 호석이혓바닥렉트는 없음
		break;
		case ENEMY_RIGHT_MOVE:
			_enemyInfo.x += _enemyInfo.speed;
			_enemyInfo.enemyAni[ENEMY_RIGHT_MOVEANI]->frameUpdate(TIMEMANAGER->getElapsedTime());
			if (!_enemyInfo.enemyAni[ENEMY_RIGHT_MOVEANI]->isPlay())_enemyInfo.enemyAni[ENEMY_RIGHT_MOVEANI]->start();

			_enemyInfo.damageRc = RectMake(0, 0, 0, 0);
		break;
		case ENEMY_LEFT_ATTACK:
			_enemyInfo.enemyAni[ENEMY_LEFT_ATTACKANI]->frameUpdate(TIMEMANAGER->getElapsedTime());
			if (!_enemyInfo.enemyAni[ENEMY_LEFT_ATTACKANI]->isPlay()) _enemyInfo.attackTime = _count = 0; 

		
			if (_enemyInfo.enemyAni[ENEMY_LEFT_ATTACKANI]->isPlay()) //호석이 공격애니가 실행중일떄 혓바닥 렉트가 나옴
			{
				_enemyInfo.damageRc = RectMake(_enemyInfo.x - _enemyInfo.enemyImage->getFrameWidth() / 2,
					_enemyInfo.y + 5, 30, 5);
			}
			else  _enemyInfo.damageRc = RectMake(0, 0, 0, 0); //호석이 공격애니가 끝나면 혓바닥렉트는 사라짐

		break;
		case ENEMY_RIGHT_ATTACK:
			_enemyInfo.enemyAni[ENEMY_RIGHT_ATTACKANI]->frameUpdate(TIMEMANAGER->getElapsedTime());
			if (!_enemyInfo.enemyAni[ENEMY_RIGHT_ATTACKANI]->isPlay()) _enemyInfo.attackTime = _count = 0;
			
			//호석이가 공격중일때 호석이 혓바닥렉트
			if (_enemyInfo.enemyAni[ENEMY_RIGHT_ATTACKANI]->isPlay())
			{
				_enemyInfo.damageRc = RectMake(_enemyInfo.x + _enemyInfo.enemyImage->getFrameWidth() / 2 - 30,
					_enemyInfo.y + 5, 30, 5);
			}
			else _enemyInfo.damageRc = RectMake(0, 0, 0, 0);
		break;
		default:

		break;
	}	
}

void hosuk::setHosukHP(int HP) 
{
	_enemyInfo.hp -= HP;
	
}