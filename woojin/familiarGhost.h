#pragma once
#include "familiar.h"
#include "animation.h"
class familiarGhost : public familiar
{
private:
	image* _body;

	animation* _bodyMotion;

public:
	virtual HRESULT init(const char* imageName, float* x, float* y);
	virtual void update(void);
	virtual void move(void);
	virtual void render(void);

	familiarGhost();
	virtual ~familiarGhost();
};

