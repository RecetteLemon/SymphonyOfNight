#pragma once
#include "gameNode.h"
#include "animation.h"


class symphonyOfNight : public gameNode
{
private:

	image* _image;
	animation* _playerMotion;
	
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

