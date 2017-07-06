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
	//_enemyInfo.enemyImage = new image;
	_enemyInfo.enemyImage = IMAGEMANAGER->findImage(imageName);
	_enemyInfo.x = x;
	_enemyInfo.y = y;
	
	//						���� ��ġ���� �̹����� ���� ����ũ�⸸ŭ ��Ʈ ����
	_enemyInfo.rc = RectMake(_enemyInfo.x, _enemyInfo.y, 
		_enemyInfo.enemyImage->getFrameWidth(),
		_enemyInfo.enemyImage->getFrameHeight());

	return S_OK;
}

void enemy::release(void)
{
	for (int i = 0; i < ENEMY_ANI_END; i++)
	{
		SAFE_RELEASE(_enemyInfo.enemyAni[i]);
		SAFE_DELETE(_enemyInfo.enemyAni[i]);
	}

	SAFE_RELEASE(_enemyInfo.enemyImage);
	SAFE_DELETE(_enemyInfo.enemyImage);

	
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
	//_enemyInfo.enemyImage->aniRender(getMemDC(), _enemyInfo.x, _enemyInfo.y, _enemyInfo.enemyAni);
}

void enemy::getPlayerRect(RECT playerRc)
{
	_enemyInfo.playerRc = playerRc;
}

void enemy::move(){}
void enemy::imageInit() {}