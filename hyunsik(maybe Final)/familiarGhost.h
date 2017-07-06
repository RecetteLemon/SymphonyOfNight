#pragma once
#include "familiar.h"
#include "animation.h"
class familiarGhost : public familiar
{
private:
	image* _body;

	animation* _bodyMotion;

public:
	virtual HRESULT init(const char* imageName, float x, float y, float* playerPosX, float* playerPosY);
	virtual void update(void);
	virtual void move(void);
	virtual void render(void);
	virtual void setDirection(int direction) { _direction = (FAMILIARDIRECTION)direction; }
	familiarGhost();
	virtual ~familiarGhost();
};
