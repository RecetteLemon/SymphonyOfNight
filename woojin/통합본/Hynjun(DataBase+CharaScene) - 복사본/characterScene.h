#pragma once
#include "gameNode.h"


class characterScene : public gameNode
{
private:
	RECT _menuRC[2];
	RECT _selectRC;

	float _selectX, _selectY;
	float _menuX, _menu1Y ,_menu2Y;

	bool _down;

public:


	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	characterScene();
	~characterScene();
};

