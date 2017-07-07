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

	//_familiar = new familiar[FAMILIAR_END];
	//ZeroMemory(_familiar, sizeof(familiar) * FAMILIAR_END);

	_familiar[FAMILIAR_DEMON] = new familiarDemon;
 	_familiar[FAMILIAR_DEMON]->init(IMAGEMANAGER->findImage("familiarDemon"), _familiarX, _familiarY, _x, _y);

	_familiar[FAMILIAR_FAIRY] = new familiarFairy;
	_familiar[FAMILIAR_FAIRY]->init(IMAGEMANAGER->findImage("familiarFairy"), _familiarX, _familiarY, _x, _y);

	_familiar[FAMILIAR_GHOST] = new familiarGhost;
	_familiar[FAMILIAR_GHOST]->init(IMAGEMANAGER->findImage("familiarGhost"), _familiarX, _familiarY, _x, _y);

	//_focusFamiliar = NULL;
	_kind = FAMILIARKIND(ALUCARD_INFO->getStats().familiar);
	selectFamailiar(int(_kind));

	return S_OK;
}

void familiarManager::release()
{
	//if (_focusFamiliar != NULL) SAFE_DELETE(_focusFamiliar);
	for (int i = 0; i < FAMILIAR_END; i++)
	{
		SAFE_DELETE(_familiar[i]);
	}
	
}

void familiarManager::update()
{
	/*if (_focusFamiliar != NULL)
	{
		_focusFamiliar->update();
		selectFamailiar(ALUCARD_INFO->getStats().familiar);
	}*/
	for (int i = 0; i < FAMILIAR_END; i++)
	{
		_familiar[i]->update();
	}
}

void familiarManager::render(HDC hdc)
{
	/*for (int i = 0; i < FAMILIAR_END; i++)
	{
		if (i == (int)_kind)
		{
			_familiar[i].render(hdc);
		}
		else continue;
	}*/
	if(_focusFamiliar != NULL) _focusFamiliar->render(hdc);
}

void familiarManager::selectFamailiar(int kind)
{
	//if (_focusFamiliar != NULL) SAFE_DELETE(_focusFamiliar);

	_kind = FAMILIARKIND(kind);

	_familiarX = *_x;
	_familiarY = *_y;

	switch (_kind)
	{
	case FAMILIAR_DEMON:
		//_focusFamiliar = new familiarDemon;
		//_focusFamiliar->init(IMAGEMANAGER->findImage("familiarDemon"), _familiarX, _familiarY, _x, _y);
		_focusFamiliar = _familiar[FAMILIAR_DEMON];
		break;
	case FAMILIAR_FAIRY:
		//_focusFamiliar = new familiarFairy;
		//_focusFamiliar->init(IMAGEMANAGER->findImage("familiarFairy"), _familiarX, _familiarY, _x, _y);
		_focusFamiliar = _familiar[FAMILIAR_FAIRY];
		break;
	case FAMILIAR_GHOST:
		//_focusFamiliar = new familiarGhost;
		//_focusFamiliar->init(IMAGEMANAGER->findImage("familiarGhost"), _familiarX, _familiarY, _x, _y);
		_focusFamiliar = _familiar[FAMILIAR_GHOST];
		break;
	case FAMILIAR_END:
		_focusFamiliar = NULL;
		break;
	}
}
