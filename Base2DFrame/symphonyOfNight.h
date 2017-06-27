#pragma once
#include "gameNode.h"



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

