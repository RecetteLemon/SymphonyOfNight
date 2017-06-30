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
	image* BOSSImage; // ���ŧ���̹���

	RECT rc; // ���� �ǰ� ��Ʈ

	float x, y; // ���� ��ǥ��

	int atk, hp; // ���� ���ݷ� ü��

	bool fire; // ���� ���?

	bool Jump; // �����ϳ�?

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

