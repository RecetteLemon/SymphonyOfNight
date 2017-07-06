#pragma once
#include "enemy.h"
#define FRAMECOUNT 500.0f

class Dracula : public enemy
{

private:

	RECT _Playerrc;
	bool _isLeft; //���ʿ� �ֳ� ���� 

	
	float gravity;
	int _count, _fireCount, _fireSpeed;
	int _bCount; //�ҷ� ī��Ʈ
	
	bool Appear; //�����̵��ߴ� ��Ÿ���� �Ұ�
	
	float _reAppearTime; //�����̵� �ߴٰ� ��Ÿ���� ������
	float _maxReAppearTime; //������ �ð� �Ŀ� ��Ÿ��

	float _frameCount;

public:

	HRESULT init(const char* imageName, float x, float y);
	void release();
	void update();
	void render();
	void appear();
	void setDraculaDirection();
	void setDraculaPhase();
	void fire(void);


	static void cbRightBulletFire(void* obj);
	
	static void cbLeftBulletFire(void* obj);

	static void cbRightBallFire(void* obj);
	
	static void cbLeftBallFire(void* obj);

	DRACULADIRECTION getDraculaDirection(void) { return _DraculaDirection; }
	void setDraculaDirection(DRACULADIRECTION direction) { _DraculaDirection = direction; }

	animation* getDraculaAnimation() { return _enemyInfo.enemyAni; }
	void setDraculaAnimation(animation* ani) { _enemyInfo.enemyAni = ani; }

	

	Dracula();
	~Dracula();

};


