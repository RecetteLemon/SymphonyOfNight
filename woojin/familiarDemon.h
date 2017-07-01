#pragma once
#include "familiar.h"
#include "animation.h"

class familiarDemon : public familiar
{
private:
	image* _body;
	image* _wing;

	animation* _bodyMotion;
	animation* _wingMotion;

public:
	virtual virtual HRESULT init(const char* imageName, float* x, float* y);
	virtual void update(void);
	virtual void move(void);
	virtual void render(void);

	static void cbRightAttack(void* obj);
	static void cbLeftAttack(void* obj);

	familiarDemon();
	virtual ~familiarDemon();
};

