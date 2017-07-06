#include "stdafx.h"
#include "openingScene.h"

openingScene::openingScene()
	:_player(NULL)
{
}

openingScene::~openingScene()
{
}

HRESULT openingScene::init(void)
{
	IMAGEMANAGER->addImage("introBackGround", "introImage/Background1.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("introTree1", "introImage/intro_1-1.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("introTree2", "introImage/intro_2-1.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("introTree3", "introImage/intro_4-1.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("introEarth", "introImage/intro_3-1.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bridge", "introImage/bridge-1.bmp", 21012, 549, 17, 1, true, RGB(255, 0, 255));

	_dx = 0;
	_dx1 = 0;
	
	_frameCount = 0;
	
	loopRect = { 0, 0, WINSIZEX, WINSIZEY };
	loopRectTree1 = { 0, 0, WINSIZEX, WINSIZEY };
	loopRectTree2 = { 0, 0, WINSIZEX, WINSIZEY };
	loopRectTree3 = { WINSIZEX, 0, WINSIZEX * 2, WINSIZEY };

	_frameX = 0;

	_bridgeImageSpeed = WINSIZEX * 2;

	// 플레이어
	_player = new player;
	_player->init(-50, WINSIZEY - 210, NULL, true);

	return S_OK;
}
void openingScene::release()
{
	_player->release();
	SAFE_DELETE(_player);

	IMAGEMANAGER->deleteImage("introBackGround");
	IMAGEMANAGER->deleteImage("introTree1");
	IMAGEMANAGER->deleteImage("introTree2");
	IMAGEMANAGER->deleteImage("introTree3");
	IMAGEMANAGER->deleteImage("introEarth");

	
}
void openingScene::update()
{
	KEYANIMANAGER->update();

	if (_dx < 10000)
	{
		_dx += 20.0f;
		_dx1 += 25.0f;
	}
	else
	{
		if (loopRect.right > 10)
		{
			loopRect.left -= 20.0f;
			loopRect.right = loopRect.left + WINSIZEX;
		}
	}

	if (_dx >= 9200) frameWork();

	if (_dx > 1000)
	{
		if (loopRectTree2.right < 1800)
		{
			loopRectTree2.left -= 20.0f;
			loopRectTree2.right = loopRectTree2.left + WINSIZEX;
		}
	}

	if (_dx > 1800 && _dx < 5600)
	{
		if (_dx < 2335)
		{
			loopRectTree3.left -= 20.0f;
			loopRectTree3.right = loopRectTree3.left + WINSIZEX * 2;
		}
		else loopRectTree3 = { 0, 0, WINSIZEX, WINSIZEY };
	}
	else if (_dx >= 5600)
	{
		loopRectTree3.left -= 20.0f;
		loopRectTree3.right = loopRectTree3.left + WINSIZEX * 2;
	}

	if (_dx1 > 4000)
	{
		if (loopRectTree1.right < 4800)
		{
			loopRectTree1.left -= 25.0f;
			loopRectTree1.right = loopRectTree1.left + WINSIZEX;
		}
	}

	if (_dx > 9200 && _bridgeImageSpeed > 10) _bridgeImageSpeed -= 20;

	// player
	if (_player) _player->update();
	//-------
}
void openingScene::render()
{
	IMAGEMANAGER->findImage("introBackGround")->render(getMemDC(), 0, 0);
	
	if (_dx < 10000) IMAGEMANAGER->findImage("introEarth")->loopRender(getMemDC(), &loopRect, _dx, 0);
	else
	{
		IMAGEMANAGER->findImage("introEarth")->loopRender(getMemDC(), &loopRect, 10000, 0);
		
	}
	if ( _dx > 9200) IMAGEMANAGER->findImage("bridge")->frameRender(getMemDC(), _bridgeImageSpeed, 50, _frameX, 0);
	
	if (_dx > 1800 && _dx < 5600)
	{
		if (_dx < 2335) IMAGEMANAGER->findImage("introTree3")->loopRender(getMemDC(), &loopRectTree3, 0, 0);
		else IMAGEMANAGER->findImage("introTree3")->loopRender(getMemDC(), &loopRect, _dx, 0);
	}
	else if (_dx >= 5600)
	{
		IMAGEMANAGER->findImage("introTree3")->loopRender(getMemDC(), &loopRectTree3, 5600, 0);
	}

	//player 달려가기
	_player->render(getMemDC());
	//---------------

	if (_dx < 1000) IMAGEMANAGER->findImage("introTree2")->loopRender(getMemDC(), &loopRect, _dx, 0);
	else if (loopRectTree2.right < 1800) IMAGEMANAGER->findImage("introTree2")->loopRender(getMemDC(), &loopRectTree2, 1000, 0);

	if (_dx1 < 4000) IMAGEMANAGER->findImage("introTree1")->loopRender(getMemDC(), &loopRect, _dx1, 0);
	else if (loopRectTree1.right < 4800) IMAGEMANAGER->findImage("introTree1")->loopRender(getMemDC(), &loopRectTree1, 4000, 0);

//	SetTextColor(getMemDC(), RGB(255, 255,255));
//	char str[128];
//	sprintf(str, "%5.2f", _dx);
//	TextOut(getMemDC(), WINSIZEX / 2, 50, str, strlen(str));
//	sprintf(str, "%5.2f", _dx1);
//	TextOut(getMemDC(), WINSIZEX / 2, 70, str, strlen(str));
}

void openingScene::frameWork(void)
{
	if (_frameCount + BGFRAMECOUNT < GetTickCount())
	{
		_frameCount = GetTickCount();
		++_frameX;
		if (_frameX >= IMAGEMANAGER->findImage("bridge")->getMaxFrameX())
		{
			_frameX = IMAGEMANAGER->findImage("bridge")->getMaxFrameX();
			SCENEMANAGER->changeScene("맵1");
		
		}
	}
}