#pragma once
#include "gameNode.h"


struct tagMenu
{
	image* image;
	
	RECT rc;
	
	float x, y;
	int kind;
	bool on;

};

class familiarScene : public gameNode
{
private:



	tagMenu _demon;
	tagMenu _ghost;
	tagMenu _fairy;


	RECT _unkown;
	RECT _selectRC;

	

	float _x, _y;
	float _selectX, _selectY;
	int _kind;
	int _unkown1;

	bool _on;

	

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	

	familiarScene();
	~familiarScene();
};

