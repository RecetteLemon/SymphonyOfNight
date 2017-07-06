#pragma once
#include "gameNode.h"
#include "player.h"

#define BGFRAMECOUNT 120.0f

class openingScene : public gameNode
{
private:
	player* _player;

	image* _backImage;
	image* _realBackImage;

	image* _backGround;

	float _dx;
	float _dx1;
	float _frameCount;

	RECT loopRect;
	RECT loopRectTree1;
	RECT loopRectTree2;
	RECT loopRectTree3;
	
	int _frameX;
	float _bridgeImageSpeed;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void frameWork(void);

	HDC getFieldDC(void) { return _backImage->getMemDC(); }

	openingScene();
	~openingScene();
};

