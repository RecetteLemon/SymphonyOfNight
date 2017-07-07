#pragma once
#include "gameNode.h"

//플레이어 체력숫자 관련
struct HPFONT
{
	float x, y;
	image* img;
	int frameX;
	bool renderOn;
};

struct HEARTFONT
{
	float x, y;
	image* img;
	int frameX;
	bool renderOn;
};

typedef struct PLAYERHPINFO
{
	int currentHP;
	HPFONT hpFont[3];
	int currentHEART;
	HEARTFONT heartFont[2];
	RECT rc;

} PLAYERHPINFO;


class UI : public gameNode
{
private:
	RECT _rcprogress;
	
	int _x, _y;
	float _width, height;

	float maxMP, currentMP;
	float currentMg;

	float currentWidth, currentHeight;
	UI* _mpBar;
	image* progressBottom;
	image* progressTOP;
	image* progressTOP2;
	image* heart;
	image* number;
	image* Hnumber;
	
	RECT _rc;
	RECT _rc2;
	RECT _rc3;

	int _currentFrameX;
	int _count;
	int _count2;

	PLAYERHPINFO _playerHP, _playerHT;

public:
	HRESULT init(int x, int y, int width, int height, const char* topBar, const char* backBar, const char* magic);
	void release();
	void update();
	void render(const char* topBar, const char* backBar, const char* magic);
	void MANA(float magic);

	void setGauge(float currentGauge, float maxGauge);
	float getMP(void) { return currentMP; }
	void setHP(float hp) { _playerHP.currentHP -= hp; }
	void setHP2(float hp2) { _playerHP.currentHP += hp2; }
	void setHT(float ht) { _playerHT.currentHEART -= ht; }
	void setHT2(float ht2) { _playerHT.currentHEART += ht2; }
	
	inline RECT getRect(void) { return _rc; }
	inline RECT getRect2(void) { return _rc2; }
	inline RECT getRect3(void) { return _rc3; }

	
	//게이지 바 위치 조절 함쑤
	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }

	UI();
	~UI();
};

