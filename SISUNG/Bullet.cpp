#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}

HRESULT Bullet::init(const char* imageName)
{
	_imageName = imageName;

	return S_OK;

}
void Bullet::release(void)
{

}
void Bullet::update(void)
{
	frameWork();
	move();
}
void Bullet::render(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;
		_viBullet->BulletImage->frameRender(getMemDC(), _viBullet->x, _viBullet->y, _viBullet->frameX, _viBullet->frameY);// , _viBullet->_DraculaBullet);

	}
}
void Bullet::fire(const char* imageName, float x, float y, float angle, float speed, bool isLeft)
{
	tagBullet Bullet;
	
	ZeroMemory(&Bullet, sizeof(tagBullet));
	
	Bullet.BulletImage = IMAGEMANAGER->findImage(imageName);
	//Bullet.angle = angle;
	
	if (isLeft)
	{
		Bullet.frameY = 1;
		Bullet.BulletImage->getMaxFrameX() - 1;
	}
	else
	{
		Bullet.frameY = 0;
	}
	Bullet.angle = angle;
	Bullet.speed = speed;
	Bullet.x = Bullet.fireX = x;
	Bullet.y = Bullet.fireY = y;
	
	Bullet.fire = true;
	Bullet.frameCount = 0;
	Bullet.rc = RectMakeCenter(Bullet.x, Bullet.y, Bullet.BulletImage->getFrameWidth(),
		Bullet.BulletImage->getFrameHeight());

	_vBullet.push_back(Bullet);

}
void Bullet::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();_viBullet++)
	{
		if (!_viBullet->fire) continue;
		
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += (-sinf(_viBullet->angle)) * _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->BulletImage->getFrameWidth(),
			_viBullet->BulletImage->getFrameHeight());
	}
}

void Bullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}

void Bullet::frameWork(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); _viBullet++)
	{
		if (!_viBullet->fire) continue;
		if (_viBullet->frameCount + BULLETFRAMECOUNT < GetTickCount())
		{
			_viBullet->frameCount = GetTickCount();
			if (_viBullet->frameY == 0)
			{
				++_viBullet->frameX;
				if (_viBullet->frameX > _viBullet->BulletImage->getMaxFrameX()) _viBullet->frameX = 0;
			}
			else if (_viBullet->frameY == 1)
			{
				--_viBullet->frameX;
				if (_viBullet->frameX < 0) _viBullet->frameX = _viBullet->BulletImage->getMaxFrameX() - 1;
			}
		}
		
		//_viBullet->frameCount += TIMEMANAGER->getElapsedTime();

		/*if (_viBullet->frameCount > 0.5f)
		{
			if (_viBullet->BulletImage->getFrameY() == 0)
			{
				if (_viBullet->BulletImage->getFrameX() >= _viBullet->BulletImage->getMaxFrameX()) _viBullet->BulletImage->setFrameX(0);
				_viBullet->BulletImage->setFrameX(_viBullet->BulletImage->getFrameX() + 1);
			}
			else
			{
				if (_viBullet->BulletImage->getFrameX() < 0) _viBullet->BulletImage->setFrameX(_viBullet->BulletImage->getMaxFrameX());
				_viBullet->BulletImage->setFrameX(_viBullet->BulletImage->getFrameX() - 1);
			}
			_viBullet->frameCount = 0;
		}*/
	}
}
