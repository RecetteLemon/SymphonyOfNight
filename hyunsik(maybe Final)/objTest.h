#pragma once
#include "gameNode.h"
#include "objectCreate.h"

class objTest : public gameNode
{
private:


	objectCreate* _obj;

	RECT _rc;
	float _x, _y;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

public:
	objTest();
	~objTest();
};

