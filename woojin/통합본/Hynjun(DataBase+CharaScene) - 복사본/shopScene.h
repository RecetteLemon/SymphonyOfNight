#pragma once
#include "gameNode.h"


class shopScene : public gameNode
{
public:

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);


	shopScene();
	~shopScene();
};

