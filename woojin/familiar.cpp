#include "stdafx.h"
#include "familiar.h"


familiar::familiar()
{
}

familiar::~familiar()
{
}

HRESULT familiar::init(const char* imageName, float* x, float* y)
{
	gameNode::init();

	_x = x;
	_y = y;

	_targetX = *x;
	_targetY = *y;

	//*_y = *_y - WINSIZEY / 2;

	_familiarChange = true;

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