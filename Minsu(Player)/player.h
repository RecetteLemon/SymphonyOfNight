#pragma once
#include "gameNode.h"

#define MOVESPEED 2.0f

// 플레이어 행동패턴
enum PLAYERDIRECTION
{
	DIR_RIGHT_STOP,		// 멈춰있을때
	DIR_LEFT_STOP,
	DIR_RIGHT_MOVE,		// 움직일때
	DIR_LEFT_MOVE,
	DIR_RIGHT,TURN,		// 돌아설때
	DIR_LEFT_TURN,
	DIR_RIGHT_SIT,		// 앉을때
	DIR_LEFT_SIT,
	DIR_RIGHT_BACKDASH,	// 백대쉬 할때
	DIR_LEFT_BACKDASH,
	DIR_RIGHT_JUMP,		// 점프 할때
	DIR_LEFT_JUMP,
	DIR_RIGHT_DJUMP,	// 더블점프 할때
	DIR_LEFT_DJUMP,
	DIR_RIGHT_SJUMP,	// 슈퍼점프 할때
	DIR_LEFT_SJUMP,
	DIR_RIGHT_FALL,		// 떨어질때
	DIR_LEFT_FALL,
	DIR_RIGHT_ATK,		// 공격할때
	DIR_LEFT_ATK,
	DIR_RIGHT_HIT,		// 맞았을때
	DIR_LEFT_HIT,
	DIR_RIGHT_SKILL,	// 스킬쓸때
	DIR_LEFT_SKILL
};

class player : public gameNode
{
private:
	// 플레이어 행동
	PLAYERDIRECTION _playerDir;

	image* _image[2];	// 두개는
	float _x, _y;	// 말 안해도 알G용?

	RECT _rc_Hit;	// 피격판정
	RECT _rc_Atk;	// 공격판정

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

