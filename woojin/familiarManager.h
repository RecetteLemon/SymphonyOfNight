#pragma once
#include "gameNode.h"
#include "familiarDemon.h"
#include "familiarFairy.h"

enum FAMILIARKIND
{
	FAMILIAR_DEMON,
	FAMILIAR_FAIRY,
	FAMILIAR_GHOST,
	FAMILIAR_END
};

class familiarManager : public gameNode
{
private:
	familiar* _familiar[FAMILIAR_END];
	familiar* _focusFamiliar;
	FAMILIARKIND _kind;

	float _x;
	float _y;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void selectFamailiar(int kind);

	void keyControl(void);

	familiarManager();
	~familiarManager();
};

