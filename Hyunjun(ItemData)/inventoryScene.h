#pragma once
#include "gameNode.h"

class inventoryScene : public gameNode
{
private:

	image* _invenUIImg;

public:

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	inventoryScene();
	~inventoryScene();
};

