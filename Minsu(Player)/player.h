#pragma once
#include "gameNode.h"
#include "pixelCollision.h"
#include "familiarManager.h"

#define MOVESPEED 3.0f
#define JUMPFORCE 5.0f
#define GRAVITYPOWER 10.0f

// 플레이어 행동패턴
enum PLAYERDIRECTION
{
	DIR_RIGHT_STOP,			// 멈춰있을때
	DIR_LEFT_STOP,
	DIR_RIGHT_MOVE,			// 움직일때
	DIR_LEFT_MOVE,
	DIR_RIGHT_SIT,			// 앉을때
	DIR_LEFT_SIT,
	DIR_RIGHT_BACKDASH,		// 백대쉬 할때
	DIR_LEFT_BACKDASH,
	DIR_RIGHT_JUMP,			// 점프 할때
	DIR_LEFT_JUMP,
	DIR_RIGHT_MOVE_JUMP,	// 움직이면서 점프 할때
	DIR_LEFT_MOVE_JUMP,
	DIR_RIGHT_FALL,			// 떨어질때
	DIR_LEFT_FALL,
	DIR_RIGHT_ATK,			// 공격할때
	DIR_LEFT_ATK,
	DIR_RIGHT_HIT,			// 맞았을때
	DIR_LEFT_HIT,
	DIR_RIGHT_SKILL,		// 스킬쓸때
	DIR_LEFT_SKILL
};

class player : public gameNode
{
private:
	PLAYERDIRECTION _playerDir;	// 플레이어 행동

	image* _image[2];			// 두개는
	float _x, _y, _gravity;		// 말 안해도 알G용?

	RECT _rc_Hit;				// 피격판정
	RECT _rc_Atk;				// 공격판정

	animation* _playerMotion;	// 모션

	pixelCollision _collision; // 픽셀 충돌

	familiarManager* _fm;

	float _fX, _fY;

public:
	HRESULT init(float x, float y);
	void release();
	void update();
	void render();

	// 움직이기
	static void rightMoving(void* obj);
	static void leftMoving(void* obj);

	// 멈춤
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

