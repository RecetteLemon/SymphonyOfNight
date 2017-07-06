#include "stdafx.h"
#include "objectCreate.h"


objectCreate::objectCreate()
{
}


objectCreate::~objectCreate()
{
}

HRESULT objectCreate::init(float x, float y, int pickObj)
{
	

	this->randomSour();
	_itemCurrentFrameX = 0;
	_objCurrentFrameX = 0;
	_elapsedTime = 0;
	_pickObj = pickObj;

	if (_pickObj == 0) _objImg = IMAGEMANAGER->findImage("Object1");
	else if (_pickObj == 1) _objImg = IMAGEMANAGER->findImage("Object2");
	else if (_pickObj == 2) _objImg = IMAGEMANAGER->findImage("Object3");

	_pickRandom = RND->getInt(43);

	_pixel = new pixelCollision;
	_itemImg = new image*[DROP_ITEM_END];
	
	
	_onDropItem = false;
	_onBottomItem = false;
	ZeroMemory(_itemImg, sizeof(image*) * (int)DROP_ITEM_END);
	_itemImg[HEART] = IMAGEMANAGER->findImage("Heart");
	_itemImg[GOLD] = IMAGEMANAGER->findImage("Gold");
	_itemImg[DROP_I] = IMAGEMANAGER->findImage(_randomCreateItem.find(_pickRandom)->second);

	_randomItem = (DROP_ITEM)RND->getInt(3);
	_gold = RND->getFromIntTo(1, 100);
	_heart = RND->getFromIntTo(1, 100);
	
	_x = _startX = x;
	_y = y;
	_countX = 0;
	_rc = RectMakeBottomCenter(_x, _y, _itemImg[_randomItem]->getFrameWidth(), _itemImg[_randomItem]->getFrameHeight());

	return S_OK;
}

void objectCreate::release(void)	
{
	
	safeDelete(_pixel);
	safeDeleteArray(_itemImg);
}

void objectCreate::update(void)		
{
	if (_onDropItem)
	{
		_checkY = _y;
		_y += DROP_SPEED;
		if ((int)_randomItem < 2) _itemImg[_randomItem]->setFrameX(_itemCurrentFrameX);
		
		this->heartMoving();

		_itemCurrentFrameX++;

		
		if (_itemImg[_randomItem]->getMaxFrameX() < _itemCurrentFrameX && (int)_randomItem < 2) _itemCurrentFrameX = 0;
	}
	else
	{
		if (_elapsedTime >= 1.0f / 10.0f)
		{
			_objImg->setFrameX(_objCurrentFrameX);
			_objCurrentFrameX++;
			if (_objImg->getMaxFrameX() < _objCurrentFrameX) _objCurrentFrameX = 0;

			_elapsedTime = 0;
		}
	}

	
	_pixel->pixelColliBottom(0, 0, IMAGEMANAGER->findImage("PixelTest"), _x, _y, 10);

	if (_onDropItem)
	{
		if ((int)_randomItem < 2)
		{
			_rc = RectMakeBottomCenter(_x, _y, _itemImg[_randomItem]->getFrameWidth(), _itemImg[_randomItem]->getFrameHeight());
		}
		else if ((int)_randomItem == 2)
		{
			_rc = RectMakeBottomCenter(_x, _y, _itemImg[_randomItem]->getWidth(), _itemImg[_randomItem]->getHeight());
		}
		else
		{
			_rc = RectMake(0, 0, 0, 0);
		}
	}
	else
	{
		_rc = RectMakeBottomCenter(_x, _y, _objImg->getFrameWidth(), _objImg->getFrameHeight());
	}
	
	if (_checkY == _y) _onBottomItem = true;

	_elapsedTime += TIMEMANAGER->getElapsedTime();
}

void objectCreate::render(void)		
{
	if (_onDropItem)
	{
		if ((int)_randomItem < 2)
		{
			_itemImg[_randomItem]->frameRender(getMemDC(), _rc.left, _rc.top);
		}
		else if ((int)_randomItem == 2)
		{
			char str[128];
			HFONT font, oldFont;
			font = CreateFont(20, 0, 0, 0, 500, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "고딕");
			oldFont = (HFONT)SelectObject(getMemDC(), font);

			SetTextColor(getMemDC(), RGB(0, 0, 0));
			SetBkMode(getMemDC(), TRANSPARENT);

			sprintf_s(str, "%s", _randomCreateItem.find(_pickRandom)->second.c_str());
			TextOut(getMemDC(), _rc.left - 10, _rc.top - 20, str, strlen(str));
			_itemImg[_randomItem]->render(getMemDC(), _rc.left, _rc.top);

			DeleteObject(SelectObject(getMemDC(), oldFont));
		}
		else
		{

		}
	}
	else
	{
		_objImg->frameRender(getMemDC(), _rc.left, _rc.top);
	}
}

void objectCreate::heartMoving()
{
	if (_randomItem == HEART && !_onBottomItem)
	{
		_y -= 6;
		_x = _startX + 10 * sinf(_countX);
		if (_countX <= 2 * PI) _countX += PI32;
		else _countX = 0;
	}
}

void objectCreate::randomSour()
{
	_randomCreateItem.insert(pair<int, string>(0, "바제랄드"));
	_randomCreateItem.insert(pair<int, string>(1, "숏소드"));
	_randomCreateItem.insert(pair<int, string>(2, "레이피어"));
	_randomCreateItem.insert(pair<int, string>(3, "쥬엘소드"));
	_randomCreateItem.insert(pair<int, string>(4, "컴뱃나이프"));
	_randomCreateItem.insert(pair<int, string>(5, "틸핑"));
	_randomCreateItem.insert(pair<int, string>(6, "그라디우스"));
	_randomCreateItem.insert(pair<int, string>(7, "세이버"));
	_randomCreateItem.insert(pair<int, string>(8, "하루파"));
	_randomCreateItem.insert(pair<int, string>(9, "발만웨"));
	_randomCreateItem.insert(pair<int, string>(10, "녹슨검"));
	_randomCreateItem.insert(pair<int, string>(11, "요도무라마사"));
	_randomCreateItem.insert(pair<int, string>(12, "타케미츠"));
	_randomCreateItem.insert(pair<int, string>(13, "야스츠나"));
	_randomCreateItem.insert(pair<int, string>(14, "마사무네"));
	_randomCreateItem.insert(pair<int, string>(15, "실버티아라"));
	_randomCreateItem.insert(pair<int, string>(16, "석가면"));
	_randomCreateItem.insert(pair<int, string>(17, "은빛서클렛"));
	_randomCreateItem.insert(pair<int, string>(18, "성스러운안경"));
	_randomCreateItem.insert(pair<int, string>(19, "펠트의모자"));
	_randomCreateItem.insert(pair<int, string>(20, "미러큐이러스"));
	_randomCreateItem.insert(pair<int, string>(21, "실버체스트"));
	_randomCreateItem.insert(pair<int, string>(22, "골드체스트"));
	_randomCreateItem.insert(pair<int, string>(23, "다이아블래스트"));
	_randomCreateItem.insert(pair<int, string>(24, "플레티넘체스트"));
	_randomCreateItem.insert(pair<int, string>(25, "킹스톤"));
	_randomCreateItem.insert(pair<int, string>(26, "넥클레스"));
	_randomCreateItem.insert(pair<int, string>(27, "진주반지"));
	_randomCreateItem.insert(pair<int, string>(28, "마스터부츠"));
	_randomCreateItem.insert(pair<int, string>(29, "플레티넘부츠"));
	_randomCreateItem.insert(pair<int, string>(30, "리버서블망토"));
	_randomCreateItem.insert(pair<int, string>(31, "피로물든망토"));
	_randomCreateItem.insert(pair<int, string>(32, "엘프망토"));
	_randomCreateItem.insert(pair<int, string>(33, "블루망토"));
	_randomCreateItem.insert(pair<int, string>(34, "오더메이드"));
	_randomCreateItem.insert(pair<int, string>(35, "고기"));
	_randomCreateItem.insert(pair<int, string>(36, "버섯"));
	_randomCreateItem.insert(pair<int, string>(37, "소주"));
	_randomCreateItem.insert(pair<int, string>(38, "스파게티"));
	_randomCreateItem.insert(pair<int, string>(39, "바베큐"));
	_randomCreateItem.insert(pair<int, string>(40, "파란포션"));
	_randomCreateItem.insert(pair<int, string>(41, "초록포션"));
	_randomCreateItem.insert(pair<int, string>(42, "주황포션"));
}

void objectCreate::gainItem(RECT rc)
{
	RECT temp;
	if (IntersectRect(&temp, &_rc, &rc) && _onDropItem)
	{
		INVEN->insertItem(_randomCreateItem.find(_pickRandom)->second);
		_onDropItem = false;
	}
}