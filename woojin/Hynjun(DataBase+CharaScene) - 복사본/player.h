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
	DIR_RIGHT_SUPER_JUMP,	// �������� �Ҷ�
	DIR_LEFT_SUPER_JUMP,
	DIR_RIGHT_FALL,			// ��������
	DIR_LEFT_FALL,
	DIR_RIGHT_ATK,			// �Ϲ� �����Ҷ�
	DIR_LEFT_ATK,
	DIR_RIGHT_AIR_ATK,		// �����߿� �����Ҷ�
	DIR_LEFT_AIR_ATK,
	DIR_RIGHT_HIT,			// �¾�����
	DIR_LEFT_HIT,
	DIR_RIGHT_SKILL,		// ��ų����
	DIR_LEFT_SKILL
};

class player : public gameNode
{
private:
	bool _isOp;

	PLAYERDIRECTION _playerDir;	// �÷��̾� �ൿ

	image* _image[2];				
	float _x, _y, _gravity, _jumpForce;
	bool isDjump;
	

	RECT _rc_Hit;				// �ǰ�����
	RECT _rc_Atk;				// ��������

	animation* _playerMotion;	// ���
	pixelCollision _collision; // �ȼ� �浹

	// Ŀ�ǵ� ���� ����
	vector<KEYINPUT> _vCommand;
	vector<KEYINPUT>::iterator _viCommand;

	KEYINPUT _currentInput;
	KEYINPUT _prevInput;
	float keyTimer;

	// �۹и��� ���� ����
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

	// Ŀ�ǵ�
	void keyInput();
	void showInput();
	void checkCommand();

	// �����̱�
	static void rightMoving(void* obj);
	static void leftMoving(void* obj);

	// ����
	static void rightStopping(void* obj);
	static void leftStopping(void* obj);

	// �ɾ�����
	static void rightSitting(void* obj);
	static void leftSitting(void * obj);

	// ������
	static void rightFalling(void* obj);
	static void leftFalling(void* obj);

	// getter �� setter ����
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

