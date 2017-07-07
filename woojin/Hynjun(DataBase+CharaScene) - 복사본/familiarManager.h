#pragma once
#include "gameNode.h"
#include "familiarDemon.h"
#include "familiarFairy.h"
#include "familiarGhost.h"

enum FAMILIARKIND
{
	FAMILIAR_DEMON,
	FAMILIAR_FAIRY,
	FAMILIAR_GHOST,
	FAMILIAR_END
};

enum PLAYERDIRECT
{
	PRIGHT, PLEFT
};

class familiarManager : public gameNode
{
private:

	familiar* _focusFamiliar;
	familiar* _familiar[FAMILIAR_END];
	FAMILIARKIND _kind;
	PLAYERDIRECT _playerDirect;

	float* _x;
	float* _y;
	float _familiarX;
	float _familiarY;

	RECT _rc;

public:
	HRESULT init(float* x, float* y);
	void release(void);
	void update(void);
	void render(HDC hdc);

	void selectFamailiar(int kind);
	
	int getFamiliarKind(void) { return (int)_kind; }

	void setPlayerDirect(int direct) { _playerDirect = (PLAYERDIRECT)direct; }

	familiarManager();
	~familiarManager();
};

