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
	float _probeX, _probeY;					//Ž�� ��ǥ

	bool _colli[COLLISION_END];				//�浹 ���� ����

public:
	
	//�ȼ� �浹 �����¿� �Լ�
	void pixelColliTop(int fromCheckX, int fromCheckY, image* pixelImage, float& checkX, float& checkY, int scale);
	void pixelColliBottom(int fromCheckX, int fromCheckY, image* pixelImage, float& checkX, float& checkY, int scale);
	void pixelColliRight(int fromCheckX, int fromCheckY, image* pixelImage, float& checkX, float& checkY, int scale);
	void pixelColliLeft(int fromCheckX, int fromCheckY, image* pixelImage, float& checkX, float& checkY, int scale);


	bool pixelColliState(COLLISION colli) { return _colli[colli]; } // �浹 ���� ������

	pixelCollision();
	~pixelCollision();
};

