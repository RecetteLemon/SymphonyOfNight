#pragma once
#include "enemy.h"

// �� �ذ�

// �� ���� ���ϼ��� ���� ���̴�. ���࿡ �÷��̾�� ������ ���� ���ذ� �ȴ�.
// ������ �ð��� ������ �� ������ �������� �ٽ� �̵��Ѵ�.
class bloodSkeleton : public enemy
{
private:
	RECT _leftRect, _rightRect; // �̵� ���� ����
	

	float _speed; // �ӵ�
	float _maxReviveTime; // �� �ð��� ������ ��Ƴ�
	float _reviveTime; // ��Ƴ��� ������? _reviveTime += getElieceTIme; < �� �κ�

	bool _isLeft; // ����, ������ �̵� ����

public:
	//				�̹��� �̸�				�갡 ������ ��Ʈ ���� ���� ������		��ġ x,  y
	HRESULT init(const char* imageName, RECT leftRect, RECT rightRect, float x, float y);
	void release();
	void update();
	void render();

	
	void imageInit();	// �̹��� ���� ���� (�ִϸ��̼��̳� �̹��� ����)
	void statChange();	// �������� �ٲٰ� �̵��ϴ� �׷� �Լ�

	// �ִϸ��̼��� ������ �ٸ� �ִϸ��̼����� �ٲٴ� ��
	static void leftRevive(void* obj);
	static void rightRevive(void* obj);

	// ������
	RECT getSkeletonRect() { return _enemyInfo.rc; }
	int getSkeletonAtk() { return _enemyInfo.atk; }
	
	// ������
	void setSkeletonHP(int HP) { _enemyInfo.hp = HP; }

	STAT getSkeletonDirection() { return _enemyInfo.stat; }
	void setSkeletonDirection(STAT stat) { _enemyInfo.stat = stat; }

	animation* getSkeletonAnimation() { return _enemyInfo.enemyAni; }
	void setSkeletonAnimation(animation* ani) { _enemyInfo.enemyAni = ani; }

	bloodSkeleton();
	~bloodSkeleton();
};
