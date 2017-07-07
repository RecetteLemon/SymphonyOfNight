#include "stdafx.h"
#include "UI.h"


UI::UI()
{
}


UI::~UI()
{
}

HRESULT UI::init(int x, int y, int width, int height, const char* topBar, const char* backBar, const char* magic)
{
	_x = x;
	_y = y;

	_rcprogress = RectMake(x, y, width, height);

	progressBottom = IMAGEMANAGER->addImage(backBar, "HUD.bmp", x, y, width, height, true, RGB(255, 0, 255));
	progressTOP = IMAGEMANAGER->addFrameImage(topBar, "ManaUI.bmp", x, y, width, height, true, RGB(255, 0, 255));
	progressTOP2 = IMAGEMANAGER->addImage(topBar, "manaUI2.bmp", x, y, width, height, true, RGB(255, 0, 255));
	heart = IMAGEMANAGER->addFrameImage(magic, "heart.bmp", x, y, width, height, true, RGB(255, 0, 255));
	number = IMAGEMANAGER->addFrameImage("hp", "HPnum.bmp", 100, 13, 10, 1, true, RGB(255, 0, 255));
	Hnumber = IMAGEMANAGER->addFrameImage("heart", "ManaNum.bmp", 120, 10, 10, 1, true, RGB(255, 0, 255));
	currentWidth = width;
	currentHeight = height;
	_rc = RectMakeCenter(WINSIZEX / 2 + 100, WINSIZEY / 2, 30,30);
	_rc2 = RectMakeCenter(WINSIZEX / 2 - 100, WINSIZEY / 2, 30, 30);
	_rc3 = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 100, 30, 30);

	_width = 100;

	_count = 0;
	//_count2 = 0;


	// 체력넘버 관련
	ZeroMemory(&_playerHP, sizeof(PLAYERHPINFO));

	_playerHP.currentHP = ALUCARD_INFO->getStats().HP;
	
	for (int i = 0; i < 3; i++)
	{
		_playerHP.hpFont[i].x = 5 + i * 10; //IMAGEMANAGER->findImage("hp")->getFrameWidth() - 10;
		_playerHP.hpFont[i].y = 30;
		_playerHP.hpFont[i].img = IMAGEMANAGER->findImage("hp");
		_playerHP.hpFont[i].frameX = 0;
		_playerHP.hpFont[i].renderOn = true;

	}
	

	// 하트넘버 관련
	ZeroMemory(&_playerHT, sizeof(PLAYERHPINFO));

	_playerHT.currentHEART = ALUCARD_INFO->getStats().heart;

	for (int i = 0; i < 2; i++)
	{
		_playerHT.heartFont[i].x = 110 + i * 7; //* IMAGEMANAGER->findImage("heart")->getFrameWidth();
		_playerHT.heartFont[i].y = 25;
		_playerHT.heartFont[i].img = IMAGEMANAGER->findImage("heart");
		_playerHT.heartFont[i].frameX = 0;
		_playerHT.heartFont[i].renderOn = true;
	}

	maxMP = currentMP = ALUCARD_INFO->getStats().mana;
	
	_currentFrameX = 0;

	return S_OK;

}
void UI::release()
{


}
void UI::update()
{
	_rcprogress = RectMakeCenter(_x, _y, _width, height);

	//체력 넘버관련 
	if (_playerHP.currentHP > 99 && _playerHP.currentHP <= 999)
	{
		_playerHP.hpFont[0].frameX = _playerHP.currentHP / 100;
		_playerHP.hpFont[1].frameX = (_playerHP.currentHP % 100) / 10;
		_playerHP.hpFont[2].frameX = (_playerHP.currentHP % 10);
	}
	if (_playerHP.currentHP < 99 && _playerHP.currentHP <= 999)
	{
		_playerHP.hpFont[0].frameX = _playerHP.currentHP / 100;
		_playerHP.hpFont[1].frameX = (_playerHP.currentHP % 100) / 10;
		_playerHP.hpFont[2].frameX = (_playerHP.currentHP % 10);
	}
	
	if (_playerHP.currentHP > 9 && _playerHP.currentHP <= 99)
	{
		_playerHP.hpFont[0].frameX = _playerHP.currentHP / 10;
		_playerHP.hpFont[1].frameX = _playerHP.currentHP % 10;
		_playerHP.hpFont[2].frameX = 0;
		_playerHP.hpFont[2].renderOn = false;
	}

	
	if (_playerHP.currentHP >= 0 && _playerHP.currentHP <= 9)
	{
		_playerHP.hpFont[0].frameX = 0;
		_playerHP.hpFont[0].renderOn = false;
		_playerHP.hpFont[1].frameX = _playerHP.currentHP % 10;
		_playerHP.hpFont[2].frameX = 0;
		_playerHP.hpFont[2].renderOn = false;
	}

	if (_playerHP.currentHP < 0) _playerHP.currentHP = 0;
	

	//하트 넘버관련

	if (_playerHT.currentHEART > 9 && _playerHT.currentHEART <= 99)
	{
		_playerHT.heartFont[0].frameX = _playerHT.currentHEART / 10;
		_playerHT.heartFont[1].frameX = _playerHT.currentHEART % 10;
		_playerHT.heartFont[2].frameX = 0;
		_playerHT.heartFont[2].renderOn = false;
	}
	 if (_playerHT.currentHEART >= 0 && _playerHT.currentHEART <= 9)
	{
		 _playerHT.heartFont[0].frameX = _playerHT.currentHEART % 10;
		 _playerHT.heartFont[1].frameX = 0;
		 _playerHT.heartFont[1].renderOn = false;
		 _playerHT.heartFont[2].frameX = 0;
		 _playerHT.heartFont[2].renderOn = false;
	
	}
	 

	//if (_count % 4 == 0)
	//{
	//	progressTOP->setFrameX(progressTOP->getFrameX() + 1);
	//	_currentFrameX++;
	//
	//	if (_currentFrameX > progressTOP->getFrameX()) _currentFrameX = 0;
	//}

	 _count++;

     if (_width >= 100)
     {
		if (_count % 4 == 0)
		{
			progressTOP->setFrameX(progressTOP->getFrameX() + 0);
			_currentFrameX++;
	
			if (_currentFrameX > progressTOP->getMaxFrameX())
			{
				_currentFrameX = 0;
			}
		}
		//_count++;
	 }

	

	if (_count % 8 == 0)
	{
		heart->setFrameX(heart->getFrameX() + 1);
		_currentFrameX++;

		if (_currentFrameX > heart->getFrameX()) _currentFrameX = 0;

		_count++;
	}

	
	

}


void UI::render(const char* topBar, const char* backBar,const char* magic)
{
	IMAGEMANAGER->findImage("뒷게이지")->render(getMemDC(), 0, 0);
	IMAGEMANAGER->findImage("하트")->frameRender(getMemDC(), 96, 22, _currentFrameX, 0);
	if(_width == 100) IMAGEMANAGER->findImage("앞게이지")->frameRender(getMemDC(), 60, 10, _currentFrameX, 0);
	else IMAGEMANAGER->findImage("앞게이지2")->render(getMemDC(), 60, 10, 0, 0, _width,10);
	
	for (int i = 0; i < 3; i++)
	{
		if (!_playerHP.hpFont[i].renderOn) continue;
		_playerHP.hpFont[i].img->frameRender(getMemDC(),
			_playerHP.hpFont[i].x, _playerHP.hpFont[i].y,
			_playerHP.hpFont[i].frameX, 0);
	}

	for (int i = 0; i < 2; i++)
	{
		if (!_playerHT.heartFont[i].renderOn) continue;
		_playerHT.heartFont[i].img->frameRender(getMemDC(),
			_playerHT.heartFont[i].x, _playerHT.heartFont[i].y
			, _playerHT.heartFont[i].frameX, 0);
	}
}
void UI::MANA(float magic)
{
	currentMP -= magic;
}

void UI::setGauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge) * 100;

}