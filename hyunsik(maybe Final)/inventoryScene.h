#pragma once
#include "gameNode.h"
#include "effect.h"
#include "hosuk.h"

class inventoryScene : public gameNode
{
private:
	
	image* _invenUIImg;
	effect* _ef;
	hosuk* _hs;
	const char* _sceneName;


public:

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	inventoryScene();
	~inventoryScene();
};

