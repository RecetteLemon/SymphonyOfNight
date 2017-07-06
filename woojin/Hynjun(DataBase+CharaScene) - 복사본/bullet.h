#pragma once
#include "gameNode.h"
#include <vector>
#define BULLETFRAMECOUNT 50.0f

struct tagBullet
{
	RECT rc;
	image* BulletImage;
	animation* _DraculaBullet;
	float x, y;
	float angle;
	float fireX, fireY;
	float speed;
	bool fire;
	int count;
	int frameX;
	int frameY;
	float frameCount;
};



class Bullet : public gameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	

	const char* _imageName;
	float _range;
	
	int _bulletMax;
	

public:
	HRESULT init(const char* imageName);
	void release(void);
	void update(void);
	void render(void);
	void fire(const char* imageName, float x, float y, float angle, float speed, bool isLeft);
	void move(void);
	void removeBullet(int arrNum);
	void frameWork(void);

	vector<tagBullet> &getVBullet(void) { return _vBullet; }
	vector<tagBullet>::iterator &getVIBullet(void) { return _viBullet; }


	Bullet();
	~Bullet();
};

