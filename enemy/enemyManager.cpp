#include "stdafx.h"
#include "enemyManager.h"


enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{
}

// ÀÚÀ¯·Î¿î ¸÷µé
HRESULT enemyManager::init(const char* imageName, float x, float y, float moveRange, int kind)
{
	if (kind == 1)
	{
		_enemy = new bat;
		
	}
	else if (kind == 2)
	{
		_enemy = new hosuk;
		
	}
	else if (kind == 3)
	{
		_enemy = new bloodSkeleton;
	}
	else
	{
		_enemy = new Dracula;
	}

	
	_enemy->init(imageName, x, y, moveRange);

	_vEnemy.push_back(_enemy);

	return S_OK;
}


void enemyManager::release()																	
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->release();
		//_viEnemy = _vEnemy.erase(_viEnemy);
	}

}

void enemyManager::update()																		
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->update();
	}
	
}

void enemyManager::render()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->render();
	}
}
