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

	_UI = new UI;
	_UI->init(0, 0, 102, 28, "앞게이지2", "뒷게이지", "하트");

	return S_OK;
}

void MapManager::release()
{
	SAFE_DELETE(_UI);
}

void MapManager::update()
{
	_UI->update();

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
	_UI->render("뒷게이지", "앞게이지2", "하트");
}

void MapManager::setPosY(float y)
{
	_rc.top = y;
	_rc.bottom = _rc.top - WINSIZEY;
}