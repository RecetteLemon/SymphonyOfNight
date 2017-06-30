#include "stdafx.h"
#include "enemy.h"


enemy::enemy()
{
}


enemy::~enemy()
{

}

HRESULT enemy::init(const char* imageName, float x, float y)
{
	_enemyInfo.enemyImage = new image;
	_enemyInfo.enemyImage = IMAGEMANAGER->findImage(imageName);
	_enemyInfo.x = x;
	_enemyInfo.y = y;
	
	//						적의 위치에서 이미지의 가로 세로크기만큼 렉트 생성
	_enemyInfo.rc = RectMake(_enemyInfo.x, _enemyInfo.y, 
		_enemyInfo.enemyImage->getFrameWidth(),
		_enemyInfo.enemyImage->getFrameHeight());

	return S_OK;
}

void enemy::release(void)
{

}

void enemy::update(void)
{
	if (_enemyInfo.hp < 0) _enemyInfo.die = true;
}

void enemy::render(void)
{
	//_enemyInfo.enemyImage->aniRender(getMemDC(), _enemyInfo.x, _enemyInfo.y, _enemyInfo.enemyAni);
}