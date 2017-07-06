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
	INVEN->insertItem("하루파");
	
	

	INVEN->deleteItem("틸핑");
	INVEN->deleteItem("피로물든망토");
	_x = 200;
	_y = 10;
	_invenScroll = 0;
	_invenNum = 0;
	_alucardNum = 0;
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

	if (KEYMANAGER->isOnceKeyDown('X') && ALUCARD->getValucard().size() > 0)
	{
		for (int i = 0; i < ALUCARD->getValucard().size();)
		{
			if (ALUCARD->getValucard()[i].category_ == (CATEGORY_E)_alucardNum)
			{
				ALUCARD->deleteItem(ALUCARD->getValucard()[i].name_);
				break;
			}
			else
			{
				i++;
			}
		}
	}

	ALUCARD_INFO->statUpdate();

	this->sceneChange();
}

void inventoryScene::render(void)
{
	int count = 0;
	char str[128];
	_invenUIImg->render(getMemDC(), 0, 0);

	this->alucardSelectDraw();
	this->invenDraw();
	this->statDraw();
	_itemSelect->render(getMemDC(), _rc.left, _rc.top);

}

void inventoryScene::alucardSelect()
{
	if (KEYMANAGER->isOnceKeyDown(VK_UP) && _equip != FIRST)
	{
		_alucardNum--;
		_equip = (EQUIP_POS)((int)_equip - 1);
		_y -= 40;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_DOWN) && _equip != SEVENTH)
	{
		_alucardNum++;
		_equip = (EQUIP_POS)((int)_equip + 1);
		_y += 40;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_onInven = true;
		_equip = FIRST;
		_x = 80;
		_y = 300;
		_invenNum = 0;
	}
}

void inventoryScene::invenSelect()
{
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (_equip == FIRST || _equip == SECOND)
		{
			if (_invenScroll > 0)
			{
				_invenScroll -= 2;
				_invenNum -= 2;
			}
		}
		else
		{
			_equip = (EQUIP_POS)((int)_equip - 2);
			_y -= 40;
			_invenNum -= 2;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (_equip == NINTH || _equip == TENTH)
		{
			if (INVEN->getVinven().size() - _invenScroll > 10)
			{
				_invenScroll += 2;
				_invenNum += 2;
			}
		}
		else
		{
			_equip = (EQUIP_POS)((int)_equip + 2);
			_y += 40;
			_invenNum += 2;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) && ((int)(_equip)) % 2 == 0 )
	{
		_equip = (EQUIP_POS)((int)_equip + 1);
		_x += 400;
		_invenNum += 1;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT) && ((int)(_equip)) % 2 == 1)
	{
		_equip = (EQUIP_POS)((int)_equip - 1);
		_x -= 400;
		_invenNum -= 1;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		this->invenPick();
		_onInven = false;
		_x = 200;
		_y = 10;
		_equip = FIRST;
		_alucardNum = 0;
		_invenScroll = 0;
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

		if (i - _invenScroll == (int)_equip && _onInven)
		{
			sprintf_s(str, "%s", INVEN->getVinven()[i].description_.c_str());
			TextOut(getMemDC(), 100, 535, str, strlen(str));
			INVEN->getVinven()[i].img_->render(getMemDC(), 20, 530, 0, 0, 50, 50, 25, 25);

			sprintf_s(str, "+%d", INVEN->getVinven()[i].str_);
			TextOut(getMemDC(), 100, 137, str, strlen(str));

			sprintf_s(str, "+%d", INVEN->getVinven()[i].con_);
			TextOut(getMemDC(), 100, 172, str, strlen(str));

			sprintf_s(str, "+%d", INVEN->getVinven()[i].int_);
			TextOut(getMemDC(), 100, 207, str, strlen(str));

			sprintf_s(str, "+%d", INVEN->getVinven()[i].lck_);
			TextOut(getMemDC(), 100, 242, str, strlen(str));

			
		}
	}

	DeleteObject(SelectObject(getMemDC(), oldFont));

	sprintf_s(str, "%d, %d", ALUCARD_INFO->getStats().HP, ALUCARD_INFO->getStats().HPMax);
	TextOut(getMemDC(), 700, 535, str, strlen(str));

	sprintf_s(str, "%d, %d", INVEN->getVinven().size(), ALUCARD->getValucard().size());
	TextOut(getMemDC(), 700, 550, str, strlen(str));
}

void inventoryScene::alucardSelectDraw()
{
	char str[128];
	HFONT font, oldFont;
	font = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "고딕");
	oldFont = (HFONT)SelectObject(getMemDC(), font);

	SetTextColor(getMemDC(), RGB(255, 255, 255));
	SetBkMode(getMemDC(), TRANSPARENT);
	for (int i = 0; i < ALUCARD->getValucard().size(); i++)
	{
		if (ALUCARD->getValucard()[i].category_ == DAGGER)
		{
			ALUCARD->getValucard()[i].img_->render(getMemDC(), 200, 15 + 40 * 0);
			sprintf_s(str, "%s", ALUCARD->getValucard()[i].name_.c_str());
			TextOut(getMemDC(), 250, 15 + 40 * 0, str, strlen(str));
		}
		else if (ALUCARD->getValucard()[i].category_ == SWORD)
		{
			ALUCARD->getValucard()[i].img_->render(getMemDC(), 200, 15 + 40 * 1);
			sprintf_s(str, "%s", ALUCARD->getValucard()[i].name_.c_str());
			TextOut(getMemDC(), 250, 15 + 40 * 1, str, strlen(str));
		}
		else if (ALUCARD->getValucard()[i].category_ == SUB)
		{
			ALUCARD->getValucard()[i].img_->render(getMemDC(), 200, 15 + 40 * 2);
			sprintf_s(str, "%s", ALUCARD->getValucard()[i].name_.c_str());
			TextOut(getMemDC(), 250, 15 + 40 * 2, str, strlen(str));
		}
		else if (ALUCARD->getValucard()[i].category_ == HEAD)
		{
			ALUCARD->getValucard()[i].img_->render(getMemDC(), 200, 15 + 40 * 3);
			sprintf_s(str, "%s", ALUCARD->getValucard()[i].name_.c_str());
			TextOut(getMemDC(), 250, 15 + 40 * 3, str, strlen(str));
		}
		else if (ALUCARD->getValucard()[i].category_ == ARMOR)
		{
			ALUCARD->getValucard()[i].img_->render(getMemDC(), 200, 15 + 40 * 4);
			sprintf_s(str, "%s", ALUCARD->getValucard()[i].name_.c_str());
			TextOut(getMemDC(), 250, 15 + 40 * 4, str, strlen(str));
		}
		else if (ALUCARD->getValucard()[i].category_ == ACCESSORY)
		{
			ALUCARD->getValucard()[i].img_->render(getMemDC(), 200, 15 + 40 * 5);
			sprintf_s(str, "%s", ALUCARD->getValucard()[i].name_.c_str());
			TextOut(getMemDC(), 250, 15 + 40 * 5, str, strlen(str));
		}
		else if (ALUCARD->getValucard()[i].category_ == CAPE)
		{
			ALUCARD->getValucard()[i].img_->render(getMemDC(), 200, 15 + 40 * 6);
			sprintf_s(str, "%s", ALUCARD->getValucard()[i].name_.c_str());
			TextOut(getMemDC(), 250, 15 + 40 * 6, str, strlen(str));
		}
	}

	
	switch (_alucardNum)
	{
	case 0:
		sprintf_s(str, "DAGGER");
		TextOut(getMemDC(), 20, 50, str, strlen(str));
		sprintf_s(str, "SLOT");
		TextOut(getMemDC(), 20, 80, str, strlen(str));
		break;

	case 1:
		sprintf_s(str, "SWORD");
		TextOut(getMemDC(), 20, 50, str, strlen(str));
		sprintf_s(str, "SLOT");
		TextOut(getMemDC(), 20, 80, str, strlen(str));
		break;
	case 2:
		sprintf_s(str, "SUB");
		TextOut(getMemDC(), 20, 50, str, strlen(str));
		sprintf_s(str, "SLOT");
		TextOut(getMemDC(), 20, 80, str, strlen(str));
		break;

	case 3:
		sprintf_s(str, "HEAD");
		TextOut(getMemDC(), 20, 50, str, strlen(str));
		sprintf_s(str, "SLOT");
		TextOut(getMemDC(), 20, 80, str, strlen(str));
		break;

	case 4:
		sprintf_s(str, "ARMOR");
		TextOut(getMemDC(), 20, 50, str, strlen(str));
		sprintf_s(str, "SLOT");
		TextOut(getMemDC(), 20, 80, str, strlen(str));
		break;

	case 5:
		sprintf_s(str, "ACCESSORY");
		TextOut(getMemDC(), 20, 50, str, strlen(str));
		sprintf_s(str, "SLOT");
		TextOut(getMemDC(), 20, 80, str, strlen(str));
		break;

	case 6:
		sprintf_s(str, "CAPE");
		TextOut(getMemDC(), 20, 50, str, strlen(str));
		sprintf_s(str, "SLOT");
		TextOut(getMemDC(), 20, 80, str, strlen(str));
		break;
	}
	
	
	DeleteObject(SelectObject(getMemDC(), oldFont));
}

void inventoryScene::invenPick()
{
	if (INVEN->getVinven().size() > 0)
	{
		if (INVEN->getVinven()[_invenNum].category_ == FOOD)
		{
			if (ALUCARD_INFO->getStats().HP == ALUCARD_INFO->getStats().HPMax) return;

			ALUCARD_INFO->setHP(ALUCARD_INFO->getStats().HP + INVEN->getVinven()[_invenNum].HP_);

			if (ALUCARD_INFO->getStats().HP > ALUCARD_INFO->getStats().HPMax)
			{
				ALUCARD_INFO->setHP(ALUCARD_INFO->getStats().HPMax);
			}

			INVEN->deleteItem(INVEN->getVinven()[_invenNum].name_.c_str());
			return;
		}

		if (INVEN->getVinven()[_invenNum].category_ == POTION)
		{
			ALUCARD_INFO->setHP(ALUCARD_INFO->getStats().HP + INVEN->getVinven()[_invenNum].HP_);

			if (ALUCARD_INFO->getStats().HP > ALUCARD_INFO->getStats().HPMax)
			{
				ALUCARD_INFO->setHP(ALUCARD_INFO->getStats().HPMax);
			}

			ALUCARD_INFO->setSaveStr(ALUCARD_INFO->getStats().saveStr + INVEN->getVinven()[_invenNum].str_);
			ALUCARD_INFO->setSaveCon(ALUCARD_INFO->getStats().saveCon + INVEN->getVinven()[_invenNum].con_);
			ALUCARD_INFO->setSaveInt(ALUCARD_INFO->getStats().saveInt + INVEN->getVinven()[_invenNum].int_);
			ALUCARD_INFO->setSaveLck(ALUCARD_INFO->getStats().saveLck + INVEN->getVinven()[_invenNum].lck_);

			INVEN->deleteItem(INVEN->getVinven()[_invenNum].name_.c_str());
			return;
		}

		if (ALUCARD->getValucard().size() > 0)
		{
			for (int i = 0; i < ALUCARD->getValucard().size(); ++i)
			{
				if (ALUCARD->getValucard()[i].category_ == INVEN->getVinven()[_invenNum].category_)
				{
					if (ALUCARD->getValucard()[i].name_ == INVEN->getVinven()[_invenNum].name_) return;
					ALUCARD->deleteItem(ALUCARD->getValucard()[i].name_);
					ALUCARD->insertItem(INVEN->getVinven()[_invenNum].name_, _invenNum);
					INVEN->deleteItem(INVEN->getVinven()[_invenNum].name_.c_str());
					return;
				}
			}
		}

		ALUCARD->insertItem(INVEN->getVinven()[_invenNum].name_.c_str(), _invenNum);
		INVEN->deleteItem(INVEN->getVinven()[_invenNum].name_.c_str());
	}
}


void inventoryScene::statDraw()
{
	char str[128];
	HFONT font, oldFont;
	font = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "고딕");
	oldFont = (HFONT)SelectObject(getMemDC(), font);

	sprintf_s(str, "%d", ALUCARD_INFO->getStats().str);
	TextOut(getMemDC(), 670, 28, str, strlen(str));

	sprintf_s(str, "%d", ALUCARD_INFO->getStats().con);
	TextOut(getMemDC(), 670, 58, str, strlen(str));

	sprintf_s(str, "%d", ALUCARD_INFO->getStats().int_);
	TextOut(getMemDC(), 670, 88, str, strlen(str));

	sprintf_s(str, "%d", ALUCARD_INFO->getStats().lck);
	TextOut(getMemDC(), 670, 118, str, strlen(str));

	sprintf_s(str, "%d", ALUCARD_INFO->getStats().HP);
	TextOut(getMemDC(), 650, 160, str, strlen(str));

	sprintf_s(str, " / %d", ALUCARD_INFO->getStats().HPMax);
	TextOut(getMemDC(), 710, 160, str, strlen(str));

	sprintf_s(str, "%d", ALUCARD_INFO->getStats().atk);
	TextOut(getMemDC(), 660, 205, str, strlen(str));

	sprintf_s(str, "%d", ALUCARD_INFO->getStats().def);
	TextOut(getMemDC(), 660, 240, str, strlen(str));


	//아이템 착용 후 예상 스탯

	if (_invenNum + 1 - _invenScroll <= INVEN->getVinven().size() - _invenScroll && _onInven)
	{
		sprintf_s(str, "%d", ALUCARD_INFO->getStats().str + INVEN->getVinven()[_invenNum].str_);
		TextOut(getMemDC(), 750, 28, str, strlen(str));

		sprintf_s(str, "%d", ALUCARD_INFO->getStats().con + INVEN->getVinven()[_invenNum].con_);
		TextOut(getMemDC(), 750, 58, str, strlen(str));

		sprintf_s(str, "%d", ALUCARD_INFO->getStats().int_ + INVEN->getVinven()[_invenNum].int_);
		TextOut(getMemDC(), 750, 88, str, strlen(str));

		sprintf_s(str, "%d", ALUCARD_INFO->getStats().lck + INVEN->getVinven()[_invenNum].lck_);
		TextOut(getMemDC(), 750, 118, str, strlen(str));

		sprintf_s(str, "%d", ALUCARD_INFO->getStats().atk + INVEN->getVinven()[_invenNum].atk_ + INVEN->getVinven()[_invenNum].str_ * 3 + INVEN->getVinven()[_invenNum].con_ * 2);
		TextOut(getMemDC(), 750, 205, str, strlen(str));

		sprintf_s(str, "%d", ALUCARD_INFO->getStats().def + INVEN->getVinven()[_invenNum].def_ + INVEN->getVinven()[_invenNum].lck_ * 2 + INVEN->getVinven()[_invenNum].int_);
		TextOut(getMemDC(), 750, 240, str, strlen(str));
	}

	DeleteObject(SelectObject(getMemDC(), oldFont));

	//_alucardStat.str * 3 + _alucardStat.con * 2
	//_alucardStat.lck * 2 + _alucardStat.int_ 
}

void inventoryScene::sceneChange()
{
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		SCENEMANAGER->changeScene("CharScene");
	}

	if (KEYMANAGER->isOnceKeyDown('V'))
	{
		//
	}
}