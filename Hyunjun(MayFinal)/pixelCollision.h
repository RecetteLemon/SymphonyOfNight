#pragma once
#include "gameNode.h"

enum COLLISION
{
	LEFT, TOP, RIGHT, BOTTOM, COLLISION_END
};

class pixelCollision : public gameNode
{
public:


private:
	

	COLORREF _color;
	int _r, _g, _b;;
	float _probeX, _probeY;					//탐색 좌표

	bool _colli[COLLISION_END];				//충돌 판정 유무

public:
	
	//픽셀 충돌 상하좌우 함수
	void pixelColliTop(int fromCheckX, int fromCheckY, image* pixelImage, float& checkX, float& checkY, int scale);
	void pixelColliBottom(int fromCheckX, int fromCheckY, image* pixelImage, float& checkX, float& checkY, int scale);
	void pixelColliRight(int fromCheckX, int fromCheckY, image* pixelImage, float& checkX, float& checkY, int scale);
	void pixelColliLeft(int fromCheckX, int fromCheckY, image* pixelImage, float& checkX, float& checkY, int scale);


	bool pixelColliState(COLLISION colli) { return _colli[colli]; } // 충돌 판정 접근자

	pixelCollision();
	~pixelCollision();
};

