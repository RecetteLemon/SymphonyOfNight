#pragma once
#include "enemy.h"

// 피 해골

// 이 적은 죽일수는 없는 적이다. 만약에 플레이어에게 맞으면 뼈가 분해가 된다.
// 일정한 시간이 지나면 그 뼈들은 합쳐지고 다시 이동한다.
class bloodSkeleton : public enemy
{
private:
	RECT _leftRect, _rightRect; // 이동 범위 설정
	RECT _comeRange;			// 판정 범위
	
	float _maxReviveTime; // 이 시간이 지나면 살아남
	float _reviveTime; // 살아나는 딜레이? _reviveTime += getElieceTIme; < 이 부분

	bool _isLeft; // 왼쪽, 오른쪽 이동 판정

public:
	//				이미지 이름			위치 x,  y			움직일 범위
	HRESULT init(const char* imageName, float x, float y, float moveRange);
	void release();
	void update();
	void render();

	
	void imageInit();	// 이미지 넣을 공간 (애니메이션이나 이미지 값들)
	void move();	// 정보값을 바꾸고 이동하는 그런 함수

	// 애니메이션이 끝나면 다른 애니메이션으로 바꾸는 거
	static void leftRevive(void* obj);
	static void rightRevive(void* obj);

	// 접근자
	RECT getSkeletonRect() { return _enemyInfo.rc; }
	int getSkeletonAtk() { return _enemyInfo.atk; }
	
	// 설정자
	void setSkeletonHP(int HP) { _enemyInfo.hp = HP; }
	void setSkeletonDirection(bool direction) { _isLeft = direction; }

	STAT getSkeletonStat() { return _enemyInfo.stat; }
	void setSkeletonStat(STAT stat) { _enemyInfo.stat = stat; }


	void setSkeletonDie(bool die) { _enemyInfo.die = die; }

	bloodSkeleton();
	~bloodSkeleton();
};

