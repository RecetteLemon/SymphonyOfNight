#pragma once
#include "gameNode.h"
#include "pixelCollision.h"
#define DROP_SPEED 8

class objectCreate : public gameNode
{
private:

	map<int, string> _randomCreateItem;

	int _pickRandom;
	int _pickObj;
	float _elapsedTime;

private:

	pixelCollision* _pixel;

	enum DROP_ITEM
	{
		HEART, GOLD, DROP_I, DROP_ITEM_END
	};

	float		_x, _y, _startX;
	float		_checkY;
	float		_countX;
	RECT		_rc;
	bool		_onDropItem;
	bool		_onBottomItem;
	int			_gold;
	int			_heart;
	DROP_ITEM	_randomItem;


	image** _itemImg;
	image*	_objImg;


	int			_itemCurrentFrameX;
	int			_objCurrentFrameX;

public:

	virtual HRESULT init(float x, float y, int pickObj = 0);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void heartMoving();
	void randomSour();

	void gainItem(RECT rc);

	//=========================================================================Getter, Setter
	RECT getRect() { return _rc; }
	bool getOnDropItem() { return _onDropItem; }
	void setOnDropItem(bool item) { _onDropItem = item; }

	DROP_ITEM getItem() { return _randomItem; }
	int getGold() { return _gold; }
	int getHeart() { return _heart; }

	

	objectCreate();
	~objectCreate();
};

