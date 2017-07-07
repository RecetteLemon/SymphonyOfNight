#pragma once
#include "gameNode.h"
#include "objTest.h"
#include "loadingScene.h"
#include "titleScene.h"
#include "inventoryScene.h"
#include "characterScene.h"
#include "familiarScene.h"
#include "openingScene.h"
#include "Scene_Map1.h"
#include "Scene_Map2.h"
#include "Scene_Map3.h"
#include "Scene_Map4.h"

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

