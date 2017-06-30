#pragma once
#include "gameNode.h"
#include "animation.h"


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
		ENEMY_LEFT_MOVE,
		ENEMY_RIGHT_MOVE,
		ENEMY_LEFT_REVIVE,	// ���̸��� ��Ƴ��� ���°�
		ENEMY_RIGHT_REVIVE, //  ���� ����
		ENEMY_LEFT_DIE,
		ENEMY_RIGHT_DIE
	};
	// ���� ����
	struct ENEMYINFO
	{
		STAT stat;				// ���� ���°�
		image* enemyImage;		// ���� �̹���
		animation* enemyAni;	// ���� ������ �ִϸ��̼� ����

		RECT rc; // ���� �ǰ� ��Ʈ

		float x, y; // ���� ��ǥ��

		int atk, hp; // ���� ���ݷ� ü��
		int exp;

		bool die; // �׾��� ��Ҵ�
	};

protected:
	DIRECTION _direction;
	ENEMYINFO _enemyInfo;


public:
	//------------------------------------------------- �� �ʱ�ȭ, ������Ʈ, �׷���
	//						ã�ƿ� �̹��� �̸�   ��ġ x,   y
	virtual HRESULT init(const char* imageName, float x, float y);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//------------------------------------------------- �ٸ� �Լ���



	enemy();
	~enemy();
};

