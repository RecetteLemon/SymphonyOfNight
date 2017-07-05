#pragma once
#include "gameNode.h"

enum EQUIP_POS
{
	FIRST, SECOND, THIRD, FOURTH, FIFTH, SIXTH, SEVENTH, EIGHTH, NINTH, TENTH, EQUIP_POS_END
};


class inventoryScene : public gameNode
{
private:

	int		_invenScroll;

	EQUIP_POS _equip;

	image* _invenUIImg;
	image* _itemSelect;

	float _x, _y;
	RECT _rc;

	bool _onInven;
public:

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void alucardSelect();
	void invenSelect();
	void invenDraw();

	inventoryScene();
	~inventoryScene();
};

