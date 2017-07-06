#pragma once
#include "gameNode.h"
#include "animation.h"
#include "Bullet.h"


class enemy : public gameNode
{
protected:
	//���� ���ŧ�� �ܰ�
	enum DRACULAPHASE
	{
		PHASE1,  //������
		PHASE2  //������
	};

	//���� �ൿ ����
	enum DRACULADIRECTION
	{
		DRACULA_RIGHT_IDLE, //������ ��������
		DRACULA_LEFT_IDLE,  //���� ��������
		DRACULA_RIGHT_JUMP, //������ �������
		DRACULA_LEFT_JUMP,  //���� �������
		DRACULA_RIGHT_BULLETATTK,  //������ �Ҳɰ���
		DRACULA_LEFT_BULLETATTK,   //���� �Ҳɰ���
		DRACULA_RIGHT_BALLATTK,   //������ ���̾ ����
		DRACULA_LEFT_BALLATTK,   //������ ���̾ ����
		DRACULA_RIGHT_MOVE,  //������ �̵� 
		DRACULA_LEFT_MOVE,   //���� �̵�
		DRACULA_RIGHT_CHANGE,  //������ ��ȭ���
		DRACULA_LEFT_CHANGE,   //���� ��ȭ���
		DRACULA_DAMAGED //�������� �Ծ�����
		
	};
	
	


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
		image* MonsterImage;    // ���� ���� �� �̹���
		animation* enemyAni;	// ���� ������ �ִϸ��̼� ����

		DRACULAPHASE _DraculaPhase; //���ŧ���� ��ȭ ���°�
		DRACULADIRECTION _DraculaDirection;  // ���ŧ���� ��� ���°�


		RECT rc; // ���� �ǰ� ��Ʈ

		float x, y; // ���� ��ǥ��

		int atk, hp; // ���� ���ݷ� ü��
		
		int exp;

		bool die; // �׾��� ��Ҵ�
		
		bool fire; // ������ ���� ���?

		bool Jump; // ������ �����ϳ�?
	};

protected:
	DIRECTION _direction;
	ENEMYINFO _enemyInfo;

	//���� �ܰ�� ���� ����
	DRACULAPHASE _DraculaPhase;
	DRACULADIRECTION _DraculaDirection;
	
	//�Ѿ�
	Bullet* _Bullet;

	int _count;
	float _currentHP;
	float _MaxHP;

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

