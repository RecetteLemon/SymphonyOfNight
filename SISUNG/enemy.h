#pragma once
#include "gameNode.h"
#include "animation.h"
#include "Bullet.h"


class enemy : public gameNode
{
protected:
	//보스 드라큘라 단계
	enum DRACULAPHASE
	{
		PHASE1,  //변신전
		PHASE2  //변신후
	};

	//보스 행동 패턴
	enum DRACULADIRECTION
	{
		DRACULA_RIGHT_IDLE, //오른쪽 정지상태
		DRACULA_LEFT_IDLE,  //왼쪽 정지상태
		DRACULA_RIGHT_JUMP, //오른쪽 점프모션
		DRACULA_LEFT_JUMP,  //왼쪽 점프모션
		DRACULA_RIGHT_BULLETATTK,  //오른쪽 불꽃공격
		DRACULA_LEFT_BULLETATTK,   //왼쪽 불꽃공격
		DRACULA_RIGHT_BALLATTK,   //오른쪽 파이어볼 공격
		DRACULA_LEFT_BALLATTK,   //오른쪽 파이어볼 공격
		DRACULA_RIGHT_MOVE,  //오른쪽 이동 
		DRACULA_LEFT_MOVE,   //왼쪽 이동
		DRACULA_RIGHT_CHANGE,  //오른쪽 변화모션
		DRACULA_LEFT_CHANGE,   //왼쪽 변화모션
		DRACULA_DAMAGED //데미지를 입었을때
		
	};
	
	


	// 프레임 배열값 변경 기준
	enum DIRECTION
	{
		ENEMY_LEFT, // 왼쪽을 보고있다
		ENEMY_RIGHT // 오른쪽을 보고있다
	};

	// 상태값
	enum STAT
	{
		ENEMY_LEFT_MOVE,
		ENEMY_RIGHT_MOVE,
		ENEMY_LEFT_REVIVE,	// 스켈만이 살아나는 상태값
		ENEMY_RIGHT_REVIVE, //  위랑 같음
		ENEMY_LEFT_DIE,
		ENEMY_RIGHT_DIE
	};
	// 적의 정보
	struct ENEMYINFO
	{
		STAT stat;				// 적의 상태값
		image* enemyImage;		// 적의 이미지
		image* MonsterImage;    // 보스 변신 후 이미지
		animation* enemyAni;	// 적의 프레임 애니메이션 설정

		DRACULAPHASE _DraculaPhase; //드라큘라의 변화 상태값
		DRACULADIRECTION _DraculaDirection;  // 드라큘라의 모션 상태값


		RECT rc; // 적의 피격 렉트

		float x, y; // 적의 좌표값

		int atk, hp; // 적의 공격력 체력
		
		int exp;

		bool die; // 죽었니 살았니
		
		bool fire; // 보스가 불을 쏘냐?

		bool Jump; // 보스가 점프하냐?
	};

protected:
	DIRECTION _direction;
	ENEMYINFO _enemyInfo;

	//보스 단계와 방향 설정
	DRACULAPHASE _DraculaPhase;
	DRACULADIRECTION _DraculaDirection;
	
	//총알
	Bullet* _Bullet;

	int _count;
	float _currentHP;
	float _MaxHP;

public:
	//------------------------------------------------- 적 초기화, 업데이트, 그려줌
	//						찾아올 이미지 이름   위치 x,   y
	virtual HRESULT init(const char* imageName, float x, float y);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	
	//------------------------------------------------- 다른 함수들



	enemy();
	~enemy();
};

