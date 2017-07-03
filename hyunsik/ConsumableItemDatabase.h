#pragma once
#include "singletonBase.h"
#include <vector>
#include <map>

enum CATEGORY_C
{
	ONE_HAND,
	CATEGORY_C_END
};
enum cKind
{
	FOOD,
	POTION,
	cKInd_END
};

struct cItem
{
	string name;
	CATEGORY_C category;
	cKind cItemKind;
	int HP_;
	int str_;
	int con_;
	int int_;
	int lck_;
	string explanation;

	image* img_;

	cItem(){}
	~cItem(){}
};



class ConsumableItemDatabase : public singletonBase<ConsumableItemDatabase>
{
private:

	typedef vector<string>	arrCitems;
	typedef vector<string>::iterator iterCitems;
	typedef map<string, cItem*> arrCitem;
	typedef map<string, cItem*>::iterator iterCitem;

private:

	arrCitem _mTotalCitem;


public:
	HRESULT init();
	void release();
	void loadDatabase(string name);

	cItem* getCitemData(string str) { return _mTotalCitem.find(str)->second; }




	ConsumableItemDatabase();
	~ConsumableItemDatabase();
};

