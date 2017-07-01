#pragma once
#include "gameNode.h"


class UI : public gameNode
{
private:
	RECT _rcprogress;

	int _x, _y;
	float width, height;

	float currentWidth, currentHeight;

	image* progressBottom;
	image* progressTOP;
	image* heart;

	int _currentFrameX;
	int _count;


public:

	HRESULT init(int x, int y, int width, int height, const char* topBar, const char* backBar, const char* magic);
	void release();
	void update();
	void render(const char* topBar, const char* backBar, const char* magic);

	void setGauge(float currentGauge, float maxGauge);

	//������ �� ��ġ ���� �Ծ�
	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }
	UI();
	~UI();
};

