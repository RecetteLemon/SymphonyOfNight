#pragma once
#include "enemy.h"

// 박쥐

// 한, 두방에 죽는 몹이다.
// 플레이어 위치를 기준으로 위, 아래, 왼쪽 오른쪽이 결정된다.

class bat : public enemy
{
private:
	RECT _comeRange;		// 플레이어가 여기 안으로 들어오면 그때 움직인다.

	float _waveRange;		// 위랑 아래로 내려가는 범위
	float _saveY;			// 위 아래로 움직일 기준의 Y좌표를 저장하는 곳

	bool _upDown;			// 이 값을 기준으로 위 또는 아래로 내려간다.
	bool _moveLeft;			// 왼쪽 오른쪽으로 움질임을 판단하는 변수
	bool _move;				// 움직임 판정 위에 렉트범위 안에 오면 그때 사용 X좌표 판정
	bool _comePlayerY;		// 플레이어 좌표의 Y값에 왔니?				  Y좌표 판정

	// 테스트 용으로 필요한거

public:
	//				이미지 이름			위치x,	 y
	HRESULT init(const char* imageName, float x, float y);
	void release();
	void update();
	void render();

	void imageInit();
	void move();

	// 접근자
	RECT getBatRect() { return _enemyInfo.rc; }
	//			움직임 판정 렉트
	RECT getBatComeRangeRect() { return _comeRange; }
	int getBatAtk() { return _enemyInfo.atk; }

	// 설정자
	void setBatHP(int HP) { _enemyInfo.hp = HP; }
	void setBatMove(bool move) { _move = move; }

	// 지금은 실험을 하기위해 필요하다.


	bat();
	~bat();
};

