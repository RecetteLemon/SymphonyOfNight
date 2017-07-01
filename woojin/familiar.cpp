#include "stdafx.h"
#include "familiar.h"


familiar::familiar()
	//:_x(0.0f), _y(0.0f), _direction(FAMILIAR_DIRECTION_NULL)
	//_targetX(0.0f), _targetY(0.0f),
	//_rc({ 0, 0, 0, 0 }), _hitBox({ 0, 0, 0, 0 }), 
{
}

familiar::~familiar()
{
}

HRESULT familiar::init(const char* imageName, float* x, float* y)
{
	gameNode::init();
	return S_OK;
}

void familiar::release(void)
{
	gameNode::release();
}

void familiar::update(void)
{
	gameNode::update();
}

void familiar::render(void)
{
}

void familiar::move(void)
{
}

void familiar::stopMotion(void)
{
}