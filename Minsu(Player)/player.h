#pragma once
#include "gameNode.h"
#include "pixelCollision.h"
#include "familiarManager.h"

#define MOVESPEED 3.0f
#define JUMPFORCE 5.0f
#define GRAVITYPOWER 10.0f

// �÷��̾� �ൿ����
enum PLAYERDIRECTION
{
	DIR_RIGHT_STOP,			// ����������
	DIR_LEFT_STOP,
	DIR_RIGHT_MOVE,			// �����϶�
	DIR_LEFT_MOVE,
	DIR_RIGHT_SIT,			// ������
	DIR_LEFT_SIT,
	DIR_RIGHT_BACKDASH,		// ��뽬 �Ҷ�
	DIR_LEFT_BACKDASH,
	DIR_RIGHT_JUMP,			// ���� �Ҷ�
	DIR_LEFT_JUMP,
	DIR_RIGHT_MOVE_JUMP,	// �����̸鼭 ���� �Ҷ�
	DIR_LEFT_MOVE_JUMP,
	DIR_RIGHT_FALL,			// ��������
	DIR_LEFT_FALL,
	DIR_RIGHT_ATK,			// �����Ҷ�
	DIR_LEFT_ATK,
	DIR_RIGHT_HIT,			// �¾�����
	DIR_LEFT_HIT,
	DIR_RIGHT_SKILL,		// ��ų����
	DIR_LEFT_SKILL
};

class player : public gameNode
{
private:
	PLAYERDIRECTION _playerDir;	// �÷��̾� �ൿ

	image* _image[2];			// �ΰ���
	float _x, _y, _gravity;		// �� ���ص� ��G��?

	RECT _rc_Hit;				// �ǰ�����
	RECT _rc_Atk;				// ��������

	animation* _playerMotion;	// ���

	pixelCollision _collision; // �ȼ� �浹

	familiarManager* _fm;

	float _fX, _fY;

public:
	HRESULT init(float x, float y);
	void release();
	void update();
	void render();

	// �����̱�
	static void rightMoving(void* obj);
	static void leftMoving(void* obj);

	// ����
	static void rightStopping(void* obj);
	static void leftStopping(void * obj);

	static void rightFalling(void* obj);
	static void leftFalling(void * obj);

	PLAYERDIRECTION getPlayerDir() { return _playerDir; }
	void setPlayerDir(PLAYERDIRECTION dir) { _playerDir = dir; }

	animation* getPlayerMotion() { return _playerMotion; }
	void setPlayerMotion(animation* ani) { _playerMotion = ani; }

	void setFamiliarDirection(void);

	player();
	~player();
};

