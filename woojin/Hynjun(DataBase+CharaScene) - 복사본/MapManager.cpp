#include "stdafx.h"
#include "MapManager.h"

MapManager::MapManager()
	:_fieldImage(NULL), _player(NULL), _rc({0, 0, 0, 0})
{
}


MapManager::~MapManager()
{
}

HRESULT MapManager::init(image* img, player* player)
{
	_fieldImage = img;
	_player = player;

	return S_OK;
}

void MapManager::release()
{
}

void MapManager::update()
{
	_rc = RectMakeCenter(_player->getPlayerPosX(), _player->getPlayerPosY(), WINSIZEX, WINSIZEY);

	if (_rc.left < 0)
	{
		_rc.right += -_rc.left;
		_rc.left = 0;
	}
	if (_rc.right > _fieldImage->getWidth())
	{
		_rc.left -= _rc.right - _fieldImage->getWidth();
		_rc.right = _fieldImage->getWidth();
	}
	if (_rc.top < 0)
	{
		_rc.bottom += _rc.top;
		_rc.top = 0;
	}
	if (_rc.bottom > _fieldImage->getHeight())
	{
		_rc.top -= _rc.bottom - _fieldImage->getHeight();
		_rc.bottom = _fieldImage->getHeight();
	}
}
void MapManager::render()
{
	_fieldImage->render(getMemDC(), 0, 0, _rc.left, _rc.top, WINSIZEX, WINSIZEY);
}

void MapManager::setPosY(float y)
{
	_rc.top = y;
	_rc.bottom = _rc.top - WINSIZEY;

}