#include "stdafx.h"
#include "objectCreate.h"


objectCreate::objectCreate()
{
}


objectCreate::~objectCreate()
{
}

HRESULT objectCreate::init(float x, float y)
{
	
	_itemImg = new image[DROP_ITEM_END];
	
	
	_onDropItem = false;
	_onBottomItem = false;
	ZeroMemory(_itemImg, sizeof(image) * (int)DROP_ITEM_END);
	_itemImg[HEART].init("Image/Item/heart.bmp", 154, 12, 11, 1, true, RGB(255, 0, 255));
	_itemImg[GOLD].init("Image/Item/gold.bmp", 19, 17, 1, 1, true, RGB(255, 0, 255));

	_randomItem = (DROP_ITEM)RND->getInt(2);
	_gold = RND->getFromIntTo(1, 100);
	_heart = RND->getFromIntTo(1, 100);
	
	_x = _startX = x;
	_y = y;
	_countX = 0;
	_rc = RectMakeBottomCenter(_x, _y, _itemImg[_randomItem].getFrameWidth(), _itemImg[_randomItem].getFrameHeight());

	return S_OK;
}

void objectCreate::release(void)	
{
	for (int i = 0; i < DROP_ITEM_END; i++)
	{
		_itemImg[(DROP_ITEM)i].release();
	}

	
	safeDeleteArray(_itemImg);
}

void objectCreate::update(void)		
{
	if (_onDropItem)
	{
		_checkY = _y;
		_y += DROP_SPEED;
		_itemImg[_randomItem].setFrameX(_itemImg[_randomItem].getFrameX() + 1);
		this->heartMoving();
	}

	

	_rc = RectMakeBottomCenter(_x, _y, _itemImg[_randomItem].getFrameWidth(), _itemImg[_randomItem].getFrameHeight());
	
	if (_checkY == _y) _onBottomItem = true;
}

void objectCreate::render(void)		
{
	if (_onDropItem)
	{
		_itemImg[_randomItem].frameRender(getMemDC(), _rc.left, _rc.top);
	}
}

void objectCreate::heartMoving()
{
	if (_randomItem == HEART && !_onBottomItem)
	{
		_x = _startX + 10 * sinf(_countX);
		if (_countX <= 2 * PI) _countX += PI32;
		else _countX = 0;
	}
}