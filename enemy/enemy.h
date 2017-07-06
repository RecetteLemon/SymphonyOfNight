#pragma once
#include "gameNode.h"
#include "animation.h"
#include "pixelCollision.h"
#include "bullet.h"
#include <vector>



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
		DRACULA_RIGHT_DEAD,
		DRACULA_LEFT_DEAD,
		DRACULA_RIGHT_TURN,
		DRACULA_LEFT_TURN,
		DRACULA_DAMAGED, //데미지를 입었을때
		DRACULAMONSTER_RIGHT_IDLE,
		DRACULAMONSTER_LEFT_IDLE,
		DRACULAMONSTER_RIGHT_ATTCK,
		DRACULAMONSTER_LEFT_ATTCK,
		DRACULAMONSTER_RIGHT_JUMP,
		DRACULAMONSTER_LEFT_JUMP,
		DRACULAMONSTER_RIGHT_SUPERJUMP,
		DRACULAMONSTER_LEFT_SUPERJUMP

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
	struct tagEnemyInfo
	{
		STAT stat;				// 적의 상태값
		image* enemyImage;		// 적의 이미지
		image* MonsterImage;    // 보스 변신 후 이미지
		animation* enemyAni[ENEMY_ANI_END];	// 적의 프레임 애니메이션 설정
		animation* bossAni;

		RECT rc; // 적의 피격 렉트
		RECT playerRc; // 받아올 플레이어의 렉트
		RECT damageRc;

		float x, y; // 적의 좌표값
		float speed;	//적의 속도
		float attackTime;
		float moveRange;

		int atk, hp; // 적의 공격력 체력

		bool die; // 죽었니 살았니
		bool attack;

		bool fire; // 보스가 불을 쏘냐?

		bool Jump; // 보스가 점프하냐?
	};
	

protected:
	DIRECTION _direction;
	tagEnemyInfo _enemyInfo;
	pixelCollision* _px;

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
	virtual HRESULT init(const char* imageName, float x, float y, float moveRange);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//------------------------------------------------- 다른 함수들

	// 패턴 함수
	virtual void move() = 0;
	virtual void imageInit() = 0;


	void getPlayerRect(RECT playerRc);


	enemy();
	~enemy();
};

