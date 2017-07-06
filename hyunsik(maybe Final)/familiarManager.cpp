#include "stdafx.h"
#include "familiarManager.h"


familiarManager::familiarManager()
{
}


familiarManager::~familiarManager()
{
}

HRESULT familiarManager::init(float* x, float* y)
{




	_x = x;
	_y = y;

	_familiarX = *_x;
	_familiarY = *_y;

	_kind = FAMILIAR_END;
	_focusFamiliar = NULL;

	return S_OK;
}

void familiarManager::release()
{
	if (_focusFamiliar != NULL) SAFE_DELETE(_focusFamiliar);

	IMAGEMANAGER->deleteImage("familiarDemon");
	IMAGEMANAGER->deleteImage("familiarFairy");
	IMAGEMANAGER->deleteImage("familiarGhost");
}

void familiarManager::update()
{
	if (_focusFamiliar != NULL) _focusFamiliar->update();
}

void familiarManager::render()
{
	if (_focusFamiliar != NULL)
	{
		_focusFamiliar->render();
	}
}

void familiarManager::selectFamailiar(int kind)
{
	if (_focusFamiliar != NULL) SAFE_DELETE(_focusFamiliar);

	_kind = FAMILIARKIND(kind);

	_familiarX = *_x;
	_familiarY = *_y;

	switch (_kind)
	{
	case FAMILIAR_DEMON:
		_focusFamiliar = new familiarDemon;
		_focusFamiliar->init("familiarDemon", _familiarX, _familiarY, _x, _y);
		break;
	case FAMILIAR_FAIRY:
		_focusFamiliar = new familiarFairy;
		_focusFamiliar->init("familiarFairy", _familiarX, _familiarY, _x, _y);
		break;
	case FAMILIAR_GHOST:
		_focusFamiliar = new familiarGhost;
		_focusFamiliar->init("familiarGhost", _familiarX, _familiarY, _x, _y);
		break;
	case FAMILIAR_END:
		_focusFamiliar = NULL;
	}
}
