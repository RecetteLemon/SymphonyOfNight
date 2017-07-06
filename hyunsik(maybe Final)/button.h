#pragma once
#include "gameNode.h"

typedef void(*CALLBACK_FUNCTION)(void);

enum BUTTONDIRECTION
{
	BUTTONDIRECTION_NULL,
	BUTTONDIRECTION_UP,
	BUTTONDIRECTION_DOWN
};

class button : public gameNode
{
private:
	BUTTONDIRECTION _direction;

	const char* _imageName;
	image* _image;
	RECT _rc;
	float _x, _y;

	POINT _btnDownFramePoint;
	POINT _btnUpFramePoint;

	CALLBACK_FUNCTION _callbackFunction;

public:
	HRESULT init(const char* imageName, int x, int y,
		POINT btnDownFramePoint, POINT btnUpFramePoint,
		CALLBACK_FUNCTION cbFunction);
	void release(void);
	void update(void);
	void render(void);




	button();
	~button();
};

