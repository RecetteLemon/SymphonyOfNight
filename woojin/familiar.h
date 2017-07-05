#pragma once
#include "gameNode.h"
#define BODYFRAME 120.0f
#define WINGFRAME 50.0f
#define HAIRFRAME 50.0f

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
	float _x, _y;
	float* _playerPosX;
	float* _playerPosY;
	float _angle; 
	FAMILIARDIRECTION _direction;

	RECT _rc;
//	RECT _hitBox;

public:
	virtual HRESULT init(const char* imageName, float x, float y, float* playerPosX, float* playerPosY);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void move(void);
	virtual void setDirection(int direction);

	familiar();
	virtual ~familiar();
};

