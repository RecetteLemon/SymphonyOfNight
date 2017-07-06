#pragma once
#include "gameNode.h"
#include "animation.h"
#include "pixelCollision.h"




class enemy : public gameNode
{
protected:
	// 프레임 배열값 변경 기준
	enum DIRECTION
	{
		ENEMY_LEFT, // 왼쪽을 보고있다
		ENEMY_RIGHT // 오른쪽을 보고있다
	};
	// 상태값
	enum STAT
	{
		ENEMY_LEFT_STAY,
		ENEMY_RIGHT_STAY,
		ENEMY_LEFT_MOVE,
		ENEMY_RIGHT_MOVE,
		ENEMY_LEFT_REVIVE,	// 스켈만이 살아나는 상태값
		ENEMY_RIGHT_REVIVE, //  위랑 같음
		ENEMY_LEFT_DIE,
		ENEMY_RIGHT_DIE,
		ENEMY_LEFT_ATTACK,
		ENEMY_RIGHT_ATTACK
	};

	enum ANI
	{
		ENEMY_LEFT_ATTACKANI,
		ENEMY_RIGHT_ATTACKANI,
		ENEMY_LEFT_STAYANI,
		ENEMY_RIGHT_STAYANI,
		ENEMY_LEFT_MOVEANI,
		ENEMY_RIGHT_MOVEANI,
		ENEMY_LEFT_REVIVEANI,
		ENEMY_RIGHT_REVIVEANI,
		ENEMY_LEFT_DIEANI,
		ENEMY_RIGHT_DIEANI,
		ENEMY_ANI_END
	};
	// 적의 정보
	struct ENEMYINFO
	{
		STAT stat;				// 적의 상태값
		image* enemyImage;		// 적의 이미지
		animation* enemyAni[ENEMY_ANI_END];	// 적의 프레임 애니메이션 설정

		RECT rc; // 적의 피격 렉트
		RECT playerRc; // 받아올 플레이어의 렉트
		RECT damageRc;

		float x, y; // 적의 좌표값
		float speed;	//적의 속도
		float attackTime;

		int atk, hp; // 적의 공격력 체력

		


		bool die; // 죽었니 살았니
		bool attack;
	};

protected:
	DIRECTION _direction;
	ENEMYINFO _enemyInfo;
	pixelCollision* _px;

public:
	//------------------------------------------------- 적 초기화, 업데이트, 그려줌
	//						찾아올 이미지 이름   위치 x,   y
	virtual HRESULT init(const char* imageName, float x, float y);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	

	//------------------------------------------------- 다른 함수들

	// 패턴 함수
	virtual void move();
	virtual void imageInit();


	void getPlayerRect(RECT playerRc);

	enemy();
	~enemy();
};

