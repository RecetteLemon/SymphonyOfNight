#pragma once
#include "gameNode.h"
#define EPSILON 0.01f

enum FAMILIARDIRECTION
{
	FAMILIAR_DIRECTION_STAND,
	FAMILIAR_DIRECTION_RIGHT,
	FAMILIAR_DIRECTION_LEFT,
	FAMILIAR_DIRECTION_RIGHT_ATTACK,
	FAMILIAR_DIRECTION_LEFT_ATTACK,
	FAMILIAR_DIRECTION_CASTSKILL,
	FAMILIAR_DIRECTION_NULL,
};

class familiar : public gameNode
{
protected:
	float* _x;
	float* _y;
	float _targetX, _targetY;
	FAMILIARDIRECTION _direction;
	bool _familiarChange;

//	RECT _rc;
//	RECT _hitBox;

public:
	virtual HRESULT init(const char* imageName, float* x, float* y);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//RECT getRect(void) { return _rc; }

	virtual void move(void);
	virtual void setDirection(int direction) { _direction = (FAMILIARDIRECTION)direction; }

	familiar();
	virtual ~familiar();
};

