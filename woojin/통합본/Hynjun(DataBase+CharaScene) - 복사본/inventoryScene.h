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
	int		_invenNum;
	int		_alucardNum;

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
	void alucardSelectDraw();
	void invenDraw();
	void statDraw();

	void invenPick();
	void sceneChange();

	inventoryScene();
	~inventoryScene();
};

