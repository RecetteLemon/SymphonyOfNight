#pragma once
#define IF_R if (_r == 255 && _g == 0 && _b == 0)


enum 
{
	TOP = 0,
	BOTTOM
};	

enum 
{
	LEFT = 2,
	RIGHT
};

class pixelCollision
{
private:

	COLORREF _color;
	int _r, _g, _b;;
	float _probeX, _probeY;					//Ž�� ��ǥ
public:

	int VerticalCollision(RECT rc, float destX, float destY, image* sourImage);		// ����
	int HorizontalCollision(RECT rc, float destX, float destY, image* sourImage);	// ����

	pixelCollision();
	~pixelCollision();
};

