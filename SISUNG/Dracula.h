#pragma once
#include "enemy.h"
#define FRAMECOUNT 500.0f

class Dracula : public enemy
{

private:

	RECT _Playerrc;
	bool _isLeft; //왼쪽에 있나 판정 

	
	float gravity;
	int _count, _fireCount, _fireSpeed;
	int _bCount; //불렛 카운트
	
	bool Appear; //순간이동했다 나타나는 불값
	
	float _reAppearTime; //순간이동 했다가 나타나는 딜레이
	float _maxReAppearTime; //일정한 시간 후에 나타남

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


