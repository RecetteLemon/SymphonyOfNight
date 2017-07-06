#pragma once
#include "gameNode.h"


class titleScene : public gameNode
{
private:
	
	image* _image;
	animation* _start;

public:
	HRESULT init();
	void release();
	void update();
	void render();



	titleScene();
	~titleScene();
};

