#pragma once
#include "gameNode.h"

#define DROP_SPEED 2

class objectCreate : public gameNode
{
private:

	

	enum DROP_ITEM
	{
		HEART, GOLD, DROP_ITEM_END
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


	image* _itemImg;

public:

	virtual HRESULT init(float x, float y);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void heartMoving();

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

