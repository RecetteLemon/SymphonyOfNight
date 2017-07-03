#pragma once
#include "gameNode.h"
#include "animation.h"
#include "objectCreate.h"

class symphonyOfNight : public gameNode
{
private:

	image* _image;
	animation* _playerMotion;
	
	objectCreate* _obj;

	RECT _rc;
	float _x, _y;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	

	symphonyOfNight();
	~symphonyOfNight();
};

