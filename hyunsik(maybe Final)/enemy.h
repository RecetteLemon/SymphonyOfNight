#pragma once
#include "gameNode.h"
#include "animation.h"
#include "pixelCollision.h"




class enemy : public gameNode
{
protected:
	// ������ �迭�� ���� ����
	enum DIRECTION
	{
		ENEMY_LEFT, // ������ �����ִ�
		ENEMY_RIGHT // �������� �����ִ�
	};
	// ���°�
	enum STAT
	{
		ENEMY_LEFT_STAY,
		ENEMY_RIGHT_STAY,
		ENEMY_LEFT_MOVE,
		ENEMY_RIGHT_MOVE,
		ENEMY_LEFT_REVIVE,	// ���̸��� ��Ƴ��� ���°�
		ENEMY_RIGHT_REVIVE, //  ���� ����
		ENEMY_LEFT_DIE,
		ENEMY_RIGHT_DIE,
		ENEMY_LEFT_ATTACK,
		ENEMY_RIGHT_ATTACK
	};

	enum ANI
	{
		ENEMY_LEFT_ATTACKANI,
		ENEMY_RIGHT_ATTACKANI,
		ENEMY_LEFT_STAYANI,
		ENEMY_RIGHT_STAYANI,
		ENEMY_LEFT_MOVEANI,
		ENEMY_RIGHT_MOVEANI,
		ENEMY_LEFT_REVIVEANI,
		ENEMY_RIGHT_REVIVEANI,
		ENEMY_LEFT_DIEANI,
		ENEMY_RIGHT_DIEANI,
		ENEMY_ANI_END
	};
	// ���� ����
	struct ENEMYINFO
	{
		STAT stat;				// ���� ���°�
		image* enemyImage;		// ���� �̹���
		animation* enemyAni[ENEMY_ANI_END];	// ���� ������ �ִϸ��̼� ����

		RECT rc; // ���� �ǰ� ��Ʈ
		RECT playerRc; // �޾ƿ� �÷��̾��� ��Ʈ
		RECT damageRc;

		float x, y; // ���� ��ǥ��
		float speed;	//���� �ӵ�
		float attackTime;

		int atk, hp; // ���� ���ݷ� ü��

		


		bool die; // �׾��� ��Ҵ�
		bool attack;
	};

protected:
	DIRECTION _direction;
	ENEMYINFO _enemyInfo;
	pixelCollision* _px;

public:
	//------------------------------------------------- �� �ʱ�ȭ, ������Ʈ, �׷���
	//						ã�ƿ� �̹��� �̸�   ��ġ x,   y
	virtual HRESULT init(const char* imageName, float x, float y);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	

	//------------------------------------------------- �ٸ� �Լ���

	// ���� �Լ�
	virtual void move();
	virtual void imageInit();


	void getPlayerRect(RECT playerRc);

	enemy();
	~enemy();
};

