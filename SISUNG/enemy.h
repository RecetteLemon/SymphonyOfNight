#pragma once
#include "gameNode.h"


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

	// ���� ����
	struct ENEMYINFO
	{
		image* enemyImage; // ���� �̹���

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
	virtual HRESULT init();
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//------------------------------------------------- �ٸ� �Լ���



	enemy();
	~enemy();
};

