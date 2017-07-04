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

	// 저장할 Y값 초기화
	_saveY = 0;

	// 움직일 범위 설정
	_waveRange = WINSIZEY / 5;




	return S_OK;
}

void bat::release()
{
	_enemyInfo.enemyImage->release();
}

void bat::update()
{
	// 충돌 판정
	RECT temp;
	if (IntersectRect(&temp, &_enemyInfo.playerRc, &_comeRange))
	{
		_move = true;
	}



	// 움직임(패턴) 
	move();
	// 움직이지 않을때만 판정범위를 만들어 낸다.
	if (!_move)
	{
		_comeRange = RectMakeCenter(_enemyInfo.x + _enemyInfo.enemyImage->getFrameWidth() / 2, 
			_enemyInfo.y + _enemyInfo.enemyImage->getFrameHeight() / 2,
			100, 100);
	}
	// 만약 움직이면 범위는 0으로 초기화
	else
	{
		_comeRange = RectMake(0, 0, 0, 0);
	}

	// 이 박쥐의 렉트값
	_enemyInfo.rc = RectMake(_enemyInfo.x, _enemyInfo.y,
		_enemyInfo.enemyImage->getFrameWidth(),
		_enemyInfo.enemyImage->getFrameHeight());
}

void bat::render()
{
	// 그려주는거
	// 상태값에 따른 행동
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

		// 죽었을때 이미지를 지운다
	case ENEMY_LEFT_DIE:
		release();
		break;

	case ENEMY_RIGHT_DIE:
		release();
		break;
	}
}

// 이미지 초기화
void bat::imageInit()
{
	for (int i = 0; i < ENEMY_ANI_AND; i++)
	{
		_enemyInfo.enemyAni[i] = new animation;
		_enemyInfo.enemyAni[i]->init(_enemyInfo.enemyImage->getWidth(), _enemyInfo.enemyImage->getHeight()
			, _enemyInfo.enemyImage->getFrameWidth(), _enemyInfo.enemyImage->getFrameHeight());
	}
	// 애니메이션 초기화들 왼쪽 움직임과 오른쪽 움직임, 왼쪽 가만히 있는거랑 오른쪽 가만히 있는거
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

// 움직임(패턴)
void bat::move()
{
	// 플레이어가 박쥐의 판정 렉트에 다았을때 그때 움직인다.
	if (_move)
	{
		// 플레이어의 Y좌표에 다가가지 못했다면 
		if (!_comePlayerY)
		{
			// 박쥐의 y좌표를 더해준다.
			_enemyInfo.y += _enemyInfo.speed;
			// 플레이어가 이 적의 왼쪽에 있을 경우
			if (_enemyInfo.playerRc.left <= _enemyInfo.x)
			{
				_moveLeft = true;
				_enemyInfo.stat = ENEMY_LEFT_MOVE;
			}

			// 오른쪽
			if (_enemyInfo.playerRc.right > _enemyInfo.x)
			{
				_moveLeft = false;
				_enemyInfo.stat = ENEMY_RIGHT_MOVE;
			}

			// 적이 플레이어 위치에 왔을때
			if (_enemyInfo.y >= _enemyInfo.playerRc.top)
			{
				// 저장할 Y좌표
				_saveY = _enemyInfo.y;
				_comePlayerY = true;

			}
		}
		// 플레이어의 y좌표 판정
		if (_comePlayerY)
		{
			// 여기는 플레이어 위치를 받아서 왼쪽 오른쪽으로 이동한다
			// 여기서 왼쪽 오른쪽이 결정되면 애니메이션 상태값도 변경

			// 물결로 움직임
			if (_upDown)
			{
				_enemyInfo.y += 1.5f;
			}
			else
			{
				_enemyInfo.y -= 1.5f;
			}

			// 만약에 현재 적의 y좌표에서 웨이브범위만큼 더한게 시작 y좌표보다 작아지면 다시 위로 올라간다
			if (_enemyInfo.y + _waveRange / 2 < _saveY)
			{
				_upDown = true;
			}

			// 만약에 현재 적의 y좌표에서 웨이브범위를 뺀게 시작 y좌표보다 커지면 다시 아래로 내려간다
			if (_enemyInfo.y - _waveRange / 2 > _saveY)
			{
				_upDown = false;
			}
		}
	}

	// 상태값에 따른 행동
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

		// 죽었을때 이미지를 지운다
		case ENEMY_LEFT_DIE:

			release();
			break;

		case ENEMY_RIGHT_DIE:
			release();
			break;
	}	
}