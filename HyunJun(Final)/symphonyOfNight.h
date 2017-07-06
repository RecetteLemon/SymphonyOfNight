#pragma once
#include "gameNode.h"
#include "objTest.h"
#include "loadingScene.h"
#include "titleScene.h"
#include "inventoryScene.h"
#include "characterScene.h"
#include "familiarScene.h"


class symphonyOfNight : public gameNode
{
private:



public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void deleteImage();

	symphonyOfNight();
	~symphonyOfNight();
};

