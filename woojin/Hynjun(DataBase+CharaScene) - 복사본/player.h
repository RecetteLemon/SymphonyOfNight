#pragma once
#include "gameNode.h"
#include "pixelCollision.h"
#include "familiarManager.h"

#define MOVESPEED 3.0f
#define JUMPFORCE 6.0f
#define GRAVITYPOWER 0.5f

enum KEYINPUT
{
	INPUT_LEFT,
	INPUT_LEFT_DOWN,
	INPUT_DOWN,
	INPUT_RIGHT_DOWN,
	INPUT_RIGHT,
	INPUT_LEFT_UP,
	INPUT_UP,
	INPUT_RIGHT_UP,
	INPUT_Z,
	INPUT_X,
	INPUT_S,
	INPUT_D,
	INPUT_NOT
};

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
	DIR_RIGHT_SUPER_JUMP,	// 슈퍼점프 할때
	DIR_LEFT_SUPER_JUMP,
	DIR_RIGHT_FALL,			// 떨어질때
	DIR_LEFT_FALL,
	DIR_RIGHT_ATK,			// 일반 공격할때
	DIR_LEFT_ATK,
	DIR_RIGHT_AIR_ATK,		// 점프중에 공격할때
	DIR_LEFT_AIR_ATK,
	DIR_RIGHT_HIT,			// 맞았을때
	DIR_LEFT_HIT,
	DIR_RIGHT_SKILL,		// 스킬쓸때
	DIR_LEFT_SKILL
};

class player : public gameNode
{
private:
	bool _isOp;

	PLAYERDIRECTION _playerDir;	// 플레이어 행동

	image* _image[2];				
	float _x, _y, _gravity, _jumpForce;
	bool isDjump;
	

	RECT _rc_Hit;				// 피격판정
	RECT _rc_Atk;				// 공격판정

	animation* _playerMotion;	// 모션
	pixelCollision _collision; // 픽셀 충돌

	// 커맨드 관련 변수
	vector<KEYINPUT> _vCommand;
	vector<KEYINPUT>::iterator _viCommand;

	KEYINPUT _currentInput;
	KEYINPUT _prevInput;
	float keyTimer;

	// 퍼밀리어 관련 변수
	familiarManager* _fm;
	float _fX, _fY;

	image* _imageName;

public:
	

	HRESULT init(float x, float y, image* img, bool isOp = false);
	void release();
	void update();
	void render(HDC hdc);

	void playerDirection();
	void opening();

	// 커맨드
	void keyInput();
	void showInput();
	void checkCommand();

	// 움직이기
	static void rightMoving(void* obj);
	static void leftMoving(void* obj);

	// 멈춤
	static void rightStopping(void* obj);
	static void leftStopping(void* obj);

	// 앉아있음
	static void rightSitting(void* obj);
	static void leftSitting(void * obj);

	// 떨어짐
	static void rightFalling(void* obj);
	static void leftFalling(void* obj);

	// getter 랑 setter 관련
	inline float getPlayerPosX() { return _x; }
	inline float getPlayerPosY() { return _y; }

	void setPlayerPosX(float x) { _x = x; }
	void setPlayerPosY(float y) { _y = y; }

	//inline const char* getImageName() { return _imageName; }

	PLAYERDIRECTION getPlayerDir() { return _playerDir; }
	void setPlayerDir(PLAYERDIRECTION dir) { _playerDir = dir; }

	animation* getPlayerMotion() { return _playerMotion; }
	void setPlayerMotion(animation* ani) { _playerMotion = ani; }

	void setFamiliarDirection(void);

	player();
	~player();
};

