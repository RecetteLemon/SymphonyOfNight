#pragma once
#include "enemy.h"
#define FRAMECOUNT 500.0f
#define GRAVITY 5.0f

class Dracula : public enemy
{
private:

	RECT _Playerrc;
	bool _isLeft; //���ʿ� �ֳ� ���� 

	
	float _gravity;
	float _fireCount;
	int _count, _fireSpeed;
	int _bCount; //�ҷ� ī��Ʈ

	float _patternTime;
	int _patternRan; // ������ ���ϴ� ����
	
	bool Appear; //�����̵��ߴ� ��Ÿ���� �Ұ�
	bool BossDead;
	float _reAppearTime; //�����̵� �ߴٰ� ��Ÿ���� ������
	float _maxReAppearTime; //������ �ð� �Ŀ� ��Ÿ��

	float _frameCount;

	float _saveY;

public:

	HRESULT init(const char* imageName, float x, float y, float moveRange);
	void release();
	void update();
	void render();
	void appear();
	void setDraculaDirection();
	void setDraculaPhase();
	void fire(void);
	void patternSelect(void);

	void imageInit();
	void move();



	static void cbRightBulletFire(void* obj);
	
	static void cbLeftBulletFire(void* obj);

	static void cbRightBallFire(void* obj);
	
	static void cbLeftBallFire(void* obj);

	static void cbRightMonsterBulletFire(void* obj);

	static void cbLeftMonsterBulletFire(void* obj);

	static void cbRightTurnEnd(void* obj);

	static void cbLeftTurnEnd(void* obj);

	DRACULADIRECTION getDraculaDirection(void) { return _DraculaDirection; }
	void setDraculaDirection(DRACULADIRECTION direction) { _DraculaDirection = direction; }

	animation* getDraculaAnimation() { return _enemyInfo.bossAni; }
	void setDraculaAnimation(animation* ani) { _enemyInfo.bossAni = ani; }

	void setPattern(int pattern) { _patternRan = pattern; }

	

	Dracula();
	~Dracula();

};


