#pragma once
#include "singletonBase.h"

//============================================================================����������
enum CATEGORY_E
{
	DAGGER, SWORD, SUB, HEAD, ARMOR, ACCESSORY, CAPE, FOOD, POTION, CATEGORY_END
};

//============================================================================�����̻� ���
enum CCT
{
	STONE, POISON, NONE, CCT_END
};


//============================================================================������ ���� ����ü
struct eItem
{
	string		name_;
	CATEGORY_E	category_;
	CCT			cct_;
	int			atk_;
	int			atkSpd_;
	int			def_;
	int			str_;
	int			con_;
	int			int_;
	int			lck_;
	int			HP_;
	string		description_;
	int			gold_;

	image*		img_;
	eItem() {};
	~eItem() {};
};

class allItem : public singletonBase<allItem>
{
private:
	typedef vector<string> arrEitem;
	typedef vector<string>::iterator iterEitem;
	typedef map<string, eItem*> mArrEitem;
	typedef map<string, eItem*>::iterator mIterEitem;

private:
	mArrEitem _mTotalEitem;

public:
	HRESULT init();
	void release();

	void loadDatabase(string name);

	//������
	eItem* getData(string str) { return _mTotalEitem.find(str)->second; }


	allItem();
	~allItem();
};


