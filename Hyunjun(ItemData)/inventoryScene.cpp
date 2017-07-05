#include "stdafx.h"
#include "inventoryScene.h"


inventoryScene::inventoryScene()
{
}


inventoryScene::~inventoryScene()
{
}

HRESULT inventoryScene::init(void)
{
	_invenUIImg = IMAGEMANAGER->findImage("InventoryUI");
	_itemSelect = IMAGEMANAGER->findImage("ItemSelect");
	_equip = FIRST;

	INVEN->insertItem("발만웨");
	INVEN->insertItem("고기");
	INVEN->insertItem("바베큐");
	INVEN->insertItem("바베큐");
	INVEN->insertItem("소주");
	INVEN->insertItem("진주반지");
	INVEN->insertItem("골드체스트");
	INVEN->insertItem("석가면");
	INVEN->insertItem("파란포션");
	INVEN->insertItem("레이피어");
	INVEN->insertItem("타케미츠");
	INVEN->insertItem("주황포션");
	INVEN->insertItem("틸핑");
	INVEN->insertItem("녹슨검");
	INVEN->insertItem("엘프망토");
	INVEN->insertItem("엘프망토");
	INVEN->insertItem("피로물든망토");
	

	INVEN->deleteItem("틸핑");
	_x = 200;
	_y = 10;
	_invenScroll = 0;
	_onInven = false;
	return S_OK;
}

void inventoryScene::release(void)
{
	_invenUIImg = NULL;
	_itemSelect = NULL;
}

void inventoryScene::update(void)
{
	if (!_onInven)
	{
		this->alucardSelect();
	}
	else
	{
		this->invenSelect();
	}

	_rc = RectMake(_x, _y, _itemSelect->getWidth(), _itemSelect->getHeight());
}

void inventoryScene::render(void)
{
	int count = 0;
	char str[128];
	_invenUIImg->render(getMemDC(), 0, 0);

	
	
	
	this->invenDraw();
	_itemSelect->render(getMemDC(), _rc.left, _rc.top);

	//sprintf_s(str, "%d", INVEN->getVinven()[2].count_);
	//TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY / 2, str, strlen(str));
}

void inventoryScene::alucardSelect()
{
	if (KEYMANAGER->isOnceKeyDown(VK_UP) && _equip != FIRST)
	{
		_equip = (EQUIP_POS)((int)_equip - 1);
		_y -= 40;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_DOWN) && _equip != SEVENTH)
	{
		_equip = (EQUIP_POS)((int)_equip + 1);
		_y += 40;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_onInven = true;
		_equip = FIRST;
		_x = 80;
		_y = 300;
	}
}

void inventoryScene::invenSelect()
{
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (_equip == FIRST || _equip == SECOND)
		{
			if (_invenScroll > 0) _invenScroll -= 2;
		}
		else
		{
			_equip = (EQUIP_POS)((int)_equip - 2);
			_y -= 40;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (_equip == NINTH || _equip == TENTH)
		{
			if (INVEN->getVinven().size() - _invenScroll > 10) _invenScroll += 2;
		}
		else
		{
			_equip = (EQUIP_POS)((int)_equip + 2);
			_y += 40;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) && ((int)(_equip)) % 2 == 0 )
	{
		_equip = (EQUIP_POS)((int)_equip + 1);
		_x += 400;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT) && ((int)(_equip)) % 2 == 1)
	{
		_equip = (EQUIP_POS)((int)_equip - 1);
		_x -= 400;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_onInven = false;
		_x = 200;
		_y = 10;
		_equip = FIRST;
	}
}

void inventoryScene::invenDraw()
{
	char str[128];
	HFONT font, oldFont;
	font = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "고딕");
	oldFont = (HFONT)SelectObject(getMemDC(), font);

	SetTextColor(getMemDC(), RGB(255, 255, 255));
	SetBkMode(getMemDC(), TRANSPARENT);
	for (int i = _invenScroll; i < INVEN->getVinven().size(); i++)
	{
		if (i - _invenScroll >= 10) break;

		
		INVEN->getVinven()[i].img_->render(getMemDC(), ((i - _invenScroll) % 2) * 400 + 90, ((i - _invenScroll) / 2) * 40 + 305);

		sprintf_s(str, "%s", INVEN->getVinven()[i].name_.c_str());
		TextOut(getMemDC(), ((i - _invenScroll) % 2) * 400 + 120, ((i - _invenScroll) / 2) * 40 + 305, str, strlen(str));
		sprintf_s(str, "X%d", INVEN->getVinven()[i].count_);
		TextOut(getMemDC(), ((i - _invenScroll) % 2) * 400 + 345, ((i - _invenScroll) / 2) * 40 + 305, str, strlen(str));

		if (i -_invenScroll == (int)_equip && _onInven)
		{
			sprintf_s(str, "%s", INVEN->getVinven()[i].description_.c_str());
			TextOut(getMemDC(), 100, 535, str, strlen(str));
			INVEN->getVinven()[i].img_->render(getMemDC(), 20, 530, 0, 0, 50, 50, 25, 25);
		}
	}

	DeleteObject(SelectObject(getMemDC(), oldFont));
}