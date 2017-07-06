#pragma once
#include "enemy.h"
#define FRAMECOUNT 500.0f
#define GRAVITY 5.0f

class Dracula : public enemy
{
private:

	RECT _Playerrc;
	bool _isLeft; //왼쪽에 있나 판정 

	
	float _gravity;
	float _fireCount;
	int _count, _fireSpeed;
	int _bCount; //불렛 카운트

	float _patternTime;
	int _patternRan; // 패턴을 정하는 변수
	
	bool Appear; //순간이동했다 나타나는 불값
	bool BossDead;
	float _reAppearTime; //순간이동 했다가 나타나는 딜레이
	float _maxReAppearTime; //일정한 시간 후에 나타남

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


