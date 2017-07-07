#pragma once
#include "enemy.h"

// �� �ذ�

// �� ���� ���ϼ��� ���� ���̴�. ���࿡ �÷��̾�� ������ ���� ���ذ� �ȴ�.
// ������ �ð��� ������ �� ������ �������� �ٽ� �̵��Ѵ�.
class bloodSkeleton : public enemy
{
private:
	RECT _leftRect, _rightRect; // �̵� ���� ����
	RECT _comeRange;			// ���� ����
	
	float _maxReviveTime; // �� �ð��� ������ ��Ƴ�
	float _reviveTime; // ��Ƴ��� ������? _reviveTime += getElieceTIme; < �� �κ�

	bool _isLeft; // ����, ������ �̵� ����

public:
	//				�̹��� �̸�			��ġ x,  y			������ ����
	HRESULT init(const char* imageName, float x, float y, float moveRange);
	void release();
	void update();
	void render();

	
	void imageInit();	// �̹��� ���� ���� (�ִϸ��̼��̳� �̹��� ����)
	void move();	// �������� �ٲٰ� �̵��ϴ� �׷� �Լ�

	// �ִϸ��̼��� ������ �ٸ� �ִϸ��̼����� �ٲٴ� ��
	static void leftRevive(void* obj);
	static void rightRevive(void* obj);

	// ������
	RECT getSkeletonRect() { return _enemyInfo.rc; }
	int getSkeletonAtk() { return _enemyInfo.atk; }
	
	// ������
	void setSkeletonHP(int HP) { _enemyInfo.hp = HP; }
	void setSkeletonDirection(bool direction) { _isLeft = direction; }

	STAT getSkeletonStat() { return _enemyInfo.stat; }
	void setSkeletonStat(STAT stat) { _enemyInfo.stat = stat; }


	void setSkeletonDie(bool die) { _enemyInfo.die = die; }

	bloodSkeleton();
	~bloodSkeleton();
};

