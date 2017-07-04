#pragma once
#include "enemy.h"

// ����

// ��, �ι濡 �״� ���̴�.
// �÷��̾� ��ġ�� �������� ��, �Ʒ�, ���� �������� �����ȴ�.

class bat : public enemy
{
private:
	RECT _comeRange;		// �÷��̾ ���� ������ ������ �׶� �����δ�.

	float _waveRange;		// ���� �Ʒ��� �������� ����
	float _saveY;			// �� �Ʒ��� ������ ������ Y��ǥ�� �����ϴ� ��

	bool _upDown;			// �� ���� �������� �� �Ǵ� �Ʒ��� ��������.
	bool _moveLeft;			// ���� ���������� �������� �Ǵ��ϴ� ����
	bool _move;				// ������ ���� ���� ��Ʈ���� �ȿ� ���� �׶� ��� X��ǥ ����
	bool _comePlayerY;		// �÷��̾� ��ǥ�� Y���� �Դ�?				  Y��ǥ ����

	// �׽�Ʈ ������ �ʿ��Ѱ�

public:
	//				�̹��� �̸�			��ġx,	 y
	HRESULT init(const char* imageName, float x, float y);
	void release();
	void update();
	void render();

	void imageInit();
	void move();

	// ������
	RECT getBatRect() { return _enemyInfo.rc; }
	//			������ ���� ��Ʈ
	RECT getBatComeRangeRect() { return _comeRange; }
	int getBatAtk() { return _enemyInfo.atk; }

	// ������
	void setBatHP(int HP) { _enemyInfo.hp = HP; }
	void setBatMove(bool move) { _move = move; }

	// ������ ������ �ϱ����� �ʿ��ϴ�.


	bat();
	~bat();
};

