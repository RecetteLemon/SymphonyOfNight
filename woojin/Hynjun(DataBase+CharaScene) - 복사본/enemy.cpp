#include "stdafx.h"
#include "enemy.h"


enemy::enemy()
{
}


enemy::~enemy()
{

}

HRESULT enemy::init(const char* imageName, float x, float y, float moveRange)
{
	//_enemyInfo.enemyImage = new image;
	_enemyInfo.enemyImage = IMAGEMANAGER->findImage(imageName);
	
	_enemyInfo.x = x;
	_enemyInfo.y = y;
	_enemyInfo.moveRange = moveRange;
	
	//						적의 위치에서 이미지의 가로 세로크기만큼 렉트 생성
	_enemyInfo.rc = RectMake(_enemyInfo.x, _enemyInfo.y,
		_enemyInfo.enemyImage->getFrameWidth(),
		_enemyInfo.enemyImage->getFrameHeight());


	return S_OK;
}

void enemy::release(void)
{

	_enemyInfo.enemyImage->release();
	_enemyInfo.enemyImage = NULL;

	for (int i = 0; i < ENEMY_ANI_END; i++)
	{
		SAFE_RELEASE(_enemyInfo.enemyAni[i]);
		SAFE_DELETE(_enemyInfo.enemyAni[i]);
		
	}

}

void enemy::update(void)
{
	if (_enemyInfo.hp < 0) _enemyInfo.die = true;

	_enemyInfo.rc = RectMake(_enemyInfo.x, _enemyInfo.y,
		_enemyInfo.enemyImage->getFrameWidth(),
		_enemyInfo.enemyImage->getFrameHeight());
	
}

void enemy::render(void)
{
	//switch (_enemyInfo.stat)
	//{
	//	case ENEMY_LEFT_MOVE:
	//		_enemyInfo.enemyImage->aniRender(getMemDC(), _enemyInfo.x, _enemyInfo.y, _enemyInfo.enemyAni[ENEMY_LEFT_MOVEANI]);
	//	
	//		break;
	//	
	//	case ENEMY_RIGHT_MOVE:
	//		_enemyInfo.enemyImage->aniRender(getMemDC(), _enemyInfo.x, _enemyInfo.y, _enemyInfo.enemyAni[ENEMY_RIGHT_MOVEANI]);
	//	
	//		break;
	//}
}

void enemy::getPlayerRect(RECT playerRc)
{
	_enemyInfo.playerRc = playerRc;
}