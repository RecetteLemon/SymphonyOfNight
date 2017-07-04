#pragma once
#include "gameNode.h"
#include "objTest.h"
#include "loadingScene.h"
#include "titleScene.h"


class symphonyOfNight : public gameNode
{
private:



public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	

	symphonyOfNight();
	~symphonyOfNight();
};

