#pragma once
#include "enemy.h"
class hosuk : public enemy
{
public:

	//실험용변수
	float playerX,playerY;
	
	float _count;



	virtual HRESULT init(const char* imageName, float x, float y);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	virtual void imageInit();
	virtual void move();


	RECT getHosukRC(void) { return _enemyInfo.rc; }


	void setHosukHP(int HP);
	//bool setHosukDie(bool die) { _enemyInfo.die = die; }



	hosuk();
	~hosuk();
};

