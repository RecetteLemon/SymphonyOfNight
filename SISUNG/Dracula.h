#pragma once
#include "enemy.h"

enum DRACULAPHASE
{
	Phase1,
	Phase2
};

enum DRACULADIRECTION
{
	DRACULA_RIGHT_STOP,
	DRACULA_LEFT_STOP,
	DRACULA_RIGHT_JUMP,
	DRACULA_LEFT_JUMP,
	DRACULA_RIGHT_ATTK,
	DRACULA_LEFT_ATTK

};


struct DRACULAINFO
{
	image* BOSSImage; // 드라큘라이미지

	RECT rc; // 적의 피격 렉트

	float x, y; // 적의 좌표값

	int atk, hp; // 적의 공격력 체력

	bool fire; // 불을 쏘냐?

	bool Jump; // 점프하냐?

	float gravity;

	float timer;


};
class Dracula : public enemy
{

private:

	DRACULAPHASE _DraculaPhase;
	DRACULADIRECTION _DraculaDirection;
	DRACULAINFO _DraculaInfo;

	animation* _DraculaMotion;

	image* _Draculaimage;
	image* _Monsterimage;


	int _count;
	int _fireCount;
	int _rndFireCount;


public:

	HRESULT init();
	void release();
	void update();
	void render();
	void move();


	DRACULADIRECTION getDraculaDirection(void) { return _DraculaDirection; }
	void setDraculaDirection(DRACULADIRECTION direction) { _DraculaDirection = direction; }

	animation* getDraculaMotion(void) { return _DraculaMotion; }
	void setDraculaMotion(animation* ani) { _DraculaMotion = ani; }



	Dracula();
	~Dracula();
};

