#pragma once
#include "familiar.h"
#include "animation.h"

class familiarFairy : public familiar
{
private:
	image* _body;
	image* _wing;
	image* _hair;

	animation* _bodyMotion;
	animation* _wingMotion;
	animation* _hairMotion;

public:
	virtual HRESULT init(const char* imageName, float* x, float* y);
	virtual void update(void);
	virtual void move(void);
	virtual void render(void);

	familiarFairy();
	virtual ~familiarFairy();
};
