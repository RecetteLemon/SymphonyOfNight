#include "stdafx.h"
#include "familiarManager.h"


familiarManager::familiarManager()
{
}


familiarManager::~familiarManager()
{
}

HRESULT familiarManager::init()
{
	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;
	
	_focusFamiliar = NULL;

	IMAGEMANAGER->addFrameImage("familiarDemon", "familiar_demon.bmp", 640, 672, 5, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("familiarFairy", "familiar_fairy.bmp", 256, 512, 4, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("familiarGhost", "familiar_ghost.bmp", 256, 256, 4, 4, true, RGB(255, 0, 255));

	_familiar[FAMILIAR_DEMON] = new familiarDemon;
	_familiar[FAMILIAR_DEMON]->init("familiarDemon", &_x, &_y);

	_familiar[FAMILIAR_FAIRY] = new familiarFairy;
	_familiar[FAMILIAR_FAIRY]->init("familiarFairy", &_x, &_y);

	_familiar[FAMILIAR_GHOST] = new familiarGhost;
	_familiar[FAMILIAR_GHOST]->init("familiarGhost", &_x, &_y);

	_kind = FAMILIAR_DEMON;
	_focusFamiliar = _familiar[_kind];
	_familiar[_kind]->setDirection(1);
	return S_OK;
}

void familiarManager::release()
{
	gameNode::release();

	for (int i = 0; i < FAMILIAR_END; i++)
	{
		if (_familiar[i] != NULL)
		{
			SAFE_DELETE(_familiar[i]);
		}
	}
}

void familiarManager::update()
{
	gameNode::update();

	keyControl();

	for (int i = 0; i < FAMILIAR_END; i++)
	{
		if (_familiar[i] == NULL) continue;
		_familiar[i]->update();
	}

	
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
	_kind = FAMILIARKIND(kind);
	
	switch (_kind)
	{
	case FAMILIAR_DEMON:
		_familiar[_kind]->setDirection(1);
		_focusFamiliar = _familiar[_kind];
		break;
	case FAMILIAR_FAIRY:
		_familiar[_kind]->setDirection(0);
		_focusFamiliar = _familiar[_kind];
		break;
	case FAMILIAR_GHOST:
		_familiar[_kind]->setDirection(1);
		_focusFamiliar = _familiar[_kind];
		break;
	case FAMILIAR_END:
		_focusFamiliar = NULL;
	}

	
}

void familiarManager::keyControl(void)
{
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		selectFamailiar(0);
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		selectFamailiar(1);
	}
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		selectFamailiar(2);
	}
	if (KEYMANAGER->isOnceKeyDown('4'))
	{
		selectFamailiar(3);
	}
}