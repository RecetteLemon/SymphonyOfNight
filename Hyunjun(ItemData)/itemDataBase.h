#pragma once
#include "singletonBase.h"

//============================================================================����������
enum CATEGORY_E
{
	ONE_HAND, TWO_HAND, HEAD, ARMOR, CAPE, ACCESSORY, CATEGORY_END
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
	string		description_;

	image*		img_;
	eItem() {};
	~eItem() {};
};

class equipment : public singletonBase<equipment>
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


	equipment();
	~equipment();
};