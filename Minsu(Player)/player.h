#pragma once
#include "gameNode.h"

#define MOVESPEED 2.0f

// �÷��̾� �ൿ����
enum PLAYERDIRECTION
{
	DIR_RIGHT_STOP,		// ����������
	DIR_LEFT_STOP,
	DIR_RIGHT_MOVE,		// �����϶�
	DIR_LEFT_MOVE,
	DIR_RIGHT,TURN,		// ���Ƽ���
	DIR_LEFT_TURN,
	DIR_RIGHT_SIT,		// ������
	DIR_LEFT_SIT,
	DIR_RIGHT_BACKDASH,	// ��뽬 �Ҷ�
	DIR_LEFT_BACKDASH,
	DIR_RIGHT_JUMP,		// ���� �Ҷ�
	DIR_LEFT_JUMP,
	DIR_RIGHT_DJUMP,	// �������� �Ҷ�
	DIR_LEFT_DJUMP,
	DIR_RIGHT_SJUMP,	// �������� �Ҷ�
	DIR_LEFT_SJUMP,
	DIR_RIGHT_FALL,		// ��������
	DIR_LEFT_FALL,
	DIR_RIGHT_ATK,		// �����Ҷ�
	DIR_LEFT_ATK,
	DIR_RIGHT_HIT,		// �¾�����
	DIR_LEFT_HIT,
	DIR_RIGHT_SKILL,	// ��ų����
	DIR_LEFT_SKILL
};

class player : public gameNode
{
private:
	// �÷��̾� �ൿ
	PLAYERDIRECTION _playerDir;

	image* _image[2];	// �ΰ���
	float _x, _y;	// �� ���ص� ��G��?

	RECT _rc_Hit;	// �ǰ�����
	RECT _rc_Atk;	// ��������

	animation* _playerMotion;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	static void rightMoving(void* obj);
	static void leftMoving(void* obj);

	PLAYERDIRECTION getPlayerDir() { return _playerDir; }
	void setPlayerDir(PLAYERDIRECTION dir) { _playerDir = dir; }

	animation* getPlayerMotion() { return _playerMotion; }
	void setPlayerMotion(animation* ani) { _playerMotion = ani; }

	player();
	~player();
};

